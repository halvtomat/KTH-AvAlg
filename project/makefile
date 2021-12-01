CFLAGS = -O2

%.o: %.cpp 
	g++ -c -o $@ $< $(CFLAGS)

main: main.o helper.o greedy.o opt2.o christofides.o
	g++ -o main main.o helper.o greedy.o opt2.o christofides.o

clean:
	rm *.o main
