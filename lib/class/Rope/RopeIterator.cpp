#include "class/Rope/RopeIterator.hpp"
#include "class/Rope/RopeNode.hpp"

RopeIterator::RopeIterator(const std::shared_ptr<RopeNode>& root)  {
    pushLeftNodes(root);
    currentIndex = 0;
}

bool RopeIterator::hasNext() const {
    return !nodeStack.empty() || (currentData && currentIndex < currentData->size());
}

char16_t RopeIterator::next() {
    if (!currentData || currentIndex >= currentData->size()) {
        if (nodeStack.empty()) {
            return 0;
        }
        auto node = nodeStack.top();
        nodeStack.pop();

        auto right = node->getRight();
        if (right) {
        pushLeftNodes(right);
        }

        auto left = node->getLeft();
        if (left) {
        pushLeftNodes(left);
}
        return next();
    }

    return (*currentData)[currentIndex++];
}

void RopeIterator::pushLeftNodes(const std::shared_ptr<RopeNode>& node)  {
    if (!node) return;

    if (node->getLeft() && node->getRight()) {
        nodeStack.push(node);
        pushLeftNodes(node->getLeft());
    } else {
        currentData = node->getDataPtr();
        currentIndex = 0;
    }
}