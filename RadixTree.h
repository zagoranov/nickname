#include <list>
#include <set>
#include <memory>
#include <string>

class Node {
public:
	Node() : is_end(true), parent(nullptr) {};
	std::string label;
	bool is_end;
	std::list<std::shared_ptr<Node>> children;
	std::shared_ptr<Node> parent;

	void ShowChidren(std::string pref = "") const;
	void ShowChidrenUnique(std::string pref = "") const;
};


class RadixTree {
	std::set<std::shared_ptr<Node>> data;
public:
	void Add(std::string &&s);
	void ChangePlaces(std::shared_ptr<Node> pNode, std::shared_ptr<Node> best_parent);
	std::shared_ptr<Node> AddProxy(std::shared_ptr<Node> pNode, std::shared_ptr<Node> best_parent);
	void AddNode(std::shared_ptr<Node> pChild, std::shared_ptr<Node> pParent = nullptr);
	void EraseFromRoot(std::shared_ptr<Node> pNode);

	void ShowPretty() const;
	void ShowUnique() const;
	bool FindSubTree(std::shared_ptr<Node> cur_node, std::string& s2search, std::string& prefix, size_t& prev_max, std::shared_ptr<Node> &pBest_node, std::string &parent_label) const;
};

