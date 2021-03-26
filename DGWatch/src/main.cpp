/*
 Name:		DGWatch.ino
 Created:	1/18/2021 8:46:27 PM
 Author:	Diego Garcia
*/

#include "config/config.h"
#include "config/global.h"
#include <Arduino.h>
#include "esp_bt.h"
#include "esp_task_wdt.h"
#include <LilyGoWatch.h>
#include <arduino-timer.h>
#include "Log.h"
#include "BatteryApp.h"
#include "StaticList.h"
#include "MainMenu.h"

#include "hardware/display.h"
#include "hardware/powermgm.h"
#include "hardware/motor.h"
#include "hardware/wifictl.h"
#include "hardware/blectl.h"
#include "hardware/pmu.h"
#include "hardware/timesync.h"
#include "hardware/sound.h"
#include "hardware/callback.h"

constexpr const int AppCount = 3;

constexpr const int LogManagerID = 0;
constexpr const int BatteryAppID = 1;
constexpr const int MainMenuAppID = 2;

App* AppList[AppCount]{
	new Log(),
	new BatteryApp(),
	new MainMenu(),
};

void startlog() {
	AppList[LogManagerID]->Initialize(nullptr);
	AppList[LogManagerID]->Start(nullptr);
}

int main() {
	init();
	//-------Initialization
	ttgo = TTGOClass::getWatch();
	startlog();
	Log::Information("Initialized Logger, Initializing DGWatch system", __FILE__, __LINE__);

	Log::Verbose("Initializing Timer...", __FILE__, __LINE__);
	timer = new Timer<TIMER_TASKS>();

	Log::Verbose("Obtaining Watch handler", __FILE__, __LINE__);
	ttgo = TTGOClass::getWatch();

	Log::Verbose("Starting Watch", __FILE__, __LINE__);
	ttgo->begin();

	Log::Verbose("Initializing LVGL", __FILE__, __LINE__);
	ttgo->lvgl_begin();

	Log::Debug("Checking RTC Clock", __FILE__, __LINE__);
	ttgo->rtc->check();

	Log::Debug("Synching System to RTC", __FILE__, __LINE__);
	ttgo->rtc->syncToRtc();

	//app pre init
	{
		Log::Information("PreInitializing Apps", __FILE__, __LINE__);
		App::PreInitializationArguments_t args;
		for (int i = 0; i < AppCount; i++) {
			Log::Debug(String("PreInitializing app: ") + AppList[i]->Name, __FILE__, __LINE__);
			AppList[i]->PreInitialize(args);
		}
	}
	Log::Information("Starting all StartUp Apps", __FILE__, __LINE__);
	for (int i = 0; i < AppCount; i++)
		if (AppList[i]->StartUp)
			AppList[i]->Start(nullptr);

	//-------Running loop
	while (1) {
		timer->tick();
	}
	Log::Fatal("Running loop broke unexpectedly", __FILE__, __LINE__);
	Log::ForceFlush();
	delay(5000);
	abort();
}
