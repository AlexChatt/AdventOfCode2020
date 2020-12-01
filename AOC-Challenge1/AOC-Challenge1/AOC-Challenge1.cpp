// AOC-Challenge1.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
	std::vector<uint16_t> Numbers;
	uint16_t num1, num2, num3;
	int answer;
	std::ifstream report("expense-report.txt");

	if (!report)
	{
		std::cout << "Cant not open expense report";
		return 1;
	}

	std::string line;
	while (std::getline(report, line))
	{
		if (line.size() > 0)
		{
			Numbers.push_back(std::stoi(line));
		}
	}
	report.close();

	bool foundCombo1 = false;
	bool foundCombo2 = false;

	for (int i = 0; i < Numbers.size() && (!foundCombo1 || !foundCombo2); i++)
	{
		for (int j = i+1; j < Numbers.size() && (!foundCombo1 || !foundCombo2); j++)
		{
			if (Numbers[i] + Numbers[j] == 2020)
			{
				num1 = Numbers[i];
				num2 = Numbers[j];
				foundCombo1 = true;

				answer = num1 * num2;
				std::cout << num1 << " + " << num2 << " = " << num1 + num2 << '\n';
				std::cout << num1 << " * " << num2 << " = " << answer << '\n';
			}

			for (int k = j + 1; k < Numbers.size() && !foundCombo2; k++)
			{
				if (Numbers[i] + Numbers[j] + Numbers[k] == 2020)
				{
					num1 = Numbers[i];
					num2 = Numbers[j];
					num3 = Numbers[k];
					foundCombo2 = true;

					answer = num1 * num2 * num3;
					std::cout << num1 << " + " << num2 << " + " << num3 << " = " << num1 + num2 + num3 << '\n';
					std::cout << num1 << " * " << num2 << " * " << num3 << " = " << answer << '\n';
				}
			}
		}
	}

	std::cin.get();
}
