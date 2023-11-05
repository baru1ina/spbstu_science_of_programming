#include "tree.h"

iterator tree::begin() {
	iterator itr(root.get());
	return itr;
}

iterator tree::end() {
	iterator itr(root.get());
	itr = root->end();
	return itr;
}

void tree::load(const std::string& infilename) {
	std::ifstream file(infilename);

	if (!file)
		throw std::runtime_error("file opening error\n");
	
	std::stack<std::shared_ptr<node>> nodes;
	
	std::string line;

	std::getline(file, line);
	if (line.empty())
		throw std::runtime_error("wrong file format \n");
	else {
		while (std::getline(file, line)) {
			if (line.empty())
				throw std::runtime_error("empty xml file\n");

			std::string::size_type ptr;
			while ((ptr = line.find(' ')) != std::string::npos)
				line.erase(ptr, 1);

			size_t i = 0;
			while (line[i] == '\t')
				i++;

			if (line.find("</") != std::string::npos)
				continue;

			size_t positionBegin = line.find('<');
			size_t positionEnd = line.find('>');
			std::string tagName = line.substr(i + 1, positionEnd - positionBegin - 1);

			size_t position = line.find('=');
			std::string tagValue = line.substr(position + 1);

			std::shared_ptr<node> newNode(new node(tagName, tagValue));

			if (i == 0) {
				this->root = newNode;
				nodes.push(newNode);
			}
			else {
				while (nodes.size() > i) nodes.pop();
				newNode->setParent(nodes.top());
				nodes.top()->push_back(newNode);
			}
			nodes.push(newNode);
		}
	}
	file.close();
}

void tree::save(std::shared_ptr<node> root, int hight, std::ofstream& outfilename) {
	if (root == nullptr) exit(1);
	std::string indent = "";
	for (int i = 0; i < hight; i++)
		indent += "\t";
	outfilename << indent << "<" << root->getKey() << ">" << " value = " << root->getValue() << std::endl;
	for (int ind = 0; ind < root->childrenSize(); ind++)
		save(root->getChild(ind), hight + 1, outfilename);
	outfilename << indent << "</" << root->getKey() << ">" << std::endl;
}

iterator tree::findKey(const std::string& tagName) {
	for (iterator itr = this->begin(), end = this->end(); itr != end; itr++)
		if (itr->getKey() == tagName)
			return itr;
	throw std::runtime_error("no key coincidence found");
}

iterator tree::findValue(const std::string& tagValue) {
	for (iterator itr = this->begin(), end = this->end(); itr != end; itr++)
		if (itr->getValue() == tagValue)
			return itr;
	throw std::runtime_error("no value coincidence found");
}

//iterator tree::add(const std::string& tagName, const std::string& tagValue, iterator& itr) {
//}
//
//bool tree::erase(iterator& itr) {
//}


void tree::print(std::shared_ptr<node> root, int hight) {
	if (root == nullptr) exit(1);
	for (int i = 0; i < hight; i++) std::cout << "\t";
	std::cout << root->getKey() << ":  value = " << root->getValue() << std::endl;
	for (int ind = 0; ind < root->childrenSize(); ind++) {
		print(root->getChild(ind), hight + 1);
	}
}

void save(std::shared_ptr<tree> tree, const std::string outfilename) {
	std::ofstream file(outfilename);
	if (!file)
		throw std::runtime_error("file opening error\n");
	if (!tree) {
		throw std::runtime_error("tree's empty\n");
	}
	file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
	tree->save(tree->getRoot(), 0, file);
	file.close();
}