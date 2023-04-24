#include "RuEnTransliterator.h"

#include <locale.h>


namespace Transliterator {

std::wstring russianToEnglish(const std::wstring& text) {
	return L"Not implemented!";
}

std::wstring englishToRussian(const std::wstring& text) {
	return L"Не реализовано!";
}


void setNeutralLocale() {
	setlocale(LC_ALL, "");
}

}