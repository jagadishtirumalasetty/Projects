#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "types.h"
#define BOOST_HAS_STDINT_H
#include "boost/program_options.hpp"
#include "msp.h"


namespace po = boost::program_options;
using std::vector;
using std::string;
using std::fstream;
using std::exception;
using std::endl;
using std::ostream;

namespace msp
{
	namespace settings {
		int  x_sense    = 5;
		int  y_sense    = 5;
		bool x_invert   = false;
		bool y_invert   = false;
		int  x_deadzone = 3;
		int  y_deadzone = 3;
		bool x_wheel    = false;
		bool y_wheel    = false;
		float cal_angle_x = vector3::pi();
		float cal_angle_y = vector3::pi()/2.0f;
	}
	bool is_options_init = false;
	
	template<class T, class charT = char>
	class saveable_value : public po::typed_value<T,charT>
	{
	public:
		saveable_value(T* var)
			: typed_value(var) { pointer = var; }
		ostream & print(ostream & os) const { if (pointer != NULL) os << *pointer; return os; }
	private:
		T* pointer;
	};

	class po_setting_any
	{
	public:
		po_setting_any(string _section, string _name, string _desc)
			: section(_section), name(_name), desc(_desc) { }
		virtual ostream & print(ostream & os) const { return (os << name << '=' << "\"\" #" << desc); }
		virtual po::value_semantic * value() { return NULL; }
	public:
		string section;
		string name;
		string desc;
	};
	std::ostream & operator<<(std::ostream & os, const po_setting_any & set)
	{
		return set.print(os);
	}

	template<class T>
	class po_setting : public po_setting_any
	{
	public:
		po_setting(string _section, string _name, T* _valuep, T _default, char * _desc)
			: po_setting_any(_section, _name, _desc) { valuep = new saveable_value<T>(_valuep); valuep->default_value(_default); }
		virtual ostream & print(ostream & os) const { os << name << '='; valuep->print(os); if (desc != "") os <<" #" << desc; return os; }
		virtual po::value_semantic * value() { return valuep; }
	public:
		saveable_value<T> * valuep;
	};

//	float setting_NaN = std::numeric_limits<float>::quiet_NaN();

	po_setting_any * setting_db[] = {
		new po_setting<string>("Mode",        "x_mode",        &mode_string[X_BOX],    std::string(mode_db[MODE_MOUSE]), "Watch X mode while cursor is visible"),
		new po_setting<string>("Mode",        "y_mode",        &mode_string[Y_BOX],    std::string(mode_db[MODE_MOUSE]), ""),
		new po_setting<string>("Mode",        "x_hidden",      &mode_string[X_HIDDEN], std::string(mode_db[MODE_PPJOY]), "Watch X mode while cursor is hidden"),
		new po_setting<string>("Mode",        "y_hidden",      &mode_string[Y_HIDDEN], std::string(mode_db[MODE_PPJOY]), ""),
		new po_setting<bool>  ("Mode",        "x_wheel",       &settings::x_wheel,   false, "true/false"),
		new po_setting<bool>  ("Mode",        "y_wheel",       &settings::y_wheel,   false, ""),
		new po_setting<float> ("Calibration", "watch_x",       &calibration.x,     -300.0f, "Watch raw accelerometer calibration level : -128.0 to +128.0"),
		new po_setting<float> ("Calibration", "watch_y",       &calibration.y,     -300.0f, ""),
		new po_setting<float> ("Calibration", "watch_z",       &calibration.z,     -300.0f, ""),
		new po_setting<float> ("Calibration", "angle_x",       &cal_angle_x, vector3::pi(), "Angle calibration x : -pi to pi"),
		new po_setting<float> ("Calibration", "angle_y",       &cal_angle_y, vector3::pi()/2.0f, ""),
		new po_setting<int>   ("Settings",    "x_sensitivity", &settings::x_sense,       5, "0 to 10"),
		new po_setting<int>   ("Settings",    "y_sensitivity", &settings::y_sense,       5, ""),
		new po_setting<bool>  ("Settings",    "invert_x_axis", &settings::x_invert,  false, "true/false"),
		new po_setting<bool>  ("Settings",    "invert_y_axis", &settings::y_invert,  false, ""),
		new po_setting<int>   ("Settings",    "x_deadzone",    &settings::x_deadzone,    3, "0 to 10"),
		new po_setting<int>   ("Settings",    "y_deadzone",    &settings::y_deadzone,    3, "")
	};
	int setting_db_size = ((sizeof setting_db) / (sizeof setting_db[0]));

	po::options_description file_settings;

	int init_options()
	{
		int i = 0;
		while (i < setting_db_size)
		{
			po::options_description curr_scn_opt(setting_db[i]->section);
			po::options_description_easy_init curr_scn_add = curr_scn_opt.add_options();
			do
			{
				curr_scn_add((setting_db[i]->section + "." + setting_db[i]->name).c_str(), setting_db[i]->value(), setting_db[i]->desc.c_str());
				i++;
			} while (i < setting_db_size && setting_db[i - 1]->section == setting_db[i]->section);
			file_settings.add(curr_scn_opt);
		}

		is_options_init = true;
		return 0;
	}

	int load_options()
	{
		if (!is_options_init)
			if (init_options() != 0) return -1;

		struct stat statbuf;
		if (stat(consts::settingsfile, &statbuf) != 0)
		{
			FILE* zero_file = NULL;
			fopen_s(&zero_file, consts::settingsfile, "w");
			fclose(zero_file);
		}
		
		while (1)
		{
			try
			{
				po::variables_map vm;
				po::store(po::parse_config_file<char>(consts::settingsfile, file_settings), vm);
				notify(vm);
				break;
			}
			catch(exception& e)
			{
				int choice = MessageBox(windowHandle(window),(string(e.what()) + string("\n\nWould you like to overwrite settings.ini?")).c_str(), "Error reading settings.ini",MB_YESNOCANCEL | MB_ICONERROR | MB_SETFOREGROUND);
				if (choice == IDYES)
				{
					FILE* zero_file = NULL;
					fopen_s(&zero_file, consts::settingsfile, "w");
					fclose(zero_file);
				}
				else
					return -1;
			}
		}

		sync_settings_to_ui();
		return 0;
	}

	int save_options()
	{
		if (!is_options_init)
			if (init_options() != 0) return -1;

		sync_ui_to_settings();

		fstream save_file = fstream(consts::settingsfile, fstream::out);

		int i = 0;
		while (i < setting_db_size)
		{
			save_file << '[' << setting_db[i]->section << ']' << endl;
			do
			{
				save_file << *(setting_db[i]) << endl; //->name << '=' << *(setting_db[i]->valuep()) << setting_db[i]->desc);
				i++;
			} while (i < setting_db_size && setting_db[i - 1]->section == setting_db[i]->section);
			save_file << endl;
		}
		return 0;
	}
}