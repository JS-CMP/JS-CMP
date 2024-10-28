// RopeConcat.hpp
#ifndef ROPECONCAT_HPP
#define ROPECONCAT_HPP

#include "RopeNode.hpp"
#include "RopeLeaf.hpp"
#include <memory>
#include <string>

class RopeConcat : public RopeNode {
public:
    RopeConcat(std::shared_ptr<RopeNode> l, std::shared_ptr<RopeNode> r);
    RopeConcat(std::shared_ptr<RopeNode> l, const std::string& r);
    RopeConcat(const std::string& l, std::shared_ptr<RopeNode> r);

    [[nodiscard]] size_t length() const override;
    [[nodiscard]] char getCharAt(size_t idx) const override;
    [[nodiscard]] std::shared_ptr<RopeNode> getLeft();
    [[nodiscard]] std::shared_ptr<RopeNode> getRight();
    void print() const override;
private:
    std::shared_ptr<RopeNode> left;
    std::shared_ptr<RopeNode> right;
    size_t totalLength;
};

#endif // ROPECONCAT_HPP
