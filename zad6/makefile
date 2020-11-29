DEPS=zad6main.o matma.o funkcje.o

zad6main: $(DEPS)
	gcc $^ -o $@ -lm -Wall --pedantic

%.o:%.c
	gcc -c $^ -o $@

clean:
	rm  zad6main
	rm  *.o
