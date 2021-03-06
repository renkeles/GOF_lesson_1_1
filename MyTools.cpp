
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "MyTools.h"

using namespace std;

namespace MyTools {

    

    //=============================================================================================

    void ScreenSingleton::ClrScr()
    {
        system("cls");
    }

    void __fastcall ScreenSingleton::GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t ScreenSingleton::GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    }

    uint16_t ScreenSingleton::GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }

    void ScreenSingleton::SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

    //=============================================================================================

    void __fastcall FileLoggerSingletone::OpenLogFile(const string& FN)
    {
        FileLoggerSingletone::logOut.open(FN, ios_base::out);
    }

    void FileLoggerSingletone::CloseLogFile()
    {
        if (FileLoggerSingletone::logOut.is_open())
        {
            FileLoggerSingletone::logOut.close();
        }
    }

    string GetCurDateTime()
    {
        auto cur = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(cur);
        char buf[64] = { 0 };
        ctime_s(buf, 64, &time);
        buf[strlen(buf) - 1] = '\0';
        return string(buf);
    }

    void __fastcall FileLoggerSingletone::WriteToLog(const string& str)
    {
        if (FileLoggerSingletone::logOut.is_open())
        {
            FileLoggerSingletone::logOut << GetCurDateTime() << " - " << str << endl;
        }
    }

    void __fastcall FileLoggerSingletone::WriteToLog(const string& str, int n)
    {
        if (FileLoggerSingletone::logOut.is_open())
        {
            FileLoggerSingletone::logOut << GetCurDateTime() << " - " << str << n << endl;
        }
    }

    void __fastcall FileLoggerSingletone::WriteToLog(const string& str, double d)
    {
        if (FileLoggerSingletone::logOut.is_open())
        {
            FileLoggerSingletone::logOut << GetCurDateTime() << " - " << str << d << endl;
        }
    }

    //=============================================================================================


} // namespace MyTools