CC=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=-lcrypto++
SOURCES= CBC.cpp cipher.cpp interface.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=CBC

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm *.hex *.bin *.o $(EXECUTABLE)
