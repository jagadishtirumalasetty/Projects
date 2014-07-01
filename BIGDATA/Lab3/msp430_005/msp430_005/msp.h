#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef _DEBUG
#define TRACK_INTERNALS 1
#else
#define TRACK_INTERNALS 0
#endif

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include <float.h>
#include <string.h>
#include <limits>
#include <string>

#include "types.h"
#include "vector3.h"
#include "gui2.h"
#include "eZ430_Chronos_CC.h"
#include "ppjoy.h"
#include "debug.h"

#include "mode.h"
#include "filter.h"

#define SPL_D_NODATA 0xFF
#define SPL_K_STAR   0x10
#define SPL_K_NUM    0x20
#define SPL_K_UP     0x30
#define SPL_T_MOUSE  0x01
#define SPL_T_KEY    0x02


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);

namespace msp
{
	namespace consts
	{
		extern char * settingsfile;
	}
	namespace settings
	{
		extern vector3 calibration;
		extern axis_mode currmode[MODEBOX_COUNT];
		extern std::string mode_string[MODEBOX_COUNT];
		extern int   x_sense,    y_sense;
		extern bool  x_invert,   y_invert;
		extern int   x_deadzone, y_deadzone;
		extern bool  x_wheel,    y_wheel;
		extern float cal_angle_x, cal_angle_y;
	}

	using settings::calibration;
	using settings::currmode;
	using settings::mode_string;
	using settings::cal_angle_x;
	using settings::cal_angle_y;

	extern bool is_mouse_on;
	extern bool is_com;
	extern bool is_spl;
	extern bool is_ppjoy;
	extern HANDLE ppjoy_port;
	extern handle window;
	extern handle startbutton;

	extern JOYSTICK_STATE JoyState;
	


	//extern POINT velocity;

	extern FILE* log;

	inline float SPL_X(DWORD data) { return (float)((int8)((data >>  8) & 0xFF)) - calibration.x; }
	inline float SPL_Y(DWORD data) { return (float)((int8)((data >> 16) & 0xFF)) - calibration.y; }
	inline float SPL_Z(DWORD data) { return (float)((int8)((data >> 24) & 0xFF)) - calibration.z; }
	inline uint8 SPL_D(DWORD data) { return (data) & 0xFF; }
	inline uint8 SPL_K(DWORD data) { return (data) & 0xF0; }
	inline uint8 SPL_T(DWORD data) { return (data) & 0x0F; }

	// UI infrastructure
	int  main();
	int  start_ui();
	void destroy_ui();
	int  check_ui_events();
	void sync_settings_to_ui();
	void sync_ui_to_settings();
	void set_status(const char * status);

	// COM
	//void toggle_enabled();
	int  start_com();
	void close_com();
	int  start_spl();
	void stop_spl();
	int  start_ppjoy();
	void close_ppjoy();

	// Calibrate
	void calibrate_watch();
	void calibrate_angle();

	// Mouse
	void toggle_mouse_control();
	void process_mouse_control();
	void move_mouse(int32 delta_x, int32 delta_y);
	void click_mouse(DWORD mouseevent);
	void set_joystick(int32 x, int32 y);

	// Transform
	void reset_transform();
	void transform(DWORD spldata);

	// Options
	int load_options();
	int save_options();

	inline vector3 tovector3(DWORD spldata)
	{ return vector3(SPL_X(spldata), SPL_Y(spldata), SPL_Z(spldata)); }


}



#endif