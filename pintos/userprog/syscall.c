#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/loader.h"
#include "userprog/gdt.h"
#include "threads/flags.h"
#include "intrinsic.h"
#include "console.h"
#include "threads/mmu.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "threads/synch.h"
#include "threads/palloc.h"

void syscall_entry(void);
void syscall_handler(struct intr_frame *);
void check_address(void *addr);
void sys_exit(int status);
static bool sys_create(const char *file, unsigned initial_size);
static int sys_open(const char *file);
static void sys_close(int fd);
static int sys_read(int fd, void *buffer, unsigned size);
static int sys_write(int fd, void *buffer, unsigned size);
static int sys_filesize(int fd);

/* System call.
 *
 * Previously system call services was handled by the interrupt handler
 * (e.g. int 0x80 in linux). However, in x86-64, the manufacturer supplies
 * efficient path for requesting the system call, the `syscall` instruction.
 *
 * The syscall instruction works by reading the values from the the Model
 * Specific Register (MSR). For the details, see the manual. */

#define MSR_STAR 0xc0000081			/* Segment selector msr */
#define MSR_LSTAR 0xc0000082		/* Long mode SYSCALL target */
#define MSR_SYSCALL_MASK 0xc0000084 /* Mask for the eflags */

static struct lock filesys_lock;

void syscall_init(void)
{
	lock_init(&filesys_lock); // 락 초기화
	write_msr(MSR_STAR, ((uint64_t)SEL_UCSEG - 0x10) << 48 |
							((uint64_t)SEL_KCSEG) << 32);
	write_msr(MSR_LSTAR, (uint64_t)syscall_entry);

	/* The interrupt service rountine should not serve any interrupts
	 * until the syscall_entry swaps the userland stack to the kernel
	 * mode stack. Therefore, we masked the FLAG_FL. */
	write_msr(MSR_SYSCALL_MASK,
			  FLAG_IF | FLAG_TF | FLAG_DF | FLAG_IOPL | FLAG_AC | FLAG_NT);
}

/* The main system call interface */
void syscall_handler(struct intr_frame *f UNUSED)
{
	// TODO: Your implementation goes here.
	/* 시스템 콜 번호는 %rax레지스터에 저장 */
	switch (f->R.rax)
	{
	case SYS_WRITE:
	{ // Write면
		/* write는 fd,buffer,size순으로 레지스터에 담겨옴 */
		f->R.rax = sys_write((int)f->R.rdi, (void *)f->R.rsi, (unsigned)f->R.rdx);
		break;
	}
	case SYS_EXIT:
		sys_exit(f->R.rdi);
		break;

	case SYS_HALT:
		power_off();
		break;

	case SYS_CREATE:
	{
		/* 파일 이름과 파일 초기 크기 인자 넘겨주기 */
		bool success = sys_create((const char *)f->R.rdi, (unsigned)f->R.rsi);
		f->R.rax = success; // 성공 결과 반환
		break;
	}
	case SYS_OPEN:
	{
		const char *file = (const char *)f->R.rdi;
		f->R.rax = sys_open(file);
		break;
	}
	case SYS_CLOSE:
	{
		sys_close((int)f->R.rdi);
		break;
	}
	case SYS_READ:
	{
		f->R.rax = sys_read((int)f->R.rdi, (void *)f->R.rsi, (unsigned)f->R.rdx);
		break;
	}
	case SYS_FILESIZE:
		f->R.rax = sys_filesize((int)f->R.rdi);
		break;
	}
}

static int sys_filesize(int fd)
{
	struct thread *curr = thread_current();
	if (fd >= 2 && fd < FD_MAX && curr->fd_table[fd] != NULL)
	{
		lock_acquire(&filesys_lock);
		off_t length = file_length(curr->fd_table[fd]);
		lock_release(&filesys_lock);
		return length;
	}
	else
	{
		return -1;
	}
}

static int sys_write(int fd, void *buffer, unsigned size)
{
	/* 버퍼 시작과 끝 검사하면 연속된 버퍼가 유효하다는 뜻 */
	check_address((void *)buffer);
	if (size > 0)
		check_address((void *)buffer + size - 1);
	// 1. STDOUT이면
	if (fd == 1)
	{
		putbuf((const char *)buffer, size); // 버퍼내용을 콘솔에 출력
		return size;						// 성공했으면 size 반환
	}
	// 2. 일반 파일에 쓰기 (fd >= 2)
	if (fd >= 2 && fd < FD_MAX)
	{
		struct thread *curr = thread_current();
		struct file *file_obj = curr->fd_table[fd]; // fd가 실제로 열려있는 유효한 파일인지?
		if (file_obj != NULL)						// 열려있으면
		{
			lock_acquire(&filesys_lock);
			/* 쓰기 작업 수행 */
			off_t bytes_written = file_write(file_obj, buffer, size); // 파일에 buffer 내용을 size바이트만 큼 쓰고, 쓰기에 성공한 바이트 수 만큼 반환
			lock_release(&filesys_lock);
			return bytes_written;
		}
	}
	// 3. 유효하지 않은 fd (STDIN 포함)
	return -1;
}

static int sys_read(int fd, void *buffer, unsigned size)
{
	/* 인자 검증 */
	check_address(buffer);
	if (size > 0)
		check_address((void *)buffer + size - 1);
	if (fd == 0)
	{ // STDIN
		// 키보드 입력은 Project 2 후반부에서 구현
		return -1; // 임시로 실패 처리
	}
	else if (fd >= 2 && fd < FD_MAX)
	{
		struct file *file_obj = thread_current()->fd_table[fd]; // fd가 실제로 열려있는 유효한 파일인지?
		if (file_obj != NULL)
		{
			lock_acquire(&filesys_lock);
			/* 읽기 작업 수행 */
			off_t bytes_read = file_read(file_obj, buffer, size); // 디스크에서 데이터를 읽어 사용자 버퍼에 저장, 성공적으로 읽은 바이트 수 반환
			lock_release(&filesys_lock);
			return bytes_read;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

static void sys_close(int fd)
{
	struct thread *curr = thread_current();
	if (fd >= 2 && fd < FD_MAX && curr->fd_table[fd] != NULL) // 사용자 정의 fd이고 사용자 영역 fd이면서 fd_table에 존재해야하면?
	{
		lock_acquire(&filesys_lock);
		file_close(curr->fd_table[fd]); // 파일 닫기
		lock_release(&filesys_lock);
		curr->fd_table[fd] = NULL; // FD_table에서 제거
	}
}

static bool sys_create(const char *file, unsigned initial_size)
{
	/* 주소 유효성 검증 */
	check_address((void *)file); // 파일 포인터가 NULL이거나 커널 메모리 영역을 가리키면 exit
	/* 파일 생성+동기화 */
	lock_acquire(&filesys_lock);					   // 락을 획득해서 여러프로세스 동시접근x, 다른 프로세스 끼어들지 못하게 제한
	bool success = filesys_create(file, initial_size); // 파일 생성 초기 사이즈와 파일이름으로 (성공여부 반환)
	lock_release(&filesys_lock);					   // 성공적으로 만들면 락 해제
	/* 결과 반환 */
	return success;
}

static int sys_open(const char *file)
{
	/* 주소 유효성 검증 */
	check_address((void *)file); // 파일 포인터가 NULL이거나 커널 메모리 영역을 가리키면 exit
	/* 파일 생성+동기화 */
	lock_acquire(&filesys_lock);				// 락을 획득해서 여러프로세스 동시접근x, 다른 프로세스 끼어들지 못하게 제한
	struct file *file_obj = filesys_open(file); // 파일 열기, 파일 이름 문자열을 디스크상 파일 데이터와 연결
	lock_release(&filesys_lock);				// 성공적으로 만들면 락 해제
	/* 예외 처리 */
	if (file_obj == NULL)
	{			   // NULL반환했으면 열기 실패
		return -1; //-1
	}
	else
	{
		struct thread *curr = thread_current(); // 현재 실행중인 스레드
		int fd = curr->next_fd;					// 다음에 할당될 fd
		// FD수를 넘지 않으면
		if (curr->next_fd < FD_MAX)
		{
			curr->fd_table[fd] = file_obj; // 다음 할당할 fd번호에 열린 파일 할당
			curr->next_fd++;			   // 다음 fd 가리키게
			return fd;					   // 파일 할당완료했으니까 rax에 fd넣기
		}
		// FD수 넘으면
		else
		{
			lock_acquire(&filesys_lock); // 프로세스 접근 권한 주고
			file_close(file_obj);		 // 파일 닫고
			lock_release(&filesys_lock); // 접근 권한 반납
			return -1;					 //-1반환
		}
	}
}

void sys_exit(int status)
{
	struct thread *curr = thread_current();
	curr->exit_status = status;					  // 부모 깨우기 전에 상태 저장
	printf("%s: exit(%d)\n", curr->name, status); // 0개 겠지뭐
	sema_up(&curr->wait_sema);					  // 자식이 종료될때 부모를 up 시켜 깨움, 부모를 가리키고 있음
	thread_exit();								  // 부모 프로세스도 종료
}

void check_address(void *addr)
{
	struct thread *curr = thread_current();
	/* 커널 영역 침범 여부(KERN_BASE 미만 + NULL인지) || 미할당 영역 접근 여부(가상주소 -> 페이지 테이블 매핑?) */
	if (!is_user_vaddr(addr) || addr == NULL || pml4_get_page(curr->pml4, addr) == NULL)
	{
		sys_exit(-1);
	}
}