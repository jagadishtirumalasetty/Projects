#ifndef _PPJOY_H_

#include "ppjioctl_devname.h"
#include "ppjioctl.h"
#include "types.h"

#define PPJOY_AXIS_0      ((PPJOY_AXIS_MIN + PPJOY_AXIS_MAX) / 2)
#define PPJOY_SIGNED_MAX  PPJOY_AXIS_0

#define	NUM_ANALOG	2		/* Number of analog values which we will provide */
#define	NUM_DIGITAL	1		/* Number of digital values which we will provide */

#define ERROR_PPJOY_DELETED 2 /* error code of DeviceIoControl() when ppjoy device is deleted */

#pragma pack(push,1)		/* All fields in structure must be byte aligned. */
typedef struct
{
 uint32_t		Signature;				/* Signature to identify packet to PPJoy IOCTL */
 int8_t			NumAnalog;				/* Num of analog values we pass */
 int32_t		Analog[NUM_ANALOG];		/* Analog values */
 int8_t			NumDigital;				/* Num of digital values we pass */
 int8_t			Digital[NUM_DIGITAL];	/* Digital values */
}	JOYSTICK_STATE;
#pragma pack(pop)

#endif