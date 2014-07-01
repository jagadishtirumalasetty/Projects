
#include "msp.h"
#include "time.h"

namespace msp
{
	namespace settings
	{
		vector3 calibration;
	}

	vector3 get_current_acc();

	void calibrate_watch()
	{
		bool retry = true;
		int choice;
		vector3 oldcal;
		bool was_spl = is_spl;

		do
		{
			if (!is_com) start_com();
			if (!is_spl) start_spl();
			if (!is_com || !is_spl)
			{
				choice = MessageBox(windowHandle(window),
					"Please make sure the RF access point is plugged in and not in use by another program, and try again.\n\nWould you like to retry calibration?",
					"Watch Calibration Error", MB_RETRYCANCEL | MB_SETFOREGROUND);
				retry = (choice == IDRETRY);
			}
		} while (retry && !is_com);

		if (!is_com) return;

		do
		{
			retry = false;
			oldcal = calibration;
			calibration = vector3(0.0f,0.0f,0.0f);
			choice = MessageBox(windowHandle(window),"Please turn your watch on, set it down on it's face, and press OK.",
				"Watch Calibration", MB_YESNOCANCEL | MB_SETFOREGROUND);
			if (choice != IDYES) break;

			vector3 getcal = get_current_acc();
			if (abs(getcal.x) < 128.0f)
			{
				getcal.z += 50.0f;
				char buffer[256];
				sprintf_s(buffer, "The calibration values recieved were:\n"
					"<calibration> = <%f, %f, %f>\n"
					"\nWould you like to use this calibration?",
					getcal.x,getcal.y,getcal.z);

				choice = MessageBox(windowHandle(window),buffer, "Watch Calibration Successful", MB_YESNOCANCEL | MB_SETFOREGROUND);
				if (choice == IDYES)
					calibration = getcal;
				else
					calibration = oldcal;
			}
			else
			{
				calibration = oldcal;
				choice = MessageBox(windowHandle(window),
					"Please make sure the watch is on ACC mode and has its wireless on, and try again.\n\nWould you like to retry calibration?",
					"Watch Calibration Error", MB_RETRYCANCEL | MB_SETFOREGROUND);
				retry = (choice == IDRETRY);
			}
		} while (retry);

		if (!was_spl) stop_spl();
	}


	void calibrate_angle()
	{
		
		bool retry = true;
		int choice;
		float old_x, old_y;
		bool was_spl = is_spl;

		do
		{
			if (!is_com) start_com();
			if (!is_spl) start_spl();
			if (!is_com || !is_spl)
			{
				choice = MessageBox(windowHandle(window),
					"Please make sure the RF access point is plugged in and not in use by another program, and try again.\n\nWould you like to retry calibration?",
					"Angle Calibration Error", MB_RETRYCANCEL | MB_SETFOREGROUND);
				retry = (choice == IDRETRY);
			}
		} while (retry && !is_com);

		if (!is_com) return;

		do
		{
			retry = false;
			old_x = cal_angle_x;
			old_y = cal_angle_y;
			//calibration = vector3(0.0f,0.0f,0.0f);
			choice = MessageBox(windowHandle(window),"Please hold your watch in a desired neutral position, then press OK.\n"
				"Make sure you have already calibrated the watch itself.",
				"Angle Calibration", MB_YESNOCANCEL | MB_SETFOREGROUND);
			if (choice != IDYES) break;

			vector3 getcal = get_current_acc();
			if (abs(getcal.x) < 128.0f)
			{
				cal_angle_y = getcal.angle_y();
				cal_angle_x = getcal.angle_xz();
				char buffer[256];
				sprintf_s(buffer, "The calibration angles recieved were:\n"
					"<x, y> = <%f, %f>\n"
					"\nWould you like to use this angle calibration?",
					cal_angle_x,cal_angle_y);

				choice = MessageBox(windowHandle(window),buffer, "Angle Calibration Successful", MB_YESNOCANCEL | MB_SETFOREGROUND);
				if (choice != IDYES)
				{
					cal_angle_x = old_x;
					cal_angle_y = old_y;
				}
			}
			else
			{
				cal_angle_x = old_x;
				cal_angle_y = old_y;
				choice = MessageBox(windowHandle(window),
					"Please make sure the watch is on ACC mode and has its wireless on, and try again.\n\nWould you like to retry calibration?",
					"Angle Calibration Error", MB_RETRYCANCEL | MB_SETFOREGROUND);
				retry = (choice == IDRETRY);
			}
		} while (retry);

		if (!was_spl) stop_spl();
	}


	vector3 get_current_acc()
	{
		DWORD data = SPL_D_NODATA;
		vector3 cal(0.0f,0.0f,0.0f);
		time_t quit_time = (time_t)4;
		time_t starttime = time(NULL);

		for (int i = 0; i < 10; i++)
		{
			bool ok = false;
			do
			{
				ok = BM_SPL_GetData(data);
			} while ((!ok || SPL_D(data) == SPL_D_NODATA) && (time(0) - starttime) < quit_time);
			if ((time(0) - starttime) >= quit_time)
				break;
			
			cal.average(tovector3(data),0.1f);
		}

		if ((time(0) - starttime) < quit_time)
			return cal;
		else
			return vector3(-300.0f, -300.0f, -300.0f);
	}
}