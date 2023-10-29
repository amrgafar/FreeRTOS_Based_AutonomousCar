/*
 * temp_tasks.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#ifndef APP_TEMP_MODULE_TEMP_TASKS_H_
#define APP_TEMP_MODULE_TEMP_TASKS_H_

#include "../../HAL/TEMP_SENSOR/temperture_sensor.h"

#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ADC/adc.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


void temperature_init_task(void*ptr);
void temperature_update_task(void *ptr);


#endif /* APP_TEMP_MODULE_TEMP_TASKS_H_ */
