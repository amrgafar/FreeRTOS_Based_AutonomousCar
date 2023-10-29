/*
 * display_taskes.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#ifndef APP_DISPLAY_MOUDLE_DISPLAY_TASKS_H_
#define APP_DISPLAY_MOUDLE_DISPLAY_TASKS_H_

#include "../../LIB/std_types.h"

#include "../../HAL/LCD/lcd.h"

#include "../../MCAL/TIMER/timer.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void lcd_init_task(void*ptr);
void lcd_update_task(void *ptr);

void manage_time(void);

#endif /* APP_DISPLAY_MOUDLE_DISPLAY_TASKS_H_ */
