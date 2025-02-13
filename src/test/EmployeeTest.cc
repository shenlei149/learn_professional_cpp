#include "Employee.h"

#include <gtest/gtest.h>

TEST(EmployeeTest, TestAll)
{
	Records::Employee employee { "Jane", "Doe" };
	employee.SetFirstName("John");
	employee.Hire();
	employee.SetEmployeeNumber(71);
	employee.SetSalary(50'000);
	employee.Promote();
	employee.Promote(50);

	ASSERT_TRUE(employee.IsHired());
	ASSERT_EQ(51'050, employee.GetSalary());
	ASSERT_EQ("John", employee.GetFirstName());
	ASSERT_EQ("Doe", employee.GetLastName());
	ASSERT_EQ(71, employee.GetEmployeeNumber());
}
