# Matrix
##  Требования

- C++17
- CMake ≥ 3.16
- GTest
- Python (для генерации тестов `gen_tests.py`)

---

##  Сборка проекта

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

---

##  Запуск

### Функциональный запуск

```bash
./build/funcdet < tests/e2e/in/test1.txt
```

### Производительный запуск (бенчмарк)

```bash
./build/benchdet < tests/e2e/in/test1.txt
```

---

##  Тестирование

### Unit тесты

Собираются и запускаются с использованием CTest:

```bash
cd build && ctest --output-on-failure
```

Или вручную:

```bash
./build/unit_tests_matrix
./build/unit_tests_vector
```

### E2E тесты

```bash
./build/e2e
```

---

##  Структура проекта

```
Matrix/
│
├── include/
│   ├── Matrix.hpp
│   └── MyVector.hpp
│
├── src/
│   ├── benchdet.cpp
│   ├── funcdet.cpp
│   ├── runner.cpp
│   └── runner.hpp
│
├── tests/
│   ├── e2e/
│   │   ├── in/
│   │   └── out/
│   └── unit/
│       ├── test_matrix.cpp
│       └── test_myvector.cpp
│
├── gen_tests.py
├── CMakeLists.txt
└── README.md
```

---

##  Полезные команды

```bash
python3 gen_tests.py
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
rm -rf build/
```

---
