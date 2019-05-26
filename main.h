#include <list>
#include <map>
#include <memory>
#include <string>
/*
struct Node {
	char *label;
	int is_end;
	Node *childs; // new Node[26]
};*/

class Node {
public:
	Node() : root(true), is_end(true) {};
	std::string label;
	bool is_end, root;
	std::list<std::shared_ptr<Node>> children;
    void ShowChidren(std::string pref = "") const;
};

class RadixTree {
	std::map<std::string, std::shared_ptr<Node>> data;
public:
	void Add(std::string &&s);
	void ShowPretty() const;
};
