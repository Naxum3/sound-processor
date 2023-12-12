#include "argparser.h"

int arg_parser(std::string& str)
{
	std::string arg;
	std::stringstream buff;
	buff << str;
	buff >> arg;
	std::string buff2;
	buff2 = str;
	str.clear();
	std::getline(buff, str);
	if (str == buff2) //Nothing changed
		throw std::exception("Not valid argument");
	if (arg[0] == '$')
		arg.erase(arg.begin());
	return std::stoi(arg);
}