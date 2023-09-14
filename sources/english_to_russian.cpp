#include "RuEnTransliterator.h"

#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
	if (argc > 3) {
		std::cerr << "Wrong number of arguments!\n";
		return 1;
	}

	if (argc == 1) {
		std::string bytes;
		while (std::getline(std::cin, bytes)) {
			std::wstring text = RuEnTransliterator::wstringFromUTF8(bytes);
			text = RuEnTransliterator::englishToRussian(text);
			bytes = RuEnTransliterator::wstringToUTF8(text);
			std::cout << bytes << std::endl;
		}
		return 0;
	}

	std::wstring text;
	RuEnTransliterator::EncodingInfo info;
	if (!RuEnTransliterator::readFileUTF8(argv[1], text, info)) {
		std::cerr << "Cannot read the file \"" << argv[1] << "\"!\n";
		return 1;
	}
	text = RuEnTransliterator::englishToRussian(text);

	if (argc == 2) {
		std::string bytes = RuEnTransliterator::wstringToUTF8(text);
		std::cout << bytes << std::endl;
		return 0;
	}
	
	if (!RuEnTransliterator::writeFileUTF8(argv[2], text, info)) {
		std::cerr << "Cannot write to the file \"" << argv[2] << "\"!\n";
		return 1;
	}
}