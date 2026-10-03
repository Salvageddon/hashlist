srctarget = src/source/hashlist.c
dlltarget = ./hashlist.dll

maintarget = src/source/main.c

all: build run

build:
	gcc -shared ${srctarget} -o ${dlltarget}

run:
	gcc ${maintarget} -o ./test -L. -lhashlist
	./test