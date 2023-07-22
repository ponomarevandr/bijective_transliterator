#pragma once

#include <vector>
#include <string>
#include <functional>

#include "symbolic_analyser/encoding.h"
#include "automata/nondeterministic_automaton.h"


namespace RuEnTransliterator {

class RulesProcessor {
public:
	using Series = std::vector<std::pair<Code, size_t>>;

	class Instruction {
	private:
		enum class Type {
			SINGLE,
			EQUAL_ZERO,
			EQUAL_ONE,
			LESS,
			GREATER
		};

		struct Step {
			Code code;
			Type type;
			size_t series_index;
			Code series_code;
		};

	private:
		std::vector<Step> steps;

	private:
		static void append(WordCodes&, size_t, Code);

	public:
		Instruction(const std::wstring& my, const std::wstring& opposite,
			std::function<Code(wchar_t)> encode_my, std::function<Code(wchar_t)> encode_opposite);
		size_t addToAutomaton(NondeterministicAutomaton&) const;
		WordCodes operator()(const Series& series) const;
	};

private:
	std::vector<std::wstring> rules_text;
	NondeterministicAutomaton automaton_ru_en;
	NondeterministicAutomaton automaton_en_ru;

private:
	static std::vector<std::wstring> split(const std::wstring&);
	void translateRule(const std::wstring& text);

public:
	RulesProcessor() = default;
	void addRuleText(const std::wstring& text);
	void run();
	NondeterministicAutomaton getAutomatonRuEn();
	NondeterministicAutomaton getAutomatonEnRu();
};

}