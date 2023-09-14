#pragma once

#include "RuEnTransliterator.h"

#include <string>


namespace RuEnTransliterator {

std::wstring wstringFromUTF8(const std::string& bytes);
std::string wstringToUTF8(const std::wstring& text);

bool readFileUTF8(const std::string& filename, std::wstring& text, EncodingInfo& info);
bool writeFileUTF8(const std::string& filename, const std::wstring& text, const EncodingInfo& info);

}