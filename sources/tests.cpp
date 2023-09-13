#include "RuEnTransliterator.h"

#include "tester/tester.h"

#include <locale>
#include <string>


size_t estimatedLength(size_t symbols_number) {
	if (symbols_number > 20)
		return 4;
	if (symbols_number > 11)
		return 5;
	if (symbols_number > 7)
		return 6;
	if (symbols_number > 5)
		return 7;
	if (symbols_number > 4)
		return 8;
	if (symbols_number > 3)
		return 9;
	return 12;
}

void testRussianToEnglish(const std::wstring& symbols, size_t length = 0) {
	RuEnTransliterator::Tester tester(RuEnTransliterator::russianToEnglish,
		RuEnTransliterator::englishToRussian);
	tester.setSymbols(symbols);
	if (length == 0)
		length = estimatedLength(symbols.size());
	tester.run(length);
}

void testEnglishToRussian(const std::wstring& symbols, size_t length = 0) {
	RuEnTransliterator::Tester tester(RuEnTransliterator::englishToRussian,
		RuEnTransliterator::russianToEnglish);
	tester.setSymbols(symbols);
	if (length == 0)
		length = estimatedLength(symbols.size());
	tester.run(length);
}

int main() {
	std::setlocale(LC_ALL, "");

	testRussianToEnglish(L" абвгдеёжзийклмнопрстуфхцчшщъыьэюя", 4);
	testEnglishToRussian(L" abcdefghijklmnopqrstuvwxyz", 4);

	testRussianToEnglish(L"ВвУуЩщ");
	testEnglishToRussian(L"IiEeXx");

	testRussianToEnglish(L"сцхктчшщ");
	testEnglishToRussian(L"schkt");

	testRussianToEnglish(L"йоеиёэ");
	testEnglishToRussian(L"yoei");

	testRussianToEnglish(L"йоаихёъ");
	testEnglishToRussian(L"yoaih");

	testRussianToEnglish(L"йоюиёу");
	testEnglishToRussian(L"youi");

	testRussianToEnglish(L"оеайхэы");
	testEnglishToRussian(L"oeayh");

	testRussianToEnglish(L"иеайхьы");
	testEnglishToRussian(L"ieayh");

	testRussianToEnglish(L"йоеаихёэы");
	testEnglishToRussian(L"yoeaih");

	testRussianToEnglish(L"аоуыэиеёюяйх");
	testEnglishToRussian(L"aeiouyh");

	testRussianToEnglish(L"увфйи");
	testEnglishToRussian(L"wouvfyi");

	testRussianToEnglish(L"кгъ");
	testEnglishToRussian(L"qkgoa");

	testRussianToEnglish(L"кгсшх");
	testEnglishToRussian(L"xkgsh");

	testRussianToEnglish(L"кгсщшчт");
	testEnglishToRussian(L"xkgsch");

	return 0;
}