
#include <algorithm>
#include <vector>
#include <limits>

#include "rectangle.h"

namespace rectangle {

Rectangle intersection(const Rectangle &lhs, const Rectangle &rhs) {
    if (lhs.right_bottom().y <= rhs.left_top().y || lhs.right_bottom().x <= rhs.left_top().x ||
        lhs.left_top().y >= rhs.right_bottom().y || lhs.left_top().x >= rhs.right_bottom().x) {
        return Rectangle{0, 0, 0, 0};
    }

    int inter_left = std::max(lhs.left_top().x, rhs.left_top().x);
    int inter_top = std::max(lhs.left_top().y, rhs.left_top().y);
    int inter_right = std::min(lhs.right_bottom().x, rhs.right_bottom().x);
    int inter_bottom = std::min(lhs.right_bottom().y, rhs.right_bottom().y);

    return Rectangle(inter_left, inter_top, inter_right, inter_bottom);
}

Rectangle intersection(const std::vector<Rectangle> &rectangles) {
    if (rectangles.empty()) {
        return Rectangle(0, 0, 0, 0);
    }

    auto result = rectangles[0];

    for (std::size_t i = 1; i < rectangles.size(); ++i) {
        result = intersection(result, rectangles[i]);
        if (result.is_degenerate()) {
            break;
        }
    }

    return result;
}

Rectangle bounding_box(const std::vector<Rectangle> &rectangles) {
    if (rectangles.empty()) {
        return Rectangle(0, 0, 0, 0);
    }

    int min_x = std::numeric_limits<int>::max();
    int min_y = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int max_y = std::numeric_limits<int>::min();

    for (const auto &rect : rectangles) {
        min_x = std::min(min_x, rect.left_top().x);
        min_y = std::min(min_y, rect.left_top().y);
        max_x = std::max(max_x, rect.right_bottom().x);
        max_y = std::max(max_y, rect.right_bottom().y);
    }

    if (min_x > max_x || min_y > max_y) {
        return Rectangle(0, 0, 0, 0);
    }

    return Rectangle(min_x, min_y, max_x, max_y);
}

}