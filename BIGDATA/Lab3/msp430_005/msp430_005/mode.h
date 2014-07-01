namespace msp
{
	enum MODEBOX {
		X_BOX = 0,
		Y_BOX,
		X_HIDDEN,
		Y_HIDDEN,
		MODEBOX_COUNT
	};

	enum axis_mode {
		MODE_MOUSE = 0,
		MODE_MOUSEJOY,
		MODE_PPJOY,
		MODE_NONE
	};

	extern const char * const mode_db[];
	extern const int mode_count;
}