#ifndef ROPE_HPP
#define ROPE_HPP

#include "RopeConcat.hpp"
#include "RopeLeaf.hpp"
#include "RopeNode.hpp"

class Rope {
public:
    explicit Rope(const std::string& str);
    explicit Rope(const char* str);
    explicit Rope(std::shared_ptr<RopeNode> node);

    [[nodiscard]] size_t length() const;

    [[nodiscard]] char getCharAt(size_t idx) const;

    [[nodiscard]] int compare(const Rope& other) const;
    void concat(const Rope& other);
    Rope operator+(const Rope& other) const;
    Rope operator+(const std::string& other) const ;
    Rope operator+(const std::string&& other) const;

    friend Rope operator+(const std::string&& other, const Rope& rope);
    friend Rope operator+(const std::string& other, const Rope& rope);

    bool operator==(const Rope& other) const;
    void print() const;

    [[nodiscard]] std::string toString() const;

private:
    std::shared_ptr<RopeNode> root;
    std::string build;
    bool updated = false;
    void toStringHelper(std::string& result, const std::shared_ptr<RopeNode>& node) const;

    [[nodiscard]] bool equals(const std::shared_ptr<RopeNode>& node1, const std::shared_ptr<RopeNode>& node2) const;
};

#endif // ROPE_HPP