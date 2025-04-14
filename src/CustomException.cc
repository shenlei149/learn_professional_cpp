#include <iostream>
#include <memory>
#include <source_location>
#include <stacktrace>
#include <print>

class MyException : public std::exception
{
public:
	explicit MyException(std::string message, std::source_location location = std::source_location::current())
		: message_ { std::move(message) }
		, location_ { std::move(location) }
		, stackTrace_ { std::stacktrace::current(1) } // 1 means skip top frame.
	{
	}

	const char *
	what() const noexcept override
	{
		return message_.c_str();
	}

	virtual const std::source_location &
	where() const noexcept
	{
		return location_;
	}

	virtual const std::stacktrace &
	how() const noexcept
	{
		return stackTrace_;
	}

private:
	std::string message_;
	std::source_location location_;
	std::stacktrace stackTrace_;
};

void
DoSomething()
{
	throw MyException { "error..." };
}

int
main()
{
	try
	{
		DoSomething();
	}
	catch (const MyException &e)
	{
		std::println("error message {}", e.what());
		auto &location = e.where();
		std::println("exception from file {} at line {} in function {}",
					 location.file_name(),
					 location.line(),
					 location.function_name());
		std::println("callstack {}", e.how());
	}

	return 0;
}
