#ifndef ICONBAR_H
#define ICONBAR_H

#include "App.h"
#include <LilyGoWatch.h>

class MainMenu : public App
{
private:
	static lv_area_t* _ScreenArea;
	static lv_area_t* _DrawableArea;
	static lv_area_t* _IconBarItemSize;
	static lv_area_t* _IconBarSize;
	static lv_area_t* _MainMenuIconSize;
	static lv_area_t* _MainMenuIconCellSize;
	static lv_area_t* _BatteryBarSize;
public:
	MainMenu() : App("MainMenuApp", HIGH_PRIORITY, 2, PRIMARY_CORE) {
		_StartUp = true;

		_ScreenArea = new (ps_malloc(sizeof(lv_area_t))) lv_area_t();
		_DrawableArea = new (ps_malloc(sizeof(lv_area_t))) lv_area_t();
		_IconBarItemSize = new (ps_malloc(sizeof(lv_area_t))) lv_area_t();
		_IconBarSize = new (ps_malloc(sizeof(lv_area_t))) lv_area_t();
		_MainMenuIconSize = new (ps_malloc(sizeof(lv_area_t))) lv_area_t();
		_MainMenuIconCellSize = new (ps_malloc(sizeof(lv_area_t))) lv_area_t();
		_BatteryBarSize = new (ps_malloc(sizeof(lv_area_t))) lv_area_t();

		lv_area_set(_ScreenArea, 0, 0, 240, 240);
		lv_area_set(_DrawableArea, 0, 0, 240, 240 - 25);
		lv_area_set(_IconBarItemSize, 0, 0, 16, 16);
		lv_area_set(_IconBarSize, 0, 0, 240, 22);
		lv_area_set(_MainMenuIconSize, 0, 0, 52, 52);
		lv_area_set(_MainMenuIconCellSize, 0, 0, 78, 78);
		lv_area_set(_BatteryBarSize, 0, 0, 240, 3);
	}

	//Icon Bar Size 240 x 240
	//It is assumed that IconBar is set to the top of the screen, and it's horizontal axis is elongated to the screen's size
	static int BarSize; //Its height
	static int ItemSize; //Size of each item along the size of the Bar. Each Item is allowed to take as much horizontal space as it needs.
	/// <summary>
	/// Where: *drawfunc(int x, int y, int width_height)
	/// </summary>
	static int AddBarIcon(void* drawfunc(int, int, int, __restrict App*), __restrict App* instance);
};
int IconBarSize = 18;
int IconBarItemSize = 16;

#endif