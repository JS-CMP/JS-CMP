#include "Nodes.hpp"

class Rope {
    std::shared_ptr<RopeNode> root;
    std::string concatenatedString;
    bool updated = false;
public:
    explicit Rope(const std::string& str) {
        root = std::make_shared<RopeLeaf>(str);
    }
    explicit Rope (const char* str) {
        root = std::make_shared<RopeLeaf>(std::string(str));
    }
    explicit Rope(std::shared_ptr<RopeNode> node) : root(node) {}

    [[nodiscard]] size_t length() const {
        return root->length();
    }

    [[nodiscard]] char getCharAt(size_t idx) const {
        if (idx >= length()) {
            throw std::out_of_range("Index out of bounds");
        }
        return root->getCharAt(idx);
    }

    void concat(const Rope& other) {
        root = std::make_shared<RopeConcat>(root, other.root);
    }

    Rope operator+(const Rope& other) const {
        return Rope(std::make_shared<RopeConcat>(root, other.root));
    }

    Rope operator+(const std::string& other) {
        return Rope(std::make_shared<RopeConcat>(root, other));
    }

    Rope operator+(std::string&& other) const {
        return Rope(std::make_shared<RopeConcat>(root, other));
    }

    [[nodiscard]] Rope addLeft(const std::string &other) const {
        return Rope(std::make_shared<RopeConcat>(other, root));
    }

    [[nodiscard]] Rope addLeft(const std::string &&other) const {
        return Rope(std::make_shared<RopeConcat>(other, root));
    }

    bool operator==(const Rope& other) const {
        return equals(this->root, other.root);
    }

    void print() const {
        root->print();
        std::cout << std::endl;
    }

    // TODO: uncomment the line and deal with the fact that std::get return a const pointer and cant call a methods that is not const
    std::string toString() const{
        if (updated)
            return concatenatedString;

        std::string result;
        toStringHelper(result, root);
//        concatenatedString = result;
//        updated = true;
        return result;
    }
private:
    void toStringHelper(std::string& result, const std::shared_ptr<RopeNode>& node) const {
        if (auto leaf = std::dynamic_pointer_cast<RopeLeaf>(node)) {
            result += leaf->getData();
        } else if (auto concat = std::dynamic_pointer_cast<RopeConcat>(node)) {
            toStringHelper(result, concat->getLeft());
            toStringHelper(result, concat->getRight());
        }
    }

    [[nodiscard]] bool equals(const std::shared_ptr<RopeNode>& node1, const std::shared_ptr<RopeNode>& node2) const {
        if (!node1 && !node2) {
            return true;
        }

        if (!node1 || !node2) {
            return false;
        }

        // If both are leaf nodes, compare their data
        if (auto leaf1 = std::dynamic_pointer_cast<RopeLeaf>(node1)) {
            if (auto leaf2 = std::dynamic_pointer_cast<RopeLeaf>(node2)) {
                return leaf1->getData() == leaf2->getData();
            } else {
                return false;
            }
        }

        // If both are concatenation nodes, recursively compare their children
        if (auto concat1 = std::dynamic_pointer_cast<RopeConcat>(node1)) {
            if (auto concat2 = std::dynamic_pointer_cast<RopeConcat>(node2)) {
                return equals(concat1->getLeft(), concat2->getLeft()) &&
                       equals(concat1->getRight(), concat2->getRight());
            } else {
                return false;
            }
        }

        return false;
    }
};