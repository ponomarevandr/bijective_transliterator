#pragma once

#include "symbolic_analyser/encoding.h"

#include <iostream>
#include <vector>
#include <functional>


class NondeterministicAutomaton {
public:
	using MaskState = std::vector<int8_t>;
	using ActionFunction = std::function<WordCodes(const std::vector<size_t>&)>;

private:
	struct Node {
		size_t next_default;
		std::vector<size_t> next[CODE_SIZE];
		bool is_terminal;
		ActionFunction action;

		Node(size_t next_default, bool is_terminal = false);
	};

private:
	std::vector<Node> nodes;
	MaskState current_state;
	std::vector<MaskState> history;

public:
	NondeterministicAutomaton();
	void reset();
	MaskState getCurrentState() const;
	bool isCurrentTerminal() const;
	ActionFunction getCurrentAction() const;
	void step(Code code);
	void undoStep();
	size_t getRoot() const;
	size_t addNode(size_t next_default);
	void setTerminalAndAction(size_t node, ActionFunction action);
	void addNext(size_t node, Code code, size_t next);
	void debugPrint(std::wostream&) const;
};