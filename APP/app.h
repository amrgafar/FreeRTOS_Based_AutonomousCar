/*
 * app.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Kareem Abdelrasheed
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include <APP/DISPLAY_MOUDLE/display_tasks.h>
#include <APP/LDR_MOUDLE/ldr_tasks.h>
#include <APP/ULTRA_MOUDLE/ultrasonic_tasks.h>
#include "BUTTON_MOUDLE/button_taskes.h"
#include "MOVEMENT_MODULE/movement_tasks.h"
#include "TEMP_MODULE/temp_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

void APP_SysCreate(void);

void APP_SysOn(void);


#endif /* APP_APP_H_ */
