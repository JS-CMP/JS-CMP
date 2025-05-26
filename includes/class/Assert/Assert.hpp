#ifndef JS_CMP_ASSERT_HPP
#define JS_CMP_ASSERT_HPP

#include "exceptions/AssertionError.hpp"
#include "exceptions/TypeError.hpp"
#include "global/global.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsObject.hpp"
#include "utils/Compare.hpp"

#include <cmath>

/** List of assertion to do (inverse of those function are also to do)
- [x] assert.equal(actual, expected[, message])
- [x] assert.strictEqual(actual, expected[, message])
- [x] assert.deepEqual(actual, expected[, message])
- [x] assert.deepStrictEqual(actual, expected[, message])
- [x] assert.ok(value[, message])
- [x] assert.fail([message])
- [x] assert.ifError(value)
- [x] assert.throws(fn[, error][, message])

- [ ] assert.doesNotMatch(string, regexp[, message]) -> need regexp
- [ ] assert.doesNotReject(asyncFn[, error][, message]) -> need async
- [ ] assert.rejects(asyncFn[, error][, message]) -> need async
*/
class assert : public JS::Object {
public:
    template <typename... Args>
    static JS::Any equal(Args&&... args) {
        return equalHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any notEqual(Args&&... args) {
        return notEqualHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any strictEqual(Args&&... args) {
        return strictEqualHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any notStrictEqual(Args&&... args) {
        return notStrictEqualHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any deepEqual(Args&&... args) {
        return deepEqualHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any notDeepEqual(Args&&... args) {
        return notDeepEqualHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any deepStrictEqual(Args&&... args) {
        return deepStrictEqualHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any notStrictDeepEqual(Args&&... args) {
        return notStrictDeepEqualHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any ok(Args&&... args) {
        return okHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any fail(Args&&... args) {
        return failHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any ifError(Args&&... args) {
        return ifErrorHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any throws(Args&&... args) {
        return throwsHelper({std::forward<Args>(args)...});
    }
    template <typename... Args>
    static JS::Any sameValue(Args&&... args) {
        return sameValue({std::forward<Args>(args)...});
    }

private:
    static JS::Any equalHelper(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any notEqualHelper(const JS::Any& thisArgs, const JS::Any& args);

    static JS::Any strictEqualHelper(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any notStrictEqualHelper(const JS::Any& thisArgs, const JS::Any& args);

    static JS::Any deepEqualHelper(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any notDeepEqualHelper(const JS::Any& thisArgs, const JS::Any& args);

    static JS::Any deepStrictEqualHelper(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any notStrictDeepEqualHelper(const JS::Any& thisArgs, const JS::Any& args);

    static JS::Any okHelper(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any failHelper(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any ifErrorHelper(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any throwsHelper(const JS::Any& thisArgs, const JS::Any& args);

    // test262 asserts
    static JS::Any sameValueHelper(const JS::Any& actual, const JS::Any& expected);
    static bool _sameValue(const JS::Any& actual, const JS::Any& expected);

    assert();
    // TODO: add handling stackStartFn
    static void innerFail(const JS::Any& actual, const JS::Any& expected, const JS::Any& message,
                          const std::string& operator_);
    static bool isDeepEqual(const JS::Any& actual, const JS::Any& expected, bool strict = false);
};

#endif // JS_CMP_ASSERT_HPP
