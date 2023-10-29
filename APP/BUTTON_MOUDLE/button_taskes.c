/*
 * display_taskes.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#include "button_taskes.h"

extern int32_t seconds_count;

extern TaskHandle_t Handle_switches_init_task;

extern TaskHandle_t TaskHandle_ldr;
extern TaskHandle_t TaskHandle_lcd;
extern TaskHandle_t TaskHandle_temp;
extern TaskHandle_t TaskHandle_switches;
extern TaskHandle_t TaskHandle_ultrasonic;
extern TaskHandle_t movement_swing_task_handle;
extern TaskHandle_t movement_obstacle_task_handle;

button_t start_switch = {
                         .btnPort =PORTF_ID,
                         .btnPin = PIN0_ID,
                         .btn_conn = PULL_UP,
                         .btn_state = RELEASED
};

button_t stop_switch = {
                        .btnPort =PORTF_ID,
                        .btnPin = PIN4_ID,
                        .btn_conn = PULL_UP,
                        .btn_state = RELEASED
};


void switches_init_task(void*ptr)
{
    /*start switch init*/
    button_init(&start_switch);
    /*stop switch init*/
    button_init(&stop_switch);

    vTaskDelete(Handle_switches_init_task);
}


void switches_update_task(void *ptr)
{
    static buttonState_t current_start_switch_state , last_start_switch_state = RELEASED;
    static buttonState_t current_stop_switch_state , last_stop_switch_state = RELEASED;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        button_get_state(&start_switch, &current_start_switch_state);
        button_get_state(&stop_switch, &current_stop_switch_state);

        /****************** Start operation************************/
        /*when both current and last are equal do nothing*/
        if(current_start_switch_state == PRESSED && last_start_switch_state == RELEASED)
        {
            robot_move_stop();

            vTaskResume(TaskHandle_ultrasonic);
            vTaskResume(TaskHandle_ldr       );
            vTaskResume(movement_swing_task_handle);
            vTaskResume(movement_obstacle_task_handle);
            vTaskResume(TaskHandle_lcd       );
            vTaskResume(TaskHandle_temp      );

            /*reset second counter*/
            seconds_count = 0;
        }
        else /*Button_currentState == RELEASED && Button_lastState == PRESSED*/
        {
            /*then we are in the pre-release state */
            /*make the last stated = pressed*/
            last_start_switch_state = current_start_switch_state;
        }
        /****************** Stop operation************************/
        if(seconds_count > 59 || ( current_stop_switch_state == PRESSED && last_stop_switch_state == RELEASED))
        {
            robot_move_stop();

            vTaskSuspend(TaskHandle_ultrasonic);
            vTaskSuspend(TaskHandle_ldr       );
            vTaskSuspend(movement_swing_task_handle);
            vTaskSuspend(movement_obstacle_task_handle);
            vTaskSuspend(TaskHandle_lcd       );
            vTaskSuspend(TaskHandle_temp      );

        }
        else /*Button_currentState == RELEASED && Button_lastState == PRESSED*/
        {
            /*then we are in the pre-release state */
            /*make the last stated = pressed*/
            last_stop_switch_state = current_stop_switch_state;
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));
    }
}

