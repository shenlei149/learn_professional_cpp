#include <exception>
#include <format>
#include <optional>
#include <utility>
#include <vector>

template<typename T>
class Grid
{
public:
	explicit Grid(std::size_t width = DefaultWidth, std::size_t height = DefaultHeight);
	virtual ~Grid() = default;

	Grid(const Grid &src) = default;
	Grid &operator=(const Grid &rhs) = default;
	Grid(Grid &&src) = default;
	Grid &operator=(Grid &&rhs) = default;

	template<typename E>
	Grid(const Grid<E> &src);
	template<typename E>
	Grid &operator=(const Grid<E> &rhs);

	template<typename Self>
	auto &&At(this Self &&self, std::size_t x, std::size_t y);

	std::size_t
	GetWidth() const
	{
		return width_;
	}

	std::size_t
	GetHeight() const
	{
		return height_;
	}

public:
	static constexpr std::size_t DefaultWidth { 10 };
	static constexpr std::size_t DefaultHeight { 10 };

private:
	void VerifyCoordinate(std::size_t x, std::size_t y) const;
	void Swap(Grid &other) noexcept;

private:
	std::vector<std::optional<T>> cells_;
	std::size_t width_ { 0 };
	std::size_t height_ { 0 };
};

template<typename T>
Grid<T>::Grid(std::size_t width, std::size_t height)
	: width_ { width }
	, height_ { height }
{
	cells_.resize(width_ * height_);
}

template<typename T>
template<typename E>
Grid<T>::Grid(const Grid<E> &src)
	: Grid { src.GetWidth(), src.GetHeight() }
{
	for (size_t i = 0; i < width_; i++)
	{
		for (size_t j = 0; j < height_; j++)
		{
			At(i, j) = src.At(i, j);
		}
	}
}

template<typename T>
template<typename E>
Grid<T> &
Grid<T>::operator=(const Grid<E> &rhs)
{
	Grid<T> temp { rhs };
	Swap(temp);
	return *this;
}

template<typename T>
template<typename Self>
auto &&
Grid<T>::At(this Self &&self, std::size_t x, std::size_t y)
{
	self.VerifyCoordinate(x, y);
	return std::forward_like<Self>(self.cells_[x + y * self.width_]);
}

template<typename T>
void
Grid<T>::VerifyCoordinate(std::size_t x, std::size_t y) const
{
	if (x >= width_)
	{
		throw std::out_of_range { std::format("x ({}) must be less than width ({}).", x, width_) };
	}

	if (y >= height_)
	{
		throw std::out_of_range { std::format("y ({}) must be less than height ({}).", y, height_) };
	}
}

template<typename T>
void
Grid<T>::Swap(Grid &other) noexcept
{
	std::swap(width_, other.width_);
	std::swap(height_, other.height_);
	std::swap(cells_, other.cells_);
}
