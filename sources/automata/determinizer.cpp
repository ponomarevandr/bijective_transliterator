#include "determinizer.h"

#include "symbolic_analyser/encoding.h"


bool Determinizer::MasksComparator::operator()(const MaskState& first,
		const MaskState& second) const {
	for (size_t i = 0; i < first.size(); ++i) {
		if (first[i] != second[i])
			return first[i] < second[i];
	}
	return false;
}


Determinizer::Determinizer(const NondeterministicAutomaton& source): source(source) {}

Determinizer::Determinizer(NondeterministicAutomaton&& source): source(std::move(source)) {}

void Determinizer::buildingDfs() {
	MaskState current = source.getCurrentState();
	size_t current_index = index_of_mask[current];
	for (size_t i = 0; i < CODE_LOWER_SIZE; ++i) {
		source.step(i);
		MaskState next = source.getCurrentState();
		if (index_of_mask.count(next)) {
			result.setNext(current_index, i, index_of_mask[next]);
			source.undoStep();
			continue;
		}
		size_t next_index = result.addNode();
		index_of_mask[next] = next_index;
		result.setNext(current_index, i, next_index);
		result.step(i);
		buildingDfs();
		source.undoStep();
		result.undoStep();
	}
}

void Determinizer::run() {
	source.reset();
	result = DeterministicAutomaton();
	index_of_mask.clear();
	index_of_mask[source.getCurrentState()] = result.getCurrentState();
	buildingDfs();
}

DeterministicAutomaton Determinizer::getResult() {
	return std::move(result);
}