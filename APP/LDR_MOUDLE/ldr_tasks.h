/*
 * display_taskes.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#ifndef APP_LDR_MOUDLE_LDR_TASKS_H_
#define APP_LDR_MOUDLE_LDR_TASKS_H_

#include "../../HAL/LDR/ldr_sensor.h"

#include "../../MCAL/GPIO/gpio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

void ldr_init_task(void*ptr);
void ldr_update_task(void *ptr);

#endif /* APP_LDR_MOUDLE_LDR_TASKS_H_ */
