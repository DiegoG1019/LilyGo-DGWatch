#include <LilyGoWatch.h>
#include "App.h"

void AppTaskCode(void* params) {
    Log::Debug("Initializing App task code", AppFileName, 5);

    Log::Verbose("Casting params to AppParams", AppFileName, 6);
    App::AppParams* parms = static_cast<App::AppParams*>(params);

    Log::Debug("Running app");
    parms->AppPtr->Run(parms->params);
    //If the app needs to stop, then either run or the app manager should call "Finish" on it. If it returns, it's an error.
    char* str = nullptr;
    Log::Error(String(parms->AppPtr->Name) + "'s App::Run returned unexpectedly", AppFileName, 19);
}

void App::Start(void* params) {
    Log::Debug(String("Starting app: ") + Name, AppFileName, 18);
    AppParams* p = new AppParams();
    p->AppPtr = this;
    p->params = params;
    _IsRunning = true;
    task = new Task(AppTaskCode, Name, StackSize, p, Priority, CoreID);
}

void App::Finalize() {
    Log::Debug("Finishing app", AppFileName, 31);
    _IsRunning = false;
    vTaskDelete(task->TaskHandle);
}