#ifndef ICONBAR_H
#define ICONBAR_H

#include "App.h"

class MainMenu : public App
{
public:
	struct Area_t {
	private:
		uint16_t _width;
		uint16_t _height;
	public:
		const uint16_t& Width;
		const uint16_t& Height;
		Area_t(uint16_t w, uint16_t h) : Width(_width), Height(_height) {
			_width = w;
			_height = h;
		};
	};
private:
	static Area_t _ScreenArea;
	static Area_t _DrawableArea;
	static Area_t _IconBarItemSize;
	static Area_t _IconBarSize;
	static Area_t _MainMenuIconSize;
public:
	MainMenu() : App("MainMenuApp", HIGH_PRIORITY, 2, PRIMARY_CORE) {
		_StartUp = true;
		_ScreenArea = Area_t(240, 240);
	}

	//Icon Bar Size 240 x 320
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