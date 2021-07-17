/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-17                  the first version
 */
#ifndef TEMP_H_
#define TEMP_H_

#include <rtthread.h>

#define ST_RDONLY             0x0001 /* Mount read-only.  */
#define ST_NOSUID             0x0002 /* Ignore suid and sgid bits.  */

typedef uint32_t     fsblkcnt_t;
typedef uint32_t     fsfilcnt_t;

struct statvfs
{
    unsigned long f_bsize;   /* File system block size */
    unsigned long f_frsize;  /* Fundamental file system block size */
    fsblkcnt_t    f_blocks;  /* Total number of blocks on file system in
                            * units of f_frsize */
    fsblkcnt_t    f_bfree;   /* Total number of free blocks */
    fsblkcnt_t    f_bavail;  /* Number of free blocks available to
                            * non-privileged process */
    fsfilcnt_t    f_files;   /* Total number of file serial numbers */
    fsfilcnt_t    f_ffree;   /* Total number of free file serial numbers */
    fsfilcnt_t    f_favail;  /* Number of file serial numbers available to
                            * non-privileged process */
    unsigned long f_fsid;    /* File system ID */
    unsigned long f_flag;    /* Bit mask of f_flag values */
    unsigned long f_namemax; /* Maximum filename length */
};


struct iovec
{
    void *iov_base;  /* Base address of I/O memory region */
    size_t    iov_len;   /* Size of the memory pointed to by iov_base */
};






char *basename(char *path);
int chmod(const char *path, mode_t mode);
int fchmod(int fildes, mode_t mode);
    
int dirfd(DIR *dirp);
char *dirname(char *path);

int lstat(const char *path, struct stat *buf);

int mlock(const void *addr, size_t len);
void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
int mprotect(void *addr, size_t len, int prot);
int msync(void *addr, size_t len, int flags);
int munlock(const void *addr, size_t len);
int munmap(void *addr, size_t len);
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
int nice(int inc);
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
int statvfs(const char *restrict path, struct statvfs *restrict buf);
int utimes(const char *path, const struct timeval times[2]);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#endif /* TEMP_H_ */
