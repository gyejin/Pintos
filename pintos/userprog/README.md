**PintOS Project - Userprog Branch**

---

## 📌 Project Overview
본 프로젝트는 **PintOS 운영체제**의 User Program 부분을 구현하고 테스트한 결과를 정리한 것입니다.  
구현한 기능은 다음과 같습니다:

- **User Program**
  - Argument Passing
  - System Calls (halt, exit, create, open, read, write, close, exec, wait, fork 등)
  - File Descriptor 관리
  - 메모리 접근 검증
  - 동시성 및 대용량 파일 처리

---

## ✅ Test Results

### 🗂 Argument Passing
| Test | Result |
|------|--------|
| args-none       | ✅ PASS |
| args-single     | ✅ PASS |
| args-multiple   | ✅ PASS |
| args-many       | ✅ PASS |
| args-dbl-space  | ✅ PASS |

### 🔧 System Calls
| Test | Result |
|------|--------|
| halt           | ✅ PASS |
| exit           | ✅ PASS |
| create-normal  | ✅ PASS |
| create-empty   | ✅ PASS |
| create-null    | ✅ PASS |
| create-bad-ptr | ✅ PASS |
| create-long    | ✅ PASS |
| create-exists  | ✅ PASS |
| create-bound   | ✅ PASS |
| open-normal    | ✅ PASS |
| open-missing   | ✅ PASS |
| open-boundary  | ✅ PASS |
| open-empty     | ✅ PASS |
| open-null      | ✅ PASS |
| open-bad-ptr   | ✅ PASS |
| open-twice     | ✅ PASS |
| close-normal   | ✅ PASS |
| close-twice    | ✅ PASS |
| close-bad-fd   | ✅ PASS |
| read-normal    | ✅ PASS |
| read-bad-ptr   | ✅ PASS |
| read-boundary  | ✅ PASS |
| read-zero      | ✅ PASS |
| read-stdout    | ✅ PASS |
| read-bad-fd    | ✅ PASS |
| write-normal   | ✅ PASS |
| write-bad-ptr  | ✅ PASS |
| write-boundary | ✅ PASS |
| write-zero     | ✅ PASS |
| write-stdin    | ✅ PASS |
| write-bad-fd   | ✅ PASS |

### 🧬 Process Control
| Test | Result |
|------|--------|
| fork-once       | ✅ PASS |
| fork-multiple   | ✅ PASS |
| fork-recursive  | ✅ PASS |
| fork-read       | ✅ PASS |
| fork-close      | ✅ PASS |
| fork-boundary   | ✅ PASS |
| exec-once       | ✅ PASS |
| exec-arg        | ✅ PASS |
| exec-boundary   | ✅ PASS |
| exec-missing    | ✅ PASS |
| exec-bad-ptr    | ✅ PASS |
| exec-read       | ✅ PASS |
| wait-simple     | ✅ PASS |
| wait-twice      | ✅ PASS |
| wait-killed     | ✅ PASS |
| wait-bad-pid    | ✅ PASS |

### 🔁 Multi-Process & Concurrency
| Test | Result |
|------|--------|
| multi-recurse   | ✅ PASS |
| multi-child-fd  | ✅ PASS |
| multi-oom       | ✅ PASS |
| syn-read        | ✅ PASS |
| syn-remove      | ✅ PASS |
| syn-write       | ✅ PASS |

### 🔒 Robustness & Protection
| Test | Result |
|------|--------|
| rox-simple      | ✅ PASS |
| rox-child       | ❌ FAIL |
| rox-multichild  | ❌ FAIL |
| bad-read        | ✅ PASS |
| bad-write       | ✅ PASS |
| bad-read2       | ✅ PASS |
| bad-write2      | ✅ PASS |
| bad-jump        | ✅ PASS |
| bad-jump2       | ✅ PASS |

### 📂 File System Stress Tests
| Test | Result |
|------|--------|
| lg-create      | ✅ PASS |
| lg-full        | ✅ PASS |
| lg-random      | ✅ PASS |
| lg-seq-block   | ✅ PASS |
| lg-seq-random  | ✅ PASS |
| sm-create      | ✅ PASS |
| sm-full        | ✅ PASS |
| sm-random      | ✅ PASS |
| sm-seq-block   | ✅ PASS |
| sm-seq-random  | ✅ PASS |

---

## 📂 Summary
- **총 테스트 수**: 77  
- **성공(PASS)**: 75 🎉  
- **실패(FAIL)**: 2 ❌  
- 실패한 테스트: `rox-child`, `rox-multichild`  

---

## 📝 Notes
- 대부분의 **System Call** 및 **Argument Passing** 기능은 정상 동작함  
- `rox-child`, `rox-multichild` 테스트 실패 → 실행 파일의 **Read-Only eXecutable(ROX)** 보호와 관련된 문제 가능성 높음  
- 향후 **메모리 보호 기능 보완** 필요