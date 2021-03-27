#ifndef CONNECTIVITYMANAGER_H
#define CONNECTIVITYMANAGER_H

#include "config/config.h"
#include "config/global.h"

class NetworkManagerApp : public App {
    public:
    NetworkManagerApp() : App("NetworkManager", DEFAULT_PRIORITY, 30, SECONDARY_CORE) {
        _StartUp = true;
    }
    void PreInitialize(PreInitializationArguments_t);
    void Initialize(void*);
    void Run(void*);
};

#endif