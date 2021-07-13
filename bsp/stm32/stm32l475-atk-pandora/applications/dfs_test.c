
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_posix.h>
#include <unistd.h>
#include "rtlibc.h"

#define FILE_NAME "/test_rtt2.txt"
#define DIR_NAME  "/rtt_dir2"

int host_name_test(void)
{
    char name[10];
    gethostname(name, 10);
    rt_kprintf("%s\n", name);
    return 0;
}
MSH_CMD_EXPORT(host_name_test, host_name);



//---------------------------------start--------------------

static void create_file(char *file_name)
{

    int fd, size;
    char s[] = "RT-Thread Programmer!";

    rt_kprintf("--------create file-------\n");
    fd = open(file_name, O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        write(fd, s, sizeof(s));
        close(fd);
        rt_kprintf("file %s done.\n", file_name);
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


//---------------------------------end----------------------
int real_path_test(void)
{
    char *symlinkpath = "/tmp/symlink/file";
    char *actualpath;


    actualpath = realpath(symlinkpath, NULL);
    if (actualpath != NULL)
    {
//    ... use actualpath ...
    rt_kprintf("real path is %s \n",actualpath);

        free(actualpath);
    }
    else
    {
        //  ... handle error ...
    }
    return 0;
}
MSH_CMD_EXPORT(real_path_test, real_path_test);

int truncate_test(void)
{
    char *file = "test_tru.txt";
    create_file(file);
    rt_kprintf("start truncate\n");
    truncate(file, 20); //int truncate(const char *path, off_t length)
    ls();
    return 0;
}
MSH_CMD_EXPORT(truncate_test, truncate_test);


int read_link_test(void)
{
    char buf[1024];
    ssize_t len;


    if ((len = readlink("/modules/pass1", buf, sizeof(buf) - 1)) != -1)
    {
        buf[len] = '\0';
    }
    return 0;
}
MSH_CMD_EXPORT(read_link_test, read_link_test);




