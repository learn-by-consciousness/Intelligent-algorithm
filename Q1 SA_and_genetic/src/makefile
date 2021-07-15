CC := g++				# compiler to use
CFLAGS := 				# compiling options
LDFLAGS :=

EXEC1 := ../bin/sa.out	# name of the executable
EXEC2 := ../bin/ls.out	# name of the executable

# all is the default rule
all: $(EXEC1) $(EXEC2)

# rule to generate the executable
$(EXEC1): method.o sa.o
	$(CC) -o $@ $^ 
$(EXEC2): method.o ls.o
	$(CC) -o $@ $^ 

# rule to  *.o
method.o: method.cpp parameter.h FileInfo.h
	$(CC) $(CFLAGS) -o $@ -c $<
# rule to generate *.o
sa.o: sa.cpp parameter.h FileInfo.h
	$(CC) $(CFLAGS) -o $@ -c $<
# rule to generate *.o
ls.o: ls.cpp parameter.h FileInfo.h
	$(CC) $(CFLAGS) -o $@ -c $<

# clean
.PHONY: clean
clean:
	rm -f *.o $(EXEC)
