#ifndef LOGGER_H
#define LOGGER_H

#include "enemy.h"
#include "cell_objects.h"
#include "ostream_wrapper.h"
#include <sstream>
#include <map>
//#include <vector>
#include <functional>
//#include <ostream>

enum Logger_level{
	Default = 0,
	File,
	Console
};

class Logger{
    private:
        std::vector<std::reference_wrapper<OWrapper>> ostr_list;
		static std::map<Logger_level, Logger*> logger_map;

    public:
        Logger(OWrapper& ostr);
		Logger(const std::vector<std::reference_wrapper<OWrapper>>& stream);
		~Logger();

		//void display( const Player& player, const std::string& prefix);
		//void display(const Enemy& enemy, const std::string& prefix);
		void display(const std::string& str);

		static void init(Logger_level level, const std::vector<std::reference_wrapper<OWrapper>>& stream);
		static Logger& logger_out(Logger_level level = Default);
};

#endif