#include "nondeterministic_automaton.h"


NondeterministicAutomaton::Node::Node(size_t next_default, bool is_terminal):
	next_default(next_default), is_terminal(is_terminal) {}


NondeterministicAutomaton::NondeterministicAutomaton() {
	nodes.emplace_back(0);
	current_state.push_back(true);
}

void NondeterministicAutomaton::reset() {
	current_state.assign(nodes.size(), false);
	current_state[0] = true;
}

NondeterministicAutomaton::MaskState NondeterministicAutomaton::getCurrentState() const {
	return current_state;
}

bool NondeterministicAutomaton::isCurrentTerminal() const {
	size_t number_of_terminal = 0;
	for (size_t i = 0; i < nodes.size(); ++i) {
		number_of_terminal += current_state[i] && nodes[i].is_terminal;
	}
	return number_of_terminal == 1;
}

NondeterministicAutomaton::ActionFunction NondeterministicAutomaton::getCurrentAction() const {
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (current_state[i])
			return nodes[i].action;
	}
	return [](const std::vector<size_t>&) -> WordCodes {
		return encodeEnglish(L"ERROR");
	};
}

void NondeterministicAutomaton::step(Code code) {
	MaskState new_state(nodes.size(), false);
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (!current_state[i])
			continue;
		if (nodes[i].next[code].empty()) {
			new_state[nodes[i].next_default] = true;
			continue;
		}
		for (size_t j : nodes[i].next[code]) {
			new_state[j] = true;
		}
	}
	current_state = new_state;
}

size_t NondeterministicAutomaton::getRoot() const {
	return 0;
}

size_t NondeterministicAutomaton::addNode(size_t next_default) {
	nodes.emplace_back(next_default);
	return nodes.size() - 1;
}

void NondeterministicAutomaton::setTerminalAndAction(size_t node, ActionFunction action) {
	nodes[node].is_terminal = true;
	nodes[node].action = action;
}

void NondeterministicAutomaton::addNext(size_t node, Code code, size_t next) {
	nodes[node].next[code].push_back(next);
}