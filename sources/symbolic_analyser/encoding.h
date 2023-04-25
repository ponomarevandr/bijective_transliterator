#pragma once

#include <vector>
#include <string>


using Code = int8_t;
using WordCodes = std::vector<Code>;

constexpr size_t CODE_SIZE = 68;
extern const Code CODE_END;
extern const Code CODE_UNKNOWN;

bool isRussian(wchar_t);
bool isEnglish(wchar_t);

bool isLowerCase(wchar_t);
bool isUpperCase(wchar_t);
wchar_t lowerCase(wchar_t);
wchar_t upperCase(wchar_t);

std::wstring lowerCase(const std::wstring);
std::wstring upperCase(const std::wstring);

Code encodeRussian(wchar_t);
Code encodeEnglish(wchar_t);
wchar_t decodeRussian(Code);
wchar_t decodeEnglish(Code);

WordCodes encodeRussian(const std::wstring&);
WordCodes encodeEnglish(const std::wstring&);
std::wstring decodeRussian(const WordCodes&);
std::wstring decodeEnglish(const WordCodes&);