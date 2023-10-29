/*
 * movement_tasks.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#ifndef APP_MOVEMENT_MODULE_MOVEMENT_TASKS_H_
#define APP_MOVEMENT_MODULE_MOVEMENT_TASKS_H_

#include "../ROBOT/robot.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


void movement_init_task(void*ptr);
void movement_obstacle_task(void*ptr);
void movement_swing_task(void*ptr);

#endif /* APP_MOVEMENT_MODULE_MOVEMENT_TASKS_H_ */
