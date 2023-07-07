.PHONY: clean
all:
	mkdir -p ./bin
	gcc -O3 ./src/battle.c ./src/cmd.c ./src/event.c ./src/file.c ./src/main.c ./src/utils.c -o ./bin/fist
clean:
	rm -f ./bin/fist
