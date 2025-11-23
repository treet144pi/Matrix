import random

def generate_matrix(n: int,
                    det_value: int = None,
                    steps: int = 50,
                    coeff_bound: int = 3,
                    max_abs: int = 20000):
    if det_value is None:
        det_value = random.choice([i for i in range(-9, 10) if i != 0])

    A = [[0] * n for _ in range(n)]
    A[0][0] = det_value
    for i in range(1, n):
        A[i][i] = 1

    coeffs = [k for k in range(-coeff_bound, coeff_bound + 1) if k != 0]

    for _ in range(steps):
        op_type = random.choice(["row", "col"])
        i, j = random.sample(range(n), 2)
        k = random.choice(coeffs)

        if op_type == "row":
            ok = True
            for c in range(n):
                new_val = A[i][c] + k * A[j][c]
                if abs(new_val) > max_abs:
                    ok = False
                    break
            if not ok:
                continue
            for c in range(n):
                A[i][c] += k * A[j][c]

        else:
            ok = True
            for r in range(n):
                new_val = A[r][i] + k * A[r][j]
                if abs(new_val) > max_abs:
                    ok = False
                    break
            if not ok:
                continue
            for r in range(n):
                A[r][i] += k * A[r][j]

    return det_value, A


def print_test(n, det_value, A):
    print(n)
    for row in A:
        print(" ".join(str(x) for x in row))
    print()


if __name__ == "__main__":
    N         = 9
    DET_VALUE = 890
    random.seed()
    d, A = generate_matrix(n=N,det_value=DET_VALUE,steps=1000,coeff_bound=5,max_abs=10000,)
    print_test(N, d, A)

