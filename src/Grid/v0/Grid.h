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

	std::optional<T> &At(std::size_t x, std::size_t y);
	const std::optional<T> &At(std::size_t x, std::size_t y) const;

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

private:
	std::vector<std::optional<T>> cells_;
	std::size_t width_ { 0 };
	std::size_t height_ { 0 };
};

template<typename T>
inline Grid<T>::Grid(std::size_t width, std::size_t height)
	: width_ { width }
	, height_ { height }
{
	cells_.resize(width_ * height_);
}

template<typename T>
inline std::optional<T> &
Grid<T>::At(std::size_t x, std::size_t y)
{
	return const_cast<std::optional<T> &>(std::as_const(*this).At(x, y));
}

template<typename T>
inline const std::optional<T> &
Grid<T>::At(std::size_t x, std::size_t y) const
{
	VerifyCoordinate(x, y);
	return cells_[x + y * width_];
}

template<typename T>
inline void
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
