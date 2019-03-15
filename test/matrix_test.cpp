#include "gtest/gtest.h"
#include "../Matrix/Matrix.h"

using namespace std;

std::string create_matrix_string(double i) {
    return "{{" + std::to_string(i) + "," + std::to_string(i) + "}," +
           "{" + std::to_string(i) + "," + std::to_string(i) + "}}";
}

TEST (matrix_test, constructors) {
    std::cout<<"aaaaa1\n";
    ASSERT_NO_THROW(Matrix(10, 20));
    ASSERT_NO_THROW(Matrix(0.01));

    double vector[] = {1, 0.2, 3, 0.4, 5};
    ASSERT_NO_THROW(Matrix(5, vector));
    ASSERT_NO_THROW(Matrix(vector, 5));

    ASSERT_NO_THROW(Matrix("{{1,0.1,0.01},{2,0.2,0.02}}"));
    ASSERT_THROW(Matrix("{{1,2},{3,4}"), std::invalid_argument);

    std::stringstream matrix_stream;
    matrix_stream << Matrix("{{1,0.1,0.01},{2,0.2,0.02}}");
    ASSERT_EQ(Matrix("{{1,0.1,0.01},{2,0.2,0.02}}"), matrix_stream.str());
}

const double EPS = 0.5;

TEST(matrix_test, put_get) {
    std::cout<<"aaaaa2\n";

    int rows = 3;
    int columns = 4;
    Matrix m(rows, columns);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            m[i][j] = i * j;
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            ASSERT_EQ(m[i][j], i * j);
        }
    }
}

TEST(matrix_test, non_exact_comparision) {
    // random number generator initialization
    srand(69);

    double vector[2];
    double rnd = rand();
    ASSERT_EQ(Matrix(rnd + (rand() / RAND_MAX * EPS)), Matrix("{{" + std::to_string(rnd) + "}}"));

    ASSERT_NE(Matrix(rnd + EPS + 1), Matrix("{{" + std::to_string(rnd) + "}}"));

    vector[0] = rnd + rand() / RAND_MAX * EPS;
    vector[1] = rnd + rand() / RAND_MAX * EPS;
    ASSERT_EQ(Matrix(vector, 2), Matrix("{{" + std::to_string(rnd) + "," + std::to_string(rnd) + "}}"));


    vector[0] = rnd + EPS + 1;
    vector[1] = rnd + EPS + 1;
    ASSERT_NE(Matrix(vector, 2), Matrix("{{" + std::to_string(rnd) + "," + std::to_string(rnd) + "}}"));

    vector[0] = rnd + rand() / RAND_MAX * EPS;
    vector[1] = rnd + rand() / RAND_MAX * EPS;
    ASSERT_EQ(Matrix(2, vector), Matrix("{{" + std::to_string(rnd) + "},{" + std::to_string(rnd) + "}}"));

    vector[0] = rnd + EPS + 1;
    vector[1] = rnd + EPS + 1;
    ASSERT_NE(Matrix(2, vector), Matrix("{{" + std::to_string(rnd) + "},{" + std::to_string(rnd) + "}}"));
}

TEST(matrix_test, comparition_exceptions) {
    for (int i = 2; i < 10; ++i) {
        for (int j = 2; j < 10; ++j) {
            if (j != i) {
                ASSERT_THROW(Matrix(i, j) == Matrix(j, i), std::out_of_range);
            } else {
                ASSERT_NO_THROW(Matrix(i, j) == Matrix(j, i));
            }
        }
    }
}

TEST(matrix_test, arithmetic_operators) {
// +
    for (int i = -100; i < 100; i += 10) {
        std::string str1 = create_matrix_string(i);

        std::string str2 = create_matrix_string(2 * i);

        ASSERT_EQ(Matrix(str1)
                          +Matrix(str1), Matrix(str2));
    }

// -
    for (int i = -100; i < 100; i += 10) {
        std::string str1 = create_matrix_string(i);

        std::string str2 = create_matrix_string(2 * i);
        ASSERT_EQ(Matrix(str2)
                          -Matrix(str1), Matrix(str1));
    }

// *
    ASSERT_EQ(Matrix("{{1,1},{1,1}}") * Matrix("{{2,2},{3,69}}"),
            Matrix("{{5,71},{5,71}}"));
}

TEST(matrix_test, unary_operators) {
    // unary -
    for (int i = -100; i < 100; i += 20) {
        std::string str1 = create_matrix_string(i);

        std::string str2 = create_matrix_string(-i);

        ASSERT_EQ(-Matrix(str1), Matrix(str2));
    }

    // +=
    for (int i = -100; i < 100; i += 20) {
        std::string str1 = create_matrix_string(i);

        std::string str2 = create_matrix_string(2 * i);
        Matrix m = Matrix(str1);

        ASSERT_EQ(m += Matrix(str1), Matrix(str2));
    }

    // -=
    for (int i = -100; i < 100; i += 20) {
        std::string str1 = create_matrix_string(i);

        std::string str2 = create_matrix_string(2 * i);
        Matrix m = Matrix(str2);

        ASSERT_EQ(m -= Matrix(str1), Matrix(str1));
    }

    // *= double
    for (int i = -100; i < 100; i += 20) {
        std::string str1 = create_matrix_string(i);

        std::string str2 = create_matrix_string(2 * i);
        Matrix m = Matrix(str1);

        ASSERT_EQ(m *= i, Matrix(str2));
    }

}

TEST(matrix_test, functors) {
    // rows(), columns()
    for (size_t i = 1; i < 11; ++i) {
        for (size_t j = 1; j < 11; ++j) {
            Matrix m(i, j);
            ASSERT_EQ(i, m.rows());
            ASSERT_EQ(j, m.columns());
        }
    }

    // set()
    Matrix m = Matrix(create_matrix_string(1));
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.columns(); ++j) {
            m.set(i, j, i * j);
            ASSERT_EQ(m[i][j], i * j);
        }
    }

    // diagonal()
    for (int i = 0; i < 11; ++i) {
        std::string str1 = create_matrix_string(i);
        double vector[2];
        vector[0] = i;
        vector[1] = i;
        ASSERT_EQ(Matrix(str1), Matrix::diagonal(vector, 2));
    }

    // identity
    ASSERT_EQ(Matrix(create_matrix_string(1)), Matrix::identity(2));

}
