#include <iostream>
#include <fstream>
#include "msp.h"

//#define CONST_SENSE 100.0f

namespace msp
{
	extern handle stable_window;

	float still(float x, float tolerance);
	float still_xd(float x);
	float still_yd(float y);
	int   round(float x);

	vector3      acc_low;
	//vector3      acc_low_1;
	vector3      acc_high;
	//vector3      acc_high_1;
	//vector3      acc_deriv;
	vector3      acc_joy;

	float angle_x;
	float angle_x_1;
	float angle_y;
	float angle_y_1;

	DWORD spldata_1;

	int32 been_clicking   = 0;
	POINT last_stable_pos = {LONG_MIN, LONG_MIN};
	int32 last_stable_time = -10000;
	const int history_count = 4;
	POINT last_positions[history_count] = {{LONG_MIN, LONG_MIN}, {LONG_MIN, LONG_MIN}};//, {LONG_MIN, LONG_MIN}};
	int history_pos = 0;

//	float velocity_x;

	struct DELTA32 {
		int32 x;
		int32 y;
	};

	exp_filter filter_exp_low(0.125f);
	exp_filter filter_exp_joy(0.5f);

//	dsp_filter butterworth_low(2.374f, -1.929f, 0.532f, 0.0f,
//	                   0.00290f, 0.00869f, 0.00869f, 0.00290f, 0.0f);

//	dsp_filter chebyshev_low(2.186f, -2.373f, 1.330f, -0.327f,
//	                 0.0109f, 0.0435f, 0.0653f, 0.0435f, 0.0109f);

//	dsp_filter high_filter(-0.9624f, -1.1433f, -0.5894f, -0.1926f,
//	                 0.0463f, -0.1851f, 0.2776f, -0.1851f, 0.0463f);
//	dsp_filter high_filter(-0.9624f, -1.1433f, -0.5894f, -0.1926f,
//	                       0.0463f, -0.1851f, 0.2776f, -0.1851f, 0.0463f);
	dsp_filter high_filter(-0.0931f, -0.7825f, -0.2303f, -0.1431f,
	                        0.0945f, -0.3781f, 0.5672f, -0.3781f, 0.0945f);


	void reset_transform()
	{
		last_stable_time = static_cast<int32>(GetTickCount()) - 10000;
	}

	void transform(DWORD spldata)
	{
		DELTA32 mouse = {0, 0};
		DELTA32 joy   = {0, 0};

		vector3 vdata = tovector3(spldata);

		std::ofstream myfile;
		myfile.open ("cronos_out.txt", std::ios::out | std::ios::app);
		myfile << vdata.x << " " << vdata.y << " " << vdata.z << "\n";
		myfile.close();

		acc_low = filter_exp_low(vdata);
		acc_joy = filter_exp_joy(vdata);
		acc_high = high_filter(vdata);
		//acc_deriv = acc_low - acc_low_1;
		
		//char buf[128];
		//sprintf_s(buf,"%f %f %f",acc_low.x, acc_low.y, acc_low.z);
		//set_status(buf);

		bool click = false;
		if (acc_high.norm() > 25.0f && (been_clicking != 0 || static_cast<int32>(GetTickCount()) - last_stable_time < 2000))
		{
			//messagef("hi","%f",acc_low.norm());
			//Sleep(1000);
			been_clicking++;
		}
		else
			been_clicking = 0;

		      angle_y  = acc_low.angle_y();
		      angle_x  = acc_low.angle_xz();
		float angle_jy = acc_joy.angle_y();
		float angle_jx = acc_joy.angle_xz();
		float absangle_y = vector3::anglediff(angle_y, cal_angle_y);
		float absangle_x = vector3::anglediff(angle_x, cal_angle_x);
		float relangle_y = vector3::anglediff(angle_y,  angle_y_1);
		float relangle_x = vector3::anglediff(angle_x,  angle_x_1);
		float joyangle_y = vector3::anglediff(angle_jy, cal_angle_y);
		float joyangle_x = vector3::anglediff(angle_jx, cal_angle_x);

		//fprintf(datalog,"%f\t%f\t%f\t%f\t%f\t%f\n",acc_low.angle_x(),acc_low.angle_y(),acc_low.angle_z(),acc_low.angle_yz(),acc_low.angle_x(),acc_low.angle_xy());


		// Mouse Status
		CURSORINFO cur_info;
		cur_info.cbSize = sizeof cur_info;
		GetCursorInfo(&cur_info);
		bool mouse_visible = (cur_info.flags & CURSOR_SHOWING) != 0;

		// Current mode
		axis_mode x_mode = (mouse_visible)? currmode[X_BOX] : currmode[X_HIDDEN];
		axis_mode y_mode = (mouse_visible)? currmode[Y_BOX] : currmode[Y_HIDDEN];
		
		if (been_clicking != 0)
		{
			if (been_clicking == 1)
			{
				SetCursorPos(last_stable_pos.x, last_stable_pos.y);
				click_mouse(MOUSEEVENTF_LEFTDOWN);
				click_mouse(MOUSEEVENTF_LEFTUP);
			}
			else if (been_clicking == 20)
			{
				click_mouse(MOUSEEVENTF_LEFTDOWN);
				click_mouse(MOUSEEVENTF_LEFTUP);
				Sleep(50);
				click_mouse(MOUSEEVENTF_LEFTDOWN);
				click_mouse(MOUSEEVENTF_LEFTUP);
			}
			joy.x = joy.y = INT32_MIN;
		}
		if (angle_y < 0.4f)
		{
			if (y_mode == MODE_MOUSE)
				mouse.y = -4;
			joy.x = joy.y = INT32_MIN;
		}
		else if(angle_y > vector3::pi() - 0.4f)
		{
			if (y_mode == MODE_MOUSE)
				mouse.y = 4;
			joy.x = joy.y = INT32_MIN;
		}
		else
		{
			// Y motion
			if (y_mode == MODE_MOUSE)
			{
				float y_float = still_yd(relangle_y) * 1000.0f * settings::y_sense/5.0f;
				mouse.y       = round(y_float);
			}
			else if (y_mode == MODE_MOUSEJOY)
			{
				float y_float = still_yd(absangle_y) * 30.0f * settings::y_sense/5.0f;
				mouse.y       = round(y_float);
			}
			else if (y_mode == MODE_PPJOY) 
			{
				float y_float = still_yd(joyangle_y) / (vector3::pi()/3.0f) * settings::y_sense/5.0f;
				joy.y         = round((y_float * PPJOY_SIGNED_MAX));
			}
			/* MODE_NONE */

			// X motion
			if (x_mode == MODE_MOUSE)
			{
				float x_float = still_xd(relangle_x) * 800.0f * settings::x_sense/5.0f;
				mouse.x       = round(x_float);
			}
			else if (x_mode == MODE_MOUSEJOY)
			{
				float x_float = still_xd(absangle_x) * 30.0f * settings::x_sense/5.0f;
				mouse.x       = round(x_float);
			}
			else if (x_mode == MODE_PPJOY)
			{
				float x_float = still_xd(joyangle_x) / (vector3::pi()/3.0f) * settings::x_sense/5.0f;
				joy.x         = round((x_float * PPJOY_SIGNED_MAX));
			}
			/* MODE_NONE */
		}


		// Wheel mode
		if (settings::y_wheel)
		{
			if (abs(relangle_x) > 0.03f)
			{
				mouse.y = 0;
				joy.y = INT32_MIN;
			}
			else if (abs(absangle_x) > 0.5f)
				joy.y = INT32_MIN;
		}
		if (settings::x_wheel)
		{
			if (abs(relangle_y) > 0.03f)
			{
				mouse.x = 0;
				joy.x = INT32_MIN;
			}
			else if (abs(absangle_y) > 0.5f)
				joy.x = INT32_MIN;
		}

		// Inversion
		// !settings::x_invert because "positive" values above are for a right handed watch
		if (mouse.x != INT32_MIN && !settings::x_invert) mouse.x = -mouse.x;
		if (mouse.y != INT32_MIN && !settings::y_invert) mouse.y = -mouse.y;
		if (  joy.x != INT32_MIN && !settings::x_invert)   joy.x =   -joy.x;
		if (  joy.y != INT32_MIN && !settings::y_invert)   joy.y =   -joy.y;

		//fprintf(datalog,"%8x\n",spldata & 0xFF);
		// Button clicking
		if (SPL_K(spldata) != SPL_K_STAR && SPL_K(spldata_1) == SPL_K_STAR)
			click_mouse(MOUSEEVENTF_WHEEL | MOUSEEVENTF_MIDDLEUP);
		else if (SPL_K(spldata) != SPL_K_NUM && SPL_K(spldata_1) == SPL_K_NUM)
			click_mouse(MOUSEEVENTF_WHEEL | MOUSEEVENTF_MIDDLEDOWN);
		else if (SPL_K(spldata) == SPL_K_UP && SPL_K(spldata_1) != SPL_K_UP)
			click_mouse(MOUSEEVENTF_RIGHTDOWN);
		else if (SPL_K(spldata) != SPL_K_UP && SPL_K(spldata_1) == SPL_K_UP)
			click_mouse(MOUSEEVENTF_RIGHTUP);

		// Move the mouse
		move_mouse(mouse.x, mouse.y);

		// Move the joystick
		set_joystick(joy.x, joy.y);

		GetCursorPos(&last_positions[history_pos]);
		
		int32 instability = 0;
		const POINT & last_pos = last_positions[history_pos];
		for (int i = 0; i < history_count - 1; i++)
			instability += abs(last_pos.x - last_positions[i].x) + abs(last_pos.y - last_positions[i].y);

		if (instability <= (history_count * (settings::x_sense + settings::y_sense + 6 - settings::x_deadzone - settings::y_deadzone) + 5)/10
			&& been_clicking == 0)
		{
			last_stable_pos = last_positions[history_pos];
			last_stable_time = static_cast<int32>(GetTickCount());
#if TRACK_INTERNALS
			moveGadget(stable_window,last_stable_pos.x-5,last_stable_pos.y-5);
#endif
		}

		history_pos = (history_pos+1) % history_count;

		// Save last round of data
		//acc_low_1  = acc_low;
		//acc_high_1 = acc_high;
		angle_x_1  = angle_x;
		angle_y_1  = angle_y;
		spldata_1  = spldata;

		return;
	}


	inline float still(float x, float tolerance)
	{
		if (x < -tolerance)
			return x + tolerance;
		else if (x > tolerance)
			return x - tolerance;
		else
			return 0.0f;
	}
	inline float still_xd(float x)
	{
		return still(x, (settings::x_deadzone) / 600.0f);
	}
	inline float still_yd(float y)
	{
		return still(y, (settings::y_deadzone) / 600.0f);
	}

	inline int round(float x)
	{
		return static_cast<int>(floor(x + 0.5f));
	}



}