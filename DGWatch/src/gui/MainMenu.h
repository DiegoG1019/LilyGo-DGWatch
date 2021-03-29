#ifndef ICONBAR_H
#define ICONBAR_H

#include "App.h"
#include "config/config.h"
#include <LilyGoWatch.h>

class MainMenu : public App
{
private:
	static lv_area_t* _PrimaryIconSize;
	static uint8_t _PrimaryIconPadding;

	static lv_area_t* _SecondaryIconSize;
	static uint8_t _SecondaryIconScreenPadding;
	static uint8_t _SecondaryIconPrimaryNotifPadding;
	static uint8_t _SecondaryIconSecondaryNotifPadding;

public:
	MainMenu() : App("MainMenuApp", HIGH_PRIORITY, 30, PRIMARY_CORE) {
		_StartUp = true;

		_PrimaryIconSize = ps_new(lv_area_t);
		_SecondaryIconSize = ps_new(lv_area_t);

		_PrimaryIconPadding = 6;

		_SecondaryIconScreenPadding = 6;
		_SecondaryIconPrimaryNotifPadding = 3;
		_SecondaryIconSecondaryNotifPadding = 2;

		lv_area_set(_PrimaryIconSize, 0, 0, 52, 52);
		lv_area_set(_SecondaryIconSize, 0, 0, 28, 28);
	}

	//Icon Bar Size 240 x 240
	//It is assumed that IconBar is set to the top of the screen, and it's horizontal axis is elongated to the screen's size
	static int BarSize; //Its height
	static int ItemSize; //Size of each item along the size of the Bar. Each Item is allowed to take as much horizontal space as it needs.
	/// <summary>
	/// Where: *drawfunc(int x, int y, int width_height)
	/// </summary>
	static int AddBarIcon(void* drawfunc(int, int, int, __restrict App*), __restrict App* instance);
	void PreInitialize(PreInitializationArguments_t);
    void Initialize(void*);
    void Run(void*);
};

#endif