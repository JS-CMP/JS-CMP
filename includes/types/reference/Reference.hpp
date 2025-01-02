//
// Created by Simon BANDIERA on 28/12/2024.
//

#ifndef JS_CMP_REFERENCE_HPP
#define JS_CMP_REFERENCE_HPP

#include <types/JsAny.hpp>
#include "../../../lib/class/Helper.hpp"

namespace JS {
    class Reference {
        private:
            Reference(const JS::Value& base, const std::string& reference, bool strict);
            Reference(Reference& reference);
            ~Reference() = default;

            JS::Value getBase() const;
            std::string getReference() const;
            bool isStrict() const;
            bool hasPrimitiveBase() const;
            bool isPropertyReference() const;
            bool isUnresolvableReference() const;

            JS::Value getValue() const;
            void putValue(const JS::Value& value);
        private:
            JS::Value base;
            std::string reference;
            bool strict;
    };
}


#endif //JS_CMP_REFERENCE_HPP
