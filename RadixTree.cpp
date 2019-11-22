#include <iostream>
#include <algorithm>
#include "RadixTree.h"


size_t NodeCompare(const std::string& s1, const std::string& s2) {
	size_t res, max = std::max(s1.length(), s2.length());
	for(res = 0; res < max; ++res)
		if(s1[res] != s2[res])
			break;
	return res;
}

//-----------------------------------------------------------------------------------------

void Node::ShowChidren(std::string& pref) const {
	std::cout << pref << " + " << label << (is_end?"$":"") << std::endl;
	for(const auto node: children)
		node->ShowChidren(pref + " |");	
}

void Node::ShowChidrenUnique(std::string& pref) const {
	if (is_end)
		std::cout << pref + label << " " << pref << label[0] << std::endl;
	for (const auto& node : children)
		node->ShowChidrenUnique(pref + label);
}

//-----------------------------------------------------------------------------------------

void RadixTree::AddNode(std::shared_ptr<Node>& pChild, std::shared_ptr<Node>& pParent) {
	if (pParent) {
		pChild->parent = pParent;
		pParent->children.push_back(pChild);
	}
	else
		data.insert(pChild);
}

void RadixTree::EraseFromRoot(const std::shared_ptr<Node>& pNode) {
	auto it = data.find(pNode);
	if (it != data.end())
		data.erase(it);
}

std::shared_ptr<Node> RadixTree::AddProxy(std::shared_ptr<Node>& pNode, std::shared_ptr<Node>& best_parent) {
	auto pProxiNode = std::make_shared<Node>();
	std::shared_ptr<Node> pBigParent = best_parent->parent;
	if (pBigParent) {
		pBigParent->children.remove(best_parent);
		AddNode(pProxiNode, pBigParent);
	}
	else {
		EraseFromRoot(best_parent);
		AddNode(pProxiNode);
	}
	pProxiNode->is_end = false;
	AddNode(pNode, pProxiNode);
	AddNode(best_parent, pProxiNode);
	return pProxiNode;
}


void RadixTree::ChangePlaces(std::shared_ptr<Node>& pNode, std::shared_ptr<Node>& best_parent) {
	if (best_parent->parent) {
		auto pBigParent = best_parent->parent;
		if (pBigParent) {
			pBigParent->children.remove(best_parent);
			AddNode(pNode, pBigParent);
		}
		else {
			EraseFromRoot(best_parent);
			AddNode(pNode);
		}
	}
	AddNode(best_parent, pNode);
}


bool RadixTree::FindSubTree(const std::shared_ptr<Node>& cur_node, std::string& s2search, std::string& prefix, size_t& prev_max, std::shared_ptr<Node> &pBest_node, std::string &parent_label) const {
	bool res = false;
	std::string wholelabel = prefix + cur_node->label;
	size_t i = NodeCompare(wholelabel, s2search);
	if (i > prev_max || (i > 0 && i == prev_max && !pBest_node->is_end)) {
		pBest_node = cur_node;
		prev_max = i;
		parent_label = wholelabel;
		res = true;
	}
	for (auto& node : cur_node->children)
		res = res | FindSubTree(node, s2search, wholelabel, prev_max, pBest_node, parent_label);
	return res;
}

void RadixTree::Add(std::string &&s) {
	size_t max = 0, i;
	std::string parent_label = "";
	std::shared_ptr<Node> best_parent = nullptr;
	for (auto &node : data) {
			FindSubTree(node, s, parent_label, max, best_parent, parent_label);
	}
	auto pNode = std::make_shared<Node>();
	if (max == 0 || max == s.length())
		pNode->label = s;
	else
		pNode->label = s.substr(max, s.length() - max);
	// íå íàøëè ïîäõîäÿùåãî ðîäèòåëÿ
	if (max == 0) {
		AddNode(pNode);
	}
	else // íàøëè ïîäõîäÿùåãî ðîäèòåëÿ
	{
		// ñîçäàåì ïðîìåæóòî÷íóþ íîäó è äîáàâëÿåìñÿ ñ ðîäèòåëåì â äåòè, (îáðåçàâ label ó ðîäèòåëÿ)
		if (max < s.length() && max < parent_label.length() ) {  
			std::shared_ptr<Node> pProxiNode = AddProxy(pNode, best_parent);
			pProxiNode->label = s.substr(parent_label.length() - best_parent->label.length(), std::max(s.length(), parent_label.length()) - max);
			best_parent->label = parent_label.substr(max, parent_label.length() - (max - 1));
		}
		// ìû ìåíüøå ðîäèòåëÿ, òåïåðü ìû ðîäèòåëü, à îí ó íàñ â ÷àéëäàõ (ïðåäâàðèòåëüíî îáðåçàâ label ó ðîäèòåëÿ)
		else if (max == s.length())  { 
			pNode->label = s.substr(parent_label.length() - best_parent->label.length(), max - (parent_label.length() - best_parent->label.length()));
			best_parent->label = parent_label.substr(max, parent_label.length() - (max - 1));
			ChangePlaces(pNode, best_parent);
		}
		// ìû áîëüøå ðîäèòåëÿ, ïðîñòî äîáàâëÿåìñÿ ê íåìó äåòè
		else if (max == parent_label.length()) { 
			AddNode(pNode, best_parent);
		}
	}
}

void RadixTree::ShowPretty() const {
	for(const auto &node : data){
			node->ShowChidren();
	}
}

void RadixTree::ShowUnique() const {
	for (const auto &node : data) {
			node->ShowChidrenUnique();
	}
}
