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
- [x] assert.deepEqual(actual, expected[, message])
- [x] assert.deepStrictEqual(actual, expected[, message])
- [x] assert.ok(value[, message])
- [x] assert.fail([message])
- [x] assert.ifError(value)
- [ ] assert.throws(fn[, error][, message])

- [ ] assert.doesNotMatch(string, regexp[, message]) -> need regexp
- [ ] assert.doesNotReject(asyncFn[, error][, message]) -> need async
- [ ] assert.rejects(asyncFn[, error][, message]) -> need async
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

    static JS::Any deepStrictEqual(const std::vector<JS::Any>& args);
    static JS::Any notStrictDeepEqual(const std::vector<JS::Any>& args);

    static JS::Any ok(const std::vector<JS::Any>& args);

    static JS::Any fail(const std::vector<JS::Any>& args);

    static JS::Any ifError(const std::vector<JS::Any>& args);

private:
    // TODO: add handling stackStartFn
    static void innerFail(const JS::Any& actual, const JS::Any &expected,
                          const JS::Any &message, const std::string& operator_);
    static bool isDeepEqual(const JS::Any& actual, const JS::Any& expected, bool strict = false);
};

#endif //JS_CMP_ASSERT_HPP
