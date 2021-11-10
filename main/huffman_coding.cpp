#include "huffman_coding.h"

struct compare {
	bool operator()(huffman_node* a, huffman_node* b) const {
		if (a->rate_ < b->rate_)
		{
			return true;
		}
		if (a->rate_ == b->rate_)
		{
			if (a->data_.size() > b->data_.size())
			{
				return false;
			}
			else if (a->data_.size() < b->data_.size())
			{
				return true;
			}
			else
			{
				for (size_t i = 0; i < a->data_.size(); ++i)
				{
					if (a->data_[i] < b->data_[i])
					{
						return true;
					}
					else if (a->data_[i] > b->data_[i])
					{
						return false;
					}
				}
				return false;
			}
		}
		return false;
	}
};

huffman_coding::huffman_coding() = default;

huffman_coding::huffman_coding(std::wstring str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		rate_[str[i]]++;
	}

	if (rate_.size() == 1)
	{
		const auto& it = rate_.begin();
		alphabet_["0"] = it->first;
		code_[it->first] = "0";
		encode(str);
		return;
	}
	std::set<huffman_node*, compare> hp;

	for (const auto &it : rate_)
	{
		std::wstring tmp = L"";
		tmp += it.first;
		hp.insert(new huffman_node(tmp, it.second));
	}

	while (hp.size() > 1)
	{
		huffman_node* left = *hp.begin();
		hp.erase(hp.begin());

		huffman_node* right = *hp.begin();
		hp.erase(hp.begin());

		huffman_node* v = new huffman_node(left->data_ + right->data_, left->rate_ + right->rate_);
		v->left_ = left;
		v->right_ = right;

		hp.insert(v);
	}

	generate_code_for_alphabet(*hp.begin(), "");

	encode(str);
}

huffman_coding::~huffman_coding()
{
}

void huffman_coding::generate_code_for_alphabet(huffman_node *v, std::string str)
{
	if (v->data_.size() > 1)
	{
		generate_code_for_alphabet(v->left_, str + "0");
		generate_code_for_alphabet(v->right_, str + "1");
	}
	else
	{
		alphabet_[str] = v->data_[0];
		code_[v->data_[0]] = str;
	}
}

void huffman_coding::encode(std::wstring str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		encode_ += code_[str[i]];
	}
}

void huffman_coding::decode()
{
	decode_ = L"";
	std::string cur = "";
	for (size_t i = 0; i < encode_.size(); ++i)
	{
		cur += encode_[i];
		if (alphabet_.find(cur) != alphabet_.end())
		{
			decode_ += alphabet_.find(cur)->second;
			cur = "";
		}
	}
	if (alphabet_.find(cur) != alphabet_.end())
	{
		decode_ += alphabet_.find(cur)->second;
		cur = "";
	}
}

std::string huffman_coding::get_encode()
{
	return encode_;
}

std::wstring huffman_coding::get_decode()
{
	return decode_;
}

void huffman_coding::print_code()
{
	std::vector<std::pair<std::string, wchar_t>> out;
	for (const auto& it : code_)
	{
		out.push_back({ it.second, it.first });
	}
	sort(out.begin(), out.end());

	for (const auto& it : out)
	{
		std::wcout << it.second << " : ";
		std::cout << it.first << '\n';
	}
}
