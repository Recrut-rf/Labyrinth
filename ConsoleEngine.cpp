#include "ConsoleEngine.h"
#include <tchar.h>
#include <winnt.h>
#include <fstream>
#include <sstream>
#include <strsafe.h>    // ��� StringCchPrintf()
#include <WinUser.h>

#include <conio.h>  // ��� _cputs � _getch();

//#pragma comment (lib, "User32.lib") // ����� �������� ���� ����� ������� ������ � MessageBox


/*
����� �������� �������� ������ �����������

std::cout << _MSVC_LANG << std::endl;

��������� ��� ������� 201402, ��� ��������, ��� ���������� ��-�������� �������� � C++14

std::cout << _MSC_VER << std::endl;

������ �����������

#if _MSC_VER >= 1910
// . . .
#elif _MSC_VER >= 1900
// . . .
#else
// . . .
#endif
*/

ConsoleEngine::ConsoleEngine() : wAttribute_{}, hStdOut_{ GetStdHandle(STD_OUTPUT_HANDLE) },
charBuffer_{}, consoleCursorInfo_{}, bufferSize_{}, charPosition_{}, writeRegion_{}
{     }


ConsoleEngine::~ConsoleEngine()
{     }

void ConsoleEngine::outputDataToNewConsoleBuffer(std::string str)
{
	// ������ ����� ������
	hStdOutNew_ = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	if (hStdOutNew_ == INVALID_HANDLE_VALUE)
		ErrorExit(/*_T*/("CreateConsoleScreenBuffer"));

	// ������ �������� ����� ����� ������
	if (!SetConsoleActiveScreenBuffer(hStdOutNew_))
		ErrorExit(/*_T*/("SetConsoleActiveScreenBuffer"));

	// ������� ����� � ����� ����� ������
	if (!WriteConsole(hStdOutNew_, str.c_str(), str.size() + 1, {}, NULL))
		ErrorExit(/*_T*/("WriteConsole"));

	char infoStr[] = "\nPress any key to set old screen buffer.";
	if (!WriteConsole(hStdOutNew_, infoStr, sizeof(infoStr), {}, NULL))
		ErrorExit("WriteConsole");

	_getch();

	// ��������������� ������ ����� ������
	if (!SetConsoleActiveScreenBuffer(hStdOut_))
		ErrorExit(/*_T*/("SetConsoleActiveScreenBuffer"));

	// ��������� ����� ����� ������
	CloseHandle(hStdOutNew_);
}

void ConsoleEngine::writeConsole()
{
	if (!WriteConsoleOutput(hStdOut_, charBuffer_, bufferSize_,
		charPosition_, &writeRegion_))
		ErrorExit("WriteConsoleOutput");	
}

void ConsoleEngine::flushBuffer()
{	
	std::memset(charBuffer_, 0, sizeof(charBuffer_));
}

void ConsoleEngine::setBufferSize(SHORT X, SHORT Y)
{
	bufferSize_.X = X;
	bufferSize_.Y = Y;
}

void ConsoleEngine::setCharPosition(SHORT X, SHORT Y)
{
	charPosition_.X = X;
	charPosition_.Y = Y;
}

void ConsoleEngine::setWriteRegion(size_t Left, size_t Top, size_t Right, size_t Bottom)
{
	writeRegion_.Left = Left;
	writeRegion_.Top = Top;
	writeRegion_.Right = Right;
	writeRegion_.Bottom = Bottom;
}

void ConsoleEngine::setAttribute(WORD attribute, size_t indx)
{	
	charBuffer_[indx].Attributes = attribute;
}

void ConsoleEngine::setCursorAttribute(BOOL bVisible, DWORD dwSize)
{
	consoleCursorInfo_.dwSize = dwSize;
	consoleCursorInfo_.bVisible = bVisible;

	if (!SetConsoleCursorInfo(hStdOut_, std::addressof(consoleCursorInfo_)))
		ErrorExit("SetConsoleCursorInfo");
}

void ConsoleEngine::setCursorPosition(COORD coord)
{
	if (!SetConsoleCursorPosition(hStdOut_, coord))
		ErrorExit("SetConsoleCursorPosition");
}

void ConsoleEngine::setCharBuffer(int position, char val)
{
	charBuffer_[position].Char.AsciiChar = val;
}

void ConsoleEngine::ErrorExit(const char* lpszFunction)
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// ����������� ������ � ���������� �������� ��������
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}
