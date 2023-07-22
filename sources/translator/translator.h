#pragma once

#include "RuEnTransliterator.h"
#include "symbolic_analyser/encoding.h"
#include "automata/deterministic_automaton.h"

#include <string>
#include <functional>


namespace RuEnTransliterator {

class TranslatorImpl: public TranslatorImplBase {
private:
	DeterministicAutomaton automaton_ru_en;
	DeterministicAutomaton automaton_en_ru;

private:
	template <typename VectorT>
	static void append(VectorT& first, const VectorT& second) {
		for (const auto& symbol : second) {
			first.push_back(symbol);
		}
	}

	static WordCodes transliterateWord(WordCodes&, DeterministicAutomaton&);
	std::wstring transliterateText(std::function<bool(wchar_t)> is_language,
		std::function<WordCodes(const std::wstring&)> encode,
		std::function<std::wstring(const WordCodes&)> decode,
		DeterministicAutomaton& automaton, const std::wstring& text);

public:
	TranslatorImpl() = default;
	void setup();
	std::wstring transliterateRuEn(const std::wstring&);
	std::wstring transliterateEnRu(const std::wstring&);
};

}