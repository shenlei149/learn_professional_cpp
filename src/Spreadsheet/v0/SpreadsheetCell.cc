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

SpreadsheetCell
SpreadsheetCell::operator+(const SpreadsheetCell &rhs) const
{
	return SpreadsheetCell(GetValue() + rhs.GetValue());
}

SpreadsheetCell
SpreadsheetCell::operator+(double value) const
{
	return SpreadsheetCell(GetValue() + value);
}

SpreadsheetCell &
SpreadsheetCell::operator+=(const SpreadsheetCell &rhs)
{
	SetValue(GetValue() + rhs.GetValue());
	return *this;
}

SpreadsheetCell &
SpreadsheetCell::operator+=(double value)
{
	SetValue(GetValue() + value);
	return *this;
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

SpreadsheetCell
operator+(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs)
{
	return SpreadsheetCell(lhs.GetValue() + rhs.GetValue());
}

bool
SpreadsheetCell::operator==(double rhs) const
{
	return GetValue() == rhs;
}

std::partial_ordering
SpreadsheetCell::operator<=>(double rhs) const
{
	return GetValue() <=> rhs;
}
