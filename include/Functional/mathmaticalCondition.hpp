#pragma once
#ifndef DMATH_MATHMATICAL_CONDITION_HPP
#define DMATH_MATHMATICAL_CONDITION_HPP

#include <memory>
#include <functional>
#include <type_traits>
#include <stdexcept>
#include "../Utils/dataTypes.hpp"

NAMESPACESTART

// ==================== FUNCTION TRAITS ====================
template<typename T>
struct FunctionTraits;




// Funktionszeiger
template<typename R, typename... Args>
struct FunctionTraits<R(*)(Args...)> {
    static constexpr size_t arity = sizeof...(Args);
    using ReturnType = R;
};



// std::function
template<typename R, typename... Args>
struct FunctionTraits<std::function<R(Args...)>> {
    static constexpr size_t arity = sizeof...(Args);
    using ReturnType = R;
};



// Lambda oder Funktor (über operator())
template<typename T>
struct FunctionTraits : public FunctionTraits<decltype(&T::operator())> {};




// Memberfunktion von Lambda: z. B. bool (lambda::*)(double) const
template<typename C, typename R, typename... Args>
struct FunctionTraits<R(C::*)(Args...) const> {
    static constexpr size_t arity = sizeof...(Args);
    using ReturnType = R;
};



class ConditionBase {
public:
    virtual ~ConditionBase() = default;

    virtual bool callX(Dmath::Scalar x) = 0;
    virtual bool callXY(Dmath::Scalar x, Dmath::Scalar y) = 0;
    virtual bool callXYZ(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z) = 0;

    virtual std::unique_ptr<ConditionBase> clone() const = 0;
};

// Helper: Count function args
template<typename T>
struct ArgCount;

template<typename R, typename... Args>
struct ArgCount<std::function<R(Args...)>> {
    static constexpr size_t value = sizeof...(Args);
};

// Wrapper
template<typename Func>
class ConditionWrapper : public ConditionBase {
private:
    Func func;
    static constexpr size_t ArgCountValue = FunctionTraits<Func>::arity;

public:
    ConditionWrapper(Func f) : func(f) {}

    bool callX(Dmath::Scalar x) override {
        if constexpr (ArgCountValue == 1)
            return func(x);
        throw std::runtime_error("Lambda does not accept 1 parameter.");
    }

    bool callXY(Dmath::Scalar x, Dmath::Scalar y) override {
        if constexpr (ArgCountValue == 2)
            return func(x, y);
        throw std::runtime_error("Lambda does not accept 2 parameters.");
    }

    bool callXYZ(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z) override {
        if constexpr (ArgCountValue == 3)
            return func(x, y, z);
        throw std::runtime_error("Lambda does not accept 3 parameters.");
    }

    std::unique_ptr<ConditionBase> clone() const override {
        return std::make_unique<ConditionWrapper<Func>>(func);
    }
};
// Main Condition class
class Condition {
private:
    std::unique_ptr<ConditionBase> funcBase;

public:
    template<typename F>
    Condition(F f) {
        constexpr size_t argCount = FunctionTraits<F>::arity;
        if (argCount > 3)
            throw std::invalid_argument("Too many arguments in lambda. Max is 3.");
        funcBase = std::make_unique<ConditionWrapper<F>>(f);
    }

    

    Condition(const Condition& other) : funcBase(other.funcBase->clone()) {}
    Condition& operator=(const Condition& other) {
        if (this != &other)
            funcBase = other.funcBase->clone();
        return *this;
    }

    bool operator()(Dmath::Scalar x) const {
        return funcBase->callX(x);
    }

    bool operator()(Dmath::Scalar x, Dmath::Scalar y) const {
        return funcBase->callXY(x, y);
    }

    bool operator()(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z) const {
        return funcBase->callXYZ(x, y, z);
    }
};

NAMESPACEEND
#endif
