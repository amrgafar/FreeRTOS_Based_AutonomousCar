/*
 * display_taskes.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#ifndef APP_BUTTON_MOUDLE_BUTTON_TASKES_H_
#define APP_BUTTON_MOUDLE_BUTTON_TASKES_H_

#include <APP/DISPLAY_MOUDLE/display_tasks.h>
#include "../../HAL/SWITCH/switch.h"

#include "../../MCAL/GPIO/gpio.h"

#include "../ROBOT/robot.h"
#include "FreeRTOS.h"
#include "task.h"

void switches_init_task(void*ptr);
void switches_update_task(void *ptr);


#endif /* APP_BUTTON_MOUDLE_BUTTON_TASKES_H_ */
