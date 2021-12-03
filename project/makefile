CFLAGS = -O2 -std=gnu++17 -g -static

%.o: %.cpp 
	g++ -c -o $@ $< $(CFLAGS)

main: main.o helper.o greedy.o opt2.o
	g++ -o main main.o helper.o greedy.o opt2.o

clean:
	rm *.o main
