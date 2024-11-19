#ifndef ROPE_HPP
#define ROPE_HPP

#include "RopeConcat.hpp"
#include "RopeLeaf.hpp"
#include "RopeNode.hpp"

#include <memory>
#include <string>

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
    /** @brief Default constructor initializes the rope to an empty string. */
    explicit Rope(const std::string& str);
    /** @brief Constructor for char* */
    explicit Rope(const char* str);
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
    [[nodiscard]] char getCharAt(size_t idx) const;

    /**
     * @brief Compares this rope with another rope.
     * @param other The other rope to compare with.
     * @return An integer less than, equal to, or greater than zero.
     */
    [[nodiscard]] int compare(const Rope& other) const;

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
    Rope operator+(const std::string& other);

    /**
     * @brief Concatenation operator for a rope with a temporary string.
     * @param other The temporary string to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    Rope operator+(const std::string& other) const;
    Rope operator+(const std::string&& other) const;

    /**
     * @brief Friend function for concatenating a temporary string with a rope.
     * @param other The temporary string to concatenate.
     * @param rope The rope to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    friend Rope operator+(const std::string&& other, const Rope& rope);

    /**
     * @brief Friend function for concatenating a string with a rope.
     * @param other The string to concatenate.
     * @param rope The rope to concatenate.
     * @return New Rope which is the result of the concatenation.
     */
    friend Rope operator+(const std::string& other, const Rope& rope);

    /**
     * @brief Equality operator to check if two ropes are equal.
     * @param other The other rope to compare against.
     * @return Boolean indicating equality of ropes.
     */
    bool operator==(const Rope& other) const;

    /**
     * @brief Prints the content of the rope.
     */
    void print() const;

    /**
     * @brief Converts the rope to a string.
     * @return The string representation of the rope.
     */
    [[nodiscard]] std::string toString() const;

private:
    std::shared_ptr<RopeNode> root; /**< Root node of the rope structure. */
    std::string build;              /**< Cached string representation. */
    bool updated = false;           /**< Flag indicating if the rope has been updated. */

    /**
     * @brief Helper function to build the string representation from a RopeNode.
     * @param result The resulting string.
     * @param node The node being processed.
     */
    void toStringHelper(std::string& result, const std::shared_ptr<RopeNode>& node) const;

    /**
     * @brief Compares two nodes for equality.
     * @param node1 First node to compare.
     * @param node2 Second node to compare.
     * @return Boolean indicating equality of nodes.
     */
    [[nodiscard]] bool equals(const std::shared_ptr<RopeNode>& node1, const std::shared_ptr<RopeNode>& node2) const;
};

#endif // ROPE_HPP