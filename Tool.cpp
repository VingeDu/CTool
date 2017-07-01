// Tool.cpp: implementation of the CTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTool::CTool()
{
}

CTool::~CTool()
{
}
//多字节转换并存储到宽字节的CString类中，如果定义为非UNICODE模式，则出错
BOOL CTool::AnsiToUnicode(const char *pSrc, CString &strResult)
{
#ifndef _UNICODE
	return FALSE;
#endif
	int nLen=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pSrc,-1,NULL,0);
	strResult.Empty();
	if(nLen==0)
		return FALSE;
	wchar_t* pResult=new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pSrc,-1,pResult,nLen);
	strResult.Format(_T("%s"),pResult);
	delete[] pResult;
	pResult=NULL;
	return TRUE;
}

wchar_t* CTool::AnsiToUnicode(const char *szStr)
{
	int nLen=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,szStr,-1,NULL,0);
	if(nLen==0)
		return NULL;
	wchar_t* pResult=new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,szStr,-1,pResult,nLen);
	return pResult;
}

char* CTool::CStringToCharEnter(CString strSource)
{
	int iNewCharLen = strSource.GetAllocLength()+2;
	char* pNewChar = new char[iNewCharLen];
	int k=0;
	for (; k<iNewCharLen-2; k++)
	{
		pNewChar[k] = strSource.GetAt(k);
	}
	pNewChar[k] = 0x0D;
	pNewChar[k+1] = 0x0A;
	return pNewChar;
}
char* CTool::UnicodeToAnsi(const wchar_t *szStr)
{
	int nLen=WideCharToMultiByte(CP_ACP,0,szStr,-1,NULL,0,NULL,NULL);
	if(nLen==0)
		return NULL;
	char* pResult=new char[nLen];
	WideCharToMultiByte(CP_ACP,0,szStr,-1,pResult,nLen,NULL,NULL);
	return pResult;
}

CString CTool::GetAppPath()
{
	TCHAR path[_MAX_PATH];
    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];        
	GetModuleFileName(::AfxGetApp()->m_hInstance,path,_MAX_PATH);
#ifdef UNICODE
    _wsplitpath(path,drive,dir,fname,ext);
#else
	_splitpath(path,drive,dir,fname,ext);
#endif
	const int nPathLength=256;
	TCHAR strEzCadPath[nPathLength];
	
	_tcscpy(strEzCadPath,drive);
	_tcscat(strEzCadPath,dir);
	
	return strEzCadPath;
}

double CTool::strtof(const CString &str)
{
	TCHAR* pStop;
	return _tcstod(str,&pStop);
}

int CTool::strtoi(const CString& str)
{
	return _ttoi(str);
}

double CTool::CStringToDouble(CString strNUM)
{
	double dValue = 0.0;
	TCHAR tChar[512];
	ZeroMemory(tChar,512);
	int i=0;
	for (; i<strNUM.GetLength(); i++)
	{
		TCHAR theChar = strNUM.GetAt(i);
		tChar[i] = theChar;
	}
	tChar[i] = '\0';

#ifndef _UNICODE
	dValue = atof(tChar);
#else
	char ch[255];
	ZeroMemory(ch,255);
	sprintf(ch,"%S",tChar);
	dValue = atof(ch);
#endif
	return dValue;
}

int CTool::WriteToCutFile(CStdioFileEx* pFile,CString strWtString)
{
	pFile->SeekToEnd();
	pFile->WriteString(strWtString+_T("\r\n"));	
	return 0;
}

int CTool::GetDataAndNameFromCUT(CString strSource, CString& strData, CString& strName)
{
	int iFirstRight = strSource.Find(_T(">"));
	int iSecondRight = strSource.Find(_T(">"),iFirstRight+1);
	int iFirstLeft = strSource.Find(_T("<"),1);
	strData = strSource.Mid(iFirstRight+1,iFirstLeft-iFirstRight-1);
	strName = strSource.Mid(1,iFirstRight-1);

	return 0;
}
