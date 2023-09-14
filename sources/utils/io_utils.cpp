#include "io_utils.h"

#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <vector>


namespace RuEnTransliterator {

std::wstring wstringFromUTF8(const std::string& bytes) {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	std::u32string intermediate;
	intermediate = converter.from_bytes(bytes);
	std::wstring text(intermediate.size(), 0);
	for (size_t i = 0; i < intermediate.size(); ++i) {
		text[i] = intermediate[i];
	}
	return text;
}

std::string wstringToUTF8(const std::wstring& text) {
	std::u32string intermediate(text.size(), 0);
	for (size_t i = 0; i < text.size(); ++i) {
		intermediate[i] = text[i];
	}
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	std::string bytes = converter.to_bytes(intermediate);
	return bytes;
}

bool readFileUTF8(const std::string& filename, std::wstring& text, EncodingInfo& info) {
	std::ifstream fin(filename, std::ios::binary | std::ios::ate);
	if (fin.fail())
		return false;
	size_t file_size = fin.tellg();
	fin.seekg(0);
	std::string bytes(file_size, 0);
	fin.read(const_cast<char*>(bytes.data()), file_size);
	fin.close();
	info.has_bom = !bytes.empty() && bytes[0] == 0xEF;
	if (info.has_bom)
		bytes.erase(bytes.begin(), bytes.begin() + 3);
	text = wstringFromUTF8(bytes);
	return true;
}


bool writeFileUTF8(const std::string& filename, const std::wstring& text,
		const EncodingInfo& info) {
	std::string bytes = wstringToUTF8(text);
	if (info.has_bom) {
		std::vector<int> bom = { 0xEF, 0xBB, 0xBF };
		bytes.insert(bytes.begin(), bom.begin(), bom.end());
	}
	std::ofstream fout(filename, std::ios::binary);
	if (fout.fail())
		return false;
	fout.write(bytes.data(), bytes.size());
	fout.close();
	return true;
}

}