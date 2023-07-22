#pragma once

#include "symbolic_analyser/encoding.h"

#include <iostream>
#include <vector>
#include <functional>


namespace RuEnTransliterator {

class DeterministicAutomaton {
public:
	using ActionFunction = std::function<WordCodes(const std::vector<std::pair<Code, size_t>>&)>;

private:
	struct Node {
		size_t next[CODE_LOWER_SIZE];
		bool is_terminal = false;
		bool is_perspective = false;
		ActionFunction action;

		Node();
	};

private:
	std::vector<Node> nodes;
	size_t current_state = 0;
	std::vector<size_t> history;
	std::vector<std::pair<Code, size_t>> series;

private:
	void updateIsPerspective(size_t node);

public:
	DeterministicAutomaton();
	void reset();
	size_t getCurrentState() const;
	bool isCurrentTerminal() const;
	bool isCurrentPerspective() const;
	WordCodes currentActionResult() const;
	void step(Code code);
	void undoStep();
	size_t getRoot() const;
	size_t addNode();
	void setTerminal(size_t node, ActionFunction action);
	void setNext(size_t node, Code code, size_t next);
	void updateIsPerspective();
	void debugPrint(std::wostream&) const;
};

}