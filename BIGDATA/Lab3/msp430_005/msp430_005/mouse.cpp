#include "msp.h"

namespace msp
{
	bool is_mouse_on = false;
	JOYSTICK_STATE  JoyState;

	void toggle_mouse_control()
	{
		if (!is_mouse_on) // Switching to mouse control
		{
			if (!is_com) start_com();
			if (is_com)
			{
				start_spl();
				is_mouse_on = true;
				setGadgetText(startbutton,"Stop");
				reset_transform();
			}
		}
		else
		{
			stop_spl();
			is_mouse_on = false;
			setGadgetText(startbutton,"Start");
		}
	}

	void process_mouse_control()
	{
		DWORD data;
		bool is_data = BM_SPL_GetData(data);

		if (!is_data || SPL_D(data) == SPL_D_NODATA) return;

		// Do the actual mouse movement
		transform(data);

	}

/*	void move_mouse(int32 delta_x, int32 delta_y)
	{
		POINT ptCursorPos;
		GetCursorPos(&ptCursorPos);
//		if (ptCursorPos.x == 0 || ptCursorPos.x == 1439)
//			velocity.x = 0;
		SetCursorPos(ptCursorPos.x + delta_x, ptCursorPos.y + delta_y);
	}*/

	void move_mouse(int32 delta_x, int32 delta_y)
	{
		INPUT inevent;
		inevent.type = INPUT_MOUSE;
		inevent.mi.dx = delta_x;
		inevent.mi.dy = delta_y;
		inevent.mi.mouseData = 0;
		inevent.mi.dwFlags = MOUSEEVENTF_MOVE;
		inevent.mi.time = 0;
		inevent.mi.dwExtraInfo = NULL;
		SendInput(1, &inevent, sizeof inevent);
	}
	
	void click_mouse(DWORD mouseevent)
	{
		INPUT inevent;
		inevent.type = INPUT_MOUSE;
		inevent.mi.dx = 0;
		inevent.mi.dy = 0;
		inevent.mi.time = 0;
		inevent.mi.dwExtraInfo = NULL;

		if ((mouseevent & MOUSEEVENTF_WHEEL) != 0)
		{
			inevent.mi.dwFlags   = MOUSEEVENTF_WHEEL;
			inevent.mi.mouseData = (mouseevent & MOUSEEVENTF_MIDDLEUP) != 0 ? WHEEL_DELTA : -WHEEL_DELTA;
		}
		else
		{
			inevent.mi.mouseData = 0;
			inevent.mi.dwFlags = mouseevent;
		}
				SendInput(1, &inevent, sizeof inevent);
	}

	void set_joystick(int32 x, int32 y)
	{
		if (!is_ppjoy) return;

		
		DWORD           RetSize;


		if (x != INT32_MIN)
			JoyState.Analog[0] = PPJOY_AXIS_0 + x;
		if (y != INT32_MIN)
			JoyState.Analog[1] = PPJOY_AXIS_0 + y;

		JoyState.Digital[0] = 0;

		BOOL joy_err = DeviceIoControl(ppjoy_port,IOCTL_PPORTJOY_SET_STATE,&JoyState,sizeof(JoyState),NULL,0,&RetSize,NULL);
		if (joy_err == 0)
		{
			DWORD err_code = GetLastError();
			if (err_code == ERROR_PPJOY_DELETED)
				close_ppjoy();
			else
				messagef("Error","PPJoy error: %d\n",err_code);
		}
	}
}