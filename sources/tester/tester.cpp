#include "tester.h"

#include "utils/io_utils.h"

#include <iostream>
#include <chrono>
#include <exception>


namespace RuEnTransliterator {

size_t Tester::power(size_t base, size_t exponent) {
	size_t result = 1;
	for (size_t i = 0; i < exponent; ++i) {
		result *= base;
	}
	return result;
}

void Tester::resetWord() {
	codes.assign(word_size, 0);
	word.resize(word_size);
	is_changed.assign(word_size, true);
	updateWord();
}

bool Tester::nextWord() {
	++codes.back();
	is_changed.back() = true;
	for (size_t i = word_size; i > 1 && codes[i - 1] == symbols.size(); --i) {
		codes[i - 1] = 0;
		++codes[i - 2];
		is_changed[i - 2] = true;
	}
	if (codes[0] == symbols.size())
		return false;
	updateWord();
	return true;
}

void Tester::updateWord() {
	for (size_t i = word_size; i > 0 && is_changed[i - 1]; --i) {
		word[i - 1] = symbols[codes[i - 1]];
		is_changed[i - 1] = false;
	}
}


Tester::Tester(Conversion direct, Conversion inverse): direct(direct), inverse(inverse) {}

void Tester::setSymbols(const std::wstring& symbols) {
	this->symbols = symbols;
}

void Tester::run(size_t word_size) {
	this->word_size = word_size;
	std::cout << "Test (\"" << wstringToUTF8(symbols) << "\", " << word_size << ")\n";
	auto time_begin = std::chrono::steady_clock::now();
	resetWord();
	size_t words_counter = 0;
	size_t words_total = power(symbols.size(), word_size);
	size_t progress_bar = 0;
	do {
		std::wstring image = direct(word);
		std::wstring inverse_image = inverse(image);
		if (inverse_image != word) {
			std::cout << "\nError!\n";
			std::cout << "On word \"" << wstringToUTF8(word) << "\"\n";
			std::cout << "The image is \"" << wstringToUTF8(image) <<
				"\", its inverse image is \"" << wstringToUTF8(inverse_image) << "\".";
			std::cout << std::endl;
			throw std::exception();
		}
		++words_counter;
		while (words_counter * 20 / words_total > progress_bar) {
			std::cout << "+";
			std::flush(std::cout);
			++progress_bar;
		}
	} while (nextWord());
	auto time_end = std::chrono::steady_clock::now();
	size_t ms_elapsed =
		std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin).count();
	std::cout << "\nPassed successfully\n";
	std::cout << words_counter << " words, " << ms_elapsed << "ms elapsed\n";
}

}