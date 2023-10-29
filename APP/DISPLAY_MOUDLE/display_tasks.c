/*
 * display_taskes.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#include <APP/DISPLAY_MOUDLE/display_tasks.h>

extern TaskHandle_t Handle_lcd_init_task;

extern xQueueHandle xQueue_temperature_value;
extern xQueueHandle xQueue_LDR_Difference_LCD;

extern uint32_t seconds_count;

GPTM_ConfigType Stop_watch = {
                              .timer_global_operation = _16BIT_IN_16_OR_32_BIT_TIMER,
                              .timer_mode = PERIODIC,
                              .timer_number = TIMER3,
                              .timer_type = _16_OR_32_BIT_TIMER,
                              .timer_use = INDIVIDUAL_A
};


void stopwatch_init(void)
{
    /*timer init*/
    timer_init(&Stop_watch, 1000);
}


void lcd_init_task(void*ptr)
{
    /*initialization of lcd */
    lcd_init();

    /*stop watch init*/
    stopwatch_init();

    vTaskDelete(Handle_lcd_init_task);
}

void lcd_update_task(void *ptr)
{
    /*Initialize variables to receive from the queue*/
    int32_t temperature_value = 0U;
    int32_t LDR_Difference_LCD = 0U;

    /*Set cursor position to ROW_0 and COL_0*/
    lcd_move_cursor(0,0);
    /*Displaying Temperature on LCD*/
    lcd_display_string("Temp=");

    /*Set cursor position to ROW_1 and COL_0*/
    lcd_move_cursor(1,0);
    /*Displaying Time on LCD*/
    lcd_display_string("Time=");

    /*Set cursor position to ROW_1 and COL_8*/
    lcd_move_cursor(1,8);
    /*Displaying Temperature sensor value*/
    lcd_display_string("LD=");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        /*Receive the temperature value from its queue*/
        xQueueReceive(xQueue_temperature_value , &temperature_value, 0 );
        /*Receive the LDR difference value from its queue*/
        xQueueReceive(xQueue_LDR_Difference_LCD , &LDR_Difference_LCD, 0 );

        /*Set cursor position to ROW_0 and COL_5*/
        lcd_move_cursor(0,5);
        /*Display the temperature value on LCD*/
        lcd_intger_to_string(temperature_value);
        lcd_display_string("C");

        /*Displaying Time */
        manage_time();

        /*clear this LDR old part on LCD*/
        lcd_move_cursor(1,11);
        lcd_display_string("     ");

        /*Set cursor position to ROW_1 and COL_10*/
        lcd_move_cursor(1,11);
        /*Displaying LDR difference value*/
        lcd_intger_to_string(LDR_Difference_LCD);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}

void manage_time(void)
{
    static uint32_t secs ;
    secs = seconds_count% 60 ;
    lcd_move_cursor(1,5);
    if(secs >= 10)
    {
        lcd_move_cursor(1,5);
        lcd_intger_to_string(secs);
    }else if (secs == 0)
    {
        lcd_move_cursor(1,5);
        lcd_display_string("00");
    }
    else {
        lcd_move_cursor(1,6);
        lcd_intger_to_string(secs);
    }
}
