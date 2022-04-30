SRC=shell

INCLUDEDIR = ./include/

FLAGS = -I $(INCLUDEDIR)

all: main
	@out/$(SRC)

main: src/$(SRC).c
	@mkdir -p out/
	@gcc $(FLAGS) src/$(SRC).c -o out/$(SRC)