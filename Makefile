all: a.out

a.out: main.o GoodReads.o Book.o User.o Author.o Shelf.o Review.o ReadData.o functions.o Interface.o
	g++ -std=c++11 main.o GoodReads.o Book.o User.o Author.o Shelf.o Review.o ReadData.o functions.o Interface.o

main.o: main.cpp GoodReads.hpp ReadData.hpp
	g++ -std=c++11 -c main.cpp

Interface.o: Interface.hpp GoodReads.hpp
	g++ -std=c++11 -c Interface.cpp

GoodReads.o: GoodReads.cpp GoodReads.hpp Book.hpp User.hpp Author.hpp ReadData.hpp functions.hpp
	g++ -std=c++11 -c GoodReads.cpp

Book.o: Book.cpp Book.hpp Author.hpp
	g++ -std=c++11 -c Book.cpp

User.o: User.cpp User.hpp Author.hpp Shelf.hpp Review.hpp functions.hpp
	g++ -std=c++11 -c User.cpp

Author.o: Author.cpp Author.hpp Book.hpp
	g++ -std=c++11 -c Author.cpp 

Review.o: Review.cpp Review.hpp 
	g++ -std=c++11 -c Review.cpp

ReadData.o: ReadData.cpp ReadData.hpp Book.hpp User.hpp Author.hpp
	g++ -std=c++11 -c ReadData.cpp

Shelf.o: Shelf.cpp Shelf.hpp Book.hpp
	g++ -std=c++11 -c Shelf.cpp

functions.o: functions.cpp functions.hpp Book.hpp
	g++ -std=c++11 -c functions.cpp 

clean:
	rm *.o
	rm a.out
