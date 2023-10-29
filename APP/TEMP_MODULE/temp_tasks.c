/*
 * temp_tasks.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#include "temp_tasks.h"

extern xQueueHandle xQueue_temperature_value;

extern TaskHandle_t Handle_temperature_init_task;

Temp_Sensor_t TEMP_SENSOR = {
                             .sensorPort = PORTE_ID,
                             .sensorPin = PIN3_ID,
                             .adcChannel = CH_0,
                             .sequencer = SS_3,
                             .sample = S_0,
                             .adc_module = ADC_1,
                             .temp_sensor_mode =YES

};

void temperature_init_task(void*ptr)
{
    /*TEMP_Sensor init*/
    temperature_sensor_init(&TEMP_SENSOR);

    vTaskDelete(Handle_temperature_init_task);
}

void temperature_update_task(void *ptr)
{
    int32_t temperature_value=0 ;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        temperature_value = temperature_sensor_reading(&TEMP_SENSOR);
        temperature_value = (147.5 - ((75*3.3*temperature_value)/4096));

        xQueueSendToBack(xQueue_temperature_value, &temperature_value, 5);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}



