#include <limits.h>

#if defined(ULLONG_MAX) && !defined(TEST_NO_LLONG)
typedef unsigned long long UMAX;
#define UMAX_MAX  ULLONG_MAX
#define UMAX_PRI  "%llu"
#define UMAX_PRIx "%llx"
typedef long long SMAX;
#define SMAX_MAX  LLONG_MAX
#define SMAX_MIN  LLONG_MIN
#define SMAX_PRI  "%lld"

#elif defined(_WIN32) && !defined(TEST_NO_I64)
typedef unsigned __int64 UMAX;
#define UMAX_MAX  _UI64_MAX
#define UMAX_PRI  "%I64u"
#define UMAX_PRIx "%I64x"
typedef __int64 SMAX;
#define SMAX_MAX  _I64_MAX
#define SMAX_MIN  _I64_MIN
#define SMAX_PRI  "%I64d"

#else
typedef unsigned long UMAX;
#define UMAX_MAX  ULONG_MAX
#define UMAX_PRI  "%lu"
#define UMAX_PRIx "%lx"
typedef long SMAX;
#define SMAX_MAX  LONG_MAX
#define SMAX_MIN  LONG_MIN
#define SMAX_PRI  "%ld"

#endif

/********** Include StrToInt for unsigned integer **********/

#undef STRTOINT_SIGNED
#define STRTOINT_SIGNED  (0)

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToUChar
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  unsigned char
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToUShort
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  unsigned short
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToUInt
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  unsigned int
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToULong
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  unsigned long
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToUMax
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  UMAX
#include <raymai/StrToInt.h>

/********** Include StrToInt for signed integer **********/

#undef STRTOINT_SIGNED
#define STRTOINT_SIGNED  (1)

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToSChar
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  signed char
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToShort
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  short
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToInt
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  int
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToLong
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  long
#include <raymai/StrToInt.h>

#undef STRTOINT_FUNCNAME
#define STRTOINT_FUNCNAME  StrToSMax
#undef STRTOINT_INTTYPE
#define STRTOINT_INTTYPE  SMAX
#include <raymai/StrToInt.h>

/*********************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DECL(VarT, Var) \
	int err; char sz[99]; VarT Var

static void sChar10(void)
{
	DECL(signed char, sc);

	sc = 0; sprintf(sz, "%d", SCHAR_MAX);
	err = StrToSChar(sz, -1, &sc, 10);
	assert(err == 0 && sc == SCHAR_MAX);

	sc = 0; sprintf(sz, "%d", SCHAR_MIN);
	err = StrToSChar(sz, -1, &sc, 10);
	assert(err == 0 && sc == SCHAR_MIN);

	sc = 0; sprintf(sz, "%d", (int)SCHAR_MAX + 1);
	err = StrToSChar(sz, -1, &sc, 10);
	assert(err == StrToInt_errOverflow && sc == 0);

	sc = 0; sprintf(sz, "%d", (int)SCHAR_MIN - 1);
	err = StrToSChar(sz, -1, &sc, 10);
	assert(err == StrToInt_errUnderflow && sc == 0);
}

static void sShort10(void)
{
	DECL(short, ss);

	ss = 0; sprintf(sz, "%d", SHRT_MAX);
	err = StrToShort(sz, -1, &ss, 10);
	assert(err == 0 && ss == SHRT_MAX);

	ss = 0; sprintf(sz, "%d", SHRT_MIN);
	err = StrToShort(sz, -1, &ss, 10);
	assert(err == 0 && ss == SHRT_MIN);

#if INT_MAX > SHRT_MAX
	ss = 0; sprintf(sz, "%d", (int)SHRT_MAX + 1);
#elif SHRT_MAX == 32767
	ss = 0; sprintf(sz, "32768");
#else
#error "Bad SHRT_MAX"
#endif
	err = StrToShort(sz, -1, &ss, 10);
	assert(err == StrToInt_errOverflow && ss == 0);

#if INT_MIN < SHRT_MIN
	ss = 0; sprintf(sz, "%d", (int)SHRT_MIN - 1);
#elif SHRT_MIN == -32768
	ss = 0; sprintf(sz, "-32769");
#else
#error "Bad SHRT_MIN"
#endif
	err = StrToShort(sz, -1, &ss, 10);
	assert(err == StrToInt_errUnderflow && ss == 0);
}

static void sInt10(void)
{
	DECL(int, si);

	si = 0; sprintf(sz, "%d", INT_MAX);
	err = StrToInt(sz, -1, &si, 10);
	assert(err == 0 && si == INT_MAX);

	si = 0; sprintf(sz, "%d", INT_MIN);
	err = StrToInt(sz, -1, &si, 10);
	assert(err == 0 && si == INT_MIN);

#if LONG_MAX > INT_MAX
	si = 0; sprintf(sz, "%ld", (long)INT_MAX + 1);
#elif INT_MAX == 2147483647
	si = 0; sprintf(sz, "2147483648");
#else
#error "Bad INT_MAX"
#endif
	err = StrToInt(sz, -1, &si, 10);
	assert(err == StrToInt_errOverflow && si == 0);

#if LONG_MIN < INT_MIN
	si = 0; sprintf(sz, "%ld", (long)INT_MIN - 1);
#elif INT_MIN == -2147483648
	si = 0; sprintf(sz, "-2147483649");
#else
#error "Bad INT_MIN"
#endif
	err = StrToInt(sz, -1, &si, 10);
	assert(err == StrToInt_errUnderflow && si == 0);
}

static void sLong10(void)
{
	DECL(long, sl);

	sl = 0; sprintf(sz, "%ld", LONG_MAX);
	err = StrToLong(sz, -1, &sl, 10);
	assert(err == 0 && sl == LONG_MAX);

	sl = 0; sprintf(sz, "%ld", LONG_MIN);
	err = StrToLong(sz, -1, &sl, 10);
	assert(err == 0 && sl == LONG_MIN);

#if SMAX_MAX > LONG_MAX
	sl = 0; sprintf(sz, SMAX_PRI, (SMAX)LONG_MAX + 1);
#elif LONG_MAX == 2147483647
	sl = 0; sprintf(sz, "2147483648");
#else
#error "Bad LONG_MAX"
#endif
	err = StrToLong(sz, -1, &sl, 10);
	assert(err == StrToInt_errOverflow && sl == 0);

#if SMAX_MIN < LONG_MIN
	sl = 0; sprintf(sz, SMAX_PRI, (SMAX)LONG_MIN - 1);
#elif LONG_MIN == -2147483648
	sl = 0; sprintf(sz, "-2147483649");
#else
#error "Bad LONG_MIN"
#endif
	err = StrToLong(sz, -1, &sl, 10);
	assert(err == StrToInt_errUnderflow && sl == 0);
}

static void sMax10(void)
{
	DECL(SMAX, sm);

	sm = 0; sprintf(sz, SMAX_PRI, SMAX_MAX);
	err = StrToSMax(sz, -1, &sm, 10);
	assert(err == 0 && sm == SMAX_MAX);

	sm = 0; sprintf(sz, SMAX_PRI, SMAX_MIN);
	err = StrToSMax(sz, -1, &sm, 10);
	assert(err == 0 && sm == SMAX_MIN);
}

static void uChar10(void)
{
	DECL(unsigned char, uc);

	uc = 0; sprintf(sz, "%u", UCHAR_MAX);
	err = StrToUChar(sz, -1, &uc, 10);
	assert(err == 0 && uc == UCHAR_MAX);

	uc = 0; sprintf(sz, "%u", (unsigned int)UCHAR_MAX + 1);
	err = StrToUChar(sz, -1, &uc, 10);
	assert(err == StrToInt_errOverflow && uc == 0);
}

static void uChar16(void)
{
	DECL(unsigned char, uc);

	uc = 0; sprintf(sz, "%x", UCHAR_MAX);
	err = StrToUChar(sz, -1, &uc, 16);
	assert(err == 0 && uc == UCHAR_MAX);

	uc = 0; sprintf(sz, "%x", (unsigned int)UCHAR_MAX + 1);
	err = StrToUChar(sz, -1, &uc, 16);
	assert(err == StrToInt_errOverflow && uc == 0);
}

static void uShort10(void)
{
	DECL(unsigned short, us);

	us = 0; sprintf(sz, "%u", USHRT_MAX);
	err = StrToUShort(sz, -1, &us, 10);
	assert(err == 0 && us == USHRT_MAX);

#if UINT_MAX > USHRT_MAX
	us = 0; sprintf(sz, "%u", (unsigned int)USHRT_MAX + 1);
#elif USHRT_MAX == 65535
	us = 0; sprintf(sz, "65536");
#else
#error "Bad SHRT_MAX"
#endif
	err = StrToUShort(sz, -1, &us, 10);
	assert(err == StrToInt_errOverflow && us == 0);
}

static void uShort16(void)
{
	DECL(unsigned short, us);

	us = 0; sprintf(sz, "%x", USHRT_MAX);
	err = StrToUShort(sz, -1, &us, 16);
	assert(err == 0 && us == USHRT_MAX);

#if UINT_MAX > USHRT_MAX
	us = 0; sprintf(sz, "%x", (unsigned int)USHRT_MAX + 1);
#elif USHRT_MAX == 0xffff
	us = 0; sprintf(sz, "1" "0000");
#else
#error "Bad SHRT_MAX"
#endif
	err = StrToUShort(sz, -1, &us, 16);
	assert(err == StrToInt_errOverflow && us == 0);
}

static void uInt10(void)
{
	DECL(unsigned int, ui);

	ui = 0; sprintf(sz, "%u", UINT_MAX);
	err = StrToUInt(sz, -1, &ui, 10);
	assert(err == 0 && ui == UINT_MAX);

#if ULONG_MAX > UINT_MAX
	ui = 0; sprintf(sz, "%lu", (unsigned long)UINT_MAX + 1);
#elif UINT_MAX == 4294967295
	ui = 0; sprintf(sz, "4""294""967""296");
#else
#error "Bad UINT_MAX"
#endif
	err = StrToUInt(sz, -1, &ui, 10);
	assert(err == StrToInt_errOverflow && ui == 0);
}

static void uInt16(void)
{
	DECL(unsigned int, ui);

	ui = 0; sprintf(sz, "%x", UINT_MAX);
	err = StrToUInt(sz, -1, &ui, 16);
	assert(err == 0 && ui == UINT_MAX);

#if ULONG_MAX > UINT_MAX
	ui = 0; sprintf(sz, "%lx", (unsigned long)UINT_MAX + 1);
#elif UINT_MAX == 0xffffffff
	ui = 0; sprintf(sz, "1" "0000" "0000");
#else
#error "Bad UINT_MAX"
#endif
	err = StrToUInt(sz, -1, &ui, 16);
	assert(err == StrToInt_errOverflow && ui == 0);
}

static void uLong10(void)
{
	DECL(unsigned long, ul);

	ul = 0; sprintf(sz, "%lu", ULONG_MAX);
	err = StrToULong(sz, -1, &ul, 10);
	assert(err == 0 && ul == ULONG_MAX);

#if UMAX_MAX > ULONG_MAX
	ul = 0; sprintf(sz, UMAX_PRI, (UMAX)ULONG_MAX + 1);
#elif ULONG_MAX == 4294967295
	ul = 0; sprintf(sz, "4""294""967""296");
#else
#error "Bad ULONG_MAX"
#endif
	err = StrToULong(sz, -1, &ul, 10);
	assert(err == StrToInt_errOverflow && ul == 0);
}

static void uLong16(void)
{
	DECL(unsigned long, ul);

	ul = 0; sprintf(sz, "%lx", ULONG_MAX);
	err = StrToULong(sz, -1, &ul, 16);
	assert(err == 0 && ul == ULONG_MAX);

#if UMAX_MAX > ULONG_MAX
	ul = 0; sprintf(sz, UMAX_PRIx, (UMAX)ULONG_MAX + 1);
#elif ULONG_MAX == 0xffffffff
	ul = 0; sprintf(sz, "1" "0000" "0000");
#else
#error "Bad ULONG_MAX"
#endif
	err = StrToULong(sz, -1, &ul, 16);
	assert(err == StrToInt_errOverflow && ul == 0);
}

static void uMax10(void)
{
	DECL(UMAX, um);

	um = 0; sprintf(sz, UMAX_PRI, UMAX_MAX);
	err = StrToUMax(sz, -1, &um, 10);
	assert(err == 0 && um == UMAX_MAX);

#if UMAX_MAX == 4294967295
	um = 0; sprintf(sz, "4""294""967""296");
#elif UMAX_MAX == 18446744073709551615
	um = 0; sprintf(sz, "18""446""744""073""709""551""616");
#else
#error "Bad UMAX_MAX"
#endif
	err = StrToUMax(sz, -1, &um, 10);
	assert(err == StrToInt_errOverflow && um == 0);
}

static void uMax16(void)
{
	DECL(UMAX, um);

	um = 0; sprintf(sz, UMAX_PRIx, UMAX_MAX);
	err = StrToUMax(sz, -1, &um, 16);
	assert(err == 0 && um == UMAX_MAX);

#if UMAX_MAX == 0xffffffff
	um = 0; sprintf(sz, "1" "0000" "0000");
#elif UMAX_MAX == 0xffffffffffffffff
	um = 0; sprintf(sz, "1" "0000" "0000" "0000" "0000");
#else
#error "Bad UMAX_MAX"
#endif
	err = StrToUMax(sz, -1, &um, 16);
	assert(err == StrToInt_errOverflow && um == 0);
}

int main(void)
{
	sChar10(); uChar10(); uChar16();
	sShort10(); uShort10(); uShort16();
	sInt10(); uInt10(); uInt16();
	sLong10(); uLong10(); uLong16();
	sMax10(); uMax10(); uMax16();
	return 0;
}
