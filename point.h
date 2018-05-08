#ifndef POINT_H
#define POINT_H

template <typename T> class Point;

template <typename S> bool operator== (Point<S>, Point<S>);
template <typename S> bool operator!= (Point<S>&, Point<S>&);
template <typename S> bool operator< (Point<S>&, Point<S>&);
template <typename S> bool operator> (Point<S>&, Point<S>&);
template <typename S> bool operator<= (Point<S>&, Point<S>&);
template <typename S> bool operator>= (Point<S>&, Point<S>&);
template <typename S> Point<S> operator+(Point<S>, Point<S>&);
template <typename S> Point<S> operator-(Point<S>, Point<S>&);

template <typename T>
class Point
{
    public:
        T x, y;

        Point(T argX=0, T argY=0): x(argX), y(argY) {}

        inline void operator() (int argX, int argY)
            { x = argX; y = argY; }

        Point& operator= (const Point& other)
            { x = other.x; y = other.y; return *this; }
        Point& operator+= (const Point& other)
            { x += other.x; y += other.y; return *this; }
        Point& operator-= (const Point& other)
            { x -= other.x; y -= other.y; return *this; }
        Point& operator+= (T other)
            { x += other; y += other; return *this; }
        Point& operator-= (T other)
            { x -= other; y -= other; return *this; }
        Point& operator*= (T other)
            { x *= other; y *= other; return *this; }

        Point& operator++ ()
            { x += 1; y += 1; return *this; }
        Point operator++ (int)
            { Point result = *this; ++(*this); return result; }
        Point& operator-- ()
            { x -= 1; y -= 1; return *this; }
        Point operator-- (int)
            { Point result = *this; --(*this); return result; }

        friend bool operator== <T> (Point, Point);
        friend bool operator!= <T> (Point&, Point&);
        friend bool operator< <T> (Point&, Point&);
        friend bool operator> <T> (Point&, Point&);
        friend bool operator<= <T> (Point&, Point&);
        friend bool operator>= <T> (Point&, Point&);
        friend Point operator+ <T> (Point, Point&);
        friend Point operator- <T> (Point, Point&);
};

template <typename S>
bool operator== (Point<S> lhs, Point<S> rhs)
    {
        if( lhs.x == rhs.x && lhs.y == rhs.y ) return true;
        else return false;
    };

template <typename S>
bool operator!= (Point<S>& lhs, Point<S>& rhs)
    {
        return !( lhs == rhs );
    };

template <typename S>
bool operator< (Point<S>& lhs, Point<S>& rhs)
    {
        if( lhs.y == rhs.y ) return ( lhs.x < rhs.x );
        else return ( lhs.y < rhs.y);
    };

template <typename S>
bool operator> (Point<S>& lhs, Point<S>& rhs)
    {
        if( lhs.y == rhs.y ) return ( lhs.x > rhs.x );
        else return ( lhs.y > rhs.y);
    };

template <typename S>
bool operator<= (Point<S>& lhs, Point<S>& rhs) { return !( lhs > rhs ); };

template <typename S>
bool operator>= (Point<S>& lhs, Point<S>& rhs) { return !( lhs < rhs ); };

template <typename S>
Point<S> operator+ (Point<S> lhs, Point<S>& rhs)
    {
        lhs += rhs;
        return lhs;
    };

template <typename S>
Point<S> operator- (Point<S> lhs, Point<S>& rhs)
    {
        lhs -= rhs;
        return lhs;
    };
#endif // POINT_H
