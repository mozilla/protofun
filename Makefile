CXXFLAGS := -fPIC -O2 -std=c++11
INC := -I/usr/lib/llvm-3.9/include
SRCS = protofun.cpp

TMPDIR = /tmp
LOCK_FILE = $(TMPDIR)/mylock
RES_FILE = $(TMPDIR)/result.txt
ROOT = `pwd`/

CLANGPP = clang++-3.9
CLANGPP_FLAGS = -std=c++11 -fsyntax-only
CLANGPP_OPTS = -fplugin=./libprotofun.so -Xclang -plugin-arg-protofun -Xclang $(ROOT) -Xclang -plugin-arg-protofun -Xclang $(RES_FILE) -Xclang -plugin-arg-protofun -Xclang $(LOCK_FILE)

build: libprotofun.so

protofun.o: $(SRCS)
	$(CXX) $(CXXFLAGS) $(INC) -c $^ -o $@

libprotofun.so: protofun.o
	$(CXX) -shared $^ -o $@

clean:
	$(RM) libprotofun.so *.o

test: libprotofun.so
	touch $(LOCK_FILE)
	$(CLANGPP) $(CLANGPP_FLAGS) $(CLANGPP_OPTS) -c tests/foo.cpp
	$(RM) $(LOCK_FILE)
	diff $(RES_FILE) tests/foo.ref

	$(RM) $(RES_FILE)

.PHONY: build clean
