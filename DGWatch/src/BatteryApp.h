#ifndef BATTERYAPP_H
#define BATTERYAPP_H

#include "App.h"
#include "config/global.h"
#include "config/errors.h"

class BatteryApp : public App {
private:
    static const int ReportInterval = 60 * 1000; //1 minute
    static const int PercentageInterval = 5 * 1000; //5 seconds
    static const int ReportBufferSize = 550; //~9 hours worth of battery reports, for 20kb
    struct BatteryReport {
        float USB_Voltage;
        float USB_Current;
        float Battery_Voltage;
        float Temperature;
        float Battery_Charge_Current;
        int Power_Percentage;
        bool Is_Charging : 1;
        bool Is_Done_Charging : 1;
        bool Is_Battery_Connected : 1;
        RTC_Date IssueDate;
    };
    ArraySequence<BatteryReport>* ReportsBuffer;
    Task* BatteryPercentageTask;
    static BatteryReport* latest;
    static float Battery_Percentage;
    static void WatchBatteryPercentage(void*);
public:
    inline static float GetBatteryPercentage() {
        return Battery_Percentage;
    }
    inline static BatteryReport* GetLatest() {
        return latest;
    }
    BatteryApp() : App("BatteryDisplay", LOW_CPU_TIME, 5, SECONDARY_CORE) {
        _StartUp = true;
        ReportsBuffer = ps_new(ArraySequence<BatteryReport>, ReportBufferSize, false, true);
    };
    void PreInitialize(PreInitializationArguments_t params);
    void Initialize(void*);
    void Run(void*);
    ~BatteryApp() {
        delete ReportsBuffer;
    };
};
#endif