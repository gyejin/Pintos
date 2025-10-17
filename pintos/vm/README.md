**PintOS Project - VM Branch**

---

## 📌 Project Overview
본 프로젝트는 **PintOS 운영체제**의 가상 메모리(Virtual Memory)** 부분을 구현하고 테스트한 결과를 정리한 것입니다.  
구현한 기능은 다음과 같습니다:

- **Virtual Memory**
  - Lazy Loading
  - Memory Mapping (mmap, munmap)
  - Page Fault Handling
  - Stack Growth
  - File-backed & Anonymous Page 관리
  - Copy-On-Write (COW)
  - Swap System

---

## ✅ Test Results

| Test | Result |
|------|--------|
| exec-bad-ptr | ✅ PASS |
| sm-full | ✅ PASS |
| rox-simple | ✅ PASS |
| page-linear | ✅ PASS |
| mmap-zero | ✅ PASS |
| mmap-exit | ❌ FAIL |
| fork-multiple | ✅ PASS |
| pt-write-code | ✅ PASS |
| mmap-bad-fd | ✅ PASS |
| mmap-null | ✅ PASS |
| args-dbl-space | ✅ PASS |
| read-bad-fd | ✅ PASS |
| priority-donate-multiple | ✅ PASS |
| args-multiple | ✅ PASS |
| lg-seq-random | ✅ PASS |
| syn-write | ✅ PASS |
| syn-remove | ✅ PASS |
| priority-donate-one | ✅ PASS |
| mmap-overlap | ✅ PASS |
| create-normal | ✅ PASS |
| priority-donate-lower | ✅ PASS |
| mmap-misalign | ✅ PASS |
| bad-write | ✅ PASS |
| open-twice | ✅ PASS |
| page-shuffle | ✅ PASS |
| exec-missing | ✅ PASS |
| exec-arg | ✅ PASS |
| page-merge-mm | ❌ FAIL |
| read-bad-ptr | ✅ PASS |
| create-long | ✅ PASS |
| mmap-remove | ❌ FAIL |
| mmap-read | ✅ PASS |
| priority-preempt | ✅ PASS |
| fork-close | ✅ PASS |
| alarm-simultaneous | ✅ PASS |
| fork-boundary | ✅ PASS |
| priority-donate-chain | ✅ PASS |
| create-bound | ✅ PASS |
| rox-multichild | ✅ PASS |
| lg-random | ✅ PASS |
| page-merge-seq | ✅ PASS |
| pt-bad-read | ✅ PASS |
| priority-condvar | ✅ PASS |
| priority-donate-nest | ✅ PASS |
| page-merge-par | ✅ PASS |
| rox-child | ✅ PASS |
| mmap-write | ✅ PASS |
| alarm-single | ✅ PASS |
| lazy-file | ✅ PASS |
| pt-bad-addr | ✅ PASS |
| read-normal | ✅ PASS |
| lazy-anon | ✅ PASS |
| pt-write-code2 | ✅ PASS |
| mmap-over-stk | ✅ PASS |
| priority-donate-multiple2 | ✅ PASS |
| open-empty | ✅ PASS |
| mmap-zero-len | ✅ PASS |
| open-null | ✅ PASS |
| page-parallel | ❌ FAIL |
| sm-seq-random | ✅ PASS |
| page-merge-stk | ✅ PASS |
| bad-write2 | ✅ PASS |
| sm-seq-block | ✅ PASS |
| multi-recurse | ✅ PASS |
| alarm-priority | ✅ PASS |
| close-twice | ✅ PASS |
| mmap-over-data | ✅ PASS |
| args-none | ✅ PASS |
| mmap-kernel | ✅ PASS |
| create-bad-ptr | ✅ PASS |
| read-stdout | ✅ PASS |
| priority-fifo | ✅ PASS |
| wait-bad-pid | ✅ PASS |
| lg-create | ✅ PASS |
| pt-grow-bad | ✅ PASS |
| mmap-twice | ✅ PASS |
| pt-grow-stk-sc | ✅ PASS |
| exec-read | ✅ PASS |
| priority-sema | ✅ PASS |
| read-boundary | ✅ PASS |
| wait-twice | ✅ PASS |
| exec-boundary | ✅ PASS |
| close-normal | ✅ PASS |
| mmap-ro | ✅ PASS |
| sm-create | ✅ PASS |
| halt | ✅ PASS |
| write-bad-fd | ✅ PASS |
| sm-random | ✅ PASS |
| alarm-zero | ✅ PASS |
| open-boundary | ✅ PASS |
| create-null | ✅ PASS |
| pt-grow-stack | ✅ PASS |
| fork-recursive | ✅ PASS |
| open-bad-ptr | ✅ PASS |
| mmap-inherit | ✅ PASS |
| mmap-unmap | ❌ FAIL |
| write-normal | ✅ PASS |
| mmap-off | ✅ PASS |
| mmap-over-code | ✅ PASS |
| mmap-close | ✅ PASS |
| bad-read | ✅ PASS |
| fork-once | ✅ PASS |
| mmap-bad-fd3 | ✅ PASS |
| mmap-bad-fd2 | ✅ PASS |
| priority-change | ✅ PASS |
| write-boundary | ✅ PASS |
| wait-killed | ✅ PASS |
| lg-full | ✅ PASS |
| close-bad-fd | ✅ PASS |
| alarm-negative | ✅ PASS |
| multi-child-fd | ✅ PASS |
| exit | ✅ PASS |
| write-bad-ptr | ✅ PASS |
| priority-donate-sema | ✅ PASS |
| lg-seq-block | ✅ PASS |
| mmap-shuffle | ✅ PASS |
| wait-simple | ✅ PASS |
| exec-once | ✅ PASS |
| args-many | ✅ PASS |
| mmap-clean | ✅ PASS |
| fork-read | ✅ PASS |
| write-zero | ✅ PASS |
| alarm-multiple | ✅ PASS |
| create-exists | ✅ PASS |
| mmap-bad-off | ✅ PASS |
| open-normal | ✅ PASS |
| bad-jump | ✅ PASS |
| pt-big-stk-obj | ✅ PASS |
| bad-jump2 | ✅ PASS |
| open-missing | ✅ PASS |
| create-empty | ✅ PASS |
| args-single | ✅ PASS |
| write-stdin | ✅ PASS |
| read-zero | ✅ PASS |
| bad-read2 | ✅ PASS |
| syn-read | ✅ PASS |
| swap-file | 🚧 NONE |
| swap-anon | 🚧 NONE |
| swap-iter | 🚧 NONE |
| swap-fork | 🚧 NONE |
| cow-simple | 🚧 NONE |

---

## 📂 Summary
- **총 테스트 수**: 138  
- **성공(PASS)**: 129 🎉  
- **실패(FAIL)**: 4 ❌  
- **미구현(NONE)**: 5 🚧  
- 실패한 테스트: `mmap-exit`, `page-merge-mm`, `mmap-remove`, `page-parallel`, `mmap-unmap`  
- 미구현 테스트: `swap-file`, `swap-anon`, `swap-iter`, `swap-fork`, `cow-simple`

---

## 📝 Notes
- 대부분의 **VM 및 mmap 관련 기능**이 정상 동작함  
- 일부 **mmap 및 page 병합 관련 테스트**에서 FAIL 발생  
- **Swap 및 COW(Copy-On-Write)** 기능은 아직 구현되지 않음 🚧  
- 향후 **Page Merge, Unmap, Swap 시스템, COW 로직** 보완 필요