#include "RuEnTransliterator.h"

#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[]) {
	RuEnTransliterator::setNeutralLocale();

	std::wistream* in_ptr = &std::wcin;
	std::wostream* out_ptr = &std::wcout;
	std::wifstream fin;
	std::wofstream fout;
	if (argc >= 2) {
		fin.open(argv[1]);
		if (fin.fail()) {
			std::wcerr << L"Cannot open the input file \"" << argv[1] << L"\"!\n";
			return 1;
		}
		in_ptr = &fin;
	}
	if (argc >= 3) {
		fout.open(argv[2]);
		if (fout.fail()) {
			std::wcerr << L"Cannot open the output file \"" << argv[2] << L"\"!\n";
			return 1;
		}
		out_ptr = &fout;
	}

	std::wstring text = RuEnTransliterator::readWistream(*in_ptr);
	RuEnTransliterator::writeWostream(*out_ptr, RuEnTransliterator::russianToEnglish(text));
	if (fin.is_open())
		fin.close();
	if (fout.is_open())
		fout.close();
}