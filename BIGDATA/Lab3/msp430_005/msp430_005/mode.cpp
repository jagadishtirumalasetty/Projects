#include "msp.h"

namespace msp
{
	const char * const mode_db[] = {
		"Mouse",
		"Mouse-Joy",
		"PP Joystick",
		"None"
	};
	const int mode_count = (sizeof mode_db) / (sizeof mode_db[0]);

	namespace settings {
		axis_mode currmode[MODEBOX_COUNT] = {MODE_MOUSE, MODE_MOUSE, MODE_PPJOY, MODE_NONE};
		std::string mode_string[MODEBOX_COUNT] = {"", "", "", ""};
	}
}