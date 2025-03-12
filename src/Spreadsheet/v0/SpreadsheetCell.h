#include <string>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initValue);
	SpreadsheetCell(std::string_view initValue);

public:
	SpreadsheetCell operator+(const SpreadsheetCell &rhs) const;
	SpreadsheetCell operator+(double value) const;
	SpreadsheetCell &operator+=(const SpreadsheetCell &rhs);
	SpreadsheetCell &operator+=(double value);

public:
	[[nodiscard]]
	auto operator<=>(const SpreadsheetCell &) const = default;
	[[nodiscard]]
	bool operator==(const SpreadsheetCell &) const = default;

	[[nodiscard]]
	bool operator==(double rhs) const;
	[[nodiscard]]
	std::partial_ordering operator<=>(double rhs) const;

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

SpreadsheetCell operator+(const SpreadsheetCell &lhs, const SpreadsheetCell &rhs);
