#include "Grid.h"

#include <print>

template class Grid<int>;

int
main()
{
	Grid<double> grid { 100, 20 };
	auto &&value = grid.At(1, 2);
	std::println("value is {}", value.value_or(-1));

	return 0;
}
