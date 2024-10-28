.PHONY: all release clean

RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS   = -g -O0 -Wall
RELEASE_EXEC1  = MD5
SOURCE1        = MD5.cpp

all: release
 

release: $(RELEASE_EXEC1)

$(RELEASE_EXEC1): $(SOURCE1)
	g++ $(RELEASE_FLAGS) $(SOURCE1) -o $(RELEASE_EXEC1) -lcrypto++

clean:
	rm -f $(RELEASE_EXEC1)
