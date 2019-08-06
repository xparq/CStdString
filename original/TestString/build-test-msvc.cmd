set CL=/nologo /EHsc

cl /std:c++14     /DUNICODE /D_UNICODE TestString.cpp StdAfx.cpp  
cl /std:c++17     /DUNICODE /D_UNICODE TestString.cpp StdAfx.cpp  
cl /std:c++latest /DUNICODE /D_UNICODE TestString.cpp StdAfx.cpp  
goto :eof

cl /std:c++14     TestString.cpp StdAfx.cpp  
cl /std:c++17     TestString.cpp StdAfx.cpp  
cl /std:c++latest TestString.cpp StdAfx.cpp  
