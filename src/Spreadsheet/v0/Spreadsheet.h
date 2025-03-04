#include "SpreadsheetCell.h"

class Spreadsheet
{
public:
	Spreadsheet(std::size_t width, std::size_t height);

	Spreadsheet(const Spreadsheet &src);
	Spreadsheet &operator=(const Spreadsheet &rhs);

	~Spreadsheet();

	void Swap(Spreadsheet &other) noexcept;

	void SetCellAt(std::size_t x, std::size_t y, const SpreadsheetCell &cell);
	SpreadsheetCell &GetCellAt(std::size_t x, std::size_t y) const;

private:
	bool InRange(std::size_t value, std::size_t upper) const;
	void VerifyCoordinate(std::size_t x, std::size_t y) const;

private:
	std::size_t width_ { 0 };
	std::size_t height_ { 0 };

	// to explain how to handle resource
	SpreadsheetCell **cells_ { nullptr };
};
