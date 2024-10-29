// RopeNode.hpp
#ifndef ROPENODE_HPP
#define ROPENODE_HPP

#include <cstddef>

class RopeNode {
public:
    [[nodiscard]] virtual size_t length() const = 0;

    [[nodiscard]] virtual char getCharAt(size_t idx) const = 0;
    virtual void print() const = 0;

    virtual ~RopeNode() = default;
};

#endif // ROPENODE_HPP