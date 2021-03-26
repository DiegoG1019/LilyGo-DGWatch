// This is the basic config file that defines which
// LILYGO product you are compiling for
#ifndef CONFIG_H
#define CONFIG_H

#define LILYGO_WATCH_2020_V1              // Use T-Watch2020
#define LILYGO_WATCH_LVGL 

#define DEBUG
#ifdef DEBUG
#define LOG_RAM
#define LOG_DEBUG
#define LOG_BATTERY_REPORTS
#define _LOG_VERBOSITY Verbose
#endif

#include "WString.h"

constexpr int LOG_MESSAGE_BUFFER_SIZE = 80;
constexpr int LOG_FLUSH_TIMER = 10000;
constexpr int LOG_FLUSH_TASK_DIVIDE = 8;

constexpr int TIMER_TASKS = 1;

constexpr int PRIMARY_CORE = 1;
constexpr int SECONDARY_CORE = 0;

constexpr int LOW_PRIORITY = 0;
constexpr int DEFAULT_PRIORITY = 1;
constexpr int HIGH_PRIORITY = 2;
/// <summary>
/// Reserved for tasks that run only once at intervals of minutes or more, and perform little operations
/// </summary>
constexpr int LOW_CPU_TIME = 3;

struct System_Status_t {
    bool FirstRun : 1;
    bool Edited : 1;
    bool CorrectlyShutDown : 1;
    bool SystemLock : 1;
    String GetFormatted() {
        String str = "SysStatus: ";
        return str + "FirstRun(" + FirstRun + ") | CorrectlyShutDown(" + CorrectlyShutDown + ")";
    }
    System_Status_t() {
        FirstRun = true;
        CorrectlyShutDown = false;
        Edited = false;
    }
    void NotifyGoodShutdown() {
        Edited = true;
        CorrectlyShutDown = true;
    };
private:
    inline void edit(String str, int value) {
        Edited = true; 
    };
};
PROGMEM System_Status_t System_Status_FLASH;
System_Status_t System_Status;

struct {
    struct {
        const uint8_t Major = 0;
        const uint8_t Review = 0;
        const uint8_t Build = 0;
        const char* Tag = "Alpha";
    } Version;
    const char* Name = "DGWatch";
} System_Info;

inline int MemoryUnits(int bytes, int unit = 1) {
    return bytes / (1024 * unit);
}

#endif