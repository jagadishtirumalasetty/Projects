#ifndef _FILTER_H_
#define _FILTER_H_

namespace msp
{
	class filter
	{
	public:
		virtual vector3 operator()(vector3 newdata) = 0;
		virtual ~filter() { }
	};

	class exp_filter : filter
	{
	public:
		float alpha;

	public:
		exp_filter(float alpha_)
			: alpha(alpha_) { }
		vector3 operator()(vector3 newdata);

	private:
		vector3 out;
	};

	class dsp_filter : filter
	{
	public:
		float a1;
		float a2;
		float a3;
		float a4;

		float b0;
		float b1;
		float b2;
		float b3;
		float b4;

	public:
		dsp_filter()
			: a1(0.0f), a2(0.0f), a3(0.0f), a4(0.0f), 
			  b0(0.0f), b1(0.0f), b2(0.0f), b3(0.0f), b4(0.0f), 
			  c(0) { }

		dsp_filter(float a1_, float a2_, float a3_, float a4_, float b0_, float b1_, float b2_, float b3_, float b4_)
			: a1(a1_), a2(a2_), a3(a3_), a4(a4_), 
			  b0(b0_), b1(b1_), b2(b2_), b3(b3_), b4(b4_), 
			  c(0) { }

		vector3 operator()(vector3 newdata);

	private:
		vector3 out[5];
		vector3 in[5];
		int c;
	};
}

#endif