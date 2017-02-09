# protofun
> Clang plugin to get all the C/C++ function prototypes and their location.

## Setup

Just launch make and copy libprotofun.so file where you want.

## Usage

You need to touch a file /tmp/protofun.lock to be used as a lock when writing in the result file:
```sh
clang++-3.9 -fplugin=/path/to/libprotofun.so -Xclang -plugin-arg-protofun -Xclang /root/dir/of/your/project -Xclang -plugin-arg-protofun -Xclang /tmp/results.txt" -Xclang -plugin-arg-protofun -Xclang /tmp/protofun.lock ...
```
