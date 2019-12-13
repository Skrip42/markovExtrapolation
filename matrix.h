#ifndef Markov_Matrix_H
#define Markov_Matrix_H

#include <iostream>
#include <exception>

class Matrix
{
    public:
        Matrix(int, int, float**);
        Matrix(int, int);
        Matrix(std::istream&);
        Matrix(const Matrix&);
        ~Matrix();
        void set(float**);
        void set(int, int, float);
        void set(std::istream&);
        float get(int, int);
        int getSizeR();
        int getSizeC();
        void empty();

        static Matrix getSimple(int);
        float* operator[] (const int);
        Matrix operator- () const;
        Matrix& operator= (const Matrix&);
        
        friend std::ostream& operator<< (std::ostream&, const Matrix&);
        friend Matrix operator* (const Matrix&, const Matrix&);
        friend Matrix operator* (const Matrix&, float);
        friend Matrix operator* (float, const Matrix&);
        friend Matrix operator+ (const Matrix&, const Matrix&);
        friend Matrix operator- (const Matrix&, const Matrix&);
        friend Matrix T(const Matrix&);
        friend float det(const Matrix&);
        friend Matrix minor(const Matrix&, int, int);
        friend Matrix inv(const Matrix&);
        friend Matrix alg_d(const Matrix&);
        friend Matrix pow(const Matrix&, int);
    private:
        float** matrix;
        int matrix_size_c;
        int matrix_size_r;
        void init();
};

class MatrixException : public std::exception {
    public:
        MatrixException() : _reason("unknown") {}
        explicit MatrixException(const std::string& what) : _reason(what) {}
        virtual ~MatrixException() throw () {};
        virtual const char* what() const throw () { return _reason.c_str(); }

    private:
        std::string _reason;
};

#endif
