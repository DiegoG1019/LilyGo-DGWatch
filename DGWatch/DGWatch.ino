/*
 Name:		DGWatch.ino
 Created:	1/18/2021 8:46:27 PM
 Author:	Diego Garcia
*/

// the setup function runs once when you press reset or power the board


#include "config.h"
#include "Exceptions.h"
#include <LilyGoWatch.h>
#include <arduino-timer.h>
#include "Log.h"
#include "BatteryApp.h"
#include "StaticList.h"
#include "MainMenu.h"

TTGOClass* ttgo;
Timer<TIMER_TASKS>* timer;

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
	Log::Information("Attempting to load System_Status data from Flash Memory", DGWatch_ino, 39);
	uint32_t* addrs = reinterpret_cast<uint32_t*>(&System_Status);
	ESP.flashRead(reinterpret_cast<uintptr_t>(&System_Status_FLASH), addrs, sizeof(System_Status_t));
	Log::Information(System_Status.GetFormatted(), DGWatch_ino, 43);
	bool csd = System_Status.CorrectlyShutDown;
	System_Status.CorrectlyShutDown = false;
	return csd;
}

void SaveSystemStatus() {
	Log::Information("Attempting to save System_Status data to Flash Memory", DGWatch_ino, 47);
	System_Status.CorrectlyShutDown = true;
	ESP.flashWrite(reinterpret_cast<uintptr_t>(&System_Status_FLASH), reinterpret_cast<uint32_t*>(&System_Status), sizeof(System_Status_t));
	Log::Information("Succesfully saved System_Status data to Flash Memory", DGWatch_ino, 43);
}

void ForceShutDown() {
	SaveSystemStatus();
	Log::ForceFlush();
	abort();
};

void ShutDown() {
	SaveSystemStatus();
	Log::ForceFlush();
	ESP.deepSleep()
};

constexpr const char* DGWatch_ino = "DGWatch.ino";
int main() {
	init();
	//-------Initialization

	startlog();
	Log::Information("Initialized Logger, Initializing DGWatch system", DGWatch_ino, 43);

	Log::Verbose("Initializing Timer...", DGWatch_ino, 47);
	timer = new Timer<TIMER_TASKS>();

	Log::Verbose("Obtaining Watch handler", DGWatch_ino, 50);
	ttgo = TTGOClass::getWatch();

	Log::Verbose("Starting Watch", DGWatch_ino, 53);
	ttgo->begin();

	Log::Verbose("Initializing LVGL", DGWatch_ino, 56);
	ttgo->lvgl_begin();

	//Check if the RTC clock matches, if not, use compile time
	Log::Debug("Checking RTC Clock", DGWatch_ino, 60);
	ttgo->rtc->check();

	Log::Debug("Synching System to RTC", DGWatch_ino, 63);
	ttgo->rtc->syncToRtc();

	//app pre init
	{
		Log::Information("PreInitializing Apps", DGWatch_ino, 76);
		App::PreInitializationArguments_t args;
		for (int i = 0; i < AppCount; i++) {
			Log::Debug(String("PreInitializing app: ") + AppList[i]->Name, DGWatch_ino, 80);
			AppList[i]->PreInitialize(args);
		}
	}
	Log::Information("Starting all StartUp Apps", DGWatch_ino, 83);
	for (int i = 0; i < AppCount; i++)
		if (AppList[i]->StartUp)
			AppList[i]->Start(nullptr);

	//-------Running loop
	while (1) {
		timer->tick();
		delay(100);
	}
	char* str = nullptr;
	Log::Fatal("Running loop broke unexpectedly", DGWatch_ino, 74);
	Log::ForceFlush();
	delay(5000);
	abort();
}

inline int MemoryUnits(int bytes, int unit = 1) {
    return bytes / (1024 * unit);
}
