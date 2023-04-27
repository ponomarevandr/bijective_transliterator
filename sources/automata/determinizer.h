#pragma once

#include "nondeterministic_automaton.h"
#include "deterministic_automaton.h"

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