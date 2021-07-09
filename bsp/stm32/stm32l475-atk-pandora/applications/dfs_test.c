
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_posix.h>

int host_name_test(void)
{
    char name[10];
    gethostname(name, 10);
    rt_kprintf("%s\n", name);
    return 0;
}
MSH_CMD_EXPORT(host_name_test, host_name);



#define FILE_NAME "/test_rtt2.txt"
#define DIR_NAME  "/rtt_dir2"

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


static int unlink_file(char *file_name)
{
    int res = 0;
    res = unlinkat(0, file_name, 0);
    if (res == -1)
    {
        rt_kprintf("unlink err\n");
        return -1;
    }

    rt_kprintf("unlink ok\n");
    ls();
    return 0;
}

static int unlink_dir(char *dir_name)
{
    int res = 0;
    res = unlinkat(0, dir_name, 0);
    if (res == -1)
    {
        rt_kprintf("unlink err\n");
        return -1;
    }

    rt_kprintf("unlink ok\n");
    ls();
    return 0;
}

/* unlinkat 可以删除文件（默认）或文件夹（需要设置flags为AT_REMOVEDIR）*/
int unlinkat_test(void)
{
    create_file(FILE_NAME);
    create_dir(DIR_NAME);

    rt_kprintf("--------unlinkat test-------\n");
    unlink_file(FILE_NAME);
    //  unlink_dir(DIR_NAME);

}
MSH_CMD_EXPORT(unlinkat_test, unlinkat_test);



int real_path_test()
{

}


#include <unistd.h>


char buf[1024];
ssize_t len;
int read_link_test(void)
{
    if ((len = readlink("/modules/pass1", buf, sizeof(buf) - 1)) != -1)
    {
        buf[len] = '\0';
    }
}





