#pragma once

#include <vector>
#include <string>


using WordCodes = std::vector<int8_t>;

extern const size_t RUSSIAN_CODE_SIZE;
extern const size_t ENGLISH_CODE_SIZE;
extern const int8_t CODE_END;
extern const int8_t CODE_UNKNOWN;

bool isRussian(wchar_t);
bool isEnglish(wchar_t);

bool isLowerCase(wchar_t);
bool isUpperCase(wchar_t);
wchar_t lowerCase(wchar_t);
wchar_t upperCase(wchar_t);

std::wstring lowerCase(const std::wstring);
std::wstring upperCase(const std::wstring);

int8_t encodeRussian(wchar_t);
int8_t encodeEnglish(wchar_t);
wchar_t decodeRussian(int8_t);
wchar_t decodeEnglish(int8_t);

WordCodes encodeRussian(const std::wstring&);
WordCodes encodeEnglish(const std::wstring&);
std::wstring decodeRussian(const WordCodes&);
std::wstring decodeEnglish(const WordCodes&);