#pragma once

#include <vector>
#include <string>
#include <functional>

#include "symbolic_analyser/encoding.h"
#include "automata/nondeterministic_automaton.h"


class RulesProcessor {
public:
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
		};

	private:
		std::vector<Step> steps;

	private:
		static void append(WordCodes&, size_t, Code);

	public:
		Instruction(const std::wstring& my, const std::wstring& opposite,
			std::function<Code(wchar_t)> encode);
		size_t addToAutomaton(NondeterministicAutomaton&) const;
		WordCodes operator()(const std::vector<size_t>& series_length) const;
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