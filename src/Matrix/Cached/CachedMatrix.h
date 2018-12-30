#ifndef MATRIX_H
#define MATRIX_H
#include "../GenericMatrix.h"

class CachedMatrix : GenericMatrix {
public:	
	GenericMatrix copy() const override; // deep copy
	CachedMatrix transpose() const override; // New Transposed Matrix

	virtual GenericMatrix matmul(const CachedMatrix &mat) const override; // this * mat
	virtual GenericMatrix matmul(float const* const* const &mat, 
		int rows, int cols) const override; 

	void print() const; // Prints Matrix
	static void print(float const* const* const &arr, int num_rows, int num_cols); // Prints 2d arr

	void set(const CachedMatrix& mat); 
	void set(float const* const* const &mat, int rows, int cols);

	float** get() const;

	int getRows() const;
	int getCols() const;

	static float dotProduct(float const* const &arr1, float const* const &arr2, int size);
private:
	virtual Matrix cachedMatmul(float const* const* const &transposed_array, 
		int original_number_columns) const;

	float** getInternalTransposedArray() const;

};
#endif