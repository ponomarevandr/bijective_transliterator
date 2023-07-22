#pragma once

#include <string>
#include <memory>


namespace RuEnTransliterator {

void setNeutralLocale();

std::wstring russianToEnglish(const std::wstring&);
std::wstring englishToRussian(const std::wstring&);


class TranslatorImplBase {
public:
	virtual ~TranslatorImplBase() = default;
};

class Transliterator {
private:
	std::unique_ptr<TranslatorImplBase> impl;

public:
	Transliterator();
	void setup();
	std::wstring russianToEnglish(const std::wstring&);
	std::wstring englishToRussian(const std::wstring&);
};

extern Transliterator global_transliterator;
extern bool setup_done;

}