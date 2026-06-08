all:
	mkdir -p build
	gcc -o ./build/hello ./src/main.c -Wall
clean:
	rm -r ./build/*
run:
	./build/hello
