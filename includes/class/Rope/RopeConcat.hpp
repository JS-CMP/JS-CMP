// RopeConcat.hpp
#ifndef ROPECONCAT_HPP
#define ROPECONCAT_HPP

#include "RopeLeaf.hpp"
#include "RopeNode.hpp"

#include <memory>
#include <string>

/**
 * @class RopeConcat
 * @brief Represents a concatenation node in a Rope data structure.
 *
 * Manages two child nodes, allowing concatenation of ropes.
 */
class RopeConcat : public RopeNode {
public:
    /**
     * @brief Constructs a RopeConcat from two RopeNode shared pointers.
     * @param l Shared pointer to the left rope node.
     * @param r Shared pointer to the right rope node.
     */
    RopeConcat(std::shared_ptr<RopeNode> l, std::shared_ptr<RopeNode> r);

    /**
     * @brief Constructs a RopeConcat from a RopeNode and a string.
     * @param l Shared pointer to the left rope node.
     * @param r The right string to concatenate.
     */
    RopeConcat(std::shared_ptr<RopeNode> l, const std::u16string& r);

    /**
     * @brief Constructs a RopeConcat from a string and a RopeNode.
     * @param l The left string to concatenate.
     * @param r Shared pointer to the right rope node.
     */
    RopeConcat(const std::u16string& l, std::shared_ptr<RopeNode> r);

    /**
     * @brief Returns the total length of the concatenated nodes.
     * @return Combined size of both nodes.
     */
    [[nodiscard]] size_t length() const override;

    /**
     * @brief Gets the character at the specified index across concatenated nodes.
     * @param idx Index of the character.
     * @return Character at the given index.
     */
    [[nodiscard]] char16_t getCharAt(size_t idx) const override;

    /**
     * @brief Returns the left child node.
     * @return Shared pointer to the left rope node.
     */
    [[nodiscard]] std::shared_ptr<RopeNode> getLeft();

    /**
     * @brief Returns the right child node.
     * @return Shared pointer to the right rope node.
     */
    [[nodiscard]] std::shared_ptr<RopeNode> getRight();

    /**
     * @return Pointer to the data stored in the leaf.
     */
    [[nodiscard]] const std::u16string* getDataPtr() const override;

    /**
     * @brief Finds the first occurrence of a substring in the concatenated nodes.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the first occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] size_t find(const std::u16string& str, size_t pos = 0) const override;

    /**
     * @brief Finds the last occurrence of a substring in the concatenated nodes.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the last occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] size_t rfind(const std::u16string& str, size_t pos = std::u16string::npos) const override;

    /**
     * @brief Prints the concatenated string by combining both child nodes.
     */
    void print() const override;

private:
    std::shared_ptr<RopeNode> left;  /**< Left child node. */
    std::shared_ptr<RopeNode> right; /**< Right child node. */
    size_t totalLength;              /**< Cached total length of the concatenated nodes. */
};

#endif // ROPECONCAT_HPP