#include "RuEnTransliterator.h"

#include "translator/translator.h"
#include "utils/file_io_utils.h"


namespace RuEnTransliterator {

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
	impl->setup();
}

std::wstring Transliterator::russianToEnglish(const std::wstring& text) {
	return impl->transliterateRuEn(text);
}

std::wstring Transliterator::englishToRussian(const std::wstring& text) {
	return impl->transliterateEnRu(text);
}

}