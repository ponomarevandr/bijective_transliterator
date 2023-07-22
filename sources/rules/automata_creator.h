#pragma once

#include "automata/deterministic_automaton.h"
#include "rules/rules_processor.h"

#include <string>


namespace RuEnTransliterator {

class AutomataCreator {
private:
	RulesProcessor rules_processor;
	DeterministicAutomaton automaton_ru_en;
	DeterministicAutomaton automaton_en_ru;

public:
	AutomataCreator();
	void run();
	DeterministicAutomaton getAutomatonRuEn();
	DeterministicAutomaton getAutomatonEnRu();
};

}