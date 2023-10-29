/*
 * display_taskes.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#include <APP/ULTRA_MOUDLE/ultrasonic_tasks.h>

extern xSemaphoreHandle xBinarySemaphore_obstacle;

extern TaskHandle_t Handle_ultrasonic_init_task;

ultraSonic_t Ultrasonic_Sensor = {
                                  .ultrasonicPort = PORTC_ID,
                                  .ultrasonicTriggerPin = PIN5_ID,
                                  .ultrasonicEchoPin = PIN6_ID
};

void ultrasonic_init_task(void*ptr)
{
    /*Initialize ultrasonic sensor*/
    ultrasonic_sensor_init(&Ultrasonic_Sensor);

    vTaskDelete(Handle_ultrasonic_init_task);
}

void ultrasonic_update_task(void *ptr)
{
    uint16_t obstacle_distance = 0U;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        /*get distance*/
        obstacle_distance = ultrasonic_sensor_read_value(&Ultrasonic_Sensor);
        /*check the car is blocked*/
        if(( 15U < obstacle_distance) || (0U == obstacle_distance ))
        {
            /*do nothing*/
        }
        else
        {
            xSemaphoreGive(xBinarySemaphore_obstacle);
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(40));
    }

}


