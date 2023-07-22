#pragma once

#include <vector>
#include <string>
#include <functional>


namespace RuEnTransliterator {

class Tester {
private:
	using Conversion = std::function<std::wstring(const std::wstring&)>;

private:
	Conversion direct;
	Conversion inverse;
	std::wstring symbols;
	size_t word_size = 0;
	std::vector<uint32_t> codes;
	std::wstring word;
	std::vector<int8_t> is_changed;

private:
	static size_t power(size_t base, size_t exponent);
	void resetWord();
	bool nextWord();
	void updateWord();

public:
	Tester(Conversion direct, Conversion inverse);
	void setSymbols(const std::wstring&);
	void run(size_t word_size);
};

}