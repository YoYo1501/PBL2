#include <iostream>
#include <conio.h>
#include "../include/AuthSystem.h"
#include "../include/MenuSystem.h"
#include "../include/AuthSystem.h"
#include "../include/models/User.h"
#include <windows.h>


using namespace std;

void setUTF8Console() {
    SetConsoleOutputCP(65001);
}


string getPassword()
{
    string password;
    char ch;

    while (true)
    {
        ch = _getch();

        if (ch == 13)
        { 
            break;
        }
        else if (ch == 8)
        { 
            if (!password.empty())
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            cout << '*';
            password.push_back(ch);
        }
    }
    cout << endl;
    return password;
}

void showLoginMenu(AuthSystem &auth)
{
    string username, password;

    cout << "\n=== DANG NHAP HE THONG ===" << endl;
    cout << "Ten dang nhap: ";
    cin >> username;

    cout << "Mat khau: ";
    password = getPassword();

    if (auth.login(username, password))
    {
        User *user = auth.getCurrentUser();
        cout << "\n Dang nhap thanh cong!" << endl;
        cout << "Chao mung: " << user->getFullName() << endl;
        cout << "Vai tro: " << user->getRole() << endl;

      
        if (auth.isAdmin())
        {
            cout << "\n=== MENU QUAN TRI ===" << endl;
            cout << "1. Quan ly nguoi dung" << endl;
            cout << "2. Quan ly phong" << endl;
            cout << "3. Thong ke" << endl;
        }
        else if (auth.isAdmin())
        {
            cout << "\n=== MENU QUAN LY ===" << endl;
            cout << "1. Quan ly sinh vien" << endl;
            cout << "2. Quan ly hop dong" << endl;
            cout << "3. Quan ly hoa don" << endl;
        }
        else if (auth.isStudent())
        {
            int studentChoice;
            do
            {
                system("cls");
                cout << "\n=== MENU SINH VIEN ===" << endl;
                cout << "1. Xem thong tin ca nhan" << endl;
                cout << "2. Chinh sua thong tin ca nhan" << endl;
                cout << "3. Dang xuat" << endl;
                cout << "Chon chuc nang (1-3): ";
                cin >> studentChoice;
                cin.ignore();
                switch (studentChoice)
                {
                case 1:
                    user->viewProfile();
                    cout << "\nNhan phim bat ky de tiep tuc...";
                    _getch();
                    break;
                case 2:
                    user->editProfile();
                    cout << "\nNhan phim bat ky de tiep tuc...";
                    _getch();
                    break;
                case 3:
                    cout << "Dang xuat..." << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le!" << endl;
                    cout << "\nNhan phim bat ky de tiep tuc...";
                    _getch();
                }
            } while (studentChoice != 3);
            auth.logout();
        }
    }
    else
    {
        cout << "\n Sai ten dang nhap hoac mat khau!" << endl;
        cout << "Nhan phim bat ky de tiep tuc...";
        _getch();
    }
}

void showRegistrationMenu(AuthSystem &auth)
{
    int roleChoice;
    string username, password, confirmPassword, fullName, studentId;
    cout << "\n=== DANG KY TAI KHOAN ===" << endl;
    cout << "1. Dang ky Sinh vien" << endl;
    cout << "2. Dang ky Quan ly" << endl;
    cout << "Chon vai tro: ";
    cin >> roleChoice;
    if (roleChoice != 1 && roleChoice != 2)
    {
        cout << "Lua chon khong hop le!" << endl;
        return;
    }
    cout << "Ten dang nhap: ";
    cin >> username;
    if (auth.usernameExists(username))
    {
        cout << " Ten dang nhap da ton tai!" << endl;
        return;
    }
    cout << "Mat khau: ";
    password = getPassword();
    cout << "Xac nhan mat khau: ";
    confirmPassword = getPassword();
    if (password != confirmPassword)
    {
        cout << " Mat khau khong khop!" << endl;
        return;
    }
    cin.ignore();
    cout << "Ho va ten: ";
    getline(cin, fullName);
    string role;
    if (roleChoice == 1)
    {
        role = "student";
        cout << "Ma sinh vien: ";
        cin >> studentId;
    }
    else
    {
        role = "admin";
        studentId = "";
    }
    if (auth.registerUser(username, password, role, fullName, studentId))
    {
        cout << " Dang ky thanh cong!" << endl;
        cout << "Ban co the dang nhap ngay bay gio." << endl;
    }
    else
    {
        cout << " Dang ky that bai!" << endl;
    }
    cout << "Nhan phim bat ky de tiep tuc...";
    _getch();
}

void showMainMenu()
{
    setUTF8Console();
    AuthSystem authSystem;
    int choice;
    do
    {
        system("cls");
        cout << "==========================================" << endl;
        cout << "    HE THONG QUAN LY KY TUC XA" << endl;
        cout << "==========================================" << endl;
        cout << "1. Dang nhap" << endl;
        cout << "2. Dang ky" << endl;
        cout << "3. Thoat" << endl;
        cout << "==========================================" << endl;
        cout << "Chon chuc nang (1-3): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            showLoginMenu(authSystem);
            break;
        case 2:
            showRegistrationMenu(authSystem);
            break;
        case 3:
            cout << "Tam biet!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            cout << "Nhan phim bat ky de tiep tuc...";
            _getch();
        }
    } while (choice != 3);
}

int main()
{
    showMainMenu();
    return 0;
}