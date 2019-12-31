#include "iostream"
#include "matrix.h"
#include <math.h>

int main(void)
{
    int i, j, siz, offset, step;
    std::cout << "enter entity count: ";
    std::cin >> siz;
    Matrix::Matrix transition(siz, siz);
    Matrix::Matrix initial(1, siz);
    std::cout << "\nenter transition matrix:\n";
    transition.set(std::cin);
    std::cout << "\nenter initial state vector:\n";
    initial.set(std::cin);
    std::cout << "\nenter start offset: ";
    std::cin >> offset;
    std::cout << "\nenter step count: ";
    std::cin >> step;
    std::cout << "\n\n";
    Matrix::Matrix extrapolate = pow(transition, offset);
    Matrix::Matrix state = initial * extrapolate;
    for (i = 0; i < step; i++) {
        std::cout << "step " << offset + i << ":\t";
        for (j = 0; j < siz; j++) {
            //std::cout << state;
            std::cout << round(state.get(0, j) * 100) / 100 << "\t";
        }
        extrapolate = extrapolate * transition;
        state = initial * extrapolate;
        std::cout << "\n";
    }
    return EXIT_SUCCESS;
}
