#pragma once

#include <string>
#include <memory>


namespace RuEnTransliterator {

struct EncodingInfo {
	bool has_bom;
};

std::wstring wstringFromUTF8(const std::string& bytes);
std::string wstringToUTF8(const std::wstring& text);

bool readFileUTF8(const std::string& filename, std::wstring& text, EncodingInfo& info);
bool writeFileUTF8(const std::string& filename, const std::wstring& text, const EncodingInfo& info);

std::wstring russianToEnglish(const std::wstring&);
std::wstring englishToRussian(const std::wstring&);


class TranslatorImpl;

class Transliterator {
private:
	std::unique_ptr<TranslatorImpl> impl;

public:
	Transliterator();
	void setup();
	std::wstring russianToEnglish(const std::wstring&);
	std::wstring englishToRussian(const std::wstring&);
};

extern Transliterator global_transliterator;
extern bool setup_done;

}