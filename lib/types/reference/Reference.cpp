//
// Created by Simon BANDIERA on 28/12/2024.
//

#include <types/reference/Reference.hpp>

JS::Reference::Reference(const JS::Value& base, const std::string& reference, bool strict) {
    this->base = base;
    this->reference = reference;
    this->strict = strict;
}

JS::Value JS::Reference::getBase() const {
    return this->base;
}

std::string JS::Reference::getReference() const {
    return this->reference;
}

bool JS::Reference::isStrict() const {
    return this->strict;
}

bool JS::Reference::hasPrimitiveBase() const {
    auto type = this->base.index();
    return type == JS::NUMBER || type == JS::STRING || type == JS::BOOL;
}

bool JS::Reference::isPropertyReference() const {
    return this->hasPrimitiveBase() || this->base.index() == JS::OBJECT;
}

bool JS::Reference::isUnresolvableReference() const {
    return this->base.index() == JS::UNDEFINED;
}

JS::Value JS::Reference::getValue() const {
    // TODO : check [[Get]] when object is a done
    if (this->isUnresolvableReference()) {
        throw std::runtime_error("ReferenceError: Cannot access '" + this->reference + "' before initialization");
    }
    if (this->isPropertyReference()) {
        if (!this->hasPrimitiveBase()) {
            return this->base[this->reference];
        }
        return this->base;
    }
    return this->base[this->reference];
}

void JS::Reference::putValue(const JS::Value& value) {
    // TODO : check [[Put]] when object is a done
    if (this->isUnresolvableReference()) {
        throw std::runtime_error("ReferenceError: Cannot access '" + this->reference + "' before initialization");
    }
    if (this->isPropertyReference()) {
        if (!this->hasPrimitiveBase()) {
            this->base[this->reference] = value;
            return;
        }
        throw std::runtime_error("TypeError: Cannot assign to read only property '" + this->reference + "' of object");
    }
    this->base[this->reference] = value;
}