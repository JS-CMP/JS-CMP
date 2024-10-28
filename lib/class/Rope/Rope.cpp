#include <Rope/Rope.hpp>

Rope::Rope(const std::string& str) : root(std::make_shared<RopeLeaf>(str)) {}

Rope::Rope(const char* str) : root(std::make_shared<RopeLeaf>(std::string(str))) {}

Rope::Rope(std::shared_ptr<RopeNode> node) : root(node) {}

size_t Rope::length() const {
    return root->length();
}

char Rope::getCharAt(size_t idx) const {
    if (idx >= length()) {
        throw std::out_of_range("Index out of bounds");
    }
    return root->getCharAt(idx);
}

void Rope::concat(const Rope& other) {
    root = std::make_shared<RopeConcat>(root, other.root);
}

Rope Rope::operator+(const Rope& other) const {
    return Rope(std::make_shared<RopeConcat>(root, other.root));
}

Rope Rope::operator+(const std::string& other) {
    return Rope(std::make_shared<RopeConcat>(root, other));
}

Rope Rope::operator+(std::string&& other) const {
    return Rope(std::make_shared<RopeConcat>(root, other));
}

Rope operator+(const std::string&& other, const Rope& rope) {
    return Rope(std::make_shared<RopeConcat>(other, rope.root));
}

Rope operator+(const std::string& other, const Rope& rope) {
    return Rope(std::make_shared<RopeConcat>(other, rope.root));
}

bool Rope::operator==(const Rope& other) const {
    return equals(this->root, other.root);
}

int Rope::compare(const Rope& other) const {
    return equals(this->root, other.root) ? 1 : -1;
}

void Rope::print() const {
    root->print();
    std::cout << std::endl;
}

std::string Rope::toString() const {
    if (updated)
        return build;

    std::string result;
    toStringHelper(result, root);
    return result;
}

void Rope::toStringHelper(std::string& result, const std::shared_ptr<RopeNode>& node) const {
    if (auto leaf = std::dynamic_pointer_cast<RopeLeaf>(node)) {
        result += leaf->getData();
    } else if (auto concat = std::dynamic_pointer_cast<RopeConcat>(node)) {
        toStringHelper(result, concat->getLeft());
        toStringHelper(result, concat->getRight());
    }
}

bool Rope::equals(const std::shared_ptr<RopeNode>& node1, const std::shared_ptr<RopeNode>& node2) const {
    if (!node1 && !node2) {
        return true;
    }
    if (!node1 || !node2) {
        return false;
    }

    auto leaf1 = std::dynamic_pointer_cast<RopeLeaf>(node1);
    auto leaf2 = std::dynamic_pointer_cast<RopeLeaf>(node2);
    if (leaf1 && leaf2) {
        return leaf1->getData() == leaf2->getData();
    }

    auto concat1 = std::dynamic_pointer_cast<RopeConcat>(node1);
    auto concat2 = std::dynamic_pointer_cast<RopeConcat>(node2);
    if (concat1 && concat2) {
        return equals(concat1->getLeft(), concat2->getLeft()) &&
               equals(concat1->getRight(), concat2->getRight());
    }

    return false;
}