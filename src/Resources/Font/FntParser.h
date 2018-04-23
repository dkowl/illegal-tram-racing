#pragma once

#include <string>
#include <map>
#include <vector>
#include <istream>

class FntParser
{
public:
	struct Line;
	static const char QUOTE;

private:
	std::vector<Line> chars;
	std::vector<Line> kernings;


public:
	explicit FntParser(const std::string& filepath);

	void Display() const;

	static std::string ReadUntil(int& i, const std::string& s, const char& c);
	static std::string ReadUntilWhitespace(int& i, const std::string& s);

	struct Value
	{
		static const char EQUAL;

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
		void Display() const;
	};
};