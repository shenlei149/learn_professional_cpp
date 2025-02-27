#include <string>

class SpreadsheetCell
{
public:
	void SetValue(double value);
	double GetValue() const;

	void SetString(std::string_view value);
	std::string GetString() const;

private:
	std::string DoubleToString(double value) const;
	double StringToDouble(std::string_view value) const;

private:
	double value_ { 0 };
};
