#include "Employee.h"

#include <print>

namespace Records
{

Employee::Employee(const std::string &firstName, const std::string &lastName)
	: firstName_(firstName)
	, lastName_(lastName)
{
}

void
Employee::Promote(int raiseAmount)
{
	SetSalary(GetSalary() + raiseAmount);
}

void
Employee::Demote(int demeritAmount)
{
	SetSalary(GetSalary() - demeritAmount);
}

void
Employee::Hire()
{
	hired_ = true;
}

void
Employee::Fire()
{
	hired_ = false;
}

void
Employee::Display() const
{
	std::println("Employee: {}, {}", GetLastName(), GetFirstName());
	std::println("-------------------------");
	std::println("{}", (IsHired() ? "Current Employee" : "Former Employee"));
	std::println("Employee Number: {}", GetEmployeeNumber());
	std::println("Salary: ${}", GetSalary());
	std::println("");
}

void
Employee::SetFirstName(const std::string &firstName)
{
	firstName_ = firstName;
}

const std::string &
Employee::GetFirstName() const
{
	return firstName_;
}

void
Employee::SetLastName(const std::string &lastName)
{
	lastName_ = lastName;
}

const std::string &
Employee::GetLastName() const
{
	return lastName_;
}

void
Employee::SetEmployeeNumber(int employeeNumber)
{
	employeeNumber_ = employeeNumber;
}

int
Employee::GetEmployeeNumber() const
{
	return employeeNumber_;
}

void
Employee::SetSalary(int newSalary)
{
	salary_ = newSalary;
}

int
Employee::GetSalary() const
{
	return salary_;
}

bool
Employee::IsHired() const
{
	return hired_;
}

} // namespace Records
