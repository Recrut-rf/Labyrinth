#pragma once
#include <Windows.h>
#include <string>

const size_t BUFFERSIZE = 16 * 51;

class ConsoleEngine
{
public:
	ConsoleEngine();
	~ConsoleEngine();

	// вывод новых данных в консоль с сохранением предыдущих данных
	void outputDataToNewConsoleBuffer(std::string str);

	void writeConsole();

	void flushBuffer();  // очистка содержимого буфера консоли

	void setBufferSize(SHORT X, SHORT Y);
	void setCharPosition(SHORT X, SHORT Y);
	void setWriteRegion(SHORT Left, SHORT Top, SHORT Right, SHORT Bottom);
	void setAttribute(WORD attribute, size_t indx);
	void setCursorAttribute(BOOL bVisible, DWORD dwSize = sizeof(CONSOLE_CURSOR_INFO));
	void setCursorPosition(COORD  coord);
	void setCharBuffer(int position, char val);

private:
	// Получение сообщения о системной ошибке и завершение текущего процесса
	void ErrorExit(const char* lpszFunction);

	WORD    wAttribute_;                    // цвет фона и текста
	HANDLE  hStdOut_;                       // дескриптор стандартного вывода
	HANDLE  hStdOutNew_;                    // дескриптор буфера экрана для полной смены картинки
	CHAR_INFO charBuffer_[BUFFERSIZE];      // буфер с данными, которые будем выводить в консоль
	                                        // нужно сделать динамическим, без привязки к BUFFERSIZE
	                                        // тогда можно будет грузить любые уровни из файла
	                                        // сейчас же размеры жёстко прописаны - это не есть хорошо
	CONSOLE_CURSOR_INFO consoleCursorInfo_; // информация о курсоре

	COORD bufferSize_;                      // размеры выводимой области 
	COORD charPosition_;                    // координаты левого угла прямоугольника, из которого выводим
	SMALL_RECT writeRegion_;                // координаты левого угла прямоугольника, в который пишем
};
