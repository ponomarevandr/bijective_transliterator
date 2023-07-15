#include "RuEnTransliterator.h"

#include "translator/translator.h"

#include <iostream>
#include <string>


int main() {
	Transliterator::setNeutralLocale();

	Translator translator;
	translator.setup();
	std::wstring text;
	while (std::getline(std::wcin, text)) {
		std::wcout << translator.transliterateRuEn(text) << "\n";
	}

	return 0;
}