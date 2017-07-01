#if !defined(AFX_TOOL_H__BA82A031_5C94_44CC_B085_E8F31ACBC99D__INCLUDED_)
#define AFX_TOOL_H__BA82A031_5C94_44CC_B085_E8F31ACBC99D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StdioFileEx.h"

class CTool  
{
public:      
	CTool();
	virtual ~CTool();

	//字符串转整型
	static int strtoi(const CString& str);
	//字符串转浮点
	static double strtof(const CString& str);
	//获取当前文件所在路径
	static CString GetAppPath();

	//宽字节转多字节
	static char* UnicodeToAnsi(const wchar_t *szStr);

	//Cstring To char +(回车)
	static char* CStringToCharEnter(CString strSource);

	//多字节转宽字节
	static wchar_t* AnsiToUnicode(const char* szStr);
	//多字节转宽字节，并把结果存储到CString对象中，在MCBS模式下直接返回假
	static BOOL AnsiToUnicode(const char* pSrc,CString& strResult);	
	static double CStringToDouble(CString strNUM);
	static int WriteToCutFile(CStdioFileEx* pFile,CString strWtString);
	static int GetDataAndNameFromCUT(CString strSource, CString& strData, CString& strName);
};

#endif // !defined(AFX_TOOL_H__BA82A031_5C94_44CC_B085_E8F31ACBC99D__INCLUDED_)
