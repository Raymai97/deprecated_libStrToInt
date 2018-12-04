/*
	StrToInt is a header-only library.
	By default, it defines a static function called StrToInt.
	By #define you may define
		the function name,
		the pointer to const char type,
		the integer type,
		the signness of the integer type.
	As such, it may be included more than once.

	For string like "0x1234", caller must provide "1234".
	For string like "-123,456", caller must provide "-123456".
	String like "00123" will be treated as "123".
	This design is intentional, to give maximum control to caller.
	e.g. Is thousand separator acceptable? Is "0x" acceptable?
	
	On success:
		The function returns positive value after set the parsed integer to *pInt.
		If return value is non-zero, it is (iBadChar + 1).
		Example: If "123 456" is given, *pInt = 123, return (3 + 1).
	
	On error:
		The function returns negative value such as StrToInt_errOverflow.
*/

#ifndef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToInt
#endif

#ifndef STRTOINT_PCSTRTYPE
#define STRTOINT_PCSTRTYPE  char const *
#endif

#ifndef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  int
#endif

#ifndef STRTOINT_SIGNED
#define STRTOINT_SIGNED  (1)
#endif

#ifndef STRTOINT__CHARDIGIT
#define STRTOINT__CHARDIGIT
static int StrToInt__CharDigit(int c, int radix)
{
	switch (radix) {
	case 16: return
		(c >= '0' && c <= '9') ? (c - '0') :
		(c >= 'a' && c <= 'f') ? (c - 'a') + 10 :
		(c >= 'A' && c <= 'F') ? (c - 'A') + 10 : -1;
	case 10: return
		(c >= '0' && c <= '9') ? (c - '0') : -1;
	case 8: return
		(c >= '0' && c <= '7') ? (c - '0') : -1;
	case 2: return
		(c >= '0' && c <= '1') ? (c - '0') : -1;
	}
	return -1;
}
#endif/* STRTOINT__CHARDIGIT */

#ifndef STRTOINT__ERR_ENUM
#define STRTOINT__ERR_ENUM
enum {
	StrToInt_errOverflow = -1,
	StrToInt_errUnderflow = -2,
	StrToInt_errBadArg = -3,
	StrToInt_errBadRadix = -4
};
#endif/* STRTOINT__ERR_ENUM */

#ifndef CHAR_BIT
#define STRTOINT__ASSUME_CHAR_BIT
#define CHAR_BIT  (8)
#endif

static int
STRTOINT_FUNCNAME(
	STRTOINT_PCSTRTYPE const pszStr,
	/* if (< 0) then assume strlen<char_t>(pszStr) */ int cchStr,
	STRTOINT_INTTYPE * const pInt,
	/* 2 (bin) / 8 (oct) / 10 (dec) / 16 (hex) */ int const radix)
{
	typedef STRTOINT_INTTYPE rInt;
	rInt theInt = 0;
#if (STRTOINT_SIGNED)
	rInt const rIntMin = (rInt)-1 << (sizeof(rInt) * CHAR_BIT - 1);
	rInt const rIntMax = ~rIntMin;
#else
	rInt const rIntMax = (rInt)~0;
#endif
	int iStr = 0;
	if (!pszStr || !pInt) {
		return StrToInt_errBadArg;
	}
	if (radix != 2 && radix != 8 && radix != 10 && radix != 16) {
		return StrToInt_errBadRadix;
	}
	if (cchStr < 0) {
		for (cchStr = 0; pszStr[cchStr]; ++cchStr);
	}
#if (STRTOINT_SIGNED)
	if (radix == 10 && pszStr[0] == '-') {
		for (iStr = 1; iStr < cchStr; ++iStr) {
			int const d = StrToInt__CharDigit(pszStr[iStr], radix);
			if (d < 0) goto onBadChar;
			if (theInt < rIntMin / (rInt)radix) {
				return StrToInt_errUnderflow;
			}
			theInt *= (rInt)radix;
			if (theInt < rIntMin + (rInt)d) {
				return StrToInt_errUnderflow;
			}
			theInt -= (rInt)d;
		}
		*pInt = theInt;
		return 0;
	}
#endif
	for (iStr = 0; iStr < cchStr; ++iStr) {
		int const d = StrToInt__CharDigit(pszStr[iStr], radix);
		if (d < 0) goto onBadChar;
		if (theInt > rIntMax / (rInt)radix) {
			return StrToInt_errOverflow;
		}
		theInt *= (rInt)radix;
		if (theInt > rIntMax - (rInt)d) {
			return StrToInt_errOverflow;
		}
		theInt += (rInt)d;
	}
	*pInt = theInt;
	return 0;
onBadChar:
	*pInt = theInt;
	return /* iBadChar */ iStr + 1;
}

#if defined(STRTOINT__ASSUME_CHAR_BIT)
#undef CHAR_BIT
#endif
