rc restest.rc

set CL=/nologo /EHsc /W4

if not x%1x==xx goto %1

rem Varying the /MT and /MD and ...d flags a bit, just to hopefully cover a wider base. :)

:1
cl /std:c++latest TestString.cpp restest.res & if not x%1x==xx goto :eof
:2
cl /std:c++latest /MD TestString.cpp restest.res & if not x%1x==xx goto :eof
:3
cl /std:c++latest /DUNICODE /D_UNICODE TestString.cpp restest.res & if not x%1x==xx goto :eof
:4
cl /std:c++latest /MT /DUNICODE /D_UNICODE TestString.cpp restest.res & if not x%1x==xx goto :eof

:5
cl /std:c++17 TestString.cpp restest.res & if not x%1x==xx goto :eof
:6
cl /std:c++17 /DUNICODE /D_UNICODE TestString.cpp restest.res & if not x%1x==xx goto :eof

:7
cl /std:c++14 /MDd TestString.cpp restest.res & if not x%1x==xx goto :eof
:8
cl /std:c++17 /MTd TestString.cpp restest.res & if not x%1x==xx goto :eof
:9
cl /std:c++latest /MDd TestString.cpp restest.res & if not x%1x==xx goto :eof

:10
cl /std:c++14 /MDd /DUNICODE /D_UNICODE TestString.cpp restest.res & if not x%1x==xx goto :eof
:11
cl /std:c++17 /MTd /DUNICODE /D_UNICODE TestString.cpp restest.res & if not x%1x==xx goto :eof
:12
cl /std:c++latest /MTd /DUNICODE /D_UNICODE TestString.cpp restest.res & if not x%1x==xx goto :eof
