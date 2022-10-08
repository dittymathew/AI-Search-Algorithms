all : hello
hello : main.o solution.o simulate.o hillclimb.o iteratedhc.o beamsearch.o
		g++ main.o solution.o simulate.o hillclimb.o iteratedhc.o beamsearch.o -o tsp
main.o : main.cpp tsp.h
		g++ -c main.cpp
solution.o : solution.cpp
		g++ -c solution.cpp
simulate.o : simulate.cpp
		g++ -c simulate.cpp
hillclimb.o : hillclimb.cpp
		g++ -c hillclimb.cpp
iteratedhc.o : iteratedhc.cpp
		g++ -c iteratedhc.cpp
beamsearch.o : beamsearch.cpp
		g++ -c beamsearch.cpp

clean:
	rm -rf main.o
	rm -rf solution.o
	rm -rf simulate.o
	rm -rf hillclimb.o
	rm -rf iteratedhc.o
	rm -rf beamsearch.o
