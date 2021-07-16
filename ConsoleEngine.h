#pragma once
#include <Windows.h>
#include <string>

const size_t BUFFERSIZE = 16 * 51;

class ConsoleEngine
{
public:
	ConsoleEngine();
	~ConsoleEngine();

	// ����� ����� ������ � ������� � ����������� ���������� ������
	void outputDataToNewConsoleBuffer(std::string str);

	void writeConsole();

	void flushBuffer();  // ������� ����������� ������ �������

	void setBufferSize(SHORT X, SHORT Y);
	void setCharPosition(SHORT X, SHORT Y);
	void setWriteRegion(size_t Left, size_t Top, size_t Right, size_t Bottom);
	void setAttribute(WORD attribute, size_t indx);
	void setCursorAttribute(BOOL bVisible, DWORD dwSize = sizeof(CONSOLE_CURSOR_INFO));
	void setCursorPosition(COORD  coord);
	void setCharBuffer(int position, char val);

private:
	// ��������� ��������� � ��������� ������ � ���������� �������� ��������
	void ErrorExit(const char* lpszFunction);

	WORD    wAttribute_;                    // ���� ���� � ������
	HANDLE  hStdOut_;                       // ���������� ������������ ������
	HANDLE  hStdOutNew_;                    // ���������� ������ ������ ��� ������ ����� ��������
	CHAR_INFO charBuffer_[BUFFERSIZE];      // ����� � �������, ������� ����� �������� � �������
	                                        // ����� ������� ������������, ��� �������� � BUFFERSIZE
	                                        // ����� ����� ����� ������� ����� ������ �� �����
	                                        // ������ �� ������� ����� ��������� - ��� �� ���� ������
	CONSOLE_CURSOR_INFO consoleCursorInfo_; // ���������� � �������

	COORD bufferSize_;                      // ������� ��������� ������� 
	COORD charPosition_;                    // ���������� ������ ���� ��������������, �� �������� �������
	SMALL_RECT writeRegion_;                // ���������� ������ ���� ��������������, � ������� �����
};
