#ifndef GENERICMATRIX_H
#define GENERICMATRIX_H
#include <iostream>
namespace MatrixMath {
	float** linspace2d(int num_rows, int num_cols);
}

class GenericMatrix {
	GenericMatrix();
	GenericMatrix(float const* const* const &mat, int rows, int cols);
	virtual ~GenericMatrix() = 0;
	
	virtual GenericMatrix copy() const; // deep copy
	virtual GenericMatrix transpose() const; // New Transposed Matrix

	
	virtual GenericMatrix matmul(const GenericMatrix &mat) const = 0; // this * mat
	virtual GenericMatrix matmul(float const* const* const &mat, int rows, int cols); 

	void print() const; // Prints Matrix
	static void print(float const* const* const &arr, int num_rows, int num_cols); // Prints 2d arr

	void set(const GenericMatrix& mat); 
	void set(float const* const* const &mat, int rows, int cols);

	float** get() const;

	int getRows() const;
	int getCols() const;

	GenericMatrix operator+(const GenericMatrix& other) const;
	GenericMatrix operator*(const GenericMatrix& other) const;

	static float dotProduct(float const* const &arr1, float const* const &arr2, int size);

protected:
	float** matrix;
	int num_rows;
	int num_cols;
	float** transposed_matrix;
	void Matrix::makeInternalTransposedMatrix();

};

std::ostream& operator<<(std::ostream& stream, const GenericMatrix& other);
#endif