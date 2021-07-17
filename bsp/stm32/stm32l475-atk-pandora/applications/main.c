/*
 * 程序清单：这是一个 RTC 设备使用例程
 * 例程导出了 alarm_sample 命令到控制终端
 * 命令调用格式：alarm_sample
 * 程序功能：创建，启动，控制，停止，删除 Alarm 闹钟，并且每一步操作结束后打印一次 alarm 信息。
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

int led = 0;

void user_alarm_callback(rt_alarm_t alarm, time_t timestamp)
{
    rt_pin_write(led,PIN_LOW);
    rt_kprintf("User alarm!.\n");
}

//void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
//{
//    rt_pin_write(led,PIN_LOW);
//    rt_kprintf("User alarm!.\n");
//}

void update(void *args)
{
    rt_device_t dev = rt_device_find("rtc");
    while(1)
    {
        rt_alarm_update(dev,1);
        rt_thread_mdelay(500);
    }
}
//MSH_CMD_EXPORT(update,update alarm);

void alarm_sample(void)
{  
//    set_date(2021,7,17);
//    set_time(9,29,55);
    rt_device_t dev = rt_device_find("rtc");
    struct rt_alarm_setup setup;
    struct rt_alarm * alarm = RT_NULL;
    static time_t now;
    struct tm *p_tm;
    
    if (alarm != RT_NULL)
        return;
    
    now = time(NULL);
    p_tm = localtime(&now);
    
    setup.flag = RT_ALARM_SECOND;
    setup.wktime.tm_wday = p_tm->tm_wday;
    setup.wktime.tm_year = p_tm->tm_year;
    setup.wktime.tm_mon  = p_tm->tm_mon;
    setup.wktime.tm_mday = p_tm->tm_mday;
    setup.wktime.tm_hour = p_tm->tm_hour;
    setup.wktime.tm_min  = p_tm->tm_min;
    setup.wktime.tm_sec  = p_tm->tm_sec;

    alarm = rt_alarm_create(user_alarm_callback, &setup);    
    if(RT_NULL != alarm)
    {
        rt_alarm_dump();
        rt_alarm_start(alarm);
        rt_alarm_dump();
    }
    rt_alarm_update(dev,1);
}
/* export msh cmd */
MSH_CMD_EXPORT(alarm_sample,alarm sample);

void thread(void)
{
    rt_thread_t  alarm_thread = rt_thread_create("alarm_thread",update,RT_NULL,2048,24,10);
    if(RT_NULL != alarm_thread)
    {
        rt_thread_startup(alarm_thread);
    }
}

MSH_CMD_EXPORT(thread,alarm update thread);

int main(void)
{
    led = rt_pin_get("PE.7");
    rt_pin_mode(led,PIN_MODE_OUTPUT);
    rt_pin_write(led,PIN_HIGH);
    
    while(1)
    {
        rt_pin_write(led,PIN_HIGH);
        rt_thread_mdelay(500);
    }
    
    return 0;
}
