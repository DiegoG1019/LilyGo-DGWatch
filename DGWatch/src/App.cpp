#include <LilyGoWatch.h>
#include "App.h"
#include "Log.h"

void AppTaskCode(void* params) {
    Log::Debug("Initializing App task code", __FILE__, __LINE__);

    Log::Verbose("Casting params to AppParams", __FILE__, __LINE__);
    App::AppParams* parms = static_cast<App::AppParams*>(params);

    Log::Debug("Running app");
    parms->AppPtr->Run(parms->params);
    //If the app needs to stop, then either run or the app manager should call "Finish" on it. If it returns, it's an error.
    Log::Error(String(parms->AppPtr->Name) + "'s App::Run returned unexpectedly", __FILE__, __LINE__);
}

void App::Start(void* params) {
    Log::Debug(String("Starting app: ") + Name, __FILE__, __LINE__);
    AppParams* p = new AppParams();
    p->AppPtr = this;
    p->params = params;
    _IsRunning = true;
    task = new Task(AppTaskCode, Name, StackSize, p, Priority, CoreID);
}

void App::Finalize() {
    Log::Debug("Finishing app", __FILE__, __LINE__);
    _IsRunning = false;
    vTaskDelete(task->TaskHandle);
}