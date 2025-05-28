// RopeNode.hpp
#ifndef ROPENODE_HPP
#define ROPENODE_HPP

#include <cstddef>
#include <memory>
#include <string>

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
    [[nodiscard]] virtual char16_t getCharAt(size_t idx) const = 0;

    /**
     * @brief Finds the first occurrence of a substring in the rope node.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the first occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] virtual size_t find(const std::u16string& str, size_t pos = 0) const = 0;

    /**
     * @brief Finds the last occurrence of a substring in the rope node.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the last occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] virtual size_t rfind(const std::u16string& str, size_t pos = std::u16string::npos) const = 0;

    /**
     * @brief Returns the left child of the rope node.
     */
    [[nodiscard]] virtual std::shared_ptr<RopeNode> getLeft() const {
        return nullptr; // Default implementation returns nullptr, can be overridden
    }
    /**
     * @brief Returns the right child of the rope node.
     */
    [[nodiscard]] virtual std::shared_ptr<RopeNode> getRight() const {
        return nullptr; // Default implementation returns nullptr, can be overridden
    }

    /**
     * @brief Returns a pointer to the data stored in the rope node.
     * @return Pointer to the data.
     */
    [[nodiscard]] virtual const std::u16string* getDataPtr() const {
        return nullptr; // Default implementation returns nullptr, can be overridden
    };


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