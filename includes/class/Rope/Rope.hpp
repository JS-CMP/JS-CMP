#ifndef ROPE_HPP
#define ROPE_HPP

#include "RopeLeaf.hpp"
#include "RopeNode.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 * @class Rope
 * @brief Represents a rope, a data structure for efficiently manipulating and storing strings.
 */
class Rope {
public:
    /**
     * @name Constructors
     * These constructors create a new Rope object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the rope to a string. */
    explicit Rope(const std::string& str);
    /** @brief Default constructor initializes the rope to a u16string. */
    explicit Rope(const std::u16string& str);
    /** @brief Constructor for char* */
    explicit Rope(const char* str);
    /** @brief Constructor for char16_t* */
    explicit Rope(const char16_t* str);
    /** @brief Constructor for char */
    explicit Rope(std::shared_ptr<RopeNode> node);
    ///@}

    /**
     * @brief Returns the total length of the rope.
     * @return Length of the rope.
     */
    [[nodiscard]] size_t length() const;

    /**
     * @brief Gets the character at the specified index in the rope.
     * @param idx Index of the character.
     * @return Character at the given index.
     */
    [[nodiscard]] char16_t getCharAt(size_t idx) const;

    /**
     * @brief Concatenates another rope to this rope.
     * @param other The rope to be concatenated.
     */
    void concat(const Rope& other);

    /**
     * @brief Concatenation operator for two ropes.
     * @param other The other rope to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    Rope operator+(const Rope& other) const;

    /**
     * @brief Concatenation operator for a rope with a string.
     * @param other The string to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    Rope operator+(const std::u16string& other);

    /**
     * @brief Concatenation operator for a rope with a temporary string.
     * @param other The temporary string to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    Rope operator+(const std::u16string& other) const;
    /**
     * @brief Concatenation operator for a rope with a temporary string.
     * @param other The temporary string to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    Rope operator+(const std::u16string&& other) const;

    /**
     * @brief Friend function for concatenating a temporary string with a rope.
     * @param other The temporary string to concatenate.
     * @param rope The rope to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    friend Rope operator+(const std::u16string&& other, const Rope& rope);

    /**
     * @brief Friend function for concatenating a string with a rope.
     * @param other The string to concatenate.
     * @param rope The rope to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    friend Rope operator+(const std::u16string& other, const Rope& rope);

    /**
     * @brief Equality operator to check if two ropes are equal.
     * @param other The other rope to compare against.
     * @return Boolean indicating equality of ropes.
     */
    bool operator==(const Rope& other) const;

    /**
     * @brief Gets the character at the specified index using the subscript operator.
     * @param idx Index of the character.
     * @return Character at the given index.
     */
    [[nodiscard]] char16_t operator[](size_t idx) const;

    /**
     * @brief Finds the first occurrence of a substring in the rope.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the first occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] size_t find(const std::u16string& str, size_t pos = 0) const;

    /**
     * @brief Finds the last occurrence of a substring in the rope.
     * @param str The substring to search for.
     * @param pos The position to start searching from.
     * @return The index of the last occurrence of the substring, or npos if not found.
     */
    [[nodiscard]] size_t rfind(const std::u16string& str, size_t pos = std::u16string::npos) const;

    /**
     * @brief Compares this rope with another rope.
     * @param other The other rope to compare with.
     * @return An integer less than, equal to, or greater than zero.
     */
    [[nodiscard]] int compare(const Rope& other) const;

    /**
     * @brief Extracts a substring from the rope.
     * @param pos The starting position of the substring.
     * @param len The length of the substring.
     * @return A new Rope containing the substring.
     */
    [[nodiscard]] Rope substr(size_t pos, size_t len) const;

    /**
     * @brief Prints the content of the rope.
     */
    void print() const;

    /**
     * @brief Converts the rope to a string.
     * @return The string representation of the rope.
     */
    [[nodiscard]] std::u16string toString() const;

private:
    std::shared_ptr<RopeNode> root; /**< Root node of the rope structure. */
    std::u16string build;           /**< Cached string representation. */
    bool updated = false;           /**< Flag indicating if the rope has been updated. */

    /**
     * @brief Helper function to build the string representation from a RopeNode.
     * @param result The resulting string.
     * @param node The node being processed.
     */
    void toStringHelper(std::u16string& result, const std::shared_ptr<RopeNode>& node) const;

    /**
     * @brief Compares two nodes for equality.
     * @param node1 First node to compare.
     * @param node2 Second node to compare.
     * @return Boolean indicating equality of nodes.
     */
    [[nodiscard]] bool equals(const std::shared_ptr<RopeNode>& node1, const std::shared_ptr<RopeNode>& node2) const;

    /**
     * @brief Helper function to extract a substring from the rope.
     * @param node The current node being processed.
     * @param pos The starting position of the substring.
     * @param len The length of the substring.
     * @param pieces Vector to store the resulting pieces of the substring.
     */
    void substrHelper(const std::shared_ptr<RopeNode>& node, size_t pos, size_t len, std::vector<std::shared_ptr<RopeNode>>& pieces) const;
};

#endif // ROPE_HPP