#include <class/Rope/Rope.hpp>
#include <class/Rope/RopeConcat.hpp>
#include <class/Rope/RopeIterator.hpp>
#include <utils/Convert.hpp>

Rope::Rope(const std::string& str) : root(std::make_shared<RopeLeaf>(JS::CONVERT::ToUtf16(str))) {}

Rope::Rope(const std::u16string& str) : root(std::make_shared<RopeLeaf>(str)) {}

Rope::Rope(const char16_t* str) : root(std::make_shared<RopeLeaf>(std::u16string(str))) {}

Rope::Rope(const char* str) : root(std::make_shared<RopeLeaf>(JS::CONVERT::ToUtf16(str))) {}

Rope::Rope(std::shared_ptr<RopeNode> node) : root(std::move(node)) {}

size_t Rope::length() const {
    return root->length();
}

char16_t Rope::getCharAt(size_t idx) const {
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
Rope Rope::operator+(const std::u16string& other) {
    return Rope(std::make_shared<RopeConcat>(root, other));
}

Rope Rope::operator+(const std::u16string& other) const {
    return Rope(std::make_shared<RopeConcat>(root, other));
}

Rope Rope::operator+(const std::u16string&& other) const {
    return Rope(std::make_shared<RopeConcat>(root, other));
}

Rope operator+(const std::u16string&& other, const Rope& rope) {
    return Rope(std::make_shared<RopeConcat>(other, rope.root));
}

Rope operator+(const std::u16string& other, const Rope& rope) {
    return Rope(std::make_shared<RopeConcat>(other, rope.root));
}

bool Rope::operator==(const Rope& other) const {
    return equals(this->root, other.root);
}

char16_t Rope::operator[](size_t idx) const {
    if (idx >= length()) {
        throw std::out_of_range("Index out of bounds");
    }
    return root->getCharAt(idx);
}

size_t Rope::find(const std::u16string& str, size_t pos) const {
    return root->find(str, pos);
}

size_t Rope::rfind(const std::u16string& str, size_t pos) const {
    return root->rfind(str, pos);
}

int Rope::compare(const Rope& other) const {
    RopeIterator it1(this->root);
    RopeIterator it2(other.root);

    while (it1.hasNext() && it2.hasNext()) {
        char16_t c1 = it1.next();
        char16_t c2 = it2.next();

        if (c1 != c2) {
            return (c1 < c2) ? -1 : 1;
        }
    }
    if (it1.hasNext()) {
        return 1;
    }
    if (it2.hasNext()) {
        return -1;
    }
    return 0;
}

void Rope::substrHelper(const std::shared_ptr<RopeNode>& node, size_t pos, size_t len,
                        std::vector<std::shared_ptr<RopeNode>>& pieces) const {
    if (!node || len == 0) {
        return;
    }

    if (auto left = node->getLeft()) {
        size_t leftLen = left->length();

        if (pos < leftLen) {
            size_t takeLen = std::min(len, leftLen - pos);
            substrHelper(left, pos, takeLen, pieces);
            len -= takeLen;
            pos = 0;
        } else {
            pos -= leftLen;
        }

        if (len > 0) {
            auto right = node->getRight();
            substrHelper(right, pos, len, pieces);
        }
    } else {
        const std::u16string* data = node->getDataPtr();
        if (!data) {
            return;
        }

        size_t available = data->size();
        if (pos >= available) {
            return;
        }

        size_t takeLen = std::min(len, available - pos);
        auto substrData = std::make_shared<RopeLeaf>(data->substr(pos, takeLen));
        pieces.push_back(substrData);
    }
}

Rope Rope::substr(size_t pos, size_t len) const {
    if (!root || pos >= length() || len == 0) {
        return Rope(u"");
    }

    if (pos + len > length()) {
        len = length() - pos;
    }

    std::vector<std::shared_ptr<RopeNode>> pieces;
    substrHelper(root, pos, len, pieces);

    if (pieces.empty()) {
        return Rope(u"");
    }

    std::shared_ptr<RopeNode> newRoot = pieces[0];
    for (size_t i = 1; i < pieces.size(); ++i) {
        newRoot = std::make_shared<RopeConcat>(newRoot, pieces[i]);
    }

    return Rope(newRoot);
}

void Rope::print() const {
    root->print();
    std::cout << '\n';
}

std::u16string Rope::toString() const {
    if (updated) {
        return build;
    }
    std::u16string result;
    toStringHelper(result, root);
    return result;
}

void Rope::toStringHelper(std::u16string& result, const std::shared_ptr<RopeNode>& node) const {
    if (auto leaf = std::dynamic_pointer_cast<RopeLeaf>(node)) {
        result += leaf->getData();
    } else if (auto concat = std::dynamic_pointer_cast<RopeConcat>(node)) {
        toStringHelper(result, concat->getLeft());
        toStringHelper(result, concat->getRight());
    }
}

// TODO: to change it to a while because a recursive can stack overflow
bool Rope::equals(const std::shared_ptr<RopeNode>& node1, const std::shared_ptr<RopeNode>& node2) const {
    if (!node1 && !node2) {
        return true;
    }
    if (!node1 || !node2) {
        return false;
    }

    if (node1 && node2) {
        return (*node1->getDataPtr()) == (*node2->getDataPtr());
    }

    if (node1 && node2) {
        return equals(node1->getLeft(), node2->getLeft()) && equals(node1->getRight(), node2->getRight());
    }
    return false;
}