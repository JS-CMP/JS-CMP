// RopeLeaf.hpp
#ifndef ROPELEAF_HPP
#define ROPELEAF_HPP

#include "RopeNode.hpp"

#include <iostream>
#include <string>

class RopeLeaf : public RopeNode {
public:
    explicit RopeLeaf(const std::string& str);

    [[nodiscard]] size_t length() const override;

    [[nodiscard]] std::string getData();

    [[nodiscard]] char getCharAt(size_t idx) const override;
    void print() const override;

private:
    std::string data;
};

#endif // ROPELEAF_HPP