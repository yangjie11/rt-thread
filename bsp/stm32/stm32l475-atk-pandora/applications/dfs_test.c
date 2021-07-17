
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_posix.h>
#include <unistd.h>
#include "rtlibc.h"

#include <temp.h>

int p_host_name_test(void)
{
    char name[10];
    gethostname(name, 10);
    rt_kprintf("%s\n", name);
    return 0;
}
MSH_CMD_EXPORT(p_host_name_test, host_name);

static void create_file(char *file_name)
{
    int fd;
    char s[] = "RT-Thread Programmer!";

    rt_kprintf("--------create file-------\n");
    fd = open(file_name, O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        write(fd, s, sizeof(s));
        close(fd);
        rt_kprintf("file %s done.fd is %d\n", file_name, fd);
    }
    ls();
}
static void create_dir(char *dir_name)
{
    int ret;
    rt_kprintf("--------mkdir-------\n");
    /* 创建目录 */
    ret = mkdir(dir_name, 0x777);
    if (ret < 0)
    {
        /* 创建目录失败 */
        rt_kprintf("mkdir error!\n");
    }
    else
    {
        /* 创建目录成功 */
        rt_kprintf("mkdir %s ok!\n", dir_name);
    }
    ls();
}

void real_path_entry(void *para)
{
    char *symlinkpath = "./file";//"../tmp/symlink/file";//
    char *actualpath = rt_malloc(64);
    char *actualpath2 = rt_malloc(64);

    actualpath = realpath(symlinkpath, NULL);
    if (actualpath != NULL)
    {
        rt_kprintf("real path is %s \n", actualpath);

        free(actualpath);
    }
    else
    {
        rt_kprintf("path not available\n");
        return ;
    }

    realpath(symlinkpath, actualpath2);
    if (actualpath2 != NULL)
    {
        rt_kprintf("real path2 is %s \n", actualpath2);

        free(actualpath2);
    }
    else
    {
        rt_kprintf(" no real path\n");
    }
}

int p_real_path_test(void)
{
    rt_thread_t tid1 = RT_NULL;
    tid1 = rt_thread_create("thread1",
                            real_path_entry, RT_NULL,
                            1024,
                            15, 10);

    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    return 0;
}
MSH_CMD_EXPORT(p_real_path_test, real_path_test);

int p_truncate_test(int argc, char *argv[])
{
    char file[RT_NAME_MAX];
    rt_uint16_t len = 15;

    if (argc == 2)
    {
        rt_strncpy(file, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_kprintf("truncate_test <FILE> \n");
        return 0;
    }
    create_file(file);
    rt_kprintf("start truncate\n");
    truncate(file, len);
    ls();
    return 0;
}
MSH_CMD_EXPORT(p_truncate_test, truncate_test);

int p_stat_test(int argc, char *argv[])
{
    struct stat *buf = RT_NULL;
    char file[RT_NAME_MAX];
    int fd;
    char s[] = "hello";

    if (argc == 2)
    {
        rt_strncpy(file, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_kprintf("stat_test <NEW FILE>\n");
        return 0;
    }

    fd = open(file, O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        write(fd, s, sizeof(s));
        rt_kprintf("file %s done.fd is %d\n", file, fd);
    }
    stat(file, buf);
    rt_kprintf("st_atime %d\n", buf->st_atime);
    rt_kprintf("st_mtime %d\n", buf->st_mtime);
    rt_kprintf("st_ctime %d\n", buf->st_ctime);

    return 0;
}
MSH_CMD_EXPORT(p_stat_test, stat_test);

int p_dirfd_test(int argc, char *argv[])
{
    DIR *dp;
    int fd;
    char dir[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(dir, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_kprintf("dirfd_test <NEW DIR>\n");
        return 0;
    }

    create_dir(dir);
    rt_kprintf("test start\n");

    dp = opendir(dir);
    fd = dirfd(dp);
    rt_kprintf("fd is %d\n", fd);
    return 0;
}
MSH_CMD_EXPORT(p_dirfd_test, dirfd_test);

int p_fd_open_test(int argc, char *argv[])
{
    FILE *dp;
    int fd;
    char file[RT_NAME_MAX];
    char s[] = "RT-Thread Programmer!";

    if (argc == 2)
    {
        rt_strncpy(file, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_kprintf("fd_open_test <NEW file>\n");
        return 0;
    }

    fd = open(file, O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        write(fd, s, sizeof(s));
        rt_kprintf("file %s done.fd is %d\n", file, fd);
    }

    dp = fdopen(fd, O_RDONLY);
    close(fd);
    return 0;
}
MSH_CMD_EXPORT(p_fd_open_test, fd_open_test);


int p_rw_test(void)
{   
    char buf1[5], buf2[10];
    struct iovec iov[2];
    iov[0].iov_base = buf1;
    iov[0].iov_len = 5;
    iov[1].iov_base = buf2;
    iov[1].iov_len = 10;

    int fd = open("a.txt", O_RDWR | O_CREAT);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    
    int rsize = readv(fd, iov, 2);  // 从文件a.txt中读取数据，存到iov[2]中的buf1、buf2
    printf("read len size = %d\n", rsize);

    close(fd);

    fd = open("b.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    int wsize = writev(fd, iov, 2); // 将iov[2]中的buf1、buf2，写入到文件b.txt
    printf("write len size = %d\n", wsize);

    close(fd);
    return 0;
}
MSH_CMD_EXPORT(p_rw_test, readv writev test);

int p_bd_name(int argc, char *argv[])
{
    char *files[] =
    {
        "/usr/local/nginx/conf/nginx.conf",
        "./a.out",
        "/usr/include/libgen.h",
        NULL
    };

    char **p = files;

    while (*p)
    {
        printf("basename(\"%s\")=%s\n", *p, basename(*p));
        printf("dirname (\"%s\")=%s\n\n", *p, dirname(*p));
        *p++;
    }
    return 0;
}
MSH_CMD_EXPORT(p_bd_name, base / dir name test);


int p_sdtfs_test(void)
{
    struct statvfs stat = {0};
    const char *path = "/test";

    if (statvfs(path, &stat) != 0)
    {
        return -1;
    }

    rt_kprintf("f_bsize    is  %d\n", stat.f_bsize);
    rt_kprintf("f_frsize   is  %d\n", stat.f_frsize);
    rt_kprintf("f_blocks   is  %d\n", stat.f_blocks);
    rt_kprintf("f_bfree    is  %d\n", stat.f_bfree);
    rt_kprintf("f_bavail   is  %d\n", stat.f_bavail);
    rt_kprintf("f_files    is  %d\n", stat.f_files);
    rt_kprintf("f_ffree    is  %d\n", stat.f_ffree);
    rt_kprintf("f_favail   is  %d\n", stat.f_favail);
    rt_kprintf("f_fsid     is  %d\n", stat.f_fsid);
    rt_kprintf("f_flag     is  %d\n", stat.f_flag);
    rt_kprintf("f_namemax  is  %d\n", stat.f_namemax);

    return 0;
}
MSH_CMD_EXPORT(p_sdtfs_test, statvfs_test);

