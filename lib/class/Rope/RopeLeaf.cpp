#include <class/Rope/RopeLeaf.hpp>
#include <utils/Convert.hpp>

RopeLeaf::RopeLeaf(const std::u16string& str) : data(str) {}

size_t RopeLeaf::length() const { return data.size(); }

std::u16string RopeLeaf::getData() { return data; }

char RopeLeaf::getCharAt(size_t idx) const { return data[idx]; }

void RopeLeaf::print() const { std::cout << JS::CONVERT::ToUtf8(data); }