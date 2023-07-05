#pragma once
#ifndef _MYLIB_
#define _MYLIB_

#ifndef _PRI_TYPE_TRAITS_ //控制pri_type_traits库的包含，0为包含，1为不包含
#if 0
#define _PRI_TYPE_TRAITS_
#endif
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * -- !!不要随便修改文件包含顺序!! --* * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "mylib/pri_type_traits.hpp"
#include "mylib/comp.hpp"
#include "mylib/basic_graph.hpp"
#include "mylib/output.hpp"

#endif //_MYLIB_