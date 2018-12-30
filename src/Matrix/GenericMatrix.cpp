#include "./GenericMatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <assert.h>
float** MatrixMath::linspace2d(int num_rows, int num_cols) {
	float** pointer2 = new float*[num_rows];
	for (int i = 0; i < num_rows; i++) {
		pointer2[i] = new float[num_cols];
		for (int j = 0; j < num_cols; j++) {
			pointer2[i][j] = j;
		}
	}
}



GenericMatrix::GenericMatrix()
	: num_rows(0), num_cols(0), matrix(NULL), transposed_matrix(NULL) 
{

}


GenericMatrix::GenericMatrix(float const* const* const &mat, int rows, int cols) 
	: transposed_matrix(NULL)
{
	if (rows < 0 || cols < 0) {
		this->num_rows = 0;
		this->num_cols = 0;
		this->matrix = NULL;
	} else {
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


GenericMatrix::~GenericMatrix() {
	for (int i = 0; i < this->num_rows; i++) {
		delete this->matrix[i];
	}
	delete this->matrix;
	delete this->transposed_matrix;
}


GenericMatrix GenericMatrix::copy() const {
	int rows = this->num_rows;
	int cols = this->num_cols;
	float** arr = new float*[this->num_rows];
	for ( int i = 0; i < this->num_rows; i++) {
		arr[i] = new float[this->num_cols];
		for (int j = 0; j < this->num_cols; j++) {
			arr[i][j] = this->matrix[i][j];
		}
	}
	return GenericMatrix(arr, rows, cols);
}


GenericMatrix GenericMatrix::transpose() const {
	return GenericMatrix(this->transposed_matrix, this->num_cols, this->num_rows);
}


void GenericMatrix::print() const{
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


void GenericMatrix::print(float const* const* const &arr, int num_rows, int num_cols) {
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


void GenericMatrix::set(const Matrix &mat) {
	this->set(mat.matrix, mat.num_rows, mat.num_cols);
}


void GenericMatrix::set(float const* const* const &mat, int rows, int cols) {
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


float** GenericMatrix::get() const {
	float** matcopy = new float*[this->num_rows];
	for (int i = 0; i < this->num_rows; i++) {
		matcopy[i] = new float[this->num_cols];
		for (int j = 0; j < this->num_cols; j++) {
			matcopy[i][j] = this->matrix[i][j];
		}
	}
	return matcopy;
}


int GenericMatrix::getRows() const { return this->num_rows; }


int GenericMatrix::getCols() const { return this->num_cols; }


GenericMatrix GenericMatrix::operator+(GenericMatrix& other) {
	// TODO bitwise operator which allows newMatrix to be passed into a new matrix
	// instead of copied reducing to 2n instead of 3n
	assert(this->num_rows == other.getRows() && this->num_cols == other.getCols());
	float** newMatrix = new float*[this->num_rows];
	for (int i = 0; i < this->num_rows; i++) {
		newMatrix[i] = new float[this->num_cols];
		for (int j = 0; j < this->num_cols; j++) {
			newMatrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
		}
	}
	return GenericMatrix(newMatrix, this->num_rows, this->num_cols);
}


GenericMatrix GenericMatrix::operator*(const GenericMatrix& other) const{
	return this->matmul(other);
}


float GenericMatrix::dotProduct(float const* const &arr1, float const* const &arr2, int size) {
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


void Matrix::makeInternalTransposedMatrix() {
	delete this->transposed_matrix;
	this->transposed_matrix = new float*[this->num_cols];
	for (int i = 0; i < this->num_cols; i++) {
		this->transposed_matrix[i] = new float[this->num_rows];
		for (int j = 0; j < this->num_rows; j++) {
			this->transposed_matrix[i][j] = this->matrix[j][i];
		}
	}
}


std::ostream& operator<<(std::ostream& stream, const GenericMatrix& other) {
	stream << '[';
	int num_rows = other.getRows();
	int num_cols = other.getCols();
	for (int i = 0; i < num_rows; i++) {
		stream << '[';
		for (int j = 0; j < num_cols; j++) {
			if (j == num_cols-1)
				stream << arr[i][j];
			else
				stream << arr[i][j] << ", ";
		}
		if (i == num_rows-1)
			stream << ']';
		else
			stream << "], ";
	}
	stream << "]\n";
}
