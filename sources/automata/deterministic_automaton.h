#pragma once

#include "symbolic_analyser/encoding.h"

#include <vector>
#include <functional>


class DeterministicAutomaton {
public:
	using ActionFunction = std::function<WordCodes(const std::vector<size_t>&)>;

private:
	struct Node {
		size_t next[CODE_SIZE + 1];
		bool is_terminal;
		bool is_perspective;
		ActionFunction action;

		Node(size_t next_default, bool is_terminal = false);
	};

private:
	std::vector<Node> nodes;
	size_t current_state;
	std::vector<size_t> history;
	std::vector<size_t> series_length;
	Code previous_code;

private:
	void updateIsPerspective(size_t node);

public:
	DeterministicAutomaton();
	void reset();
	size_t getCurrentState() const;
	bool isCurrentTerminal() const;
	bool isCurrentPerspective() const;
	WordCodes doCurrentAction() const;
	void step(Code code);
	void undoStep();
	size_t getRoot() const;
	size_t addNode(size_t next_default);
	void setTerminalAndAction(size_t node, ActionFunction action);
	void setNext(size_t node, Code code, size_t next);
	void updateIsPerspective();
};