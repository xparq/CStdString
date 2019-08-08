#!/bin/sh

# Ignored with MSYS2: set CXXFLAGS=...

# Disable warning "right/left operand of comma op. has no effect" for NDEBUG TRACE
# with -Wno-unused-value!

case "$1" in

	1)
	g++ -std=c++14 -DUNICODE    -D_UNICODE -Wall -pedantic -Wextra -Wno-unused-value TestString.cpp
	;;

	2)
	g++ -std=c++17 -DUNICODE -g -D_UNICODE -Wall -pedantic -Wextra -Wno-unused-value TestString.cpp
	;;

	3)
	g++ -std=c++14 -Wall    -pedantic -Wextra -Wno-unused-value TestString.cpp
	;;

	4)
	g++ -std=c++17 -Wall -g -pedantic -Wextra -Wno-unused-value TestString.cpp
	;;
esac
