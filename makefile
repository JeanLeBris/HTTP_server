exe: HTTP_server.exe

debug: debug.exe



HTTP_server.exe: obj/main.o obj/functions.o log obj dobj
	gcc -Wall obj/main.o obj/functions.o -o HTTP_server.exe -l ws2_32

obj/main.o: src/main.c obj
	gcc -Wall -c src/main.c -o obj/main.o -l ws2_32

obj/functions.o: src/functions.c obj
	gcc -Wall -c src/functions.c -o obj/functions.o -l ws2_32



debug.exe: dobj/main.o dobj/functions.o log obj dobj
	gcc -g -Wall dobj/main.o dobj/functions.o -o debug.exe

dobj/main.o: src/main.c dobj
	gcc -g -Wall src/main.c -o dobj/main.o

dobj/functions.o: src/functions.c dobj
	gcc -g -Wall src/functions.c -o dobj/functions.o



log:
	mkdir log

obj:
	mkdir obj

dobj:
	mkdir dobj



clean:
	rm -r obj
	rm -r dobj

clear: clean
	rm -r log
	rm *.exe

zip:
	zip "HTTP_server.zip" src/*.c lib/*.c README.md makefile LICENSE