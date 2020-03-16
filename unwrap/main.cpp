#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>

std::string UnwrapString(const std::string& inputString)
{
	auto messageContent{ inputString };
	if (messageContent.find_first_of("\r\n") != std::string::npos)
	{
		// Message content contains CR/LF
		std::replace(messageContent.begin(), messageContent.end(), '\r', '\n');

		// Sanitise input so it appears cohesive; that is, CRLF that may have
		// put words (e.g. foo\r\nbar -> foobar) together will have a space between them (foo bar).
		auto separator = "";
		std::istringstream stream(messageContent);
		std::string line;
		std::string output;
		while (std::getline(stream, line))
		{
			line.erase(std::find_if(line.rbegin(), line.rend(), [](const char c) {
				return !std::isspace(c);	// rtrim white space
			}).base(), line.end());
			if (!line.empty())
			{
				// append to output
				output += separator + line;
				separator = " ";
			}
		}
		messageContent = std::move(output);
	}
	return messageContent;
}

int main()
{
	const std::string expected = "A Hamsterish Hoard of Dungeons and Dragons' by taichara is the #OSR blog of the Day! https://t.co/KXu3DZpFGp";
	const char* string = "A Hamsterish Hoard of Dungeons and Dragons' by taichara \ris the #OSR blog of the Day! \r\nhttps://t.co/KXu3DZpFGp\r\n";

	const auto unwrappedString = UnwrapString(string);

	assert(expected == unwrappedString);
	
	return 0;
}
