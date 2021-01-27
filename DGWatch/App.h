#ifndef APP_H
#define APP_H

#include "Task.h"

constexpr char* AppFileName = "App.cpp";
void AppTaskCode(void* params);
class App {
public:
    struct PreInitializationArguments_t {
        
    };
    struct AppParams {
        App* AppPtr;
        void* params;
    };
    const char *Name;
    const int& Priority;
    const int& StackSize;
    const int& CoreID;
    const bool& IsRunning;
    const bool& StartUp;
    App(const App&) = delete;
    App(const char* name, int priority, int stacksize, int coreid = tskNO_AFFINITY) : Priority(_Priority), StackSize(_StackSize), IsRunning(_IsRunning), CoreID(_CoreID), StartUp(_StartUp)
    {
        Name = name;
        _Priority = priority;
        _StackSize = stacksize;
        _IsRunning = false;
        _CoreID = coreid;
    };

    ~App() {
        if (IsRunning) {
            Finalize();
        }
    };
    
    //-----Life time of an App-----//
    //Every app is instanced and given an ID in DGWatch.ino as part of static memory initialization; before even Main is called
    //At this point ->App.ctor() is called
    //This is where apps should store all of their cache data that will live accross the lifetime of the system
    //
    //Next, all vital portions of the system (Logging, managers...) are properly initialized
    //After, and ONLY after this, each and every app has their respective App.PreInitialize() called
    //In Pre-Initialize, Apps should register themselves as startup and add their Main Menu Icons
    //
    //Then the list of apps that were registered as Start-up apps will all be started, but no screen control will be given
    //During startup, a new Task will be created that will call Initialize ONCE, and proceed to call Run, which should loop indefinitely.
    //The user is given full control of Run, no loop will be provided. If it ever returns, the task will log an error and terminate itself.
    //
    //Finally, if the user clicks on the icon in the Main Menu, a new task will be created that will run PARALLEL to Run
    //However, no synchronization will be necessary as it will invariably run in the same core; these two tasks should communicate through a Queue with very few members, which should be instanced in Initialize
    //This new task will call Activate ONCE, and proceed to expect Active to loop in a similar manner to Run.
    //When the application exits foreground, The task will call deactivate and terminate; thus deactivate should also wrap up any data Active may have running.
    //
    //Finally, if an application ever needs to fully terminate, if it isn't a background App or any of the sort, it will terminate itself through Finalize();


    /// <summary>
    /// Startup process for the App, not virtual
    /// </summary>
    /// <param name="params"></param>
    void Start(void* params);

    /// <summary>
    /// Function called by main as the system starts, only called once
    /// </summary>
    virtual void PreInitialize(PreInitializationArguments_t params) { }

    /// <summary>
    /// Initialization process for the App, right before it runs
    /// </summary>
    /// <param name="params"></param>
    virtual void Initialize(void* params) { };

    /// <summary>
    /// The running process of the App while it's live
    /// </summary>
    /// <param name="params"></param>
    virtual void Run(void* params); //Pure Virtual

    /// <summary>
    /// Activation process of the App when it should take hold of the screen
    /// </summary>
    /// <param name="params"></param>
    virtual void Activate(void* params);

    /// <summary>
    /// The running process of the App while it's active (on-screen)
    /// </summary>
    /// <param name="params"></param>
    virtual void Active(void* params); //Pure Virtual

    /// <summary>
    /// The function to be called once the application deactivates
    /// </summary>
    /// <param name="params"></param>
    virtual void Deactivate(void* params);

    /// <summary>
    /// If overriden, call this at the end of the overriding method. This deletes the task.
    /// </summary>
    virtual void Finalize();
protected:
    bool _StartUp : 1;
private:
    Task* task;
    bool _IsRunning : 1;
    int _StackSize;
    int _Priority;
    int _TaskID;
    int _CoreID;
    int _CacheSize;
};
#endif