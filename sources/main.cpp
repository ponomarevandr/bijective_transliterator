#include "RuEnTransliterator.h"

#include "symbolic_analyser/encoding.h"
#include "automata/nondeterministic_automaton.h"
#include "automata/deterministic_automaton.h"
#include "automata/determinizer.h"
#include "rules/rules_processor.h"

#include <iostream>
#include <string>


int main() {
	Transliterator::setNeutralLocale();

	RulesProcessor rules_processor;
	rules_processor.addRuleText(L"а <--> a");
	rules_processor.addRuleText(L"йи*ой*е	<--> yi+oy+e");

	rules_processor.run();
	NondeterministicAutomaton nondet = rules_processor.getAutomatonRuEn();

	nondet.debugPrint(std::wcout);

	return 0;
}