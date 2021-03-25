#ifndef DGTASK_H
#define DGTASK_H

#include <FreeRTOS.h>

class Task {
private:
    BaseType_t _TaskID;
public:
    Task(const Task&) = delete;
    const char* Name;
    const BaseType_t& TaskID;
    TaskHandle_t* TaskHandle;
    Task(
        TaskFunction_t pvTaskCode,
        const char* const pcName,
        const uint32_t usStackDepth,
        void* const pvParameters,
        UBaseType_t uxPriority) : TaskID(_TaskID)
    {
        Name = pcName;
        _TaskID = xTaskCreate(pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, TaskHandle);
    }
    Task(
        TaskFunction_t pvTaskCode,
        const char* const pcName,
        const uint32_t usStackDepth,
        void* const pvParameters,
        UBaseType_t uxPriority,
        const BaseType_t xCoreID) : TaskID(_TaskID)
    {
        Name = pcName;
        _TaskID = xTaskCreatePinnedToCore(pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, TaskHandle, xCoreID);
    }
    void Terminate() {
        vTaskDelete(TaskHandle);
    }
};

#endif