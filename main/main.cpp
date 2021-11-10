#include <iostream>
#include "huffman_coding.h"

int main()
{
	std::wstring str;
	std::getline(std::wcin, str);
	huffman_coding coding(str);
	std::cout << coding.get_encode() << '\n';
	coding.decode();
	std::wcout << coding.get_decode() << '\n';
	coding.print_code();
}