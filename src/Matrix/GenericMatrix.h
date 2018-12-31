#ifndef GENERICMATRIX_H
#define GENERICMATRIX_H
#include <iostream>


namespace MatrixMath {
	float** linspace2d(int num_rows, int num_cols);
}


template<class MatrixType>
class GenericMatrix {
	GenericMatrix();
	GenericMatrix(float const* const* const &mat, int rows, int cols);
	GenericMatrix(MatrixType& other);
	virtual ~GenericMatrix() = 0;
	
	MatrixType transpose() const; // New Transposed Matrix
	
	virtual MatrixType matmul(const MatrixType &mat) const = 0; // this * mat
	virtual MatrixType matmul(float const* const* const &mat, int rows, int cols) const = 0; 

	void print() const; // Prints Matrix
	static void print(float const* const* const &arr, int num_rows, int num_cols); // Prints 2d arr

	void set(const MatrixType& mat); 
	void set(float const* const* const &mat, int rows, int cols);

	float** get() const;

	int getRows() const;
	int getCols() const;

	GenericMatrix operator+(const MatrixType& other) const;
	virtual GenericMatrix operator*(const MatrixType& other) const;

	static float dotProduct(float const* const &arr1, float const* const &arr2, int size);

protected:
	float** matrix;
	int num_rows;
	int num_cols;
	float** transposed_matrix;
	void makeInternalTransposedMatrix();

};

std::ostream& operator<<(std::ostream& stream, const GenericMatrix& other);
#endif