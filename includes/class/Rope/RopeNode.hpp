// RopeNode.hpp
#ifndef ROPENODE_HPP
#define ROPENODE_HPP

#include <cstddef>

/**
 * @class RopeNode
 * @brief Abstract base class representing a node in a Rope data structure.
 *
 * Provides an interface for the operations that can be performed on a RopeNode.
 */
class RopeNode {
public:
    /**
     * @brief Returns the length of the rope node.
     * @return Size of the rope node.
     */
    [[nodiscard]] virtual size_t length() const = 0;

    /**
     * @brief Gets the character at the specified index in the rope node.
     * @param idx Index of the character.
     * @return Character at the given index.
     */
    [[nodiscard]] virtual char getCharAt(size_t idx) const = 0;

    /**
     * @brief Prints the contents of the rope node.
     */
    virtual void print() const = 0;

    /**
     * @brief Virtual destructor for RopeNode.
     */
    virtual ~RopeNode() = default;
};

#endif // ROPENODE_HPP