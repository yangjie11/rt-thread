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
int utimes(const char *path, const struct timeval times[2])
{
    //dfs_elm_stat
}

/*返回参数dirp所指向的目录文件的文件描述符，该文件描述符的关闭应由函数closedir()执行*/
int dirfd(DIR *dirp)
{

}

/*因为内部使用了静态数据，所以readdir被认为不是线程安全的函数,因此才有了readdir_r函数的出现*/
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result)
{

}

/*改变文件的读写许可设置*/
int chmod(const char * path, mode_t mode)
{
    

}

/*会依参数mode权限来更改参数fildes所指文件的权限*/
int fchmod(int fildes,mode_t mode)
{
    struct dfs_fd *d;
    
    d = fd_get(fildes);
    if (d != NULL)
    {
        d->flags = mode;
    }   
    return 0;
}


/*获取一些文件相关的信息*/
int lstat(const char *path, struct stat *buf)
{

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
//    uint16_t time_ms = rqtp->tv_sec*1000+1;
//    rt_thread_mdelay(time_ms);
//    
//        if (rt_thread_self() != RT_NULL)
//    {
//        rt_thread_mdelay(usec / 1000u);
//    }
//    else  /* scheduler has not run yet */
//    {
//        rt_hw_us_delay(usec / 1000u);
//    }
//    rt_hw_us_delay(usec % 1000u);

//    return 0;

}



