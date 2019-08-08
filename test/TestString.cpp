//----------------------------------------------------------------------------
// Smoke-testing Joe's CStdString.h...
// (Basically the same random stuff he left behind, but I've changed it quite
// a bit, while debugging etc.)
//----------------------------------------------------------------------------

//! Silence MSVC's infamous _vsnprintf warning...
//! CStdString does it anyway, but it's too late if Windows.h is included first:
//#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

// For testing some win32-specific features (should be tested separately!)
// BTW, this will be automatically enabled by CStdString.h if Windows.h
// is included prior to it.
//!! In fact, defining this here seems to trigger a segfault in GCC! :-o
//!! See: [SS_WIN32-gcc-crash]
//#define SS_WIN32 
#define SS_NO_LOCALE
#include "../CStdString.h"

#include <map>

#include <cassert>
#include <iostream>
using std::cout; using std::wcout; // using ..., ...; would fail in c++14

// Poor man's fallback _T() (see also: https://stackoverflow.com/a/15498147/1479945)
#ifndef _T
  #ifdef TEXT
    #define _T(str) TEXT(str)
  #else
    #ifdef UNICODE
      #define _T(str) L ## str
    #else
      #define _T(str) TEXT(str)
    #endif
  #endif
#endif

#include "resource.h"

//============================================================================
int main(int argc, char* argv[]) { argc, argv; // Silence pedantic warnings about these being unused...

	#ifdef __GNUC__
	void segv_handler(int sig);
	signal(SIGSEGV, segv_handler); // https://stackoverflow.com/a/77336/1479945
	#endif

	// Just so I can check sometimes that the ASSERT macro really is on:
	//ASSERT(1 == 2);

    try {
	// You can add just about any form of string to a CStdString
	// with operator+()
	CStdString strVal1(_T("THIS IS A STRING   "));
	//!!Not available for my MSYS2/MinGW/gcc:
	//!!strVal1 += _bstr_t(" plus a BSTR string");
	strVal1 += ' ';
	strVal1 += "And this is its tail.";
	OutputDebugString(strVal1 + _T(" [plus some temp. tail only for outputting it]\n"));
	cout <<           strVal1 + _T(" [plus some temp. tail only for outputting it]\n");

	// Some conversion functions can be chained together

	strVal1.ToLower().TrimRight();
	OutputDebugString(strVal1 + _T("\n"));
	cout <<           strVal1 + _T("\n");

	// Case INsensitive comparison via Equals() or CompareNoCase()

	strVal1 = _T("THIS IS A STRING");
	CStdString strVal2(_T("thIs Is a sTRing"));
	ASSERT(strVal1 != strVal2);
	ASSERT(strVal1.Equals(strVal2));
	ASSERT(strVal1.CompareNoCase(strVal2) == 0);

	// Format() works just like CString's

	strVal1.Format(_T("This is a %s string, with a num. param: %d"), _T("*FORMATTED*"), 123);
	OutputDebugString(strVal1 + _T("\n"));
	cout <<           strVal1 + _T("\n");

	// Declare an STL map class which maps strings to integers.  The
	// keys are case insensitive, so an integer stored under the key
	// _T("MYKEY") could be retrieved with the value _T("mykey")

	typedef std::map<CStdString, int, StdStringLessNoCase> CMyMap;
	CMyMap myMap;
	myMap[_T("MYKEY")] = 7;
	ASSERT(myMap.find(_T("mykey")) != myMap.end());


#ifdef SS_WIN32
	// If we were calling some windows function that fills out a
	// buffer for us we can use the GetBuffer() function.

	CStdString strPath;
	::GetTempPath( MAX_PATH, strPath.GetBuffer(MAX_PATH+1));
	strPath.ReleaseBuffer();

	// You can set the resource handle for loading string resources
	// and then load them via either the constructor or the Load()
	// function.
	// These required SS_WIN32 to be #defined!
	CStdString::SetResourceHandle(::GetModuleHandle(NULL));
	CStdString strString(MAKEINTRESOURCE(IDS_STRING1));
	ASSERT(_T("All your base are belong to us!") == strString);

	strString.Load(IDS_STRING2);
	ASSERT(_T("I see dead people") == strString);
#endif
    } catch (...) {
	cout << "OOPS!\n";
    }

}

/*
	// If this were MFC code, we could serialize the strings to CArchives:

	void  CMyObject::Serialize(CArchive& ar)
	{
		CStdString strVal3(_T("This is a string"));
		if ( ar.IsStoring() )
			ar << strVal;
		else
			ar >> strVal;
	}

	// If we were implementing the IPersistStream interface on a COM
	// object which had a member CStdString variable named 'm_strVal',
	// we could take advantage of the CStdString stream functions to
	// greatly simplify the implementation as follows:

	HRESULT CMyComObject::GetSizeMax(ULARGE_INTEGER* pcbSizeMax)
	{
		pcbSizeMax->QuadPart = m_strVal.StreamSize();
		return S_OK;
	}
	HRESULT CMyComObject::Save(IStream* pStream, BOOL bClearDirty)
	{
		return m_strVal.StreamSave(pStream);
	}
	HRESULT CMyComObject::Load(IStream* pStream)
	{
		return m_strVal.StreamLoad(pStream);
	}

*/


//-------------------------------------------------------------------------------
//!! Aborted attempt to print a stack trace with MSYS2/MinGW...
//!! (Found somewhere on SO, I guess, but couldn't adopt for the missing backtrace())
#ifdef __GNUC__
#include <stdio.h>
//#include <backtrace.h> //!!no backtrace() in MSYS2/MinGW?!... :-o :-/
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void segv_handler(int sig) {
  //void *array[10];
  // Get void*'s for all entries on the stack:
  //size_t size = backtrace(array, 10);
  // Print all the frames to stderr:
  fprintf(stderr, "Error: signal %d caught!\n", sig);
  //backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(-1);
}
#endif
