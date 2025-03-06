#include <string>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initValue);
	SpreadsheetCell(std::string_view initValue);

public:
	void SetValue(double value);
	double GetValue() const;

	void SetString(std::string_view value);
	std::string GetString() const;

private:
	static std::string DoubleToString(double value);
	static double StringToDouble(std::string_view value);

private:
	double value_ { 0 };
};
