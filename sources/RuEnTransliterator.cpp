#include "RuEnTransliterator.h"

#include "translator/translator.h"

#include <sstream>
#include <fstream>
#include <codecvt>
#include <locale.h>


namespace RuEnTransliterator {

void setNeutralLocale() {
	setlocale(LC_ALL, "");
}

std::wstring readWistream(std::wistream& fin) {
    fin.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << fin.rdbuf();
    return wss.str();
}

void writeWostream(std::wostream& fout, const std::wstring& text) {
    fout.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    fout << text;
}


Transliterator global_transliterator;
bool setup_done = false;

std::wstring russianToEnglish(const std::wstring& text) {
	if (!setup_done) {
		global_transliterator.setup();
		setup_done = true;
	}
	return global_transliterator.russianToEnglish(text);
}

std::wstring englishToRussian(const std::wstring& text) {
	if (!setup_done) {
		global_transliterator.setup();
		setup_done = true;
	}
	return global_transliterator.englishToRussian(text);
}


Transliterator::Transliterator(): impl(std::make_unique<TranslatorImpl>()) {}

void Transliterator::setup() {
	static_cast<TranslatorImpl*>(impl.get())->setup();
}

std::wstring Transliterator::russianToEnglish(const std::wstring& text) {
	return static_cast<TranslatorImpl*>(impl.get())->transliterateRuEn(text);
}

std::wstring Transliterator::englishToRussian(const std::wstring& text) {
	return static_cast<TranslatorImpl*>(impl.get())->transliterateEnRu(text);
}


}