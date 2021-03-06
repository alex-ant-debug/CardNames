#include <QCoreApplication>
#include "card.h"
#include "deberccard.h"
#include "game.h"
#include "player.h"
#include <QDebug>
#include <Windows.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    CONSOLE_FONT_INFOEX cfi;
//    cfi.cbSize = sizeof(cfi);
//    cfi.nFont = 0;
//    cfi.dwFontSize.X = 0;                   // Width of each character in the font
//    cfi.dwFontSize.Y = 24;                  // Height
//    cfi.FontFamily = FF_DONTCARE;
//    cfi.FontWeight = FW_NORMAL;
//    std::wcscpy(cfi.FaceName, L"Terminal"); // Choose your font
//    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

   /* unsigned int arrayTest[4][8] = {{3, 1, 11, 26, 27, 28, 23, 24},
                                    {27, 21, 29, 41, 43, 44, 3, 1},
                                    {1, 3, 4, 14, 15, 16, 21, 31},
                                    {9, 31 , 11, 30, 37, 38, 1, 5}};*/


    try
    {
        unsigned int numberPlayers = 4;
        Game revenge(numberPlayers);
        revenge.runMultiple();
    }
    catch (std::string message)
    {
        std::cout<<message<<std::endl;
    }

    return a.exec();
}
