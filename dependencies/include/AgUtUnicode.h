/******************************************************************************/
/*****           Copyright 2009-2012, Analytical Graphics, Inc.           *****/
/******************************************************************************/
#ifndef __AgUtUnicode_H
#define __AgUtUnicode_H


#if defined(__cplusplus)
#ifndef AGI_COMPONENTSz
#include <atlbase.h>
#endif
#include <string>
#include <stdexcept>
#endif

#include <stdlib.h>
#include <malloc.h>
#if defined(__cplusplus)
#include <memory>	// AGI_Linux_
#else
#include <memory.h>
#include <wtypes.h>
#endif

#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC_UNICODE__ __FILE__ "(" __STR1__(__LINE__)") : UNICODE WARNING : "
#if defined(__GNUC__)
#define AgMUnicodeWarning(msg) 
#else
#define AgMUnicodeWarning(msg) __pragma(message(__LOC_UNICODE__ msg))
#endif

#define AgMWIDEN2(x)		L##x
#define AgMWIDEN(x)			AgMWIDEN2(x)

#if !defined(__WFILE__) // __WFILE__ macro is also defined in cppunittestcommon.h
#define __WFILE__		AgMWIDEN(__FILE__)
#endif 
#define __WDATE__		AgMWIDEN(__DATE__)
#define __WTIME__		AgMWIDEN(__TIME__)

#if defined(_UNICODE)
#define __TFILE__			__WFILE__
#define __TDATE__			__WDATE__
#define __TTIME__			__WTIME__
#else
#define __TFILE__			__FILE__
#define __TDATE__			__DATE__
#define __TTIME__			__TIME__
#endif

#define	_A(x)				x
#define	_W(x)				AgMWIDEN(x)

#define CP_UTF8             65001       // UTF-8 translation

#if defined(__cplusplus)
typedef unsigned int        UINT;
#ifdef AGI_Linux_
typedef uint32_t            DWORD;
#else
typedef unsigned long       DWORD;
#endif
#endif

#define	sizeofAgTCharW(x)	(x*sizeof(AgTCharW))


#if defined(__cplusplus)


#define	AgT2OLE(x)								CT2OLE(x)
#define	AgOLE2T(x)								COLE2T(x)

#if defined(_UNICODE)
#define	AgT2A(x)								(LPSTR)ATL::CW2A(x)
#define	AgA2T(x)								(LPWSTR)ATL::CA2W(x)
#define	AgW2T(x)								(LPWSTR)(x)			 
#define	AgT2W(x)								(LPWSTR)(x)	
#define AgW2A(x)								(LPSTR)ATL::CW2A(x)
#define AgA2W(x)								(LPWSTR)ATL::CA2W(x)
#define AgMUtUnicodeToUtf8(str)					AgUtUnicodeToUtf8(str)
#define AgMUtUnicodeStdStringToUtf8(str)		AgUtUnicodeToUtf8(std::wstring(str))
#define AgMUtUnicodeFromUtf8(str)				AgUtUnicodeFromUtf8(str)
#define AgMUtUnicodeFromUtf8StdString(str)		AgUtUnicodeFromUtf8(std::string(str))
#define AgMGetTypeId(TYPE)						std::wstring(CA2W(typeid(TYPE).name()))
#define	CAgT2A(x)								ATL::CW2A(x)
#define	CAgA2T(x)								ATL::CA2W(x)
#define	CAgW2T(x)								(x)			 
#define	CAgT2W(x)								(x)	
#define CAgW2A(x)								ATL::CW2A(x)
#define CAgA2W(x)								ATL::CA2W(x)
#define	AgMStringA2StringT(x)					AgTStdString(AgA2W((x).c_str()))
#define	AgMStringT2StringA(x)					AgTStdStringA(AgW2A((x).c_str()))
#define	AgMStringT2StringW(x)					(x)
#define	AgMStringW2StringT(x)					(x)
#define	AgMUtUnicodeToAnsiChar(x)				AgUtUnicodeToAnsiChar(x)
#define	AgMUtUnicodeFromAnsiChar(x)				AgUtUnicodeFromAnsiChar(x)
#define AgMUuidToString(guid, guidString)		(::UuidToString(&newGuid, (RPC_WSTR*)&result))
#define AgMRpcStringFree(guidString)			(RpcStringFree((RPC_WSTR*)(&result)))	
#else
#define	AgT2A(x)								(x)
#define	AgA2T(x)								(x)
#define	AgW2T(x)								(LPSTR)CW2A(x)	 			 
#define	AgT2W(x)								(LPWSTR)CA2W(x) 
#define AgW2A(x)								(LPSTR)CW2A(x)
#define AgA2W(x)								(LPWSTR)CA2W(x)
#define AgMUtUnicodeToUtf8(str)					(str)
#define AgMUtUnicodeStdStringToUtf8(str)		AgTStdString(str)
#define AgMUtUnicodeFromUtf8(str)				(str)
#define AgMUtUnicodeFromUtf8StdString(str)		AgTStdString(str)
#define AgMGetTypeId(TYPE)						typeid(TYPE).name()
#define	CAgT2A(x)								(x)
#define	CAgA2T(x)								(x)
#define	CAgW2T(x)								CW2A(x)	 			 
#define	CAgT2W(x)								CA2W(x) 
#define CAgW2A(x)								CW2A(x)
#define CAgA2W(x)								CA2W(x)
#define	AgMStringA2StringT(x)					(x)
#define	AgMStringT2StringA(x)					(x)
#define	AgMStringT2StringW(x)					AgTStdStringW(AgA2W((x).c_str()))
#define	AgMStringW2StringT(x)					AgTStdStringA(AgW2A((x).c_str()))
#define	AgMUtUnicodeToAnsiChar(x)				(x)
#define	AgMUtUnicodeFromAnsiChar(x)				(x)
#define AgMUuidToString(guid, guidString)		(::UuidToString(&newGuid, (RPC_CSTR*)&result)) 
#define AgMRpcStringFree(guidString)			(RpcStringFree((RPC_CSTR*)(&result))) 

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToDo_Unicode - see BUG52426
// the declaration for CP_UTF8, MultiByteToWideChar and WideCharToMultiByteare (from WinNls.h) is a workaround
// to the include file problem. It will be fixed later 

#ifndef AGI_Linux_
extern "C"
__declspec(dllimport)
int
__stdcall
MultiByteToWideChar(
    UINT     CodePage,
    DWORD    dwFlags,
    const char *lpMultiByteStr,
    int      cbMultiByte,
    wchar_t *  lpWideCharStr,
    int      cchWideChar);

extern "C"
__declspec(dllimport)
int
__stdcall
WideCharToMultiByte(
    UINT     CodePage,
    DWORD    dwFlags,
    const wchar_t *  lpWideCharStr,
    int      cchWideChar,
    char *   lpMultiByteStr,
    int      cbMultiByte,
    const char*   lpDefaultChar,
    int*  lpUsedDefaultChar);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///
///
inline std::wstring AgUtUnicodeFromUtf8 (const std::string& sNarrowStr, int nNarrowStrSize=-1)
{
	char* lpStr = (char*)sNarrowStr.c_str();
	int nStrSize = (nNarrowStrSize > -1) ? nNarrowStrSize+1 : nNarrowStrSize;

	// convert mbcs to wide
	int nLengthW = MultiByteToWideChar(CP_UTF8,0,lpStr,nStrSize,NULL,0);
	wchar_t* lpwStr = (wchar_t*)calloc(nLengthW, sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8,0,lpStr,nStrSize,lpwStr,nLengthW);
	std::wstring buf(lpwStr) ;
	free(lpwStr);

    return buf ;
}

///
///
inline std::string AgUtUnicodeToUtf8 (const std::wstring& sWideStr, int nWideStrSize=-1)
{	
	int cchWide = (nWideStrSize == -1) ? (int)sWideStr.size() : nWideStrSize;
	wchar_t* lpWide = (wchar_t*)sWideStr.c_str();
	
	// convert wide to mbcs
	int nLength = WideCharToMultiByte(CP_UTF8,0,lpWide,cchWide,NULL,0,NULL,NULL);
	std::string buf;
	char* lpStr = (char*)calloc(nLength+1, sizeof(char)); 
    if (lpStr != NULL)
    {
	    WideCharToMultiByte(CP_UTF8,0,lpWide,cchWide,lpStr,nLength,NULL,NULL);
	    lpStr[nLength] = '\0' ;
		buf = std::string(lpStr);
		free(lpStr);
    }

	return buf ;
}

#endif  // !AGI_Linux_

#else /* __cplusplus */

#ifndef AGI_Linux_

__declspec(dllimport)
int
__stdcall
MultiByteToWideChar(
    UINT     CodePage,
    DWORD    dwFlags,
    const char *lpMultiByteStr,
    int      cbMultiByte,
    wchar_t *  lpWideCharStr,
    int      cchWideChar);

__declspec(dllimport)
int
__stdcall
WideCharToMultiByte(
    UINT     CodePage,
    DWORD    dwFlags,
    const wchar_t *  lpWideCharStr,
    int      cchWideChar,
    char *   lpMultiByteStr,
    int      cbMultiByte,
    const char*   lpDefaultChar,
    int*  lpUsedDefaultChar);

#endif  // !AGI_Linux_

#endif /* __cplusplus */

#ifndef AGI_Linux_

////////////////////////////////////////////////////////////////////////////////////////
//
///// The caller is responsible to free the pointer returned
/// 
_inline wchar_t* AgUtAllocUnicodeString (const char* lpcstrNarrowStr, int nNarrowStrSize)
{	
	int nStrSize = (nNarrowStrSize > -1) ? nNarrowStrSize+1 : nNarrowStrSize;

	// convert mbcs to wide
	int nLengthW = MultiByteToWideChar(CP_UTF8,0,lpcstrNarrowStr,nStrSize,NULL,0);
	wchar_t* lpwStr = (wchar_t*)calloc(nLengthW ,sizeof(wchar_t));	
	MultiByteToWideChar(CP_UTF8,0,lpcstrNarrowStr,nStrSize,lpwStr,nLengthW);
    return lpwStr ;
}

////////////////////////////////////////////////////////////////////////////////////////
//
/// The caller is responsible to free the pointer returned
///
_inline char* AgUtAllocUtf8String (const wchar_t* lpwStrWideStr, int nWideStrSize)
{	
	int cchWide = (nWideStrSize == -1) ? (int)wcslen(lpwStrWideStr) : nWideStrSize;
		
	// convert wide to mbcs
	int nLength = WideCharToMultiByte(CP_UTF8,0,lpwStrWideStr,cchWide,NULL,0,NULL,NULL);	
	char* lpStr = (char*) calloc(nLength+1,sizeof(char));		
    if (lpStr != NULL)
    {
	    WideCharToMultiByte(CP_UTF8,0,lpwStrWideStr,cchWide,lpStr,nLength,NULL,NULL);
	    lpStr[nLength] = '\0' ;	
    }
	return lpStr ;
}

////////////////////////////////////////////////////////////////////////////////////////
//
_inline int AgUtUnicodeFromUtf8Buffer (
	const char *lpMultiByteStr, 
	int cbMultiByte, 
	wchar_t *lpWideCharStr, 
	int cchWideChar)
{	
	return MultiByteToWideChar(CP_UTF8, 0, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
}

////////////////////////////////////////////////////////////////////////////////////////
//
_inline int AgUtUnicodeToUtf8Buffer (	
	const wchar_t *lpWideCharStr, 
	int cchWideChar,
	char *lpMultiByteStr, 
	int cbMultiByte)
{	
	return WideCharToMultiByte(CP_UTF8,0, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////
//
_inline int AgUtUnicodeFromAnsiBuffer (
	const char *lpMultiByteStr, 
	int cbMultiByte, 
	wchar_t *lpWideCharStr, 
	int cchWideChar)
{	
	return MultiByteToWideChar(CP_ACP, 0, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
}

////////////////////////////////////////////////////////////////////////////////////////
//
_inline int AgUtUnicodeToAnsiBuffer (	
	const wchar_t *lpWideCharStr, 
	int cchWideChar,
	char *lpMultiByteStr, 
	int cbMultiByte)
{	
	return WideCharToMultiByte(CP_ACP,0, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////
//
_inline int AgUtBufferUnicodeToMbChar (wchar_t wchar,	char *mbchar, size_t sizeInBytes)
{	
	int pRetValue = 0;
	return wctomb_s(&pRetValue, mbchar, sizeInBytes, wchar);
}

////////////////////////////////////////////////////////////////////////////////////////
//
_inline int AgUtBufferUnicodeFromMbChar (const char *mbchar, wchar_t *wchar, size_t count )
{	
	return mbtowc(wchar, mbchar, count);
}

///////////////////////////////////////////////////////////////////////////////////////
//
_inline char AgUtUnicodeToAnsiChar (const wchar_t wchar)
{	
	char   retCharA = _A('\0');
	AgUtBufferUnicodeToMbChar(wchar,&retCharA,1);		
	return retCharA;
}

////////////////////////////////////////////////////////////////////////////////////////
//
_inline wchar_t AgUtUnicodeFromAnsiChar (const char ansiChar)
{	
	wchar_t   retCharW = _W('\0');
	AgUtBufferUnicodeFromMbChar (&ansiChar,&retCharW,MB_CUR_MAX);
	return retCharW;
}


////////////////////////////////////////////////////////////////////////////////////////
//

////////////////////////////////////////////////////////////////////////////////////////
//
#if defined(_UNICODE)
_inline int AgUtWcstomvs(const wchar_t* widestr, char** mbsstr)
{
	size_t len = wcstombs(0, widestr, 0);
	// check that (errno != EILSEQ);
	// check that *mbsstr == 0;
	*mbsstr = (char*)malloc(len+1);
	*mbsstr[len] = 0;
	return (int)wcstombs(*mbsstr, widestr, len);
}
#endif
#endif  // !AGI_Linux_
#endif // __AgUtUnicode_H
/******************************************************************************/
/*****           Copyright 2002-2012, Analytical Graphics, Inc.           *****/
/******************************************************************************/
