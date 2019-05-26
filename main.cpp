#include <iostream>

#include "main.h"

size_t NodeCompare(std::string& s1, std::string& s2) {
	size_t res, max = std::max(s1.length(), s2.length());
	for(res =0; res < max; ++res)
		if(s1[res] != s2[res])
			break;
	return res;
}

void SwapNodes(std::shared_ptr<Node> pOldNode, std::shared_ptr<Node> pNewNode) {
	if(pOldNode->root) {
		pOldNode->root = false;
		pNewNode->root = true;
	}
	pOldNode->is_end = false;
	pNewNode->is_end = true;
	std::swap(pNewNode, pOldNode);
}

void Node::ShowChidren(std::string pref) const {
	std::cout << pref << " + " << label << std::endl;
	for(auto node: children)
		node->ShowChidren(pref + " |");	
}

void RadixTree::Add(std::string &&s) {
	size_t max = 0, i;
	std::shared_ptr<Node> best_parent = nullptr;
	for(auto &node : data) {
		i = NodeCompare(s, node.second->label); 
		if(i > max) {
			best_parent = node.second;
			max = i;
		}
	}
	auto pNode = std::make_shared<Node>();
	pNode->label = s;
	data.insert(std::pair<std::string, std::shared_ptr<Node>>(s, pNode));
	if(max > 0) {
		if(s.length() > best_parent->label.length()) {
			best_parent->is_end = false;
			pNode->root = false;
			best_parent->children.push_back(pNode);
		}
		else {
			if(best_parent->root) {
				best_parent->root = false;
				pNode->root = true;
			}
			best_parent->is_end = false;
			pNode->is_end = true;
			pNode->children.push_back(best_parent);
		}
	}
}

void RadixTree::ShowPretty() const {
	for(auto &node : data){
		if(node.second->root) node.second->ShowChidren();
	}
}


int main()
{
	RadixTree rt;
	rt.Add("aleksey");
	rt.Add("alesha");
	rt.Add("aleks");
	rt.Add("maxim");

	rt.ShowPretty();

	//std::system("pause");
}

/*
aleksey
  alesha
  aleks
maxim


+ ale
| + k$
| | + s$
| | + ey$
| + sha$
+ maksim$
+ sasha$

//  UTF-8
*/
