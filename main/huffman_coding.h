#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "huffman_node.h"

class huffman_coding
{
private:
	std::unordered_map<wchar_t, int> rate_;
	std::unordered_map<wchar_t, std::string> code_;
	std::unordered_map<std::string, wchar_t> alphabet_;
	std::string encode_;
	std::wstring decode_;

	void encode(std::wstring str);
	void generate_code_for_alphabet(huffman_node* v, std::string str);
public:
	huffman_coding();
	huffman_coding(std::wstring str);
	~huffman_coding();

	void decode();

	std::string get_encode();
	std::wstring get_decode();
	void print_code();
};

#endif