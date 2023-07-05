#pragma once
#ifndef _PRI_TYPE_TRAITS_
#define _PRI_TYPE_TRAITS_

#include <utility>
#include <iostream>

namespace myLib {

    template<typename T, typename T2 = void >
    struct is_Printable{
        static constexpr bool value = false;
    };
    template<typename T>
    struct is_Printable<T, ::std::void_t<::std::decay_t<decltype(::std::cout << ::std::declval<T>())>>> {
        static constexpr bool value = true;
    };
    template<typename T>
    constexpr bool is_Printable_v = is_Printable<T>::value;


}

#endif