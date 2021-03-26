#include "BatteryApp.h"

void BatteryApp::PreInitialize(PreInitializationArguments_t args) {
    
}

void BatteryApp::WatchBatteryPercentage(void*) {
    ttgo->power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);
    Battery_Percentage = ttgo->power->getBattPercentage();
    ttgo->power->adc1Enable(NULL, false);
    delay(PercentageInterval);
}

void BatteryApp::Initialize(void*){
    BatteryPercentageTask = new Task(WatchBatteryPercentage, "Watch Battery Percentage Task", 2, nullptr, Priority, CoreID);
}

void BatteryApp::Run(void*) {
    BatteryReport* firstreport = ReportsBuffer->Next();
    ttgo->power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);
    firstreport->USB_Voltage = ttgo->power->getVbusVoltage();
    firstreport->USB_Current = ttgo->power->getVbusCurrent();
    firstreport->Temperature = ttgo->power->getTemp();
    firstreport->Is_Battery_Connected = ttgo->power->isBatteryConnect();
    firstreport->Battery_Voltage = ttgo->power->getBattVoltage();
    firstreport->Battery_Charge_Current = ttgo->power->getBattChargeCurrent();
    firstreport->Power_Percentage = ttgo->power->getBattPercentage();
    firstreport->Is_Charging = ttgo->power->isChargeing();
    firstreport->Is_Done_Charging = ttgo->power->isChargingDoneIRQ();
    firstreport->IssueDate = ttgo->rtc->getDateTime();
    ttgo->power->adc1Enable(NULL, false);
    latest = firstreport;
    delay(ReportInterval);
}