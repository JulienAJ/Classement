Classement: main.o classement.o
	g++ -O2 $^ -o Classement 

main.o: main.cpp
	g++ -c $^

classement.o: classement.cpp classement.hpp
	g++ -c $<
	
clean:
	@rm -rf *.o

run: Classement 
