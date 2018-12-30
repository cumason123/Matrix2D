#include "./Matrix/Matrix.h"
#include "./Matrix/ThreadedMatrix/ThreadedMatrix.h"
#include <stdio.h>
#include <chrono>

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	{
		float** pointer1 = MatrixMath::linspace2d(4, 4);
		float** pointer2 = MatrixMath::linspace2d(4, 8);

		Matrix mat1(pointer1, 4, 4);
		Matrix mat2(pointer2, 4, 8);
		Matrix resultant = mat1.matmul(mat2);
		resultant.print();
	}
	auto stop = std::chrono::high_resolution_clock::now();
	return 0;
}