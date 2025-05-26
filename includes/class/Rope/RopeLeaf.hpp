// RopeLeaf.hpp
#ifndef ROPELEAF_HPP
#define ROPELEAF_HPP

#include "RopeNode.hpp"

#include <iostream>
#include <string>

/**
 * @class RopeLeaf
 * @brief Concrete class representing a leaf node in a Rope data structure.
 *
 * Stores a string and implements the operations for a leaf node.
 */
class RopeLeaf : public RopeNode {
public:
    /**
     * @brief Constructs a RopeLeaf with the given string data.
     * @param str The string to be stored in the leaf.
     */
    explicit RopeLeaf(const std::u16string& str);

    /**
     * @brief Returns the length of the string stored in the leaf.
     * @return Size of the string.
     */
    [[nodiscard]] size_t length() const override;

    /**
     * @brief Returns the string data stored in the leaf.
     * @return The string data.
     */
    [[nodiscard]] std::u16string getData();

    /**
     * @brief Gets the character at the specified index in the string.
     * @param idx Index of the character.
     * @return Character at the given index.
     */
    [[nodiscard]] char getCharAt(size_t idx) const override;

    /**
     * @brief Prints the contents of the string stored in the leaf.
     */
    void print() const override;

private:
    std::u16string data; /**< The string data stored in this RopeLeaf. */
};

#endif // ROPELEAF_HPP