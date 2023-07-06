#pragma once
#ifndef _MYBASIC_GRAPHIC_
#define _MYBASIC_GRAPHIC_

#include <iostream>
#if __cpp_lib_concepts //C++20概念与约束
#include <concepts>

namespace myLib {
	constexpr auto PI = 3.14159265358979l;

	/* * * * * --  Point类  -- * * * * */
	template<typename T>
		requires (::std::integral<T> || ::std::floating_point<T>)
	class Point {
		T _x;
		T _y;

	public:
		constexpr Point(T x = 0, T y = 0) :_x(x), _y(y) {}
		constexpr Point(const Point&) = default;
		constexpr Point(Point&&) = default;
		Point<T>& operator=(const Point<T>& p) = default;
		template<typename T1, typename T2>
		friend constexpr bool operator==(const Point<T1>& p1, const Point<T2>& p2);
		template<typename T1, typename T2, typename Tc>
		friend constexpr Point<Tc> operator-(const Point<T1>& p1, const Point<T2>& p2);
		template<typename T1, typename T2, typename Tc>
		friend constexpr Point<Tc> operator+(const Point<T1>& p1, const Point<T2>& p2);
		template<typename T1, typename Tc = ::std::common_type_t<T, T1>>
			requires (::std::integral<T1> || ::std::floating_point<T1>)
		constexpr Point<Tc> operator*(T1 ratio)const {
			return Point<Tc>(this->_x * ratio, this->_y * ratio);
		}
		template<typename T1>
		constexpr bool is_under(const Point<T1>& p)const {
			using Tc = ::std::common_type_t<T1, T>;
			return static_cast<Tc>(this->_y) < static_cast<Tc>(p._y);
		}
		template<typename T1>
		constexpr bool is_left(const Point<T1>& p)const {
			using Tc = ::std::common_type_t<T1, T>;
			return static_cast<Tc>(this->_x) < static_cast<Tc>(p._x);
		}
		constexpr T getX()const { return _x; }
		constexpr T getY()const { return _y; }
		void setX(T x) { _x = x; }
		void setY(T y) { _y = y; }
		void moveTo(T x, T y) { _x = x, _y = y; }
		void moveTo(const Point<T>& p) { _x = p._x, _y = p._y; }
		template<typename T1, typename T2>
		friend constexpr auto pointDistancePow(const Point<T1>& p1, const Point<T2>& p2);
		template<typename T1, typename T2>
		friend constexpr auto pointDistance(const Point<T1>& p1, const Point<T2>& p2);
		template<typename Ti> requires (::std::integral<T> || ::std::floating_point<T>)
		operator Point<Ti>() {
			return Point<Ti>(static_cast<Ti>(this->_x), static_cast<Ti>(this->_y));
		}
		template<typename T>
		friend ::std::ostream& operator<<(::std::ostream& out, const Point<T>& point_Out);
	};
	template<typename...Args>
	Point(Args&&...) -> Point<::std::common_type_t<Args...>>;

	template<typename T1, typename T2>
	constexpr bool operator==(const Point<T1>& p1, const Point<T2>& p2) {
		using Tc = ::std::common_type_t<T1, T2>;
		return _cmp_equal(p1._x, p2._x) && _cmp_equal(p1._y, p2._y);
	}
	template<typename T1, typename T2, typename Tc = ::std::common_type_t<T2, T1>>
	constexpr Point<Tc> operator-(const Point<T1>& p1, const Point<T2>& p2) {
		return Point<Tc>(p1._x - p2._x, p1._y - p2._y);
	}
	template<typename T1, typename T2, typename Tc = ::std::common_type_t<T2, T1>>
	constexpr Point<Tc> operator+(const Point<T1>& p1, const Point<T2>& p2) {
		return Point<Tc>(p1._x + p2._x, p1._y + p2._y);
	}
	template<typename T1, typename T2>
	/*两点距离的平方*/
	constexpr auto pointDistancePow(const Point<T1>& p1, const Point<T2>& p2) {
		return (p1._x - p2._x) * (p1._x - p2._x) + (p1._y - p2._y) * (p1._y - p2._y);
	}
	template<typename T1, typename T2>
	/*两点距离*/
	constexpr auto pointDistance(const Point<T1>& p1, const Point<T2>& p2) {
		return ::std::hypot(p1._x - p2._x, p1._y - p2._y);
	}
	template<typename T>
	::std::ostream& operator<<(::std::ostream& out, const Point<T>& point_Out) {
		return out << "(" << point_Out._x << ", " << point_Out._y << ")";
	}

	template<typename T>
	/*Vec 二维向量*/
	using Vec = Point<T>;

	/* * * * * --  Line类  -- * * * * */
	template<typename T>
		requires (::std::integral<T> || ::std::floating_point<T>)
	class Line {
		Point<T> _beg, _end;

	public:
		constexpr Line() :_beg{}, _end{} {}
		constexpr Line(T x1, T y1, T x2, T y2) :_beg{ x1, y1 }, _end{ x2, y2 } {}
		template<typename Ti, typename U>
		constexpr Line(const Point<Ti>& begin, const Point<U>& end) {
			_beg = Point<T>(static_cast<T>(begin.getX()), static_cast<T>(begin.getY()));
			_end = Point<T>(static_cast<T>(end.getX()), static_cast<T>(end.getY()));
		}
		constexpr Line(const Line&) = default;
		constexpr Line(Line&&) = default;
		Line<T>& operator=(const Line<T>&) = default;
		template<typename T1, typename T2>
		friend constexpr bool operator==(const Line<T1>& l1, const Line<T2>& l2);
		constexpr auto length()const {
			return pointDistance(_beg, _end);
		}
		/*平移*/
		void translation(T vx, T vy) {
			_beg.moveTo(_beg.getX() + vx, _beg.getY() + vy);
			_end.moveTo(_end.getX() + vx, _end.getY() + vy);
		}
		/*平移*/
		void translation(const Vec<T>& vec) {
			_beg.moveTo(_beg.getX() + vec.getX(), _beg.getY() + vec.getY());
			_end.moveTo(_end.getX() + vec.getX(), _end.getY() + vec.getY());
		}
		/*以center_point为中心旋转rot弧度*/
		void rotate(const Point<T>& center_point, long double rot) {
			long double a = center_point.getX(), b = center_point.getY();
			auto sth = sin(rot), cth = cos(rot);
			_beg.moveTo((_beg.getX() - a) * cth - (_beg.getY() - b) * sth + a,
				(_beg.getX() - a) * sth + (_beg.getY() - b) * cth + b);
			_end.moveTo((_end.getX() - a) * cth - (_end.getY() - b) * sth + a,
				(_end.getX() - a) * sth + (_end.getY() - b) * cth + b);
		}
		template<typename T1,typename T2>
		friend constexpr bool is_Parallel(const Line<T1>& L1, const Line<T2>& L2);
		template<typename T1, typename T2>
		friend constexpr bool is_Intersection(const Line<T1>& L1, const Line<T2>& L2, long double precision);
		template<typename T1, typename T2>
		friend constexpr Point<long double> getcrossPoint(const Line<T1>& L1, const Line<T2>& L2);
		constexpr Point<T> getBegin()const { return _beg; }
		constexpr Point<T> getEnd()const { return _end; }
		void moveBeginTo(Point<T>& point) { _beg = point; }
		void moveBeginTo(T x, T y) { _beg = Point{ x,y }; }
		void moveEndTo(Point<T>& point) { _end = point; }
		void moveEndTo(T x, T y) { _end = Point{ x,y }; }
		template<typename T1>
		operator Line<T1>() {
			return Line<T1>(static_cast<T1>(this->_beg), static_cast<T1>(this->_end));
		}
		template<typename T>
		friend ::std::ostream& operator<<(::std::ostream& out, const Line<T>& line_Out);
	};
	template<typename T1, typename T2>
	Line(const Point<T1>&, const Point<T2>&) -> Line<::std::common_type_t<T1, T2>>;
	template<typename T1, typename T2, typename T3, typename T4>
	Line(T1&&,T2&&,T3&&,T4&&) -> Line<::std::common_type_t<T1, T2, T3, T4>>;


	template<typename T1, typename T2>
	constexpr bool operator==(const Line<T1>& l1, const Line<T2>& l2) {
		return l1._beg == l2._beg && l1._end == l2._end;
	}
	template<typename T1, typename T2>
	constexpr bool is_Parallel(const Line<T1>& L1, const Line<T2>& L2) {
		if (long double ll1 = L1.length(), ll2 = L2.length(); !(_cmp_equal(ll1, 0) || _cmp_equal(ll2, 0))) {
			long double x1 = static_cast<long double>(L1._end.getX()) - L1._beg.getX();
			long double y1 = static_cast<long double>(L1._end.getY()) - L1._beg.getY();
			long double x2 = static_cast<long double>(L2._end.getX()) - L2._beg.getX();
			long double y2 = static_cast<long double>(L2._end.getY()) - L2._beg.getY();
			x1 = x1 / ll1;
			y1 = y1 / ll1;
			x2 = x2 / ll2;
			y2 = y2 / ll2;
			return _cmp_equal(x1, x2) && _cmp_equal(y1, y2);
		}
		return true;
	}
	template<typename T1,typename T2,typename T3>
	constexpr auto cross(const Point<T1>& p1, const Point<T2>& p2, const Point<T3>& p3) {
		return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) - (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
	}
	template<typename T1, typename T2>
	constexpr bool is_Intersection(const Line<T1>& L1, const Line<T2>& L2, long double precision = 1e-10) {
		if (!(::std::min(L1._beg.getX(), L1._end.getX()) <= ::std::max(L2._beg.getX(), L2._end.getX()) &&
			::std::min(L2._beg.getY(), L2._end.getY()) <= ::std::max(L1._beg.getY(), L1._end.getY()) &&
			::std::min(L2._beg.getX(), L2._end.getX()) <= ::std::max(L1._beg.getX(), L1._end.getX()) &&
			::std::min(L1._beg.getY(), L1._end.getY()) <= ::std::max(L2._beg.getY(), L2._end.getY()))) {
			return false;
		}
		return (cross(L1._beg, L2._beg, L1._end) * cross(L1._beg, L2._end, L1._end) < precision) &&
			(cross(L2._beg, L1._beg, L2._end) * cross(L2._beg, L1._end, L2._end) < precision);
	}
	template<typename T1, typename T2>
	/*获取两线段交点 <!-- 前提是两线段相交 -->*/
	constexpr Point<long double> getcrossPoint(const Line<T1>& L1, const Line<T2>& L2) {
		Point<T2> base = L2._end - L2._beg;
		long double d1 = ::abs(cross(L2._beg, L2._end, L1._beg));
		auto d2 = ::abs(cross(L2._beg, L2._end, L1._end));
		if (_cmp_equal(d1 + d2, 0)) {
			throw ::std::invalid_argument("除 0 错误");
		}
		long double t = d1 / (d1 + d2);
		return L1._beg + (L1._end - L1._beg) * t;
	}
	template<typename T1, typename T2>
	constexpr auto getDisPointToLine(const Point<T1>& p, const Line<T2>& l) {
		return abs(cross(l.getBegin(), l.getEnd(), p)) / l.length();
	}
	template<typename T>
	::std::ostream& operator<<(::std::ostream& out, const Line<T>& line_Out) {
		return out << line_Out._beg << "->" << line_Out._end;
	}

	/* * * * * --  Ellipse类  -- * * * * */
	template<typename T>
		requires (::std::integral<T> || ::std::floating_point<T>)
	class Ellipse {
	protected:
		Point<T> _center;
		T _a, _b;		//长轴、短轴长
		Vec<T> _vec;
		
	public:
		constexpr Ellipse() :_center{}, _a{}, _b{}, _vec{} {}
		constexpr Ellipse(const Point<T>& center, T a, T b, Vec<T> vec = {}) :_center(center), _a(a), _b(b), _vec(vec) {}
		constexpr Ellipse(const Ellipse&) = default;
		constexpr Ellipse(Ellipse&&) = default;
		Ellipse<T>& operator=(const Ellipse<T>&) = default;
		constexpr Point<T> getCenter()const { return _center; }	//获取中心点
		/*获得长轴长*/
		constexpr T getaxisLong()const { return _a; }
		/*获得短轴长*/
		constexpr T getaxisShort()const { return _b; }
		/*获得焦距*/
		constexpr long double getFocalLen()const {
			return 2.0l * ::sqrt(_a * _a - _b * _b);
		}
		/*获取离心率*/
		constexpr long double getEccentricity()const { return getFocalLen() / _a; }
		void moveCenter(Point<T> point) { _center = point; }
		void moveCenter(T x, T y) { _center = Point<T>{ x,y }; }
		/*改变长轴长*/
		void alteraxisLong(T length) { _a = length; }
		/*改变短轴长*/
		void alteraxisShort(T length) { _b = length; }
		/*修改旋转向量*/
		void rotateTo(Vec<T> vec) { _vec = vec; }
	};
	template<typename T1, typename T2, typename T3, typename T4>
	Ellipse(const Point<T1>&, T2&&, T3&&, const Vec<T4>&) -> Ellipse<::std::common_type_t<T1, T2, T3, T4>>;
	template<typename T1, typename T2, typename T3>
	Ellipse(const Point<T1>&, T2&&, T3&&) -> Ellipse<::std::common_type_t<T1, T2, T3>>;

	/* * * * * --  Circular类  -- * * * * */
	template<typename T>
		requires (::std::integral<T> || ::std::floating_point<T>)
	class Circular :protected Ellipse<T> {
		T& _radius = Ellipse<T>::_a;

	public:
		constexpr Circular() :Ellipse<T>{} {}
		constexpr Circular(const Point<T>& center, T r = {}) :Ellipse<T>(center, r, r) {}
		constexpr Circular(const Circular<T>&) = default;
		constexpr Circular(Circular<T>&&) = default;
		Circular<T>& operator=(const Circular<T>&) = default;
		using Ellipse<T>::getCenter;
		constexpr T getRadius()const { return _radius; }
		using Ellipse<T>::moveCenter;
		void alterRadius(T radius) {
			_radius = radius;
		}
		/*获得周长*/
		long double getCircumference()const {
			return 2 * PI * _radius;
		}
		/*获得面积*/
		long double getArea()const {
			return PI * _radius * _radius;
		}
		template<typename Ti>
		constexpr bool operator==(const Circular<Ti>& cir)const {
			return this->_center == cir._center && _cmp_equal(this->_radius, cir._radius);
		}
		template<typename T1,typename T2>
		friend constexpr auto getCirCenterDis(const Circular<T1>& c1, const Circular<T2>& c2);
		template<typename Ti>
		friend ::std::ostream& operator<<(::std::ostream& os, const Circular<Ti>& ocir);
	};
	template<typename T1,typename T2>
	Circular(const Point<T1>&, T2&&) -> Circular<::std::common_type_t<T1, T2>>;


	enum class RealatCircles{ 
		Intersection,//相交
		Separation,//相离
		ExternTangent,//外切
		Inclusive,//内含
		InterTangent//内切
	};

	template<typename T1, typename T2>
	/*获得两圆中心点距离*/
	constexpr auto getCirCenterDis(const Circular<T1>& c1, const Circular<T2>& c2) {
		return ::std::hypot(c1._center.getX() - c2._center.getX(), c1._center.getY() - c2._center.getY());
	}
	template<typename T1,typename T2>
	/*获得两圆位置关系*/
	constexpr RealatCircles getRealatCirs(const Circular<T1>& c1, const Circular<T2>& c2) {
		auto _dis = getCirCenterDis(c1, c2);
		auto _minr = ::std::min(c1._radius, c2._radius);
		auto _maxr = ::std::max(c1._radius, c2._radius);
		if (_dis > _minr + _maxr) {
			return RealatCircles::Separation;
		}
		else if (_cmp_equal(_dis, _minr + _maxr)) {
			return RealatCircles::ExternTangent;
		}
		else if (_dis > _maxr - _minr && _dis < _maxr + _minr) {
			return RealatCircles::Intersection;
		}
		else if (_cmp_equal(_dis, _maxr - _minr)) {
			return RealatCircles::InterTangent;
		}
		else {
			return RealatCircles::Inclusive;
		}
	}
	template<typename T1, typename T2>
	constexpr auto getCirMinDis(const Circular<T1>& c1, const Circular<T2>& c2) {
		return getCirCenterDis(c1, c2) - c1.getRadius() - c2.getRadius();
	}
	template<typename T1, typename T2>
	constexpr auto getCirMaxDis(const Circular<T1>& c1, const Circular<T2>& c2) {
		return getCirCenterDis(c1, c2) + c1.getRadius() + c2.getRadius();
	}
	template<typename Ti>
	::std::ostream& operator<<(::std::ostream& os, const Circular<Ti>& ocir) {
		return os << "center point: " << ocir._center << " r: " << ocir._radius;
	}

	enum class RealatPoint_Circle {
		Inside,
		Outside,
		On
	};
	template<typename T1,typename T2>
	constexpr RealatPoint_Circle getRealatPointCir(const Point<T1>& p, const Circular<T2>& c) {
		auto _dis = pointDistance(p, c.getCenter());
		if (_cmp_equal(_dis, c.getRadius())) {
			return RealatPoint_Circle::On;
		}
		else if (_dis > c.getRadius()) {
			return RealatPoint_Circle::Outside;
		}
		else {
			return RealatPoint_Circle::Inside;
		}
	}

	enum class RealatLine_Circle {
		Intersection,//相交
		Tangency,//相切
		Detachment//相离
	};
	template<typename T1,typename T2>
	constexpr RealatLine_Circle getRealatLineCir(const Line<T1>& l, const Circular<T2>& c) {
		auto _dis = getDisPointToLine(c.getCenter(), l);
		if (_cmp_equal(_dis, c.getRadius())) {
			return RealatLine_Circle::Tangency;
		}
		else if (_dis > c.getRadius()) {
			return RealatLine_Circle::Detachment;
		}
		else {
			return RealatLine_Circle::Intersection;
		}
	}

	/* * * * * --  Triangle类  -- * * * * */
	template<typename T>
		requires (::std::integral<T> || ::std::floating_point<T>)
	class Triangle {
		Point<T> _a, _b, _c;

	public:
		constexpr Triangle() :_a(), _b(), _c() {}
		constexpr Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c) :_a(a), _b(b), _c(c) {}
		constexpr Triangle(const Triangle&) = default;
		constexpr Triangle(Triangle&&) = default;
		Triangle<T>& operator=(const Triangle<T>&) = default;
		constexpr Point<T> getPointA()const { return _a; }
		constexpr Point<T> getPointB()const { return _b; }
		constexpr Point<T> getPointC()const { return _c; }
		constexpr Line<T> getEdgeA()const { return Line<T>(_b, _c); }
		constexpr Line<T> getEdgeB()const { return Line<T>(_a, _c); }
		constexpr Line<T> getEdgeC()const { return Line<T>(_a, _b); }
		void movePointATo(const Point<T>& p) { _a = p; }
		void movePointBTo(const Point<T>& p) { _b = p; }
		void movePointCTo(const Point<T>& p) { _c = p; }
		bool movePointToPoint(const Point<T>& Src, const Point<T>& Des) {
			if (Src == _a) {
				_a = Des;
				return true;
			}
			else if (Src == _b) {
				_b = Des;
				return true;
			}
			else if (Src == _c) {
				_c = Des;
				return true;
			}
			return false;
		}
		constexpr long double getArea()const {
			T _z1 = _b.getY() - _c.getY(), _z2 = _c.getY() - _a.getY(), _z3 = _a.getY() - _b.getY();
			return 0.5 * (_a.getX() * _z1 + _b.getX() * _z2 + _c.getX() * _z3);
		}
		Circular<long double> getCircumcircle()const {
			if (_cmp_equal(cross(_a, _b, _c), 0)) {
				throw ::std::invalid_argument("除 0 错误");
			}
			auto _tmp1 = _b.getX() * _b.getX() + _b.getY() * _b.getY();
			auto _tmp2 = _tmp1 - _a.getX() * _a.getX() - _a.getY() * _a.getY();
			auto _tmp3 = _c.getX() * _c.getX() + _c.getY() * _c.getY() - _tmp1;
			long double _tmp4 = 2 * (_c.getY() - _b.getY()) * (_b.getX() - _a.getX()) - 2 * (_b.getY() - _a.getY()) * (_c.getX() - _b.getX());
			long double _px = ((_c.getY() - _b.getY()) * _tmp2 - (_b.getY() - _a.getY()) * _tmp3) / _tmp4;
			long double _py = ((_b.getX() - _a.getX()) * _tmp3 - (_c.getX() - _b.getX()) * _tmp2) / _tmp4;
			long double _r = ::std::hypot(_px - _a.getX(), _py - _a.getY());
			return Circular<long double>(Point<long double>(_px, _py), _r);
		}
		template<typename Ti>
		constexpr bool operator==(const Triangle<Ti>& t)const {
			return this->_a == t._a && this->_b == t._b && this->_c == t._c;
		}
		template<typename T1, typename T2, typename Tc>
		friend Line<Tc> getSameEdge(const Triangle<T1>& t1, const Triangle<T2>& t2);
		template<typename Ti>
		operator Triangle<Ti>() {
			return Triangle<Ti>(static_cast<Ti>(this->_a), static_cast<Ti>(this->_b), static_cast<Ti>(this->_c));
		}
	};
	template<typename T1, typename T2, typename T3>
	Triangle(const Point<T1>&, const Point<T2>&, const Point<T3>&) -> Triangle<::std::common_type_t<T1, T2, T3>>;

	template<typename T1, typename T2, typename Tc = ::std::common_type_t<T1,T2>>
	Line<Tc> getSameEdge(const Triangle<T1>& t1, const Triangle<T2>& t2) {
		if (t1._a == t2._a) {
			if (t1._b == t2._b || t1._b == t2._c) {
				return Line<Tc>(t1._a, t1._b);
			}
			else if (t1._c == t2._b || t1._c == t2._c) {
				return Line<Tc>(t1._a, t1._c);
			}
		}
		else if (t1._a == t2._b) {
			if (t1._b == t2._a || t1._b == t2._c) {
				return Line<Tc>(t1._a, t1._b);
			}
			else if (t1._c == t2._a || t1._c == t2._c) {
				return Line<Tc>(t1._a, t1._c);
			}
		}
		else if (t1._a == t2._c) {
			if (t1._b == t2._a || t1._b == t2._b) {
				return Line<Tc>(t1._a, t1._b);
			}
			else if (t1._c == t2._a || t1._c == t2._b) {
				return Line<Tc>(t1._a, t1._c);
			}
		}
		else {
			if (t1._b == t2._a) {
				if (t1._c == t2._b || t1._c == t2._c) {
					return Line<Tc>(t1._b, t1._c);
				}
			}
			else if (t1._b == t2._b) {
				if (t1._c == t2._a || t1._c == t2._c) {
					return Line<Tc>(t1._b, t1._c);
				}
			}
			else if (t1._b == t2._c) {
				if (t1._c == t2._b || t1._c == t2._a) {
					return Line<Tc>(t1._b, t1._c);
				}
			}
		}
		return Line<Tc>{};
	}

	/* * * * * --  Rectangle类  -- * * * * */
	template<typename T>
		requires (::std::integral<T> || ::std::floating_point<T>)
	class Rectangle {
		T _left, _right, _top, _bottom;

	public:
		constexpr Rectangle() :_left(), _right(), _top(), _bottom() {}
		constexpr Rectangle(T left, T right, T top, T bottom) :_left(left), _right(right), _top(top), _bottom(bottom) {}
		constexpr Rectangle(const Triangle<T>& tri) {
			_left = ::std::min({ tri.getPointA().getX(),tri.getPointB().getX(),tri.getPointC().getX() });
			_right = ::std::max({ tri.getPointA().getX(),tri.getPointB().getX(),tri.getPointC().getX() });
			_top = ::std::min({ tri.getPointA().getY(),tri.getPointB().getY(),tri.getPointC().getY() });
			_bottom = ::std::max({ tri.getPointA().getY(),tri.getPointB().getY(),tri.getPointC().getY() });
		}
		constexpr Rectangle(const Rectangle&) = default;
		constexpr Rectangle(Rectangle&&) = default;
		constexpr T getLeft()const { return _left; }
		constexpr T getRight()const { return _right; }
		constexpr T getTop()const { return _top; }
		constexpr T getBottom()const { return _bottom; }

	};
}
#endif // __cpp_lib_concepts
#endif // _MYBASIC_GRAPHIC_