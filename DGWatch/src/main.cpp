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

#include "gui/gui.h"
#include "gui/screenshot.h"

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

App *AppList[AppCount]{
	new (ps_malloc(sizeof(Log))) Log(),
	new (ps_malloc(sizeof(BatteryApp))) BatteryApp(),
	new (ps_malloc(sizeof(MainMenu))) MainMenu()
};

void startlog()
{
	AppList[LogManagerID]->Initialize(nullptr);
	AppList[LogManagerID]->Start(nullptr);
}

constexpr auto Main_Filename = __FILE__;
int main()
{
	init();
	//-------Initialization
	Serial.begin(SERIAL_BAUDRATE);
	startlog();
	Log::Information("Initialized Logger, Initializing DGWatch system", Main_Filename, __LINE__);
	
	//I want these buffers to go out of scope
	{
		//name_max + tag_max + format + 3 digits for each version portion
		char buff[16 + 16 + 24 + (3*3)];
		sprintf(buff,"Runing %s v.%d.%d.%d-%s", System_Info.Name, System_Info.Version.Major, System_Info.Version.Build, System_Info.Version.Review, System_Info.Version.Tag);
		Log::Information(buff, Main_Filename, __LINE__);
	}

	{
		char buff[103];
		sprintf(buff, "Memory Report:\nTotal Heap: %d\nFree Heap: %d\nTotal PSRAM: %d\nFree PSRAM: %d",
		ESP.getHeapSize(),
		ESP.getFreeHeap(),
		ESP.getPsramSize(),
		ESP.getFreePsram());	
		Log::Debug(buff, Main_Filename, __LINE__);
	}
	

	Log::Verbose("Initializing Timer...", Main_Filename, __LINE__);
	timer = ps_new(Timer<TIMER_TASKS>);

	Log::Verbose("Obtaining Watch handle", Main_Filename, __LINE__);
	ttgo = TTGOClass::getWatch();

	Log::Information("Starting Watch", Main_Filename, __LINE__);
	ttgo->begin();

	Log::Information("Initializing LVGL", Main_Filename, __LINE__);
	ttgo->lvgl_begin();

	Log::Information("Initializing SPIFFS", Main_Filename, __LINE__);
	SPIFFS.begin();

	Log::Debug("Setting up motor", Main_Filename, __LINE__);
	motor_setup();

	Log::Debug("Setting up display", Main_Filename, __LINE__);
	display_setup();

	Log::Verbose("Setting up Screenshots", Main_Filename, __LINE__);
	screenshot_setup();

	Log::Debug("Making sure SPIFFS is active", Main_Filename, __LINE__);
	if (!SPIFFS.begin())
	{
		Log::Warning("SPIFFS failed to activate, retrying", Main_Filename, __LINE__);
		SPIFFS.format();
		delay(500);
		if (!SPIFFS.begin())
		{
			Log::Fatal("SPIFFS could not be activated", Main_Filename, __LINE__);
			Fail();
		}
	}

	Log::Debug("Setting up powermgm", Main_Filename, __LINE__);
	powermgm_setup();

	//app pre init
	{
		Log::Information("PreInitializing Apps", Main_Filename, __LINE__);
		App::PreInitializationArguments_t args;
		for (int i = 0; i < AppCount; i++)
		{
			Log::Debug(String("PreInitializing app: ") + AppList[i]->Name, Main_Filename, __LINE__);
			AppList[i]->PreInitialize(args);
		}
	}
	Log::Information("Starting all StartUp Apps", Main_Filename, __LINE__);
	for (int i = 0; i < AppCount; i++)
		if (AppList[i]->StartUp)
			AppList[i]->Start(nullptr);

	//-------Running loop
	while (1)
	{
		timer->tick();
		powermgm_loop();
	}
	Log::Fatal("Running loop broke unexpectedly", Main_Filename, __LINE__);
	Fail();
}
