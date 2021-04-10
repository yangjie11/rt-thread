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
#include <rtdevice.h>
#include <board.h>

#define STM32_SRAM1_SIZE1               (50)//(96)
#define STM32_SRAM1_SIZE2               (90)//(96)
#define STM32_SRAM1_START1              (0x20000000)
#define STM32_SRAM1_END1                (STM32_SRAM1_START1 + STM32_SRAM1_SIZE1 * 1024+8)
#define STM32_SRAM1_END2                (STM32_SRAM1_START1 + STM32_SRAM1_SIZE2 * 1024)

/* defined the LED0 pin: PE7 */
#define LED0_PIN    GET_PIN(E, 7)

int main(void)
{
    int count = 1;
    void* result;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    
    rt_kprintf("main\n");
    list_mem();
    rt_kprintf("start add\n");
    result = rt_system_heap_add((void*)STM32_SRAM1_END1,(void*)STM32_SRAM1_END2);
    if(result == RT_NULL)
    {
        rt_kprintf("add error\n");
        return RT_NULL;
    }
    

    rt_kprintf("add ok\n");
    list_mem();
    rt_kprintf("\n");
    
    rt_system_heap_remove(result);
    
    rt_kprintf("remove ok\n");
    list_mem();
    rt_kprintf("\n");
//    

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}


