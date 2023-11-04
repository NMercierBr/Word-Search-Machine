CFLAGS = -Wall -g

#
# Link
#

bin/WordSearchMachine: obj/file.o obj/hash.o obj/main.o
	gcc -o bin/WordSearchMachine obj/file.o obj/hash.o obj/main.o

#
# Objets of TP Lists
#

obj/file.o: src/file.c include/types.h include/functions.h
	gcc  $(CFLAGS) -c src/file.c -I./include -o obj/file.o

obj/hash.o: src/hash.c include/functions.h
	gcc  $(CFLAGS) -c src/hash.c -I./include -o obj/hash.o
	
obj/main.o: src/main.c include/types.h include/functions.h
	gcc  $(CFLAGS) -c src/main.c -I./include -o obj/main.o
	
#
# Listing creation in pdf
#

listing:
	a2ps -o listing.ps include/types.h include/functions.h src/file.c src/hash.c src/main.c
	ps2pdf listing.ps
	rm listing.ps

#
# Remove files
#

clean :
	rm obj/*.o
	rm bin/WordSearchMachine

#
# Test the functionality 
#

rapide :
	make -f Makefile
	./bin/WordSearchMachine < test/serietest.txt
#testeur

test :
	make -f Makefile
	make listing
	make clean
