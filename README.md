# icoldLib

## 包含文件

```c++
#include "mylib/pri_type_traits.hpp"
#include "mylib/comp.hpp"
#include "mylib/basic_graph.hpp"
#include "mylib/output.hpp"
```

## 元编程库 —— pri_type_traits.hpp

### 1.可打印参数

```C++
template<typename T, typename T2 = void >
struct is_Printable;

template<typename T>
struct is_Printable<T, ::std::void_t<::std::decay_t<decltype(::std::cout << ::std::declval<T>())>>>;
```

判断变量类型是否可被 `cout` 输出，若可以则 `is_Printable` 中 `value` 值为 `true` ，否则为 `false`。

**辅助类型**

```c++
template<typename T>
constexpr bool is_Printable_v = is_Printable<T>::value;
```

## 比较库 —— comp.hpp

### 1.比较两实数是否相等

```c++
template<typename T1, typename T2>
		requires (::std::integral<T1> || ::std::integral<T2> || ::std::floating_point<T1> || ::std::floating_point<T2>)
	constexpr bool _cmp_equal(T1 a, T2 b); //要求：C++20
```

## 基本图形库 —— basic_graph.hpp

**！！！注：图形库的使用要求为C++20，而且图形库中有推导指引，大多数情况下无需写明模板类型 ！！！**

### 1.Point类

#### 声明

```c++
template<typename T>
	requires (::std::integral<T> || ::std::floating_point<T>)
class Point;
```

#### 构造函数

```c++
constexpr Point(T x = 0, T y = 0);
constexpr Point(const Point&) = default;
constexpr Point(Point&&) = default;
```

#### 赋值运算符

```c++
Point<T>& operator=(const Point<T>& p) = default;
```

#### 运算符

```c++
template<typename T1, typename T2>
friend constexpr bool operator==(const Point<T1>& p1, const Point<T2>& p2);

template<typename T1, typename T2, typename Tc>
friend constexpr Point<Tc> operator-(const Point<T1>& p1, const Point<T2>& p2);

template<typename T1, typename T2, typename Tc>
friend constexpr Point<Tc> operator+(const Point<T1>& p1, const Point<T2>& p2);

template<typename T1, typename Tc = ::std::common_type_t<T, T1>>
	requires (::std::integral<T1> || ::std::floating_point<T1>)
constexpr Point<Tc> operator*(T1 ratio)const;

template<typename T>
friend ::std::ostream& operator<<(::std::ostream& out, const Point<T>& point_Out);
```

#### 转换运算符

```c++
template<typename Ti> requires (::std::integral<T> || ::std::floating_point<T>)
operator Point<Ti>;
```

#### 成员函数

```c++
template<typename T1>
constexpr bool is_under(const Point<T1>& p)const;
template<typename T1>
constexpr bool is_left(const Point<T1>& p)const;
constexpr T getX()const;
constexpr T getY()const;
void setX(T x);
void setY(T y);
void moveTo(T x, T y);
void moveTo(const Point<T>& p)
```

#### 其他函数

```c++
template<typename T1, typename T2>
constexpr auto pointDistancePow(const Point<T1>& p1, const Point<T2>& p2);	//两点距离的平方
template<typename T1, typename T2>
constexpr auto pointDistance(const Point<T1>& p1, const Point<T2>& p2);		//两点距离
```

#### 相关类

```c++
template<typename T>
using Vec = Point<T>;//Vec 二维向量
```

### 2.Line类

#### 声明

```c++
template<typename T>
	requires (::std::integral<T> || ::std::floating_point<T>)
class Line
```

#### 构造函数

```c++
constexpr Line();
constexpr Line(T x1, T y1, T x2, T y2);
template<typename Ti, typename U>
constexpr Line(const Point<Ti>& begin, const Point<U>& end);
constexpr Line(const Line&) = default;
constexpr Line(Line&&) = default;
```

#### 赋值运算符

```c++
Line<T>& operator=(const Line<T>&) = default;
```

#### 运算符

```c++
template<typename T1, typename T2>
friend bool operator==(const Line<T1>& l1, const Line<T2>& l2);

template<typename T>
friend ::std::ostream& operator<<(::std::ostream& out, const Line<T>& line_Out);
```

#### 转换运算符

```c++
template<typename Ti>
operator Line<Ti>;
```

#### 成员函数

```c++
constexpr auto length()const;
void translation(T vx, T vy);					//平移
void translation(const Vec<T>& vec);				//平移
void rotate(const Point<T>& center_point, long double rot);	//以center_point为中心旋转rot弧度
constexpr Point<T> getBegin()const;
constexpr Point<T> getEnd()const;
void moveBeginTo(Point<T>& point);
void moveBeginTo(T x, T y);
void moveEndTo(Point<T>& point);
void moveEndTo(T x, T y);
```

#### 其他函数

```c++
template<typename T1, typename T2>
constexpr bool is_Parallel(const Line<T1>& L1, const Line<T2>& L2);//判断两线段平行
template<typename T1, typename T2>
constexpr bool is_Intersection(const Line<T1>& L1, const Line<T2>& L2, long double precision = 1e-10);//判断两线段是否相交
template<typename T1, typename T2>
constexpr Point<long double> getcrossPoint(const Line<T1>& L1, const Line<T2>& L2);//获取两线段交点，前提是两线段相交
template<typename T1, typename T2>
constexpr auto getDisPointToLine(const Point<T1>& p, const Line<T2>& l);//点到直线距离
```

### 3.Ellipse类

#### 声明

```c++
template<typename T>
	requires (::std::integral<T> || ::std::floating_point<T>)
class Ellipse;
```

#### 构造函数

```c++
constexpr Ellipse();
constexpr Ellipse(const Point<T>& center, T a, T b, Vec<T> vec = {});
constexpr Ellipse(const Ellipse&) = default;
constexpr Ellipse(Ellipse&&) = default;
```

#### 赋值运算符

```c++
Ellipse<T>& operator=(const Ellipse<T>&) = default;
```

#### 运算符

无

#### 转换运算符

无

#### 成员函数

```c++
constexpr Point<T> getCenter()const;		//获取中心点
constexpr T getaxisLong()const;			//获取长轴长
constexpr T getaxisShort()const;		//获取短轴长
constexpr long double getFocalLen()const;	//获得焦距
constexpr long double getEccentricity()const;	//获得离心率
void moveCenter(Point<T> point);
void moveCenter(T x, T y);
void alteraxisLong(T length);			//改变长轴
void alteraxisShort(T length);			//改变短轴
void rotateTo(Vec<T> vec);			//修改旋转向量
```

### 4.Circular类

#### 声明

```c++
template<typename T>
	requires (::std::integral<T> || ::std::floating_point<T>)
class Circular;
```

#### 构造函数

```c++
constexpr Circular();
constexpr Circular(const Point<T>& center, T r = {});
constexpr Circular(const Circular<T>&) = default;
constexpr Circular(Circular<T>&&) = default;
```

#### 赋值运算符

```c++
Circular<T>& operator=(const Circular<T>&) = default;
```

#### 运算符

```c++
template<typename Ti>
constexpr bool operator==(const Circular<Ti>& cir)const;

template<typename Ti>
friend ::std::ostream& operator<<(::std::ostream& os, const Circular<Ti>& ocir);
```

#### 转换运算符

无

#### 成员函数

```c++
constexpr Point<T> getCenter()const;	//获得圆心
constexpr T getRadius()const;		//获得半径
void moveCenter(Point<T> point);
void moveCenter(T x, T y);
void alterRadius(T radius);		//修改圆心
long double getCircumference()const;	//获得周长
long double getArea()const;		//获得面积
```

#### 其他函数

```c++
template<typename T1, typename T2>
constexpr auto getCirCenterDis(const Circular<T1>& c1, const Circular<T2>& c2);//获得两圆中心点距离
template<typename T1,typename T2>
constexpr RealatCircles getRealatCirs(const Circular<T1>& c1, const Circular<T2>& c2);//获得两圆位置关系
template<typename T1, typename T2>
constexpr auto getCirMinDis(const Circular<T1>& c1, const Circular<T2>& c2);//获得两圆间最近端距离，注意要相离
template<typename T1, typename T2>
constexpr auto getCirMaxDis(const Circular<T1>& c1, const Circular<T2>& c2)//获得两圆最远端距离
template<typename T1,typename T2>
constexpr RealatPoint_Circle getRealatPointCir(const Point<T1>& p, const Circular<T2>& c);//获得点与圆的位置关系
template<typename T1,typename T2>
constexpr RealatLine_Circle getRealatLineCir(const Line<T1>& l, const Circular<T2>& c);//获得直线与圆的位置关系
```

**未完待续。。。**



## 输出库 —— output.hpp

### 1.print —— 格式化输出字符串（类似python）

Unicode字符集

```c++
template<typename... Args>
void print(const ::std::string_view fmt_str, Args&&... args);
```

多字节字符集

```c++
template<typename... Args>
void print(const ::std::wstring_view fmt_str, Args&&... args);
```

### 2.printc —— 定点输出

```c++
void printc(const ::std::string& t);		//输出单个string

void printc(const char* t);			//输出单个字符串

template<::std::ranges::range T>
void printc(const T& t);			//输出可迭代范围，如vector、array等，要求：C++20

template<typename T, typename...Args>
	requires requires(T t,Args...args){
		::std::cout << t << ' ';
		((::std::cout << args << ' '), ...);
	}
void printc(const T& t, Args&&...args);		//输出可变参数，要求：C++20

template<typename...Args>
typename ::std::enable_if_t <(is_Printable_v<Args> && ...)>
	printc(Args&&...args);			//输出可变参数，要求：C++17
```
