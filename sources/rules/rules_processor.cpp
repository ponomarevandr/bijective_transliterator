#include "rules_processor.h"


namespace RuEnTransliterator {

void RulesProcessor::Instruction::append(WordCodes& word_codes, size_t number, Code code) {
	for (size_t i = 0; i < number; ++i) {
		word_codes.push_back(code);
	}
}

RulesProcessor::Instruction::Instruction(const std::wstring& my, const std::wstring& opposite,
		std::function<Code(wchar_t)> encode_my, std::function<Code(wchar_t)> encode_opposite) {
	size_t opposite_index = 0;
	size_t opposite_series = 0;
	for (size_t i = 0; i < my.size(); ++i) {
		steps.emplace_back();
		steps.back().code = encode_my(my[i]);
		if (i + 1 == my.size() || (my[i + 1] != L'*' && my[i + 1] != L'+')) {
			steps.back().type = Type::SINGLE;
			continue;
		}
		while (opposite[opposite_index + 1] != L'*' && opposite[opposite_index + 1] != L'+') {
			++opposite_index;
			++opposite_series;
		}
		if (my[i + 1] == L'*' && opposite[opposite_index + 1] == L'*')
			steps.back().type = Type::EQUAL_ZERO;
		if (my[i + 1] == L'*' && opposite[opposite_index + 1] == L'+')
			steps.back().type = Type::LESS;
		if (my[i + 1] == L'+' && opposite[opposite_index + 1] == L'*')
			steps.back().type = Type::GREATER;
		if (my[i + 1] == L'+' && opposite[opposite_index + 1] == L'+')
			steps.back().type = Type::EQUAL_ONE;
		steps.back().series_index = opposite_series;
		steps.back().series_code = encode_opposite(opposite[opposite_index]);
		++i;
		++opposite_index;
	}
}

size_t RulesProcessor::Instruction::addToAutomaton(NondeterministicAutomaton& automaton) const {
	size_t node_current = automaton.getRoot();
	for (const Step step : steps) {
		size_t node_next;
		switch (step.type) {
		case Type::SINGLE:
			node_next = automaton.addNode();
			automaton.addNext(node_current, step.code, node_next);
			node_current = node_next;
			continue;
		case Type::EQUAL_ZERO:
		case Type::LESS:
			automaton.addNext(node_current, step.code, node_current);
			continue;
		case Type::GREATER:
		case Type::EQUAL_ONE:
			node_next = automaton.addNode();
			automaton.addNext(node_current, step.code, node_next);
			automaton.addNext(node_next, step.code, node_next);
			node_current = node_next;
			continue;
		}
	}
	return node_current;
}

WordCodes RulesProcessor::Instruction::operator()(const Series& series) const {
	WordCodes result;
	size_t miss_offset = 0;
	for (const Step step : steps) {
		if (step.type == Type::SINGLE) {
			result.push_back(step.code);
			continue;
		}
		size_t length = 0;
		if (series[step.series_index - miss_offset].first == step.series_code) {
			length = series[step.series_index - miss_offset].second;
		} else {
			++miss_offset;
		}
		switch (step.type) {
		case Type::EQUAL_ZERO:
		case Type::EQUAL_ONE:
			append(result, length, step.code);
			continue;
		case Type::LESS:
			append(result, length - 1, step.code);
			continue;
		case Type::GREATER:
			append(result, length + 1, step.code);
			continue;
		}
	}
	return result;
}


std::vector<std::wstring> RulesProcessor::split(const std::wstring& text) {
	std::vector<std::wstring> result;
	result.emplace_back();
	for (size_t i = 0; i < text.size(); ++i) {
		if (!std::iswspace(text[i])) {
			result.back().push_back(text[i]);
			continue;
		}
		if (!result.back().empty())
			result.emplace_back();
	}
	return result;
}

void RulesProcessor::addRuleText(const std::wstring& text) {
	rules_text.push_back(text);
}

void RulesProcessor::translateRule(const std::wstring& text) {
	std::vector<std::wstring> splitted = split(text);
	std::wstring expression_ru = splitted[0];
	std::wstring expression_en = splitted[2];
	Instruction instruction_ru(expression_ru, expression_en, [](wchar_t symbol) {
		return encodeRussian(symbol);
	}, [](wchar_t symbol) {
		return encodeEnglish(symbol);
	});
	Instruction instruction_en(expression_en, expression_ru, [](wchar_t symbol) {
		return encodeEnglish(symbol);
	}, [](wchar_t symbol) {
		return encodeRussian(symbol);
	});
	size_t node_finish_ru = instruction_ru.addToAutomaton(automaton_ru_en);
	automaton_ru_en.setTerminal(node_finish_ru, instruction_en);
	size_t node_finish_en = instruction_en.addToAutomaton(automaton_en_ru);
	automaton_en_ru.setTerminal(node_finish_en, instruction_ru);
}

void RulesProcessor::run() {
	for (const std::wstring& text : rules_text) {
		translateRule(text);
	}
}

NondeterministicAutomaton RulesProcessor::getAutomatonRuEn() {
	return std::move(automaton_ru_en);
}

NondeterministicAutomaton RulesProcessor::getAutomatonEnRu() {
	return std::move(automaton_en_ru);
}

}