#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <assert.h>
GenericMatrix Matrix::copy() const override{
	int rows = this->num_rows;
	int cols = this->num_cols;
	float** arr = new float*[this->num_rows];
	for ( int i = 0; i < this->num_rows; i++) {
		arr[i] = new float[this->num_cols];
		for (int j = 0; j < this->num_cols; j++) {
			arr[i][j] = this->matrix[i][j];
		}
	}
	return CachedMatrix(arr, rows, cols);
}


GenericMatrix Matrix::transpose() const override{
	return CachedMatrix(this->transposed_matrix, this->num_cols, this->num_rows);
}


GenericMatrix Matrix::matmul(const Matrix &mat) const override{
	assert(this->num_cols == mat.num_rows);
	return this->cachedMatmul(mat.getInternalTransposedArray(), mat.getCols());
}


GenericMatrix Matrix::matmul(float const* const* const &mat, int rows, int cols) const override{
	assert(rows == this->num_cols);
	float** transposed_matrix = new float*[cols];
	for (int i = 0; i < cols; i++) {
		transposed_matrix[i] = new float[rows];
		for (int j = 0; j < rows; j++) {
			transposed_matrix[i][j] = mat[j][i];
		}
	}
	return this->cachedMatmul(transposed_matrix, cols);
}


void Matrix::print() const{
	printf("[");
	for (int i = 0; i < this->num_rows; i++) {
		printf("[");
		for (int j = 0; j < this->num_cols; j++) {
			if (j == this->num_cols-1)
				printf("%4.2f", this->matrix[i][j]);
			else
				printf("%4.2f, ", this->matrix[i][j]);
		}
		if (i == this->num_rows-1)
			printf("]");
		else
			printf("], ");
	}
	printf("]\n");
}


void Matrix::print(float const* const* const &arr, int num_rows, int num_cols) {
	printf("[");
	for (int i = 0; i < num_rows; i++) {
		printf("[");
		for (int j = 0; j < num_cols; j++) {
			if (j == num_cols-1)
				printf("%4.2f", arr[i][j]);
			else
				printf("%4.2f, ", arr[i][j]);
		}
		if (i == num_rows-1)
			printf("]");
		else
			printf("], ");
	}
	printf("]\n");
}


void Matrix::set(const Matrix &mat) {
	this->set(mat.matrix, mat.num_rows, mat.num_cols);
}


void Matrix::set(float const* const* const &mat, int rows, int cols) {
	if (rows >= 0 && cols >= 0) {
		delete this->matrix;
		this->num_rows = rows;
		this->num_cols = cols;
		this->matrix = new float*[rows];
		for (int i = 0; i < rows; i++) {
			this->matrix[i] = new float[cols];
			for (int j = 0; j < cols; j++) {
				this->matrix[i][j] = mat[i][j];
			}
		}
		this->makeInternalTransposedMatrix();
	}
	
}


float** Matrix::get() const {
	float** matcopy = new float*[this->num_rows];
	for (int i = 0; i < this->num_rows; i++) {
		matcopy[i] = new float[this->num_cols];
		for (int j = 0; j < this->num_cols; j++) {
			matcopy[i][j] = this->matrix[i][j];
		}
	}
	return matcopy;
}


int Matrix::getRows() const { return this->num_rows; }


int Matrix::getCols() const { return this->num_cols; }


float Matrix::dotProduct(float const* const &arr1, float const* const &arr2, int size) {
	if (size == -1) {
        throw std::invalid_argument("size error");
        return 0;
	}
	float sum = 0;
	for (int i = 0; i < size; i++) {
		sum += arr1[i] * arr2[i];
	}
	return sum;
}


Matrix Matrix::cachedMatmul(float const* const* const &transposed_array, int original_number_columns) const {
	float** result = new float*[this->num_rows];

	for (int i = 0; i < this->num_rows; i++) {
		result[i] = new float[original_number_columns];
		for (int j = 0; j < original_number_columns; j++) {
			float product = Matrix::dotProduct(this->matrix[i], transposed_array[j], this->num_cols);
			result[i][j] = product;

		}
	}
	return Matrix(result, this->num_rows, original_number_columns);
}


float** Matrix::getInternalTransposedArray() const{
	return this->transposed_matrix;
}