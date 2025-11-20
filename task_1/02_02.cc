#include <cmath>
#include <iostream>
#include <optional>

enum class SolutionCount {
  kNoSolution = 0,
  kOneSolution = 1,
  kTwoSolutions = 2,
  kInfSolutions = -1
};

struct SolutionResult {
  SolutionCount count;
  std::optional<double> x1;
  std::optional<double> x2;
};

SolutionResult solve_linear(double b, double c, double epsilon) {
  if (std::abs(b) < epsilon) {
    return (std::abs(c) < epsilon) ? SolutionResult{SolutionCount::kInfSolutions,
                                                    std::nullopt, std::nullopt}
                                   : SolutionResult{SolutionCount::kNoSolution,
                                                    std::nullopt, std::nullopt};
  } else {
    double x = -c / b;
    return {SolutionCount::kOneSolution, x, std::nullopt};
  }
}

SolutionResult solve_quadratic(double a, double b, double c, double epsilon) {
  if (std::abs(a) < epsilon) {
    return solve_linear(b, c, epsilon);
  } else {
    double discriminant = b * b - 4 * a * c;
    if (std::abs(discriminant) < epsilon) {
      double x = -b / (2 * a);

      return {SolutionCount::kOneSolution, x, std::nullopt};
    } else if (discriminant > 0) {
      double sqrt_d = std::sqrt(discriminant);
      double x1 = (-b + sqrt_d) / (2 * a);
      double x2 = (-b - sqrt_d) / (2 * a);

      return {SolutionCount::kTwoSolutions, x1, x2};
    } else {
      return {SolutionCount::kNoSolution, std::nullopt, std::nullopt};
    }
  }
}

int main() {
  double a, b, c;
  std::cin >> a >> b >> c;

  constexpr double epsilon = 1e-9;
  SolutionResult result = solve_quadratic(a, b, c, epsilon);

  switch (result.count) {
  case SolutionCount::kOneSolution:
    if (result.x1) {
      std::cout << *result.x1 << std::endl;
    }
    break;
  case SolutionCount::kTwoSolutions:
    if (result.x1 && result.x2) {
      std::cout << *result.x1 << " " << *result.x2 << std::endl;
    }
    break;
  case SolutionCount::kInfSolutions:
    std::cout << "infinite solutions" << std::endl;
    break;
  case SolutionCount::kNoSolution:
    std::cout << "no solutions" << std::endl;
    break;
  }

  return 0;
}
