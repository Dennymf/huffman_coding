#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

struct huffman_node
{
	std::wstring data_;
	int rate_;
	huffman_node* left_;
	huffman_node* right_;

	huffman_node() = default;
	huffman_node(std::wstring data, int rate);
	~huffman_node() = default;
};

inline huffman_node::huffman_node(std::wstring data, int rate)
	: data_(data), rate_(rate)
{
	left_ = nullptr;
	right_ = nullptr;
}
#endif