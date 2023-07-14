#include "RuEnTransliterator.h"

#include "symbolic_analyser/encoding.h"
#include "automata/nondeterministic_automaton.h"
#include "automata/deterministic_automaton.h"
#include "automata/determinizer.h"

#include <iostream>
#include <string>


int main() {
	Transliterator::setNeutralLocale();

	NondeterministicAutomaton nondet;
	nondet.addNode();
	nondet.addNode();
	nondet.addNode();
	nondet.addNode();
	nondet.addNext(0, 2, 1);
	nondet.addNext(0, 2, 2);
	nondet.addNext(0, 3, 1);
	nondet.addNext(1, 2, 3);
	nondet.addNext(3, 1, 3);
	nondet.addNext(3, 3, 2);

	Determinizer determinizer(nondet);
	determinizer.run();
	DeterministicAutomaton det = determinizer.getResult();

	nondet.debugPrint(std::wcout);
	det.debugPrint(std::wcout);

	return 0;
}