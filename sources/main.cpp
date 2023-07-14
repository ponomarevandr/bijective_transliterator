#include "RuEnTransliterator.h"

#include "automata/deterministic_automaton.h"
#include "rules/automata_creator.h"

#include <iostream>
#include <string>


int main() {
	Transliterator::setNeutralLocale();

	AutomataCreator creator;
	creator.run();
	DeterministicAutomaton ru_en = creator.getAutomatonRuEn();
	DeterministicAutomaton en_ru = creator.getAutomatonEnRu();

	ru_en.debugPrint(std::wcout);

	return 0;
}