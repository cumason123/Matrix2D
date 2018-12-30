make:
	g++ -c ./Main.cpp -o ./Main.o
	g++ -c ./Matrix/Matrix.cpp -o ./Matrix/Matrix.o
	g++ -c ./Matrix/ThreadedMatrix/ThreadedMatrix.cpp -o ./Matrix/ThreadedMatrix/ThreadedMatrix.o

	ar rcs ./Matrix/libmatrix.a ./Matrix/Matrix.o ./Matrix/ThreadedMatrix/ThreadedMatrix.o
	g++ -o Main Main.o -L./Matrix -lmatrix
	./Main