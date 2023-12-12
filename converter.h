#pragma once
#include "parser.h"
#include "argparser.h"
#include <algorithm>

class Converter
{
protected:
	sstream* buff;
public:
	Converter(sstream*);
	Converter();
	void set_sstream(sstream* in);
	virtual void work(std::string, std::vector<std::string>) = 0;
	static Converter* createConv(std::string);
	virtual ~Converter() = default;
};

class Mix : public Converter
{
public:
	void work(std::string, std::vector<std::string>);

};

class Mute : public Converter
{
public:
	void work(std::string argv, std::vector<std::string>);
};

class Smth :public Converter
{
public:
	void work(std::string argv, std::vector<std::string>);
};