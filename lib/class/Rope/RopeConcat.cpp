#include <class/Rope/RopeConcat.hpp>
//#include "../../../includes/class/Rope/RopeConcat.hpp" // when compiling with g++

RopeConcat::RopeConcat(std::shared_ptr<RopeNode> l, std::shared_ptr<RopeNode> r)
    : left(std::move(l)), right(std::move(r)), totalLength(left->length() + right->length()) {}

RopeConcat::RopeConcat(std::shared_ptr<RopeNode> l, const std::string& r)
    : left(std::move(l)), right(std::make_shared<RopeLeaf>(r)), totalLength(left->length() + right->length()) {}

RopeConcat::RopeConcat(const std::string& l, std::shared_ptr<RopeNode> r)
    : left(std::make_shared<RopeLeaf>(l)), right(std::move(r)), totalLength(left->length() + right->length()) {}

size_t RopeConcat::length() const { return totalLength; }

char RopeConcat::getCharAt(size_t idx) const {
    if (idx < left->length()) {
        return left->getCharAt(idx);
    } else {
        return right->getCharAt(idx - left->length());
    }
}

std::shared_ptr<RopeNode> RopeConcat::getLeft() { return left; }

std::shared_ptr<RopeNode> RopeConcat::getRight() { return right; }

void RopeConcat::print() const {
    left->print();
    right->print();
}