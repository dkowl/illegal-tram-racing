#include "FntParser.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>

const char FntParser::Value::EQUAL = '=';
const char FntParser::QUOTE = '"';
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

FntParser::FntParser(const std::string& filepath)
{
	std::ifstream file(filepath);
	if(!file.good())
	{
		std::cout << "FntParser: wrong file " << filepath << std::endl;
		return;
	}
	std::istream& istream(file);
	std::string stringLine;
	while(std::getline(istream, stringLine))
	{
		Line line(stringLine);
		if(line.name == "char")
		{
			chars.emplace_back(std::move(line));
		}
		else if(line.name == "kerning")
		{
			kernings.emplace_back(std::move(line));
		}
	}
}

void FntParser::Display() const
{
	for(auto&& i : chars)
	{
		i.Display();
	}

	for(auto&& i : kernings)
	{
		i.Display();
	}
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
	bool isInQuote = false;
	while ((!std::isspace(s[i]) || isInQuote) && i < s.size())
	{
		if (s[i] == QUOTE) isInQuote = !isInQuote;
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

void FntParser::Line::Display() const
{
	std::cout << "name: " << name << std::endl;
	for(auto&& i : values)
	{
		std::cout << "	" << i.first << ": " << i.second.intValue << std::endl;
	}
}
