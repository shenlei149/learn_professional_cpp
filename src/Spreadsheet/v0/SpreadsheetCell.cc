#include "SpreadsheetCell.h"

#include <charconv>

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
SpreadsheetCell::DoubleToString(double value) const
{
	return std::to_string(value);
}

double
SpreadsheetCell::StringToDouble(std::string_view value) const
{
	double number { 0.0 };
	std::from_chars(value.data(), value.data() + value.size(), number);
	return number;
}
