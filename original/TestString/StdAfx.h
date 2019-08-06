// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6A224A0B_7769_4B7A_AE2C_444918A23E26__INCLUDED_)
#define AFX_STDAFX_H__6A224A0B_7769_4B7A_AE2C_444918A23E26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Turn off some common warnings that are generated en-masse
// by the Microsoft STL implementation headers.

#pragma warning ( disable : 4018 ) // signed/unsigned mismatch
//#pragma warning ( disable : 4097 ) // typedef name used as synonym for class name
#pragma warning ( disable : 4100 ) // unreferenced formal parameter
//#pragma warning ( disable : C4146 )	// unary minus operator applied to unsigned type, result still unsigned
#pragma warning ( disable : 4211 ) // nonstandard extension used : redefined extern as static
#pragma warning ( disable : 4244 ) // conversion from A to B, possible loss of data
#pragma warning ( disable : 4245 ) // initializing conversion signed/unsigned mismatch
#pragma warning ( disable : 4251 ) // class <x> needs to have dll-interface to be used by clients of class <y>
#pragma warning ( disable : 4310 ) // cast truncates constant value (comutil.h gives this one a lot).
#pragma warning ( disable : 4511 ) // private constructors are OK
#pragma warning ( disable : 4512 ) // private operator=() are OK
#pragma warning ( disable : 4663 ) // C++ Language change -- new syntax for explicit specialization of templates.
#pragma warning ( disable : 4786 ) // symbolic name too long : truncated to 255 characters
#pragma warning ( disable : 4290 ) // C++ Exception Specification ignored


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6A224A0B_7769_4B7A_AE2C_444918A23E26__INCLUDED_)
