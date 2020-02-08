# protofun
> Clang plugin to get all the C/C++ function prototypes and their location.

## Setup

Just launch make and copy libprotofun.so file where you want.

## Usage

You need to touch a file /tmp/protofun.lock to be used as a lock when writing in the result file:
```sh
clang++-3.9 -fplugin=/path/to/libprotofun.so -Xclang -plugin-arg-protofun -Xclang /root/dir/of/your/project -Xclang -plugin-arg-protofun -Xclang /tmp/results.txt -Xclang -plugin-arg-protofun -Xclang /tmp/protofun.lock ...
```

## Example of output

For the file tests/foo.cpp, the results are (function proto | file | line number):
```
add<int>(int, int) | tests/foo.cpp | 2
add(int) | tests/foo.cpp | 7
A<double>::foo(double) | tests/foo.cpp | 16
A<double>::bar(double) | tests/foo.cpp | 17
A<char>::bar(char) | tests/foo.cpp | 17
A<char>::A() | tests/foo.cpp | 14
A<int>::foo(int) | tests/foo.cpp | 16
toto(const A<double> &) | tests/foo.cpp | 20
B::B() | tests/foo.cpp | 29
B::oof<char>(float, A<char> &) | tests/foo.cpp | 33
C<char, int>::C() | tests/foo.cpp | 43
C<short, long>::C() | tests/foo.cpp | 37
main(int, char **) | tests/foo.cpp | 49
```

