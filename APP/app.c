/*
 * app.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#include "app.h"


TaskHandle_t Handle_switches_init_task;
TaskHandle_t Handle_lcd_init_task;
TaskHandle_t Handle_ldr_init_task;
TaskHandle_t Handle_ultrasonic_init_task;
TaskHandle_t Handle_temperature_init_task;
TaskHandle_t Handle_movement_init_task;

TaskHandle_t TaskHandle_ldr;
TaskHandle_t TaskHandle_lcd;
TaskHandle_t movement_swing_task_handle;
TaskHandle_t movement_obstacle_task_handle;
TaskHandle_t TaskHandle_temp;
TaskHandle_t TaskHandle_switches;
TaskHandle_t TaskHandle_ultrasonic;

xQueueHandle xQueue_LDR_Difference;
xQueueHandle xQueue_LDR_Difference_LCD;
xQueueHandle xQueue_temperature_value;


xSemaphoreHandle xBinarySemaphore_obstacle;
xSemaphoreHandle xBinarySemaphore_LDR;


void APP_SysCreate(void)
{
    /*Create our queues*/
    xQueue_temperature_value  = xQueueCreate(1, sizeof(int32_t));
    xQueue_LDR_Difference_LCD = xQueueCreate(1, sizeof(int32_t));
    xQueue_LDR_Difference =     xQueueCreate(1, sizeof(int32_t));

    /*Create our semaphores*/
    vSemaphoreCreateBinary(xBinarySemaphore_obstacle);
    vSemaphoreCreateBinary(xBinarySemaphore_LDR);
    /*To be taken as a default*/
    xSemaphoreTake(xBinarySemaphore_obstacle , 1);
    xSemaphoreTake(xBinarySemaphore_LDR , 1);


    /*create the init tasks*/
    xTaskCreate(switches_init_task   ,NULL, configMINIMAL_STACK_SIZE, NULL, 6, &Handle_switches_init_task);
    xTaskCreate(lcd_init_task        ,NULL, configMINIMAL_STACK_SIZE, NULL, 5, &Handle_lcd_init_task);
    xTaskCreate(ldr_init_task        ,NULL, configMINIMAL_STACK_SIZE, NULL, 4, &Handle_ldr_init_task);
    xTaskCreate(ultrasonic_init_task ,NULL, configMINIMAL_STACK_SIZE, NULL, 3, &Handle_ultrasonic_init_task);
    xTaskCreate(temperature_init_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, &Handle_temperature_init_task);
    xTaskCreate(movement_init_task   ,NULL, configMINIMAL_STACK_SIZE, NULL, 1, &Handle_movement_init_task);

    /*create the tasks*/
    xTaskCreate(switches_update_task   ,"switches_update"   , configMINIMAL_STACK_SIZE, NULL, 1, &TaskHandle_switches);
    xTaskCreate(ultrasonic_update_task ,"ultrasonic_update" , configMINIMAL_STACK_SIZE, NULL, 4, &TaskHandle_ultrasonic);
    xTaskCreate(ldr_update_task        ,"ldr_update"        , configMINIMAL_STACK_SIZE, NULL, 3, &TaskHandle_ldr);
    xTaskCreate(movement_obstacle_task ,"robot_obstacle"    , configMINIMAL_STACK_SIZE, NULL, 2, &movement_obstacle_task_handle);
    xTaskCreate(movement_swing_task    ,"robot_swing"       , configMINIMAL_STACK_SIZE, NULL, 2, &movement_swing_task_handle);
    xTaskCreate(lcd_update_task        ,"lcd_update"        , configMINIMAL_STACK_SIZE, NULL, 1, &TaskHandle_lcd);
    xTaskCreate(temperature_update_task,"temperature_update", configMINIMAL_STACK_SIZE, NULL, 1, &TaskHandle_temp);

    /*Suspend unneeded tasks at first*/
    vTaskSuspend(TaskHandle_ultrasonic);
    vTaskSuspend(TaskHandle_ldr);
    vTaskSuspend(movement_obstacle_task_handle);
    vTaskSuspend(movement_swing_task_handle);
    vTaskSuspend(TaskHandle_lcd);
    vTaskSuspend(TaskHandle_temp);
}

void APP_SysOn(void)
{
    vTaskStartScheduler();
}
