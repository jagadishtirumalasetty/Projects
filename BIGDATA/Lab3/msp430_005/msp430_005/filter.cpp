#include "msp.h"

namespace msp
{
	vector3 exp_filter::operator()(vector3 newdata)
	{
		return out = out + ((newdata - out)*alpha);
	}

	vector3 dsp_filter::operator()(vector3 newdata)
	{
		in[c] = newdata;
		out[c] = out[(c+4)%5]*a1+out[(c+3)%5]*a2+out[(c+2)%5]*a3+out[(c+1)%5]*a4+in[c]*b0+in[(c+4)%5]*b1+in[(c+3)%5]*b2+in[(c+2)%5]*b3+in[(c+1)%5]*b4;
		c=(c+1)%5;
		return out[c];
	}
}