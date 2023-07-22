#include "RuEnTransliterator.h"

#include "translator/translator.h"

#include <iostream>
#include <string>


int main() {
	RuEnTransliterator::setNeutralLocale();

	std::wcout << RuEnTransliterator::russianToEnglish(L"Выберете целевой язык:\n");
	std::wstring language;
	std::getline(std::wcin, language);
	language = RuEnTransliterator::russianToEnglish(language);

	if (language[0] == 'e' || language[0] == 'a') {
		std::wcout << RuEnTransliterator::russianToEnglish(
			L"Хорошо, транслитерируем на английский\n\n");
		std::wstring text;
		while (std::getline(std::wcin, text)) {
			std::wcout << RuEnTransliterator::russianToEnglish(text) << "\n";
		}
	} else if (language[0] == 'r') {
		std::wcout << RuEnTransliterator::englishToRussian(L"OK, transliterating to Russian\n\n");
		std::wstring text;
		while (std::getline(std::wcin, text)) {
			std::wcout << RuEnTransliterator::englishToRussian(text) << "\n";
		}
	}

	return 0;
}