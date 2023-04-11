GCPP = g++

laba1: main.cpp tree.o tree.h
	$(GCPP) main.cpp tree.o -o $@
clean:
	-rm -f *.o
	-rm -f laba1

tree.o: tree.cpp tree.h
	$(GCPP) -c $< -o $@
