#include "msp.h"

namespace msp
{
	uint8_t  com_port = 0;
	bool     is_com   = false;
	bool     is_spl   = false;
	bool     is_ppjoy = false;
	HANDLE   ppjoy_port = NULL;

	int start_com()
	{
		if (is_com) return 0;

		is_com = BM_GetCOM(com_port);
		is_com = BM_OpenCOM(com_port, 115200, 30, false, false);
		if (!is_com)
		{
			set_status("Plug in RF point");
			return -1;
		}

		if (is_ppjoy)
			set_status("RF point and PPJoy found");
		else
			set_status("RF point found; no PPJoy found");

		return 0;
	}

	void close_com()
	{
		if (!is_com) return;

		stop_spl();
		BM_CloseCOM();
		is_com = false;
	}

	int start_spl()
	{
		if (is_spl) return 0;
		is_spl = BM_SPL_Start();
		if (!is_spl)
		{
			set_status("RF point SimpliciTI error");
			return -1;
		}
		return 0;
	}

	void stop_spl()
	{
		if (!is_spl) return;
		BM_SPL_Stop();
		is_spl = false;
	}


	int start_ppjoy()
	{
		if (is_ppjoy) return 0;

		ppjoy_port = CreateFile(PPJOY_IOCTL_DEVNAME,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
		if (ppjoy_port == INVALID_HANDLE_VALUE)
		{
			if (is_com)
				set_status("RF point found; no PPJoy found");
			else
				set_status("No RF point or PPJoy found");
			is_ppjoy = false;
			return -1;
		}

		JoyState.Signature  = JOYSTICK_STATE_V1;
		JoyState.NumAnalog  = NUM_ANALOG;	/* Number of analog values */
		JoyState.NumDigital = NUM_DIGITAL;	/* Number of digital values */
		for (int i = 0; i < NUM_ANALOG; i++)
			JoyState.Analog[i] = PPJOY_AXIS_0;
		for (int i = 0; i < NUM_DIGITAL; i++)
			JoyState.Digital[i] = 0;

		is_ppjoy = true;
		if (is_com)
			set_status("RF point and PPJoy found");
		else
			set_status("No RF point found; PPJoy found");

		return 0;
	}

	void close_ppjoy()
	{
		if (!is_ppjoy) return;
		CloseHandle(ppjoy_port);
	}
}