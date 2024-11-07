#include <class/Rope/RopeLeaf.hpp>
//#include "../../../includes/class/Rope/RopeLeaf.hpp" // when compiling with g++

RopeLeaf::RopeLeaf(const std::string& str) : data(str) {}

size_t RopeLeaf::length() const { return data.size(); }

std::string RopeLeaf::getData() { return data; }

char RopeLeaf::getCharAt(size_t idx) const { return data[idx]; }

void RopeLeaf::print() const { std::cout << data; }