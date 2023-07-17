#include "translator.h"

#include "rules/automata_creator.h"

#include <iostream>


void Translator::setup() {
	AutomataCreator creator;
	creator.run();
	automaton_ru_en = creator.getAutomatonRuEn();
	automaton_en_ru = creator.getAutomatonEnRu();
}

WordCodes Translator::transliterateWord(WordCodes& word, DeterministicAutomaton& automaton) {
	automaton.reset();
	WordCodes result;
	word.push_back(CODE_END);
	for (size_t i = 0;; ++i) {
		automaton.step(word[i]);
		if (automaton.isCurrentPerspective())
			continue;
		do {
			automaton.undoStep();
			--i;
		} while (!automaton.isCurrentTerminal() &&
			automaton.getCurrentState() != automaton.getRoot());
		if (!automaton.isCurrentTerminal())
			break;
		append(result, automaton.currentActionResult());
		automaton.reset();
	}
	return result;
}

std::wstring Translator::transliterateText(std::function<bool(wchar_t)> is_language,
		std::function<WordCodes(const std::wstring&)> encode,
		std::function<std::wstring(const WordCodes&)> decode,
		DeterministicAutomaton& automaton, const std::wstring& text) {
	std::wstring result;
	std::wstring word;
	for (size_t i = 0;; ++i) {
		wchar_t symbol = i < text.size() ? text[i] : L'\0';
		if (is_language(symbol) && isLowerCase(symbol)) {
			word.push_back(symbol);
			continue;
		}
		if (!word.empty()) {
			bool is_capital = isUpperCase(word[0]);
			word[0] = lowerCase(word[0]);
			WordCodes codes = encode(word);
			codes = transliterateWord(codes, automaton);
			std::wstring transliterated = decode(codes);
			if (is_capital)
				transliterated[0] = upperCase(transliterated[0]);
			append(result, transliterated);
			word.clear();
		}
		if (i == text.size())
			break;
		if (is_language(symbol)) {
			word.push_back(symbol);
			continue;
		}
		result.push_back(symbol);
	}
	return result;
}

std::wstring Translator::transliterateRuEn(const std::wstring& text) {
	return transliterateText(isRussian, [](const std::wstring& string) {
		return encodeRussian(string);
	}, [](const WordCodes& word_codes) {
		return decodeEnglish(word_codes);
	}, automaton_ru_en, text);
}

std::wstring Translator::transliterateEnRu(const std::wstring& text) {
	return transliterateText(isEnglish, [](const std::wstring& string) {
		return encodeEnglish(string);
	}, [](const WordCodes& word_codes) {
		return decodeRussian(word_codes);
	}, automaton_en_ru, text);
}