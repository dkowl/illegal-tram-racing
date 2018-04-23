#pragma once

#include <string>
#include <map>

class FntParser
{

public:
	static std::string ReadUntil(int& i, const std::string& s, const char& c);
	static std::string ReadUntilWhitespace(int& i, const std::string& s);

	struct Value
	{
		static const char EQUAL;
		static const char QUOTE;

		std::string name;
		std::string stringValue;
		bool isInt;
		int intValue;

		Value() = default;
		explicit Value(const std::string &expression);

		void Display() const;

	};

	struct Line
	{
		static const char SEPARATOR;

		std::string name;
		std::map<std::string, Value> values;

		explicit Line(const std::string& line);

		void AddValue(Value&& value);
		void Display();
	};
};