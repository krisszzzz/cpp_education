#include <cmath>
#include <iostream>
#include <optional>
#include <utility>
#include <variant>

constexpr double kEpsilon = 1e-7;

using Solution = std::optional<std::variant<std::monostate, double, std::pair<double, double>>>;

Solution solve_linear(double b, double c) {
    if (std::abs(b) < kEpsilon) {
        if (std::abs(c) < kEpsilon) {
            return std::make_optional(std::variant<std::monostate, double, std::pair<double, double>>(std::monostate{}));
        }
        else {
            return std::nullopt;
        }
    }
    double x = -c / b;
    return std::make_optional(std::variant<std::monostate, double, std::pair<double, double>>(x));
}

Solution solve_quadratic(double a, double b, double c) {
    if (std::abs(a) < kEpsilon) {
        return solve_linear(b, c);
    }

    double discriminant = b * b - 4 * a * c;

    if (std::abs(discriminant) < kEpsilon) {
        double x = -b / (2 * a);
        return std::make_optional(std::variant<std::monostate, double, std::pair<double, double>>(x));
    }

    if (discriminant > 0) {
        double sqrt_d = std::sqrt(discriminant);
        double x1 = (-b + sqrt_d) / (2 * a);
        double x2 = (-b - sqrt_d) / (2 * a);
        return std::make_optional(std::variant<std::monostate, double, std::pair<double, double>>(std::pair(x1, x2)));
    }

    return std::nullopt;
}

void print_solution(const Solution& sol) {
    if (!sol.has_value()) {
        std::cout << "No solutions\n";
        return;
    }

    const auto& var = sol.value();
    if (std::holds_alternative<std::monostate>(var)) {
        std::cout << "Infinite solutions\n";
    } else if (std::holds_alternative<double>(var)) {
        std::cout << "x1 = x2 = " << std::get<double>(var) << '\n';
    } else {
        auto [x1, x2] = std::get<std::pair<double, double>>(var);
        std::cout << "x1 = " << x1 << ", x2 = " << x2 << '\n';
    }
}

int main() {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    std::cin >> a >> b >> c;

    Solution sol = solve_quadratic(a, b, c);
    print_solution(sol);

    return 0;
}