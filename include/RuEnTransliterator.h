#pragma once

#include <string>


namespace Transliterator {

std::wstring russianToEnglish(const std::wstring&);
std::wstring englishToRussian(const std::wstring&);

void setNeutralLocale();

}