#include <iostream>
#include <stdlib.h>
#include <cmath> 
#include <iomanip>
#include <limits>

using namespace std;

//Patient
struct Patient
{
    string name;
    int age;
    string blood;
    string gender;
    string problems;
    string status;
    int sNo;

};

struct Doctor
{
    string Docid;
};

struct Staff
{
    int Staffid;
};

void Get_NewPatient_details(Patient *database, int *PatientNum)
{
    cout << "Welcome! Please Enter Your Details Below" << endl;

    cout << "Enter Your Full Name :";
    cin.ignore();
    getline(cin, database[*PatientNum].name);

    cout << "Enter Your age :";
    cin >> database[*PatientNum].age;

    cout << "Enter Your Blood Group :";
    cin.ignore();
    while (true)
    {
        getline(cin, database[*PatientNum].blood);
        if(database[*PatientNum].blood == "A+" || database[*PatientNum].blood == "A-" || database[*PatientNum].blood == "B+" 
            || database[*PatientNum].blood == "B-" || database[*PatientNum].blood == "O+" || database[*PatientNum].blood == "O-" 
            || database[*PatientNum].blood == "AB+" || database[*PatientNum].blood == "AB-"){

            break;
        }
        else{
            cout << "Enter Blood group Correctly ('A+'):";
        }
           
    }
    
    
    cout << "Enter Gender (male or female) : ";
    while (true)
    {
        
        getline(cin, database[*PatientNum].gender);
        if (database[*PatientNum].gender == "male" || database[*PatientNum].gender == "female")
        {
            break;
        }
        else
        {
            cout << "Invalid gender. \nPlease enter 'male' or 'female': ";
        }
    }

    cout << "What problems you have :";
    getline(cin, database[*PatientNum].problems);

    database[*PatientNum].status = "Pending"; 

    database[*PatientNum].sNo = rand(); 

    ++(*PatientNum);

    

    cout << "Your Details have been updated in the Database\n";
}

void Update_details(Patient *database, int PatientNum)
{
    bool patientFound = false;
    int sNo_staff;

    cout << "Enter Patient's Serial Number:";
    cin.ignore();
   cin >> sNo_staff;

    for (int i = 0; i < PatientNum; ++i)
    {
        if (database[i].sNo == sNo_staff)
        {
            cout << "Patient Found!\n";
            cout << "Name: " << database[i].name << endl;
            cout << "Age: " << database[i].age << endl;
            cout << "Blood Group: " << database[i].blood << endl;
            cout << "Gender: " << database[i].gender << endl;
            cout << "Problems: " << database[i].problems << endl;
            cout << "Status: " << database[i].status << endl;

            cout << "Update status to completed=y , Rejected=r? (y/r/n): ";
            char response;
            cin >> response;

            if (response == 'y' || response == 'Y')
            {
                database[i].status = "Completed";
                cout << "Patient status updated to Completed.\n";
            }else if (response == 'r' || response == 'R'){
                database[i].status = "Rejected";
                cout << "Patient status updated to Rejected.\n";
            }

            patientFound = true;
            break;
        }
    }

    if (!patientFound)
    {
        cout << "Patient with Serial " << sNo_staff << " not found in the database.\n";
    }
}

void DeletePatientSno(Patient *database, int &PatientNum)
{
    int deletedCount = 0;

    cout << "Enter patient Sno to delete: ";
    int sNo_DOC;
    cin >> sNo_DOC;

    for (int i = 0; i < PatientNum;)
    {
        if (database[i].sNo == sNo_DOC)
        {
            for (int j = i; j < PatientNum - 1; ++j)
            {
                database[j] = database[j + 1];
            }

            --PatientNum;
            ++deletedCount;
        }
        else
        {
            ++i;
        }
    }

    if (deletedCount > 0)
    {
        cout << "Deleted " << deletedCount << " occurrences of patient " << sNo_DOC << " from the database.\n";
    }
    else
    {
        cout << "Patient with Serial NO " << sNo_DOC << " not found in the database.\n";
    }
}

void displayPatient_Details(Patient *database, int &PatientNum)
{
    if(PatientNum == 0){
        cout << "No Patient Found";
    }
    
    else{
        cout << endl << "-----------------------------------------";
        cout << "\n" << "Patient Database:" << "\n";
        //cout << endl << "Name\t Age\t BloodGroup\tGender\t problems\t status\t Serial Number" << endl;
        cout << endl << setw(2) << "Name" << setw(7) << "Age" << setw(15) << "BloodGroup" << setw(8) << "Gender" << setw(15) << "Problems" << setw(10) << "Status" << setw(15) << "Serial Number" << endl;

        for (int i = 0; i < PatientNum; i++) {
            cout << setw(2) << database[i].name << setw(7) << database[i].age << setw(15) << database[i].blood << setw(8) << database[i].gender << setw(15) << database[i].problems << setw(10) << database[i].status << setw(15) << database[i].sNo << endl;
        }
            cout << endl << "-----------------------------------------";
    }
}


void DoctorMenu(Patient *patientDB, int &PatientNum, Doctor *doc)
{
    int docMenu;

    cout << "Enter doctor id:";
    cin.ignore();
    getline(cin, doc->Docid);

    if (doc->Docid == "x490")
    {
        cout << "1.Display Patient Record\n 2.Update\n";
        cout << "Select Option:";
        cin >> docMenu;

        switch (docMenu)
        {
        case 1:
        {
            displayPatient_Details(patientDB, PatientNum);
            break;
        }

        case 2:
        {
            Update_details(patientDB, PatientNum);
            break;
        }
        default:
            cout << "Enter valid Option\n";
            break;
        }
    }
    else
    {
        cout << "Please Enter Authorized Doctor Id" << endl;
    }
}

void StaffMenu(Patient *patientDB, int &PatientNum, Staff *st)
{
    int StaffMenuOption;
    cout << "Enter Staff id:";
    cin >> st->Staffid;

    if (st->Staffid == 791)
    {
        cout << "1. Display Patient  \n2. Delete Patient\n";
        cout << "Choose your option:";
        cin >> StaffMenuOption;
        switch (StaffMenuOption)
        {
        case 1:
            displayPatient_Details(patientDB, PatientNum);
            break;
        case 2:
            DeletePatientSno(patientDB, PatientNum);
            break;
        default:
            break;
        }
    }
    else
    {
        cout << "Wrong Credential";
    }
}

int main()
{
    int Menubtn;
    const int MAX_PATIENTS = 100;
    Patient patientDB[MAX_PATIENTS];
    int PatientNum = 0;
    Doctor doc;
    Staff st;

    do
    {

        cout << endl << "<<<<< Hospital Management System >>>>>" << endl;

        cout << "1.Patient \n2.Doctor \n3.Staff \n4.Exit" << endl;

        cout << "Select your role:";
        cin >> Menubtn;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            
            cin.clear();
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            continue;
        }

        switch (Menubtn)
        {
        case 1:
            //PatientMenu(patientDB, PatientNum);
            Get_NewPatient_details(patientDB, &PatientNum);
            break;
        case 2:
            DoctorMenu(patientDB, PatientNum, &doc);
            break;
        case 3:
            StaffMenu(patientDB, PatientNum, &st);
            break;
        case 4:
            cout << "Program exiting";
            break;
        default:
            cout << "Enter valid Option\n";
            break;
        }
    } while (Menubtn != 4);

    return 0;
}


/*void PatientMenu(Patient *patientDB, int &PatientNum)
{
    int Menubtn_Patient;

    cout << "1.New patient \n";

    cout << "Are You? :";
    cin >> Menubtn_Patient;

    switch (Menubtn_Patient)
    {
    case 1:
    {
        Get_NewPatient_details(patientDB, &PatientNum);
        break;
    }
    case 2:
    default:
        cout << "Enter Valid Number";
        break;
    }
}*/
