#pragma once

#include "automata/nondeterministic_automaton.h"
#include "automata/deterministic_automaton.h"

#include <vector>
#include <map>


class Determinizer {
private:
	using MaskState = NondeterministicAutomaton::MaskState;
	struct MasksComparator {
		bool operator()(const MaskState&, const MaskState&) const;
	};

private:
	NondeterministicAutomaton source;
	DeterministicAutomaton result;
	std::map<MaskState, size_t, MasksComparator> index_of_mask;

private:
	void buildingDfs();

public:
	explicit Determinizer(const NondeterministicAutomaton&);
	explicit Determinizer(NondeterministicAutomaton&&);
	void run();
	DeterministicAutomaton getResult();
};