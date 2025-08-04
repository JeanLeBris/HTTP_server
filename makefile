export OS
export CC=gcc
export CFLAGS= -Wall
export LDFLAGS= -Wall
export SERVER_EXEC=HTTP_server
export CLIENT_EXEC=HTTP_client
SRCNAMES= functions.c config.c
SERVER_SRCNAMES= $(SRCNAMES) server.c
CLIENT_SRCNAMES= $(SRCNAMES) client.c
export SRCDIR=src
SERVER_SRC= $(foreach srcname, $(SERVER_SRCNAMES), $(SRCDIR)/$(srcname))
CLIENT_SRC= $(foreach srcname, $(CLIENT_SRCNAMES), $(SRCDIR)/$(srcname))
SERVER_OBJNAMES= $(SERVER_SRCNAMES:.c=.o)
CLIENT_OBJNAMES= $(CLIENT_SRCNAMES:.c=.o)
export OBJDIR=obj
SERVER_OBJ= $(foreach objname, $(SERVER_OBJNAMES), $(OBJDIR)/$(objname))
CLIENT_OBJ= $(foreach objname, $(CLIENT_OBJNAMES), $(OBJDIR)/$(objname))
export BINDIR=bin
export DEPENDENCIES=
LOGDIR=log

ifeq ($(OS), Windows)
	RMDIR= rmdir
	RMFILE= del /s /q
	COPYFILE= copy
	SHARED_LIBRARY_EXT= dll
	CFLAGS+= -l ws2_32
	LDFLAGS+= -l ws2_32
	FILE_SLASH=\\

else
ifeq ($(OS), Windows_NT)
	OS=Windows
	RMDIR= rmdir
	RMFILE= del /s /q
	COPYFILE= copy
	SHARED_LIBRARY_EXT= dll
	CFLAGS+= -l ws2_32
	LDFLAGS+= -l ws2_32
	FILE_SLASH=\\

else
ifeq ($(OS), Linux)
	RMDIR= rmdir
	RMFILE= rm
	COPYFILE= cp
	SHARED_LIBRARY_EXT= so
	FILE_SLASH=/
endif
endif
endif

export RMDIR
export RMFILE
export COPYFILE
export SHARED_LIBRARY_EXT
export FILE_SLASH

ifeq ($(LIBRARY_TYPE), shared)
else
	ifeq ($(LIBRARY_TYPE), static)
	else
		LIBRARY_TYPE=shared
	endif
endif
export LIBRARY_TYPE

ifeq ($(DEBUG), true)
	CFLAGS+= -g
	LDFLAGS+= -g
endif

compile:bin obj $(SERVER_OBJNAMES) $(CLIENT_OBJNAMES)
	$(CC) $(SERVER_OBJ) $(LDFLAGS) -o $(SERVER_EXEC)
	$(CC) $(CLIENT_OBJ) $(LDFLAGS) -o $(CLIENT_EXEC)

%.o:
	$(CC) -c $(SRCDIR)/$(@:.o=.c) $(CFLAGS) -o $(OBJDIR)/$@

.PHONY: compile clean

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	$(RMFILE) $(OBJDIR)$(FILE_SLASH)*
	$(RMDIR) $(OBJDIR)
	$(RMFILE) $(BINDIR)$(FILE_SLASH)*
	$(RMDIR) $(BINDIR)
	$(RMFILE) $(LOGDIR)$(FILE_SLASH)*
	$(RMDIR) $(LOGDIR)
	$(RMFILE) *.exe






# exe: HTTP_server.exe HTTP_client.exe

# debug_server: debug_server.exe debug_client.exe



# HTTP_server.exe: obj/server.o obj/functions.o obj/config.o log obj dobj
# 	gcc -Wall obj/server.o obj/functions.o obj/config.o -o HTTP_server.exe -l ws2_32

# HTTP_client.exe: obj/client.o obj/functions.o obj/config.o log obj dobj
# 	gcc -Wall obj/client.o obj/functions.o obj/config.o -o HTTP_client.exe -l ws2_32

# obj/server.o: src/server.c obj
# 	gcc -Wall -c src/server.c -o obj/server.o -l ws2_32

# obj/client.o: src/client.c obj
# 	gcc -Wall -c src/client.c -o obj/client.o -l ws2_32

# obj/functions.o: src/functions.c obj
# 	gcc -Wall -c src/functions.c -o obj/functions.o -l ws2_32

# obj/config.o: src/config.c obj
# 	gcc -Wall -c src/config.c -o obj/config.o -l ws2_32



# debug_server.exe: dobj/server.o dobj/functions.o dobj/config.o log obj dobj
# 	gcc -g -Wall dobj/server.o dobj/functions.o dobj/config.o -o debug_server.exe

# debug_client.exe: dobj/client.o dobj/functions.o dobj/config.o log obj dobj
# 	gcc -g -Wall dobj/client.o dobj/functions.o dobj/config.o -o debug_client.exe

# dobj/server.o: src/server.c dobj
# 	gcc -g -Wall src/server.c -o dobj/server.o

# dobj/client.o: src/client.c dobj
# 	gcc -g -Wall src/client.c -o dobj/client.o

# dobj/functions.o: src/functions.c dobj
# 	gcc -g -Wall src/functions.c -o dobj/functions.o

# dobj/config.o: src/config.c dobj
# 	gcc -g -Wall src/config.c -o dobj/config.o



# log:
# 	mkdir log

# obj:
# 	mkdir obj

# dobj:
# 	mkdir dobj



# clean:
# 	rm -r obj
# 	rm -r dobj

# clear: clean
# 	rm -r log
# 	rm *.exe

# zip:
# 	zip "HTTP_server.zip" src/*.c lib/*.c README.md makefile LICENSE