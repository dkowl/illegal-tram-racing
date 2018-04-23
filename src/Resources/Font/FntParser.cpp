#include "FntParser.h"
#include <sstream>

const char FntParser::Value::EQUAL = '=';
const char FntParser::Value::QUOTE = '"';

FntParser::Value::Value(const std::string &expression)
{
	int i = 0;
	name = ReadUntil(i, expression, EQUAL);
	i++;
	if(expression[i] == QUOTE)
	{
		stringValue = ReadUntil(i, expression, QUOTE);
	}
	else
	{
		std::stringstream sstream(expression.substr(i));
		sstream >> intValue;
		isInt = true;
	}
}

std::string FntParser::Value::ReadUntil(int& i, const std::string& s, const char& c)
{
	std::string result;
	while(s[i] != c && i < s.size())
	{
		result += s[i];
		i++;
	}
	return result;
}

FntParser::Line::Line(std::string line)
{
}
