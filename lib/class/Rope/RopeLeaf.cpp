#include <class/Rope/RopeLeaf.hpp>
#include <utils/Convert.hpp>

RopeLeaf::RopeLeaf(const std::u16string& str) : data(str) {}

size_t RopeLeaf::length() const {
    return data.size();
}

char16_t RopeLeaf::getCharAt(size_t idx) const {
    return data[idx];
}

size_t RopeLeaf::find(const std::u16string& str, size_t pos) const {
    return data.find(str, pos);
}

size_t RopeLeaf::rfind(const std::u16string& str, size_t pos) const {
    if (pos >= data.size()) {
        pos = data.size() - 1;
    }
    return data.rfind(str, pos);
}

std::u16string RopeLeaf::getData() {
    return data;
}

std::shared_ptr<RopeNode> RopeLeaf::getLeft() const {
    return nullptr;
}
std::shared_ptr<RopeNode> RopeLeaf::getRight() const {
    return nullptr;
}
const std::u16string* RopeLeaf::getDataPtr() const {
    return &data;
}

void RopeLeaf::print() const {
    std::cout << JS::CONVERT::ToUtf8(data);
}