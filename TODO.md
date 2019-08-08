! GCC won't compile it, if Windows.h is not included before CStdString.h.
  Maybe that's OK, but MSVC does that without a hitch.

!![SS_WIN32-gcc-crash] Segfault with gcc...

  (It's not the cout/wchar misuse, that's just the likely reason of garbled output.
  When commented out, it still crashed.)

  -> All these with Windows.h being included first (GCC currently won't compile otherwise.)
     "no SS_WIN32" means it's not *explicitly* defined before including SS:

  Explicitly defining SS_WIN32 seems to trigger the crash, EVEN IF Windows.h is
  *included BEFORE* CStdString.h, even though that should render SS_WIN32 redundant.
  (And the trivial suspicion that it may use something depending on SS_WIN32 *before*
  its auto-enbling logic kicks in, proved to be a dead-end.)


	no SS_WIN32, no SS_NO_LOCALE,    UNICODE	ASSERT fail: ~878, NO output
	no SS_WIN32, no SS_NO_LOCALE, no UNICODE	OK! (output OK, no crash)
	no SS_WIN32,    SS_NO_LOCALE,    UNICODE	debug-out: Format() GARBLED, cout: pointers, no crash
	no SS_WIN32,    SS_NO_LOCALE, no UNICODE	OK! (output OK, no crash)

	SS_WIN32, no SS_NO_LOCALE,    UNICODE		ASSERT fail: ~878
	SS_WIN32, no SS_NO_LOCALE, no UNICODE		!!CRASH!!
	SS_WIN32,    SS_NO_LOCALE,    UNICODE		!!CRASH!!, out: Format() GARBLED
	SS_WIN32,    SS_NO_LOCALE, no UNICODE		!!CRASH!!, output OK

  - "Garbled" output means that e.g. the Format()ed test output is wrong: 
	Instead of: "This is a *FORMATTED* string, with a num. param: 123",
	it shows: "This is a * string, with a num. param: 123".

- NO CRASH, if:

      1. CStdString.h is included BEFORE Windows.h

      2. SS_WIN32 is NOT defined!
         Note: if defined, albeit looks redundant, it DOES trigger the crash,
         BUT now the formatter output IS CORRECT!...

Anyway, since I can't reproduce that crash with MSVC, or with SS_WIN32 *not*
defined, I have to conclude for now, that the problem lies somewhere near the
fact that my MSYS2/MinGW is not a proper Win32 env: GCC there doesn't even
define __MINGW64__ or  __MINGW64__ (why?! I only saw __MSYS__).

! Assertion fails in the VS build with locales (i.e. without SS_NO_LOCALE):
	line ~878: ASSERT(SSCodeCvt::ok == res);

+ GCC build falters spectacularly on SS_NO_LOCALE. (MSVC's happy.)
  Fixed.

* No cout << op. support in unicode mode?! (It just dumps the pointer.)

* The gcc build fails with SS_NO_LOCALE, without SS_WIN32 (i.e. when
Windows.h is not included beforehand, or SS_WIN32 is not explicitly
defined).
