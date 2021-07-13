/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include "pw_framework.h"

extern void js_app_ready_sem_release(void);

int main(void)
{
    // pw_framework_init();
    // sys_info_init();
    // pw_framework_startup();

    //js_app_ready_sem_release();
    return RT_EOK;
}

int cpu_usage_init()
{
    return 0;
}
int cpu_load_average()
{
    return 0;
}
