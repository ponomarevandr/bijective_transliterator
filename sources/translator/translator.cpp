#include "translator.h"

#include "rules/automata_creator.h"

#include <iostream>


void Translator::setup() {
	AutomataCreator creator;
	creator.run();
	automaton_ru_en = creator.getAutomatonRuEn();
	automaton_en_ru = creator.getAutomatonEnRu();
}

WordCodes Translator::transliterateWord(const WordCodes& word, DeterministicAutomaton& automaton) {
	automaton.reset();
	WordCodes result;
	for (size_t i = 1; i <= word.size(); ++i) {
		automaton.step(word[i - 1]);
		if (automaton.isCurrentPerspective())
			continue;
		automaton.undoStep();
		if (!automaton.isCurrentTerminal()) {
			automaton.reset();
			result.push_back(CODE_UNKNOWN);
			continue;
		}
		--i;
		append(result, automaton.currentActionResult());
		automaton.reset();
	}
	if (automaton.isCurrentTerminal()) {
		append(result, automaton.currentActionResult());
	} else {
		result.push_back(CODE_UNKNOWN);
	}
	return result;
}

std::wstring Translator::transliterateRuEn(const std::wstring& text) {
	std::wstring result;
	std::wstring word;
	for (wchar_t symbol : text) {
		if (isRussian(symbol) && isLowerCase(symbol)) {
			word.push_back(symbol);
			continue;
		}
		if (!word.empty()) {
			bool is_capital = isUpperCase(word[0]);
			word[0] = lowerCase(word[0]);
			WordCodes codes = encodeRussian(word);
			codes = transliterateWord(codes, automaton_ru_en);
			std::wstring transliterated = decodeEnglish(codes);
			if (is_capital)
				transliterated[0] = upperCase(transliterated[0]);
			append(result, transliterated);
			word.clear();
		}
		if (!isRussian(symbol)) {
			result.push_back(symbol);
			continue;
		}
		word.push_back(symbol);
	}
	if (!word.empty()) {
		bool is_capital = isUpperCase(word[0]);
		word[0] = lowerCase(word[0]);
		WordCodes codes = encodeRussian(word);
		codes = transliterateWord(codes, automaton_ru_en);
		std::wstring transliterated = decodeEnglish(codes);
		if (is_capital)
			transliterated[0] = upperCase(transliterated[0]);
		append(result, transliterated);
		word.clear();
	}
	return result;
}