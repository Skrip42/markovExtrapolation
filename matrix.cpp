#include "matrix.h"
#include <iostream>

Matrix::Matrix(int num_r, int num_c, float **mtr)
{
    matrix_size_r = num_r;
    matrix_size_c = num_c;
    init();
    set(mtr);
}

Matrix::Matrix(int num_r, int num_c)
{
    matrix_size_r = num_r;
    matrix_size_c = num_c;
    init();
}

Matrix::Matrix(std::istream &is)
{
    is >> matrix_size_r;
    is >> matrix_size_c;
    init();
    int r, c;
    for (r = 0; r < matrix_size_r; r++) {
        for (c = 0; c < matrix_size_c; c++) {
            is >> matrix[r][c];
        }
    }
}

Matrix::Matrix(const Matrix& m)
{
    matrix_size_r = m.matrix_size_r;
    matrix_size_c = m.matrix_size_c;
    int r, c;
    matrix = new float* [matrix_size_r];
    for (r = 0; r < matrix_size_r; r++) {
        matrix[r] = new float[matrix_size_c];
        for (c = 0; c < matrix_size_c; c++) {
            matrix[r][c] = m.matrix[r][c];
        }
    }
}

void Matrix::init()
{
    if (matrix_size_r == 1 && matrix_size_c == 1) {
        throw new MatrixException("its no matrix!");
    }
    matrix = new float* [matrix_size_r];
    int r, c;
    for (r = 0; r < matrix_size_r; r++) {
        matrix[r] = new float[matrix_size_c];
        for (c = 0; c < matrix_size_c; c++) {
            matrix[r][c] = 0;
        }
    }
}

void Matrix::empty()
{
    int r,c;
    for (r = 0; r < matrix_size_r; r++) {
        for (c = 0; c < matrix_size_c; c++) {
            set(r, c, 0);
        }
    }
}

Matrix Matrix::getSimple(int r)
{
    Matrix mr(r,r);
    int i;
    for (i = 0; i < r; i++) {
        mr.set(i, i, 1);
    }
    return mr;
}

void Matrix::set(float **mtr)
{
    int r,c;
    for (r = 0; r < matrix_size_r; r++) {
        for (c = 0; c < matrix_size_c; c++) {
            set(r, c, mtr[r][c]);
        }
    }
}

void Matrix::set(int num_r, int num_c, float val)
{
    matrix[num_r][num_c] = val;
}

void Matrix::set(std::istream &is)
{
    int r, c;
    for (r = 0; r < matrix_size_r; r++) {
        for (c = 0; c < matrix_size_c; c++) {
            is >> matrix[r][c];
        }
    }
}

float Matrix::get(int r, int c)
{
    return matrix[r][c];
}

int Matrix::getSizeC()
{
    return matrix_size_c;
}

int Matrix::getSizeR()
{
    return matrix_size_r;
}

Matrix::~Matrix()
{
    int r;
    for (r = 0; r < matrix_size_r; r++) {
        delete [] matrix[r];
    }
    delete [] matrix;
}

Matrix& Matrix::operator= (const Matrix& m)
{
    matrix_size_r = m.matrix_size_r;
    matrix_size_c = m.matrix_size_c;
    int r, c;
    matrix = new float* [matrix_size_r];
    for (r = 0; r < matrix_size_r; r++) {
        matrix[r] = new float[matrix_size_c];
        for (c = 0; c < matrix_size_c; c++) {
            matrix[r][c] = m.matrix[r][c];
        }
    }
    return *this;
}

float* Matrix::operator[] (const int i)
{
    return matrix[i];
}

Matrix Matrix::operator- () const
{
    int r, c;
    Matrix mr(matrix_size_r, matrix_size_c);
    for (r = 0; r < matrix_size_r; r++) {
        for (c = 0; c < matrix_size_c; c++) {
            mr[r][c] = -matrix[r][c];
        }
    }
    return mr;
}


Matrix operator* (const Matrix &m, float a)
{
    Matrix mr(m.matrix_size_r, m.matrix_size_c);
    int r, c;
    for (r = 0; r < m.matrix_size_r; r++) {
        for (c = 0; c < m.matrix_size_c; c++) {
            mr[r][c] = m.matrix[r][c] * a;
        }
    }
    
    return mr; 
}

Matrix operator* (float a, const Matrix &m)
{
    return m * a;
}

Matrix operator* (const Matrix &m1, const Matrix &m2)
{
    if (m1.matrix_size_c != m2.matrix_size_r) {
        throw MatrixException("Uncorect size of myltiply matrix!");
    }
    Matrix mr(m1.matrix_size_r, m2.matrix_size_c);
    int r, c;
    int i;
    float val;

    for (r = 0; r < m1.matrix_size_r; r++) {
        for (c = 0; c < m2.matrix_size_c; c++) {
            val = 0;
            for (i = 0; i < m1.matrix_size_c; i++) {
                val += m1.matrix[r][i] * m2.matrix[i][c];
            }
            mr[r][c] = val;
        }
    }
    return mr;
}

Matrix operator+ (const Matrix &m1, const Matrix &m2)
{
    if (m1.matrix_size_r != m2.matrix_size_r || m1.matrix_size_c != m2.matrix_size_c) {
        throw MatrixException("matrix size is not equal!");
    }
    Matrix mr(m1.matrix_size_r, m2.matrix_size_c);
    int r, c;
    for (r = 0; r < m1.matrix_size_r; r++) {
        for (c = 0; c < m1.matrix_size_c; c++) {
            mr[r][c] = m1.matrix[r][c] + m2.matrix[r][c];
        }
    }
    return mr;
}

Matrix operator- (const Matrix &m1, const Matrix &m2)
{
    if (m1.matrix_size_r != m2.matrix_size_r || m1.matrix_size_c != m2.matrix_size_c) {
        throw MatrixException("matrix size is not equal!");
    }
    Matrix mr(m1.matrix_size_r, m2.matrix_size_c);
    int r, c;
    for (r = 0; r < m1.matrix_size_r; r++) {
        for (c = 0; c < m1.matrix_size_c; c++) {
            mr[r][c] = m1.matrix[r][c] - m2.matrix[r][c];
        }
    }
    return mr;
}

Matrix pow(const Matrix& m, int a)
{
    Matrix mr = Matrix::getSimple(m.matrix_size_r);
    Matrix mt = m;
    do {
        if (a & 1) {
            mr = mr * mt;
        }
        mt = mt * mt;
    } while ((a = a >> 1));
    return mr;
}

Matrix T(const Matrix& m)
{
    Matrix mr(m.matrix_size_c, m.matrix_size_r);
    int r, c;
    for (r = 0; r < m.matrix_size_r; r++) {
        for (c = 0; c < m.matrix_size_c; c++) {
            mr[c][r] = m.matrix[r][c];
        }
    }
    return mr;
}

float det(const Matrix& m)
{
    if (m.matrix_size_r != m.matrix_size_c) {
        throw MatrixException("matrix not squared");
    }
    if (m.matrix_size_r == 2) {
        return m.matrix[0][0] * m.matrix[1][1] - m.matrix[1][0] * m.matrix[0][1];
    }
    if (m.matrix_size_r == 3) {
        return m.matrix[0][0] * m.matrix[1][1] * m.matrix[2][2]
            + m.matrix[0][1] * m.matrix[1][2] * m.matrix[2][0]
            + m.matrix[0][2] * m.matrix[1][0] * m.matrix[2][1]
            - m.matrix[0][2] * m.matrix[1][1] * m.matrix[2][0]
            - m.matrix[0][0] * m.matrix[1][2] * m.matrix[2][1]
            - m.matrix[0][1] * m.matrix[1][0] * m.matrix[2][2];
    }
    int nullinrow[m.matrix_size_r]; 
    int nullincol[m.matrix_size_c];
    int i;
    for (i = 0; i < m.matrix_size_r; i++) {
        nullinrow[i] = 0;
        nullincol[i] = 0;
    }
    int maxnullrow = 0;
    int maxnullcol = 0;
    int r,c;
    for (r = 0; r < m.matrix_size_r; r++) {
        for (c = 0; c < m.matrix_size_c; c++) {
            if (!m.matrix[r][c]) {
                nullinrow[r]++;
                nullincol[c]++;
                if (nullinrow[r] > nullinrow[maxnullrow])
                    maxnullrow = r;
                if (nullincol[c] > nullincol[maxnullcol])
                    maxnullcol = c;
            }
        }
    }
    float deter = 0;
    int sign = 1;

    if (nullinrow[maxnullrow] > nullinrow[maxnullcol]) {
        if (maxnullrow % 2) sign = -1;
        for (i = 0; i < m.matrix_size_r; i++) {
            if (m.matrix[maxnullrow][i]) {
                deter += sign * m.matrix[maxnullrow][i] * det(minor(m, maxnullrow, i));
            }
            sign *= -1;
        }
    } else {
        if (maxnullcol % 2) sign = -1;
        for (i = 0; i < m.matrix_size_r; i++) {
            if (m.matrix[i][maxnullcol]) {
                deter += sign * m.matrix[i][maxnullcol] * det(minor(m, i, maxnullcol));
            }
            sign *= -1;
        }
    }
    return deter;
}

Matrix inv(const Matrix& m)
{
    if (m.matrix_size_r != m.matrix_size_c) {
        throw MatrixException("matrix not squared");
    }
    return T(alg_d(m) * (1 / det(m)));
}

Matrix alg_d(const Matrix& m)
{
    if (m.matrix_size_r != m.matrix_size_c) {
        throw MatrixException("matrix not squared");
    }
    Matrix mr(m.matrix_size_r, m.matrix_size_c);
    int r, c;
    int sign = 1;
    for (r = 0; r < m.matrix_size_r; r++) {
        for (c = 0; c < m.matrix_size_c; c++) {
            mr.set(r, c, sign * det(minor(m, r, c)));
            sign *= -1;
        }
    }
    return mr;
}

Matrix minor(const Matrix& m, int row, int col)
{
    Matrix mr(m.matrix_size_r - 1, m.matrix_size_c - 1);
    int sr, rr, sc, rc;
    for (rr = 0, sr = 0; sr < m.matrix_size_r; sr++) {
        if (sr == row) continue;
        for (sc = 0, rc = 0; sc < m.matrix_size_c; sc++) {
            if (sc == col) continue;
            mr[rr][rc] = m.matrix[sr][sc];
            rc++;
        }
        rr++;
    }
    return mr;
}

std::ostream& operator<< (std::ostream &out, const Matrix &matrix)
{
    out << "\n";
    out << matrix.matrix_size_r << " " << matrix.matrix_size_c << "\n";
    int r, c;
    for (r = 0; r < matrix.matrix_size_r; r++) {
        for (c = 0; c < matrix.matrix_size_c; c++) {
            out << matrix.matrix[r][c];
            if (c != matrix.matrix_size_c - 1) out << " ";
        }
        out << "\n";
    }
    out << "\n";
    return out;
}
