#pragma once

#include <vector>

namespace rectangle {

struct Point final {
    int x, y;
};

class Rectangle final {
   private:
    Point m_left_top, m_right_bottom;

   public:
    Rectangle(Point left_top, Point right_bottom)
        : m_left_top(left_top), m_right_bottom(right_bottom) {}
    Rectangle(int left_top_x, int left_top_y, int right_bottom_x, int right_bottom_y)
        : m_left_top{left_top_x, left_top_y}, m_right_bottom{right_bottom_x, right_bottom_y} {}

    const Point &left_top() const  { return m_left_top; }
    const Point &right_bottom() const  { return m_right_bottom; }

    unsigned width() const { return m_right_bottom.x - m_left_top.x; }
    unsigned height() const { return m_right_bottom.y - m_left_top.y; }

    bool is_degenerate() const { return width() == 0 || height() == 0; }

    int square() const {
        return (m_right_bottom.x - m_left_top.x) * (m_right_bottom.y - m_left_top.y);
    }
};

Rectangle intersection(const Rectangle &lhs, const Rectangle &rhs);
Rectangle intersection(const std::vector<Rectangle> &rectangles);
Rectangle bounding_box(const std::vector<Rectangle> &rectangles);

}  // namespace rectangle