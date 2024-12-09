//
// Created by Simon BANDIERA on 24/11/2024.
//

#ifndef JS_CMP_ASSERT_HPP
#define JS_CMP_ASSERT_HPP

#include "types/objects/JsObject.hpp"
#include "types/objects/JsFunction.hpp"
#include "exceptions/TypeError.hpp"
#include "exceptions/AssertionError.hpp"
#include "../lib/class/Helper.hpp"
#include <cmath>

/** List of assertion to do (inverse of thoses function are also to do)
- [x] assert.equal(actual, expected[, message])
- [x] assert.strictEqual(actual, expected[, message])
- [ ] assert.deepEqual(actual, expected[, message])
- [ ] assert.deepStrictEqual(actual, expected[, message])
- [ ] assert.doesNotMatch(string, regexp[, message])
- [ ] assert.doesNotReject(asyncFn[, error][, message])
- [ ] assert.doesNotThrow(fn[, error][, message])
- [ ] assert.fail([message])
- [ ] assert.fail(actual, expected[, message[, operator[, stackStartFn]]])
- [ ] assert.ifError(value)
- [ ] assert.ok(value[, message])
- [ ] assert.rejects(asyncFn[, error][, message])
- [ ] assert.throws(fn[, error][, message])
*/

class Assert : public JS::Object {
public:
    Assert();
    static JS::Any equal(const std::vector<JS::Any>& args);
    static JS::Any notEqual(const std::vector<JS::Any>& args);
    static JS::Any strictEqual(const std::vector<JS::Any>& args);
    static JS::Any notStrictEqual(const std::vector<JS::Any>& args);
    static JS::Any deepEqual(const std::vector<JS::Any>& args);
    static JS::Any notDeepEqual(const std::vector<JS::Any>& args);
private:
    // TODO: add handling stackStartFn
    static void innerFail(const JS::Any& actual, const JS::Any &expected,
                          const JS::Any &message, const std::string& operator_);
    static bool isDeepEqual(const JS::Any& actual, const JS::Any& expected);
};

#endif //JS_CMP_ASSERT_HPP
