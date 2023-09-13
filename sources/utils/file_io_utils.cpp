#include "file_io_utils.h"

#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <vector>


namespace RuEnTransliterator {

bool readFileUTF8(const std::string& filename, std::wstring& text, EncodingInfo& info) {
	std::ifstream fin(filename, std::ios::binary | std::ios::ate);
	if (fin.fail())
		return false;
	size_t file_size = fin.tellg();
	fin.seekg(0);
	std::vector<char> bytes(file_size);
	fin.read(bytes.data(), file_size);
	fin.close();
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	std::u32string intermediate;
	if (!bytes.empty() && bytes[0] == 0xEF) {
		info.has_bom = true;
		intermediate = converter.from_bytes(bytes.data() + 3, bytes.data() + file_size);
	} else {
		info.has_bom = false;
		intermediate = converter.from_bytes(bytes.data(), bytes.data() + file_size);
	}
	text.resize(intermediate.size());
	for (size_t i = 0; i < intermediate.size(); ++i) {
		text[i] = intermediate[i];
	}
	return true;
}


bool writeFileUTF8(const std::string& filename, const std::wstring& text,
		const EncodingInfo& info) {
	std::u32string intermediate(text.size(), 0);
	for (size_t i = 0; i < text.size(); ++i) {
		intermediate[i] = text[i];
	}
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	std::string bytes = converter.to_bytes(intermediate);
	std::ofstream fout(filename, std::ios::binary);
	if (fout.fail())
		return false;
	if (info.has_bom) {
		std::vector<char> bom(3);
		bom[0] = 0xEF;
		bom[1] = 0xBB;
		bom[2] = 0xBF;
		fout.write(bom.data(), 3);
	}
	fout.write(bytes.data(), bytes.size());
	fout.close();
	return true;
}

}