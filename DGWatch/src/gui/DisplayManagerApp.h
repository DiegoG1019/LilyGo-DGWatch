#ifndef DISPLAYMAN_H
#define DISPLAYMAN_H

#include "config/config.h"
#include "hardware/display.h"

constexpr auto Display_Filename = __FILENAME__;
class DisplayManager : public App {
    private:
	static lv_area_t* _ScreenArea;
public:

    DisplayManager() : App("DisplayManagerApp", HIGH_PRIORITY, STACK_SIZE_SMALL, PRIMARY_CORE){
		_ScreenArea = ps_new(lv_area_t);
		lv_area_set(_ScreenArea, 0, 0, 240, 240);
        
        Log::Debug("Setting up display", Display_Filename, __LINE__);
        display_setup();
    }

    uint32_t GetBrightness(){
        return display_get_brightness();
    }

    void SetBrightness(uint32_t brightness){
        display_set_brightness(brightness);
    }

}

#endif