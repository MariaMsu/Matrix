#include <iostream>
#include "Matrix/Matrix.h"

std::string _help(
        "\"print1\" to print first matrix\n"
        "\"print2\" to print second matrix\n"
        "\"fill1\" to fill first matrix\n"
        "\"fill2\" to fill second matrix\n"
        "\"add\" to add 1 and 2 matrixes\n"
        "\"sub\" to sub 1 and 2 matrixes\n"
        "\"mul\" to mul 1 and 2 matrixes\n"
        "\"exit\" to exit the program\n"
);

int main() {
    Matrix *m1 = new Matrix(0.0);
    Matrix *m2 = new Matrix(0.0);

    std::cout << "enter \"help\" to get help" << std::endl;
    while (true) {
        std::string s;
        std::getline(std::cin, s);

        if (s == "help") {
            std::cout << _help;
        }

        if (s == "print1") {
            std::cout << *m1;
        }

        if (s == "print2") {
            std::cout << *m2;
        }

        if (s == "fill1") {
            std::cout << "enter matrix as a string" << std::endl;
            std::string matrix_string;
            std::getline(std::cin, matrix_string);
            try {
                Matrix *m = new Matrix(matrix_string);
                delete m1;
                m1 = m;
            } catch (std::exception &e) {
                //!!! only if matrix throw std::exeptions
                std::cout << e.what() << std::endl;
            }
        }

        if (s == "fill2") {
            std::cout << "enter matrix as a string" << std::endl;
            std::string matrix_string;
            std::getline(std::cin, matrix_string);
            try {
                Matrix *m = new Matrix(matrix_string);
                delete m2;
                m2 = m;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (s == "add") {
            try {
                std::cout << *m1 + *m2;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (s == "sub") {
            try {
                std::cout << *m1 - *m2;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (s == "mul") {
            try {
                std::cout << *m1 * *m2;
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (s == "exit") {
            break;
        }
    }
}
