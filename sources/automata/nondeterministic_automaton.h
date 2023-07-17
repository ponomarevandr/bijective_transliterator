#pragma once

#include "symbolic_analyser/encoding.h"

#include <iostream>
#include <vector>
#include <functional>


class NondeterministicAutomaton {
public:
	using MaskState = std::vector<int8_t>;
	using ActionFunction = std::function<WordCodes(const std::vector<std::pair<Code, size_t>>&)>;

private:
	struct Node {
		std::vector<size_t> next[CODE_LOWER_SIZE];
		bool is_terminal = false;
		ActionFunction action;
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
	size_t addNode();
	void setTerminal(size_t node, ActionFunction action);
	void addNext(size_t node, Code code, size_t next);
	void debugPrint(std::wostream&) const;
};