#include <class/Rope/RopeConcat.hpp>

RopeConcat::RopeConcat(std::shared_ptr<RopeNode> l, std::shared_ptr<RopeNode> r)
    : left(std::move(l)), right(std::move(r)), totalLength(left->length() + right->length()) {}

RopeConcat::RopeConcat(std::shared_ptr<RopeNode> l, const std::u16string& r)
    : left(std::move(l)), right(std::make_shared<RopeLeaf>(r)), totalLength(left->length() + right->length()) {}

RopeConcat::RopeConcat(const std::u16string& l, std::shared_ptr<RopeNode> r)
    : left(std::make_shared<RopeLeaf>(l)), right(std::move(r)), totalLength(left->length() + right->length()) {}

size_t RopeConcat::length() const { return totalLength; }

char16_t RopeConcat::getCharAt(size_t idx) const {
    if (idx < left->length()) {
        return left->getCharAt(idx);
    } else {
        return right->getCharAt(idx - left->length());
    }
}

std::shared_ptr<RopeNode> RopeConcat::getLeft() { return left; }

std::shared_ptr<RopeNode> RopeConcat::getRight() { return right; }
const std::u16string* RopeConcat::getDataPtr() const { return nullptr; }

size_t RopeConcat::find(const std::u16string& pattern, size_t pos) const {
    size_t leftLen = left->length();
    size_t rightLen = right->length();
    size_t patLen = pattern.length();

    if (pos >= leftLen + rightLen) {
        return std::u16string::npos;
    }

    if (pos < leftLen) {
        size_t foundInLeft = left->find(pattern, pos);
        if (foundInLeft != std::u16string::npos) {
            return foundInLeft;
        }
    }

    if (patLen > 1 && leftLen >= pos) {
        size_t overlapLen = patLen - 1;
        size_t leftOverlapStart = (leftLen > overlapLen) ? (leftLen - overlapLen) : 0;
        size_t rightOverlapSize = std::min(overlapLen, rightLen);

        std::u16string leftPart, rightPart;
        for (size_t i = leftOverlapStart; i < leftLen; ++i) {
            leftPart.push_back(left->getCharAt(i));
        }
        for (size_t i = 0; i < rightOverlapSize; ++i) {
            rightPart.push_back(right->getCharAt(i));
        }

        std::u16string boundary = leftPart + rightPart;

        size_t boundaryFind = boundary.find(pattern);
        if (boundaryFind != std::u16string::npos) {
            return leftOverlapStart + boundaryFind;
        }
    }

    if (pos > leftLen) {
        size_t foundInRight = right->find(pattern, pos > leftLen ? pos - leftLen : 0);
        if (foundInRight != std::u16string::npos) {
            return leftLen + foundInRight;
        }
    }

    return std::u16string::npos;
}

size_t RopeConcat::rfind(const std::u16string& str, size_t pos) const {
    if (str.empty()) {
        return std::u16string::npos;
    }
    if (pos > totalLength) {
        pos = totalLength;
    }

    const size_t leftLen = left->length();
    const size_t rightLen = right->length();

    if (pos > totalLength - str.size()) {
        pos = totalLength - str.size();
    }

    if (pos < leftLen) {
        size_t found = left->rfind(str, pos);
        if (found != std::u16string::npos) {
            return found;
        }
        return std::u16string::npos;
    }

    size_t rightSearchPos = (pos >= leftLen) ? (pos - leftLen) : rightLen;
    size_t foundRight = right->rfind(str, rightSearchPos);
    if (foundRight != std::u16string::npos) {
        return leftLen + foundRight;
    }

    size_t overlapLen = std::min(str.size() - 1, std::min(leftLen, rightLen));

    if (overlapLen > 0) {
        size_t leftOverlapStart = leftLen - overlapLen;
        std::u16string leftPart;
        for (size_t i = leftOverlapStart; i < leftLen; ++i) {
            leftPart.push_back(left->getCharAt(i));
        }

        std::u16string rightPart;
        for (size_t i = 0; i < overlapLen; ++i) {
            rightPart.push_back(right->getCharAt(i));
        }

        std::u16string overlapStr = leftPart + rightPart;

        size_t foundOverlap = overlapStr.rfind(str);
        if (foundOverlap != std::u16string::npos) {
            size_t ropeIndex = leftOverlapStart + foundOverlap;
            if (ropeIndex <= pos) {
                return ropeIndex;
            }
        }
    }

    size_t leftSearchPos = std::min(pos, leftLen - 1);
    size_t foundLeft = left->rfind(str, leftSearchPos);
    return foundLeft;
}

void RopeConcat::print() const {
    left->print();
    right->print();
}