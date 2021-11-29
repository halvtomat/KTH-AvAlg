CFLAGS = -O2

%.o: %.cpp 
	g++ -c -o $@ $< $(CFLAGS)

christofides: christofides.o helper.o opt2.o
	g++ -o christofides christofides.o helper.o opt2.o

main: main.o helper.o greedy.o opt2.o
	g++ -o main main.o helper.o greedy.o opt2.o

clean:
	rm *.o main
