#include<iostream>
#include<fstream>
#include<cstring>
#include<cctype>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<iomanip> 													// for manipulation

using namespace std;
//class hotel management system
class hms{

private:
struct CustomerDetails 												// create a structure
{
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[35];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
} s;
	public:
void add();
void list();
void edit();
void delete1();
void search();
void setcolor(int ForgC);
void login();
void run() {
    int i = 0;
    time_t t;
    time(&t);
    char choice;
    system("cls");

    while (true) {
        system("cls");
        setcolor(10);
        for (i = 0; i < 80; i++)
            cout << "-";
        cout << "\n";
        cout << "   ******************************  |MAIN MENU|  ***************************** \n";
        for (i = 0; i < 80; i++)
            cout << "-";
        cout << "\n";
        setcolor(10);
        cout << "\t\t *Please enter your choice for menu*:";
        cout << "\n\n";
        cout << " \n Enter 1 -> Book a room";
        cout << "\n------------------------";
        cout << " \n Enter 2 -> View Customer Record";
        cout << "\n----------------------------------";
        cout << " \n Enter 3 -> Delete Customer Record";
        cout << "\n-----------------------------------";
        cout << " \n Enter 4 -> Search Customer Record";
        cout << "\n-----------------------------------";
        cout << " \n Enter 5 -> Edit Record";
        cout << "\n-----------------------";
        cout << " \n Enter 6 -> Exit";
        cout << "\n-----------------";
        cout << "\n";
        for (i = 0; i < 80; i++)
            cout << "-";
        cout << "\nCurrent date and time : " << ctime(&t);
        for (i = 0; i < 80; i++)
            cout << "-";

        choice = _getch();
        choice = toupper(choice);
        switch (choice) {
            case '1':
                add();
                break;
            case '2':
                list();
                break;
            case '3':
                delete1();
                break;
            case '4':
                search();
                break;
            case '5':
                edit();
                break;
            case '6':
                system("cls");
                cout << "\n\n\t *****THANK YOU*****";
                cout << "\n\t FOR TRUSTING OUR SERVICE";
                exit(0);
                break;
            default:
                system("cls");
                cout << "Incorrect Input";
                cout << "\n Press any key to continue";
                _getch();
        }
    }
}
};
// function to add record
void hms::add() {
    ofstream f;
    char test;
    f.open("add.txt", ios::app);
    if (!f.is_open()) {
        f.open("add.txt", ios::out);
        system("cls");
        cout << "Please hold on while we set our database in your computer!!";
        cout << "\n Process completed press any key to continue!! ";
        _getch();
    }
    while (true) {
        system("cls");
        cout << "\n Enter Customer Details:";
        cout << "\n**************************";
        cout << "\n Enter Room number:\n";
        cin >> s.roomnumber;
        cin.ignore();
        cout << "Enter Name:\n";
        cin.get(s.name, sizeof(s));
        cout << "Enter Address:\n";
        cin >> s.address;
        cout << "Enter Phone Number:\n";
        cin >> s.phonenumber;
        cin.ignore();
        cout << "Enter Nationality:\n";
        cin >> s.nationality;
        cout << "Enter Email:\n";
        cin >> s.email;
        cout << "Enter Period ('x' days):\n";
        cin >> s.period;
        cout << "Enter Arrival date (dd\\mm\\yyyy):\n";
        cin >> s.arrivaldate;
        f.write(reinterpret_cast<char*>(&s), sizeof(s));
        cout << "\n\n1 Room is successfully booked!!";
        cout << "\n Press esc key to exit, any other key to add another customer detail:";
        test = _getche();
        if (test == 27)
            break;
    }
    f.close();
}
// function to view a list
void hms::list() {
    ifstream f;
    int i;
    f.open("add.txt", ios::in);
    if (!f.is_open())
        exit(0);
    system("cls");
    cout << left; // left align
    
    cout << setw(10) << "ROOM"; //set width through setw()
    cout << setw(2) << "  ";
    cout << setw(20) << "NAME";
    cout << setw(25) << "ADDRESS";
    cout << setw(20) << "PHONE NO.";
    cout << setw(2) << "  ";
    cout << setw(15) << "NATIONALITY";
    cout << setw(2) << "  ";
    cout << setw(20) << "EMAIL";
    cout << setw(9) << "PERIOD";
    cout << setw(2) << "  ";
    cout << setw(10) << "ARRIVALDATE" <<endl;

    for (i = 0; i < 148; i++)
        cout << "-";
    cout << endl;

    while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << setw(10) << s.roomnumber;
        cout << setw(2) << "  ";
        cout << setw(20) << s.name;
        cout << setw(25) << s.address;
        cout << setw(20) << s.phonenumber;
        cout << setw(2) << "  ";
        cout << setw(15) << s.nationality;
        cout << setw(2) << "  ";
        cout << setw(20) << s.email;
        cout << setw(10) << s.period;
        cout << setw(2) << "  ";
        cout << setw(10) << s.arrivaldate <<endl;        
    }

    cout << "\n";
    for (i = 0; i < 148; i++)
        cout << "-";
    cout << endl;

    f.close();
    _getch();
}
// function to delete  a record
void hms::delete1() {
    ifstream f;
    ofstream t;
    int i = 1;
    char roomnumber[20];
    t.open("temp.txt", ios::out);
    if (!t.is_open())
        exit(0);
    f.open("add.txt", ios::in);
    if (!f.is_open())
        exit(0);
    system("cls");
    cout << "Enter the Room Number of the hotel to be deleted from the database: \n";
    cin.ignore();
    cin.getline(roomnumber, sizeof(roomnumber));
    while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            i = 0;
            continue;
        }
        else
            t.write(reinterpret_cast<char*>(&s), sizeof(s));
    }
    if (i == 1) {
        cout << "\n\n Records of Customer in this Room number is not found!!";
        t.close();
        f.close();
        _getch();
    }
    f.close();
    t.close();
    remove("add.txt");
    rename("temp.txt", "add.txt");
    cout << "\n\nThe Customer is successfully removed....";
    t.close();
    f.close();
    _getch();
}
// function to search a record
void hms::search() {
    system("cls");
    ifstream f;
    char query[20];
    int flag = 1;
    f.open("add.txt", ios::in);
    if (!f.is_open())
        exit(0);
	cin.ignore();
    cout << "Enter Room number or Name of the customer to search its details: \n";
    cin.getline(query, sizeof(query));    
    while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (strcmp(s.roomnumber, query) == 0 || strcmp(s.name, query) == 0) {
            flag = 0;
            cout << "\n\tRecord Found\n ";
            cout << "\nRoom Number:\t" << s.roomnumber;
            cout << "\nName:\t" << s.name;
            cout << "\nAddress:\t" << s.address;
            cout << "\nPhone number:\t" << s.phonenumber;
            cout << "\nNationality:\t" << s.nationality;
            cout << "\nEmail:\t" << s.email;
            cout << "\nPeriod:\t" << s.period;
            cout << "\nArrival date:\t" << s.arrivaldate;
            break;
        }
    }
    if (flag == 1) {
        cout << "\n\tRequested Customer could not be found!";
    }
    _getch();
    f.close();
}
// function to edit a record
void hms::edit() {
    ifstream f;
    ofstream f1;
    char roomnumber[20];
    int found = 1;
    system ("cls");

    f.open("add.txt", ios::in);
    if (!f.is_open()) {
        cout << "Error opening file." << endl;
        _getch();
        return;
    }

    f1.open("temp.txt", ios::out);
    if (!f1.is_open()) {
        cout << "Error creating temporary file." << endl;
        f.close();
        _getch();
        return;
    }

    cout << "Enter Room number of the customer to edit: ";
    cin.ignore();
    cin.getline(roomnumber, sizeof(roomnumber));
    while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            found = 0;
            cout << "\nEnter Room Number     : ";
            cin.getline(s.roomnumber, sizeof(s.roomnumber));
            cout << "\nEnter Name            : ";
            cin.getline(s.name, sizeof(s.name));
            cout << "\nEnter Address         : ";
            cin.getline(s.address, sizeof(s.address));
            cout << "\nEnter Phone number    : ";
            cin.getline(s.phonenumber, sizeof(s.phonenumber));
            cout << "\nEnter Nationality     : ";
            cin.getline(s.nationality, sizeof(s.nationality));
            cout << "\nEnter Email           : ";
            cin.getline(s.email, sizeof(s.email));
            cout << "\nEnter Period          : ";
            cin.getline(s.period, sizeof(s.period));
            cout << "\nEnter Arrival date    : ";
            cin.getline(s.arrivaldate, sizeof(s.arrivaldate));
        }
        	f1.write(reinterpret_cast<char*>(&s), sizeof(s));
}   
	f.close();
	f1.close(); 

    if (found == 1) {
        cout << "\n\nTHE RECORD DOESN'T EXIST!!!!";
        remove("temp.txt");
    }
    else
	{
    remove("add.txt");
    rename("temp.txt", "add.txt");
    cout << "\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!";
	}
	_getch();    
}
// function to set color
void hms::setcolor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xB0) + (ForgC & 0x0B);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
// function to set login form
void hms::login() {
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10];
    char user[10] = "user";
    char pass[10] = "pass";
    do {
        system("cls");
        cout << "\n  **************************  LOGIN FORM  **************************  ";
        cout << " \n                       ENTER USERNAME:-";
        cin >> uname;
        cout << " \n                       ENTER PASSWORD:-";
        while (i < 10) {
            pword[i] = _getch();
            c = pword[i];
            if (c == 13) break;
            else cout << "*";
            i++;
        }
        pword[i] = '\0';
        i = 0;
        if (strcmp(uname, user) == 0 && strcmp(pword, pass) == 0) {
            cout << "  \n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL";
            break;
        } else {
            cout << "\n        SORRY !!!!  LOGIN IS UNSUCESSFUL";
            a++;
            _getch();
        }
    } while (a <= 2);
    if (a > 2) {
        cout << "\nSorry you have entered the wrong username and password for four times!!!";
        _getch();
    }
    system("cls");
}
int main()
{
	hms e; // create object
	e.login();
	e.run();
}

