#include <iostream>
#include <vector>

class ExpressionSolver {
private:
    int n;
    int s;
    std::vector<int> a;

public:
    ExpressionSolver(int n, int s) : n(n), s(s), a(n + 1, 0) {}

    void solve() {
        int sum = n * (n + 1) / 2;
        for (int i = n; i >= 1; --i) {
            if (sum - 2 * i >= s) {
                a[i] = 1;
                sum -= 2 * i;
            }
        }

        if (sum == s) {
            if (a[1]) {
                for (int i = 4; i <= n; ++i) {
                    if (a[1] == 0) break;
                    if (a[i]) {
                        for (int j = 2; j <= i / 2; ++j) {
                            if (a[j] == 0 && a[i + 1 - j] == 0) {
                                a[j] = a[i + 1 - j] = 1;
                                a[1] = a[i] = 0;
                                break;
                            }
                        }
                    }
                }

                if (a[1]) {
                    std::cout << "Impossible\n";
                    return;
                }
            }

            std::cout << "1";
            for (int i = 2; i <= n; ++i) {
                std::cout << ((a[i] == 1) ? '-' : '+') << i;
            }
        } else {
            std::cout << "Impossible\n";
        }
    }
};

int main() {

    int n, s;
    std::cin >> n >> s;

    ExpressionSolver solver(n, s);
    solver.solve();

    return 0;
}
