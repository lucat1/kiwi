# 1 "config.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "config.h"

# 1 "data.h" 1

# 1 "list.h" 1

typedef struct list list_t;

struct list {
  void *value;
  struct list *next;
};

void list_append(list_t **l, void *ele);
void list_remove(list_t **l, void *ele);
void list_free(list_t *l, void (*free)(void *));
int list_size(list_t *l);
# 5 "data.h" 2
# 1 "stack.h" 1

typedef struct stack stack_t;

struct stack {
  void *value;
  struct stack *prev;
};

void stack_push(stack_t **s, void *ele);
void *stack_pop(stack_t **s);
void stack_remove(stack_t **s, void *ele);
void stack_free(stack_t *s);
# 6 "data.h" 2
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stdbool.h" 1 3 4
# 7 "data.h" 2
# 1 "/usr/include/xcb/xcb.h" 1 3 4
# 30 "/usr/include/xcb/xcb.h" 3 4
# 1 "/usr/include/sys/types.h" 1 3 4
# 25 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 450 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 460 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 461 "/usr/include/sys/cdefs.h" 2 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 462 "/usr/include/sys/cdefs.h" 2 3 4
# 451 "/usr/include/features.h" 2 3 4
# 474 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 475 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/sys/types.h" 2 3 4

# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4

# 31 "/usr/include/bits/types.h" 3 4
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;

typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;

typedef long int __quad_t;
typedef unsigned long int __u_quad_t;

typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 142 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/time64.h" 1 3 4
# 143 "/usr/include/bits/types.h" 2 3 4

typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct {
  int __val[2];
} __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;

typedef int __clockid_t;

typedef void *__timer_t;

typedef long int __blksize_t;

typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;

typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;

typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __fsword_t;

typedef long int __ssize_t;

typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;

typedef __off64_t __loff_t;
typedef char *__caddr_t;

typedef long int __intptr_t;

typedef unsigned int __socklen_t;

typedef int __sig_atomic_t;
# 30 "/usr/include/sys/types.h" 2 3 4

typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;

typedef __loff_t loff_t;

typedef __ino_t ino_t;
# 59 "/usr/include/sys/types.h" 3 4
typedef __dev_t dev_t;

typedef __gid_t gid_t;

typedef __mode_t mode_t;

typedef __nlink_t nlink_t;

typedef __uid_t uid_t;

typedef __off_t off_t;
# 97 "/usr/include/sys/types.h" 3 4
typedef __pid_t pid_t;

typedef __id_t id_t;

typedef __ssize_t ssize_t;

typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;

typedef __key_t key_t;

# 1 "/usr/include/bits/types/clock_t.h" 1 3 4

typedef __clock_t clock_t;
# 127 "/usr/include/sys/types.h" 2 3 4

# 1 "/usr/include/bits/types/clockid_t.h" 1 3 4

typedef __clockid_t clockid_t;
# 129 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/time_t.h" 1 3 4

typedef __time_t time_t;
# 130 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/timer_t.h" 1 3 4

typedef __timer_t timer_t;
# 131 "/usr/include/sys/types.h" 2 3 4
# 144 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stddef.h" 1 3 4
# 209 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 145 "/usr/include/sys/types.h" 2 3 4

typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;

# 1 "/usr/include/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 156 "/usr/include/sys/types.h" 2 3 4

typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;

typedef int register_t __attribute__((__mode__(__word__)));
# 176 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 36 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 2 3 4
# 60 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 33 "/usr/include/bits/byteswap.h" 3 4
static __inline __uint16_t __bswap_16(__uint16_t __bsx) {

  return __builtin_bswap16(__bsx);
}

static __inline __uint32_t __bswap_32(__uint32_t __bsx) {

  return __builtin_bswap32(__bsx);
}
# 69 "/usr/include/bits/byteswap.h" 3 4
__extension__ static __inline __uint64_t __bswap_64(__uint64_t __bsx) {

  return __builtin_bswap64(__bsx);
}
# 61 "/usr/include/endian.h" 2 3 4
# 1 "/usr/include/bits/uintn-identity.h" 1 3 4
# 32 "/usr/include/bits/uintn-identity.h" 3 4
static __inline __uint16_t __uint16_identity(__uint16_t __x) { return __x; }

static __inline __uint32_t __uint32_identity(__uint32_t __x) { return __x; }

static __inline __uint64_t __uint64_identity(__uint64_t __x) { return __x; }
# 62 "/usr/include/endian.h" 2 3 4
# 177 "/usr/include/sys/types.h" 2 3 4

# 1 "/usr/include/sys/select.h" 1 3 4
# 30 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 22 "/usr/include/bits/select.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 23 "/usr/include/bits/select.h" 2 3 4
# 31 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/types/sigset_t.h" 1 3 4

# 1 "/usr/include/bits/types/__sigset_t.h" 1 3 4

typedef struct {
  unsigned long int __val[(1024 / (8 * sizeof(unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/bits/types/sigset_t.h" 2 3 4

typedef __sigset_t sigset_t;
# 34 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/types/struct_timeval.h" 1 3 4

struct timeval {
  __time_t tv_sec;
  __suseconds_t tv_usec;
};
# 38 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/types/struct_timespec.h" 1 3 4
# 9 "/usr/include/bits/types/struct_timespec.h" 3 4
struct timespec {
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
# 40 "/usr/include/sys/select.h" 2 3 4

typedef __suseconds_t suseconds_t;

typedef long int __fd_mask;
# 59 "/usr/include/sys/select.h" 3 4
typedef struct {

  __fd_mask __fds_bits[1024 / (8 * (int)sizeof(__fd_mask))];

} fd_set;

typedef __fd_mask fd_mask;
# 91 "/usr/include/sys/select.h" 3 4

# 101 "/usr/include/sys/select.h" 3 4
extern int select(int __nfds, fd_set *__restrict __readfds,
                  fd_set *__restrict __writefds, fd_set *__restrict __exceptfds,
                  struct timeval *__restrict __timeout);
# 113 "/usr/include/sys/select.h" 3 4
extern int pselect(int __nfds, fd_set *__restrict __readfds,
                   fd_set *__restrict __writefds,
                   fd_set *__restrict __exceptfds,
                   const struct timespec *__restrict __timeout,
                   const __sigset_t *__restrict __sigmask);
# 126 "/usr/include/sys/select.h" 3 4

# 180 "/usr/include/sys/types.h" 2 3 4

typedef __blksize_t blksize_t;

typedef __blkcnt_t blkcnt_t;

typedef __fsblkcnt_t fsblkcnt_t;

typedef __fsfilcnt_t fsfilcnt_t;
# 227 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/thread-shared-types.h" 1 3 4
# 77 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes-arch.h" 1 3 4
# 21 "/usr/include/bits/pthreadtypes-arch.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 22 "/usr/include/bits/pthreadtypes-arch.h" 2 3 4
# 65 "/usr/include/bits/pthreadtypes-arch.h" 3 4
struct __pthread_rwlock_arch_t {
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;

  unsigned char __pad1[7];

  unsigned long int __pad2;

  unsigned int __flags;
# 99 "/usr/include/bits/pthreadtypes-arch.h" 3 4
};
# 78 "/usr/include/bits/thread-shared-types.h" 2 3 4

typedef struct __pthread_internal_list {
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
# 118 "/usr/include/bits/thread-shared-types.h" 3 4
struct __pthread_mutex_s {
  int __lock;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;
# 148 "/usr/include/bits/thread-shared-types.h" 3 4
  int __kind;

  short __spins;
  short __elision;
  __pthread_list_t __list;
# 165 "/usr/include/bits/thread-shared-types.h" 3 4
};

struct __pthread_cond_s {
  __extension__ union {
    __extension__ unsigned long long int __wseq;
    struct {
      unsigned int __low;
      unsigned int __high;
    } __wseq32;
  };
  __extension__ union {
    __extension__ unsigned long long int __g1_start;
    struct {
      unsigned int __low;
      unsigned int __high;
    } __g1_start32;
  };
  unsigned int __g_refs[2];
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4

typedef unsigned long int pthread_t;

typedef union {
  char __size[4];
  int __align;
} pthread_mutexattr_t;

typedef union {
  char __size[4];
  int __align;
} pthread_condattr_t;

typedef unsigned int pthread_key_t;

typedef int pthread_once_t;

union pthread_attr_t {
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;

typedef union {
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union {
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union {
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union {
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;

typedef volatile int pthread_spinlock_t;

typedef union {
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union {
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 228 "/usr/include/sys/types.h" 2 3 4

# 31 "/usr/include/xcb/xcb.h" 2 3 4

# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4

# 1 "/usr/include/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4

# 1 "/usr/include/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4

typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;

typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;

typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 71 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 87 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;

typedef unsigned long int uintptr_t;
# 101 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stdint.h" 2 3 4
# 36 "/usr/include/xcb/xcb.h" 2 3 4

# 1 "/usr/include/sys/uio.h" 1 3 4
# 23 "/usr/include/sys/uio.h" 3 4
# 1 "/usr/include/bits/types/struct_iovec.h" 1 3 4
# 23 "/usr/include/bits/types/struct_iovec.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stddef.h" 1 3 4
# 24 "/usr/include/bits/types/struct_iovec.h" 2 3 4

struct iovec {
  void *iov_base;
  size_t iov_len;
};
# 24 "/usr/include/sys/uio.h" 2 3 4
# 1 "/usr/include/bits/uio_lim.h" 1 3 4
# 25 "/usr/include/sys/uio.h" 2 3 4

# 41 "/usr/include/sys/uio.h" 3 4
extern ssize_t readv(int __fd, const struct iovec *__iovec, int __count);
# 52 "/usr/include/sys/uio.h" 3 4
extern ssize_t writev(int __fd, const struct iovec *__iovec, int __count);
# 67 "/usr/include/sys/uio.h" 3 4
extern ssize_t preadv(int __fd, const struct iovec *__iovec, int __count,
                      __off_t __offset);
# 79 "/usr/include/sys/uio.h" 3 4
extern ssize_t pwritev(int __fd, const struct iovec *__iovec, int __count,
                       __off_t __offset);
# 163 "/usr/include/sys/uio.h" 3 4

# 40 "/usr/include/xcb/xcb.h" 2 3 4

# 1 "/usr/include/pthread.h" 1 3 4
# 23 "/usr/include/pthread.h" 3 4
# 1 "/usr/include/sched.h" 1 3 4
# 29 "/usr/include/sched.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stddef.h" 1 3 4
# 30 "/usr/include/sched.h" 2 3 4
# 43 "/usr/include/sched.h" 3 4
# 1 "/usr/include/bits/sched.h" 1 3 4
# 74 "/usr/include/bits/sched.h" 3 4
# 1 "/usr/include/bits/types/struct_sched_param.h" 1 3 4
# 23 "/usr/include/bits/types/struct_sched_param.h" 3 4
struct sched_param {
  int sched_priority;
};
# 75 "/usr/include/bits/sched.h" 2 3 4

# 96 "/usr/include/bits/sched.h" 3 4

# 44 "/usr/include/sched.h" 2 3 4
# 1 "/usr/include/bits/cpu-set.h" 1 3 4
# 32 "/usr/include/bits/cpu-set.h" 3 4
typedef unsigned long int __cpu_mask;

typedef struct {
  __cpu_mask __bits[1024 / (8 * sizeof(__cpu_mask))];
} cpu_set_t;
# 115 "/usr/include/bits/cpu-set.h" 3 4

extern int __sched_cpucount(size_t __setsize, const cpu_set_t *__setp)
    __attribute__((__nothrow__, __leaf__));
extern cpu_set_t *__sched_cpualloc(size_t __count)
    __attribute__((__nothrow__, __leaf__));
extern void __sched_cpufree(cpu_set_t *__set)
    __attribute__((__nothrow__, __leaf__));

# 45 "/usr/include/sched.h" 2 3 4

extern int sched_setparam(__pid_t __pid, const struct sched_param *__param)
    __attribute__((__nothrow__, __leaf__));

extern int sched_getparam(__pid_t __pid, struct sched_param *__param)
    __attribute__((__nothrow__, __leaf__));

extern int sched_setscheduler(__pid_t __pid, int __policy,
                              const struct sched_param *__param)
    __attribute__((__nothrow__, __leaf__));

extern int sched_getscheduler(__pid_t __pid)
    __attribute__((__nothrow__, __leaf__));

extern int sched_yield(void) __attribute__((__nothrow__, __leaf__));

extern int sched_get_priority_max(int __algorithm)
    __attribute__((__nothrow__, __leaf__));

extern int sched_get_priority_min(int __algorithm)
    __attribute__((__nothrow__, __leaf__));

extern int sched_rr_get_interval(__pid_t __pid, struct timespec *__t)
    __attribute__((__nothrow__, __leaf__));
# 129 "/usr/include/sched.h" 3 4

# 24 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/time.h" 1 3 4
# 29 "/usr/include/time.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/9.3/include/stddef.h" 1 3 4
# 30 "/usr/include/time.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 34 "/usr/include/time.h" 2 3 4

# 1 "/usr/include/bits/types/struct_tm.h" 1 3 4

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;

  long int tm_gmtoff;
  const char *tm_zone;
};
# 40 "/usr/include/time.h" 2 3 4
# 48 "/usr/include/time.h" 3 4
# 1 "/usr/include/bits/types/struct_itimerspec.h" 1 3 4

struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};
# 49 "/usr/include/time.h" 2 3 4
struct sigevent;
# 60 "/usr/include/time.h" 3 4
# 1 "/usr/include/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/bits/types/locale_t.h" 3 4
# 1 "/usr/include/bits/types/__locale_t.h" 1 3 4
# 28 "/usr/include/bits/types/__locale_t.h" 3 4
struct __locale_struct {

  struct __locale_data *__locales[13];

  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;

  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 61 "/usr/include/time.h" 2 3 4

extern clock_t clock(void) __attribute__((__nothrow__, __leaf__));

extern time_t time(time_t *__timer) __attribute__((__nothrow__, __leaf__));

extern double difftime(time_t __time1, time_t __time0)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__const__));

extern time_t mktime(struct tm *__tp) __attribute__((__nothrow__, __leaf__));

extern size_t strftime(char *__restrict __s, size_t __maxsize,
                       const char *__restrict __format,
                       const struct tm *__restrict __tp)
    __attribute__((__nothrow__, __leaf__));
# 104 "/usr/include/time.h" 3 4
extern size_t strftime_l(char *__restrict __s, size_t __maxsize,
                         const char *__restrict __format,
                         const struct tm *__restrict __tp, locale_t __loc)
    __attribute__((__nothrow__, __leaf__));
# 119 "/usr/include/time.h" 3 4
extern struct tm *gmtime(const time_t *__timer)
    __attribute__((__nothrow__, __leaf__));

extern struct tm *localtime(const time_t *__timer)
    __attribute__((__nothrow__, __leaf__));

extern struct tm *gmtime_r(const time_t *__restrict __timer,
                           struct tm *__restrict __tp)
    __attribute__((__nothrow__, __leaf__));

extern struct tm *localtime_r(const time_t *__restrict __timer,
                              struct tm *__restrict __tp)
    __attribute__((__nothrow__, __leaf__));

extern char *asctime(const struct tm *__tp)
    __attribute__((__nothrow__, __leaf__));

extern char *ctime(const time_t *__timer)
    __attribute__((__nothrow__, __leaf__));

extern char *asctime_r(const struct tm *__restrict __tp, char *__restrict __buf)
    __attribute__((__nothrow__, __leaf__));

extern char *ctime_r(const time_t *__restrict __timer, char *__restrict __buf)
    __attribute__((__nothrow__, __leaf__));

extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;

extern char *tzname[2];

extern void tzset(void) __attribute__((__nothrow__, __leaf__));

extern int daylight;
extern long int timezone;

extern int stime(const time_t *__when) __attribute__((__nothrow__, __leaf__));
# 196 "/usr/include/time.h" 3 4
extern time_t timegm(struct tm *__tp) __attribute__((__nothrow__, __leaf__));

extern time_t timelocal(struct tm *__tp) __attribute__((__nothrow__, __leaf__));

extern int dysize(int __year) __attribute__((__nothrow__, __leaf__))
__attribute__((__const__));
# 211 "/usr/include/time.h" 3 4
extern int nanosleep(const struct timespec *__requested_time,
                     struct timespec *__remaining);

extern int clock_getres(clockid_t __clock_id, struct timespec *__res)
    __attribute__((__nothrow__, __leaf__));

extern int clock_gettime(clockid_t __clock_id, struct timespec *__tp)
    __attribute__((__nothrow__, __leaf__));

extern int clock_settime(clockid_t __clock_id, const struct timespec *__tp)
    __attribute__((__nothrow__, __leaf__));

extern int clock_nanosleep(clockid_t __clock_id, int __flags,
                           const struct timespec *__req,
                           struct timespec *__rem);

extern int clock_getcpuclockid(pid_t __pid, clockid_t *__clock_id)
    __attribute__((__nothrow__, __leaf__));

extern int timer_create(clockid_t __clock_id, struct sigevent *__restrict __evp,
                        timer_t *__restrict __timerid)
    __attribute__((__nothrow__, __leaf__));

extern int timer_delete(timer_t __timerid)
    __attribute__((__nothrow__, __leaf__));

extern int timer_settime(timer_t __timerid, int __flags,
                         const struct itimerspec *__restrict __value,
                         struct itimerspec *__restrict __ovalue)
    __attribute__((__nothrow__, __leaf__));

extern int timer_gettime(timer_t __timerid, struct itimerspec *__value)
    __attribute__((__nothrow__, __leaf__));

extern int timer_getoverrun(timer_t __timerid)
    __attribute__((__nothrow__, __leaf__));

extern int timespec_get(struct timespec *__ts, int __base)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));
# 307 "/usr/include/time.h" 3 4

# 25 "/usr/include/pthread.h" 2 3 4

# 1 "/usr/include/bits/setjmp.h" 1 3 4
# 26 "/usr/include/bits/setjmp.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 27 "/usr/include/bits/setjmp.h" 2 3 4

typedef long int __jmp_buf[8];
# 28 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/pthread.h" 2 3 4

enum {
  PTHREAD_CREATE_JOINABLE,

  PTHREAD_CREATE_DETACHED

};

enum {
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP

  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL

};

enum {
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};

enum { PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, PTHREAD_PRIO_PROTECT };
# 115 "/usr/include/pthread.h" 3 4
enum {
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
# 156 "/usr/include/pthread.h" 3 4
enum {
  PTHREAD_INHERIT_SCHED,

  PTHREAD_EXPLICIT_SCHED

};

enum {
  PTHREAD_SCOPE_SYSTEM,

  PTHREAD_SCOPE_PROCESS

};

enum {
  PTHREAD_PROCESS_PRIVATE,

  PTHREAD_PROCESS_SHARED

};
# 191 "/usr/include/pthread.h" 3 4
struct _pthread_cleanup_buffer {
  void (*__routine)(void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};

enum {
  PTHREAD_CANCEL_ENABLE,

  PTHREAD_CANCEL_DISABLE

};
enum {
  PTHREAD_CANCEL_DEFERRED,

  PTHREAD_CANCEL_ASYNCHRONOUS

};
# 229 "/usr/include/pthread.h" 3 4

extern int pthread_create(pthread_t *__restrict __newthread,
                          const pthread_attr_t *__restrict __attr,
                          void *(*__start_routine)(void *),
                          void *__restrict __arg) __attribute__((__nothrow__))
__attribute__((__nonnull__(1, 3)));

extern void pthread_exit(void *__retval) __attribute__((__noreturn__));

extern int pthread_join(pthread_t __th, void **__thread_return);
# 272 "/usr/include/pthread.h" 3 4
extern int pthread_detach(pthread_t __th)
    __attribute__((__nothrow__, __leaf__));

extern pthread_t pthread_self(void) __attribute__((__nothrow__, __leaf__))
__attribute__((__const__));

extern int pthread_equal(pthread_t __thread1, pthread_t __thread2)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__const__));

extern int pthread_attr_init(pthread_attr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_destroy(pthread_attr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_getdetachstate(const pthread_attr_t *__attr,
                                       int *__detachstate)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_attr_setdetachstate(pthread_attr_t *__attr,
                                       int __detachstate)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_getguardsize(const pthread_attr_t *__attr,
                                     size_t *__guardsize)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_attr_setguardsize(pthread_attr_t *__attr, size_t __guardsize)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_getschedparam(const pthread_attr_t *__restrict __attr,
                                      struct sched_param *__restrict __param)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int
pthread_attr_setschedparam(pthread_attr_t *__restrict __attr,
                           const struct sched_param *__restrict __param)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_attr_getschedpolicy(const pthread_attr_t *__restrict __attr,
                                       int *__restrict __policy)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_attr_setschedpolicy(pthread_attr_t *__attr, int __policy)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_getinheritsched(const pthread_attr_t *__restrict __attr,
                                        int *__restrict __inherit)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_attr_setinheritsched(pthread_attr_t *__attr, int __inherit)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_getscope(const pthread_attr_t *__restrict __attr,
                                 int *__restrict __scope)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_attr_setscope(pthread_attr_t *__attr, int __scope)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_getstackaddr(const pthread_attr_t *__restrict __attr,
                                     void **__restrict __stackaddr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)))
    __attribute__((__deprecated__));

extern int pthread_attr_setstackaddr(pthread_attr_t *__attr, void *__stackaddr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)))
    __attribute__((__deprecated__));

extern int pthread_attr_getstacksize(const pthread_attr_t *__restrict __attr,
                                     size_t *__restrict __stacksize)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_attr_setstacksize(pthread_attr_t *__attr, size_t __stacksize)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_attr_getstack(const pthread_attr_t *__restrict __attr,
                                 void **__restrict __stackaddr,
                                 size_t *__restrict __stacksize)
    __attribute__((__nothrow__, __leaf__))
    __attribute__((__nonnull__(1, 2, 3)));

extern int pthread_attr_setstack(pthread_attr_t *__attr, void *__stackaddr,
                                 size_t __stacksize)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));
# 430 "/usr/include/pthread.h" 3 4
extern int pthread_setschedparam(pthread_t __target_thread, int __policy,
                                 const struct sched_param *__param)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(3)));

extern int pthread_getschedparam(pthread_t __target_thread,
                                 int *__restrict __policy,
                                 struct sched_param *__restrict __param)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(2, 3)));

extern int pthread_setschedprio(pthread_t __target_thread, int __prio)
    __attribute__((__nothrow__, __leaf__));
# 495 "/usr/include/pthread.h" 3 4
extern int pthread_once(pthread_once_t *__once_control,
                        void (*__init_routine)(void))
    __attribute__((__nonnull__(1, 2)));
# 507 "/usr/include/pthread.h" 3 4
extern int pthread_setcancelstate(int __state, int *__oldstate);

extern int pthread_setcanceltype(int __type, int *__oldtype);

extern int pthread_cancel(pthread_t __th);

extern void pthread_testcancel(void);

typedef struct {
  struct {
    __jmp_buf __cancel_jmp_buf;
    int __mask_was_saved;
  } __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__((__aligned__));
# 541 "/usr/include/pthread.h" 3 4
struct __pthread_cleanup_frame {
  void (*__cancel_routine)(void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};
# 681 "/usr/include/pthread.h" 3 4
extern void __pthread_register_cancel(__pthread_unwind_buf_t *__buf);
# 693 "/usr/include/pthread.h" 3 4
extern void __pthread_unregister_cancel(__pthread_unwind_buf_t *__buf);
# 734 "/usr/include/pthread.h" 3 4
extern void __pthread_unwind_next(__pthread_unwind_buf_t *__buf)
    __attribute__((__noreturn__))

    __attribute__((__weak__))

    ;

struct __jmp_buf_tag;
extern int __sigsetjmp(struct __jmp_buf_tag *__env, int __savemask)
    __attribute__((__nothrow__));

extern int pthread_mutex_init(pthread_mutex_t *__mutex,
                              const pthread_mutexattr_t *__mutexattr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_mutex_destroy(pthread_mutex_t *__mutex)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_mutex_trylock(pthread_mutex_t *__mutex)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_mutex_lock(pthread_mutex_t *__mutex)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_mutex_timedlock(pthread_mutex_t *__restrict __mutex,
                                   const struct timespec *__restrict __abstime)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
# 781 "/usr/include/pthread.h" 3 4
extern int pthread_mutex_unlock(pthread_mutex_t *__mutex)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int
pthread_mutex_getprioceiling(const pthread_mutex_t *__restrict __mutex,
                             int *__restrict __prioceiling)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_mutex_setprioceiling(pthread_mutex_t *__restrict __mutex,
                                        int __prioceiling,
                                        int *__restrict __old_ceiling)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 3)));

extern int pthread_mutex_consistent(pthread_mutex_t *__mutex)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));
# 814 "/usr/include/pthread.h" 3 4
extern int pthread_mutexattr_init(pthread_mutexattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_mutexattr_destroy(pthread_mutexattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_mutexattr_getpshared(const pthread_mutexattr_t *__restrict __attr,
                             int *__restrict __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_mutexattr_setpshared(pthread_mutexattr_t *__attr,
                                        int __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_mutexattr_gettype(const pthread_mutexattr_t *__restrict __attr,
                          int *__restrict __kind)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_mutexattr_settype(pthread_mutexattr_t *__attr, int __kind)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_mutexattr_getprotocol(const pthread_mutexattr_t *__restrict __attr,
                              int *__restrict __protocol)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_mutexattr_setprotocol(pthread_mutexattr_t *__attr,
                                         int __protocol)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *__restrict __attr,
                                 int *__restrict __prioceiling)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *__attr,
                                            int __prioceiling)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_mutexattr_getrobust(const pthread_mutexattr_t *__attr,
                                       int *__robustness)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_mutexattr_setrobust(pthread_mutexattr_t *__attr,
                                       int __robustness)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));
# 896 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_init(pthread_rwlock_t *__restrict __rwlock,
                               const pthread_rwlockattr_t *__restrict __attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_rwlock_destroy(pthread_rwlock_t *__rwlock)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_rwlock_rdlock(pthread_rwlock_t *__rwlock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_rwlock_tryrdlock(pthread_rwlock_t *__rwlock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int
pthread_rwlock_timedrdlock(pthread_rwlock_t *__restrict __rwlock,
                           const struct timespec *__restrict __abstime)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
# 927 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_wrlock(pthread_rwlock_t *__rwlock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_rwlock_trywrlock(pthread_rwlock_t *__rwlock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int
pthread_rwlock_timedwrlock(pthread_rwlock_t *__restrict __rwlock,
                           const struct timespec *__restrict __abstime)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
# 949 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_unlock(pthread_rwlock_t *__rwlock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_rwlockattr_init(pthread_rwlockattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_rwlockattr_destroy(pthread_rwlockattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *__restrict __attr,
                              int *__restrict __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *__attr,
                                         int __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t *__restrict __attr,
                              int *__restrict __pref)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *__attr,
                                         int __pref)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_cond_init(pthread_cond_t *__restrict __cond,
                             const pthread_condattr_t *__restrict __cond_attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_cond_destroy(pthread_cond_t *__cond)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_cond_signal(pthread_cond_t *__cond)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_cond_broadcast(pthread_cond_t *__cond)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_cond_wait(pthread_cond_t *__restrict __cond,
                             pthread_mutex_t *__restrict __mutex)
    __attribute__((__nonnull__(1, 2)));
# 1022 "/usr/include/pthread.h" 3 4
extern int pthread_cond_timedwait(pthread_cond_t *__restrict __cond,
                                  pthread_mutex_t *__restrict __mutex,
                                  const struct timespec *__restrict __abstime)
    __attribute__((__nonnull__(1, 2, 3)));
# 1045 "/usr/include/pthread.h" 3 4
extern int pthread_condattr_init(pthread_condattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_condattr_destroy(pthread_condattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_condattr_getpshared(const pthread_condattr_t *__restrict __attr,
                            int *__restrict __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_condattr_setpshared(pthread_condattr_t *__attr,
                                       int __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_condattr_getclock(const pthread_condattr_t *__restrict __attr,
                          __clockid_t *__restrict __clock_id)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_condattr_setclock(pthread_condattr_t *__attr,
                                     __clockid_t __clock_id)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));
# 1081 "/usr/include/pthread.h" 3 4
extern int pthread_spin_init(pthread_spinlock_t *__lock, int __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_spin_destroy(pthread_spinlock_t *__lock)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_spin_lock(pthread_spinlock_t *__lock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_spin_trylock(pthread_spinlock_t *__lock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_spin_unlock(pthread_spinlock_t *__lock)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_barrier_init(pthread_barrier_t *__restrict __barrier,
                                const pthread_barrierattr_t *__restrict __attr,
                                unsigned int __count)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_barrier_destroy(pthread_barrier_t *__barrier)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_barrier_wait(pthread_barrier_t *__barrier)
    __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));

extern int pthread_barrierattr_init(pthread_barrierattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_barrierattr_destroy(pthread_barrierattr_t *__attr)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int
pthread_barrierattr_getpshared(const pthread_barrierattr_t *__restrict __attr,
                               int *__restrict __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1, 2)));

extern int pthread_barrierattr_setpshared(pthread_barrierattr_t *__attr,
                                          int __pshared)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));
# 1148 "/usr/include/pthread.h" 3 4
extern int pthread_key_create(pthread_key_t *__key,
                              void (*__destr_function)(void *))
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(1)));

extern int pthread_key_delete(pthread_key_t __key)
    __attribute__((__nothrow__, __leaf__));

extern void *pthread_getspecific(pthread_key_t __key)
    __attribute__((__nothrow__, __leaf__));

extern int pthread_setspecific(pthread_key_t __key, const void *__pointer)
    __attribute__((__nothrow__, __leaf__));

extern int pthread_getcpuclockid(pthread_t __thread_id, __clockid_t *__clock_id)
    __attribute__((__nothrow__, __leaf__)) __attribute__((__nonnull__(2)));
# 1182 "/usr/include/pthread.h" 3 4
extern int pthread_atfork(void (*__prepare)(void), void (*__parent)(void),
                          void (*__child)(void))
    __attribute__((__nothrow__, __leaf__));
# 1196 "/usr/include/pthread.h" 3 4

# 44 "/usr/include/xcb/xcb.h" 2 3 4
# 104 "/usr/include/xcb/xcb.h" 3 4
typedef struct xcb_connection_t xcb_connection_t;
# 114 "/usr/include/xcb/xcb.h" 3 4
typedef struct {
  void *data;
  int rem;
  int index;
} xcb_generic_iterator_t;

typedef struct {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
} xcb_generic_reply_t;

typedef struct {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t pad[7];
  uint32_t full_sequence;
} xcb_generic_event_t;

typedef struct {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t pad[7];
} xcb_raw_generic_event_t;
# 166 "/usr/include/xcb/xcb.h" 3 4
typedef struct {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t event_type;
  uint16_t pad1;
  uint32_t pad[5];
  uint32_t full_sequence;
} xcb_ge_event_t;

typedef struct {
  uint8_t response_type;
  uint8_t error_code;
  uint16_t sequence;
  uint32_t resource_id;
  uint16_t minor_code;
  uint8_t major_code;
  uint8_t pad0;
  uint32_t pad[5];
  uint32_t full_sequence;
} xcb_generic_error_t;

typedef struct {
  unsigned int sequence;
} xcb_void_cookie_t;

# 1 "/usr/include/xcb/xproto.h" 1 3 4
# 15 "/usr/include/xcb/xproto.h" 3 4
# 1 "/usr/include/xcb/xcb.h" 1 3 4
# 16 "/usr/include/xcb/xproto.h" 2 3 4
# 24 "/usr/include/xcb/xproto.h" 3 4
typedef struct xcb_char2b_t {
  uint8_t byte1;
  uint8_t byte2;
} xcb_char2b_t;

typedef struct xcb_char2b_iterator_t {
  xcb_char2b_t *data;
  int rem;
  int index;
} xcb_char2b_iterator_t;

typedef uint32_t xcb_window_t;

typedef struct xcb_window_iterator_t {
  xcb_window_t *data;
  int rem;
  int index;
} xcb_window_iterator_t;

typedef uint32_t xcb_pixmap_t;

typedef struct xcb_pixmap_iterator_t {
  xcb_pixmap_t *data;
  int rem;
  int index;
} xcb_pixmap_iterator_t;

typedef uint32_t xcb_cursor_t;

typedef struct xcb_cursor_iterator_t {
  xcb_cursor_t *data;
  int rem;
  int index;
} xcb_cursor_iterator_t;

typedef uint32_t xcb_font_t;

typedef struct xcb_font_iterator_t {
  xcb_font_t *data;
  int rem;
  int index;
} xcb_font_iterator_t;

typedef uint32_t xcb_gcontext_t;

typedef struct xcb_gcontext_iterator_t {
  xcb_gcontext_t *data;
  int rem;
  int index;
} xcb_gcontext_iterator_t;

typedef uint32_t xcb_colormap_t;

typedef struct xcb_colormap_iterator_t {
  xcb_colormap_t *data;
  int rem;
  int index;
} xcb_colormap_iterator_t;

typedef uint32_t xcb_atom_t;

typedef struct xcb_atom_iterator_t {
  xcb_atom_t *data;
  int rem;
  int index;
} xcb_atom_iterator_t;

typedef uint32_t xcb_drawable_t;

typedef struct xcb_drawable_iterator_t {
  xcb_drawable_t *data;
  int rem;
  int index;
} xcb_drawable_iterator_t;

typedef uint32_t xcb_fontable_t;

typedef struct xcb_fontable_iterator_t {
  xcb_fontable_t *data;
  int rem;
  int index;
} xcb_fontable_iterator_t;

typedef uint32_t xcb_bool32_t;

typedef struct xcb_bool32_iterator_t {
  xcb_bool32_t *data;
  int rem;
  int index;
} xcb_bool32_iterator_t;

typedef uint32_t xcb_visualid_t;

typedef struct xcb_visualid_iterator_t {
  xcb_visualid_t *data;
  int rem;
  int index;
} xcb_visualid_iterator_t;

typedef uint32_t xcb_timestamp_t;

typedef struct xcb_timestamp_iterator_t {
  xcb_timestamp_t *data;
  int rem;
  int index;
} xcb_timestamp_iterator_t;

typedef uint32_t xcb_keysym_t;

typedef struct xcb_keysym_iterator_t {
  xcb_keysym_t *data;
  int rem;
  int index;
} xcb_keysym_iterator_t;

typedef uint8_t xcb_keycode_t;

typedef struct xcb_keycode_iterator_t {
  xcb_keycode_t *data;
  int rem;
  int index;
} xcb_keycode_iterator_t;

typedef uint32_t xcb_keycode32_t;

typedef struct xcb_keycode32_iterator_t {
  xcb_keycode32_t *data;
  int rem;
  int index;
} xcb_keycode32_iterator_t;

typedef uint8_t xcb_button_t;

typedef struct xcb_button_iterator_t {
  xcb_button_t *data;
  int rem;
  int index;
} xcb_button_iterator_t;

typedef struct xcb_point_t {
  int16_t x;
  int16_t y;
} xcb_point_t;

typedef struct xcb_point_iterator_t {
  xcb_point_t *data;
  int rem;
  int index;
} xcb_point_iterator_t;

typedef struct xcb_rectangle_t {
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
} xcb_rectangle_t;

typedef struct xcb_rectangle_iterator_t {
  xcb_rectangle_t *data;
  int rem;
  int index;
} xcb_rectangle_iterator_t;

typedef struct xcb_arc_t {
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  int16_t angle1;
  int16_t angle2;
} xcb_arc_t;

typedef struct xcb_arc_iterator_t {
  xcb_arc_t *data;
  int rem;
  int index;
} xcb_arc_iterator_t;

typedef struct xcb_format_t {
  uint8_t depth;
  uint8_t bits_per_pixel;
  uint8_t scanline_pad;
  uint8_t pad0[5];
} xcb_format_t;

typedef struct xcb_format_iterator_t {
  xcb_format_t *data;
  int rem;
  int index;
} xcb_format_iterator_t;

typedef enum xcb_visual_class_t {
  XCB_VISUAL_CLASS_STATIC_GRAY = 0,
  XCB_VISUAL_CLASS_GRAY_SCALE = 1,
  XCB_VISUAL_CLASS_STATIC_COLOR = 2,
  XCB_VISUAL_CLASS_PSEUDO_COLOR = 3,
  XCB_VISUAL_CLASS_TRUE_COLOR = 4,
  XCB_VISUAL_CLASS_DIRECT_COLOR = 5
} xcb_visual_class_t;

typedef struct xcb_visualtype_t {
  xcb_visualid_t visual_id;
  uint8_t _class;
  uint8_t bits_per_rgb_value;
  uint16_t colormap_entries;
  uint32_t red_mask;
  uint32_t green_mask;
  uint32_t blue_mask;
  uint8_t pad0[4];
} xcb_visualtype_t;

typedef struct xcb_visualtype_iterator_t {
  xcb_visualtype_t *data;
  int rem;
  int index;
} xcb_visualtype_iterator_t;

typedef struct xcb_depth_t {
  uint8_t depth;
  uint8_t pad0;
  uint16_t visuals_len;
  uint8_t pad1[4];
} xcb_depth_t;

typedef struct xcb_depth_iterator_t {
  xcb_depth_t *data;
  int rem;
  int index;
} xcb_depth_iterator_t;

typedef enum xcb_event_mask_t {
  XCB_EVENT_MASK_NO_EVENT = 0,
  XCB_EVENT_MASK_KEY_PRESS = 1,
  XCB_EVENT_MASK_KEY_RELEASE = 2,
  XCB_EVENT_MASK_BUTTON_PRESS = 4,
  XCB_EVENT_MASK_BUTTON_RELEASE = 8,
  XCB_EVENT_MASK_ENTER_WINDOW = 16,
  XCB_EVENT_MASK_LEAVE_WINDOW = 32,
  XCB_EVENT_MASK_POINTER_MOTION = 64,
  XCB_EVENT_MASK_POINTER_MOTION_HINT = 128,
  XCB_EVENT_MASK_BUTTON_1_MOTION = 256,
  XCB_EVENT_MASK_BUTTON_2_MOTION = 512,
  XCB_EVENT_MASK_BUTTON_3_MOTION = 1024,
  XCB_EVENT_MASK_BUTTON_4_MOTION = 2048,
  XCB_EVENT_MASK_BUTTON_5_MOTION = 4096,
  XCB_EVENT_MASK_BUTTON_MOTION = 8192,
  XCB_EVENT_MASK_KEYMAP_STATE = 16384,
  XCB_EVENT_MASK_EXPOSURE = 32768,
  XCB_EVENT_MASK_VISIBILITY_CHANGE = 65536,
  XCB_EVENT_MASK_STRUCTURE_NOTIFY = 131072,
  XCB_EVENT_MASK_RESIZE_REDIRECT = 262144,
  XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY = 524288,
  XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT = 1048576,
  XCB_EVENT_MASK_FOCUS_CHANGE = 2097152,
  XCB_EVENT_MASK_PROPERTY_CHANGE = 4194304,
  XCB_EVENT_MASK_COLOR_MAP_CHANGE = 8388608,
  XCB_EVENT_MASK_OWNER_GRAB_BUTTON = 16777216
} xcb_event_mask_t;

typedef enum xcb_backing_store_t {
  XCB_BACKING_STORE_NOT_USEFUL = 0,
  XCB_BACKING_STORE_WHEN_MAPPED = 1,
  XCB_BACKING_STORE_ALWAYS = 2
} xcb_backing_store_t;

typedef struct xcb_screen_t {
  xcb_window_t root;
  xcb_colormap_t default_colormap;
  uint32_t white_pixel;
  uint32_t black_pixel;
  uint32_t current_input_masks;
  uint16_t width_in_pixels;
  uint16_t height_in_pixels;
  uint16_t width_in_millimeters;
  uint16_t height_in_millimeters;
  uint16_t min_installed_maps;
  uint16_t max_installed_maps;
  xcb_visualid_t root_visual;
  uint8_t backing_stores;
  uint8_t save_unders;
  uint8_t root_depth;
  uint8_t allowed_depths_len;
} xcb_screen_t;

typedef struct xcb_screen_iterator_t {
  xcb_screen_t *data;
  int rem;
  int index;
} xcb_screen_iterator_t;

typedef struct xcb_setup_request_t {
  uint8_t byte_order;
  uint8_t pad0;
  uint16_t protocol_major_version;
  uint16_t protocol_minor_version;
  uint16_t authorization_protocol_name_len;
  uint16_t authorization_protocol_data_len;
  uint8_t pad1[2];
} xcb_setup_request_t;

typedef struct xcb_setup_request_iterator_t {
  xcb_setup_request_t *data;
  int rem;
  int index;
} xcb_setup_request_iterator_t;

typedef struct xcb_setup_failed_t {
  uint8_t status;
  uint8_t reason_len;
  uint16_t protocol_major_version;
  uint16_t protocol_minor_version;
  uint16_t length;
} xcb_setup_failed_t;

typedef struct xcb_setup_failed_iterator_t {
  xcb_setup_failed_t *data;
  int rem;
  int index;
} xcb_setup_failed_iterator_t;

typedef struct xcb_setup_authenticate_t {
  uint8_t status;
  uint8_t pad0[5];
  uint16_t length;
} xcb_setup_authenticate_t;

typedef struct xcb_setup_authenticate_iterator_t {
  xcb_setup_authenticate_t *data;
  int rem;
  int index;
} xcb_setup_authenticate_iterator_t;

typedef enum xcb_image_order_t {
  XCB_IMAGE_ORDER_LSB_FIRST = 0,
  XCB_IMAGE_ORDER_MSB_FIRST = 1
} xcb_image_order_t;

typedef struct xcb_setup_t {
  uint8_t status;
  uint8_t pad0;
  uint16_t protocol_major_version;
  uint16_t protocol_minor_version;
  uint16_t length;
  uint32_t release_number;
  uint32_t resource_id_base;
  uint32_t resource_id_mask;
  uint32_t motion_buffer_size;
  uint16_t vendor_len;
  uint16_t maximum_request_length;
  uint8_t roots_len;
  uint8_t pixmap_formats_len;
  uint8_t image_byte_order;
  uint8_t bitmap_format_bit_order;
  uint8_t bitmap_format_scanline_unit;
  uint8_t bitmap_format_scanline_pad;
  xcb_keycode_t min_keycode;
  xcb_keycode_t max_keycode;
  uint8_t pad1[4];
} xcb_setup_t;

typedef struct xcb_setup_iterator_t {
  xcb_setup_t *data;
  int rem;
  int index;
} xcb_setup_iterator_t;

typedef enum xcb_mod_mask_t {
  XCB_MOD_MASK_SHIFT = 1,
  XCB_MOD_MASK_LOCK = 2,
  XCB_MOD_MASK_CONTROL = 4,
  XCB_MOD_MASK_1 = 8,
  XCB_MOD_MASK_2 = 16,
  XCB_MOD_MASK_3 = 32,
  XCB_MOD_MASK_4 = 64,
  XCB_MOD_MASK_5 = 128,
  XCB_MOD_MASK_ANY = 32768
} xcb_mod_mask_t;

typedef enum xcb_key_but_mask_t {
  XCB_KEY_BUT_MASK_SHIFT = 1,
  XCB_KEY_BUT_MASK_LOCK = 2,
  XCB_KEY_BUT_MASK_CONTROL = 4,
  XCB_KEY_BUT_MASK_MOD_1 = 8,
  XCB_KEY_BUT_MASK_MOD_2 = 16,
  XCB_KEY_BUT_MASK_MOD_3 = 32,
  XCB_KEY_BUT_MASK_MOD_4 = 64,
  XCB_KEY_BUT_MASK_MOD_5 = 128,
  XCB_KEY_BUT_MASK_BUTTON_1 = 256,
  XCB_KEY_BUT_MASK_BUTTON_2 = 512,
  XCB_KEY_BUT_MASK_BUTTON_3 = 1024,
  XCB_KEY_BUT_MASK_BUTTON_4 = 2048,
  XCB_KEY_BUT_MASK_BUTTON_5 = 4096
} xcb_key_but_mask_t;

typedef enum xcb_window_enum_t { XCB_WINDOW_NONE = 0 } xcb_window_enum_t;

typedef struct xcb_key_press_event_t {
  uint8_t response_type;
  xcb_keycode_t detail;
  uint16_t sequence;
  xcb_timestamp_t time;
  xcb_window_t root;
  xcb_window_t event;
  xcb_window_t child;
  int16_t root_x;
  int16_t root_y;
  int16_t event_x;
  int16_t event_y;
  uint16_t state;
  uint8_t same_screen;
  uint8_t pad0;
} xcb_key_press_event_t;

typedef xcb_key_press_event_t xcb_key_release_event_t;

typedef enum xcb_button_mask_t {
  XCB_BUTTON_MASK_1 = 256,
  XCB_BUTTON_MASK_2 = 512,
  XCB_BUTTON_MASK_3 = 1024,
  XCB_BUTTON_MASK_4 = 2048,
  XCB_BUTTON_MASK_5 = 4096,
  XCB_BUTTON_MASK_ANY = 32768
} xcb_button_mask_t;

typedef struct xcb_button_press_event_t {
  uint8_t response_type;
  xcb_button_t detail;
  uint16_t sequence;
  xcb_timestamp_t time;
  xcb_window_t root;
  xcb_window_t event;
  xcb_window_t child;
  int16_t root_x;
  int16_t root_y;
  int16_t event_x;
  int16_t event_y;
  uint16_t state;
  uint8_t same_screen;
  uint8_t pad0;
} xcb_button_press_event_t;

typedef xcb_button_press_event_t xcb_button_release_event_t;

typedef enum xcb_motion_t {
  XCB_MOTION_NORMAL = 0,
  XCB_MOTION_HINT = 1
} xcb_motion_t;

typedef struct xcb_motion_notify_event_t {
  uint8_t response_type;
  uint8_t detail;
  uint16_t sequence;
  xcb_timestamp_t time;
  xcb_window_t root;
  xcb_window_t event;
  xcb_window_t child;
  int16_t root_x;
  int16_t root_y;
  int16_t event_x;
  int16_t event_y;
  uint16_t state;
  uint8_t same_screen;
  uint8_t pad0;
} xcb_motion_notify_event_t;

typedef enum xcb_notify_detail_t {
  XCB_NOTIFY_DETAIL_ANCESTOR = 0,
  XCB_NOTIFY_DETAIL_VIRTUAL = 1,
  XCB_NOTIFY_DETAIL_INFERIOR = 2,
  XCB_NOTIFY_DETAIL_NONLINEAR = 3,
  XCB_NOTIFY_DETAIL_NONLINEAR_VIRTUAL = 4,
  XCB_NOTIFY_DETAIL_POINTER = 5,
  XCB_NOTIFY_DETAIL_POINTER_ROOT = 6,
  XCB_NOTIFY_DETAIL_NONE = 7
} xcb_notify_detail_t;

typedef enum xcb_notify_mode_t {
  XCB_NOTIFY_MODE_NORMAL = 0,
  XCB_NOTIFY_MODE_GRAB = 1,
  XCB_NOTIFY_MODE_UNGRAB = 2,
  XCB_NOTIFY_MODE_WHILE_GRABBED = 3
} xcb_notify_mode_t;

typedef struct xcb_enter_notify_event_t {
  uint8_t response_type;
  uint8_t detail;
  uint16_t sequence;
  xcb_timestamp_t time;
  xcb_window_t root;
  xcb_window_t event;
  xcb_window_t child;
  int16_t root_x;
  int16_t root_y;
  int16_t event_x;
  int16_t event_y;
  uint16_t state;
  uint8_t mode;
  uint8_t same_screen_focus;
} xcb_enter_notify_event_t;

typedef xcb_enter_notify_event_t xcb_leave_notify_event_t;

typedef struct xcb_focus_in_event_t {
  uint8_t response_type;
  uint8_t detail;
  uint16_t sequence;
  xcb_window_t event;
  uint8_t mode;
  uint8_t pad0[3];
} xcb_focus_in_event_t;

typedef xcb_focus_in_event_t xcb_focus_out_event_t;

typedef struct xcb_keymap_notify_event_t {
  uint8_t response_type;
  uint8_t keys[31];
} xcb_keymap_notify_event_t;

typedef struct xcb_expose_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t window;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t count;
  uint8_t pad1[2];
} xcb_expose_event_t;

typedef struct xcb_graphics_exposure_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_drawable_t drawable;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t minor_opcode;
  uint16_t count;
  uint8_t major_opcode;
  uint8_t pad1[3];
} xcb_graphics_exposure_event_t;

typedef struct xcb_no_exposure_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_drawable_t drawable;
  uint16_t minor_opcode;
  uint8_t major_opcode;
  uint8_t pad1;
} xcb_no_exposure_event_t;

typedef enum xcb_visibility_t {
  XCB_VISIBILITY_UNOBSCURED = 0,
  XCB_VISIBILITY_PARTIALLY_OBSCURED = 1,
  XCB_VISIBILITY_FULLY_OBSCURED = 2
} xcb_visibility_t;

typedef struct xcb_visibility_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t window;
  uint8_t state;
  uint8_t pad1[3];
} xcb_visibility_notify_event_t;

typedef struct xcb_create_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t parent;
  xcb_window_t window;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t border_width;
  uint8_t override_redirect;
  uint8_t pad1;
} xcb_create_notify_event_t;

typedef struct xcb_destroy_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t event;
  xcb_window_t window;
} xcb_destroy_notify_event_t;

typedef struct xcb_unmap_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t event;
  xcb_window_t window;
  uint8_t from_configure;
  uint8_t pad1[3];
} xcb_unmap_notify_event_t;

typedef struct xcb_map_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t event;
  xcb_window_t window;
  uint8_t override_redirect;
  uint8_t pad1[3];
} xcb_map_notify_event_t;

typedef struct xcb_map_request_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t parent;
  xcb_window_t window;
} xcb_map_request_event_t;

typedef struct xcb_reparent_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t event;
  xcb_window_t window;
  xcb_window_t parent;
  int16_t x;
  int16_t y;
  uint8_t override_redirect;
  uint8_t pad1[3];
} xcb_reparent_notify_event_t;

typedef struct xcb_configure_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t event;
  xcb_window_t window;
  xcb_window_t above_sibling;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t border_width;
  uint8_t override_redirect;
  uint8_t pad1;
} xcb_configure_notify_event_t;

typedef struct xcb_configure_request_event_t {
  uint8_t response_type;
  uint8_t stack_mode;
  uint16_t sequence;
  xcb_window_t parent;
  xcb_window_t window;
  xcb_window_t sibling;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t border_width;
  uint16_t value_mask;
} xcb_configure_request_event_t;

typedef struct xcb_gravity_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t event;
  xcb_window_t window;
  int16_t x;
  int16_t y;
} xcb_gravity_notify_event_t;

typedef struct xcb_resize_request_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t window;
  uint16_t width;
  uint16_t height;
} xcb_resize_request_event_t;

typedef enum xcb_place_t {
  XCB_PLACE_ON_TOP = 0,

  XCB_PLACE_ON_BOTTOM = 1

} xcb_place_t;

typedef struct xcb_circulate_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t event;
  xcb_window_t window;
  uint8_t pad1[4];
  uint8_t place;
  uint8_t pad2[3];
} xcb_circulate_notify_event_t;

typedef xcb_circulate_notify_event_t xcb_circulate_request_event_t;

typedef enum xcb_property_t {
  XCB_PROPERTY_NEW_VALUE = 0,
  XCB_PROPERTY_DELETE = 1
} xcb_property_t;

typedef struct xcb_property_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t window;
  xcb_atom_t atom;
  xcb_timestamp_t time;
  uint8_t state;
  uint8_t pad1[3];
} xcb_property_notify_event_t;

typedef struct xcb_selection_clear_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_timestamp_t time;
  xcb_window_t owner;
  xcb_atom_t selection;
} xcb_selection_clear_event_t;

typedef enum xcb_time_t { XCB_TIME_CURRENT_TIME = 0 } xcb_time_t;

typedef enum xcb_atom_enum_t {
  XCB_ATOM_NONE = 0,
  XCB_ATOM_ANY = 0,
  XCB_ATOM_PRIMARY = 1,
  XCB_ATOM_SECONDARY = 2,
  XCB_ATOM_ARC = 3,
  XCB_ATOM_ATOM = 4,
  XCB_ATOM_BITMAP = 5,
  XCB_ATOM_CARDINAL = 6,
  XCB_ATOM_COLORMAP = 7,
  XCB_ATOM_CURSOR = 8,
  XCB_ATOM_CUT_BUFFER0 = 9,
  XCB_ATOM_CUT_BUFFER1 = 10,
  XCB_ATOM_CUT_BUFFER2 = 11,
  XCB_ATOM_CUT_BUFFER3 = 12,
  XCB_ATOM_CUT_BUFFER4 = 13,
  XCB_ATOM_CUT_BUFFER5 = 14,
  XCB_ATOM_CUT_BUFFER6 = 15,
  XCB_ATOM_CUT_BUFFER7 = 16,
  XCB_ATOM_DRAWABLE = 17,
  XCB_ATOM_FONT = 18,
  XCB_ATOM_INTEGER = 19,
  XCB_ATOM_PIXMAP = 20,
  XCB_ATOM_POINT = 21,
  XCB_ATOM_RECTANGLE = 22,
  XCB_ATOM_RESOURCE_MANAGER = 23,
  XCB_ATOM_RGB_COLOR_MAP = 24,
  XCB_ATOM_RGB_BEST_MAP = 25,
  XCB_ATOM_RGB_BLUE_MAP = 26,
  XCB_ATOM_RGB_DEFAULT_MAP = 27,
  XCB_ATOM_RGB_GRAY_MAP = 28,
  XCB_ATOM_RGB_GREEN_MAP = 29,
  XCB_ATOM_RGB_RED_MAP = 30,
  XCB_ATOM_STRING = 31,
  XCB_ATOM_VISUALID = 32,
  XCB_ATOM_WINDOW = 33,
  XCB_ATOM_WM_COMMAND = 34,
  XCB_ATOM_WM_HINTS = 35,
  XCB_ATOM_WM_CLIENT_MACHINE = 36,
  XCB_ATOM_WM_ICON_NAME = 37,
  XCB_ATOM_WM_ICON_SIZE = 38,
  XCB_ATOM_WM_NAME = 39,
  XCB_ATOM_WM_NORMAL_HINTS = 40,
  XCB_ATOM_WM_SIZE_HINTS = 41,
  XCB_ATOM_WM_ZOOM_HINTS = 42,
  XCB_ATOM_MIN_SPACE = 43,
  XCB_ATOM_NORM_SPACE = 44,
  XCB_ATOM_MAX_SPACE = 45,
  XCB_ATOM_END_SPACE = 46,
  XCB_ATOM_SUPERSCRIPT_X = 47,
  XCB_ATOM_SUPERSCRIPT_Y = 48,
  XCB_ATOM_SUBSCRIPT_X = 49,
  XCB_ATOM_SUBSCRIPT_Y = 50,
  XCB_ATOM_UNDERLINE_POSITION = 51,
  XCB_ATOM_UNDERLINE_THICKNESS = 52,
  XCB_ATOM_STRIKEOUT_ASCENT = 53,
  XCB_ATOM_STRIKEOUT_DESCENT = 54,
  XCB_ATOM_ITALIC_ANGLE = 55,
  XCB_ATOM_X_HEIGHT = 56,
  XCB_ATOM_QUAD_WIDTH = 57,
  XCB_ATOM_WEIGHT = 58,
  XCB_ATOM_POINT_SIZE = 59,
  XCB_ATOM_RESOLUTION = 60,
  XCB_ATOM_COPYRIGHT = 61,
  XCB_ATOM_NOTICE = 62,
  XCB_ATOM_FONT_NAME = 63,
  XCB_ATOM_FAMILY_NAME = 64,
  XCB_ATOM_FULL_NAME = 65,
  XCB_ATOM_CAP_HEIGHT = 66,
  XCB_ATOM_WM_CLASS = 67,
  XCB_ATOM_WM_TRANSIENT_FOR = 68
} xcb_atom_enum_t;

typedef struct xcb_selection_request_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_timestamp_t time;
  xcb_window_t owner;
  xcb_window_t requestor;
  xcb_atom_t selection;
  xcb_atom_t target;
  xcb_atom_t property;
} xcb_selection_request_event_t;

typedef struct xcb_selection_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_timestamp_t time;
  xcb_window_t requestor;
  xcb_atom_t selection;
  xcb_atom_t target;
  xcb_atom_t property;
} xcb_selection_notify_event_t;

typedef enum xcb_colormap_state_t {
  XCB_COLORMAP_STATE_UNINSTALLED = 0,

  XCB_COLORMAP_STATE_INSTALLED = 1

} xcb_colormap_state_t;

typedef enum xcb_colormap_enum_t { XCB_COLORMAP_NONE = 0 } xcb_colormap_enum_t;

typedef struct xcb_colormap_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  xcb_window_t window;
  xcb_colormap_t colormap;
  uint8_t _new;
  uint8_t state;
  uint8_t pad1[2];
} xcb_colormap_notify_event_t;

typedef union xcb_client_message_data_t {
  uint8_t data8[20];
  uint16_t data16[10];
  uint32_t data32[5];
} xcb_client_message_data_t;

typedef struct xcb_client_message_data_iterator_t {
  xcb_client_message_data_t *data;
  int rem;
  int index;
} xcb_client_message_data_iterator_t;

typedef struct xcb_client_message_event_t {
  uint8_t response_type;
  uint8_t format;
  uint16_t sequence;
  xcb_window_t window;
  xcb_atom_t type;
  xcb_client_message_data_t data;
} xcb_client_message_event_t;

typedef enum xcb_mapping_t {
  XCB_MAPPING_MODIFIER = 0,
  XCB_MAPPING_KEYBOARD = 1,
  XCB_MAPPING_POINTER = 2
} xcb_mapping_t;

typedef struct xcb_mapping_notify_event_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint8_t request;
  xcb_keycode_t first_keycode;
  uint8_t count;
  uint8_t pad1;
} xcb_mapping_notify_event_t;

typedef struct xcb_ge_generic_event_t {
  uint8_t response_type;
  uint8_t extension;
  uint16_t sequence;
  uint32_t length;
  uint16_t event_type;
  uint8_t pad0[22];
  uint32_t full_sequence;
} xcb_ge_generic_event_t;

typedef struct xcb_request_error_t {
  uint8_t response_type;
  uint8_t error_code;
  uint16_t sequence;
  uint32_t bad_value;
  uint16_t minor_opcode;
  uint8_t major_opcode;
  uint8_t pad0;
} xcb_request_error_t;

typedef struct xcb_value_error_t {
  uint8_t response_type;
  uint8_t error_code;
  uint16_t sequence;
  uint32_t bad_value;
  uint16_t minor_opcode;
  uint8_t major_opcode;
  uint8_t pad0;
} xcb_value_error_t;

typedef xcb_value_error_t xcb_window_error_t;

typedef xcb_value_error_t xcb_pixmap_error_t;

typedef xcb_value_error_t xcb_atom_error_t;

typedef xcb_value_error_t xcb_cursor_error_t;

typedef xcb_value_error_t xcb_font_error_t;

typedef xcb_request_error_t xcb_match_error_t;

typedef xcb_value_error_t xcb_drawable_error_t;

typedef xcb_request_error_t xcb_access_error_t;

typedef xcb_request_error_t xcb_alloc_error_t;

typedef xcb_value_error_t xcb_colormap_error_t;

typedef xcb_value_error_t xcb_g_context_error_t;

typedef xcb_value_error_t xcb_id_choice_error_t;

typedef xcb_request_error_t xcb_name_error_t;

typedef xcb_request_error_t xcb_length_error_t;

typedef xcb_request_error_t xcb_implementation_error_t;

typedef enum xcb_window_class_t {
  XCB_WINDOW_CLASS_COPY_FROM_PARENT = 0,
  XCB_WINDOW_CLASS_INPUT_OUTPUT = 1,
  XCB_WINDOW_CLASS_INPUT_ONLY = 2
} xcb_window_class_t;

typedef enum xcb_cw_t {
  XCB_CW_BACK_PIXMAP = 1,
# 1369 "/usr/include/xcb/xproto.h" 3 4
  XCB_CW_BACK_PIXEL = 2,

  XCB_CW_BORDER_PIXMAP = 4,
# 1383 "/usr/include/xcb/xproto.h" 3 4
  XCB_CW_BORDER_PIXEL = 8,

  XCB_CW_BIT_GRAVITY = 16,

  XCB_CW_WIN_GRAVITY = 32,

  XCB_CW_BACKING_STORE = 64,
# 1408 "/usr/include/xcb/xproto.h" 3 4
  XCB_CW_BACKING_PLANES = 128,

  XCB_CW_BACKING_PIXEL = 256,

  XCB_CW_OVERRIDE_REDIRECT = 512,

  XCB_CW_SAVE_UNDER = 1024,

  XCB_CW_EVENT_MASK = 2048,

  XCB_CW_DONT_PROPAGATE = 4096,

  XCB_CW_COLORMAP = 8192,
# 1448 "/usr/include/xcb/xproto.h" 3 4
  XCB_CW_CURSOR = 16384

} xcb_cw_t;

typedef enum xcb_back_pixmap_t {
  XCB_BACK_PIXMAP_NONE = 0,
  XCB_BACK_PIXMAP_PARENT_RELATIVE = 1
} xcb_back_pixmap_t;

typedef enum xcb_gravity_t {
  XCB_GRAVITY_BIT_FORGET = 0,
  XCB_GRAVITY_WIN_UNMAP = 0,
  XCB_GRAVITY_NORTH_WEST = 1,
  XCB_GRAVITY_NORTH = 2,
  XCB_GRAVITY_NORTH_EAST = 3,
  XCB_GRAVITY_WEST = 4,
  XCB_GRAVITY_CENTER = 5,
  XCB_GRAVITY_EAST = 6,
  XCB_GRAVITY_SOUTH_WEST = 7,
  XCB_GRAVITY_SOUTH = 8,
  XCB_GRAVITY_SOUTH_EAST = 9,
  XCB_GRAVITY_STATIC = 10
} xcb_gravity_t;

typedef struct xcb_create_window_value_list_t {
  xcb_pixmap_t background_pixmap;
  uint32_t background_pixel;
  xcb_pixmap_t border_pixmap;
  uint32_t border_pixel;
  uint32_t bit_gravity;
  uint32_t win_gravity;
  uint32_t backing_store;
  uint32_t backing_planes;
  uint32_t backing_pixel;
  xcb_bool32_t override_redirect;
  xcb_bool32_t save_under;
  uint32_t event_mask;
  uint32_t do_not_propogate_mask;
  xcb_colormap_t colormap;
  xcb_cursor_t cursor;
} xcb_create_window_value_list_t;

typedef struct xcb_create_window_request_t {
  uint8_t major_opcode;
  uint8_t depth;
  uint16_t length;
  xcb_window_t wid;
  xcb_window_t parent;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t border_width;
  uint16_t _class;
  xcb_visualid_t visual;
  uint32_t value_mask;
} xcb_create_window_request_t;

typedef struct xcb_change_window_attributes_value_list_t {
  xcb_pixmap_t background_pixmap;
  uint32_t background_pixel;
  xcb_pixmap_t border_pixmap;
  uint32_t border_pixel;
  uint32_t bit_gravity;
  uint32_t win_gravity;
  uint32_t backing_store;
  uint32_t backing_planes;
  uint32_t backing_pixel;
  xcb_bool32_t override_redirect;
  xcb_bool32_t save_under;
  uint32_t event_mask;
  uint32_t do_not_propogate_mask;
  xcb_colormap_t colormap;
  xcb_cursor_t cursor;
} xcb_change_window_attributes_value_list_t;

typedef struct xcb_change_window_attributes_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
  uint32_t value_mask;
} xcb_change_window_attributes_request_t;

typedef enum xcb_map_state_t {
  XCB_MAP_STATE_UNMAPPED = 0,
  XCB_MAP_STATE_UNVIEWABLE = 1,
  XCB_MAP_STATE_VIEWABLE = 2
} xcb_map_state_t;

typedef struct xcb_get_window_attributes_cookie_t {
  unsigned int sequence;
} xcb_get_window_attributes_cookie_t;

typedef struct xcb_get_window_attributes_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_get_window_attributes_request_t;

typedef struct xcb_get_window_attributes_reply_t {
  uint8_t response_type;
  uint8_t backing_store;
  uint16_t sequence;
  uint32_t length;
  xcb_visualid_t visual;
  uint16_t _class;
  uint8_t bit_gravity;
  uint8_t win_gravity;
  uint32_t backing_planes;
  uint32_t backing_pixel;
  uint8_t save_under;
  uint8_t map_is_installed;
  uint8_t map_state;
  uint8_t override_redirect;
  xcb_colormap_t colormap;
  uint32_t all_event_masks;
  uint32_t your_event_mask;
  uint16_t do_not_propagate_mask;
  uint8_t pad0[2];
} xcb_get_window_attributes_reply_t;

typedef struct xcb_destroy_window_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_destroy_window_request_t;

typedef struct xcb_destroy_subwindows_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_destroy_subwindows_request_t;

typedef enum xcb_set_mode_t {
  XCB_SET_MODE_INSERT = 0,
  XCB_SET_MODE_DELETE = 1
} xcb_set_mode_t;

typedef struct xcb_change_save_set_request_t {
  uint8_t major_opcode;
  uint8_t mode;
  uint16_t length;
  xcb_window_t window;
} xcb_change_save_set_request_t;

typedef struct xcb_reparent_window_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
  xcb_window_t parent;
  int16_t x;
  int16_t y;
} xcb_reparent_window_request_t;

typedef struct xcb_map_window_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_map_window_request_t;

typedef struct xcb_map_subwindows_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_map_subwindows_request_t;

typedef struct xcb_unmap_window_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_unmap_window_request_t;

typedef struct xcb_unmap_subwindows_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_unmap_subwindows_request_t;

typedef enum xcb_config_window_t {
  XCB_CONFIG_WINDOW_X = 1,
  XCB_CONFIG_WINDOW_Y = 2,
  XCB_CONFIG_WINDOW_WIDTH = 4,
  XCB_CONFIG_WINDOW_HEIGHT = 8,
  XCB_CONFIG_WINDOW_BORDER_WIDTH = 16,
  XCB_CONFIG_WINDOW_SIBLING = 32,
  XCB_CONFIG_WINDOW_STACK_MODE = 64
} xcb_config_window_t;

typedef enum xcb_stack_mode_t {
  XCB_STACK_MODE_ABOVE = 0,
  XCB_STACK_MODE_BELOW = 1,
  XCB_STACK_MODE_TOP_IF = 2,
  XCB_STACK_MODE_BOTTOM_IF = 3,
  XCB_STACK_MODE_OPPOSITE = 4
} xcb_stack_mode_t;

typedef struct xcb_configure_window_value_list_t {
  int32_t x;
  int32_t y;
  uint32_t width;
  uint32_t height;
  uint32_t border_width;
  xcb_window_t sibling;
  uint32_t stack_mode;
} xcb_configure_window_value_list_t;

typedef struct xcb_configure_window_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
  uint16_t value_mask;
  uint8_t pad1[2];
} xcb_configure_window_request_t;

typedef enum xcb_circulate_t {
  XCB_CIRCULATE_RAISE_LOWEST = 0,
  XCB_CIRCULATE_LOWER_HIGHEST = 1
} xcb_circulate_t;

typedef struct xcb_circulate_window_request_t {
  uint8_t major_opcode;
  uint8_t direction;
  uint16_t length;
  xcb_window_t window;
} xcb_circulate_window_request_t;

typedef struct xcb_get_geometry_cookie_t {
  unsigned int sequence;
} xcb_get_geometry_cookie_t;

typedef struct xcb_get_geometry_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
} xcb_get_geometry_request_t;

typedef struct xcb_get_geometry_reply_t {
  uint8_t response_type;
  uint8_t depth;
  uint16_t sequence;
  uint32_t length;
  xcb_window_t root;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t border_width;
  uint8_t pad0[2];
} xcb_get_geometry_reply_t;

typedef struct xcb_query_tree_cookie_t {
  unsigned int sequence;
} xcb_query_tree_cookie_t;

typedef struct xcb_query_tree_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_query_tree_request_t;

typedef struct xcb_query_tree_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  xcb_window_t root;
  xcb_window_t parent;
  uint16_t children_len;
  uint8_t pad1[14];
} xcb_query_tree_reply_t;

typedef struct xcb_intern_atom_cookie_t {
  unsigned int sequence;
} xcb_intern_atom_cookie_t;

typedef struct xcb_intern_atom_request_t {
  uint8_t major_opcode;
  uint8_t only_if_exists;
  uint16_t length;
  uint16_t name_len;
  uint8_t pad0[2];
} xcb_intern_atom_request_t;

typedef struct xcb_intern_atom_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  xcb_atom_t atom;
} xcb_intern_atom_reply_t;

typedef struct xcb_get_atom_name_cookie_t {
  unsigned int sequence;
} xcb_get_atom_name_cookie_t;

typedef struct xcb_get_atom_name_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_atom_t atom;
} xcb_get_atom_name_request_t;

typedef struct xcb_get_atom_name_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t name_len;
  uint8_t pad1[22];
} xcb_get_atom_name_reply_t;

typedef enum xcb_prop_mode_t {
  XCB_PROP_MODE_REPLACE = 0,

  XCB_PROP_MODE_PREPEND = 1,

  XCB_PROP_MODE_APPEND = 2

} xcb_prop_mode_t;

typedef struct xcb_change_property_request_t {
  uint8_t major_opcode;
  uint8_t mode;
  uint16_t length;
  xcb_window_t window;
  xcb_atom_t property;
  xcb_atom_t type;
  uint8_t format;
  uint8_t pad0[3];
  uint32_t data_len;
} xcb_change_property_request_t;

typedef struct xcb_delete_property_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
  xcb_atom_t property;
} xcb_delete_property_request_t;

typedef enum xcb_get_property_type_t {
  XCB_GET_PROPERTY_TYPE_ANY = 0
} xcb_get_property_type_t;

typedef struct xcb_get_property_cookie_t {
  unsigned int sequence;
} xcb_get_property_cookie_t;

typedef struct xcb_get_property_request_t {
  uint8_t major_opcode;
  uint8_t _delete;
  uint16_t length;
  xcb_window_t window;
  xcb_atom_t property;
  xcb_atom_t type;
  uint32_t long_offset;
  uint32_t long_length;
} xcb_get_property_request_t;

typedef struct xcb_get_property_reply_t {
  uint8_t response_type;
  uint8_t format;
  uint16_t sequence;
  uint32_t length;
  xcb_atom_t type;
  uint32_t bytes_after;
  uint32_t value_len;
  uint8_t pad0[12];
} xcb_get_property_reply_t;

typedef struct xcb_list_properties_cookie_t {
  unsigned int sequence;
} xcb_list_properties_cookie_t;

typedef struct xcb_list_properties_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_list_properties_request_t;

typedef struct xcb_list_properties_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t atoms_len;
  uint8_t pad1[22];
} xcb_list_properties_reply_t;

typedef struct xcb_set_selection_owner_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t owner;
  xcb_atom_t selection;
  xcb_timestamp_t time;
} xcb_set_selection_owner_request_t;

typedef struct xcb_get_selection_owner_cookie_t {
  unsigned int sequence;
} xcb_get_selection_owner_cookie_t;

typedef struct xcb_get_selection_owner_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_atom_t selection;
} xcb_get_selection_owner_request_t;

typedef struct xcb_get_selection_owner_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  xcb_window_t owner;
} xcb_get_selection_owner_reply_t;

typedef struct xcb_convert_selection_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t requestor;
  xcb_atom_t selection;
  xcb_atom_t target;
  xcb_atom_t property;
  xcb_timestamp_t time;
} xcb_convert_selection_request_t;

typedef enum xcb_send_event_dest_t {
  XCB_SEND_EVENT_DEST_POINTER_WINDOW = 0,
  XCB_SEND_EVENT_DEST_ITEM_FOCUS = 1
} xcb_send_event_dest_t;

typedef struct xcb_send_event_request_t {
  uint8_t major_opcode;
  uint8_t propagate;
  uint16_t length;
  xcb_window_t destination;
  uint32_t event_mask;
  char event[32];
} xcb_send_event_request_t;

typedef enum xcb_grab_mode_t {
  XCB_GRAB_MODE_SYNC = 0,

  XCB_GRAB_MODE_ASYNC = 1

} xcb_grab_mode_t;

typedef enum xcb_grab_status_t {
  XCB_GRAB_STATUS_SUCCESS = 0,
  XCB_GRAB_STATUS_ALREADY_GRABBED = 1,
  XCB_GRAB_STATUS_INVALID_TIME = 2,
  XCB_GRAB_STATUS_NOT_VIEWABLE = 3,
  XCB_GRAB_STATUS_FROZEN = 4
} xcb_grab_status_t;

typedef enum xcb_cursor_enum_t { XCB_CURSOR_NONE = 0 } xcb_cursor_enum_t;

typedef struct xcb_grab_pointer_cookie_t {
  unsigned int sequence;
} xcb_grab_pointer_cookie_t;

typedef struct xcb_grab_pointer_request_t {
  uint8_t major_opcode;
  uint8_t owner_events;
  uint16_t length;
  xcb_window_t grab_window;
  uint16_t event_mask;
  uint8_t pointer_mode;
  uint8_t keyboard_mode;
  xcb_window_t confine_to;
  xcb_cursor_t cursor;
  xcb_timestamp_t time;
} xcb_grab_pointer_request_t;

typedef struct xcb_grab_pointer_reply_t {
  uint8_t response_type;
  uint8_t status;
  uint16_t sequence;
  uint32_t length;
} xcb_grab_pointer_reply_t;

typedef struct xcb_ungrab_pointer_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_timestamp_t time;
} xcb_ungrab_pointer_request_t;

typedef enum xcb_button_index_t {
  XCB_BUTTON_INDEX_ANY = 0,

  XCB_BUTTON_INDEX_1 = 1,

  XCB_BUTTON_INDEX_2 = 2,

  XCB_BUTTON_INDEX_3 = 3,

  XCB_BUTTON_INDEX_4 = 4,

  XCB_BUTTON_INDEX_5 = 5

} xcb_button_index_t;

typedef struct xcb_grab_button_request_t {
  uint8_t major_opcode;
  uint8_t owner_events;
  uint16_t length;
  xcb_window_t grab_window;
  uint16_t event_mask;
  uint8_t pointer_mode;
  uint8_t keyboard_mode;
  xcb_window_t confine_to;
  xcb_cursor_t cursor;
  uint8_t button;
  uint8_t pad0;
  uint16_t modifiers;
} xcb_grab_button_request_t;

typedef struct xcb_ungrab_button_request_t {
  uint8_t major_opcode;
  uint8_t button;
  uint16_t length;
  xcb_window_t grab_window;
  uint16_t modifiers;
  uint8_t pad0[2];
} xcb_ungrab_button_request_t;

typedef struct xcb_change_active_pointer_grab_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_cursor_t cursor;
  xcb_timestamp_t time;
  uint16_t event_mask;
  uint8_t pad1[2];
} xcb_change_active_pointer_grab_request_t;

typedef struct xcb_grab_keyboard_cookie_t {
  unsigned int sequence;
} xcb_grab_keyboard_cookie_t;

typedef struct xcb_grab_keyboard_request_t {
  uint8_t major_opcode;
  uint8_t owner_events;
  uint16_t length;
  xcb_window_t grab_window;
  xcb_timestamp_t time;
  uint8_t pointer_mode;
  uint8_t keyboard_mode;
  uint8_t pad0[2];
} xcb_grab_keyboard_request_t;

typedef struct xcb_grab_keyboard_reply_t {
  uint8_t response_type;
  uint8_t status;
  uint16_t sequence;
  uint32_t length;
} xcb_grab_keyboard_reply_t;

typedef struct xcb_ungrab_keyboard_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_timestamp_t time;
} xcb_ungrab_keyboard_request_t;

typedef enum xcb_grab_t { XCB_GRAB_ANY = 0 } xcb_grab_t;

typedef struct xcb_grab_key_request_t {
  uint8_t major_opcode;
  uint8_t owner_events;
  uint16_t length;
  xcb_window_t grab_window;
  uint16_t modifiers;
  xcb_keycode_t key;
  uint8_t pointer_mode;
  uint8_t keyboard_mode;
  uint8_t pad0[3];
} xcb_grab_key_request_t;

typedef struct xcb_ungrab_key_request_t {
  uint8_t major_opcode;
  xcb_keycode_t key;
  uint16_t length;
  xcb_window_t grab_window;
  uint16_t modifiers;
  uint8_t pad0[2];
} xcb_ungrab_key_request_t;

typedef enum xcb_allow_t {
  XCB_ALLOW_ASYNC_POINTER = 0,
# 2359 "/usr/include/xcb/xproto.h" 3 4
  XCB_ALLOW_SYNC_POINTER = 1,
# 2368 "/usr/include/xcb/xproto.h" 3 4
  XCB_ALLOW_REPLAY_POINTER = 2,
# 2378 "/usr/include/xcb/xproto.h" 3 4
  XCB_ALLOW_ASYNC_KEYBOARD = 3,

  XCB_ALLOW_SYNC_KEYBOARD = 4,
# 2394 "/usr/include/xcb/xproto.h" 3 4
  XCB_ALLOW_REPLAY_KEYBOARD = 5,
# 2404 "/usr/include/xcb/xproto.h" 3 4
  XCB_ALLOW_ASYNC_BOTH = 6,

  XCB_ALLOW_SYNC_BOTH = 7
# 2423 "/usr/include/xcb/xproto.h" 3 4
} xcb_allow_t;

typedef struct xcb_allow_events_request_t {
  uint8_t major_opcode;
  uint8_t mode;
  uint16_t length;
  xcb_timestamp_t time;
} xcb_allow_events_request_t;

typedef struct xcb_grab_server_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_grab_server_request_t;

typedef struct xcb_ungrab_server_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_ungrab_server_request_t;

typedef struct xcb_query_pointer_cookie_t {
  unsigned int sequence;
} xcb_query_pointer_cookie_t;

typedef struct xcb_query_pointer_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_query_pointer_request_t;

typedef struct xcb_query_pointer_reply_t {
  uint8_t response_type;
  uint8_t same_screen;
  uint16_t sequence;
  uint32_t length;
  xcb_window_t root;
  xcb_window_t child;
  int16_t root_x;
  int16_t root_y;
  int16_t win_x;
  int16_t win_y;
  uint16_t mask;
  uint8_t pad0[2];
} xcb_query_pointer_reply_t;

typedef struct xcb_timecoord_t {
  xcb_timestamp_t time;
  int16_t x;
  int16_t y;
} xcb_timecoord_t;

typedef struct xcb_timecoord_iterator_t {
  xcb_timecoord_t *data;
  int rem;
  int index;
} xcb_timecoord_iterator_t;

typedef struct xcb_get_motion_events_cookie_t {
  unsigned int sequence;
} xcb_get_motion_events_cookie_t;

typedef struct xcb_get_motion_events_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
  xcb_timestamp_t start;
  xcb_timestamp_t stop;
} xcb_get_motion_events_request_t;

typedef struct xcb_get_motion_events_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint32_t events_len;
  uint8_t pad1[20];
} xcb_get_motion_events_reply_t;

typedef struct xcb_translate_coordinates_cookie_t {
  unsigned int sequence;
} xcb_translate_coordinates_cookie_t;

typedef struct xcb_translate_coordinates_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t src_window;
  xcb_window_t dst_window;
  int16_t src_x;
  int16_t src_y;
} xcb_translate_coordinates_request_t;

typedef struct xcb_translate_coordinates_reply_t {
  uint8_t response_type;
  uint8_t same_screen;
  uint16_t sequence;
  uint32_t length;
  xcb_window_t child;
  int16_t dst_x;
  int16_t dst_y;
} xcb_translate_coordinates_reply_t;

typedef struct xcb_warp_pointer_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t src_window;
  xcb_window_t dst_window;
  int16_t src_x;
  int16_t src_y;
  uint16_t src_width;
  uint16_t src_height;
  int16_t dst_x;
  int16_t dst_y;
} xcb_warp_pointer_request_t;

typedef enum xcb_input_focus_t {
  XCB_INPUT_FOCUS_NONE = 0,

  XCB_INPUT_FOCUS_POINTER_ROOT = 1,

  XCB_INPUT_FOCUS_PARENT = 2,

  XCB_INPUT_FOCUS_FOLLOW_KEYBOARD = 3

} xcb_input_focus_t;

typedef struct xcb_set_input_focus_request_t {
  uint8_t major_opcode;
  uint8_t revert_to;
  uint16_t length;
  xcb_window_t focus;
  xcb_timestamp_t time;
} xcb_set_input_focus_request_t;

typedef struct xcb_get_input_focus_cookie_t {
  unsigned int sequence;
} xcb_get_input_focus_cookie_t;

typedef struct xcb_get_input_focus_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_get_input_focus_request_t;

typedef struct xcb_get_input_focus_reply_t {
  uint8_t response_type;
  uint8_t revert_to;
  uint16_t sequence;
  uint32_t length;
  xcb_window_t focus;
} xcb_get_input_focus_reply_t;

typedef struct xcb_query_keymap_cookie_t {
  unsigned int sequence;
} xcb_query_keymap_cookie_t;

typedef struct xcb_query_keymap_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_query_keymap_request_t;

typedef struct xcb_query_keymap_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint8_t keys[32];
} xcb_query_keymap_reply_t;

typedef struct xcb_open_font_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_font_t fid;
  uint16_t name_len;
  uint8_t pad1[2];
} xcb_open_font_request_t;

typedef struct xcb_close_font_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_font_t font;
} xcb_close_font_request_t;

typedef enum xcb_font_draw_t {
  XCB_FONT_DRAW_LEFT_TO_RIGHT = 0,
  XCB_FONT_DRAW_RIGHT_TO_LEFT = 1
} xcb_font_draw_t;

typedef struct xcb_fontprop_t {
  xcb_atom_t name;
  uint32_t value;
} xcb_fontprop_t;

typedef struct xcb_fontprop_iterator_t {
  xcb_fontprop_t *data;
  int rem;
  int index;
} xcb_fontprop_iterator_t;

typedef struct xcb_charinfo_t {
  int16_t left_side_bearing;
  int16_t right_side_bearing;
  int16_t character_width;
  int16_t ascent;
  int16_t descent;
  uint16_t attributes;
} xcb_charinfo_t;

typedef struct xcb_charinfo_iterator_t {
  xcb_charinfo_t *data;
  int rem;
  int index;
} xcb_charinfo_iterator_t;

typedef struct xcb_query_font_cookie_t {
  unsigned int sequence;
} xcb_query_font_cookie_t;

typedef struct xcb_query_font_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_fontable_t font;
} xcb_query_font_request_t;

typedef struct xcb_query_font_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  xcb_charinfo_t min_bounds;
  uint8_t pad1[4];
  xcb_charinfo_t max_bounds;
  uint8_t pad2[4];
  uint16_t min_char_or_byte2;
  uint16_t max_char_or_byte2;
  uint16_t default_char;
  uint16_t properties_len;
  uint8_t draw_direction;
  uint8_t min_byte1;
  uint8_t max_byte1;
  uint8_t all_chars_exist;
  int16_t font_ascent;
  int16_t font_descent;
  uint32_t char_infos_len;
} xcb_query_font_reply_t;

typedef struct xcb_query_text_extents_cookie_t {
  unsigned int sequence;
} xcb_query_text_extents_cookie_t;

typedef struct xcb_query_text_extents_request_t {
  uint8_t major_opcode;
  uint8_t odd_length;
  uint16_t length;
  xcb_fontable_t font;
} xcb_query_text_extents_request_t;

typedef struct xcb_query_text_extents_reply_t {
  uint8_t response_type;
  uint8_t draw_direction;
  uint16_t sequence;
  uint32_t length;
  int16_t font_ascent;
  int16_t font_descent;
  int16_t overall_ascent;
  int16_t overall_descent;
  int32_t overall_width;
  int32_t overall_left;
  int32_t overall_right;
} xcb_query_text_extents_reply_t;

typedef struct xcb_str_t {
  uint8_t name_len;
} xcb_str_t;

typedef struct xcb_str_iterator_t {
  xcb_str_t *data;
  int rem;
  int index;
} xcb_str_iterator_t;

typedef struct xcb_list_fonts_cookie_t {
  unsigned int sequence;
} xcb_list_fonts_cookie_t;

typedef struct xcb_list_fonts_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  uint16_t max_names;
  uint16_t pattern_len;
} xcb_list_fonts_request_t;

typedef struct xcb_list_fonts_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t names_len;
  uint8_t pad1[22];
} xcb_list_fonts_reply_t;

typedef struct xcb_list_fonts_with_info_cookie_t {
  unsigned int sequence;
} xcb_list_fonts_with_info_cookie_t;

typedef struct xcb_list_fonts_with_info_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  uint16_t max_names;
  uint16_t pattern_len;
} xcb_list_fonts_with_info_request_t;

typedef struct xcb_list_fonts_with_info_reply_t {
  uint8_t response_type;
  uint8_t name_len;
  uint16_t sequence;
  uint32_t length;
  xcb_charinfo_t min_bounds;
  uint8_t pad0[4];
  xcb_charinfo_t max_bounds;
  uint8_t pad1[4];
  uint16_t min_char_or_byte2;
  uint16_t max_char_or_byte2;
  uint16_t default_char;
  uint16_t properties_len;
  uint8_t draw_direction;
  uint8_t min_byte1;
  uint8_t max_byte1;
  uint8_t all_chars_exist;
  int16_t font_ascent;
  int16_t font_descent;
  uint32_t replies_hint;
} xcb_list_fonts_with_info_reply_t;

typedef struct xcb_set_font_path_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  uint16_t font_qty;
  uint8_t pad1[2];
} xcb_set_font_path_request_t;

typedef struct xcb_get_font_path_cookie_t {
  unsigned int sequence;
} xcb_get_font_path_cookie_t;

typedef struct xcb_get_font_path_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_get_font_path_request_t;

typedef struct xcb_get_font_path_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t path_len;
  uint8_t pad1[22];
} xcb_get_font_path_reply_t;

typedef struct xcb_create_pixmap_request_t {
  uint8_t major_opcode;
  uint8_t depth;
  uint16_t length;
  xcb_pixmap_t pid;
  xcb_drawable_t drawable;
  uint16_t width;
  uint16_t height;
} xcb_create_pixmap_request_t;

typedef struct xcb_free_pixmap_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_pixmap_t pixmap;
} xcb_free_pixmap_request_t;

typedef enum xcb_gc_t {
  XCB_GC_FUNCTION = 1,

  XCB_GC_PLANE_MASK = 2,

  XCB_GC_FOREGROUND = 4,

  XCB_GC_BACKGROUND = 8,

  XCB_GC_LINE_WIDTH = 16,

  XCB_GC_LINE_STYLE = 32,
# 3053 "/usr/include/xcb/xproto.h" 3 4
  XCB_GC_CAP_STYLE = 64,
# 3065 "/usr/include/xcb/xproto.h" 3 4
  XCB_GC_JOIN_STYLE = 128,

  XCB_GC_FILL_STYLE = 256,
# 3091 "/usr/include/xcb/xproto.h" 3 4
  XCB_GC_FILL_RULE = 512,

  XCB_GC_TILE = 1024,
# 3108 "/usr/include/xcb/xproto.h" 3 4
  XCB_GC_STIPPLE = 2048,
# 3122 "/usr/include/xcb/xproto.h" 3 4
  XCB_GC_TILE_STIPPLE_ORIGIN_X = 4096,

  XCB_GC_TILE_STIPPLE_ORIGIN_Y = 8192,

  XCB_GC_FONT = 16384,

  XCB_GC_SUBWINDOW_MODE = 32768,
# 3140 "/usr/include/xcb/xproto.h" 3 4
  XCB_GC_GRAPHICS_EXPOSURES = 65536,

  XCB_GC_CLIP_ORIGIN_X = 131072,

  XCB_GC_CLIP_ORIGIN_Y = 262144,

  XCB_GC_CLIP_MASK = 524288,
# 3160 "/usr/include/xcb/xproto.h" 3 4
  XCB_GC_DASH_OFFSET = 1048576,

  XCB_GC_DASH_LIST = 2097152,

  XCB_GC_ARC_MODE = 4194304

} xcb_gc_t;

typedef enum xcb_gx_t {
  XCB_GX_CLEAR = 0,
  XCB_GX_AND = 1,
  XCB_GX_AND_REVERSE = 2,
  XCB_GX_COPY = 3,
  XCB_GX_AND_INVERTED = 4,
  XCB_GX_NOOP = 5,
  XCB_GX_XOR = 6,
  XCB_GX_OR = 7,
  XCB_GX_NOR = 8,
  XCB_GX_EQUIV = 9,
  XCB_GX_INVERT = 10,
  XCB_GX_OR_REVERSE = 11,
  XCB_GX_COPY_INVERTED = 12,
  XCB_GX_OR_INVERTED = 13,
  XCB_GX_NAND = 14,
  XCB_GX_SET = 15
} xcb_gx_t;

typedef enum xcb_line_style_t {
  XCB_LINE_STYLE_SOLID = 0,
  XCB_LINE_STYLE_ON_OFF_DASH = 1,
  XCB_LINE_STYLE_DOUBLE_DASH = 2
} xcb_line_style_t;

typedef enum xcb_cap_style_t {
  XCB_CAP_STYLE_NOT_LAST = 0,
  XCB_CAP_STYLE_BUTT = 1,
  XCB_CAP_STYLE_ROUND = 2,
  XCB_CAP_STYLE_PROJECTING = 3
} xcb_cap_style_t;

typedef enum xcb_join_style_t {
  XCB_JOIN_STYLE_MITER = 0,
  XCB_JOIN_STYLE_ROUND = 1,
  XCB_JOIN_STYLE_BEVEL = 2
} xcb_join_style_t;

typedef enum xcb_fill_style_t {
  XCB_FILL_STYLE_SOLID = 0,
  XCB_FILL_STYLE_TILED = 1,
  XCB_FILL_STYLE_STIPPLED = 2,
  XCB_FILL_STYLE_OPAQUE_STIPPLED = 3
} xcb_fill_style_t;

typedef enum xcb_fill_rule_t {
  XCB_FILL_RULE_EVEN_ODD = 0,
  XCB_FILL_RULE_WINDING = 1
} xcb_fill_rule_t;

typedef enum xcb_subwindow_mode_t {
  XCB_SUBWINDOW_MODE_CLIP_BY_CHILDREN = 0,
  XCB_SUBWINDOW_MODE_INCLUDE_INFERIORS = 1
} xcb_subwindow_mode_t;

typedef enum xcb_arc_mode_t {
  XCB_ARC_MODE_CHORD = 0,
  XCB_ARC_MODE_PIE_SLICE = 1
} xcb_arc_mode_t;

typedef struct xcb_create_gc_value_list_t {
  uint32_t function;
  uint32_t plane_mask;
  uint32_t foreground;
  uint32_t background;
  uint32_t line_width;
  uint32_t line_style;
  uint32_t cap_style;
  uint32_t join_style;
  uint32_t fill_style;
  uint32_t fill_rule;
  xcb_pixmap_t tile;
  xcb_pixmap_t stipple;
  int32_t tile_stipple_x_origin;
  int32_t tile_stipple_y_origin;
  xcb_font_t font;
  uint32_t subwindow_mode;
  xcb_bool32_t graphics_exposures;
  int32_t clip_x_origin;
  int32_t clip_y_origin;
  xcb_pixmap_t clip_mask;
  uint32_t dash_offset;
  uint32_t dashes;
  uint32_t arc_mode;
} xcb_create_gc_value_list_t;

typedef struct xcb_create_gc_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_gcontext_t cid;
  xcb_drawable_t drawable;
  uint32_t value_mask;
} xcb_create_gc_request_t;

typedef struct xcb_change_gc_value_list_t {
  uint32_t function;
  uint32_t plane_mask;
  uint32_t foreground;
  uint32_t background;
  uint32_t line_width;
  uint32_t line_style;
  uint32_t cap_style;
  uint32_t join_style;
  uint32_t fill_style;
  uint32_t fill_rule;
  xcb_pixmap_t tile;
  xcb_pixmap_t stipple;
  int32_t tile_stipple_x_origin;
  int32_t tile_stipple_y_origin;
  xcb_font_t font;
  uint32_t subwindow_mode;
  xcb_bool32_t graphics_exposures;
  int32_t clip_x_origin;
  int32_t clip_y_origin;
  xcb_pixmap_t clip_mask;
  uint32_t dash_offset;
  uint32_t dashes;
  uint32_t arc_mode;
} xcb_change_gc_value_list_t;

typedef struct xcb_change_gc_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_gcontext_t gc;
  uint32_t value_mask;
} xcb_change_gc_request_t;

typedef struct xcb_copy_gc_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_gcontext_t src_gc;
  xcb_gcontext_t dst_gc;
  uint32_t value_mask;
} xcb_copy_gc_request_t;

typedef struct xcb_set_dashes_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_gcontext_t gc;
  uint16_t dash_offset;
  uint16_t dashes_len;
} xcb_set_dashes_request_t;

typedef enum xcb_clip_ordering_t {
  XCB_CLIP_ORDERING_UNSORTED = 0,
  XCB_CLIP_ORDERING_Y_SORTED = 1,
  XCB_CLIP_ORDERING_YX_SORTED = 2,
  XCB_CLIP_ORDERING_YX_BANDED = 3
} xcb_clip_ordering_t;

typedef struct xcb_set_clip_rectangles_request_t {
  uint8_t major_opcode;
  uint8_t ordering;
  uint16_t length;
  xcb_gcontext_t gc;
  int16_t clip_x_origin;
  int16_t clip_y_origin;
} xcb_set_clip_rectangles_request_t;

typedef struct xcb_free_gc_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_gcontext_t gc;
} xcb_free_gc_request_t;

typedef struct xcb_clear_area_request_t {
  uint8_t major_opcode;
  uint8_t exposures;
  uint16_t length;
  xcb_window_t window;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
} xcb_clear_area_request_t;

typedef struct xcb_copy_area_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t src_drawable;
  xcb_drawable_t dst_drawable;
  xcb_gcontext_t gc;
  int16_t src_x;
  int16_t src_y;
  int16_t dst_x;
  int16_t dst_y;
  uint16_t width;
  uint16_t height;
} xcb_copy_area_request_t;

typedef struct xcb_copy_plane_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t src_drawable;
  xcb_drawable_t dst_drawable;
  xcb_gcontext_t gc;
  int16_t src_x;
  int16_t src_y;
  int16_t dst_x;
  int16_t dst_y;
  uint16_t width;
  uint16_t height;
  uint32_t bit_plane;
} xcb_copy_plane_request_t;

typedef enum xcb_coord_mode_t {
  XCB_COORD_MODE_ORIGIN = 0,

  XCB_COORD_MODE_PREVIOUS = 1

} xcb_coord_mode_t;

typedef struct xcb_poly_point_request_t {
  uint8_t major_opcode;
  uint8_t coordinate_mode;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
} xcb_poly_point_request_t;

typedef struct xcb_poly_line_request_t {
  uint8_t major_opcode;
  uint8_t coordinate_mode;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
} xcb_poly_line_request_t;

typedef struct xcb_segment_t {
  int16_t x1;
  int16_t y1;
  int16_t x2;
  int16_t y2;
} xcb_segment_t;

typedef struct xcb_segment_iterator_t {
  xcb_segment_t *data;
  int rem;
  int index;
} xcb_segment_iterator_t;

typedef struct xcb_poly_segment_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
} xcb_poly_segment_request_t;

typedef struct xcb_poly_rectangle_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
} xcb_poly_rectangle_request_t;

typedef struct xcb_poly_arc_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
} xcb_poly_arc_request_t;

typedef enum xcb_poly_shape_t {
  XCB_POLY_SHAPE_COMPLEX = 0,
  XCB_POLY_SHAPE_NONCONVEX = 1,
  XCB_POLY_SHAPE_CONVEX = 2
} xcb_poly_shape_t;

typedef struct xcb_fill_poly_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
  uint8_t shape;
  uint8_t coordinate_mode;
  uint8_t pad1[2];
} xcb_fill_poly_request_t;

typedef struct xcb_poly_fill_rectangle_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
} xcb_poly_fill_rectangle_request_t;

typedef struct xcb_poly_fill_arc_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
} xcb_poly_fill_arc_request_t;

typedef enum xcb_image_format_t {
  XCB_IMAGE_FORMAT_XY_BITMAP = 0,
  XCB_IMAGE_FORMAT_XY_PIXMAP = 1,
  XCB_IMAGE_FORMAT_Z_PIXMAP = 2
} xcb_image_format_t;

typedef struct xcb_put_image_request_t {
  uint8_t major_opcode;
  uint8_t format;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
  uint16_t width;
  uint16_t height;
  int16_t dst_x;
  int16_t dst_y;
  uint8_t left_pad;
  uint8_t depth;
  uint8_t pad0[2];
} xcb_put_image_request_t;

typedef struct xcb_get_image_cookie_t {
  unsigned int sequence;
} xcb_get_image_cookie_t;

typedef struct xcb_get_image_request_t {
  uint8_t major_opcode;
  uint8_t format;
  uint16_t length;
  xcb_drawable_t drawable;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  uint32_t plane_mask;
} xcb_get_image_request_t;

typedef struct xcb_get_image_reply_t {
  uint8_t response_type;
  uint8_t depth;
  uint16_t sequence;
  uint32_t length;
  xcb_visualid_t visual;
  uint8_t pad0[20];
} xcb_get_image_reply_t;

typedef struct xcb_poly_text_8_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
  int16_t x;
  int16_t y;
} xcb_poly_text_8_request_t;

typedef struct xcb_poly_text_16_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
  int16_t x;
  int16_t y;
} xcb_poly_text_16_request_t;

typedef struct xcb_image_text_8_request_t {
  uint8_t major_opcode;
  uint8_t string_len;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
  int16_t x;
  int16_t y;
} xcb_image_text_8_request_t;

typedef struct xcb_image_text_16_request_t {
  uint8_t major_opcode;
  uint8_t string_len;
  uint16_t length;
  xcb_drawable_t drawable;
  xcb_gcontext_t gc;
  int16_t x;
  int16_t y;
} xcb_image_text_16_request_t;

typedef enum xcb_colormap_alloc_t {
  XCB_COLORMAP_ALLOC_NONE = 0,
  XCB_COLORMAP_ALLOC_ALL = 1
} xcb_colormap_alloc_t;

typedef struct xcb_create_colormap_request_t {
  uint8_t major_opcode;
  uint8_t alloc;
  uint16_t length;
  xcb_colormap_t mid;
  xcb_window_t window;
  xcb_visualid_t visual;
} xcb_create_colormap_request_t;

typedef struct xcb_free_colormap_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
} xcb_free_colormap_request_t;

typedef struct xcb_copy_colormap_and_free_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t mid;
  xcb_colormap_t src_cmap;
} xcb_copy_colormap_and_free_request_t;

typedef struct xcb_install_colormap_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
} xcb_install_colormap_request_t;

typedef struct xcb_uninstall_colormap_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
} xcb_uninstall_colormap_request_t;

typedef struct xcb_list_installed_colormaps_cookie_t {
  unsigned int sequence;
} xcb_list_installed_colormaps_cookie_t;

typedef struct xcb_list_installed_colormaps_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
} xcb_list_installed_colormaps_request_t;

typedef struct xcb_list_installed_colormaps_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t cmaps_len;
  uint8_t pad1[22];
} xcb_list_installed_colormaps_reply_t;

typedef struct xcb_alloc_color_cookie_t {
  unsigned int sequence;
} xcb_alloc_color_cookie_t;

typedef struct xcb_alloc_color_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  uint8_t pad1[2];
} xcb_alloc_color_request_t;

typedef struct xcb_alloc_color_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  uint8_t pad1[2];
  uint32_t pixel;
} xcb_alloc_color_reply_t;

typedef struct xcb_alloc_named_color_cookie_t {
  unsigned int sequence;
} xcb_alloc_named_color_cookie_t;

typedef struct xcb_alloc_named_color_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
  uint16_t name_len;
  uint8_t pad1[2];
} xcb_alloc_named_color_request_t;

typedef struct xcb_alloc_named_color_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint32_t pixel;
  uint16_t exact_red;
  uint16_t exact_green;
  uint16_t exact_blue;
  uint16_t visual_red;
  uint16_t visual_green;
  uint16_t visual_blue;
} xcb_alloc_named_color_reply_t;

typedef struct xcb_alloc_color_cells_cookie_t {
  unsigned int sequence;
} xcb_alloc_color_cells_cookie_t;

typedef struct xcb_alloc_color_cells_request_t {
  uint8_t major_opcode;
  uint8_t contiguous;
  uint16_t length;
  xcb_colormap_t cmap;
  uint16_t colors;
  uint16_t planes;
} xcb_alloc_color_cells_request_t;

typedef struct xcb_alloc_color_cells_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t pixels_len;
  uint16_t masks_len;
  uint8_t pad1[20];
} xcb_alloc_color_cells_reply_t;

typedef struct xcb_alloc_color_planes_cookie_t {
  unsigned int sequence;
} xcb_alloc_color_planes_cookie_t;

typedef struct xcb_alloc_color_planes_request_t {
  uint8_t major_opcode;
  uint8_t contiguous;
  uint16_t length;
  xcb_colormap_t cmap;
  uint16_t colors;
  uint16_t reds;
  uint16_t greens;
  uint16_t blues;
} xcb_alloc_color_planes_request_t;

typedef struct xcb_alloc_color_planes_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t pixels_len;
  uint8_t pad1[2];
  uint32_t red_mask;
  uint32_t green_mask;
  uint32_t blue_mask;
  uint8_t pad2[8];
} xcb_alloc_color_planes_reply_t;

typedef struct xcb_free_colors_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
  uint32_t plane_mask;
} xcb_free_colors_request_t;

typedef enum xcb_color_flag_t {
  XCB_COLOR_FLAG_RED = 1,
  XCB_COLOR_FLAG_GREEN = 2,
  XCB_COLOR_FLAG_BLUE = 4
} xcb_color_flag_t;

typedef struct xcb_coloritem_t {
  uint32_t pixel;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  uint8_t flags;
  uint8_t pad0;
} xcb_coloritem_t;

typedef struct xcb_coloritem_iterator_t {
  xcb_coloritem_t *data;
  int rem;
  int index;
} xcb_coloritem_iterator_t;

typedef struct xcb_store_colors_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
} xcb_store_colors_request_t;

typedef struct xcb_store_named_color_request_t {
  uint8_t major_opcode;
  uint8_t flags;
  uint16_t length;
  xcb_colormap_t cmap;
  uint32_t pixel;
  uint16_t name_len;
  uint8_t pad0[2];
} xcb_store_named_color_request_t;

typedef struct xcb_rgb_t {
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  uint8_t pad0[2];
} xcb_rgb_t;

typedef struct xcb_rgb_iterator_t {
  xcb_rgb_t *data;
  int rem;
  int index;
} xcb_rgb_iterator_t;

typedef struct xcb_query_colors_cookie_t {
  unsigned int sequence;
} xcb_query_colors_cookie_t;

typedef struct xcb_query_colors_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
} xcb_query_colors_request_t;

typedef struct xcb_query_colors_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t colors_len;
  uint8_t pad1[22];
} xcb_query_colors_reply_t;

typedef struct xcb_lookup_color_cookie_t {
  unsigned int sequence;
} xcb_lookup_color_cookie_t;

typedef struct xcb_lookup_color_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_colormap_t cmap;
  uint16_t name_len;
  uint8_t pad1[2];
} xcb_lookup_color_request_t;

typedef struct xcb_lookup_color_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t exact_red;
  uint16_t exact_green;
  uint16_t exact_blue;
  uint16_t visual_red;
  uint16_t visual_green;
  uint16_t visual_blue;
} xcb_lookup_color_reply_t;

typedef enum xcb_pixmap_enum_t { XCB_PIXMAP_NONE = 0 } xcb_pixmap_enum_t;

typedef struct xcb_create_cursor_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_cursor_t cid;
  xcb_pixmap_t source;
  xcb_pixmap_t mask;
  uint16_t fore_red;
  uint16_t fore_green;
  uint16_t fore_blue;
  uint16_t back_red;
  uint16_t back_green;
  uint16_t back_blue;
  uint16_t x;
  uint16_t y;
} xcb_create_cursor_request_t;

typedef enum xcb_font_enum_t { XCB_FONT_NONE = 0 } xcb_font_enum_t;

typedef struct xcb_create_glyph_cursor_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_cursor_t cid;
  xcb_font_t source_font;
  xcb_font_t mask_font;
  uint16_t source_char;
  uint16_t mask_char;
  uint16_t fore_red;
  uint16_t fore_green;
  uint16_t fore_blue;
  uint16_t back_red;
  uint16_t back_green;
  uint16_t back_blue;
} xcb_create_glyph_cursor_request_t;

typedef struct xcb_free_cursor_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_cursor_t cursor;
} xcb_free_cursor_request_t;

typedef struct xcb_recolor_cursor_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_cursor_t cursor;
  uint16_t fore_red;
  uint16_t fore_green;
  uint16_t fore_blue;
  uint16_t back_red;
  uint16_t back_green;
  uint16_t back_blue;
} xcb_recolor_cursor_request_t;

typedef enum xcb_query_shape_of_t {
  XCB_QUERY_SHAPE_OF_LARGEST_CURSOR = 0,
  XCB_QUERY_SHAPE_OF_FASTEST_TILE = 1,
  XCB_QUERY_SHAPE_OF_FASTEST_STIPPLE = 2
} xcb_query_shape_of_t;

typedef struct xcb_query_best_size_cookie_t {
  unsigned int sequence;
} xcb_query_best_size_cookie_t;

typedef struct xcb_query_best_size_request_t {
  uint8_t major_opcode;
  uint8_t _class;
  uint16_t length;
  xcb_drawable_t drawable;
  uint16_t width;
  uint16_t height;
} xcb_query_best_size_request_t;

typedef struct xcb_query_best_size_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t width;
  uint16_t height;
} xcb_query_best_size_reply_t;

typedef struct xcb_query_extension_cookie_t {
  unsigned int sequence;
} xcb_query_extension_cookie_t;

typedef struct xcb_query_extension_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  uint16_t name_len;
  uint8_t pad1[2];
} xcb_query_extension_request_t;

typedef struct xcb_query_extension_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint8_t present;
  uint8_t major_opcode;
  uint8_t first_event;
  uint8_t first_error;
} xcb_query_extension_reply_t;

typedef struct xcb_list_extensions_cookie_t {
  unsigned int sequence;
} xcb_list_extensions_cookie_t;

typedef struct xcb_list_extensions_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_list_extensions_request_t;

typedef struct xcb_list_extensions_reply_t {
  uint8_t response_type;
  uint8_t names_len;
  uint16_t sequence;
  uint32_t length;
  uint8_t pad0[24];
} xcb_list_extensions_reply_t;

typedef struct xcb_change_keyboard_mapping_request_t {
  uint8_t major_opcode;
  uint8_t keycode_count;
  uint16_t length;
  xcb_keycode_t first_keycode;
  uint8_t keysyms_per_keycode;
  uint8_t pad0[2];
} xcb_change_keyboard_mapping_request_t;

typedef struct xcb_get_keyboard_mapping_cookie_t {
  unsigned int sequence;
} xcb_get_keyboard_mapping_cookie_t;

typedef struct xcb_get_keyboard_mapping_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_keycode_t first_keycode;
  uint8_t count;
} xcb_get_keyboard_mapping_request_t;

typedef struct xcb_get_keyboard_mapping_reply_t {
  uint8_t response_type;
  uint8_t keysyms_per_keycode;
  uint16_t sequence;
  uint32_t length;
  uint8_t pad0[24];
} xcb_get_keyboard_mapping_reply_t;

typedef enum xcb_kb_t {
  XCB_KB_KEY_CLICK_PERCENT = 1,
  XCB_KB_BELL_PERCENT = 2,
  XCB_KB_BELL_PITCH = 4,
  XCB_KB_BELL_DURATION = 8,
  XCB_KB_LED = 16,
  XCB_KB_LED_MODE = 32,
  XCB_KB_KEY = 64,
  XCB_KB_AUTO_REPEAT_MODE = 128
} xcb_kb_t;

typedef enum xcb_led_mode_t {
  XCB_LED_MODE_OFF = 0,
  XCB_LED_MODE_ON = 1
} xcb_led_mode_t;

typedef enum xcb_auto_repeat_mode_t {
  XCB_AUTO_REPEAT_MODE_OFF = 0,
  XCB_AUTO_REPEAT_MODE_ON = 1,
  XCB_AUTO_REPEAT_MODE_DEFAULT = 2
} xcb_auto_repeat_mode_t;

typedef struct xcb_change_keyboard_control_value_list_t {
  int32_t key_click_percent;
  int32_t bell_percent;
  int32_t bell_pitch;
  int32_t bell_duration;
  uint32_t led;
  uint32_t led_mode;
  xcb_keycode32_t key;
  uint32_t auto_repeat_mode;
} xcb_change_keyboard_control_value_list_t;

typedef struct xcb_change_keyboard_control_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  uint32_t value_mask;
} xcb_change_keyboard_control_request_t;

typedef struct xcb_get_keyboard_control_cookie_t {
  unsigned int sequence;
} xcb_get_keyboard_control_cookie_t;

typedef struct xcb_get_keyboard_control_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_get_keyboard_control_request_t;

typedef struct xcb_get_keyboard_control_reply_t {
  uint8_t response_type;
  uint8_t global_auto_repeat;
  uint16_t sequence;
  uint32_t length;
  uint32_t led_mask;
  uint8_t key_click_percent;
  uint8_t bell_percent;
  uint16_t bell_pitch;
  uint16_t bell_duration;
  uint8_t pad0[2];
  uint8_t auto_repeats[32];
} xcb_get_keyboard_control_reply_t;

typedef struct xcb_bell_request_t {
  uint8_t major_opcode;
  int8_t percent;
  uint16_t length;
} xcb_bell_request_t;

typedef struct xcb_change_pointer_control_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  int16_t acceleration_numerator;
  int16_t acceleration_denominator;
  int16_t threshold;
  uint8_t do_acceleration;
  uint8_t do_threshold;
} xcb_change_pointer_control_request_t;

typedef struct xcb_get_pointer_control_cookie_t {
  unsigned int sequence;
} xcb_get_pointer_control_cookie_t;

typedef struct xcb_get_pointer_control_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_get_pointer_control_request_t;

typedef struct xcb_get_pointer_control_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t acceleration_numerator;
  uint16_t acceleration_denominator;
  uint16_t threshold;
  uint8_t pad1[18];
} xcb_get_pointer_control_reply_t;

typedef enum xcb_blanking_t {
  XCB_BLANKING_NOT_PREFERRED = 0,
  XCB_BLANKING_PREFERRED = 1,
  XCB_BLANKING_DEFAULT = 2
} xcb_blanking_t;

typedef enum xcb_exposures_t {
  XCB_EXPOSURES_NOT_ALLOWED = 0,
  XCB_EXPOSURES_ALLOWED = 1,
  XCB_EXPOSURES_DEFAULT = 2
} xcb_exposures_t;

typedef struct xcb_set_screen_saver_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  int16_t timeout;
  int16_t interval;
  uint8_t prefer_blanking;
  uint8_t allow_exposures;
} xcb_set_screen_saver_request_t;

typedef struct xcb_get_screen_saver_cookie_t {
  unsigned int sequence;
} xcb_get_screen_saver_cookie_t;

typedef struct xcb_get_screen_saver_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_get_screen_saver_request_t;

typedef struct xcb_get_screen_saver_reply_t {
  uint8_t response_type;
  uint8_t pad0;
  uint16_t sequence;
  uint32_t length;
  uint16_t timeout;
  uint16_t interval;
  uint8_t prefer_blanking;
  uint8_t allow_exposures;
  uint8_t pad1[18];
} xcb_get_screen_saver_reply_t;

typedef enum xcb_host_mode_t {
  XCB_HOST_MODE_INSERT = 0,
  XCB_HOST_MODE_DELETE = 1
} xcb_host_mode_t;

typedef enum xcb_family_t {
  XCB_FAMILY_INTERNET = 0,
  XCB_FAMILY_DECNET = 1,
  XCB_FAMILY_CHAOS = 2,
  XCB_FAMILY_SERVER_INTERPRETED = 5,
  XCB_FAMILY_INTERNET_6 = 6
} xcb_family_t;

typedef struct xcb_change_hosts_request_t {
  uint8_t major_opcode;
  uint8_t mode;
  uint16_t length;
  uint8_t family;
  uint8_t pad0;
  uint16_t address_len;
} xcb_change_hosts_request_t;

typedef struct xcb_host_t {
  uint8_t family;
  uint8_t pad0;
  uint16_t address_len;
} xcb_host_t;

typedef struct xcb_host_iterator_t {
  xcb_host_t *data;
  int rem;
  int index;
} xcb_host_iterator_t;

typedef struct xcb_list_hosts_cookie_t {
  unsigned int sequence;
} xcb_list_hosts_cookie_t;

typedef struct xcb_list_hosts_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_list_hosts_request_t;

typedef struct xcb_list_hosts_reply_t {
  uint8_t response_type;
  uint8_t mode;
  uint16_t sequence;
  uint32_t length;
  uint16_t hosts_len;
  uint8_t pad0[22];
} xcb_list_hosts_reply_t;

typedef enum xcb_access_control_t {
  XCB_ACCESS_CONTROL_DISABLE = 0,
  XCB_ACCESS_CONTROL_ENABLE = 1
} xcb_access_control_t;

typedef struct xcb_set_access_control_request_t {
  uint8_t major_opcode;
  uint8_t mode;
  uint16_t length;
} xcb_set_access_control_request_t;

typedef enum xcb_close_down_t {
  XCB_CLOSE_DOWN_DESTROY_ALL = 0,
  XCB_CLOSE_DOWN_RETAIN_PERMANENT = 1,
  XCB_CLOSE_DOWN_RETAIN_TEMPORARY = 2
} xcb_close_down_t;

typedef struct xcb_set_close_down_mode_request_t {
  uint8_t major_opcode;
  uint8_t mode;
  uint16_t length;
} xcb_set_close_down_mode_request_t;

typedef enum xcb_kill_t { XCB_KILL_ALL_TEMPORARY = 0 } xcb_kill_t;

typedef struct xcb_kill_client_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  uint32_t resource;
} xcb_kill_client_request_t;

typedef struct xcb_rotate_properties_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
  xcb_window_t window;
  uint16_t atoms_len;
  int16_t delta;
} xcb_rotate_properties_request_t;

typedef enum xcb_screen_saver_t {
  XCB_SCREEN_SAVER_RESET = 0,
  XCB_SCREEN_SAVER_ACTIVE = 1
} xcb_screen_saver_t;

typedef struct xcb_force_screen_saver_request_t {
  uint8_t major_opcode;
  uint8_t mode;
  uint16_t length;
} xcb_force_screen_saver_request_t;

typedef enum xcb_mapping_status_t {
  XCB_MAPPING_STATUS_SUCCESS = 0,
  XCB_MAPPING_STATUS_BUSY = 1,
  XCB_MAPPING_STATUS_FAILURE = 2
} xcb_mapping_status_t;

typedef struct xcb_set_pointer_mapping_cookie_t {
  unsigned int sequence;
} xcb_set_pointer_mapping_cookie_t;

typedef struct xcb_set_pointer_mapping_request_t {
  uint8_t major_opcode;
  uint8_t map_len;
  uint16_t length;
} xcb_set_pointer_mapping_request_t;

typedef struct xcb_set_pointer_mapping_reply_t {
  uint8_t response_type;
  uint8_t status;
  uint16_t sequence;
  uint32_t length;
} xcb_set_pointer_mapping_reply_t;

typedef struct xcb_get_pointer_mapping_cookie_t {
  unsigned int sequence;
} xcb_get_pointer_mapping_cookie_t;

typedef struct xcb_get_pointer_mapping_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_get_pointer_mapping_request_t;

typedef struct xcb_get_pointer_mapping_reply_t {
  uint8_t response_type;
  uint8_t map_len;
  uint16_t sequence;
  uint32_t length;
  uint8_t pad0[24];
} xcb_get_pointer_mapping_reply_t;

typedef enum xcb_map_index_t {
  XCB_MAP_INDEX_SHIFT = 0,
  XCB_MAP_INDEX_LOCK = 1,
  XCB_MAP_INDEX_CONTROL = 2,
  XCB_MAP_INDEX_1 = 3,
  XCB_MAP_INDEX_2 = 4,
  XCB_MAP_INDEX_3 = 5,
  XCB_MAP_INDEX_4 = 6,
  XCB_MAP_INDEX_5 = 7
} xcb_map_index_t;

typedef struct xcb_set_modifier_mapping_cookie_t {
  unsigned int sequence;
} xcb_set_modifier_mapping_cookie_t;

typedef struct xcb_set_modifier_mapping_request_t {
  uint8_t major_opcode;
  uint8_t keycodes_per_modifier;
  uint16_t length;
} xcb_set_modifier_mapping_request_t;

typedef struct xcb_set_modifier_mapping_reply_t {
  uint8_t response_type;
  uint8_t status;
  uint16_t sequence;
  uint32_t length;
} xcb_set_modifier_mapping_reply_t;

typedef struct xcb_get_modifier_mapping_cookie_t {
  unsigned int sequence;
} xcb_get_modifier_mapping_cookie_t;

typedef struct xcb_get_modifier_mapping_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_get_modifier_mapping_request_t;

typedef struct xcb_get_modifier_mapping_reply_t {
  uint8_t response_type;
  uint8_t keycodes_per_modifier;
  uint16_t sequence;
  uint32_t length;
  uint8_t pad0[24];
} xcb_get_modifier_mapping_reply_t;

typedef struct xcb_no_operation_request_t {
  uint8_t major_opcode;
  uint8_t pad0;
  uint16_t length;
} xcb_no_operation_request_t;
# 4900 "/usr/include/xcb/xproto.h" 3 4
void xcb_char2b_next(xcb_char2b_iterator_t *i);
# 4912 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_char2b_end(xcb_char2b_iterator_t i);
# 4923 "/usr/include/xcb/xproto.h" 3 4
void xcb_window_next(xcb_window_iterator_t *i);
# 4935 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_window_end(xcb_window_iterator_t i);
# 4946 "/usr/include/xcb/xproto.h" 3 4
void xcb_pixmap_next(xcb_pixmap_iterator_t *i);
# 4958 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_pixmap_end(xcb_pixmap_iterator_t i);
# 4969 "/usr/include/xcb/xproto.h" 3 4
void xcb_cursor_next(xcb_cursor_iterator_t *i);
# 4981 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_cursor_end(xcb_cursor_iterator_t i);
# 4992 "/usr/include/xcb/xproto.h" 3 4
void xcb_font_next(xcb_font_iterator_t *i);
# 5004 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_font_end(xcb_font_iterator_t i);
# 5015 "/usr/include/xcb/xproto.h" 3 4
void xcb_gcontext_next(xcb_gcontext_iterator_t *i);
# 5027 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_gcontext_end(xcb_gcontext_iterator_t i);
# 5038 "/usr/include/xcb/xproto.h" 3 4
void xcb_colormap_next(xcb_colormap_iterator_t *i);
# 5050 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_colormap_end(xcb_colormap_iterator_t i);
# 5061 "/usr/include/xcb/xproto.h" 3 4
void xcb_atom_next(xcb_atom_iterator_t *i);
# 5073 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_atom_end(xcb_atom_iterator_t i);
# 5084 "/usr/include/xcb/xproto.h" 3 4
void xcb_drawable_next(xcb_drawable_iterator_t *i);
# 5096 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_drawable_end(xcb_drawable_iterator_t i);
# 5107 "/usr/include/xcb/xproto.h" 3 4
void xcb_fontable_next(xcb_fontable_iterator_t *i);
# 5119 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_fontable_end(xcb_fontable_iterator_t i);
# 5130 "/usr/include/xcb/xproto.h" 3 4
void xcb_bool32_next(xcb_bool32_iterator_t *i);
# 5142 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_bool32_end(xcb_bool32_iterator_t i);
# 5153 "/usr/include/xcb/xproto.h" 3 4
void xcb_visualid_next(xcb_visualid_iterator_t *i);
# 5165 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_visualid_end(xcb_visualid_iterator_t i);
# 5176 "/usr/include/xcb/xproto.h" 3 4
void xcb_timestamp_next(xcb_timestamp_iterator_t *i);
# 5188 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_timestamp_end(xcb_timestamp_iterator_t i);
# 5199 "/usr/include/xcb/xproto.h" 3 4
void xcb_keysym_next(xcb_keysym_iterator_t *i);
# 5211 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_keysym_end(xcb_keysym_iterator_t i);
# 5222 "/usr/include/xcb/xproto.h" 3 4
void xcb_keycode_next(xcb_keycode_iterator_t *i);
# 5234 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_keycode_end(xcb_keycode_iterator_t i);
# 5245 "/usr/include/xcb/xproto.h" 3 4
void xcb_keycode32_next(xcb_keycode32_iterator_t *i);
# 5257 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_keycode32_end(xcb_keycode32_iterator_t i);
# 5268 "/usr/include/xcb/xproto.h" 3 4
void xcb_button_next(xcb_button_iterator_t *i);
# 5280 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_button_end(xcb_button_iterator_t i);
# 5291 "/usr/include/xcb/xproto.h" 3 4
void xcb_point_next(xcb_point_iterator_t *i);
# 5303 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_point_end(xcb_point_iterator_t i);
# 5314 "/usr/include/xcb/xproto.h" 3 4
void xcb_rectangle_next(xcb_rectangle_iterator_t *i);
# 5326 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_rectangle_end(xcb_rectangle_iterator_t i);
# 5337 "/usr/include/xcb/xproto.h" 3 4
void xcb_arc_next(xcb_arc_iterator_t *i);
# 5349 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_arc_end(xcb_arc_iterator_t i);
# 5360 "/usr/include/xcb/xproto.h" 3 4
void xcb_format_next(xcb_format_iterator_t *i);
# 5372 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_format_end(xcb_format_iterator_t i);
# 5383 "/usr/include/xcb/xproto.h" 3 4
void xcb_visualtype_next(xcb_visualtype_iterator_t *i);
# 5395 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_visualtype_end(xcb_visualtype_iterator_t i);

int xcb_depth_sizeof(const void *_buffer);

xcb_visualtype_t *xcb_depth_visuals(const xcb_depth_t *R);

int xcb_depth_visuals_length(const xcb_depth_t *R);

xcb_visualtype_iterator_t xcb_depth_visuals_iterator(const xcb_depth_t *R);
# 5418 "/usr/include/xcb/xproto.h" 3 4
void xcb_depth_next(xcb_depth_iterator_t *i);
# 5430 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_depth_end(xcb_depth_iterator_t i);

int xcb_screen_sizeof(const void *_buffer);

int xcb_screen_allowed_depths_length(const xcb_screen_t *R);

xcb_depth_iterator_t xcb_screen_allowed_depths_iterator(const xcb_screen_t *R);
# 5450 "/usr/include/xcb/xproto.h" 3 4
void xcb_screen_next(xcb_screen_iterator_t *i);
# 5462 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_screen_end(xcb_screen_iterator_t i);

int xcb_setup_request_sizeof(const void *_buffer);

char *
xcb_setup_request_authorization_protocol_name(const xcb_setup_request_t *R);

int xcb_setup_request_authorization_protocol_name_length(
    const xcb_setup_request_t *R);

xcb_generic_iterator_t
xcb_setup_request_authorization_protocol_name_end(const xcb_setup_request_t *R);

char *
xcb_setup_request_authorization_protocol_data(const xcb_setup_request_t *R);

int xcb_setup_request_authorization_protocol_data_length(
    const xcb_setup_request_t *R);

xcb_generic_iterator_t
xcb_setup_request_authorization_protocol_data_end(const xcb_setup_request_t *R);
# 5494 "/usr/include/xcb/xproto.h" 3 4
void xcb_setup_request_next(xcb_setup_request_iterator_t *i);
# 5506 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_setup_request_end(xcb_setup_request_iterator_t i);

int xcb_setup_failed_sizeof(const void *_buffer);

char *xcb_setup_failed_reason(const xcb_setup_failed_t *R);

int xcb_setup_failed_reason_length(const xcb_setup_failed_t *R);

xcb_generic_iterator_t xcb_setup_failed_reason_end(const xcb_setup_failed_t *R);
# 5529 "/usr/include/xcb/xproto.h" 3 4
void xcb_setup_failed_next(xcb_setup_failed_iterator_t *i);
# 5541 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_setup_failed_end(xcb_setup_failed_iterator_t i);

int xcb_setup_authenticate_sizeof(const void *_buffer);

char *xcb_setup_authenticate_reason(const xcb_setup_authenticate_t *R);

int xcb_setup_authenticate_reason_length(const xcb_setup_authenticate_t *R);

xcb_generic_iterator_t
xcb_setup_authenticate_reason_end(const xcb_setup_authenticate_t *R);
# 5564 "/usr/include/xcb/xproto.h" 3 4
void xcb_setup_authenticate_next(xcb_setup_authenticate_iterator_t *i);
# 5576 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t
xcb_setup_authenticate_end(xcb_setup_authenticate_iterator_t i);

int xcb_setup_sizeof(const void *_buffer);

char *xcb_setup_vendor(const xcb_setup_t *R);

int xcb_setup_vendor_length(const xcb_setup_t *R);

xcb_generic_iterator_t xcb_setup_vendor_end(const xcb_setup_t *R);

xcb_format_t *xcb_setup_pixmap_formats(const xcb_setup_t *R);

int xcb_setup_pixmap_formats_length(const xcb_setup_t *R);

xcb_format_iterator_t xcb_setup_pixmap_formats_iterator(const xcb_setup_t *R);

int xcb_setup_roots_length(const xcb_setup_t *R);

xcb_screen_iterator_t xcb_setup_roots_iterator(const xcb_setup_t *R);
# 5614 "/usr/include/xcb/xproto.h" 3 4
void xcb_setup_next(xcb_setup_iterator_t *i);
# 5626 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_setup_end(xcb_setup_iterator_t i);
# 5637 "/usr/include/xcb/xproto.h" 3 4
void xcb_client_message_data_next(xcb_client_message_data_iterator_t *i);
# 5649 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t
xcb_client_message_data_end(xcb_client_message_data_iterator_t i);

int xcb_create_window_value_list_serialize(
    void **_buffer, uint32_t value_mask,
    const xcb_create_window_value_list_t *_aux);

int xcb_create_window_value_list_unpack(const void *_buffer,
                                        uint32_t value_mask,
                                        xcb_create_window_value_list_t *_aux);

int xcb_create_window_value_list_sizeof(const void *_buffer,
                                        uint32_t value_mask);

int xcb_create_window_sizeof(const void *_buffer);
# 5715 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_window_checked(
    xcb_connection_t *c, uint8_t depth, xcb_window_t wid, xcb_window_t parent,
    int16_t x, int16_t y, uint16_t width, uint16_t height,
    uint16_t border_width, uint16_t _class, xcb_visualid_t visual,
    uint32_t value_mask, const void *value_list);
# 5773 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_window(xcb_connection_t *c, uint8_t depth,
                                    xcb_window_t wid, xcb_window_t parent,
                                    int16_t x, int16_t y, uint16_t width,
                                    uint16_t height, uint16_t border_width,
                                    uint16_t _class, xcb_visualid_t visual,
                                    uint32_t value_mask,
                                    const void *value_list);
# 5834 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_window_aux_checked(
    xcb_connection_t *c, uint8_t depth, xcb_window_t wid, xcb_window_t parent,
    int16_t x, int16_t y, uint16_t width, uint16_t height,
    uint16_t border_width, uint16_t _class, xcb_visualid_t visual,
    uint32_t value_mask, const xcb_create_window_value_list_t *value_list);
# 5892 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_create_window_aux(xcb_connection_t *c, uint8_t depth, xcb_window_t wid,
                      xcb_window_t parent, int16_t x, int16_t y, uint16_t width,
                      uint16_t height, uint16_t border_width, uint16_t _class,
                      xcb_visualid_t visual, uint32_t value_mask,
                      const xcb_create_window_value_list_t *value_list);

void *xcb_create_window_value_list(const xcb_create_window_request_t *R);

int xcb_change_window_attributes_value_list_serialize(
    void **_buffer, uint32_t value_mask,
    const xcb_change_window_attributes_value_list_t *_aux);

int xcb_change_window_attributes_value_list_unpack(
    const void *_buffer, uint32_t value_mask,
    xcb_change_window_attributes_value_list_t *_aux);

int xcb_change_window_attributes_value_list_sizeof(const void *_buffer,
                                                   uint32_t value_mask);

int xcb_change_window_attributes_sizeof(const void *_buffer);
# 5945 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_window_attributes_checked(xcb_connection_t *c,
                                                       xcb_window_t window,
                                                       uint32_t value_mask,
                                                       const void *value_list);
# 5966 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_window_attributes(xcb_connection_t *c,
                                               xcb_window_t window,
                                               uint32_t value_mask,
                                               const void *value_list);
# 5990 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_window_attributes_aux_checked(
    xcb_connection_t *c, xcb_window_t window, uint32_t value_mask,
    const xcb_change_window_attributes_value_list_t *value_list);
# 6011 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_window_attributes_aux(
    xcb_connection_t *c, xcb_window_t window, uint32_t value_mask,
    const xcb_change_window_attributes_value_list_t *value_list);

void *xcb_change_window_attributes_value_list(
    const xcb_change_window_attributes_request_t *R);
# 6030 "/usr/include/xcb/xproto.h" 3 4
xcb_get_window_attributes_cookie_t
xcb_get_window_attributes(xcb_connection_t *c, xcb_window_t window);
# 6047 "/usr/include/xcb/xproto.h" 3 4
xcb_get_window_attributes_cookie_t
xcb_get_window_attributes_unchecked(xcb_connection_t *c, xcb_window_t window);
# 6065 "/usr/include/xcb/xproto.h" 3 4
xcb_get_window_attributes_reply_t *
xcb_get_window_attributes_reply(xcb_connection_t *c,
                                xcb_get_window_attributes_cookie_t cookie,
                                xcb_generic_error_t **e);
# 6088 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_destroy_window_checked(xcb_connection_t *c,
                                             xcb_window_t window);
# 6107 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_destroy_window(xcb_connection_t *c, xcb_window_t window);
# 6122 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_destroy_subwindows_checked(xcb_connection_t *c,
                                                 xcb_window_t window);
# 6134 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_destroy_subwindows(xcb_connection_t *c,
                                         xcb_window_t window);
# 6156 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_save_set_checked(xcb_connection_t *c, uint8_t mode,
                                              xcb_window_t window);
# 6176 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_save_set(xcb_connection_t *c, uint8_t mode,
                                      xcb_window_t window);
# 6202 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_reparent_window_checked(xcb_connection_t *c,
                                              xcb_window_t window,
                                              xcb_window_t parent, int16_t x,
                                              int16_t y);
# 6227 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_reparent_window(xcb_connection_t *c, xcb_window_t window,
                                      xcb_window_t parent, int16_t x,
                                      int16_t y);
# 6265 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_map_window_checked(xcb_connection_t *c,
                                         xcb_window_t window);
# 6297 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_map_window(xcb_connection_t *c, xcb_window_t window);
# 6312 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_map_subwindows_checked(xcb_connection_t *c,
                                             xcb_window_t window);
# 6324 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_map_subwindows(xcb_connection_t *c, xcb_window_t window);
# 6345 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_unmap_window_checked(xcb_connection_t *c,
                                           xcb_window_t window);
# 6363 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_unmap_window(xcb_connection_t *c, xcb_window_t window);
# 6378 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_unmap_subwindows_checked(xcb_connection_t *c,
                                               xcb_window_t window);
# 6390 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_unmap_subwindows(xcb_connection_t *c,
                                       xcb_window_t window);

int xcb_configure_window_value_list_serialize(
    void **_buffer, uint16_t value_mask,
    const xcb_configure_window_value_list_t *_aux);

int xcb_configure_window_value_list_unpack(
    const void *_buffer, uint16_t value_mask,
    xcb_configure_window_value_list_t *_aux);

int xcb_configure_window_value_list_sizeof(const void *_buffer,
                                           uint16_t value_mask);

int xcb_configure_window_sizeof(const void *_buffer);
# 6427 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_configure_window_checked(xcb_connection_t *c,
                                               xcb_window_t window,
                                               uint16_t value_mask,
                                               const void *value_list);
# 6446 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_configure_window(xcb_connection_t *c, xcb_window_t window,
                                       uint16_t value_mask,
                                       const void *value_list);
# 6468 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_configure_window_aux_checked(
    xcb_connection_t *c, xcb_window_t window, uint16_t value_mask,
    const xcb_configure_window_value_list_t *value_list);
# 6487 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_configure_window_aux(xcb_connection_t *c, xcb_window_t window,
                         uint16_t value_mask,
                         const xcb_configure_window_value_list_t *value_list);

void *xcb_configure_window_value_list(const xcb_configure_window_request_t *R);
# 6515 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_circulate_window_checked(xcb_connection_t *c,
                                               uint8_t direction,
                                               xcb_window_t window);
# 6536 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_circulate_window(xcb_connection_t *c, uint8_t direction,
                                       xcb_window_t window);
# 6551 "/usr/include/xcb/xproto.h" 3 4
xcb_get_geometry_cookie_t xcb_get_geometry(xcb_connection_t *c,
                                           xcb_drawable_t drawable);
# 6568 "/usr/include/xcb/xproto.h" 3 4
xcb_get_geometry_cookie_t xcb_get_geometry_unchecked(xcb_connection_t *c,
                                                     xcb_drawable_t drawable);
# 6586 "/usr/include/xcb/xproto.h" 3 4
xcb_get_geometry_reply_t *
xcb_get_geometry_reply(xcb_connection_t *c, xcb_get_geometry_cookie_t cookie,
                       xcb_generic_error_t **e);

int xcb_query_tree_sizeof(const void *_buffer);
# 6605 "/usr/include/xcb/xproto.h" 3 4
xcb_query_tree_cookie_t xcb_query_tree(xcb_connection_t *c,
                                       xcb_window_t window);
# 6623 "/usr/include/xcb/xproto.h" 3 4
xcb_query_tree_cookie_t xcb_query_tree_unchecked(xcb_connection_t *c,
                                                 xcb_window_t window);

xcb_window_t *xcb_query_tree_children(const xcb_query_tree_reply_t *R);

int xcb_query_tree_children_length(const xcb_query_tree_reply_t *R);

xcb_generic_iterator_t
xcb_query_tree_children_end(const xcb_query_tree_reply_t *R);
# 6650 "/usr/include/xcb/xproto.h" 3 4
xcb_query_tree_reply_t *xcb_query_tree_reply(xcb_connection_t *c,
                                             xcb_query_tree_cookie_t cookie,
                                             xcb_generic_error_t **e);

int xcb_intern_atom_sizeof(const void *_buffer);
# 6676 "/usr/include/xcb/xproto.h" 3 4
xcb_intern_atom_cookie_t xcb_intern_atom(xcb_connection_t *c,
                                         uint8_t only_if_exists,
                                         uint16_t name_len, const char *name);
# 6703 "/usr/include/xcb/xproto.h" 3 4
xcb_intern_atom_cookie_t xcb_intern_atom_unchecked(xcb_connection_t *c,
                                                   uint8_t only_if_exists,
                                                   uint16_t name_len,
                                                   const char *name);
# 6723 "/usr/include/xcb/xproto.h" 3 4
xcb_intern_atom_reply_t *xcb_intern_atom_reply(xcb_connection_t *c,
                                               xcb_intern_atom_cookie_t cookie,
                                               xcb_generic_error_t **e);

int xcb_get_atom_name_sizeof(const void *_buffer);
# 6739 "/usr/include/xcb/xproto.h" 3 4
xcb_get_atom_name_cookie_t xcb_get_atom_name(xcb_connection_t *c,
                                             xcb_atom_t atom);
# 6754 "/usr/include/xcb/xproto.h" 3 4
xcb_get_atom_name_cookie_t xcb_get_atom_name_unchecked(xcb_connection_t *c,
                                                       xcb_atom_t atom);

char *xcb_get_atom_name_name(const xcb_get_atom_name_reply_t *R);

int xcb_get_atom_name_name_length(const xcb_get_atom_name_reply_t *R);

xcb_generic_iterator_t
xcb_get_atom_name_name_end(const xcb_get_atom_name_reply_t *R);
# 6781 "/usr/include/xcb/xproto.h" 3 4
xcb_get_atom_name_reply_t *
xcb_get_atom_name_reply(xcb_connection_t *c, xcb_get_atom_name_cookie_t cookie,
                        xcb_generic_error_t **e);

int xcb_change_property_sizeof(const void *_buffer);
# 6814 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_property_checked(
    xcb_connection_t *c, uint8_t mode, xcb_window_t window, xcb_atom_t property,
    xcb_atom_t type, uint8_t format, uint32_t data_len, const void *data);
# 6846 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_property(xcb_connection_t *c, uint8_t mode,
                                      xcb_window_t window, xcb_atom_t property,
                                      xcb_atom_t type, uint8_t format,
                                      uint32_t data_len, const void *data);

void *xcb_change_property_data(const xcb_change_property_request_t *R);

int xcb_change_property_data_length(const xcb_change_property_request_t *R);

xcb_generic_iterator_t
xcb_change_property_data_end(const xcb_change_property_request_t *R);
# 6876 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_delete_property_checked(xcb_connection_t *c,
                                              xcb_window_t window,
                                              xcb_atom_t property);
# 6889 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_delete_property(xcb_connection_t *c, xcb_window_t window,
                                      xcb_atom_t property);

int xcb_get_property_sizeof(const void *_buffer);
# 6924 "/usr/include/xcb/xproto.h" 3 4
xcb_get_property_cookie_t xcb_get_property(xcb_connection_t *c, uint8_t _delete,
                                           xcb_window_t window,
                                           xcb_atom_t property, xcb_atom_t type,
                                           uint32_t long_offset,
                                           uint32_t long_length);
# 6963 "/usr/include/xcb/xproto.h" 3 4
xcb_get_property_cookie_t
xcb_get_property_unchecked(xcb_connection_t *c, uint8_t _delete,
                           xcb_window_t window, xcb_atom_t property,
                           xcb_atom_t type, uint32_t long_offset,
                           uint32_t long_length);

void *xcb_get_property_value(const xcb_get_property_reply_t *R);

int xcb_get_property_value_length(const xcb_get_property_reply_t *R);

xcb_generic_iterator_t
xcb_get_property_value_end(const xcb_get_property_reply_t *R);
# 6995 "/usr/include/xcb/xproto.h" 3 4
xcb_get_property_reply_t *
xcb_get_property_reply(xcb_connection_t *c, xcb_get_property_cookie_t cookie,
                       xcb_generic_error_t **e);

int xcb_list_properties_sizeof(const void *_buffer);
# 7011 "/usr/include/xcb/xproto.h" 3 4
xcb_list_properties_cookie_t xcb_list_properties(xcb_connection_t *c,
                                                 xcb_window_t window);
# 7026 "/usr/include/xcb/xproto.h" 3 4
xcb_list_properties_cookie_t xcb_list_properties_unchecked(xcb_connection_t *c,
                                                           xcb_window_t window);

xcb_atom_t *xcb_list_properties_atoms(const xcb_list_properties_reply_t *R);

int xcb_list_properties_atoms_length(const xcb_list_properties_reply_t *R);

xcb_generic_iterator_t
xcb_list_properties_atoms_end(const xcb_list_properties_reply_t *R);
# 7053 "/usr/include/xcb/xproto.h" 3 4
xcb_list_properties_reply_t *
xcb_list_properties_reply(xcb_connection_t *c,
                          xcb_list_properties_cookie_t cookie,
                          xcb_generic_error_t **e);
# 7085 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_selection_owner_checked(xcb_connection_t *c,
                                                  xcb_window_t owner,
                                                  xcb_atom_t selection,
                                                  xcb_timestamp_t time);
# 7115 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_selection_owner(xcb_connection_t *c,
                                          xcb_window_t owner,
                                          xcb_atom_t selection,
                                          xcb_timestamp_t time);
# 7133 "/usr/include/xcb/xproto.h" 3 4
xcb_get_selection_owner_cookie_t xcb_get_selection_owner(xcb_connection_t *c,
                                                         xcb_atom_t selection);
# 7152 "/usr/include/xcb/xproto.h" 3 4
xcb_get_selection_owner_cookie_t
xcb_get_selection_owner_unchecked(xcb_connection_t *c, xcb_atom_t selection);
# 7170 "/usr/include/xcb/xproto.h" 3 4
xcb_get_selection_owner_reply_t *
xcb_get_selection_owner_reply(xcb_connection_t *c,
                              xcb_get_selection_owner_cookie_t cookie,
                              xcb_generic_error_t **e);
# 7186 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_convert_selection_checked(xcb_connection_t *c, xcb_window_t requestor,
                              xcb_atom_t selection, xcb_atom_t target,
                              xcb_atom_t property, xcb_timestamp_t time);
# 7202 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_convert_selection(xcb_connection_t *c,
                                        xcb_window_t requestor,
                                        xcb_atom_t selection, xcb_atom_t target,
                                        xcb_atom_t property,
                                        xcb_timestamp_t time);
# 7247 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_send_event_checked(xcb_connection_t *c, uint8_t propagate,
                                         xcb_window_t destination,
                                         uint32_t event_mask,
                                         const char *event);
# 7288 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_send_event(xcb_connection_t *c, uint8_t propagate,
                                 xcb_window_t destination, uint32_t event_mask,
                                 const char *event);
# 7331 "/usr/include/xcb/xproto.h" 3 4
xcb_grab_pointer_cookie_t xcb_grab_pointer(
    xcb_connection_t *c, uint8_t owner_events, xcb_window_t grab_window,
    uint16_t event_mask, uint8_t pointer_mode, uint8_t keyboard_mode,
    xcb_window_t confine_to, xcb_cursor_t cursor, xcb_timestamp_t time);
# 7381 "/usr/include/xcb/xproto.h" 3 4
xcb_grab_pointer_cookie_t xcb_grab_pointer_unchecked(
    xcb_connection_t *c, uint8_t owner_events, xcb_window_t grab_window,
    uint16_t event_mask, uint8_t pointer_mode, uint8_t keyboard_mode,
    xcb_window_t confine_to, xcb_cursor_t cursor, xcb_timestamp_t time);
# 7406 "/usr/include/xcb/xproto.h" 3 4
xcb_grab_pointer_reply_t *
xcb_grab_pointer_reply(xcb_connection_t *c, xcb_grab_pointer_cookie_t cookie,
                       xcb_generic_error_t **e);
# 7431 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_pointer_checked(xcb_connection_t *c,
                                             xcb_timestamp_t time);
# 7452 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_pointer(xcb_connection_t *c, xcb_timestamp_t time);
# 7524 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_grab_button_checked(xcb_connection_t *c, uint8_t owner_events,
                        xcb_window_t grab_window, uint16_t event_mask,
                        uint8_t pointer_mode, uint8_t keyboard_mode,
                        xcb_window_t confine_to, xcb_cursor_t cursor,
                        uint8_t button, uint16_t modifiers);
# 7601 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_grab_button(xcb_connection_t *c, uint8_t owner_events,
                                  xcb_window_t grab_window, uint16_t event_mask,
                                  uint8_t pointer_mode, uint8_t keyboard_mode,
                                  xcb_window_t confine_to, xcb_cursor_t cursor,
                                  uint8_t button, uint16_t modifiers);
# 7624 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_button_checked(xcb_connection_t *c, uint8_t button,
                                            xcb_window_t grab_window,
                                            uint16_t modifiers);
# 7638 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_button(xcb_connection_t *c, uint8_t button,
                                    xcb_window_t grab_window,
                                    uint16_t modifiers);
# 7655 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_active_pointer_grab_checked(xcb_connection_t *c,
                                                         xcb_cursor_t cursor,
                                                         xcb_timestamp_t time,
                                                         uint16_t event_mask);
# 7669 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_active_pointer_grab(xcb_connection_t *c,
                                                 xcb_cursor_t cursor,
                                                 xcb_timestamp_t time,
                                                 uint16_t event_mask);
# 7704 "/usr/include/xcb/xproto.h" 3 4
xcb_grab_keyboard_cookie_t
xcb_grab_keyboard(xcb_connection_t *c, uint8_t owner_events,
                  xcb_window_t grab_window, xcb_timestamp_t time,
                  uint8_t pointer_mode, uint8_t keyboard_mode);
# 7744 "/usr/include/xcb/xproto.h" 3 4
xcb_grab_keyboard_cookie_t
xcb_grab_keyboard_unchecked(xcb_connection_t *c, uint8_t owner_events,
                            xcb_window_t grab_window, xcb_timestamp_t time,
                            uint8_t pointer_mode, uint8_t keyboard_mode);
# 7766 "/usr/include/xcb/xproto.h" 3 4
xcb_grab_keyboard_reply_t *
xcb_grab_keyboard_reply(xcb_connection_t *c, xcb_grab_keyboard_cookie_t cookie,
                        xcb_generic_error_t **e);
# 7782 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_keyboard_checked(xcb_connection_t *c,
                                              xcb_timestamp_t time);
# 7794 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_keyboard(xcb_connection_t *c,
                                      xcb_timestamp_t time);
# 7853 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_grab_key_checked(xcb_connection_t *c,
                                       uint8_t owner_events,
                                       xcb_window_t grab_window,
                                       uint16_t modifiers, xcb_keycode_t key,
                                       uint8_t pointer_mode,
                                       uint8_t keyboard_mode);
# 7914 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_grab_key(xcb_connection_t *c, uint8_t owner_events,
                               xcb_window_t grab_window, uint16_t modifiers,
                               xcb_keycode_t key, uint8_t pointer_mode,
                               uint8_t keyboard_mode);
# 7944 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_key_checked(xcb_connection_t *c, xcb_keycode_t key,
                                         xcb_window_t grab_window,
                                         uint16_t modifiers);
# 7968 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_key(xcb_connection_t *c, xcb_keycode_t key,
                                 xcb_window_t grab_window, uint16_t modifiers);
# 7995 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_allow_events_checked(xcb_connection_t *c, uint8_t mode,
                                           xcb_timestamp_t time);
# 8018 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_allow_events(xcb_connection_t *c, uint8_t mode,
                                   xcb_timestamp_t time);
# 8034 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_grab_server_checked(xcb_connection_t *c);
# 8045 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_grab_server(xcb_connection_t *c);
# 8059 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_server_checked(xcb_connection_t *c);
# 8070 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_ungrab_server(xcb_connection_t *c);
# 8085 "/usr/include/xcb/xproto.h" 3 4
xcb_query_pointer_cookie_t xcb_query_pointer(xcb_connection_t *c,
                                             xcb_window_t window);
# 8104 "/usr/include/xcb/xproto.h" 3 4
xcb_query_pointer_cookie_t xcb_query_pointer_unchecked(xcb_connection_t *c,
                                                       xcb_window_t window);
# 8122 "/usr/include/xcb/xproto.h" 3 4
xcb_query_pointer_reply_t *
xcb_query_pointer_reply(xcb_connection_t *c, xcb_query_pointer_cookie_t cookie,
                        xcb_generic_error_t **e);
# 8135 "/usr/include/xcb/xproto.h" 3 4
void xcb_timecoord_next(xcb_timecoord_iterator_t *i);
# 8147 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_timecoord_end(xcb_timecoord_iterator_t i);

int xcb_get_motion_events_sizeof(const void *_buffer);
# 8161 "/usr/include/xcb/xproto.h" 3 4
xcb_get_motion_events_cookie_t xcb_get_motion_events(xcb_connection_t *c,
                                                     xcb_window_t window,
                                                     xcb_timestamp_t start,
                                                     xcb_timestamp_t stop);
# 8178 "/usr/include/xcb/xproto.h" 3 4
xcb_get_motion_events_cookie_t
xcb_get_motion_events_unchecked(xcb_connection_t *c, xcb_window_t window,
                                xcb_timestamp_t start, xcb_timestamp_t stop);

xcb_timecoord_t *
xcb_get_motion_events_events(const xcb_get_motion_events_reply_t *R);

int xcb_get_motion_events_events_length(const xcb_get_motion_events_reply_t *R);

xcb_timecoord_iterator_t
xcb_get_motion_events_events_iterator(const xcb_get_motion_events_reply_t *R);
# 8207 "/usr/include/xcb/xproto.h" 3 4
xcb_get_motion_events_reply_t *
xcb_get_motion_events_reply(xcb_connection_t *c,
                            xcb_get_motion_events_cookie_t cookie,
                            xcb_generic_error_t **e);
# 8220 "/usr/include/xcb/xproto.h" 3 4
xcb_translate_coordinates_cookie_t
xcb_translate_coordinates(xcb_connection_t *c, xcb_window_t src_window,
                          xcb_window_t dst_window, int16_t src_x,
                          int16_t src_y);
# 8238 "/usr/include/xcb/xproto.h" 3 4
xcb_translate_coordinates_cookie_t xcb_translate_coordinates_unchecked(
    xcb_connection_t *c, xcb_window_t src_window, xcb_window_t dst_window,
    int16_t src_x, int16_t src_y);
# 8259 "/usr/include/xcb/xproto.h" 3 4
xcb_translate_coordinates_reply_t *
xcb_translate_coordinates_reply(xcb_connection_t *c,
                                xcb_translate_coordinates_cookie_t cookie,
                                xcb_generic_error_t **e);
# 8294 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_warp_pointer_checked(xcb_connection_t *c, xcb_window_t src_window,
                         xcb_window_t dst_window, int16_t src_x, int16_t src_y,
                         uint16_t src_width, uint16_t src_height, int16_t dst_x,
                         int16_t dst_y);
# 8332 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_warp_pointer(xcb_connection_t *c, xcb_window_t src_window,
                                   xcb_window_t dst_window, int16_t src_x,
                                   int16_t src_y, uint16_t src_width,
                                   uint16_t src_height, int16_t dst_x,
                                   int16_t dst_y);
# 8374 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_input_focus_checked(xcb_connection_t *c,
                                              uint8_t revert_to,
                                              xcb_window_t focus,
                                              xcb_timestamp_t time);
# 8408 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_input_focus(xcb_connection_t *c, uint8_t revert_to,
                                      xcb_window_t focus, xcb_timestamp_t time);
# 8422 "/usr/include/xcb/xproto.h" 3 4
xcb_get_input_focus_cookie_t xcb_get_input_focus(xcb_connection_t *c);
# 8436 "/usr/include/xcb/xproto.h" 3 4
xcb_get_input_focus_cookie_t xcb_get_input_focus_unchecked(xcb_connection_t *c);
# 8453 "/usr/include/xcb/xproto.h" 3 4
xcb_get_input_focus_reply_t *
xcb_get_input_focus_reply(xcb_connection_t *c,
                          xcb_get_input_focus_cookie_t cookie,
                          xcb_generic_error_t **e);
# 8466 "/usr/include/xcb/xproto.h" 3 4
xcb_query_keymap_cookie_t xcb_query_keymap(xcb_connection_t *c);
# 8480 "/usr/include/xcb/xproto.h" 3 4
xcb_query_keymap_cookie_t xcb_query_keymap_unchecked(xcb_connection_t *c);
# 8497 "/usr/include/xcb/xproto.h" 3 4
xcb_query_keymap_reply_t *
xcb_query_keymap_reply(xcb_connection_t *c, xcb_query_keymap_cookie_t cookie,
                       xcb_generic_error_t **e);

int xcb_open_font_sizeof(const void *_buffer);
# 8523 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_open_font_checked(xcb_connection_t *c, xcb_font_t fid,
                                        uint16_t name_len, const char *name);
# 8544 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_open_font(xcb_connection_t *c, xcb_font_t fid,
                                uint16_t name_len, const char *name);

char *xcb_open_font_name(const xcb_open_font_request_t *R);

int xcb_open_font_name_length(const xcb_open_font_request_t *R);

xcb_generic_iterator_t xcb_open_font_name_end(const xcb_open_font_request_t *R);
# 8570 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_close_font_checked(xcb_connection_t *c, xcb_font_t font);
# 8582 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_close_font(xcb_connection_t *c, xcb_font_t font);
# 8594 "/usr/include/xcb/xproto.h" 3 4
void xcb_fontprop_next(xcb_fontprop_iterator_t *i);
# 8606 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_fontprop_end(xcb_fontprop_iterator_t i);
# 8617 "/usr/include/xcb/xproto.h" 3 4
void xcb_charinfo_next(xcb_charinfo_iterator_t *i);
# 8629 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_charinfo_end(xcb_charinfo_iterator_t i);

int xcb_query_font_sizeof(const void *_buffer);
# 8645 "/usr/include/xcb/xproto.h" 3 4
xcb_query_font_cookie_t xcb_query_font(xcb_connection_t *c,
                                       xcb_fontable_t font);
# 8662 "/usr/include/xcb/xproto.h" 3 4
xcb_query_font_cookie_t xcb_query_font_unchecked(xcb_connection_t *c,
                                                 xcb_fontable_t font);

xcb_fontprop_t *xcb_query_font_properties(const xcb_query_font_reply_t *R);

int xcb_query_font_properties_length(const xcb_query_font_reply_t *R);

xcb_fontprop_iterator_t
xcb_query_font_properties_iterator(const xcb_query_font_reply_t *R);

xcb_charinfo_t *xcb_query_font_char_infos(const xcb_query_font_reply_t *R);

int xcb_query_font_char_infos_length(const xcb_query_font_reply_t *R);

xcb_charinfo_iterator_t
xcb_query_font_char_infos_iterator(const xcb_query_font_reply_t *R);
# 8698 "/usr/include/xcb/xproto.h" 3 4
xcb_query_font_reply_t *xcb_query_font_reply(xcb_connection_t *c,
                                             xcb_query_font_cookie_t cookie,
                                             xcb_generic_error_t **e);

int xcb_query_text_extents_sizeof(const void *_buffer, uint32_t string_len);
# 8739 "/usr/include/xcb/xproto.h" 3 4
xcb_query_text_extents_cookie_t
xcb_query_text_extents(xcb_connection_t *c, xcb_fontable_t font,
                       uint32_t string_len, const xcb_char2b_t *string);
# 8780 "/usr/include/xcb/xproto.h" 3 4
xcb_query_text_extents_cookie_t
xcb_query_text_extents_unchecked(xcb_connection_t *c, xcb_fontable_t font,
                                 uint32_t string_len,
                                 const xcb_char2b_t *string);
# 8800 "/usr/include/xcb/xproto.h" 3 4
xcb_query_text_extents_reply_t *
xcb_query_text_extents_reply(xcb_connection_t *c,
                             xcb_query_text_extents_cookie_t cookie,
                             xcb_generic_error_t **e);

int xcb_str_sizeof(const void *_buffer);

char *xcb_str_name(const xcb_str_t *R);

int xcb_str_name_length(const xcb_str_t *R);

xcb_generic_iterator_t xcb_str_name_end(const xcb_str_t *R);
# 8825 "/usr/include/xcb/xproto.h" 3 4
void xcb_str_next(xcb_str_iterator_t *i);
# 8837 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_str_end(xcb_str_iterator_t i);

int xcb_list_fonts_sizeof(const void *_buffer);
# 8859 "/usr/include/xcb/xproto.h" 3 4
xcb_list_fonts_cookie_t xcb_list_fonts(xcb_connection_t *c, uint16_t max_names,
                                       uint16_t pattern_len,
                                       const char *pattern);
# 8884 "/usr/include/xcb/xproto.h" 3 4
xcb_list_fonts_cookie_t xcb_list_fonts_unchecked(xcb_connection_t *c,
                                                 uint16_t max_names,
                                                 uint16_t pattern_len,
                                                 const char *pattern);

int xcb_list_fonts_names_length(const xcb_list_fonts_reply_t *R);

xcb_str_iterator_t
xcb_list_fonts_names_iterator(const xcb_list_fonts_reply_t *R);
# 8910 "/usr/include/xcb/xproto.h" 3 4
xcb_list_fonts_reply_t *xcb_list_fonts_reply(xcb_connection_t *c,
                                             xcb_list_fonts_cookie_t cookie,
                                             xcb_generic_error_t **e);

int xcb_list_fonts_with_info_sizeof(const void *_buffer);
# 8934 "/usr/include/xcb/xproto.h" 3 4
xcb_list_fonts_with_info_cookie_t xcb_list_fonts_with_info(xcb_connection_t *c,
                                                           uint16_t max_names,
                                                           uint16_t pattern_len,
                                                           const char *pattern);
# 8959 "/usr/include/xcb/xproto.h" 3 4
xcb_list_fonts_with_info_cookie_t
xcb_list_fonts_with_info_unchecked(xcb_connection_t *c, uint16_t max_names,
                                   uint16_t pattern_len, const char *pattern);

xcb_fontprop_t *
xcb_list_fonts_with_info_properties(const xcb_list_fonts_with_info_reply_t *R);

int xcb_list_fonts_with_info_properties_length(
    const xcb_list_fonts_with_info_reply_t *R);

xcb_fontprop_iterator_t xcb_list_fonts_with_info_properties_iterator(
    const xcb_list_fonts_with_info_reply_t *R);

char *xcb_list_fonts_with_info_name(const xcb_list_fonts_with_info_reply_t *R);

int xcb_list_fonts_with_info_name_length(
    const xcb_list_fonts_with_info_reply_t *R);

xcb_generic_iterator_t
xcb_list_fonts_with_info_name_end(const xcb_list_fonts_with_info_reply_t *R);
# 8997 "/usr/include/xcb/xproto.h" 3 4
xcb_list_fonts_with_info_reply_t *
xcb_list_fonts_with_info_reply(xcb_connection_t *c,
                               xcb_list_fonts_with_info_cookie_t cookie,
                               xcb_generic_error_t **e);

int xcb_set_font_path_sizeof(const void *_buffer);
# 9016 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_font_path_checked(xcb_connection_t *c,
                                            uint16_t font_qty,
                                            const xcb_str_t *font);
# 9029 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_font_path(xcb_connection_t *c, uint16_t font_qty,
                                    const xcb_str_t *font);

int xcb_set_font_path_font_length(const xcb_set_font_path_request_t *R);

xcb_str_iterator_t
xcb_set_font_path_font_iterator(const xcb_set_font_path_request_t *R);

int xcb_get_font_path_sizeof(const void *_buffer);
# 9051 "/usr/include/xcb/xproto.h" 3 4
xcb_get_font_path_cookie_t xcb_get_font_path(xcb_connection_t *c);
# 9065 "/usr/include/xcb/xproto.h" 3 4
xcb_get_font_path_cookie_t xcb_get_font_path_unchecked(xcb_connection_t *c);

int xcb_get_font_path_path_length(const xcb_get_font_path_reply_t *R);

xcb_str_iterator_t
xcb_get_font_path_path_iterator(const xcb_get_font_path_reply_t *R);
# 9088 "/usr/include/xcb/xproto.h" 3 4
xcb_get_font_path_reply_t *
xcb_get_font_path_reply(xcb_connection_t *c, xcb_get_font_path_cookie_t cookie,
                        xcb_generic_error_t **e);
# 9112 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_pixmap_checked(xcb_connection_t *c, uint8_t depth,
                                            xcb_pixmap_t pid,
                                            xcb_drawable_t drawable,
                                            uint16_t width, uint16_t height);
# 9136 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_pixmap(xcb_connection_t *c, uint8_t depth,
                                    xcb_pixmap_t pid, xcb_drawable_t drawable,
                                    uint16_t width, uint16_t height);
# 9158 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_pixmap_checked(xcb_connection_t *c,
                                          xcb_pixmap_t pixmap);
# 9173 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_pixmap(xcb_connection_t *c, xcb_pixmap_t pixmap);

int xcb_create_gc_value_list_serialize(void **_buffer, uint32_t value_mask,
                                       const xcb_create_gc_value_list_t *_aux);

int xcb_create_gc_value_list_unpack(const void *_buffer, uint32_t value_mask,
                                    xcb_create_gc_value_list_t *_aux);

int xcb_create_gc_value_list_sizeof(const void *_buffer, uint32_t value_mask);

int xcb_create_gc_sizeof(const void *_buffer);
# 9210 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_gc_checked(xcb_connection_t *c, xcb_gcontext_t cid,
                                        xcb_drawable_t drawable,
                                        uint32_t value_mask,
                                        const void *value_list);
# 9230 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_gc(xcb_connection_t *c, xcb_gcontext_t cid,
                                xcb_drawable_t drawable, uint32_t value_mask,
                                const void *value_list);
# 9253 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_create_gc_aux_checked(xcb_connection_t *c, xcb_gcontext_t cid,
                          xcb_drawable_t drawable, uint32_t value_mask,
                          const xcb_create_gc_value_list_t *value_list);
# 9273 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_create_gc_aux(xcb_connection_t *c, xcb_gcontext_t cid,
                  xcb_drawable_t drawable, uint32_t value_mask,
                  const xcb_create_gc_value_list_t *value_list);

void *xcb_create_gc_value_list(const xcb_create_gc_request_t *R);

int xcb_change_gc_value_list_serialize(void **_buffer, uint32_t value_mask,
                                       const xcb_change_gc_value_list_t *_aux);

int xcb_change_gc_value_list_unpack(const void *_buffer, uint32_t value_mask,
                                    xcb_change_gc_value_list_t *_aux);

int xcb_change_gc_value_list_sizeof(const void *_buffer, uint32_t value_mask);

int xcb_change_gc_sizeof(const void *_buffer);
# 9318 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_gc_checked(xcb_connection_t *c, xcb_gcontext_t gc,
                                        uint32_t value_mask,
                                        const void *value_list);
# 9339 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_gc(xcb_connection_t *c, xcb_gcontext_t gc,
                                uint32_t value_mask, const void *value_list);
# 9363 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_change_gc_aux_checked(xcb_connection_t *c, xcb_gcontext_t gc,
                          uint32_t value_mask,
                          const xcb_change_gc_value_list_t *value_list);
# 9384 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_change_gc_aux(xcb_connection_t *c, xcb_gcontext_t gc, uint32_t value_mask,
                  const xcb_change_gc_value_list_t *value_list);

void *xcb_change_gc_value_list(const xcb_change_gc_request_t *R);
# 9404 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_copy_gc_checked(xcb_connection_t *c,
                                      xcb_gcontext_t src_gc,
                                      xcb_gcontext_t dst_gc,
                                      uint32_t value_mask);
# 9418 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_copy_gc(xcb_connection_t *c, xcb_gcontext_t src_gc,
                              xcb_gcontext_t dst_gc, uint32_t value_mask);

int xcb_set_dashes_sizeof(const void *_buffer);
# 9438 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_dashes_checked(xcb_connection_t *c, xcb_gcontext_t gc,
                                         uint16_t dash_offset,
                                         uint16_t dashes_len,
                                         const uint8_t *dashes);
# 9453 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_dashes(xcb_connection_t *c, xcb_gcontext_t gc,
                                 uint16_t dash_offset, uint16_t dashes_len,
                                 const uint8_t *dashes);

uint8_t *xcb_set_dashes_dashes(const xcb_set_dashes_request_t *R);

int xcb_set_dashes_dashes_length(const xcb_set_dashes_request_t *R);

xcb_generic_iterator_t
xcb_set_dashes_dashes_end(const xcb_set_dashes_request_t *R);

int xcb_set_clip_rectangles_sizeof(const void *_buffer,
                                   uint32_t rectangles_len);
# 9484 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_set_clip_rectangles_checked(xcb_connection_t *c, uint8_t ordering,
                                xcb_gcontext_t gc, int16_t clip_x_origin,
                                int16_t clip_y_origin, uint32_t rectangles_len,
                                const xcb_rectangle_t *rectangles);
# 9501 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_clip_rectangles(xcb_connection_t *c, uint8_t ordering,
                                          xcb_gcontext_t gc,
                                          int16_t clip_x_origin,
                                          int16_t clip_y_origin,
                                          uint32_t rectangles_len,
                                          const xcb_rectangle_t *rectangles);

xcb_rectangle_t *
xcb_set_clip_rectangles_rectangles(const xcb_set_clip_rectangles_request_t *R);

int xcb_set_clip_rectangles_rectangles_length(
    const xcb_set_clip_rectangles_request_t *R);

xcb_rectangle_iterator_t xcb_set_clip_rectangles_rectangles_iterator(
    const xcb_set_clip_rectangles_request_t *R);
# 9532 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_gc_checked(xcb_connection_t *c, xcb_gcontext_t gc);
# 9546 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_gc(xcb_connection_t *c, xcb_gcontext_t gc);
# 9561 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_clear_area_checked(xcb_connection_t *c, uint8_t exposures,
                                         xcb_window_t window, int16_t x,
                                         int16_t y, uint16_t width,
                                         uint16_t height);
# 9578 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_clear_area(xcb_connection_t *c, uint8_t exposures,
                                 xcb_window_t window, int16_t x, int16_t y,
                                 uint16_t width, uint16_t height);
# 9608 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_copy_area_checked(xcb_connection_t *c, xcb_drawable_t src_drawable,
                      xcb_drawable_t dst_drawable, xcb_gcontext_t gc,
                      int16_t src_x, int16_t src_y, int16_t dst_x,
                      int16_t dst_y, uint16_t width, uint16_t height);
# 9638 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_copy_area(xcb_connection_t *c,
                                xcb_drawable_t src_drawable,
                                xcb_drawable_t dst_drawable, xcb_gcontext_t gc,
                                int16_t src_x, int16_t src_y, int16_t dst_x,
                                int16_t dst_y, uint16_t width, uint16_t height);
# 9661 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_copy_plane_checked(xcb_connection_t *c,
                                         xcb_drawable_t src_drawable,
                                         xcb_drawable_t dst_drawable,
                                         xcb_gcontext_t gc, int16_t src_x,
                                         int16_t src_y, int16_t dst_x,
                                         int16_t dst_y, uint16_t width,
                                         uint16_t height, uint32_t bit_plane);
# 9682 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_copy_plane(xcb_connection_t *c,
                                 xcb_drawable_t src_drawable,
                                 xcb_drawable_t dst_drawable, xcb_gcontext_t gc,
                                 int16_t src_x, int16_t src_y, int16_t dst_x,
                                 int16_t dst_y, uint16_t width, uint16_t height,
                                 uint32_t bit_plane);

int xcb_poly_point_sizeof(const void *_buffer, uint32_t points_len);
# 9710 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_point_checked(xcb_connection_t *c,
                                         uint8_t coordinate_mode,
                                         xcb_drawable_t drawable,
                                         xcb_gcontext_t gc, uint32_t points_len,
                                         const xcb_point_t *points);
# 9726 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_point(xcb_connection_t *c, uint8_t coordinate_mode,
                                 xcb_drawable_t drawable, xcb_gcontext_t gc,
                                 uint32_t points_len,
                                 const xcb_point_t *points);

xcb_point_t *xcb_poly_point_points(const xcb_poly_point_request_t *R);

int xcb_poly_point_points_length(const xcb_poly_point_request_t *R);

xcb_point_iterator_t
xcb_poly_point_points_iterator(const xcb_poly_point_request_t *R);

int xcb_poly_line_sizeof(const void *_buffer, uint32_t points_len);
# 9772 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_line_checked(xcb_connection_t *c,
                                        uint8_t coordinate_mode,
                                        xcb_drawable_t drawable,
                                        xcb_gcontext_t gc, uint32_t points_len,
                                        const xcb_point_t *points);
# 9802 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_line(xcb_connection_t *c, uint8_t coordinate_mode,
                                xcb_drawable_t drawable, xcb_gcontext_t gc,
                                uint32_t points_len, const xcb_point_t *points);

xcb_point_t *xcb_poly_line_points(const xcb_poly_line_request_t *R);

int xcb_poly_line_points_length(const xcb_poly_line_request_t *R);

xcb_point_iterator_t
xcb_poly_line_points_iterator(const xcb_poly_line_request_t *R);
# 9827 "/usr/include/xcb/xproto.h" 3 4
void xcb_segment_next(xcb_segment_iterator_t *i);
# 9839 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_segment_end(xcb_segment_iterator_t i);

int xcb_poly_segment_sizeof(const void *_buffer, uint32_t segments_len);
# 9872 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_segment_checked(xcb_connection_t *c,
                                           xcb_drawable_t drawable,
                                           xcb_gcontext_t gc,
                                           uint32_t segments_len,
                                           const xcb_segment_t *segments);
# 9902 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_segment(xcb_connection_t *c, xcb_drawable_t drawable,
                                   xcb_gcontext_t gc, uint32_t segments_len,
                                   const xcb_segment_t *segments);

xcb_segment_t *xcb_poly_segment_segments(const xcb_poly_segment_request_t *R);

int xcb_poly_segment_segments_length(const xcb_poly_segment_request_t *R);

xcb_segment_iterator_t
xcb_poly_segment_segments_iterator(const xcb_poly_segment_request_t *R);

int xcb_poly_rectangle_sizeof(const void *_buffer, uint32_t rectangles_len);
# 9933 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_rectangle_checked(xcb_connection_t *c,
                                             xcb_drawable_t drawable,
                                             xcb_gcontext_t gc,
                                             uint32_t rectangles_len,
                                             const xcb_rectangle_t *rectangles);
# 9948 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_rectangle(xcb_connection_t *c,
                                     xcb_drawable_t drawable, xcb_gcontext_t gc,
                                     uint32_t rectangles_len,
                                     const xcb_rectangle_t *rectangles);

xcb_rectangle_t *
xcb_poly_rectangle_rectangles(const xcb_poly_rectangle_request_t *R);

int xcb_poly_rectangle_rectangles_length(const xcb_poly_rectangle_request_t *R);

xcb_rectangle_iterator_t
xcb_poly_rectangle_rectangles_iterator(const xcb_poly_rectangle_request_t *R);

int xcb_poly_arc_sizeof(const void *_buffer, uint32_t arcs_len);
# 9979 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_arc_checked(xcb_connection_t *c,
                                       xcb_drawable_t drawable,
                                       xcb_gcontext_t gc, uint32_t arcs_len,
                                       const xcb_arc_t *arcs);
# 9994 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_arc(xcb_connection_t *c, xcb_drawable_t drawable,
                               xcb_gcontext_t gc, uint32_t arcs_len,
                               const xcb_arc_t *arcs);

xcb_arc_t *xcb_poly_arc_arcs(const xcb_poly_arc_request_t *R);

int xcb_poly_arc_arcs_length(const xcb_poly_arc_request_t *R);

xcb_arc_iterator_t xcb_poly_arc_arcs_iterator(const xcb_poly_arc_request_t *R);

int xcb_fill_poly_sizeof(const void *_buffer, uint32_t points_len);
# 10025 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_fill_poly_checked(xcb_connection_t *c, xcb_drawable_t drawable,
                      xcb_gcontext_t gc, uint8_t shape, uint8_t coordinate_mode,
                      uint32_t points_len, const xcb_point_t *points);
# 10042 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_fill_poly(xcb_connection_t *c, xcb_drawable_t drawable,
                                xcb_gcontext_t gc, uint8_t shape,
                                uint8_t coordinate_mode, uint32_t points_len,
                                const xcb_point_t *points);

xcb_point_t *xcb_fill_poly_points(const xcb_fill_poly_request_t *R);

int xcb_fill_poly_points_length(const xcb_fill_poly_request_t *R);

xcb_point_iterator_t
xcb_fill_poly_points_iterator(const xcb_fill_poly_request_t *R);

int xcb_poly_fill_rectangle_sizeof(const void *_buffer,
                                   uint32_t rectangles_len);
# 10089 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_poly_fill_rectangle_checked(xcb_connection_t *c, xcb_drawable_t drawable,
                                xcb_gcontext_t gc, uint32_t rectangles_len,
                                const xcb_rectangle_t *rectangles);
# 10118 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_fill_rectangle(xcb_connection_t *c,
                                          xcb_drawable_t drawable,
                                          xcb_gcontext_t gc,
                                          uint32_t rectangles_len,
                                          const xcb_rectangle_t *rectangles);

xcb_rectangle_t *
xcb_poly_fill_rectangle_rectangles(const xcb_poly_fill_rectangle_request_t *R);

int xcb_poly_fill_rectangle_rectangles_length(
    const xcb_poly_fill_rectangle_request_t *R);

xcb_rectangle_iterator_t xcb_poly_fill_rectangle_rectangles_iterator(
    const xcb_poly_fill_rectangle_request_t *R);

int xcb_poly_fill_arc_sizeof(const void *_buffer, uint32_t arcs_len);
# 10149 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_fill_arc_checked(xcb_connection_t *c,
                                            xcb_drawable_t drawable,
                                            xcb_gcontext_t gc,
                                            uint32_t arcs_len,
                                            const xcb_arc_t *arcs);
# 10164 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_fill_arc(xcb_connection_t *c,
                                    xcb_drawable_t drawable, xcb_gcontext_t gc,
                                    uint32_t arcs_len, const xcb_arc_t *arcs);

xcb_arc_t *xcb_poly_fill_arc_arcs(const xcb_poly_fill_arc_request_t *R);

int xcb_poly_fill_arc_arcs_length(const xcb_poly_fill_arc_request_t *R);

xcb_arc_iterator_t
xcb_poly_fill_arc_arcs_iterator(const xcb_poly_fill_arc_request_t *R);

int xcb_put_image_sizeof(const void *_buffer, uint32_t data_len);
# 10195 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_put_image_checked(xcb_connection_t *c, uint8_t format,
                                        xcb_drawable_t drawable,
                                        xcb_gcontext_t gc, uint16_t width,
                                        uint16_t height, int16_t dst_x,
                                        int16_t dst_y, uint8_t left_pad,
                                        uint8_t depth, uint32_t data_len,
                                        const uint8_t *data);
# 10217 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_put_image(xcb_connection_t *c, uint8_t format,
                                xcb_drawable_t drawable, xcb_gcontext_t gc,
                                uint16_t width, uint16_t height, int16_t dst_x,
                                int16_t dst_y, uint8_t left_pad, uint8_t depth,
                                uint32_t data_len, const uint8_t *data);

uint8_t *xcb_put_image_data(const xcb_put_image_request_t *R);

int xcb_put_image_data_length(const xcb_put_image_request_t *R);

xcb_generic_iterator_t xcb_put_image_data_end(const xcb_put_image_request_t *R);

int xcb_get_image_sizeof(const void *_buffer);
# 10251 "/usr/include/xcb/xproto.h" 3 4
xcb_get_image_cookie_t xcb_get_image(xcb_connection_t *c, uint8_t format,
                                     xcb_drawable_t drawable, int16_t x,
                                     int16_t y, uint16_t width, uint16_t height,
                                     uint32_t plane_mask);
# 10272 "/usr/include/xcb/xproto.h" 3 4
xcb_get_image_cookie_t
xcb_get_image_unchecked(xcb_connection_t *c, uint8_t format,
                        xcb_drawable_t drawable, int16_t x, int16_t y,
                        uint16_t width, uint16_t height, uint32_t plane_mask);

uint8_t *xcb_get_image_data(const xcb_get_image_reply_t *R);

int xcb_get_image_data_length(const xcb_get_image_reply_t *R);

xcb_generic_iterator_t xcb_get_image_data_end(const xcb_get_image_reply_t *R);
# 10305 "/usr/include/xcb/xproto.h" 3 4
xcb_get_image_reply_t *xcb_get_image_reply(xcb_connection_t *c,
                                           xcb_get_image_cookie_t cookie,
                                           xcb_generic_error_t **e);

int xcb_poly_text_8_sizeof(const void *_buffer, uint32_t items_len);
# 10325 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_text_8_checked(xcb_connection_t *c,
                                          xcb_drawable_t drawable,
                                          xcb_gcontext_t gc, int16_t x,
                                          int16_t y, uint32_t items_len,
                                          const uint8_t *items);
# 10342 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_text_8(xcb_connection_t *c, xcb_drawable_t drawable,
                                  xcb_gcontext_t gc, int16_t x, int16_t y,
                                  uint32_t items_len, const uint8_t *items);

uint8_t *xcb_poly_text_8_items(const xcb_poly_text_8_request_t *R);

int xcb_poly_text_8_items_length(const xcb_poly_text_8_request_t *R);

xcb_generic_iterator_t
xcb_poly_text_8_items_end(const xcb_poly_text_8_request_t *R);

int xcb_poly_text_16_sizeof(const void *_buffer, uint32_t items_len);
# 10375 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_text_16_checked(xcb_connection_t *c,
                                           xcb_drawable_t drawable,
                                           xcb_gcontext_t gc, int16_t x,
                                           int16_t y, uint32_t items_len,
                                           const uint8_t *items);
# 10392 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_poly_text_16(xcb_connection_t *c, xcb_drawable_t drawable,
                                   xcb_gcontext_t gc, int16_t x, int16_t y,
                                   uint32_t items_len, const uint8_t *items);

uint8_t *xcb_poly_text_16_items(const xcb_poly_text_16_request_t *R);

int xcb_poly_text_16_items_length(const xcb_poly_text_16_request_t *R);

xcb_generic_iterator_t
xcb_poly_text_16_items_end(const xcb_poly_text_16_request_t *R);

int xcb_image_text_8_sizeof(const void *_buffer);
# 10443 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_image_text_8_checked(xcb_connection_t *c,
                                           uint8_t string_len,
                                           xcb_drawable_t drawable,
                                           xcb_gcontext_t gc, int16_t x,
                                           int16_t y, const char *string);
# 10479 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_image_text_8(xcb_connection_t *c, uint8_t string_len,
                                   xcb_drawable_t drawable, xcb_gcontext_t gc,
                                   int16_t x, int16_t y, const char *string);

char *xcb_image_text_8_string(const xcb_image_text_8_request_t *R);

int xcb_image_text_8_string_length(const xcb_image_text_8_request_t *R);

xcb_generic_iterator_t
xcb_image_text_8_string_end(const xcb_image_text_8_request_t *R);

int xcb_image_text_16_sizeof(const void *_buffer);
# 10531 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_image_text_16_checked(xcb_connection_t *c, uint8_t string_len,
                          xcb_drawable_t drawable, xcb_gcontext_t gc, int16_t x,
                          int16_t y, const xcb_char2b_t *string);
# 10568 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_image_text_16(xcb_connection_t *c, uint8_t string_len,
                                    xcb_drawable_t drawable, xcb_gcontext_t gc,
                                    int16_t x, int16_t y,
                                    const xcb_char2b_t *string);

xcb_char2b_t *xcb_image_text_16_string(const xcb_image_text_16_request_t *R);

int xcb_image_text_16_string_length(const xcb_image_text_16_request_t *R);

xcb_char2b_iterator_t
xcb_image_text_16_string_iterator(const xcb_image_text_16_request_t *R);
# 10597 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_colormap_checked(xcb_connection_t *c,
                                              uint8_t alloc, xcb_colormap_t mid,
                                              xcb_window_t window,
                                              xcb_visualid_t visual);
# 10612 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_colormap(xcb_connection_t *c, uint8_t alloc,
                                      xcb_colormap_t mid, xcb_window_t window,
                                      xcb_visualid_t visual);
# 10630 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_colormap_checked(xcb_connection_t *c,
                                            xcb_colormap_t cmap);
# 10642 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_colormap(xcb_connection_t *c, xcb_colormap_t cmap);
# 10657 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_copy_colormap_and_free_checked(xcb_connection_t *c,
                                                     xcb_colormap_t mid,
                                                     xcb_colormap_t src_cmap);
# 10670 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_copy_colormap_and_free(xcb_connection_t *c,
                                             xcb_colormap_t mid,
                                             xcb_colormap_t src_cmap);
# 10686 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_install_colormap_checked(xcb_connection_t *c,
                                               xcb_colormap_t cmap);
# 10698 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_install_colormap(xcb_connection_t *c,
                                       xcb_colormap_t cmap);
# 10713 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_uninstall_colormap_checked(xcb_connection_t *c,
                                                 xcb_colormap_t cmap);
# 10725 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_uninstall_colormap(xcb_connection_t *c,
                                         xcb_colormap_t cmap);

int xcb_list_installed_colormaps_sizeof(const void *_buffer);
# 10740 "/usr/include/xcb/xproto.h" 3 4
xcb_list_installed_colormaps_cookie_t
xcb_list_installed_colormaps(xcb_connection_t *c, xcb_window_t window);
# 10755 "/usr/include/xcb/xproto.h" 3 4
xcb_list_installed_colormaps_cookie_t
xcb_list_installed_colormaps_unchecked(xcb_connection_t *c,
                                       xcb_window_t window);

xcb_colormap_t *xcb_list_installed_colormaps_cmaps(
    const xcb_list_installed_colormaps_reply_t *R);

int xcb_list_installed_colormaps_cmaps_length(
    const xcb_list_installed_colormaps_reply_t *R);

xcb_generic_iterator_t xcb_list_installed_colormaps_cmaps_end(
    const xcb_list_installed_colormaps_reply_t *R);
# 10782 "/usr/include/xcb/xproto.h" 3 4
xcb_list_installed_colormaps_reply_t *
xcb_list_installed_colormaps_reply(xcb_connection_t *c,
                                   xcb_list_installed_colormaps_cookie_t cookie,
                                   xcb_generic_error_t **e);
# 10804 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_cookie_t xcb_alloc_color(xcb_connection_t *c,
                                         xcb_colormap_t cmap, uint16_t red,
                                         uint16_t green, uint16_t blue);
# 10831 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_cookie_t xcb_alloc_color_unchecked(xcb_connection_t *c,
                                                   xcb_colormap_t cmap,
                                                   uint16_t red, uint16_t green,
                                                   uint16_t blue);
# 10852 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_reply_t *xcb_alloc_color_reply(xcb_connection_t *c,
                                               xcb_alloc_color_cookie_t cookie,
                                               xcb_generic_error_t **e);

int xcb_alloc_named_color_sizeof(const void *_buffer);
# 10868 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_named_color_cookie_t xcb_alloc_named_color(xcb_connection_t *c,
                                                     xcb_colormap_t cmap,
                                                     uint16_t name_len,
                                                     const char *name);
# 10885 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_named_color_cookie_t
xcb_alloc_named_color_unchecked(xcb_connection_t *c, xcb_colormap_t cmap,
                                uint16_t name_len, const char *name);
# 10905 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_named_color_reply_t *
xcb_alloc_named_color_reply(xcb_connection_t *c,
                            xcb_alloc_named_color_cookie_t cookie,
                            xcb_generic_error_t **e);

int xcb_alloc_color_cells_sizeof(const void *_buffer);
# 10921 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_cells_cookie_t
xcb_alloc_color_cells(xcb_connection_t *c, uint8_t contiguous,
                      xcb_colormap_t cmap, uint16_t colors, uint16_t planes);
# 10939 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_cells_cookie_t
xcb_alloc_color_cells_unchecked(xcb_connection_t *c, uint8_t contiguous,
                                xcb_colormap_t cmap, uint16_t colors,
                                uint16_t planes);

uint32_t *xcb_alloc_color_cells_pixels(const xcb_alloc_color_cells_reply_t *R);

int xcb_alloc_color_cells_pixels_length(const xcb_alloc_color_cells_reply_t *R);

xcb_generic_iterator_t
xcb_alloc_color_cells_pixels_end(const xcb_alloc_color_cells_reply_t *R);

uint32_t *xcb_alloc_color_cells_masks(const xcb_alloc_color_cells_reply_t *R);

int xcb_alloc_color_cells_masks_length(const xcb_alloc_color_cells_reply_t *R);

xcb_generic_iterator_t
xcb_alloc_color_cells_masks_end(const xcb_alloc_color_cells_reply_t *R);
# 10978 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_cells_reply_t *
xcb_alloc_color_cells_reply(xcb_connection_t *c,
                            xcb_alloc_color_cells_cookie_t cookie,
                            xcb_generic_error_t **e);

int xcb_alloc_color_planes_sizeof(const void *_buffer);
# 10994 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_planes_cookie_t
xcb_alloc_color_planes(xcb_connection_t *c, uint8_t contiguous,
                       xcb_colormap_t cmap, uint16_t colors, uint16_t reds,
                       uint16_t greens, uint16_t blues);
# 11014 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_planes_cookie_t xcb_alloc_color_planes_unchecked(
    xcb_connection_t *c, uint8_t contiguous, xcb_colormap_t cmap,
    uint16_t colors, uint16_t reds, uint16_t greens, uint16_t blues);

uint32_t *
xcb_alloc_color_planes_pixels(const xcb_alloc_color_planes_reply_t *R);

int xcb_alloc_color_planes_pixels_length(
    const xcb_alloc_color_planes_reply_t *R);

xcb_generic_iterator_t
xcb_alloc_color_planes_pixels_end(const xcb_alloc_color_planes_reply_t *R);
# 11046 "/usr/include/xcb/xproto.h" 3 4
xcb_alloc_color_planes_reply_t *
xcb_alloc_color_planes_reply(xcb_connection_t *c,
                             xcb_alloc_color_planes_cookie_t cookie,
                             xcb_generic_error_t **e);

int xcb_free_colors_sizeof(const void *_buffer, uint32_t pixels_len);
# 11066 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_colors_checked(xcb_connection_t *c,
                                          xcb_colormap_t cmap,
                                          uint32_t plane_mask,
                                          uint32_t pixels_len,
                                          const uint32_t *pixels);
# 11081 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_colors(xcb_connection_t *c, xcb_colormap_t cmap,
                                  uint32_t plane_mask, uint32_t pixels_len,
                                  const uint32_t *pixels);

uint32_t *xcb_free_colors_pixels(const xcb_free_colors_request_t *R);

int xcb_free_colors_pixels_length(const xcb_free_colors_request_t *R);

xcb_generic_iterator_t
xcb_free_colors_pixels_end(const xcb_free_colors_request_t *R);
# 11105 "/usr/include/xcb/xproto.h" 3 4
void xcb_coloritem_next(xcb_coloritem_iterator_t *i);
# 11117 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_coloritem_end(xcb_coloritem_iterator_t i);

int xcb_store_colors_sizeof(const void *_buffer, uint32_t items_len);
# 11135 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_store_colors_checked(xcb_connection_t *c,
                                           xcb_colormap_t cmap,
                                           uint32_t items_len,
                                           const xcb_coloritem_t *items);
# 11149 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_store_colors(xcb_connection_t *c, xcb_colormap_t cmap,
                                   uint32_t items_len,
                                   const xcb_coloritem_t *items);

xcb_coloritem_t *xcb_store_colors_items(const xcb_store_colors_request_t *R);

int xcb_store_colors_items_length(const xcb_store_colors_request_t *R);

xcb_coloritem_iterator_t
xcb_store_colors_items_iterator(const xcb_store_colors_request_t *R);

int xcb_store_named_color_sizeof(const void *_buffer);
# 11178 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_store_named_color_checked(xcb_connection_t *c, uint8_t flags,
                              xcb_colormap_t cmap, uint32_t pixel,
                              uint16_t name_len, const char *name);
# 11194 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_store_named_color(xcb_connection_t *c, uint8_t flags,
                                        xcb_colormap_t cmap, uint32_t pixel,
                                        uint16_t name_len, const char *name);

char *xcb_store_named_color_name(const xcb_store_named_color_request_t *R);

int xcb_store_named_color_name_length(const xcb_store_named_color_request_t *R);

xcb_generic_iterator_t
xcb_store_named_color_name_end(const xcb_store_named_color_request_t *R);
# 11219 "/usr/include/xcb/xproto.h" 3 4
void xcb_rgb_next(xcb_rgb_iterator_t *i);
# 11231 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_rgb_end(xcb_rgb_iterator_t i);

int xcb_query_colors_sizeof(const void *_buffer, uint32_t pixels_len);
# 11246 "/usr/include/xcb/xproto.h" 3 4
xcb_query_colors_cookie_t xcb_query_colors(xcb_connection_t *c,
                                           xcb_colormap_t cmap,
                                           uint32_t pixels_len,
                                           const uint32_t *pixels);
# 11263 "/usr/include/xcb/xproto.h" 3 4
xcb_query_colors_cookie_t xcb_query_colors_unchecked(xcb_connection_t *c,
                                                     xcb_colormap_t cmap,
                                                     uint32_t pixels_len,
                                                     const uint32_t *pixels);

xcb_rgb_t *xcb_query_colors_colors(const xcb_query_colors_reply_t *R);

int xcb_query_colors_colors_length(const xcb_query_colors_reply_t *R);

xcb_rgb_iterator_t
xcb_query_colors_colors_iterator(const xcb_query_colors_reply_t *R);
# 11292 "/usr/include/xcb/xproto.h" 3 4
xcb_query_colors_reply_t *
xcb_query_colors_reply(xcb_connection_t *c, xcb_query_colors_cookie_t cookie,
                       xcb_generic_error_t **e);

int xcb_lookup_color_sizeof(const void *_buffer);
# 11308 "/usr/include/xcb/xproto.h" 3 4
xcb_lookup_color_cookie_t xcb_lookup_color(xcb_connection_t *c,
                                           xcb_colormap_t cmap,
                                           uint16_t name_len, const char *name);
# 11325 "/usr/include/xcb/xproto.h" 3 4
xcb_lookup_color_cookie_t xcb_lookup_color_unchecked(xcb_connection_t *c,
                                                     xcb_colormap_t cmap,
                                                     uint16_t name_len,
                                                     const char *name);
# 11345 "/usr/include/xcb/xproto.h" 3 4
xcb_lookup_color_reply_t *
xcb_lookup_color_reply(xcb_connection_t *c, xcb_lookup_color_cookie_t cookie,
                       xcb_generic_error_t **e);
# 11361 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_cursor_checked(
    xcb_connection_t *c, xcb_cursor_t cid, xcb_pixmap_t source,
    xcb_pixmap_t mask, uint16_t fore_red, uint16_t fore_green,
    uint16_t fore_blue, uint16_t back_red, uint16_t back_green,
    uint16_t back_blue, uint16_t x, uint16_t y);
# 11383 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_cursor(xcb_connection_t *c, xcb_cursor_t cid,
                                    xcb_pixmap_t source, xcb_pixmap_t mask,
                                    uint16_t fore_red, uint16_t fore_green,
                                    uint16_t fore_blue, uint16_t back_red,
                                    uint16_t back_green, uint16_t back_blue,
                                    uint16_t x, uint16_t y);
# 11430 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_glyph_cursor_checked(
    xcb_connection_t *c, xcb_cursor_t cid, xcb_font_t source_font,
    xcb_font_t mask_font, uint16_t source_char, uint16_t mask_char,
    uint16_t fore_red, uint16_t fore_green, uint16_t fore_blue,
    uint16_t back_red, uint16_t back_green, uint16_t back_blue);
# 11474 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_create_glyph_cursor(
    xcb_connection_t *c, xcb_cursor_t cid, xcb_font_t source_font,
    xcb_font_t mask_font, uint16_t source_char, uint16_t mask_char,
    uint16_t fore_red, uint16_t fore_green, uint16_t fore_blue,
    uint16_t back_red, uint16_t back_green, uint16_t back_blue);
# 11502 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_cursor_checked(xcb_connection_t *c,
                                          xcb_cursor_t cursor);
# 11517 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_free_cursor(xcb_connection_t *c, xcb_cursor_t cursor);
# 11532 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_recolor_cursor_checked(xcb_connection_t *c, xcb_cursor_t cursor,
                           uint16_t fore_red, uint16_t fore_green,
                           uint16_t fore_blue, uint16_t back_red,
                           uint16_t back_green, uint16_t back_blue);
# 11550 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_recolor_cursor(xcb_connection_t *c, xcb_cursor_t cursor,
                                     uint16_t fore_red, uint16_t fore_green,
                                     uint16_t fore_blue, uint16_t back_red,
                                     uint16_t back_green, uint16_t back_blue);
# 11568 "/usr/include/xcb/xproto.h" 3 4
xcb_query_best_size_cookie_t
xcb_query_best_size(xcb_connection_t *c, uint8_t _class,
                    xcb_drawable_t drawable, uint16_t width, uint16_t height);
# 11586 "/usr/include/xcb/xproto.h" 3 4
xcb_query_best_size_cookie_t
xcb_query_best_size_unchecked(xcb_connection_t *c, uint8_t _class,
                              xcb_drawable_t drawable, uint16_t width,
                              uint16_t height);
# 11607 "/usr/include/xcb/xproto.h" 3 4
xcb_query_best_size_reply_t *
xcb_query_best_size_reply(xcb_connection_t *c,
                          xcb_query_best_size_cookie_t cookie,
                          xcb_generic_error_t **e);

int xcb_query_extension_sizeof(const void *_buffer);
# 11635 "/usr/include/xcb/xproto.h" 3 4
xcb_query_extension_cookie_t
xcb_query_extension(xcb_connection_t *c, uint16_t name_len, const char *name);
# 11663 "/usr/include/xcb/xproto.h" 3 4
xcb_query_extension_cookie_t xcb_query_extension_unchecked(xcb_connection_t *c,
                                                           uint16_t name_len,
                                                           const char *name);
# 11682 "/usr/include/xcb/xproto.h" 3 4
xcb_query_extension_reply_t *
xcb_query_extension_reply(xcb_connection_t *c,
                          xcb_query_extension_cookie_t cookie,
                          xcb_generic_error_t **e);

int xcb_list_extensions_sizeof(const void *_buffer);
# 11698 "/usr/include/xcb/xproto.h" 3 4
xcb_list_extensions_cookie_t xcb_list_extensions(xcb_connection_t *c);
# 11712 "/usr/include/xcb/xproto.h" 3 4
xcb_list_extensions_cookie_t xcb_list_extensions_unchecked(xcb_connection_t *c);

int xcb_list_extensions_names_length(const xcb_list_extensions_reply_t *R);

xcb_str_iterator_t
xcb_list_extensions_names_iterator(const xcb_list_extensions_reply_t *R);
# 11735 "/usr/include/xcb/xproto.h" 3 4
xcb_list_extensions_reply_t *
xcb_list_extensions_reply(xcb_connection_t *c,
                          xcb_list_extensions_cookie_t cookie,
                          xcb_generic_error_t **e);

int xcb_change_keyboard_mapping_sizeof(const void *_buffer);
# 11754 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_keyboard_mapping_checked(
    xcb_connection_t *c, uint8_t keycode_count, xcb_keycode_t first_keycode,
    uint8_t keysyms_per_keycode, const xcb_keysym_t *keysyms);
# 11769 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_keyboard_mapping(xcb_connection_t *c,
                                              uint8_t keycode_count,
                                              xcb_keycode_t first_keycode,
                                              uint8_t keysyms_per_keycode,
                                              const xcb_keysym_t *keysyms);

xcb_keysym_t *xcb_change_keyboard_mapping_keysyms(
    const xcb_change_keyboard_mapping_request_t *R);

int xcb_change_keyboard_mapping_keysyms_length(
    const xcb_change_keyboard_mapping_request_t *R);

xcb_generic_iterator_t xcb_change_keyboard_mapping_keysyms_end(
    const xcb_change_keyboard_mapping_request_t *R);

int xcb_get_keyboard_mapping_sizeof(const void *_buffer);
# 11796 "/usr/include/xcb/xproto.h" 3 4
xcb_get_keyboard_mapping_cookie_t
xcb_get_keyboard_mapping(xcb_connection_t *c, xcb_keycode_t first_keycode,
                         uint8_t count);
# 11812 "/usr/include/xcb/xproto.h" 3 4
xcb_get_keyboard_mapping_cookie_t
xcb_get_keyboard_mapping_unchecked(xcb_connection_t *c,
                                   xcb_keycode_t first_keycode, uint8_t count);

xcb_keysym_t *
xcb_get_keyboard_mapping_keysyms(const xcb_get_keyboard_mapping_reply_t *R);

int xcb_get_keyboard_mapping_keysyms_length(
    const xcb_get_keyboard_mapping_reply_t *R);

xcb_generic_iterator_t
xcb_get_keyboard_mapping_keysyms_end(const xcb_get_keyboard_mapping_reply_t *R);
# 11840 "/usr/include/xcb/xproto.h" 3 4
xcb_get_keyboard_mapping_reply_t *
xcb_get_keyboard_mapping_reply(xcb_connection_t *c,
                               xcb_get_keyboard_mapping_cookie_t cookie,
                               xcb_generic_error_t **e);

int xcb_change_keyboard_control_value_list_serialize(
    void **_buffer, uint32_t value_mask,
    const xcb_change_keyboard_control_value_list_t *_aux);

int xcb_change_keyboard_control_value_list_unpack(
    const void *_buffer, uint32_t value_mask,
    xcb_change_keyboard_control_value_list_t *_aux);

int xcb_change_keyboard_control_value_list_sizeof(const void *_buffer,
                                                  uint32_t value_mask);

int xcb_change_keyboard_control_sizeof(const void *_buffer);
# 11873 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_keyboard_control_checked(xcb_connection_t *c,
                                                      uint32_t value_mask,
                                                      const void *value_list);
# 11886 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_keyboard_control(xcb_connection_t *c,
                                              uint32_t value_mask,
                                              const void *value_list);
# 11902 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_keyboard_control_aux_checked(
    xcb_connection_t *c, uint32_t value_mask,
    const xcb_change_keyboard_control_value_list_t *value_list);
# 11915 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_keyboard_control_aux(
    xcb_connection_t *c, uint32_t value_mask,
    const xcb_change_keyboard_control_value_list_t *value_list);

void *xcb_change_keyboard_control_value_list(
    const xcb_change_keyboard_control_request_t *R);
# 11931 "/usr/include/xcb/xproto.h" 3 4
xcb_get_keyboard_control_cookie_t xcb_get_keyboard_control(xcb_connection_t *c);
# 11945 "/usr/include/xcb/xproto.h" 3 4
xcb_get_keyboard_control_cookie_t
xcb_get_keyboard_control_unchecked(xcb_connection_t *c);
# 11962 "/usr/include/xcb/xproto.h" 3 4
xcb_get_keyboard_control_reply_t *
xcb_get_keyboard_control_reply(xcb_connection_t *c,
                               xcb_get_keyboard_control_cookie_t cookie,
                               xcb_generic_error_t **e);
# 11978 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_bell_checked(xcb_connection_t *c, int8_t percent);
# 11990 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_bell(xcb_connection_t *c, int8_t percent);
# 12005 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_pointer_control_checked(
    xcb_connection_t *c, int16_t acceleration_numerator,
    int16_t acceleration_denominator, int16_t threshold,
    uint8_t do_acceleration, uint8_t do_threshold);
# 12021 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t
xcb_change_pointer_control(xcb_connection_t *c, int16_t acceleration_numerator,
                           int16_t acceleration_denominator, int16_t threshold,
                           uint8_t do_acceleration, uint8_t do_threshold);
# 12037 "/usr/include/xcb/xproto.h" 3 4
xcb_get_pointer_control_cookie_t xcb_get_pointer_control(xcb_connection_t *c);
# 12051 "/usr/include/xcb/xproto.h" 3 4
xcb_get_pointer_control_cookie_t
xcb_get_pointer_control_unchecked(xcb_connection_t *c);
# 12068 "/usr/include/xcb/xproto.h" 3 4
xcb_get_pointer_control_reply_t *
xcb_get_pointer_control_reply(xcb_connection_t *c,
                              xcb_get_pointer_control_cookie_t cookie,
                              xcb_generic_error_t **e);
# 12084 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_screen_saver_checked(xcb_connection_t *c,
                                               int16_t timeout,
                                               int16_t interval,
                                               uint8_t prefer_blanking,
                                               uint8_t allow_exposures);
# 12099 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_screen_saver(xcb_connection_t *c, int16_t timeout,
                                       int16_t interval,
                                       uint8_t prefer_blanking,
                                       uint8_t allow_exposures);
# 12114 "/usr/include/xcb/xproto.h" 3 4
xcb_get_screen_saver_cookie_t xcb_get_screen_saver(xcb_connection_t *c);
# 12128 "/usr/include/xcb/xproto.h" 3 4
xcb_get_screen_saver_cookie_t
xcb_get_screen_saver_unchecked(xcb_connection_t *c);
# 12145 "/usr/include/xcb/xproto.h" 3 4
xcb_get_screen_saver_reply_t *
xcb_get_screen_saver_reply(xcb_connection_t *c,
                           xcb_get_screen_saver_cookie_t cookie,
                           xcb_generic_error_t **e);

int xcb_change_hosts_sizeof(const void *_buffer);
# 12164 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_hosts_checked(xcb_connection_t *c, uint8_t mode,
                                           uint8_t family, uint16_t address_len,
                                           const uint8_t *address);
# 12179 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_change_hosts(xcb_connection_t *c, uint8_t mode,
                                   uint8_t family, uint16_t address_len,
                                   const uint8_t *address);

uint8_t *xcb_change_hosts_address(const xcb_change_hosts_request_t *R);

int xcb_change_hosts_address_length(const xcb_change_hosts_request_t *R);

xcb_generic_iterator_t
xcb_change_hosts_address_end(const xcb_change_hosts_request_t *R);

int xcb_host_sizeof(const void *_buffer);

uint8_t *xcb_host_address(const xcb_host_t *R);

int xcb_host_address_length(const xcb_host_t *R);

xcb_generic_iterator_t xcb_host_address_end(const xcb_host_t *R);
# 12215 "/usr/include/xcb/xproto.h" 3 4
void xcb_host_next(xcb_host_iterator_t *i);
# 12227 "/usr/include/xcb/xproto.h" 3 4
xcb_generic_iterator_t xcb_host_end(xcb_host_iterator_t i);

int xcb_list_hosts_sizeof(const void *_buffer);
# 12241 "/usr/include/xcb/xproto.h" 3 4
xcb_list_hosts_cookie_t xcb_list_hosts(xcb_connection_t *c);
# 12255 "/usr/include/xcb/xproto.h" 3 4
xcb_list_hosts_cookie_t xcb_list_hosts_unchecked(xcb_connection_t *c);

int xcb_list_hosts_hosts_length(const xcb_list_hosts_reply_t *R);

xcb_host_iterator_t
xcb_list_hosts_hosts_iterator(const xcb_list_hosts_reply_t *R);
# 12278 "/usr/include/xcb/xproto.h" 3 4
xcb_list_hosts_reply_t *xcb_list_hosts_reply(xcb_connection_t *c,
                                             xcb_list_hosts_cookie_t cookie,
                                             xcb_generic_error_t **e);
# 12294 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_access_control_checked(xcb_connection_t *c,
                                                 uint8_t mode);
# 12306 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_access_control(xcb_connection_t *c, uint8_t mode);
# 12321 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_close_down_mode_checked(xcb_connection_t *c,
                                                  uint8_t mode);
# 12333 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_set_close_down_mode(xcb_connection_t *c, uint8_t mode);
# 12354 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_kill_client_checked(xcb_connection_t *c,
                                          uint32_t resource);
# 12372 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_kill_client(xcb_connection_t *c, uint32_t resource);

int xcb_rotate_properties_sizeof(const void *_buffer);
# 12390 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_rotate_properties_checked(xcb_connection_t *c,
                                                xcb_window_t window,
                                                uint16_t atoms_len,
                                                int16_t delta,
                                                const xcb_atom_t *atoms);
# 12405 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_rotate_properties(xcb_connection_t *c,
                                        xcb_window_t window, uint16_t atoms_len,
                                        int16_t delta, const xcb_atom_t *atoms);

xcb_atom_t *
xcb_rotate_properties_atoms(const xcb_rotate_properties_request_t *R);

int xcb_rotate_properties_atoms_length(
    const xcb_rotate_properties_request_t *R);

xcb_generic_iterator_t
xcb_rotate_properties_atoms_end(const xcb_rotate_properties_request_t *R);
# 12432 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_force_screen_saver_checked(xcb_connection_t *c,
                                                 uint8_t mode);
# 12444 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_force_screen_saver(xcb_connection_t *c, uint8_t mode);

int xcb_set_pointer_mapping_sizeof(const void *_buffer);
# 12459 "/usr/include/xcb/xproto.h" 3 4
xcb_set_pointer_mapping_cookie_t xcb_set_pointer_mapping(xcb_connection_t *c,
                                                         uint8_t map_len,
                                                         const uint8_t *map);
# 12475 "/usr/include/xcb/xproto.h" 3 4
xcb_set_pointer_mapping_cookie_t
xcb_set_pointer_mapping_unchecked(xcb_connection_t *c, uint8_t map_len,
                                  const uint8_t *map);
# 12494 "/usr/include/xcb/xproto.h" 3 4
xcb_set_pointer_mapping_reply_t *
xcb_set_pointer_mapping_reply(xcb_connection_t *c,
                              xcb_set_pointer_mapping_cookie_t cookie,
                              xcb_generic_error_t **e);

int xcb_get_pointer_mapping_sizeof(const void *_buffer);
# 12510 "/usr/include/xcb/xproto.h" 3 4
xcb_get_pointer_mapping_cookie_t xcb_get_pointer_mapping(xcb_connection_t *c);
# 12524 "/usr/include/xcb/xproto.h" 3 4
xcb_get_pointer_mapping_cookie_t
xcb_get_pointer_mapping_unchecked(xcb_connection_t *c);

uint8_t *xcb_get_pointer_mapping_map(const xcb_get_pointer_mapping_reply_t *R);

int xcb_get_pointer_mapping_map_length(
    const xcb_get_pointer_mapping_reply_t *R);

xcb_generic_iterator_t
xcb_get_pointer_mapping_map_end(const xcb_get_pointer_mapping_reply_t *R);
# 12550 "/usr/include/xcb/xproto.h" 3 4
xcb_get_pointer_mapping_reply_t *
xcb_get_pointer_mapping_reply(xcb_connection_t *c,
                              xcb_get_pointer_mapping_cookie_t cookie,
                              xcb_generic_error_t **e);

int xcb_set_modifier_mapping_sizeof(const void *_buffer);
# 12566 "/usr/include/xcb/xproto.h" 3 4
xcb_set_modifier_mapping_cookie_t
xcb_set_modifier_mapping(xcb_connection_t *c, uint8_t keycodes_per_modifier,
                         const xcb_keycode_t *keycodes);
# 12582 "/usr/include/xcb/xproto.h" 3 4
xcb_set_modifier_mapping_cookie_t
xcb_set_modifier_mapping_unchecked(xcb_connection_t *c,
                                   uint8_t keycodes_per_modifier,
                                   const xcb_keycode_t *keycodes);
# 12601 "/usr/include/xcb/xproto.h" 3 4
xcb_set_modifier_mapping_reply_t *
xcb_set_modifier_mapping_reply(xcb_connection_t *c,
                               xcb_set_modifier_mapping_cookie_t cookie,
                               xcb_generic_error_t **e);

int xcb_get_modifier_mapping_sizeof(const void *_buffer);
# 12617 "/usr/include/xcb/xproto.h" 3 4
xcb_get_modifier_mapping_cookie_t xcb_get_modifier_mapping(xcb_connection_t *c);
# 12631 "/usr/include/xcb/xproto.h" 3 4
xcb_get_modifier_mapping_cookie_t
xcb_get_modifier_mapping_unchecked(xcb_connection_t *c);

xcb_keycode_t *
xcb_get_modifier_mapping_keycodes(const xcb_get_modifier_mapping_reply_t *R);

int xcb_get_modifier_mapping_keycodes_length(
    const xcb_get_modifier_mapping_reply_t *R);

xcb_generic_iterator_t xcb_get_modifier_mapping_keycodes_end(
    const xcb_get_modifier_mapping_reply_t *R);
# 12657 "/usr/include/xcb/xproto.h" 3 4
xcb_get_modifier_mapping_reply_t *
xcb_get_modifier_mapping_reply(xcb_connection_t *c,
                               xcb_get_modifier_mapping_cookie_t cookie,
                               xcb_generic_error_t **e);
# 12673 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_no_operation_checked(xcb_connection_t *c);
# 12684 "/usr/include/xcb/xproto.h" 3 4
xcb_void_cookie_t xcb_no_operation(xcb_connection_t *c);
# 206 "/usr/include/xcb/xcb.h" 2 3 4
# 228 "/usr/include/xcb/xcb.h" 3 4
typedef struct xcb_auth_info_t {
  int namelen;
  char *name;
  int datalen;
  char *data;
} xcb_auth_info_t;
# 246 "/usr/include/xcb/xcb.h" 3 4
int xcb_flush(xcb_connection_t *c);
# 263 "/usr/include/xcb/xcb.h" 3 4
uint32_t xcb_get_maximum_request_length(xcb_connection_t *c);
# 282 "/usr/include/xcb/xcb.h" 3 4
void xcb_prefetch_maximum_request_length(xcb_connection_t *c);
# 296 "/usr/include/xcb/xcb.h" 3 4
xcb_generic_event_t *xcb_wait_for_event(xcb_connection_t *c);
# 309 "/usr/include/xcb/xcb.h" 3 4
xcb_generic_event_t *xcb_poll_for_event(xcb_connection_t *c);
# 325 "/usr/include/xcb/xcb.h" 3 4
xcb_generic_event_t *xcb_poll_for_queued_event(xcb_connection_t *c);

typedef struct xcb_special_event xcb_special_event_t;

xcb_generic_event_t *xcb_poll_for_special_event(xcb_connection_t *c,
                                                xcb_special_event_t *se);

xcb_generic_event_t *xcb_wait_for_special_event(xcb_connection_t *c,
                                                xcb_special_event_t *se);

typedef struct xcb_extension_t xcb_extension_t;

xcb_special_event_t *xcb_register_for_special_xge(xcb_connection_t *c,
                                                  xcb_extension_t *ext,
                                                  uint32_t eid,
                                                  uint32_t *stamp);

void xcb_unregister_for_special_event(xcb_connection_t *c,
                                      xcb_special_event_t *se);
# 375 "/usr/include/xcb/xcb.h" 3 4
xcb_generic_error_t *xcb_request_check(xcb_connection_t *c,
                                       xcb_void_cookie_t cookie);
# 391 "/usr/include/xcb/xcb.h" 3 4
void xcb_discard_reply(xcb_connection_t *c, unsigned int sequence);
# 412 "/usr/include/xcb/xcb.h" 3 4
void xcb_discard_reply64(xcb_connection_t *c, uint64_t sequence);
# 432 "/usr/include/xcb/xcb.h" 3 4
const struct xcb_query_extension_reply_t *
xcb_get_extension_data(xcb_connection_t *c, xcb_extension_t *ext);
# 445 "/usr/include/xcb/xcb.h" 3 4
void xcb_prefetch_extension_data(xcb_connection_t *c, xcb_extension_t *ext);
# 468 "/usr/include/xcb/xcb.h" 3 4
const struct xcb_setup_t *xcb_get_setup(xcb_connection_t *c);
# 478 "/usr/include/xcb/xcb.h" 3 4
int xcb_get_file_descriptor(xcb_connection_t *c);
# 498 "/usr/include/xcb/xcb.h" 3 4
int xcb_connection_has_error(xcb_connection_t *c);
# 517 "/usr/include/xcb/xcb.h" 3 4
xcb_connection_t *xcb_connect_to_fd(int fd, xcb_auth_info_t *auth_info);
# 526 "/usr/include/xcb/xcb.h" 3 4
void xcb_disconnect(xcb_connection_t *c);
# 548 "/usr/include/xcb/xcb.h" 3 4
int xcb_parse_display(const char *name, char **host, int *display, int *screen);
# 567 "/usr/include/xcb/xcb.h" 3 4
xcb_connection_t *xcb_connect(const char *displayname, int *screenp);
# 586 "/usr/include/xcb/xcb.h" 3 4
xcb_connection_t *xcb_connect_to_display_with_auth_info(const char *display,
                                                        xcb_auth_info_t *auth,
                                                        int *screen);
# 599 "/usr/include/xcb/xcb.h" 3 4
uint32_t xcb_generate_id(xcb_connection_t *c);
# 613 "/usr/include/xcb/xcb.h" 3 4
uint64_t xcb_total_read(xcb_connection_t *c);
# 628 "/usr/include/xcb/xcb.h" 3 4
uint64_t xcb_total_written(xcb_connection_t *c);
# 8 "data.h" 2

# 9 "data.h"
typedef struct client client_t;
typedef struct layout layout_t;
typedef struct desktop desktop_t;
typedef struct keybind keybind_t;
typedef struct handler_func handler_func_t;

enum split_direction { SPLIT_VERTICAL, SPLIT_HORIZONTAL };
enum visibility { SHOWN, HIDDEN };
enum motion_type { MOTION_NONE, MOTION_DRAGGING, MOTION_RESIZING };

struct client {
  xcb_window_t window;
  float split_ratio;
  enum split_direction split_direction;
  enum motion_type motion;
  enum visibility visibility;
  int16_t x, y;
  uint16_t w, h;
};

enum layout_type { LAYOUT_TILING, LAYOUT_FLOATING };

struct layout {
  enum layout_type type;

  void (*reposition)(desktop_t *d);

  void (*move_left)(desktop_t *d);
  void (*move_right)(desktop_t *d);
  void (*move_bottom)(desktop_t *d);
  void (*move_top)(desktop_t *d);
};

struct desktop {
  int i;

  layout_t layout;
  client_t *focused;

  list_t *clients;
  stack_t *focus_stack;
};

struct arg {
  const int i;
  const char **v;
};

struct keybind {
  unsigned int mod;
  xcb_keysym_t keysym;
  void (*func)(const struct arg arg);
  const struct arg arg;
};

struct handler_func {
  uint32_t request;
  void (*func)(xcb_generic_event_t *ev);
};

client_t *new_client(xcb_window_t w);
client_t *get_client(xcb_window_t w);
desktop_t *new_desktop(layout_t l);
desktop_t *get_desktop(int i);
void free_desktop(desktop_t *list);
# 5 "config.h" 2
# 1 "kiwi.h" 1

# 1 "/usr/include/xcb/xcb_keysyms.h" 1 3 4
# 12 "/usr/include/xcb/xcb_keysyms.h" 3 4

# 12 "/usr/include/xcb/xcb_keysyms.h" 3 4
typedef struct _XCBKeySymbols xcb_key_symbols_t;

xcb_key_symbols_t *xcb_key_symbols_alloc(xcb_connection_t *c);

void xcb_key_symbols_free(xcb_key_symbols_t *syms);

xcb_keysym_t xcb_key_symbols_get_keysym(xcb_key_symbols_t *syms,
                                        xcb_keycode_t keycode, int col);
# 33 "/usr/include/xcb/xcb_keysyms.h" 3 4
xcb_keycode_t *xcb_key_symbols_get_keycode(xcb_key_symbols_t *syms,
                                           xcb_keysym_t keysym);

xcb_keysym_t xcb_key_press_lookup_keysym(xcb_key_symbols_t *syms,
                                         xcb_key_press_event_t *event, int col);

xcb_keysym_t xcb_key_release_lookup_keysym(xcb_key_symbols_t *syms,
                                           xcb_key_release_event_t *event,
                                           int col);

int xcb_refresh_keyboard_mapping(xcb_key_symbols_t *syms,
                                 xcb_mapping_notify_event_t *event);

int xcb_is_keypad_key(xcb_keysym_t keysym);

int xcb_is_private_keypad_key(xcb_keysym_t keysym);

int xcb_is_cursor_key(xcb_keysym_t keysym);

int xcb_is_pf_key(xcb_keysym_t keysym);

int xcb_is_function_key(xcb_keysym_t keysym);

int xcb_is_misc_function_key(xcb_keysym_t keysym);

int xcb_is_modifier_key(xcb_keysym_t keysym);
# 9 "kiwi.h" 2

# 10 "kiwi.h"
extern list_t *desktops;
extern desktop_t *focdesk;
extern xcb_connection_t *dpy;
extern xcb_screen_t *scr;

void killclient(const struct arg arg);
void spawn(const struct arg arg);
void closewm(const struct arg arg);
void send_to(const struct arg arg);
void send_rel(const struct arg arg);
void move_to(const struct arg arg);
void move_rel(const struct arg arg);

void focus_client(client_t *c);
void move_client(client_t *c, int16_t x, int16_t y,
# 26 "kiwi.h" 3 4
                 _Bool
# 26 "kiwi.h"
                     save);
void resize_client(client_t *c, uint16_t width, uint16_t height);
void hide_client(client_t *c);
void show_client(client_t *c);
void focus_desktop(desktop_t *desk);
void send_client(client_t *c, int i);
void setWindowDimensions(xcb_drawable_t window);
void setWindowPosition(xcb_drawable_t window);
void setBorderWidth(xcb_drawable_t window);
void setBorderColor(xcb_drawable_t window, int focus);
# 6 "config.h" 2
# 1 "layouts.h" 1

extern const layout_t tiling_layout;
# 7 "config.h" 2
# 1 "/usr/include/X11/keysym.h" 1 3 4
# 73 "/usr/include/X11/keysym.h" 3 4
# 1 "/usr/include/X11/keysymdef.h" 1 3 4
# 74 "/usr/include/X11/keysym.h" 2 3 4
# 8 "config.h" 2
# 61 "config.h"
static const char *termcmd[] = {"st",
# 61 "config.h" 3 4
                                ((void *)0)
# 61 "config.h"
};
static const char *menucmd[] = {"dmenu_run",
# 62 "config.h" 3 4
                                ((void *)0)
# 62 "config.h"
};
# 72 "config.h"
static keybind_t keys[] = {
    {XCB_MOD_MASK_4,
# 73 "config.h" 3 4
     0xff0d
# 73 "config.h"
     ,
     spawn,
     {.v = termcmd}},
    {XCB_MOD_MASK_4,
# 74 "config.h" 3 4
     0x0020
# 74 "config.h"
     ,
     spawn,
     {.v = menucmd}},
    {XCB_MOD_MASK_4,
# 75 "config.h" 3 4
     0x0077
# 75 "config.h"
     ,
     killclient,
# 75 "config.h" 3 4
     ((void *)0)
# 75 "config.h"
    },

    {XCB_MOD_MASK_4,
# 77 "config.h" 3 4
     0x006c
# 77 "config.h"
     ,
     move_rel,
     {.i = 1}},
    {XCB_MOD_MASK_4,
# 78 "config.h" 3 4
     0x0068
# 78 "config.h"
     ,
     move_rel,
     {.i = -1}},
    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 79 "config.h" 3 4
     0x006c
# 79 "config.h"
     ,
     send_rel,
     {.i = 1}},
    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 80 "config.h" 3 4
     0x0068
# 80 "config.h"
     ,
     send_rel,
     {.i = -1}},

    {XCB_MOD_MASK_4,
# 82 "config.h" 3 4
     0x0031
# 82 "config.h"
     ,
     move_to,
     {.i = 0}},
    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 82 "config.h" 3 4
     0x0031
# 82 "config.h"
     ,
     send_to,
     {.i = 0}},
    {XCB_MOD_MASK_4,
# 82 "config.h" 3 4
     0x0032
# 82 "config.h"
     ,
     move_to,
     {.i = 1}},
    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 82 "config.h" 3 4
     0x0032
# 82 "config.h"
     ,
     send_to,
     {.i = 1}},
    {XCB_MOD_MASK_4,
# 82 "config.h" 3 4
     0x0033
# 82 "config.h"
     ,
     move_to,
     {.i = 2}},
    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 82 "config.h" 3 4
     0x0033
# 82 "config.h"
     ,
     send_to,
     {.i = 2}},
    {XCB_MOD_MASK_4,
# 82 "config.h" 3 4
     0x0034
# 82 "config.h"
     ,
     move_to,
     {.i = 3}},
    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 82 "config.h" 3 4
     0x0034
# 82 "config.h"
     ,
     send_to,
     {.i = 3}},
    {XCB_MOD_MASK_4,
# 82 "config.h" 3 4
     0x0035
# 82 "config.h"
     ,
     move_to,
     {.i = 4}},
    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 82 "config.h" 3 4
     0x0035
# 82 "config.h"
     ,
     send_to,
     {.i = 4}},

    {XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,
# 84 "config.h" 3 4
     0x0071
# 84 "config.h"
     ,
     closewm,
# 84 "config.h" 3 4
     ((void *)0)
# 84 "config.h"
    },
};
