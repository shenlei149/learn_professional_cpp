#include "Spreadsheet.h"

#include <format>
#include <stdexcept>

Spreadsheet::Spreadsheet(std::size_t width, std::size_t height)
	: width_(width)
	, height_(height)
{
	cells_ = new SpreadsheetCell *[width_];
	for (size_t i = 0; i < width_; i++)
	{
		cells_[i] = new SpreadsheetCell[height_];
	}
}

Spreadsheet::Spreadsheet(const Spreadsheet &src)
	: Spreadsheet { src.width_, src.height_ }
{
	for (size_t i = 0; i < width_; i++)
	{
		for (size_t j = 0; j < height_; j++)
		{
			cells_[i][j] = src.cells_[i][j];
		}
	}
}

Spreadsheet &
Spreadsheet::operator=(const Spreadsheet &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Spreadsheet temp { rhs };
	Swap(temp);

	return *this;
}

Spreadsheet::~Spreadsheet()
{
	for (size_t i = 0; i < width_; i++)
	{
		delete[] cells_[i];
	}

	delete[] cells_;
	cells_ = nullptr;
}

void
Spreadsheet::Swap(Spreadsheet &other) noexcept
{
	std::swap(width_, other.width_);
	std::swap(height_, other.height_);
	std::swap(cells_, other.cells_);
}

void
Spreadsheet::SetCellAt(std::size_t x, std::size_t y, const SpreadsheetCell &cell)
{
	VerifyCoordinate(x, y);
	cells_[x][y] = cell;
}

SpreadsheetCell &
Spreadsheet::GetCellAt(std::size_t x, std::size_t y) const
{
	VerifyCoordinate(x, y);
	return cells_[x][y];
}

bool
Spreadsheet::InRange(std::size_t value, std::size_t upper) const
{
	return value < upper;
}

void
Spreadsheet::VerifyCoordinate(std::size_t x, std::size_t y) const
{
	if (!InRange(x, width_))
	{
		throw std::out_of_range(std::format("x({}) must be less than width({}).", x, width_));
	}

	if (!InRange(y, height_))
	{
		throw std::out_of_range(std::format("y({}) must be less than height({}).", y, height_));
	}
}
