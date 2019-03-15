# Task8_2  
вариант 9 без "/" и "|"  


Matrix - папка с библиотекой для работы с вещественными матрицами  
test - папка с тестами. Используется Google Testing Framework  


как запускать:
```
$ mkdir build && cd build
$ cmake .. && make
```

как тестить:  
```
$ make test
```

пишет что то вроде:  

```
Running tests...
Test project /home/maria/Desktop/task8_2/build
    Start 1: matrix_test.constructors
1/7 Test #1: matrix_test.constructors .............   Passed    0.00 sec
    Start 2: matrix_test.put_get
2/7 Test #2: matrix_test.put_get ..................   Passed    0.00 sec
    Start 3: matrix_test.non_exact_comparision
3/7 Test #3: matrix_test.non_exact_comparision ....   Passed    0.00 sec
    Start 4: matrix_test.comparition_exceptions
4/7 Test #4: matrix_test.comparition_exceptions ...   Passed    0.00 sec
    Start 5: matrix_test.arithmetic_operators
5/7 Test #5: matrix_test.arithmetic_operators .....   Passed    0.00 sec
    Start 6: matrix_test.unary_operators
6/7 Test #6: matrix_test.unary_operators ..........   Passed    0.00 sec
    Start 7: matrix_test.functors
7/7 Test #7: matrix_test.functors .................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.02 sec

```