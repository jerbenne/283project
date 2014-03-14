CC=gcc
FLAGS=-I./src/
TARGETS=mp3
LIBS=-lm

main: $(TARGETS)


lib/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) lib/*.o

%:lib/loadFiles.o lib/markov.o lib/%.o
	$(CC) -o $@ $^ $(LIBS)
