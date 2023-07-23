#include "RuEnTransliterator.h"

#include "tester/tester.h"

#include <string>


void testRussianToEnglish(const std::wstring& symbols, size_t length) {
	RuEnTransliterator::Tester tester(RuEnTransliterator::russianToEnglish,
		RuEnTransliterator::englishToRussian);
	tester.setSymbols(symbols);
	tester.run(length);
}

void testEnglishToRussian(const std::wstring& symbols, size_t length) {
	RuEnTransliterator::Tester tester(RuEnTransliterator::englishToRussian,
		RuEnTransliterator::russianToEnglish);
	tester.setSymbols(symbols);
	tester.run(length);
}

int main() {
	RuEnTransliterator::setNeutralLocale();

	testRussianToEnglish(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя ", 4);
	testEnglishToRussian(L"abcdefghijklmnopqrstuvwxyz ", 4);

	return 0;
}