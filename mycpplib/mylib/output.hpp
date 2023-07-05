#pragma once
#ifndef _MYOUTPUT_
#define _MYOUTPUT_

#include <iostream>
#if __cpp_lib_ranges
#include <ranges>
#endif // __cpp_lib_ranges
#if __cpp_lib_format
#include <format>
#endif // __cpp_lib_format
#include <algorithm>

namespace myLib {
#if __cpp_lib_format //C++20��ʽ���ַ���
	template<typename... Args>
	void print(const ::std::string_view fmt_str, Args&&... args)
	{
		::fputs(::std::vformat(fmt_str, ::std::make_format_args(args...)).c_str(), stdout);
		/* ���ַ�ʽ������ *
		* auto x = ::std::vformat(fmt_str, ::std::make_format_args(args...));
		* * ::std::cout << x;
		* * * ::std::ranges::copy(x, ::std::ostream_iterator<::std::string_view::value_type>{::std::cout});*/
	}

	template<typename... Args>
	void print(const ::std::wstring_view fmt_str, Args&&... args)
	{
		::std::wcout << ::std::vformat(fmt_str, ::std::make_wformat_args(args...));
	}
#endif // __cpp_lib_format
#if __cpp_lib_concepts && __cpp_lib_ranges //C++20�����뷶Χ
	template<::std::ranges::range T>
	void printc(const T& t)
	{
		for (const auto& i : t) {
			::std::cout << i << ' ';
		}
		putchar('\n');
	}
#endif // __cpp_lib_concepts && __cpp_lib_ranges

	void printc(const ::std::string& t)
	{
		::std::cout << t << '\n';
	}

	void printc(const char* t)
	{
		::std::cout << t << '\n';
	}
#if __cpp_lib_concepts //C++20ģ��
	template<typename T, typename...Args>
		requires requires(T t,Args...args){
		::std::cout << t << ' ';
		((::std::cout << args << ' '), ...);
		}
	void printc(const T& t, Args&&...args)
	{
		/* * ��һ��Ϊ�ݹ���ã��ڶ���Ϊ�۵����ʽ
		::std::cout << t << ' ';
		if constexpr (sizeof...(args) != 0) {
			::printc(args...);
		}
		*/
		::std::cout << t << ' ';
		((::std::cout << args << ' '), ...);
		::std::cout.unsetf(::std::ios_base::skipws);
		::std::cout.put('\b');
		::std::cout.setf(::std::ios_base::skipws);
	}
#elif __cpp_fold_expressions //C++17�۵����ʽ
	template<typename...Args>
	typename ::std::enable_if_t <(is_Printable_v<Args> && ...)>
		printc(Args&&...args)
	{
		static_assert((is_Printable_v<Args> && ...));
		((::std::cout << args << ' '), ...);
		::std::cout.unsetf(::std::ios_base::skipws);
		::std::cout.put('\b');
		::std::cout.setf(::std::ios_base::skipws);
	}
#endif // __cpp_lib_concepts || __cpp_fold_expressions

}
#endif // _MYOUTPUT_