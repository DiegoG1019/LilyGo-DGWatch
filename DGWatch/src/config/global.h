#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <arduino-timer.h>
#include "config.h"

TTGOClass* ttgo;
Timer<TIMER_TASKS>* timer;

template <class T>
inline T* ps_new(){
    return new (ps_malloc(sizeof(T))) T();
}
#endif