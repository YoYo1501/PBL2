#include "../include/Graphics.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace std;

HANDLE Graphics::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Graphics::setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void Graphics::resetColor() {
    SetConsoleTextAttribute(hConsole, LIGHTGRAY);
}

void Graphics::clearScreen() {
    system("cls");
}

void Graphics::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void Graphics::hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Graphics::showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Graphics::drawHorizontalLine(int length, char ch) {
    for (int i = 0; i < length; i++) {
        cout << ch;
    }
}

void Graphics::showLogo() {
    setColor(LIGHTCYAN, BLACK);
    cout << "\n";
    cout << "    +===========================================================+\n";
    cout << "    |                                                           |\n";
    cout << "    |        HE THONG QUAN LY KY TUC XA DUT                     |\n";
    cout << "    |                                                           |\n";
    cout << "    |        Dai hoc Bach Khoa- Dai hoc Da Nang                 |\n";
    cout << "    |                                                           |\n";
    cout << "    +===========================================================+\n";
    resetColor();
    cout << "\n";
}

void Graphics::showMainHeader() {
    clearScreen();
    showLogo();
    setColor(YELLOW, BLACK);
    cout << "    +----------------------------------------------------------+\n";
    cout << "    |                 DANG NHAP HE THONG                       |\n";
    cout << "    +----------------------------------------------------------+\n";
    resetColor();
    cout << "\n";
}

void Graphics::showStudentHeader() {
    clearScreen();
    setColor(LIGHTGREEN, BLACK);
    cout << "\n";
    cout << "    +===========================================================+\n";
    cout << "    |                                                           |\n";
    cout << "    |        GIAO DIEN SINH VIEN - KY TUC XA DUT                |\n";
    cout << "    |                                                           |\n";
    cout << "    +===========================================================+\n";
    resetColor();
    cout << "\n";
}

void Graphics::showAdminHeader() {
    clearScreen();
    setColor(LIGHTRED, BLACK);
    cout << "\n";
    cout << "    ╔══════════════════════════════════════════════════════════╗\n";
    cout << "    ║                                                          ║\n";
    cout << "    ║     👑 GIAO DIỆN QUẢN LÝ - KÝ TÚC XÁ DUT 👑             ║\n";
    cout << "    ║                                                          ║\n";
    cout << "    ╚══════════════════════════════════════════════════════════╝\n";
    resetColor();
    cout << "\n";
}

void Graphics::showMenuHeader(const string& title) {
    setColor(LIGHTBLUE, BLACK);
    cout << "    +----------------------------------------------------------+\n";
    cout << "    |  " << title;
    
    // Padding để căn giữa
    int padding = 55 - title.length();
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";
    cout << "    +----------------------------------------------------------+\n";
    resetColor();
    cout << "\n";
}

void Graphics::showMenuOption(int number, const string& text, bool highlight) {
    if (highlight) {
        setColor(BLACK, YELLOW);
    } else {
        setColor(WHITE, BLACK);
    }
    
    cout << "    ";
    if (number == 0) {
        setColor(LIGHTRED, BLACK);
        cout << " [X] ";
    } else {
        setColor(LIGHTGREEN, BLACK);
        cout << " " << number << ". ";
    }
    
    if (highlight) {
        setColor(BLACK, YELLOW);
    } else {
        setColor(LIGHTGRAY, BLACK);
    }
    
    cout << text << "\n";
    resetColor();
}

void Graphics::showMenuSeparator() {
    setColor(DARKGRAY, BLACK);
    cout << "    -------------------------------------------------------------\n";
    resetColor();
}

void Graphics::showMenuFooter() {
    cout << "\n";
    setColor(LIGHTBLUE, BLACK);
    cout << "    +----------------------------------------------------------+\n";
    cout << "    |  Nhap so tuong ung de chon chuc nang                     |\n";
    cout << "    +----------------------------------------------------------+\n";
    resetColor();
}

void Graphics::showSuccessMessage(const string& message) {
    setColor(BLACK, LIGHTGREEN);
    cout << " [OK] " << message << " ";
    resetColor();
    cout << "\n";
}

void Graphics::showErrorMessage(const string& message) {
    setColor(WHITE, RED);
    cout << " [ERROR] " << message << " ";
    resetColor();
    cout << "\n";
}

void Graphics::showInfoMessage(const string& message) {
    setColor(BLACK, LIGHTCYAN);
    cout << " [INFO] " << message << " ";
    resetColor();
    cout << "\n";
}

void Graphics::showLoadingBar(const string& text, int duration) {
    setColor(YELLOW, BLACK);
    cout << "    " << text << " ";
    
    setColor(LIGHTGRAY, BLACK);
    cout << "[";
    
    int barLength = 30;
    for (int i = 0; i <= barLength; i++) {
        setColor(LIGHTGREEN, BLACK);
        for (int j = 0; j < i; j++) cout << "#";
        
        setColor(DARKGRAY, BLACK);
        for (int j = i; j < barLength; j++) cout << "-";
        
        cout << "] " << (i * 100 / barLength) << "%";
        
        this_thread::sleep_for(chrono::milliseconds(duration / barLength));
        
        if (i < barLength) {
            cout << "\r    " << text << " [";
        }
    }
    resetColor();
    cout << "\n\n";
}

void Graphics::pauseWithMessage(const string& message) {
    setColor(YELLOW, BLACK);
    cout << "\n    " << message;
    resetColor();
    cin.ignore();
    cin.get();
}

string Graphics::getStyledInput(const string& prompt, bool isPassword) {
    setColor(LIGHTCYAN, BLACK);
    cout << "    >> " << prompt << ": ";
    setColor(WHITE, BLACK);
    
    string input;
    if (isPassword) {
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == 8) { // Backspace
                if (!input.empty()) {
                    input.pop_back();
                    cout << "\b \b";
                }
            } else {
                input += ch;
                cout << '*';
            }
        }
        cout << endl;
    } else {
        getline(cin, input);
    }
    
    resetColor();
    return input;
}