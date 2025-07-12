#ifndef JS_CMP_ASSERT_HPP
#define JS_CMP_ASSERT_HPP

#include "internals/Object.hpp"

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

// TODO move it when we have support for modules / require
namespace JS {
class Assert : public JS::InternalObject {
public:
    explicit Assert(const JS::Properties& properties);
    /**
     * @name Assertions Functions
     * @brief Functions to assert conditions in tests.
     */
    ///@{
    /** @brief Asserts that a value is not truthy (null, undefined, NaN, false).*/
    static JS::Any fail(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that a value is truthy (not null, undefined, NaN, false).*/
    static JS::Any ok(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that two values are equal.*/
    static JS::Any equal(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that two values are not equal.*/
    static JS::Any notEqual(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that two values are deep equal.*/
    static JS::Any deepEqual(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that two values are not deep equal.*/
    static JS::Any notDeepEqual(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that two values are strictly equal.*/
    static JS::Any strictEqual(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that two values are not strictly equal.*/
    static JS::Any notStrictEqual(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that value are throwable.*/
    static JS::Any throws(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that value are not throwable.*/
    static JS::Any doesNotThrow(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Asserts that value is ok (not null, undefined, NaN, false).*/
    static JS::Any ifError(const JS::Any& thisArgs, const JS::Any& args);
    ///@}


    // Not Needed for ES5 Error
    static JS::Any deepStrictEqual(const JS::Any& thisArgs, const JS::Any& args);
    static JS::Any notStrictDeepEqual(const JS::Any& thisArgs, const JS::Any& args);
private:
    // TODO: add handling stackStartFn
    static void innerFail(const JS::Any& actual, const JS::Any& expected, const JS::Any& message,
                          const std::u16string& operator_);
    static bool isDeepEqual(const JS::Any& actual, const JS::Any& expected, bool strict = false);

    // test262 asserts
    static JS::Any sameValue(const JS::Any& actual, const JS::Any& expected);
    static bool _sameValue(const JS::Any& actual, const JS::Any& expected);
};
} // namespace JS

#endif // JS_CMP_ASSERT_HPP
