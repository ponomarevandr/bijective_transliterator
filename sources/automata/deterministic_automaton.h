#pragma once

#include "symbolic_analyser/encoding.h"

#include <functional>


class DeterministicAutomaton {
public:
	using ActionFunction = std::function<WordCodes(const std::vector<size_t>&)>;

private:
	struct Node {
		size_t next[CODE_SIZE];
		bool is_terminal;
		ActionFunction action;

		Node(size_t next_default, bool is_terminal = false);
	};

private:
	std::vector<Node> nodes;
	size_t current_state;
	std::vector<size_t> rows_length;

public:
	DeterministicAutomaton();
	void reset();
	size_t getCurrentState() const;
	bool isCurrentTerminal() const;
	WordCodes doCurrentAction() const;
	void step(Code code);
	size_t getRoot() const;
	size_t addNode(size_t next_default);
	void setTerminalAndAction(size_t node, ActionFunction action);
	void setNext(size_t node, Code code, size_t next);
};