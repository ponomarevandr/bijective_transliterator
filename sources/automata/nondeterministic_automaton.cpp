#include "nondeterministic_automaton.h"


NondeterministicAutomaton::NondeterministicAutomaton() {
	nodes.emplace_back();
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
	return [](const std::vector<std::pair<Code, size_t>>&) -> WordCodes {
		return encodeEnglish(L"ERROR");
	};
}

void NondeterministicAutomaton::step(Code code) {
	MaskState new_state(nodes.size(), false);
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (!current_state[i])
			continue;
		for (size_t j : nodes[i].next[code]) {
			new_state[j] = true;
		}
	}
	history.push_back(std::move(current_state));
	current_state = new_state;
}

void NondeterministicAutomaton::undoStep() {
	if (history.empty())
		return;
	current_state = std::move(history.back());
	history.pop_back();
}

size_t NondeterministicAutomaton::getRoot() const {
	return 0;
}

size_t NondeterministicAutomaton::addNode() {
	nodes.emplace_back();
	current_state.push_back(false);
	return nodes.size() - 1;
}

void NondeterministicAutomaton::setTerminal(size_t node, ActionFunction action) {
	nodes[node].is_terminal = true;
	nodes[node].action = action;
}

void NondeterministicAutomaton::addNext(size_t node, Code code, size_t next) {
	nodes[node].next[code].push_back(next);
}

void NondeterministicAutomaton::debugPrint(std::wostream& out) const {
	out << "Nondeterministic automaton with " << nodes.size() << " nodes\n";
	for (size_t i = 0; i < nodes.size(); ++i) {
		out << "node " << i << " (terminal: " << nodes[i].is_terminal << "):\n";
		for (size_t j = 0; j < CODE_LOWER_SIZE; ++j) {
			if (nodes[i].next[j].empty())
				continue;
			out << "\t" << j << " --> ";
			for (size_t k = 0; k < nodes[i].next[j].size(); ++k) {
				out << nodes[i].next[j][k];
				if (k + 1 < nodes[i].next[j].size())
					out << ", ";
			}
			out << ";\n";
		}
	}
}