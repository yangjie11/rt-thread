/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-16     Meco Man     add usleep
 */
#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H

#include <rtconfig.h>
#include "types.h"

#ifdef RT_USING_DFS

#define STDIN_FILENO    0       /* standard input file descriptor */
#define STDOUT_FILENO   1       /* standard output file descriptor */
#define STDERR_FILENO   2       /* standard error file descriptor */


/* Constants used with POSIX sysconf().  sysconf() will return -1 and set
 * errno to ENOSYS for most of these.
 */

#define _SC_2_C_BIND                     0x0001
#define _SC_2_C_DEV                      0x0002
#define _SC_2_CHAR_TERM                  0x0003
#define _SC_2_FORT_DEV                   0x0004
#define _SC_2_FORT_RUN                   0x0005
#define _SC_2_LOCALEDEF                  0x0006
#define _SC_2_PBS                        0x0007
#define _SC_2_PBS_ACCOUNTING             0x0008
#define _SC_2_PBS_CHECKPOINT             0x0009
#define _SC_2_PBS_LOCATE                 0x000a
#define _SC_2_PBS_MESSAGE                0x000b
#define _SC_2_PBS_TRACK                  0x000c
#define _SC_2_SW_DEV                     0x000d
#define _SC_2_UPE                        0x000e
#define _SC_2_VERSION                    0x000f
#define _SC_ADVISORY_INFO                0x0010
#define _SC_AIO_LISTIO_MAX               0x0011
#define _SC_AIO_MAX                      0x0012
#define _SC_AIO_PRIO_DELTA_MAX           0x0013
#define _SC_ARG_MAX                      0x0014
#define _SC_ASYNCHRONOUS_IO              0x0015
#define _SC_ATEXIT_MAX                   0x0016
#define _SC_BARRIERS                     0x0017
#define _SC_BC_BASE_MAX                  0x0018
#define _SC_BC_DIM_MAX                   0x0019
#define _SC_BC_SCALE_MAX                 0x001a
#define _SC_BC_STRING_MAX                0x001b
#define _SC_CHILD_MAX                    0x001c
#define _SC_CLK_TCK                      0x001d
#define _SC_CLOCK_SELECTION              0x001e
#define _SC_COLL_WEIGHTS_MAX             0x001f
#define _SC_CPUTIME                      0x0020
#define _SC_DELAYTIMER_MAX               0x0021
#define _SC_EXPR_NEST_MAX                0x0022
#define _SC_FSYNC                        0x0023
#define _SC_GETGR_R_SIZE_MAX             0x0024
#define _SC_GETPW_R_SIZE_MAX             0x0025
#define _SC_HOST_NAME_MAX                0x0026
#define _SC_IOV_MAX                      0x0027
#define _SC_IPV6                         0x0028
#define _SC_JOB_CONTROL                  0x0029
#define _SC_LINE_MAX                     0x002a
#define _SC_LOGIN_NAME_MAX               0x002b
#define _SC_MAPPED_FILES                 0x002c
#define _SC_MEMLOCK                      0x002d
#define _SC_MEMLOCK_RANGE                0x002e
#define _SC_MEMORY_PROTECTION            0x002f
#define _SC_MESSAGE_PASSING              0x0030
#define _SC_MONOTONIC_CLOCK              0x0031
#define _SC_MQ_OPEN_MAX                  0x0032
#define _SC_MQ_PRIO_MAX                  0x0033
#define _SC_NGROUPS_MAX                  0x0034
#define _SC_OPEN_MAX                     0x0035
#define _SC_PAGE_SIZE                    0x0036
#define _SC_PAGESIZE                     _SC_PAGE_SIZE
#define _SC_PRIORITIZED_IO               0x0037
#define _SC_PRIORITY_SCHEDULING          0x0038
#define _SC_RAW_SOCKETS                  0x0039
#define _SC_RE_DUP_MAX                   0x003a
#define _SC_READER_WRITER_LOCKS          0x003b
#define _SC_REALTIME_SIGNALS             0x003c
#define _SC_REGEXP                       0x003d
#define _SC_RTSIG_MAX                    0x003e
#define _SC_SAVED_IDS                    0x003f
#define _SC_SEM_NSEMS_MAX                0x0040
#define _SC_SEM_VALUE_MAX                0x0041
#define _SC_SEMAPHORES                   0x0042
#define _SC_SHARED_MEMORY_OBJECTS        0x0043
#define _SC_SHELL                        0x0044
#define _SC_SIGQUEUE_MAX                 0x0045
#define _SC_SPAWN                        0x0046
#define _SC_SPIN_LOCKS                   0x0047
#define _SC_SPORADIC_SERVER              0x0048
#define _SC_SS_REPL_MAX                  0x0049
#define _SC_STREAM_MAX                   0x004a
#define _SC_SYMLOOP_MAX                  0x004b
#define _SC_SYNCHRONIZED_IO              0x004c
#define _SC_THREAD_ATTR_STACKADDR        0x004d
#define _SC_THREAD_ATTR_STACKSIZE        0x004e
#define _SC_THREAD_CPUTIME               0x004f
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 0x0050
#define _SC_THREAD_KEYS_MAX              0x0051
#define _SC_THREAD_PRIO_INHERIT          0x0052
#define _SC_THREAD_PRIO_PROTECT          0x0053
#define _SC_THREAD_PRIORITY_SCHEDULING   0x0054
#define _SC_THREAD_PROCESS_SHARED        0x0055
#define _SC_THREAD_SAFE_FUNCTIONS        0x0056
#define _SC_THREAD_SPORADIC_SERVER       0x0057
#define _SC_THREAD_STACK_MIN             0x0058
#define _SC_THREAD_THREADS_MAX           0x0059
#define _SC_THREADS                      0x005a
#define _SC_TIMEOUTS                     0x005b
#define _SC_TIMER_MAX                    0x005c
#define _SC_TIMERS                       0x005d
#define _SC_TRACE                        0x005e
#define _SC_TRACE_EVENT_FILTER           0x005f
#define _SC_TRACE_EVENT_NAME_MAX         0x0060
#define _SC_TRACE_INHERIT                0x0061
#define _SC_TRACE_LOG                    0x0062
#define _SC_TRACE_NAME_MAX               0x0063
#define _SC_TRACE_SYS_MAX                0x0064
#define _SC_TRACE_USER_EVENT_MAX         0x0065
#define _SC_TTY_NAME_MAX                 0x0066
#define _SC_TYPED_MEMORY_OBJECTS         0x0067
#define _SC_TZNAME_MAX                   0x0068
#define _SC_V6_ILP32_OFF32               0x0069
#define _SC_V6_ILP32_OFFBIG              0x006a
#define _SC_V6_LP64_OFF64                0x006b
#define _SC_V6_LPBIG_OFFBIG              0x006c
#define _SC_VERSION                      0x006d
#define _SC_XBS5_ILP32_OFF32             0x006e  /* (LEGACY) */
#define _SC_XBS5_ILP32_OFFBIG            0x006f  /* (LEGACY) */
#define _SC_XBS5_LP64_OFF64              0x0070  /* (LEGACY) */
#define _SC_XBS5_LPBIG_OFFBIG            0x0071  /* (LEGACY) */
#define _SC_XOPEN_CRYPT                  0x0072
#define _SC_XOPEN_ENH_I18N               0x0073
#define _SC_XOPEN_LEGACY                 0x0074
#define _SC_XOPEN_REALTIME               0x0075
#define _SC_XOPEN_REALTIME_THREADS       0x0076
#define _SC_XOPEN_SHM                    0x0077
#define _SC_XOPEN_STREAMS                0x0078
#define _SC_XOPEN_UNIX                   0x0079
#define _SC_XOPEN_VERSION                0x007a

#define _SC_PHYS_PAGES                   0x007b
#define _SC_AVPHYS_PAGES                 0x007c

#define _SC_NPROCESSORS_CONF             0x007d
#define _SC_NPROCESSORS_ONLN             0x007e


#include <dfs_posix.h>
#else
#define _FREAD      0x0001  /* read enabled */
#define _FWRITE     0x0002  /* write enabled */
#define _FAPPEND    0x0008  /* append (writes guaranteed at the end) */
#define _FMARK      0x0010  /* internal; mark during gc() */
#define _FDEFER     0x0020  /* internal; defer for next gc pass */
#define _FASYNC     0x0040  /* signal pgrp when data ready */
#define _FSHLOCK    0x0080  /* BSD flock() shared lock present */
#define _FEXLOCK    0x0100  /* BSD flock() exclusive lock present */
#define _FCREAT     0x0200  /* open with file create */
#define _FTRUNC     0x0400  /* open with truncation */
#define _FEXCL      0x0800  /* error on open if file exists */
#define _FNBIO      0x1000  /* non blocking I/O (sys5 style) */
#define _FSYNC      0x2000  /* do all writes synchronously */
#define _FNONBLOCK  0x4000  /* non blocking I/O (POSIX style) */
#define _FNDELAY    _FNONBLOCK  /* non blocking I/O (4.2 style) */
#define _FNOCTTY    0x8000  /* don't assign a ctty on this open */


#ifndef O_RDONLY
#define O_RDONLY    0       /* +1 == FREAD */
#endif
#ifndef O_WRONLY
#define O_WRONLY    1       /* +1 == FWRITE */
#endif
#ifndef O_RDWR
#define O_RDWR      2       /* +1 == FREAD|FWRITE */
#endif
#ifndef O_APPEND
#define O_APPEND    _FAPPEND
#endif
#ifndef O_CREAT
#define O_CREAT     _FCREAT
#endif
#ifndef O_TRUNC
#define O_TRUNC     _FTRUNC
#endif
#ifndef O_EXCL
#define O_EXCL      _FEXCL
#endif
#ifndef O_SYNC
#define O_SYNC      _FSYNC
#endif

#endif

int     isatty      (int fd);
char *  ttyname     (int desc);
unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);
pid_t gettid(void);
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);

#endif /* _SYS_UNISTD_H */
