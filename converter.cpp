#include "converter.h"

void Mix::work(std::string convert_info, std::vector<std::string> files) {
	int filenumber = arg_parser(convert_info)-2;
	int sec = arg_parser(convert_info);
	sec *= buff->header.sampleRate;
	sstream second;
	second.read(files[filenumber]);
	int end = std::min(sec, (int)buff->signals.size());
	for (int i = 0; i < end; i++)
		if (i >= second.signals.size())
			break;
		else
			buff->signals[i] = (buff->signals[i] + second.signals[i]) / 2;

}

void Mute::work(std::string convert_info, std::vector<std::string> files) {
	int st, en;
	st = arg_parser(convert_info);
	en = arg_parser(convert_info);
	en = std::min((int)buff->signals.size(), (int)(en * buff->header.sampleRate));
	st *= buff->header.sampleRate;
	for (int i = st; i < en; i++)
		buff->signals[i] = 0;
}

void Smth::work(std::string convert_info, std::vector<std::string> files) {
	int st, en;
	st = arg_parser(convert_info);
	en = arg_parser(convert_info);
	en = std::min((int)buff->signals.size(), (int)(en * buff->header.sampleRate));
	st *= buff->header.sampleRate;
	for (int i = st; i < en; i++)
		buff->signals[i] += 10000;
}

void Converter::set_sstream(sstream* in)
{
	if (in == NULL)
		throw std::exception("No stream");
	buff = in;
}

Converter::Converter(sstream* in)
{
	if (in == NULL)
		throw std::exception("No stream");
	buff = in;
}

Converter::Converter()
{
	buff = NULL;
}
Converter* Converter::createConv(std::string str)
{
	if (str == "mix")
		return new Mix();
	if (str == "mute")
		return new Mute();
	if (str == "smth")
		return new Smth();
	throw std::exception("Converter not found");
}
