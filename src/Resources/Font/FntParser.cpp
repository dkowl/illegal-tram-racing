#include "FntParser.h"
#include <sstream>
#include <iostream>
#include <cctype>

const char FntParser::Value::EQUAL = '=';
const char FntParser::Value::QUOTE = '"';
const char FntParser::Line::SEPARATOR = ' ';


FntParser::Value::Value(const std::string &expression):
	isInt(false)
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

void FntParser::Value::Display() const
{
	std::cout
		<< name << std::endl
		<< stringValue << std::endl
		<< intValue << std::endl;
}

std::string FntParser::ReadUntil(int& i, const std::string& s, const char& c)
{
	std::string result;
	while(s[i] != c && i < s.size())
	{
		result += s[i];
		i++;
	}
	return result;
}

std::string FntParser::ReadUntilWhitespace(int& i, const std::string& s)
{
	std::string result;
	while (!std::isspace(s[i]) && i < s.size())
	{
		result += s[i];
		i++;
	}
	return result;
}

FntParser::Line::Line(const std::string& line)
{
	int i = 0;
	name = ReadUntilWhitespace(i, line);
	while(i < line.size())
	{
		if (std::isspace(line[i])) i++;
		else AddValue(Value(ReadUntilWhitespace(i, line)));
	}
}

void FntParser::Line::AddValue(Value&& value)
{
	values[value.name] = std::move(value);
}

void FntParser::Line::Display()
{
	std::cout << "name: " << name;
	for(auto&& i : values)
	{
		std::cout << "	" << i.first << ": " << i.second.intValue << std::endl;
	}
}
