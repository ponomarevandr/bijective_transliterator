#include "encoding.h"


const Code CODE_END = 0;
const Code CODE_UNKNOWN = 1;


bool isRussianLowerCase(wchar_t symbol) {
	return symbol == L'ё' || (L'а' <= symbol && symbol <= L'я');
}

bool isRussianUpperCase(wchar_t symbol) {
	return symbol == L'Ё' || (L'А' <= symbol && symbol <= L'Я');
}

bool isEnglishLowerCase(wchar_t symbol) {
	return (L'a' <= symbol && symbol <= L'z');
}

bool isEnglishUpperCase(wchar_t symbol) {
	return (L'A' <= symbol && symbol <= L'Z');
}


bool isRussian(wchar_t symbol) {
	return isRussianLowerCase(symbol) || isRussianUpperCase(symbol);
}

bool isEnglish(wchar_t symbol) {
	return isEnglishLowerCase(symbol) || isEnglishUpperCase(symbol);
}


bool isLowerCase(wchar_t symbol) {
	return isRussianLowerCase(symbol) || isEnglishLowerCase(symbol);
}

bool isUpperCase(wchar_t symbol) {
	return isRussianUpperCase(symbol) || isEnglishUpperCase(symbol);
}


wchar_t lowerCase(wchar_t symbol) {
	if (!isUpperCase(symbol))
		return symbol;
	if (isEnglishUpperCase(symbol))
		return symbol - L'A' + L'a';
	if (symbol == L'Ё')
		return L'ё';
	return symbol - L'А' + L'а';
}

wchar_t upperCase(wchar_t symbol) {
	if (!isLowerCase(symbol))
		return symbol;
	if (isEnglishLowerCase(symbol))
		return symbol - L'a' + L'A';
	if (symbol == L'ё')
		return L'Ё';
	return symbol - L'а' + L'А';
}


std::wstring lowerCase(const std::wstring word) {
	std::wstring result;
	for (wchar_t symbol : word) {
		result.push_back(lowerCase(symbol));
	}
	return result;
}

std::wstring upperCase(const std::wstring word) {
	std::wstring result;
	for (wchar_t symbol : word) {
		result.push_back(upperCase(symbol));
	}
	return result;
}


Code encodeRussian(wchar_t symbol) {
	if (L'а' <= symbol && symbol <= L'е')
		return 2 + (symbol - L'а');
	if (symbol == L'ё')
		return 8;
	if (L'ж' <= symbol && symbol <= L'я')
		return 9 + (symbol - L'ж');
	if (L'А' <= symbol && symbol <= L'Е')
		return 35 + (symbol - L'А');
	if (symbol == L'Ё')
		return 41;
	if (L'Ж' <= symbol && symbol <= L'Я')
		return 42 + (symbol - L'Ж');
	return CODE_UNKNOWN;
}

Code encodeEnglish(wchar_t symbol) {
	if (L'a' <= symbol && symbol <= L'z')
		return 2 + (symbol - L'a');
	if (L'A' <= symbol && symbol <= L'Z')
		return 28 + (symbol - L'A');
	return CODE_UNKNOWN;
}


wchar_t decodeRussian(Code code) {
	if (code == CODE_END)
		return L'×';
	if (2 <= code && code <= 7)
		return L'а' + (code - 2);
	if (code == 8)
		return L'ё';
	if (9 <= code && code <= 34)
		return L'ж' + (code - 9);
	if (35 <= code && code <= 40)
		return L'А' + (code - 35);
	if (code == 41)
		return L'Ё';
	if (42 <= code && code <= 67)
		return L'Ж' + (code - 42);
	return L'¿';
}

wchar_t decodeEnglish(Code code) {
	if (code == CODE_END)
		return L'×';
	if (2 <= code && code <= 27)
		return L'a' + (code - 2);
	if (28 <= code && code <= 53)
		return L'A' + (code - 28);
	return L'¿';
}

WordCodes encodeRussian(const std::wstring& word) {
	WordCodes result;
	for (wchar_t symbol : word) {
		result.push_back(encodeRussian(symbol));
	}
	return result;
}

WordCodes encodeEnglish(const std::wstring& word) {
	WordCodes result;
	for (wchar_t symbol : word) {
		result.push_back(encodeEnglish(symbol));
	}
	return result;
}

std::wstring decodeRussian(const WordCodes& codes) {
	std::wstring result;
	for (wchar_t code : codes) {
		result.push_back(decodeRussian(code));
	}
	return result;
}

std::wstring decodeEnglish(const WordCodes& codes) {
	std::wstring result;
	for (wchar_t code : codes) {
		result.push_back(decodeEnglish(code));
	}
	return result;
}