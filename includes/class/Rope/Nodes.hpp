#include <iostream>
#include <memory>
#include <string>
#include <utility>

class RopeNode {
public:
    [[nodiscard]] virtual size_t length() const = 0;
    [[nodiscard]] virtual char getCharAt(size_t idx) const = 0;
    virtual void print() const = 0;
    virtual ~RopeNode() = default;
};

class RopeLeaf : public RopeNode {
    std::string data;
public:
    RopeLeaf(const std::string& str) : data(str) {}

    [[nodiscard]] size_t length() const override {
        return data.size();
    }

    [[nodiscard]] std::string getData() {
        return data;
    }

    [[nodiscard]] char getCharAt(size_t idx) const override {
        return data[idx];
    }

    void print() const override {
        std::cout << data;
    }
};

class RopeConcat : public RopeNode {
    std::shared_ptr<RopeNode> left;
    std::shared_ptr<RopeNode> right;
    size_t totalLength;

public:
    RopeConcat(std::shared_ptr<RopeNode> l, std::shared_ptr<RopeNode> r)
            : left(l), right(r), totalLength(l->length() + r->length()) {};

    RopeConcat(std::shared_ptr<RopeNode> l, const std::string& r) {
        left = std::move(l);
        right = std::make_shared<RopeLeaf>(r);
        totalLength = left->length() + right->length();
    }

    RopeConcat(const std::string& l, std::shared_ptr<RopeNode> r) {
        left = std::make_shared<RopeLeaf>(l);
        right = std::move(r);
        totalLength = left->length() + right->length();
    }

    [[nodiscard]] size_t length() const override {
        return totalLength;
    }

    [[nodiscard]] char getCharAt(size_t idx) const override {
        if (idx < left->length()) {
            return left->getCharAt(idx);
        } else {
            return right->getCharAt(idx - left->length());
        }
    }

    [[nodiscard]] std::shared_ptr<RopeNode> getLeft() {
        return left;
    }

    [[nodiscard]] std::shared_ptr<RopeNode> getRight() {
        return right;
    }

    void print() const override {
        left->print();
        right->print();
    }
};