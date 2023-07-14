#include "deterministic_automaton.h"

#include <queue>
#include <algorithm>


DeterministicAutomaton::Node::Node() {
	for (size_t i = 0; i < CODE_LOWER_SIZE; ++i) {
		next[i] = 0;
	}
}

DeterministicAutomaton::DeterministicAutomaton() {
	nodes.emplace_back();
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

WordCodes DeterministicAutomaton::currentActionResult() const {
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

size_t DeterministicAutomaton::addNode() {
	nodes.emplace_back();
	return nodes.size() - 1;
}

void DeterministicAutomaton::setTerminal(size_t node, ActionFunction action) {
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
		for (size_t i = 0; i < CODE_LOWER_SIZE; ++i) {
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

void DeterministicAutomaton::debugPrint(std::wostream& out) const {
	out << "Deterministic automaton with " << nodes.size() << " nodes\n";
	for (size_t i = 0; i < nodes.size(); ++i) {
		std::vector<std::pair<size_t, Code>> edges;
		for (size_t j = 0; j < CODE_LOWER_SIZE; ++j) {
			edges.emplace_back(nodes[i].next[j], j);
		}
		std::sort(edges.begin(), edges.end());
		out << "node " << i << " (terminal: " << nodes[i].is_terminal << "):\n";
		for (size_t j = 0; j < CODE_LOWER_SIZE; ++j) {
			out << edges[j].second;
			if (j + 1 < CODE_LOWER_SIZE && edges[j].first == edges[j + 1].first) {
				out << ", ";
				continue;
			}
			out << " --> " << edges[j].first << ";\n";
		}
	}
}