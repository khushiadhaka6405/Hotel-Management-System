// Modified for HOSTEL MANAGEMENT SYSTEM
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

void intro() {
    cout << "\n\n\t            ";
    cout << "     C++ Project On Hostel Management System";
    cout << "\n\n\t\t\t\t\t     MADE BY";
    cout << "\n===============================================";
    cout << "\n||\t\t\t     KHUSHIA\t\t\t    ||";
    cout << "\n===============================================";
}

void head() {
    system("clear"); // or system("cls") for Windows
    cout << "===============================================";
    cout << "\n\t\t\t   XYZ College Hostel\t\t\t";
    cout << "\n===============================================";
}

void time() {
    int i = 0;
    long long j;
    cout << "\n\n\n\tConnecting to Server\n \tSyncing Data";
    while (i < 10) {
        for (j = 5; j > 4; j++) {
            if (j == 99999) {
                cout << ".";
                break;
            }
        }
        ++i;
    }
}

class hostel {
private:
    int room_no;
    char name[30];
    char branch[30];
    char phone[15];
    int months;
    float rent;
public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

void hostel::main_menu() {
    int choice;
    while (choice != 5) {
        system("clear");
        head();
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\n\t\t\t1.Allot Room";
        cout << "\n\t\t\t2.Student Record";
        cout << "\n\t\t\t3.Allotted Rooms";
        cout << "\n\t\t\t4.Edit Record";
        cout << "\n\t\t\t5.Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: break;
            default: cout << "\n\n\t\t\tWrong choice.....!!!"; getchar();
        }
    }
}

void hostel::add() {
    system("clear");
    head();
    int r, flag;
    ofstream fout("HostelRecord.dat", ios::app);
    cout << "\n Enter Student Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: "; cin >> r;
    flag = check(r);
    if (flag)
        cout << "\n Sorry..!!! Room is already allotted";
    else {
        room_no = r;
        cout << " Name: "; cin.ignore(); cin.getline(name, 30);
        cout << " Branch: "; cin.getline(branch, 30);
        cout << " Phone No: "; cin.getline(phone, 15);
        cout << " No of Months: "; cin >> months;
        rent = months * 1500; // Monthly hostel rent
        fout.write((char*)this, sizeof(hostel));
        cout << "\n Room is allotted...!!!";
    }
    getchar();
    fout.close();
}

void hostel::display() {
    system("clear");
    head();
    ifstream fin("HostelRecord.dat", ios::in);
    int r, flag = 0;
    cout << "\n Enter room no: "; cin >> r;
    while (fin.read((char*)this, sizeof(hostel))) {
        if (room_no == r) {
            system("clear");
            head();
            cout << "\n Student Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Branch: " << branch;
            cout << "\n Phone no: " << phone;
            cout << "\n Months: " << months;
            cout << "\n Total Rent: " << rent;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant....!!";
    getchar();
    fin.close();
}

void hostel::rooms() {
    system("clear");
    head();
    ifstream fin("HostelRecord.dat", ios::in);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    while (fin.read((char*)this, sizeof(hostel))) {
        cout << "\n Room no: " << room_no << "\n Name: " << name;
        cout << "\n Branch: " << branch << "\n Phone: " << phone;
        cout << "\n Months: " << months << "\n Total Rent: " << rent;
        cout << "\n**********************************";
    }
    getchar();
    fin.close();
}

void hostel::edit() {
    system("clear");
    head();
    int choice, r;
    cout << "\n EDIT MENU\n ---------";
    cout << "\n\n 1.Modify Student Record";
    cout << "\n 2.Delete Student Record";
    cout << "\n Enter your choice: "; cin >> choice;
    cout << "\n Enter room no: "; cin >> r;
    switch (choice) {
        case 1: modify(r); break;
        case 2: delete_rec(r); break;
        default: cout << "\n Wrong Choice.....!!";
    }
    getchar();
}

int hostel::check(int r) {
    int flag = 0;
    ifstream fin("HostelRecord.dat", ios::in);
    while (fin.read((char*)this, sizeof(hostel))) {
        if (room_no == r) {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

void hostel::modify(int r) {
    system("clear");
    head();
    long pos;
    int flag = 0;
    fstream file("HostelRecord.dat", ios::in | ios::out | ios::binary);
    while (!file.eof()) {
        pos = file.tellg();
        file.read((char*)this, sizeof(hostel));
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cout << "\n Name: "; cin.ignore(); cin.getline(name, 30);
            cout << " Branch: "; cin.getline(branch, 30);
            cout << " Phone no: "; cin.getline(phone, 15);
            cout << " Months: "; cin >> months;
            rent = months * 1500;
            file.seekg(pos);
            file.write((char*)this, sizeof(hostel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant...!!";
    file.close();
}

void hostel::delete_rec(int r) {
    system("clear");
    head();
    int flag = 0;
    char ch;
    ifstream fin("HostelRecord.dat", ios::in);
    ofstream fout("temp.dat", ios::out);
    while (fin.read((char*)this, sizeof(hostel))) {
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Branch: " << branch;
            cout << "\n Phone No: " << phone;
            cout << "\n Months: " << months;
            cout << "\n Total Rent: " << rent;
            cout << "\n\n Do you want to delete this record(y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write((char*)this, sizeof(hostel));
            flag = 1;
            continue;
        }
        fout.write((char*)this, sizeof(hostel));
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n Sorry room no. not found or vacant...!!";
    else {
        remove("HostelRecord.dat");
        rename("temp.dat", "HostelRecord.dat");
    }
}

int main() {
    hostel h;
    system("clear");
    intro();
    time();
    cout << "\n\n\n\t\t\tPress any key to continue....!!";
    getchar();
    system("clear");
    head();
    char id[5], pass[7];
    cout << "\n\n\t\t\t\tusername => "; cin >> id;
    cout << "\n\t\t\t\tpassword => "; cin >> pass;
    cout << "\n\n\t"; time(); cout << "\t";
    if (strcmp(id, "admin") == 0 && strcmp(pass, "******") == 0)
        cout << "\n\n\t\t\t  !!!Login Successful!!!";
    else {
        cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
        getchar();
        exit(-1);
    }
    system("clear");
    h.main_menu();
    getchar();
    return 0;
}