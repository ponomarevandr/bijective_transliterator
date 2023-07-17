#include "RuEnTransliterator.h"

#include "translator/translator.h"

#include <iostream>
#include <string>


int main() {
	Transliterator::setNeutralLocale();

	Translator translator;
	translator.setup();

	std::wcout << translator.transliterateRuEn(L"Выберете целевой язык:\n");
	std::wstring language;
	std::getline(std::wcin, language);
	language = translator.transliterateRuEn(language);

	if (language[0] == 'e' || language[0] == 'a') {
		std::wcout << translator.transliterateRuEn(
			L"Хорошо, транслитерируем на английский\n\n");
		std::wstring text;
		while (std::getline(std::wcin, text)) {
			std::wcout << translator.transliterateRuEn(text) << "\n";
		}
	} else if (language[0] == 'r') {
		std::wcout << translator.transliterateEnRu(L"OK, transliterating to Russian\n\n");
		std::wstring text;
		while (std::getline(std::wcin, text)) {
			std::wcout << translator.transliterateEnRu(text) << "\n";
		}
	}

	return 0;
}