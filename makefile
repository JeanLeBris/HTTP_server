exe: HTTP_server.exe HTTP_client.exe

debug_server: debug_server.exe debug_client.exe



HTTP_server.exe: obj/server.o obj/functions.o obj/config.o log obj dobj
	gcc -Wall obj/server.o obj/functions.o obj/config.o -o HTTP_server.exe -l ws2_32

HTTP_client.exe: obj/client.o obj/functions.o obj/config.o log obj dobj
	gcc -Wall obj/client.o obj/functions.o obj/config.o -o HTTP_client.exe -l ws2_32

obj/server.o: src/server.c obj
	gcc -Wall -c src/server.c -o obj/server.o -l ws2_32

obj/client.o: src/client.c obj
	gcc -Wall -c src/client.c -o obj/client.o -l ws2_32

obj/functions.o: src/functions.c obj
	gcc -Wall -c src/functions.c -o obj/functions.o -l ws2_32

obj/config.o: src/config.c obj
	gcc -Wall -c src/config.c -o obj/config.o -l ws2_32



debug_server.exe: dobj/server.o dobj/functions.o dobj/config.o log obj dobj
	gcc -g -Wall dobj/server.o dobj/functions.o dobj/config.o -o debug_server.exe

debug_client.exe: dobj/client.o dobj/functions.o dobj/config.o log obj dobj
	gcc -g -Wall dobj/client.o dobj/functions.o dobj/config.o -o debug_client.exe

dobj/server.o: src/server.c dobj
	gcc -g -Wall src/server.c -o dobj/server.o

dobj/client.o: src/client.c dobj
	gcc -g -Wall src/client.c -o dobj/client.o

dobj/functions.o: src/functions.c dobj
	gcc -g -Wall src/functions.c -o dobj/functions.o

dobj/config.o: src/config.c dobj
	gcc -g -Wall src/config.c -o dobj/config.o



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