// main.cpp : Defines the entry point for the application.
//

#include "msp.h"
#include "vector3.h"

#define INT_UNINIT 0

int WINAPI _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	msp::main();
	return 0;
}

namespace msp
{
	namespace consts
	{
		char * name = "Chronos Flying Mouse";
		int32 style   = WINDOW_TITLEBAR | WINDOW_CLOSEBUTTON | WINDOW_MINBUTTON;
		int32 exstyle = WINDOW_TOOLWINDOW | WS_EX_APPWINDOW;
		int32 width        = 240;
		int32 height       = 240;
		int32 framewidth   = INT_UNINIT;
		RECT desktopsize = {0,0,consts::width,consts::height};
		uint32 backfill  = 0x3333AA;
		uint32 backtext  = 0xFFFFFF;
		uint32 frontfill = 0x8888FF;
		uint32 fronttext = 0x000000;
		char * settingsfile = "settings.ini";
	}

//	bool is_enabled = false;

//	handle desktop         = NULL;
	handle window          = NULL;
	handle windowpanel     = NULL;
	handle windowtabs      = NULL;
	handle mainpanel       = NULL;
	//	handle enablebutton    = NULL;
		handle startbutton     = NULL;
		handle startfont       = NULL;
		handle status_label    = NULL;
	handle modepanel       = NULL;
		handle x_mode_label    = NULL;
		handle y_mode_label    = NULL;
		handle visible_label   = NULL;
		handle hidden_label    = NULL;
		handle wheel_label     = NULL;
		handle modebox[MODEBOX_COUNT] = {NULL, NULL, NULL, NULL};
		handle x_wheel_check   = NULL;
		handle y_wheel_check   = NULL;
	handle settingspanel   = NULL;
		handle cal_watch_btn   = NULL;
		handle cal_angle_btn   = NULL;
		handle x_set_label     = NULL;
		handle y_set_label     = NULL;
		handle x_dset_label    = NULL;
		handle y_dset_label    = NULL;
		handle sense_label     = NULL;
		handle invert_label    = NULL;
		handle deadzone_label  = NULL;
		handle x_invert_check  = NULL;
		handle y_invert_check  = NULL;
		handle x_slider        = NULL;
		handle y_slider        = NULL;
		handle x_dslider       = NULL;
		handle y_dslider       = NULL;

#if TRACK_INTERNALS
	FILE* datalog;
	handle stable_window = NULL;
#endif

	int main()
	{
		start_ui();
		calibration = vector3(-300,-300,-300);

#if TRACK_INTERNALS
		fopen_s(&datalog,"log.txt","w");
		fprintf(datalog,"angle_x()\tangle_y()\tangle_z()\tangle_yz()\tangle_xz()\tangle_xy()\n");
#endif

		bool options_loaded = (load_options() == 0);
		if (options_loaded)
		{

//			messagef("<calibration> = ","<%f, %f, %f>",calibration.x,calibration.y,calibration.z);

			//calibration = vector3(4,0,-28);
			if (abs(calibration.x) > 128.0f || abs(calibration.y) > 128.0f || abs(calibration.z) > 128.0f)
				calibrate_watch();

			start_ppjoy();
			start_com();

			setGadgetVisible(window,true);
			SetForegroundWindow(windowHandle(window));

			int loopcount = 0;
			while (true)
			{
				if (check_ui_events() != 0) break;

				if (is_mouse_on)
					process_mouse_control();

				loopcount = (loopcount + 1) & 0xFF;
			}

			if (is_ppjoy) close_ppjoy();
			if (is_com)   close_com();

			save_options();
		}

		destroy_ui();
#if TRACK_INTERNALS
		fclose(datalog);
#endif
		return 0;
	}


	int start_ui()
	{
		startBlue();

//		desktop = createGadgetFromWindow(desktopWindow());


		// Fonts
		startfont = createFont("Verdana",14,0,0,0);


		setGadgetDefaults(false); // hide main window
		window = createWindow(0,0,consts::width,consts::height,consts::name,consts::style,consts::exstyle,1,0);
		setWindowIcon(window,"cfm.ico");
//		setWindowLargeIconOnce(window,"cfm.ico");

		consts::framewidth = consts::width - gadgetClientWidth(window);		
		SystemParametersInfo(SPI_GETWORKAREA,0,&consts::desktopsize,0);
		int x = consts::desktopsize.right - consts::width - consts::framewidth;
		int y = consts::desktopsize.bottom - consts::height - consts::framewidth;
		moveGadget(window,x,y);
		
		setGadgetDefaults(true);
		windowpanel = createPanel(0, 0, consts::width,consts::height,window);
		setPanelBorderStyle(windowpanel, BORDER_NONE);
		setPanelImage(windowpanel,"background.bmp");
		windowtabs = createTabs(0, 0, consts::width,consts::height,0,windowpanel);
		setGadgetAlign(windowtabs,ALIGN_ALL);
		
		// Main Panel
		addTab(windowtabs, "Main");
		// 247x232
		mainpanel = createPanel(2, 22, gadgetClientWidth(windowpanel) - 6, gadgetClientHeight(windowpanel) - 25, windowtabs);
		attachGadget(windowtabs, 0, mainpanel);
		setGadgetColor(mainpanel,0x002040,0xFFFFFF);
		setPanelImage(mainpanel,"title.bmp");
		int mainpanel_width = gadgetClientWidth(mainpanel);
		startbutton = createButton(60,110,mainpanel_width-120,32,"Start",false,mainpanel);
		applyFont(startbutton, startfont);
		status_label = createTransparentLabel(0,160,mainpanel_width,16,"UI Loaded",mainpanel);
		//handle temp = createFont("Courier New",10,0,0,0);
		//applyFont(status_label,temp);
		setGadgetTextAlign(status_label,TEXT_ALIGN_CENTER);
		setGadgetColor(status_label, 0x00000000, 0x00FFFFFF);

		// Mode Panel
		addTab(windowtabs, "Mode");
		modepanel = createPanel(2, 22, gadgetClientWidth(windowpanel) - 6, gadgetClientHeight(windowpanel) - 25, windowtabs);
		attachGadget(windowtabs, 1, modepanel);
		setGadgetColor(modepanel,0x002040,0xFFFFFF);
		setPanelImage(modepanel,"background.bmp");
		visible_label   = createTransparentLabel(25, 20, 80, 16,"Visible:",modepanel);
		hidden_label    = createTransparentLabel(110,20, 80, 16,"Hidden:",modepanel);
		wheel_label     = createTransparentLabel(180,20, 56, 16,"Wheel",modepanel);
		x_mode_label    = createTransparentLabel(10, 45, 10, 16,"X:",modepanel);
		y_mode_label    = createTransparentLabel(10, 75, 10, 16,"Y:",modepanel);
		setGadgetTextAlign(visible_label,  TEXT_ALIGN_CENTER);
		setGadgetTextAlign(hidden_label,   TEXT_ALIGN_CENTER);
		setGadgetTextAlign(wheel_label,    TEXT_ALIGN_CENTER);
		setGadgetTextAlign(x_mode_label,   TEXT_ALIGN_RIGHT);
		setGadgetTextAlign(y_mode_label,   TEXT_ALIGN_RIGHT);
		setGadgetColor(visible_label,   0x00000000, 0x00FFFFFF);
		setGadgetColor(hidden_label,    0x00000000, 0x00FFFFFF);
		setGadgetColor(wheel_label,     0x00000000, 0x00FFFFFF);
		setGadgetColor(x_mode_label,    0x00000000, 0x00FFFFFF);
		setGadgetColor(y_mode_label,    0x00000000, 0x00FFFFFF);
		for (int axis = 0; axis < MODEBOX_COUNT; axis++)
		{
			modebox[axis] = createCombobox(25+85*((axis&0x2)>>1), 40+30*(axis&0x1), 80, 120, modepanel);
			for (int i = 0; i < mode_count; i++)
				addItem(modebox[axis],mode_db[i]);
		}
		x_wheel_check = createCheckbox(200,43,16,16,"",modepanel);
		y_wheel_check = createCheckbox(200,73,16,16,"",modepanel);

		// Settings Panel
		addTab(windowtabs, "Settings");
		settingspanel = createPanel(2, 22, gadgetClientWidth(windowpanel) - 6, gadgetClientHeight(windowpanel) - 25, windowtabs);
		attachGadget(windowtabs, 2, settingspanel);
		setGadgetColor(settingspanel,0x002040,0xFFFFFF);
		setPanelImage(settingspanel,"background.bmp");
		// Calibration Buttons
		cal_watch_btn = createButton(20, 7,90,22,"Calibrate Watch",false,settingspanel);
		cal_angle_btn = createButton(120,7,90,22,"Calibrate Angle",false,settingspanel);
		// Labels
		x_set_label    = createTransparentLabel(20, 53, 10, 16,"X:",         settingspanel);
		y_set_label    = createTransparentLabel(20, 83, 10, 16,"Y:",         settingspanel);
		sense_label    = createTransparentLabel(30, 35, 140,16,"Sensitivity",settingspanel);
		invert_label   = createTransparentLabel(160,35, 56, 16,"Invert",     settingspanel);
		x_dset_label   = createTransparentLabel(20, 133,10, 16,"X:",         settingspanel);
		y_dset_label   = createTransparentLabel(20, 163,10, 16,"Y:",         settingspanel);
		deadzone_label = createTransparentLabel(30, 115,140,16,"Deadzone",   settingspanel);
		setGadgetTextAlign(x_set_label,   TEXT_ALIGN_RIGHT);
		setGadgetTextAlign(y_set_label,   TEXT_ALIGN_RIGHT);
		setGadgetTextAlign(x_dset_label,  TEXT_ALIGN_RIGHT);
		setGadgetTextAlign(y_dset_label,  TEXT_ALIGN_RIGHT);
		setGadgetTextAlign(sense_label,   TEXT_ALIGN_CENTER);
		setGadgetTextAlign(invert_label,  TEXT_ALIGN_CENTER);
		setGadgetTextAlign(deadzone_label,TEXT_ALIGN_CENTER);
		setGadgetColor(x_set_label,    0x00000000, 0x00FFFFFF);
		setGadgetColor(y_set_label,    0x00000000, 0x00FFFFFF);
		setGadgetColor(x_dset_label,   0x00000000, 0x00FFFFFF);
		setGadgetColor(y_dset_label,   0x00000000, 0x00FFFFFF);
		setGadgetColor(sense_label,    0x00000000, 0x00FFFFFF);
		setGadgetColor(invert_label,   0x00000000, 0x00FFFFFF);
		setGadgetColor(deadzone_label, 0x00000000, 0x00FFFFFF);
		// inversion Checkboxes
		x_invert_check = createCheckbox(180,53,16,16,"",settingspanel);
		y_invert_check = createCheckbox(180,83,16,16,"",settingspanel);
		// Sensitivity & Deadzone trackbars
		x_slider  = createTrackbar(30,50, 140,32,0,settingspanel);
		y_slider  = createTrackbar(30,80, 140,32,0,settingspanel);
		x_dslider = createTrackbar(30,130,140,32,0,settingspanel);
		y_dslider = createTrackbar(30,160,140,32,0,settingspanel);
		// Make the trackbars transparent :D
		SetWindowLong(windowHandle(x_slider),  GWL_STYLE, GetWindowLong(windowHandle(x_slider),  GWL_STYLE) | TBS_TRANSPARENTBKGND);
		SetWindowLong(windowHandle(y_slider),  GWL_STYLE, GetWindowLong(windowHandle(y_slider),  GWL_STYLE) | TBS_TRANSPARENTBKGND);
		SetWindowLong(windowHandle(x_dslider), GWL_STYLE, GetWindowLong(windowHandle(x_dslider), GWL_STYLE) | TBS_TRANSPARENTBKGND);
		SetWindowLong(windowHandle(y_dslider), GWL_STYLE, GetWindowLong(windowHandle(y_dslider), GWL_STYLE) | TBS_TRANSPARENTBKGND);
		SetClassLong(windowHandle(x_slider),  GCL_HBRBACKGROUND, (LONG)GetStockObject(HOLLOW_BRUSH));
		SetClassLong(windowHandle(y_slider),  GCL_HBRBACKGROUND, (LONG)GetStockObject(HOLLOW_BRUSH));
		SetClassLong(windowHandle(x_dslider), GCL_HBRBACKGROUND, (LONG)GetStockObject(HOLLOW_BRUSH));
		SetClassLong(windowHandle(y_dslider), GCL_HBRBACKGROUND, (LONG)GetStockObject(HOLLOW_BRUSH));
		// Set up values
		setTrackbarRange(x_slider,  0, 10);
		setTrackbarRange(y_slider,  0, 10);
		setTrackbarRange(x_dslider, 0, 10);
		setTrackbarRange(y_dslider, 0, 10);
		setTrackbarTickFrequency(x_slider,  1);
		setTrackbarTickFrequency(x_slider,  1);
		setTrackbarTickFrequency(x_dslider, 1);
		setTrackbarTickFrequency(x_dslider, 1);

//		message("width",gadgetWidth(mainpanel));
//		message("height",gadgetHeight(mainpanel));

		
#if TRACK_INTERNALS
		stable_window = createWindow(50,50,10,10,"",WINDOW_NOBORDER,0,1,0);
		handle stable_panel = createPanel(0,0,10,10,stable_window);
		setGadgetColor(stable_panel,0xFF0000,0xFF0000);
#endif



//		setGadgetEnabled(startbutton,0);

		return 0;
	}

	void sync_settings_to_ui()
	{
		for (int axis = 0; axis < MODEBOX_COUNT; axis++) {
			for (int i = 0; i < mode_count; i++) {
				if (strcmp(settings::mode_string[axis].c_str(),mode_db[i]) == 0)
				{
					currmode[axis] = (axis_mode)i;
					selectItem(modebox[axis], (int)currmode[axis]);
					break;
				}
			}
		}

		setTrackbarPosition(x_slider,  settings::x_sense);
		setTrackbarPosition(y_slider,  settings::y_sense);
		setTrackbarPosition(x_dslider, settings::x_deadzone);
		setTrackbarPosition(y_dslider, settings::y_deadzone);
		
		setChecked(x_wheel_check,  settings::x_wheel);
		setChecked(y_wheel_check,  settings::y_wheel);
		setChecked(x_invert_check, settings::x_invert);
		setChecked(y_invert_check, settings::y_invert);
	}

	void sync_ui_to_settings()
	{
		for (int axis = 0; axis < MODEBOX_COUNT; axis++)
			settings::mode_string[axis] = std::string(mode_db[currmode[axis]]);
	}

	void destroy_ui()
	{
		deleteGadget(x_set_label);
		deleteGadget(y_set_label);
		deleteGadget(x_dset_label);
		deleteGadget(y_dset_label);
		deleteGadget(sense_label);
		deleteGadget(invert_label);
		deleteGadget(deadzone_label);
		deleteGadget(x_slider);
		deleteGadget(y_slider);
		deleteGadget(x_dslider);
		deleteGadget(y_dslider);
		deleteGadget(x_invert_check);
		deleteGadget(y_invert_check);
		detachGadget(windowtabs, 2, settingspanel);
		deleteGadget(settingspanel);

		for (int axis = 0; axis < MODEBOX_COUNT; axis++)
			deleteGadget(modebox[axis]);
		deleteGadget(x_wheel_check);
		deleteGadget(y_wheel_check);
		detachGadget(windowtabs, 1, modepanel);
		deleteGadget(modepanel);

		deleteGadget(startbutton);
		detachGadget(windowtabs, 0, mainpanel);
		deleteGadget(mainpanel);

		deleteGadget(windowtabs);
		deleteGadget(windowpanel);
		deleteGadget(window);

		deleteFont(startfont);
	}


	int check_ui_events()
	{
		do
		{
			getEvent();
			handle eventSource_ = eventSource();
			DWORD eventType_ = eventType();

			if (eventSource_ == startbutton && eventType_ == MOUSE_CLICK)
				toggle_mouse_control();

			for (int axis = 0; axis < MODEBOX_COUNT; axis++)
			{
				if (eventSource_ == modebox[axis] && eventType_ == COMBOBOX_CHANGE)
				{
					currmode[axis] = static_cast<axis_mode>(selectedItem(modebox[axis]));
					break;
				}
			}

			if (eventSource_ == x_wheel_check && eventType_ == GUI_COMMAND)
				settings::x_wheel = (getChecked(x_wheel_check) != 0);
			if (eventSource_ == y_wheel_check && eventType_ == GUI_COMMAND)
				settings::y_wheel = (getChecked(y_wheel_check) != 0);

			if (eventSource_ == cal_watch_btn && eventType_ == MOUSE_CLICK)
				calibrate_watch();
			if (eventSource_ == cal_angle_btn && eventType_ == MOUSE_CLICK)
				calibrate_angle();

			if (eventSource_ == x_slider && eventType_ == TRACKBAR_CHANGE)
				settings::x_sense = getTrackbarPosition(x_slider);
			if (eventSource_ == y_slider && eventType_ == TRACKBAR_CHANGE)
				settings::y_sense = getTrackbarPosition(y_slider);

			if (eventSource_ == x_invert_check && eventType_ == GUI_COMMAND)
				settings::x_invert = (getChecked(x_invert_check) != 0);
			if (eventSource_ == y_invert_check && eventType_ == GUI_COMMAND)
				settings::y_invert = (getChecked(y_invert_check) != 0);

			if (eventSource_ == x_dslider && eventType_ == TRACKBAR_CHANGE)
				settings::x_deadzone = getTrackbarPosition(x_dslider);
			if (eventSource_ == y_dslider && eventType_ == TRACKBAR_CHANGE)
				settings::y_deadzone = getTrackbarPosition(y_dslider);

			if (eventSource_ == window && eventType_ == WINDOW_CLOSE)
				return WINDOW_CLOSE;

			processEvents();
			Sleep(1);
		}
		while (eventType() != 0);

		return 0;
	}

	void set_status(const char * status)
	{
		setGadgetText(status_label,status);
	}

}; // namespace mspmouse