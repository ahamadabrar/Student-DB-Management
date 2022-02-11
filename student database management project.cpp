#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;

struct student
    {
        char firstName[50], lastName[50];
        char course[100];
        string section;
        int regNumber;
        float CGPA;
    };

int main()
{
    FILE *filep, *filet;
    char another1, choice1;

    student stdnt;
    char last_name[50];
    int regN;
    long int stdntObjSize;

    filep=fopen("users.txt","rb+");

    if (filep == NULL)
    {
        filep = fopen("users.txt","wb+");

        if (filep==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }


    stdntObjSize = sizeof(stdnt);

    while(1)
    {
        system("cls");

        cout << "\t\t====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout <<"\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. Add    Records";
        cout << "\n \t\t\t 2. Show   Records";
        cout << "\n \t\t\t 3. Modify Records";
        cout << "\n \t\t\t 4. Delete Records";
        cout << "\n \t\t\t 5. Exit   Program";
        cout << "\n\n";
        cout << "\t\t\t Select Your Choice :=> ";
        fflush(stdin);
        choice1 = getche();
        switch(choice1)
        {
        case '1' :
            fseek(filep,0,SEEK_END);
            another1 ='Y';
            while(another1 == 'Y' || another1 == 'y')
            {
                system("cls");
                cout << "Enter the First Name : ";
                cin >> stdnt.firstName;
                cout << "Enter the Last Name : ";
                cin >> stdnt.lastName;
                cout << "Enter the Course    : ";
                cin >> stdnt.course;
                cout << "Enter the Section(string form)   : ";
                cin >> stdnt.section;
                cout << "Enter registration number(numerical)   : ";
                cin >> stdnt.regNumber;
                cout << "Enter the CGPA(float of point form)   : ";
                cin >> stdnt.CGPA;
                fwrite(&stdnt,stdntObjSize,1,filep);
                cout << "\n Add Another Record (Y/N) ";
                fflush(stdin);
                another1 = getchar();
            }
            break;
        case '2':
            system("cls");
            rewind(filep);
            cout << "=== View the Records in the Database ===";
            cout << "\n";
            while (fread(&stdnt,stdntObjSize,1,filep) == 1)
            {
                cout <<"Name: " << stdnt.firstName  <<" "<< stdnt.lastName;
                cout <<"\nRegistration Number: " <<stdnt.regNumber;
                cout <<"\nCourse: " <<stdnt.course;
                cout<<"\nSection: "<< stdnt.section;
                cout <<"\nCGPA: " << stdnt.CGPA;
                cout<<"\n\n";
            }
            cout << "\n\n";
            system("pause");
            break;

        case '3' :
            system("cls");
            another1 = 'Y';
            while (another1 == 'Y'|| another1 == 'y')
            {
                cout << "\n Enter the last name OR reg number of the student : ";
                cout<<"Last Name(if dont know type anything): ";
                cin >> last_name;
                cout<<"Reg Number: ";
                cin >> regN;

                rewind(filep);
                while (fread(&stdnt,stdntObjSize,1,filep) == 1)
                {
                    if (strcmp(stdnt.lastName,last_name) == 0 || stdnt.regNumber==regN)
                    {
                        cout << "Enter the new First Name : ";
                        cin >> stdnt.firstName;
                        cout << "Enter the new Last Name : ";
                        cin >> stdnt.lastName;
                        cout << "Enter the new Course    : ";
                        cin >> stdnt.course;
                        cout << "Enter the new Section(string form)   : ";
                        cin >> stdnt.section;
                        cout << "Enter new registration number(numerical)   : ";
                        cin >> stdnt.regNumber;
                        cout << "Enter new CGPA(float(10.5)form)   : ";
                        cin >> stdnt.CGPA;

                        fseek(filep, - stdntObjSize, SEEK_CUR);
                        fwrite(&stdnt,stdntObjSize,1,filep);
                        break;
                    }
                    else
                        cout<<"record not found";
                }
                cout << "\n Modify Another Record (Y/N) ";
                fflush(stdin);
                another1 = getchar();
            }
            break;


        case '4':
            system("cls");
            another1 = 'Y';
            while (another1 == 'Y'|| another1 == 'y')
            {
                cout << "\n Enter the last name to delete student record  : ";
                cin >> last_name;

                filet = fopen("temp.dat", "wb");

                rewind(filep);
                while (fread (&stdnt, stdntObjSize,1,filep) == 1)

                    if (strcmp(stdnt.lastName,last_name) != 0)
                    {
                        fwrite(&stdnt,stdntObjSize,1,filet);
                    }
                fclose(filep);
                fclose(filet);
                remove("users.txt");
                rename("temp.dat","users.txt");

                filep=fopen("users.txt","rb+");

                cout << "\n Delete Another Record (Y/N) ";
                fflush(stdin);
                another1 = getchar();
            }

            break;

        case '5':
            fclose(filep);
            cout << "\n\n";
            cout << "\t\t     THANK YOU FOR USING THIS SOFTWARE";
            cout << "\n\n";
            exit(0);
        }
    }


    system("pause");
    return 0;
}
