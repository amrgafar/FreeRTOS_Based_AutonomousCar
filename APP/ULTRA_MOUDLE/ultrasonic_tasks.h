/*
 * display_taskes.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#ifndef APP_ULTRA_MOUDLE_ULTRSONIC_TASKES_H_
#define APP_ULTRA_MOUDLE_ULTRSONIC_TASKES_H_

#include "../../HAL/ULTRASONIC/ultrasonic_sensor.h"

#include "../../MCAL/GPIO/gpio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


void ultrasonic_init_task(void*ptr);
void ultrasonic_update_task(void *ptr);


#endif /* APP_ULTRA_MOUDLE_ULTRSONIC_TASKES_H_ */
