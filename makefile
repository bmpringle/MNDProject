mac:
	rm a.out; g++ -std=c++2a main.cpp
windows:
	rm a.exe; x86_64-w64-mingw32-g++ -static -static-libstdc++ -static-libgcc -std=c++2a main.cpp