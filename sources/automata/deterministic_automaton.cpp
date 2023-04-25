#include "deterministic_automaton.h"


DeterministicAutomaton::Node::Node(size_t next_default, bool is_terminal):
		is_terminal(is_terminal) {
	for (size_t i = 0; i < CODE_SIZE; ++i) {
		next[i] = next_default;
	}
}

DeterministicAutomaton::DeterministicAutomaton(): current_state(0) {
	nodes.emplace_back(0);
}

void DeterministicAutomaton::reset() {
	current_state = 0;
}

size_t DeterministicAutomaton::getCurrentState() const {
	return current_state;
}

bool DeterministicAutomaton::isCurrentTerminal() const {
	return nodes[current_state].is_terminal;
}

WordCodes DeterministicAutomaton::doCurrentAction() const {
	return nodes[current_state].action(rows_length);
}

void DeterministicAutomaton::step(Code code) {
	current_state = nodes[current_state].next[code];
}

size_t DeterministicAutomaton::getRoot() const {
	return 0;
}

size_t DeterministicAutomaton::addNode(size_t next_default) {
	nodes.emplace_back(next_default);
	return nodes.size() - 1;
}

void DeterministicAutomaton::setTerminalAndAction(size_t node, ActionFunction action) {
	nodes[node].is_terminal = true;
	nodes[node].action = action;
}

void DeterministicAutomaton::setNext(size_t node, Code code, size_t next) {
	nodes[node].next[code] = next;
}