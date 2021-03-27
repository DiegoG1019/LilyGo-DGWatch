#include "ConnectivityManager.h"
#include <Arduino.h>

void NetworkManager::PreInitialize(PreInitializationArguments_t) {
}

void NetworkManager::Initialize(void*){
    if ( wifictl_get_autoon() && ( pmu_is_charging() || pmu_is_vbus_plug() || ( pmu_get_battery_voltage() > 3400) ) )
        wifictl_on();
    blectl_setup();
}

void NetworkManager::Run(void*){
    while(1){
        delay(UINT32_MAX);
    }
}