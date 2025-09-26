#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <string>
#include <windows.h>

// Console Colors
enum ConsoleColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

class Graphics {
public:
    // Color functions
    static void setColor(int textColor, int bgColor = BLACK);
    static void resetColor();
    static void clearScreen();
    
    // Box drawing
    static void drawBox(int x, int y, int width, int height);
    static void drawHorizontalLine(int length, char ch = '═');
    static void drawVerticalLine(int height);
    
    // UI Elements
    static void showLogo();
    static void showMainHeader();
    static void showStudentHeader();
    static void showAdminHeader();
    static void showSuccessMessage(const std::string& message);
    static void showErrorMessage(const std::string& message);
    static void showInfoMessage(const std::string& message);
    
    // Menu styling
    static void showMenuOption(int number, const std::string& text, bool highlight = false);
    static void showMenuSeparator();
    static void showMenuHeader(const std::string& title);
    static void showMenuFooter();
    
    // Loading and progress
    static void showLoadingBar(const std::string& text, int duration = 1000);
    static void pauseWithMessage(const std::string& message = "Nhan Enter de tiep tuc...");
    
    // Cursor positioning
    static void gotoxy(int x, int y);
    static void hideCursor();
    static void showCursor();
    
    // Input styling
    static std::string getStyledInput(const std::string& prompt, bool isPassword = false);
    
private:
    static HANDLE hConsole;
};

#endif