#pragma once

#include <string>
#include <map>

class FntParser
{

public:

	struct Value
	{
		static const char EQUAL;
		static const char QUOTE;

		std::string name;
		std::string stringValue;
		bool isInt;
		int intValue;

		explicit Value(const std::string &expression);

		static std::string ReadUntil(int& i, const std::string& s, const char& c);
	};

	struct Line
	{
		std::string name;
		std::map<std::string, Value> values;

		explicit Line(std::string line);
	};
};