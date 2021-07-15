#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs.h>
#include <dfs_posix.h>
#include "dfs_private.h"
#include <sys/time.h>
#include <unistd.h>
#include <rtlibc.h>

/*修改文件存储时间(微秒级)*/
/*
The futimens() and utimensat() functions shall set the access and modification times of a file to the values of the times argument
1>访问时间（access time 简写为atime）
2>修改时间（modify time 简写为mtime）
3>状态修改时间(change time 简写为ctime)
*/
int utimes(const char *path, const struct timeval times[2])
{
    return 0;
}

/*返回参数dirp所指向的目录文件的文件描述符，该文件描述符的关闭应由函数closedir()执行*/
int dirfd(DIR *dirp)
{
    if (dirp != NULL)
    {
        return dirp->fd;
    }
    rt_set_errno(-EBADF);
    return -1;
}

/*因为内部使用了静态数据，所以readdir被认为不是线程安全的函数,因此才有了readdir_r函数的出现*/
// readdir_r将返回结果填充到调用者提供的entry缓冲区中，保证了它的线程安全性
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

int chmod(const char *path, mode_t mode)
{
    return 0;
}

int fchmod(int fildes, mode_t mode)
{
    return 0;
}

//lstat()与stat()作用完全相同，都是取得参数file_name所指的文件状态，其差别在于，当文件为符号连接时，lstat()会返回该link本身的状态。详细内容请参考stat()。
/*获取一些文件相关的信息*/
//执行成功则返回0，失败返回-1，错误代码存于errno

int lstat(const char *path, struct stat *buf)
{
//The lstat() function shall be equivalent to stat(),
//except when path refers to a symbolic link

    stat(path, buf);
    return 0;
}

/*
导致当前的线程将暂停执行,直到rqtp参数所指定的时间间隔。
或者在指定时间间隔内有信号传递到当前线程，将引起当前线程调用信号捕获函数或终止该线程

这个函数功能是暂停某个线程直到你规定的时间后恢复，参数req就是你要暂停的时间，
其中req->tv_sec是以秒为单位，而tv_nsec以纳秒为单位（10的-9次方秒），范围是[0,999999999]。
由于调用nanosleep是使线程进入TASK_INTERRUPTIBLE,这种状态是会响应信号而进入TASK_RUNNING状态的，
这就意味着有可能会没有等到你规定的时间就因为其它信号而唤醒，此时函数返回-1，
且还剩余的时间会被记录在rem中（rem不为空的情况下）。
nanosleep可以很好的保留中断时剩余时间,是比sleep()函数更高精度的时间函数
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



