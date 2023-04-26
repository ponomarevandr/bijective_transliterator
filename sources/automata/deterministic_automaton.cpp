#include "deterministic_automaton.h"

#include <queue>


DeterministicAutomaton::Node::Node(size_t next_default, bool is_terminal):
		is_terminal(is_terminal) {
	for (size_t i = 0; i <= CODE_SIZE; ++i) {
		next[i] = next_default;
	}
}

DeterministicAutomaton::DeterministicAutomaton(): current_state(0) {
	nodes.emplace_back(0);
}

void DeterministicAutomaton::reset() {
	current_state = 0;
	history.clear();
	series_length.clear();
}

size_t DeterministicAutomaton::getCurrentState() const {
	return current_state;
}

bool DeterministicAutomaton::isCurrentTerminal() const {
	return nodes[current_state].is_terminal;
}

bool DeterministicAutomaton::isCurrentPerspective() const {
	return nodes[current_state].is_perspective;
}

WordCodes DeterministicAutomaton::doCurrentAction() const {
	return nodes[current_state].action(series_length);
}

void DeterministicAutomaton::step(Code code) {
	history.push_back(current_state);
	current_state = nodes[current_state].next[code];
	if (series_length.empty() || code != previous_code) {
		series_length.push_back(1);
		previous_code = code;
	} else {
		++series_length.back();
	}
}

void DeterministicAutomaton::undoStep() {
	if (history.empty())
		return;
	current_state = history.back();
	history.pop_back();
	if (series_length.back() == 0) {
		series_length.pop_back();
	} else {
		--series_length.back();
	}
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

void DeterministicAutomaton::updateIsPerspective(size_t node) {
	nodes[node].is_perspective = false;
	std::queue<size_t> queue;
	std::vector<int> is_visited(nodes.size(), false);
	queue.push(node);
	is_visited[node] = true;
	while (!queue.empty()) {
		size_t current = queue.front();
		queue.pop();
		if (nodes[current].is_terminal) {
			nodes[node].is_perspective = true;
			return;
		}
		for (size_t i = 0; i <= CODE_SIZE; ++i) {
			size_t next = nodes[current].next[i];
			if (is_visited[next])
				continue;
			queue.push(next);
			is_visited[next] = true;
		}
	}
}

void DeterministicAutomaton::updateIsPerspective() {
	for (size_t i = 0; i < nodes.size(); ++i) {
		updateIsPerspective(i);
	}
}