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
     * @brief Gets the character at the specified index in the string.
     * @param idx Index of the character.
     * @return Character at the given index.
     */
    [[nodiscard]] char16_t getCharAt(size_t idx) const override;

    /**
     * @brief Finds the first occurrence of a substring in the string.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the first occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] size_t find(const std::u16string& str, size_t pos = 0) const override;

    /**
     * @brief Finds the last occurrence of a substring in the string.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the last occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] size_t rfind(const std::u16string& str, size_t pos = std::u16string::npos) const override;

    /**
     * @brief Returns the left child of the rope node.
     * @return Shared pointer to the left child node.
     */
    [[nodiscard]] std::shared_ptr<RopeNode> getLeft() const override;

    /**
     * @brief Returns the right child of the rope node.
     * @return Shared pointer to the right child node.
     */
    [[nodiscard]] std::shared_ptr<RopeNode> getRight() const override;

    /**
     * @return Pointer to the data stored in the leaf.
     */
    [[nodiscard]] const std::u16string* getDataPtr() const override;

    /**
     * @brief Prints the contents of the string stored in the leaf.
     */
    void print() const override;

private:
    std::u16string data; /**< The string data stored in this RopeLeaf. */
};

#endif // ROPELEAF_HPP