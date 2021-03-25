/*
 Name:		DGWatch.ino
 Created:	1/18/2021 8:46:27 PM
 Author:	Diego Garcia
*/

#include <Arduino.h>
#include "config/config.h"
#include <LilyGoWatch.h>
#include <arduino-timer.h>
#include "Log.h"
#include "BatteryApp.h"
#include "StaticList.h"
#include "MainMenu.h"
#include "config/global.h"

constexpr const int AppCount = 3;
constexpr const int LogManagerID = 0;
constexpr const int BatteryAppID = 1;
constexpr const int MainMenuAppID = 2;

App* AppList[AppCount]{
	new Log(Log::LogLevel::_LOG_VERBOSITY),
	new BatteryApp(),
	new MainMenu(),
};

void startlog() {
	AppList[LogManagerID]->Initialize(nullptr);
	AppList[LogManagerID]->Start(nullptr);
}

bool LoadSystemStatus(){
	Log::Information("Attempting to load System_Status data from Flash Memory", __FILE__, __LINE__);
	uint32_t* addrs = reinterpret_cast<uint32_t*>(&System_Status);
	ESP.flashRead(reinterpret_cast<uintptr_t>(&System_Status_FLASH), addrs, sizeof(System_Status_t));
	Log::Information(System_Status.GetFormatted(), __FILE__, __LINE__);
	bool csd = System_Status.CorrectlyShutDown;
	System_Status.CorrectlyShutDown = false;
	return csd;
}

void SaveSystemStatus() {
	Log::Information("Attempting to save System_Status data to Flash Memory", __FILE__, __LINE__);
	if (!System_Status.Edited) {
		Log::Information("System_Settings has not been edited, no need to save.", __FILE__, __LINE__);
		return;
	}
	System_Status.CorrectlyShutDown = true;
	ESP.flashWrite(reinterpret_cast<uintptr_t>(&System_Status_FLASH), reinterpret_cast<uint32_t*>(&System_Status), sizeof(System_Status_t));
	Log::Information("Succesfully saved System_Status data to Flash Memory", __FILE__, __LINE__);
}

void ForceShutDown() {
	Log::ForceFlush();
	abort();
};

void DeepSleep() {
	SaveSystemStatus();
	Log::ForceFlush();
	ESP.deepSleep(UINT32_MAX);
};

int main() {
	init();
	//-------Initialization

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
		ESP.deepSleep(100);
	}
	Log::Fatal("Running loop broke unexpectedly", __FILE__, __LINE__);
	Log::ForceFlush();
	delay(5000);
	abort();
}
