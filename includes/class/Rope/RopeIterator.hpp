#ifndef ROPEITERATOR_HPP
#define ROPEITERATOR_HPP

#include <memory>
#include <stack>

class RopeNode;

class RopeIterator {
public:
    /**
     * @brief Constructs a RopeIterator for the given root node.
     * @param root The root node of the rope to iterate over.
     */
    explicit RopeIterator(const std::shared_ptr<RopeNode>& root);

    /**
     * @brief Checks if there are more characters to iterate over.
     * @return True if there are more characters, false otherwise.
     */
    [[nodiscard]] bool hasNext() const;
    /**
     * @brief Returns the next character in the rope.
     * @return The next character and 0 if there are no more characters.
     */
    char16_t next();

private:
    std::stack<std::shared_ptr<RopeNode>> nodeStack; /** Stack to hold nodes during iteration. */
    const std::u16string* currentData = nullptr;     /** Pointer to the current data being iterated over. */
    size_t currentIndex = 0;                         /** Current index in the current data. */

    /**
     * @brief Pushes all left nodes onto the stack starting from the given node.
     * @param node The node to start pushing left nodes from.
     */
    void pushLeftNodes(const std::shared_ptr<RopeNode>& node);
};

#endif // ROPEITERATOR_HPP
