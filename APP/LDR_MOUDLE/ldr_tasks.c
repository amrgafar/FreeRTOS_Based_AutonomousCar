/*
 * display_taskes.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#include <APP/LDR_MOUDLE/ldr_tasks.h>


#define LDR_SET_POINT_POSTIVE  500

extern xQueueHandle xQueue_LDR_Difference_LCD;
extern xQueueHandle xQueue_LDR_Difference;

extern TaskHandle_t Handle_ldr_init_task;

extern xSemaphoreHandle xBinarySemaphore_LDR;



LDR_Sensor_t LDR1 = {
                     .ldrPort = PORTE_ID,
                     .ldrPin = PIN1_ID,
                     .adcChannel = CH_1,
                     .sequencer = SS_0,
                     .sample = S_0,
                     .adc_module = ADC_0,
                     .temp_sensor_mode =NO

};

LDR_Sensor_t LDR2 = {
                     .ldrPort = PORTE_ID,
                     .ldrPin = PIN2_ID,
                     .adcChannel = CH_2,
                     .sequencer = SS_0,
                     .sample = S_0,
                     .adc_module = ADC_1,
                     .temp_sensor_mode =NO
};

void ldr_init_task(void*ptr)
{
    /*LDRs init*/
    ldr_sensor_init(&LDR1);
    ldr_sensor_init(&LDR2);

    vTaskDelete(Handle_ldr_init_task);
}

void ldr_update_task(void *ptr)
{
    uint16_t LDR1_Read = 0U;
    uint16_t LDR2_Read = 0U;
    int32_t LDR_Difference = 0U;

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        LDR1_Read = ldr_sensor_reading(&LDR1);
        LDR2_Read = ldr_sensor_reading(&LDR2);

        LDR_Difference = LDR1_Read - LDR2_Read;

        xQueueSendToBack(xQueue_LDR_Difference, &LDR_Difference, 5);
        xQueueSendToBack(xQueue_LDR_Difference_LCD, &LDR_Difference, 5);

        /*check LDRs value*/
        if((LDR_Difference > 0) && (LDR_SET_POINT_POSTIVE > LDR_Difference))
        {
            /*do nothing*/
        }
        else
        {
            xSemaphoreGive(xBinarySemaphore_LDR);
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(40));
    }
}



