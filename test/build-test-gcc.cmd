:: Ignored with MSYS2: set CXXFLAGS=...

if not x%1x==xx goto %1

rem Disable warning "right/left operand of comma op. has no effect" for NDEBUG TRACE
rem with -Wno-unused-value.

:1
g++ -std=c++14 -DUNICODE    -D_UNICODE -Wall -pedantic -Wextra -Wno-unused-value TestString.cpp & if not x%1x==xx goto :eof
:2
g++ -std=c++17 -DUNICODE -g -D_UNICODE -Wall -pedantic -Wextra -Wno-unused-value TestString.cpp & if not x%1x==xx goto :eof

:3
g++ -std=c++14 -Wall    -pedantic -Wextra -Wno-unused-value TestString.cpp & if not x%1x==xx goto :eof
:4
g++ -std=c++17 -Wall -g -pedantic -Wextra -Wno-unused-value TestString.cpp & if not x%1x==xx goto :eof
