//
// Created by Simon BANDIERA on 24/11/2024.
//

#ifndef JS_CMP_ASSERT_HPP
#define JS_CMP_ASSERT_HPP

#include "types/objects/JsObject.hpp"
#include "types/objects/JsFunction.hpp"
#include "exceptions/TypeError.hpp"
#include "exceptions/AssertionError.hpp"
#include <cmath>

/** List of assertion to do (inverse of thoses function are also to do)
- [ ] assert.deepEqual(actual, expected[, message])
- [ ] assert.deepStrictEqual(actual, expected[, message])
- [ ] assert.doesNotMatch(string, regexp[, message])
- [ ] assert.doesNotReject(asyncFn[, error][, message])
- [ ] assert.doesNotThrow(fn[, error][, message])
- [x] assert.equal(actual, expected[, message])
- [ ] assert.fail([message])
- [ ] assert.fail(actual, expected[, message[, operator[, stackStartFn]]])
- [ ] assert.ifError(value)
- [ ] assert.match(string, regexp[, message])
- [ ] assert.notDeepEqual(actual, expected[, message])
- [ ] assert.notDeepStrictEqual(actual, expected[, message])
- [ ] assert.notEqual(actual, expected[, message])
- [ ] assert.notStrictEqual(actual, expected[, message])
- [ ] assert.ok(value[, message])
- [ ] assert.rejects(asyncFn[, error][, message])
- [ ] assert.strictEqual(actual, expected[, message])
- [ ] assert.throws(fn[, error][, message])
*/

class Assert : public JS::Object {
public:
    Assert();
    static JS::Any equal(const std::vector<JS::Any>& args);
    static JS::Any notEqual(const std::vector<JS::Any>& args);
private:
    // TODO: add handling stackStartFn
    static void innerFail(const JS::Any& actual, const JS::Any &expected,
                          const JS::Any &message, const std::string& operator_);
};

#endif //JS_CMP_ASSERT_HPP
