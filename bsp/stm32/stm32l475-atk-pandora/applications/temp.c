#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs.h>
#include <dfs_posix.h>
#include "dfs_private.h"
#include <sys/time.h>
#include <unistd.h>
#include <rtlibc.h>

#include <temp.h>

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/utimes.html
 */
int utimes(const char *path, const struct timeval times[2])
{
    return 0;
}

/* 
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/dirfd.html
 */
int dirfd(DIR *dirp)
{
    if (dirp != NULL)
    {
        return dirp->fd;
    }
    rt_set_errno(-EBADF);
    return -1;
}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/readdir_r.html
 */
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result)
{
    int res;
    struct dfs_fd *fd;

    fd = fd_get(dirp->fd);
    if (fd == NULL)
    {
        rt_set_errno(-EBADF);
        return NULL;
    }

    if (dirp->num)
    {
        struct dirent *dirent_ptr;
        dirent_ptr = (struct dirent *)&dirp->buf[dirp->cur];
        dirp->cur += dirent_ptr->d_reclen;
    }

    if (!dirp->num || dirp->cur >= dirp->num)
    {
        /* get a new entry */
        res = dfs_file_getdents(fd,
                                (struct dirent *)dirp->buf,
                                sizeof(dirp->buf) - 1);
        if (res <= 0)
        {
            fd_put(fd);
            rt_set_errno(res);

            return NULL;
        }

        dirp->num = res;
        dirp->cur = 0; /* current entry index */
    }

    fd_put(fd);

    entry = (struct dirent *)(dirp->buf + dirp->cur);
    *result = entry;

    return 0;
}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_stat.h.html#tag_13_62
 * for:
 * chmod/fchmod/lstat
 */
int chmod(const char *path, mode_t mode)
{
    return 0;
}
int fchmod(int fildes, mode_t mode)
{
    return 0;
}
int lstat(const char *path, struct stat *buf)
{
    stat(path, buf);
    return 0;
}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/nanosleep.html#
 */
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    uint16_t time_ms = rqtp->tv_sec * 1000;
    uint16_t time_us = rqtp->tv_nsec / 1000;
    uint16_t i = 0;

    rt_thread_mdelay(time_ms);

    if (rt_thread_self() != RT_NULL)
    {
        rt_thread_mdelay(time_ms);
    }
    else  /* scheduler has not run yet */
    {
        for (i = 0; i < time_ms - 1; i++)
        {
            rt_hw_us_delay(1000u);
        }
    }
    rt_hw_us_delay(time_us);

    return 0;
}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html#tag_13_80
 */
int nice(int inc)
{
    return 0;
}
/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_mman.h.html#tag_13_55
 * for
 * msync/mlock/munlock/mprotect/mmap/munmap
 */
int msync(void *addr, size_t len, int flags)
{
    return 0;
}
int mlock(const void *addr, size_t len)
{
    return 0;
}
int munlock(const void *addr, size_t len)
{
    return 0;
}
int mprotect(void *addr, size_t len, int prot)
{
    return 0;
}
//注意已有
void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off)
{
    return 0;
}
//注意已有
int munmap(void *addr, size_t len)
{
    return 0;
}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/basename.html#tag_16_32
 */
char *basename(char *path)
{
    char *dst, *src;
    src = path;
    dst = path;

    char c = *src;

    if (path == NULL)
    {
        return ".";
    }

    while ((c = *src++) != '\0')
    {
        if (c == '/')
        {
            dst = src;
        }
    }
    return dst;
}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/dirname.html#tag_16_91
 */
char *dirname(char *path)
{
    char *dst, *src, *dst0;
    src = path;
    dst0 = path;

    long len = 0;

    char c = *src;

    if (path == NULL)
    {
        return ".";
    }

    while ((c = *src++) != '\0')
    {
        len++;
        if (c == '/')
        {
            dst0 = src;
        }
    }

    while ((*dst0++) != '\0')
    {
        len--;
    }
    len--;

    if (len > DFS_PATH_MAX)
    {
        rt_set_errno(-ENOTDIR);

        return NULL;
    }

    dst0 = rt_malloc(256);
    rt_strncpy(dst0, path, len);
    dst0[len] = '\0';
    dst = dst0;
    rt_free(dst0);

    return dst;
}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/statvfs.html
 */
int statvfs(const char *restrict path, struct statvfs *restrict buf)
{
    int result;
    struct statfs buffer = {0};
    result = dfs_statfs(path, &buffer);
    if (result < 0)
    {
        rt_set_errno(result);

        return -1;
    }

    buf->f_bsize = buffer.f_bsize;
    buf->f_blocks = buffer.f_blocks;
    buf->f_bfree = buffer.f_bfree;

    buf->f_flag = ST_RDONLY;//or ST_NOSUID
    return 0;

}

/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_uio.h.html#tag_13_68
 * for
 * readv/writev
 */
ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
{
    int i = 0;
    size_t length = 0;

    for (i = 0; i < iovcnt; i++)
    {
        if (read(fd, iov[i].iov_base, iov[i].iov_len) >= 0)
        {
            length += iov[i].iov_len;
        }
        else
        {
            rt_set_errno(-EIO);
            return -1;
        }
    }
    return length;
}

ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
{
    int i = 0;
    size_t length = 0;

    for (i = 0; i < iovcnt; i++)
    {
        if (write(fd, iov[i].iov_base, iov[i].iov_len) >= 0)
        {
             length += iov[i].iov_len;
        }
        else
        {
            rt_set_errno(-EIO);
            return -1;
        }
    }
    return length;
}

