#include "..//headers/logger.h"

std::map<Logger_level, Logger*> Logger::logger_map;

Logger::Logger(OWrapper& ostr){
	this->ostr_list.push_back(ostr);
	ostr.link();
}

Logger::Logger(const std::vector<std::reference_wrapper<OWrapper>>& stream){
	for(auto i = stream.begin(); i != stream.end(); ++i){
		OWrapper& ow = (*i);
		ow.link();
		ostr_list.push_back(*i);
	}
}
Logger::~Logger(){
	for(auto i = ostr_list.begin(); i != ostr_list.end(); ++i){
		OWrapper& ow = (*i);
		ow.unlink();
	}
}

/*void Logger::display(const Player& player, const std::string& prefix){
	for(auto i=0; i<ostr_list.size(); i++)
	{
		std::stringstream strs;
		strs << prefix << ": " << player;
		ostr_list[i].get().print(strs.str());
	}
}

void Logger::display(const Enemy& enemy, const std::string& prefix){
	for(auto i=0; i<ostr_list.size(); i++)
	{
		std::stringstream strs;
		strs << prefix << ": " << enemy;
		ostr_list[i].get().print(strs.str());
	}
}*/

void Logger::display(const std::string& str){
	if(this == nullptr) return;
	for(auto i=0; i<ostr_list.size(); i++)
	{
		ostr_list[i].get().print(str);
	}
}

void Logger::init(Logger_level level, const std::vector<std::reference_wrapper<OWrapper>>& stream){
	logger_map[level] = new Logger(stream);
}

Logger& Logger::logger_out(Logger_level level){
    return *logger_map[level];
}