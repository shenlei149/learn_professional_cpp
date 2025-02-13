#include <iostream>
#include <print>
#include <string>
#include <vector>

std::string
Replace(const std::string &source, const std::string &find, const std::string &replacement)
{
	std::string result { source };
	auto pos = result.find(find);
	while (pos != std::string::npos)
	{
		result = result.replace(pos, find.size(), replacement);
		pos = result.find(find);
	}

	return result;
}

std::string
Replace(const std::string_view &source,
		const std::string_view &find,
		const std::string_view &replacement)
{
	std::string result { source };
	auto pos = result.find(find);
	while (pos != std::string::npos)
	{
		result = result.replace(pos, find.size(), replacement);
		pos = result.find(find);
	}

	return result;
}

int
main()
{
	std::println("Enter the first string");
	std::string s1;
	std::getline(std::cin, s1);

	std::println("Enter the second string");
	std::string s2;
	std::getline(std::cin, s2);

	auto cmp { s1 <=> s2 };

	std::println("alphabetical order:");
	if (std::is_lteq(cmp))
	{
		std::println("{}\n{}", s1, s2);
	}
	else
	{
		std::println("{}\n{}", s2, s1);
	}

	std::println("Enter the source string");
	std::string haystack;
	std::getline(std::cin, haystack);

	std::println("Enter the string to find");
	std::string needle;
	std::getline(std::cin, needle);

	std::println("Enter the replacement string");
	std::string replacement;
	std::getline(std::cin, replacement);

	println("{}", Replace(haystack, needle, replacement));
	println("{}",
			Replace(std::string_view { haystack },
					std::string_view { needle },
					std::string_view { replacement }));

	std::println("Enter some words, ending with *");
	std::vector<std::string> words;
	std::string word;
	while (std::cin >> word && word != "*")
	{
		words.push_back(word);
	}

	std::size_t length { 0 };
	for (auto &&word : words)
	{
		if (length < word.size())
		{
			length = word.size();
		}
	}

	const int nPerRow { 5 };
	auto ngroups { words.size() / nPerRow };
	for (size_t i = 0; i < ngroups; i++)
	{
		std::println("{1:^{0}} | {2:^{0}} | {3:^{0}} | {4:^{0}} | {5:^{0}}",
					 length,
					 words[i * nPerRow + 0],
					 words[i * nPerRow + 1],
					 words[i * nPerRow + 2],
					 words[i * nPerRow + 3],
					 words[i * nPerRow + 4]);
	}

	if (ngroups * nPerRow < words.size())
	{
		auto index { ngroups * nPerRow };
		while (index < words.size())
		{
			std::print("{1:^{0}}", length, words[index]);
			index++;

			if (index < words.size())
			{
				std::print(" | ");
			}
		}

		std::println();
	}

	return 0;
}
