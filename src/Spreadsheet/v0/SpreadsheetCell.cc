#include "SpreadsheetCell.h"

#include <charconv>

SpreadsheetCell::SpreadsheetCell(double initValue)
	: value_ { initValue }
{
}

SpreadsheetCell::SpreadsheetCell(std::string_view initValue)
	: SpreadsheetCell { StringToDouble(initValue) }
{
}

void
SpreadsheetCell::SetValue(double value)
{
	value_ = value;
}

double
SpreadsheetCell::GetValue() const
{
	return value_;
}

void
SpreadsheetCell::SetString(std::string_view value)
{
	value_ = StringToDouble(value);
}

std::string
SpreadsheetCell::GetString() const
{
	return DoubleToString(value_);
}

std::string
SpreadsheetCell::DoubleToString(double value)
{
	return std::to_string(value);
}

double
SpreadsheetCell::StringToDouble(std::string_view value)
{
	double number { 0.0 };
	std::from_chars(value.data(), value.data() + value.size(), number);
	return number;
}
