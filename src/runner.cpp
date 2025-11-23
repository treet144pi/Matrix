#include "runner.hpp"
#include "Matrix.hpp"
#include <chrono>
#include <iostream>
#include <stdexcept>

int launcher(std::istream& in, std::ostream& out, bool benchmark)
{
    using clock = std::chrono::steady_clock;
    using ns    = std::chrono::nanoseconds;

    ns acc{0};

    size_t n = 0;
    if (!(in >> n)) {
        throw std::runtime_error("failed to read size of matrix");
    }

    matrix::Matrix<long long> A(n);

    try {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                long long elem = 0;
                if (!(in >> elem)) {
                    throw std::runtime_error("failed to read matrix element");
                }
                A[i][j] = elem;
            }
        }

        long long res = 0;

        if (benchmark)
        {
            auto t0 = clock::now();
            (void)det_bar(A);
            auto t1 = clock::now();
            acc += (t1 - t0);
        }
        else
        {
            res = det_bar(A);
            out << res;
        }
    }
    catch (const std::exception& ex) {
        out << ex.what() << '\n';
        return 1;
    }

    if (benchmark)
    {
        auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(acc).count();
        out << ms << " ns\n";
    }
    else
    {
        out << '\n';
    }
    return 0;
}
