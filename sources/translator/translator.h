#pragma once

#include "symbolic_analyser/encoding.h"
#include "automata/deterministic_automaton.h"

#include <string>


class Translator {
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

	static WordCodes transliterateWord(const WordCodes&, DeterministicAutomaton&);

public:
	Translator() = default;
	void setup();
	std::wstring transliterateRuEn(const std::wstring&);
	std::wstring transliterateEnRu(const std::wstring&);
};