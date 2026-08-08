#pragma once 

#ifndef DMATH_TYPE_TRAIDS_HPP
#define DMATH_TYPE_TRAIDS_HPP

#include"../Functional/vectorfunction.hpp"
#include"../Complex/complex.hpp"
NAMESPACESTART

template<typename Com>
struct is_Complex{
    static constexpr bool value = std::is_same<Com,Dmath::Complex>::value;
};

template<typename Num>
struct is_Num{
    static constexpr bool value = std::is_same<Num, Dmath::Scalar>::value || 
                                  std::is_same<Num, Dmath::Natural>::value ||
                                  std::is_same<Num, Dmath::Complex>::value;
};

template<typename Func>
struct is_function_object{
    static constexpr bool value = std::is_same<Func ,Dmath::SingleVarFunction>::value || 
                                  std::is_same<Func ,Dmath::DoubleVarFunction>::value ||
                                  std::is_same<Func ,Dmath::TripleVarFunction>::value ||

                                  std::is_same<Func ,Dmath::SingleVectorFunction>::value ||
                                  std::is_same<Func ,Dmath::DoubleVectorFunction>::value ||
                                  std::is_same<Func ,Dmath::TripleVectorFunction>::value;
};


template<typename Vec2>
struct is_vec2{
    static constexpr bool value = std::is_same<Vec2, Dmath::Vec2D >::value ||
                                  std::is_same<Vec2, Dmath::sVec2f>::value ||
                                  std::is_same<Vec2, Dmath::sVec2i>::value;
};


template<typename Vec3>

struct is_vec3{
    static constexpr bool value = std::is_same<Vec3, Dmath::Vec3D >::value ||
                                  std::is_same<Vec3, Dmath::sVec3f>::value ||
                                  std::is_same<Vec3, Dmath::sVec3i>::value;
};


//Templates for functional

template<typename Func>
struct function_traits; // Basis-Template

// Spezial for functionen with 2 Arguments
template<typename R, typename T1, typename T2>
struct function_traits<R(*)(T1,T2)> {
    using Arg1 = T1;
    using Arg2 = T2;
    using Return = R;
};

// Spezialisierung für Functor oder Lambda
template<typename R, typename C, typename T1, typename T2>
struct function_traits<R(C::*)(T1,T2) const> {
    using Arg1 = T1;
    using Arg2 = T2;
    using Return = R;
};


NAMESPACEEND
#endif