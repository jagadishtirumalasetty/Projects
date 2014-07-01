#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <stdlib.h>
#include <math.h>
#include "eZ430_Chronos_CC.h"

class vector3
{
public:
	float x;
	float y;
	float z;

public:
	explicit vector3()
		: x(0.0f), y(0.0f), z(0.0f) { }

	explicit vector3(float x_, float y_, float z_)
		: x(x_), y(y_), z(z_) { }

	vector3 operator+(const vector3 & rhs) const;
	vector3 operator-(const vector3 & rhs) const;
	vector3 operator*(float c) const;

	float normsqr() const { return      x*x + y*y + z*z;  }
	float norm() const    { return sqrt(x*x + y*y + z*z); }
	
	vector3 proj(vector3 onto_b) const;

	static float pi() { return 3.1415926535898f; }
	static float anglediff(float a, float b);
	float angle_yz();
	float angle_xz();
	float angle_xy();
	float angle_x();
	float angle_y();
	float angle_z();
	float angle_xz_after_y();
	float xz_norm() { return sqrt(x*x + z*z); }
	float xy_norm() { return sqrt(x*x + y*y); }
	float yz_norm() { return sqrt(y*y + z*z); }

	vector3 & average(vector3 other, float weight);

//	vector3 & low_filter (vector3 newdata, float lalpha);
//	vector3 & high_filter(vector3 low_1, vector3 newdata, float halpha);
};

/*class vector3_band : public vector3
{
public:
	vector3 & band_filter(vector3 newdata, float lalpha, float haplha);

private:
	vector3 my_low_result;
};*/

class vector3_low : public vector3
{
public:
	vector3_low()
		: vector3(), c(0) { }
	const vector3_low & operator=(const vector3 & rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
	vector3_low & low_filter (vector3 newdata, float lalpha);
private:
	vector3 out[5];
	vector3 in[5];
	int c;
};

class vector3_band : public vector3
{
public:
	vector3 & band_filter(vector3 newdata, float lalpha, float haplha);

private:
	vector3 my_low_result;
};

inline vector3 vector3::proj(vector3 onto_b) const
{
	float b_norm = onto_b.norm();
	return vector3(x*onto_b.x/b_norm, y*onto_b.y/b_norm, z*onto_b.z/b_norm);
}

inline vector3_low & vector3_low::low_filter(vector3 newdata, float lalpha)
{
	x = x + lalpha * (newdata.x - x);
	y = y + lalpha * (newdata.y - y);
	z = z + lalpha * (newdata.z - z);
	return *this;
	float b0 = 0.00290f;//0.000417f;//0.00168f;//0.000182f;//0.0056f;//0.0463f;
	float b1 = 0.00869f;//0.00167f;//0.00671f;//0.000728f;//0.0225f;//0.1851f;
	float b2 = 0.00869f;//0.00250f;//0.0101 f;//0.001092f;//0.0337f;//0.2776f;
	float b3 = 0.00290f;//0.00167f;//0.00671f;//0.000728f;//0.0225f;//0.1851f;
	float b4 = 0.0f;//0.000417f;//0.00168f;//0.000182f;//0.0056f;//0.0463f;

	float a1 = 2.374f;//3.181f;//3.048f;//3.533f;//2.5614f;//0.9624f;
	float a2 = -1.929f;//-3.861f;//-3.766f;//-4.782f;//-2.9222f;//-1.1423f;
	float a3 = 0.532f;//2.112f;//2.199f;//2.933f;//1.6586f;//0.5894f;
	float a4 = 0.0f;//-0.438f;//-0.509f;//-0.687f;//-0.3931f;//-0.1926f;

	/*in[c][0].x=newdata.x*b0;
	in[c][0].y=newdata.y*b0;
	in[c][0].z=newdata.z*b0;

	in[c][1].x=newdata.x*b1;
	in[c][1].y=newdata.y*b1;
	in[c][1].z=newdata.z*b1;

	in[c][2].x=newdata.x*b2;
	in[c][2].y=newdata.y*b2;
	in[c][2].z=newdata.z*b2;*/

	in[c] = newdata;

	*this = out[c] = out[(c+4)%5]*a1+out[(c+3)%5]*a2+out[(c+2)%5]*a3+out[(c+1)%5]*a4+in[c]*b0+in[(c+4)%5]*b1+in[(c+3)%5]*b2+in[(c+2)%5]*b3+in[(c+1)%5]*b4;

/*	out[c][1].x=out[c][0].x*a1;
	out[c][1].y=out[c][0].y*a1;
	out[c][1].z=out[c][0].z*a1;

	out[c][2].x=out[c][0].x*a2;
	out[c][2].y=out[c][0].y*a2;
	out[c][2].z=out[c][0].z*a2;

	out[c][3].x=out[c][0].x*a3;
	out[c][3].y=out[c][0].y*a3;
	out[c][3].z=out[c][0].z*a3;

	out[c][4].x=out[c][0].x*a4;
	out[c][4].y=out[c][0].y*a4;
	out[c][4].z=out[c][0].z*a4;

	x=out[c][0].x;
	y=out[c][0].y;
	z=out[c][0].z;*/

	c=(c+1)%5;

	return *this;
}

/*inline vector3 & vector3::high_filter(vector3 low_1, vector3 newdata, float halpha)
{
	x = halpha * (x + newdata.x - low_1.x);
	y = halpha * (y + newdata.y - low_1.y);
	z = halpha * (z + newdata.z - low_1.z);
	return *this;
}*/

inline vector3 & vector3_band::band_filter(vector3 newdata, float lalpha, float halpha)
{
	vector3 low;
	low.x = my_low_result.x + lalpha * (newdata.x - x);
	low.y = my_low_result.y + lalpha * (newdata.y - y);
	low.z = my_low_result.z + lalpha * (newdata.z - z);

	x = halpha * (x + low.x - my_low_result.x);
	y = halpha * (y + low.y - my_low_result.y);
	z = halpha * (z + low.z - my_low_result.z);
	
	my_low_result = low;
	return *this;
}

inline vector3 vector3::operator+(const vector3 & rhs) const
{
	return vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline vector3 vector3::operator-(const vector3 & rhs) const
{
	return vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline vector3 vector3::operator*(float c) const
{
	return vector3(x*c, y*c, z*c);
}


inline float vector3::angle_yz()
{
	return atan2(z,y);
}

inline float vector3::angle_xz()
{
	return atan2(z,x);
}

inline float vector3::angle_xy()
{
	return atan2(x,y);
}

inline float vector3::angle_x()
{
	return atan2(yz_norm(),x);
}

inline float vector3::angle_y()
{
	return atan2(xz_norm(),y);
}

inline float vector3::angle_z()
{
	return atan2(xy_norm(),z);
}

inline float vector3::anglediff(float a, float b)
{
	float diff = a - b;
	if      (diff >  pi())
		return a - b - 2*pi();
	else if (diff< -pi())
		return a - b + 2*pi();
	else
		return diff;
}

inline vector3 & vector3::average(vector3 other, float weight)
{
	x += weight * other.x;
	y += weight * other.y;
	z += weight * other.z;
	return *this;
}

#endif