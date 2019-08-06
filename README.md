# CStdString
Joe O'Leary's excellent (and >20-year-old...) drop-in replacement for MFC's CString, facelifted for contemporary C++.

## USAGE:

Just copy `CStdString.h` to a suitable place in your project, and:

    #include "CStdString.h"
    typedef CStdString CString; // CStdStringA, CStdStringW, CStdStringO are also available

## NOTE:

* The `original` folder is just the unpacked zip files published in Joe's 2011 [CodeProject article](https://www.codeproject.com/Articles/1146/CString-clone-Using-Standard-C)
(see below), added for easier browsing. It doesn't compile any more with recent compilers. (That's the reason of this facelifting project.)

* The updated version of the original `stdstring.h` is renamed to `CStdString.h` here.

* It has been test-compiled (building Joe's original test app) with MSVC 16.1 (Visual Studio 2019),
  both with and without `UNICODE` (and `_UNICODE`), and both for `c++14` and `c++17` (and `c++latest`,
  which is just `c++17` now, I guess).

* It has been successfully integrated into [my fork of Notepad++](https://github.com/lunakid/notepad-plusplus-gilded),
  replacing the original `CString` class there.

* GCC support has not been restored yet. (Tried, and failed, with MSYS2's 9.1. See `test/gcc-errors.log`.`)

* **WARNING:** NO OTHER TESTS have been performed, so there may very well be more unfixed deprecations left,
  or even new, exciting regressions, too. (Fixes: on-demand. Note: this is pretty much obsolete legacy code,
  kept alive only for replacing even more obsolete legacy code, and its primarily purpose is to aid
  transition/migration *away from* old code-bases, to things that no longer need the CString class.)

* The links to Joe's old sites in the original header and the article are dead.

### A copy of Joe's CodeProject article:

-----------------------------------------------------------------------------
# CString-clone Using Standard C++
Joe O'Leary, 7 Dec 2011

A Drop-In replacement for CString that builds on the Standard C++ Library's basic_string template

 -> Download *[HIS ORIGINAL!]* [source files - 33.5 KB](https://raw.githubusercontent.com/lunakid/CStdString/master/original/StdString_src.zip)
 
 -> Download *[HIS ORIGINAL!]* [demo project - 27.8 KB](https://raw.githubusercontent.com/lunakid/CStdString/master/original/StdString_demo.zip)

## Introduction

As much as I use and appreciate the Standard C++ Library, I've never liked its string template - basic_string<>. At times, it seems the designers went out of their way to make it difficult to use.

On the other hand, I've always loved the ease of use of MFC's CString class. It checks for NULL pointers, implicitly converts to const TCHAR*, and has some very handy member functions (Format, Load, etc.) that make string programming a breeze. But of course, I don't want to use MFC anymore. In fact, I don't want to rely on any proprietary library because I want portability.

Therefore I decided to combine the best of both worlds and create:

## CStdString

This is a class (a template instantiation actually) that derives from from basic_string<TCHAR>. To the basic_string it adds the entire CString API. You get CString ease of use with 100% basic_string compatibility. In short, a CStdString object is a basic_string that (with very few exceptions (noted below) it is also a drop-in replacement for CString. The best part of this is that both APIs (basic_string and CString) are well known and well documented.

I originally submitted this article to another code site (which shall remain nameless :)) a few years ago. I like CodeProject so much I thought I'd submit it here too. I have used this class in almost every professional project I've done over the past 4 years. It has proven to be the single most useful piece of code I've ever written. It is also extensively debugged. I hope you like it. If you ever have any problems with it, please e-mail me. I'm happy to help.

I provided a simple source application here to prove some of the CString functions work but it's really just a token. The list of sample projects out there that use CString and/or basic_string is massive.

## Features

Drop in Replacement for CString (see below for exceptions)
Two instantiations available at all times -- wchar_t-based version CStdStringW and char-based version CStdStringA. The name CStdString is just a typedef of one of these two.
Safely checks for NULL string pointer inputs (like CString) in all functions
Extra constructors and assignment operators to automatically convert between wide (wchar_t-based) and thin (char-based) strings for you.
Implicit conversion to c_str(). The C++ committee doesn't like this but I sure do.
Builds on several platforms, including Windows, Unix and Linux. Works with several implementations of the Standard C++ Library, including Dinkumware, GNU, CodeWarrior, and STLPort.
Win32 builds give you some extra goodies like UNICODE/MBCS conversion macros (just like MFCs) as well as member functions for persisting CStdString objects to and from DCOM IStreams.
Makes no use of any implementation details of the base class template (basic_string)
The derived template adds no member data to basic_string and adds no virtual functions
There are a couple of issues about this code of that I should point out.

## CString Compatibility

I was unable to exactly reproduce the CString API. There are a two functions that both CString and basic_string; share, but implement differently. In these cases, I felt it best to make CStdString behave like basic_string (the base class) rather than CString. To be specific.

CStdString::operator[] returns characters by value (unlike CString which returns them by reference)
The constructor that takes a character and a count takes them in the order (count, value) which is the opposite of the order CString declares them. That's the order that basic_string<>; needs and it was impossible to implement both versions.
There were also two CString functions I could not implement at all -- LockBuffer and UnlockBuffer.

## Deriving From basic_string<>

The template I wrote derives from basic_string, a class template without a virtual destructor. Any introductory text to C++ will tell you that it is dangerous to derive from a class without a virtual destructor. It can lead to behavior that is undefined. So if you were to code the following (deleting a CStdStringA through a pointer to the base class), you would technically get undefined behavior:

// assign DERIVED object to  BASE pointer
std::string* pstr = new CStdStringA("Hi"); 

// delete  DERIVED through BASE class pointer -- UNDEFINED
delete pstr;   
Personally, I don't think this is much of an issue. I mean really how often do you actually do this with string objects? I have rarely (if ever) needed to dynamically allocate a string object on the heap. And if I ever do, I won't using a base-class pointer. So if you don't do this, you'll never have to worry. In fact, even if you do code this way, I doubt you'll have any problems with CStdString. I can tell you that at least with Microsoft Visual C++, even the above code runs just fine with no errors or memory leaks. I doubt many other compilers would give you problems either. However my doubt does not impose reality on the C++ world. Caveat Emptor.

--------------------
## History
7 Dec 2011: Updated source code.

--------------------
## License
This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)

---------------------
## About the Author

Joe O'Leary - Web Developer, United States

I've been a software developer since 1990.

While my main page is out of date (and I have therefore blanked it),
you can read about the CStdString pages here

http://home.earthlink.net/~jmoleary/stdstring.htm *[DEAD LINK!]*
