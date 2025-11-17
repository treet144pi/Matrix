import random


N = 5               # размерность матрицы (n x n)
DET_VALUE = 9     # детерминант: число или None, чтобы был случайный ненулевой
NUM_TESTS = 10        # сколько тестов сгенерировать
STEPS = 1000000          # сколько случайных операций пытаться сделать

# Диапазон коэффициентов k в операциях
COEFF_VALUES = [i for i in range(-1000000,1000000)]

# Максимальный |элемент| в матрице
MAX_ABS = 10**7

def generate_matrix(n=4, det_value=None, steps=20):
    if det_value is None:
        det_value = 0
        while det_value == 0:
            det_value = random.randint(-9, 9)
    A = [[0] * n for _ in range(n)]
    for i in range(n):
        A[i][i] = 1
    A[0][0] = det_value
    for _ in range(steps):
        op_type = random.choice(["row", "col"])
        i, j = random.sample(range(n), 2)
        k = random.choice(COEFF_VALUES)

        if op_type == "row":
            ok = True
            for c in range(n):
                new_val = A[i][c] + k * A[j][c]
                if abs(new_val) > MAX_ABS:
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
                if abs(new_val) > MAX_ABS:
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
    print("# det =", det_value)
    print()


if __name__ == "__main__":
    random.seed()
    for _ in range(NUM_TESTS):
        d, A = generate_matrix(
            n=N,
            det_value=DET_VALUE,
            steps=STEPS,
        )
        print_test(N, d, A)
