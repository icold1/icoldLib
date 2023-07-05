#pragma once
#ifndef _MYCOMP_
#define _MYCOMP_

#if _HAS_CXX20 //C++20
#include <utility>
#include <type_traits>
namespace myLib {
	template<typename T1, typename T2>
		requires (::std::integral<T1> || ::std::integral<T2> || ::std::floating_point<T1> || ::std::floating_point<T2>)
	constexpr bool _cmp_equal(T1 a, T2 b) {
		if constexpr (::std::is_floating_point_v<T1> || ::std::is_floating_point_v<T2>) {
			long double t1 = static_cast<long double>(a);
			long double t2 = static_cast<long double>(b);
			return t1 < t2 + 1e-10 && t1>t2 - 1e-10;
		}
		else {
			return ::std::cmp_equal(a, b);
		}
	}
}
#endif // _HAS_CXX20

#endif // _MYCOMP_