/*
 * movement_tasks.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#include "movement_tasks.h"

extern carSide_t LEFT_SIDE;
extern carSide_t RIGHT_SIDE;

extern TaskHandle_t Handle_movement_init_task;
extern TaskHandle_t movement_swing_task_handle;
extern TaskHandle_t movement_obstacle_task_handle;


extern xQueueHandle xQueue_LDR_Difference;


extern xSemaphoreHandle xBinarySemaphore_obstacle;
extern xSemaphoreHandle xBinarySemaphore_LDR;

xSemaphoreHandle xBinarySemaphore_Free;

void movement_init_task(void*ptr)
{
    /*initialize the car*/
    car_init(&LEFT_SIDE, &RIGHT_SIDE);

    /**/
    vSemaphoreCreateBinary(xBinarySemaphore_Free);
    xSemaphoreTake(xBinarySemaphore_Free, 2);

    vTaskDelete(Handle_movement_init_task);
}


void movement_obstacle_task(void*ptr)
{
    static uint8_t Counter = 0U;
    uint8_t CAR_90FLAG=0U;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        if(xSemaphoreTake(xBinarySemaphore_obstacle, 1))
        {
            CAR_90FLAG=1U;
            robot_move_back();
        }
        else if( CAR_90FLAG==1U )
        {
            if(Counter==12U)
            {
                /*Down the flag*/
                CAR_90FLAG=0U;
            }
            else
            {
                /*increment the counter*/
                Counter++;
                robot_move_rotate();
            }
            /*TODO: Remove Delay*/
            //vTaskDelay(pdMS_TO_TICKS(700));
        }
        else
        {
            /*Reset the counter*/
            Counter=0U;
            /*Give the permission to the movement_swing_task to take the control */
            xSemaphoreGive(xBinarySemaphore_Free);
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));
    }
}

void movement_swing_task(void*ptr)
{
    int32_t LDR_Difference=0;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        /*try to take the control from movement_obstacle_task*/
        if(xSemaphoreTake(xBinarySemaphore_Free, 1))
        {
            /*check if there is an event on LDR to take an action*/
            if(xSemaphoreTake(xBinarySemaphore_LDR, 1))
            {
                vTaskPrioritySet(movement_swing_task_handle , 3);
                xQueueReceive(xQueue_LDR_Difference, &LDR_Difference, 0);
                if(LDR_Difference > 0 )
                {
                    robot_move_right();
                }
                else if(LDR_Difference < 0)
                {
                    robot_move_left();
                }
                else
                {
                    robot_move_forward();
                }
            }
            else
            {
                robot_move_forward();
            }
            vTaskPrioritySet(movement_swing_task_handle , 2);
        }
        else
        {
            /*Do nothing*/
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));
    }

}
