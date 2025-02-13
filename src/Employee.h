#include <string>

namespace Records
{
const int DefaultStartingSalary { 30'000 };
const int DefaultRaiseAndDemeritAmount { 1'000 };

class Employee
{
public:
	Employee(const std::string &firstName, const std::string &lastName);

	void Promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
	void Demote(int demeritAmount = DefaultRaiseAndDemeritAmount);
	void Hire();		  // Hires or rehires the employee
	void Fire();		  // Dismisses the employee
	void Display() const; // Prints employee info to console

	// Getters and setters
	void SetFirstName(const std::string &firstName);
	const std::string &GetFirstName() const;
	void SetLastName(const std::string &lastName);
	const std::string &GetLastName() const;
	void SetEmployeeNumber(int employeeNumber);
	int GetEmployeeNumber() const;
	void SetSalary(int newSalary);
	int GetSalary() const;
	bool IsHired() const;

private:
	std::string firstName_;
	std::string lastName_;
	int employeeNumber_ { -1 };
	int salary_ { DefaultStartingSalary };
	bool hired_ { false };
};
} // namespace Records
