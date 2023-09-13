#include "RuEnTransliterator.h"

#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Wrong number of arguments!\n";
		return 1;
	}
	std::wstring text;
	RuEnTransliterator::EncodingInfo info;
	if (!RuEnTransliterator::readFileUTF8(argv[1], text, info)) {
		std::cerr << "Cannot read the file \"" << argv[1] << "\"!\n";
		return 1;
	}
	text = RuEnTransliterator::russianToEnglish(text);
	if (!RuEnTransliterator::writeFileUTF8(argv[2], text, info)) {
		std::cerr << "Cannot write to the file \"" << argv[2] << "\"!\n";
		return 1;
	}
}