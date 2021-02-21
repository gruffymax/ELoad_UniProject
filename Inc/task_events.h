#ifndef TASK_EVENTS_H
#define TASK_EVENTS_H

#define BUTTON_CP_MASK      0x00000080
#define BUTTON_CR_MASK      0x00000040
#define BUTTON_CV_MASK      0x00000020
#define BUTTON_CC_MASK      0x00000010
#define BUTTON_START_MASK   0x00000008
#define RE_BUTTON_MASK      0x00000004
#define CCW_EVENT_MASK      0x00000002
#define CW_EVENT_MASK       0x00000001

TaskHandle_t control_task_handle = NULL;

void task_events(void *arguments);

#endif //TASK_EVENTS_H
