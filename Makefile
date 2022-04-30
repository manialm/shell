SRC=shell

all: main
	@./out/$(SRC)

main: src/$(SRC).c
	@gcc src/$(SRC).c -o out/$(SRC)