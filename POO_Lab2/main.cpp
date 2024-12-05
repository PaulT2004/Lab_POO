#include <iostream>
#include <cstring>

using namespace std;

const int MAX_STRING = 40;

class Student {
private:
    string firstName;
    string lastName;
    string email;
    string enrollmentDate;
    string dateOfBirth;
    bool graduated;
public:
    Student() {}
    Student(const string& firstName, const string& lastName, const string& email, const string& enrollmentDate, const string& dateOfBirth, bool graduated = false) {
        this->firstName=firstName;
        this->lastName=lastName;
        this->email=email;
        this->enrollmentDate=enrollmentDate;
        this->dateOfBirth=dateOfBirth;
        this->graduated=graduated;
    }

    string ReturnEmail() const {
        return email;
    }

    bool ReturnGraduated() const {
        return graduated;
    }

    void PrintStudent() const {
        cout << "First name: " << firstName << "\nLast name: " << lastName << "\nEmail: " << email << "\nEnrollment date: " << enrollmentDate << "\nDate of birth: " << dateOfBirth << "\n" << endl;
    }
};

class Faculty {
private:
    Student faculty[MAX_STRING];
    string facultyName;
    string abbreviation;
    int countStudents;

public:
    Faculty():countStudents(0) {}
    Faculty(const string& facultyName, const string& abbreviation) {
        this->facultyName=facultyName;
        this->abbreviation=abbreviation;
    }

    string ReturnFacultyName() const {
        return facultyName;
    }

    void PrintFaculty() const {
        cout << "Faculty name: " << facultyName << "\nAbbreviation: " << abbreviation << "\n" << endl;
    }

    void AddStudent(const Faculty& faculty, const Student& student) const {
        faculty.faculty[faculty.countStudents] = student;
        faculty.countStudents++;
    }

    void CreateStudent(const Faculty& faculty) const {
        string firstName;
        string lastName;
        string email;
        string enrollmentDate;
        string dateOfBirth;
        bool graduated = false;

        cout << "Enter the student's first name: ";
        cin >> firstName;
        cout << "Enter the student's last name: ";
        cin >> lastName;
        cout << "Enter the student's email: ";
        cin >> email;
        cout << "Enter the student's enrollment date: ";
        cin >> enrollmentDate;
        cout << "Enter the student's date of birth: ";
        cin >> dateOfBirth;

        Student newStudent(firstName, lastName, email, enrollmentDate, dateOfBirth, graduated);
        AddStudent(faculty, newStudent);
    }

    void GraduateStudent(const Faculty& faculty) const {
        string searchEmail;
        cout << "Insert the student's email: ";
        cin >> searchEmail;

        bool searchStudent=false;
        for (int i=0; i<faculty.countStudents; i++) {
            if (faculty.faculty[i].ReturnEmail() == searchEmail) {
                searchStudent=true;
                if(faculty.faculty[i].ReturnGraduated() == false){
                    faculty.faculty[i].ReturnGraduated() = true;
                    cout << "Student graduated" << endl;
                }
                else{
                    cout << "Student already graduated" << endl;
                }
            }
        }
        if(searchStudent==false){
            cout << "Student not found" << endl;
        }
    }

    void PrintCurrentStudents(const Faculty& faculty) const {
        bool currentStudents=false;
        if(faculty.countStudents==0) {
            cout << "None of the students have learned in this faculty yet" << endl;
        }
        else{
            for(int i=0;i<faculty.countStudents;i++) {
                if(faculty.faculty[i].ReturnGraduated()==false){
                    faculty.faculty[i].PrintStudent();
                    currentStudents=true;
                }
            }
            if(currentStudents==false){
            cout << "None of the students is learning in this faculty now" << endl;
            }
        }
    }

    void PrintGraduatedStudents(const Faculty& faculty) const {
        bool graduatedStudents=false;
        if(faculty.countStudents==0) {
            cout << "None of the students have learned in this faculty yet" << endl;
        }
        else{
            for(int i=0;i<faculty.countStudents;i++) {
                if(faculty.faculty[i].ReturnGraduated()==true){
                    faculty.faculty[i].PrintStudent();
                    graduatedStudents=true;
                }
            }
            if(graduatedStudents==false){
            cout << "None of the students have graduated in this faculty yet" << endl;
            }
        }
    }

    void SearchFacultyStudent(const Faculty& faculty) const {
        string searchEmail;
        cout << "Insert the student's email: ";
        cin >> searchEmail;

        bool searchStudent=false;
        for(int i=0; i<faculty.countStudents; i++) {
            if(faculty.faculty[i].ReturnEmail() == searchEmail) {
                searchStudent=true;
                cout << "Student belongs to this faculty" << endl;
            }
        }
        if(searchStudent==false){
            cout << "Student doesn't belong to this faculty" << endl;
        }
    }

    void SearchStudent(const Faculty& faculty, const string& tempEmail) const {
        for(int i=0; i<faculty.countStudents; i++) {
            if(faculty.faculty[i].ReturnEmail() == tempEmail) {
                cout << "Student belongs to " << faculty.abbreviation << " faculty" << endl;
            }
        }
    }
};

class Field {
private:
    Faculty field[MAX_STRING];
    string fieldName;
    int countFaculties;

public:
    Field():countFaculties(0) {}
    Field(const string& fieldName) {
        this->fieldName=fieldName;
        countFaculties=0;
    }

    void AddFaculty(const Field& field, const Faculty& faculty) const {
        fieeld. field[field.countFaculties] = faculty;
        field.countFaculties++;
    }

    void CreateFaculty(const Field& field) const {
        string facultyName;
        string abbreviation;

        cout << "Enter the faculty name: ";
        cin >> facultyName;
        cout << "Enter the faculty's abbreviation: ";
        cin >> abbreviation;

        Faculty newFaculty(facultyName, abbreviation);
        AddFaculty(newFaculty);
    }

    string ReturnFieldName(){
        return fieldName;
    }

    void PrintFaculties(const Field& field) const {
        for(int i=0;i<field.countFaculties;i++) {
            field.field[i].PrintFaculty();
        }
    }

    void PrintSpecificFaculties(const Field& field) const {
        for(int i=0;i<field.countFaculties;i++) {
            field.field[i].PrintFaculty();
        }
    }

    void SearchSpecificStudent(const Field& field, const string& tempEmail) const {
        for(int i=0;i<field.countFaculties;i++) {
            field.field[i].SearchStudent(field.field[i], tempEmail);
        }
    }

    void SearchSpecificFaculty(const Field& field, const string& tempFacultyName) const {
        for(int i=0;i<field.countFaculties;i++) {
            if(field.field[i].ReturnFacultyName()==tempFacultyName){
                facultyMenu(field.field[i]);
            }
        }
    }

};

class FieldList {
private:
    Field fieldList[MAX_STRING];
    int countFields;

public:
    FieldList():countFields(0) {}


    void AddField(const FieldList& fieldList, const Field& field) const {
        fieldList.fieldList[fieldList.countFields] = field;
        fieldList.countFields++;
    }

    void CreateField(const string& fieldName){
        Field newField(fieldName);
        AddField(newField);
    }

    void AddFacultyField(const FieldList& fieldList, const string& tempFieldName) const {
        for(int i=0;i<fieldList.countFields;i++) {
            if(fieldList.fieldList[i].ReturnFieldName()==tempFieldName){
                fieldList[i].CreateFaculty(tempFieldName);
            }
        }
    }


    void PrintAllFaculties(const FieldList& fieldList) const {
        for(int i=0;i<fieldList.countFields;i++) {
            fieldList.fieldList[i].PrintFaculties(fieldList.fieldList[i]);
        }
    }

    void PrintFieldFaculties(const FieldList& fieldList, const string& tempFieldName) const {
        for(int i=0;i<fieldList.countFields;i++) {
            if(fieldList.fieldList[i].ReturnFieldName()==tempFieldName){
                fieldList.fieldList[i].PrintSpecificFaculties(fieldList.fieldList[i]);
            }
        }
    }

    void SearchingStudent(const FieldList& fieldList, const string& tempEmail) const {
        for(int i=0;i<fieldList.countFields;i++) {
            fieldList.fieldList[i].SearchSpecificStudent(fieldList.fieldList[i], tempEmail);
        }
    }

    void SearchFieldFaculty(const FieldList& fieldList, const string& tempFieldName) const {
        for(int i=0;i<fieldList.countFields;i++) {
            fieldList.fieldList[i].SearchSpecificFaculty(fieldList.fieldList[i], tempFieldName);
        }
    }

};







void facultyMenu(Faculty& faculty) {

    int menuNumber;

    cout << "Faculty menu: What are you looking for?\n1: Add a student\n2: Graduate a student\n3: Print all current students\n4: Print all graduated students\n5: Search a student\n6: Go to main menu\n7: Exit" << endl;
    cin >> menuNumber;

    if(menuNumber==1){
        faculty.CreateStudent(faculty);
        facultyMenu(faculty);
    }
    else if(menuNumber==2){
        faculty.GraduateStudent(faculty);
        facultyMenu(faculty);
    }
    else if(menuNumber==3){
        faculty.PrintCurrentStudents(faculty);
        facultyMenu(faculty);
    }
    else if(menuNumber==4){
        Faculty PrintGraduatedStudents(faculty);
        facultyMenu(faculty);
    }
    else if(menuNumber==5){
        faculty.SearchFacultyStudents(faculty);
        facultyMenu(faculty);
    }
    else if(menuNumber==6){
        //goes to main menu
    }
    else if(menuNumber==7){
        exit(0);
    }
    else{
        cout << "You inserted another number\n" << endl;
        facultyMenu(faculty);
    }
}

void generalMenu(FieldList& fieldList) {
    int menuNumber;

    cout << "General menu: What are you looking for?\n1: Create a new faculty\n2: Search what faculty a student belongs to\n3: Print all current faculties\n4: Print all faculties from a specific field\n5: Go to main menu\n6: Exit" << endl;
    cin >> menuNumber;

    if(menuNumber==1){
        string tempFieldName;
        cout << "Insert in which field you want to add it: " << endl;
        cin >> tempFieldName;

        fieldList.AddFacultyField(fieldList, tempFieldName);
        generalMenu(fieldList);
    }
    else if(menuNumber==2){
        string tempEmail;
        cout << "Insert student's email: " << endl;
        cin >> tempEmail;

        fieldList.SearchingStudent(fieldList, tempEmail);
        generalMenu(fieldList);
    }
    else if(menuNumber==3){
        fieldList.PrintAllFaculties(fieldList);
        generalMenu(fieldList);
    }
    else if(menuNumber==4){
        string tempFieldName;
        cout << "Insert field name: " << endl;
        cin >> tempFieldName;

        PrintFieldFaculties(fieldList, tempFieldName);
        generalMenu(fieldList);
    }
    else if(menuNumber==5){
        mainMenu(fieldList);
    }
    else if(menuNumber==6){
        exit(0);
    }
    else{
        cout << "You inserted another number\n" << endl;
        generalMenu(fieldList);
    }
}

void mainMenu(FieldList& fieldList) {
    int menuNumber;

    cout << "Main menu: What are you looking for?\n1: General operations\n2: Faculty operations\n3: Exit" << endl;
    cin >> menuNumber;

    if(menuNumber==1){
        generalMenu(fieldList);
    }
    else if(menuNumber==2){
        string tempFieldName;
        cout << "Insert field name: " << endl;
        cin >> tempFieldName;

        fieldList.SearchFieldFaculty(fieldList, tempFieldName);
        mainMenu(fieldList);
    }
    else if(menuNumber==3){
        exit(0);
    }
    else{
        cout << "You inserted another number\n" << endl;
        mainMenu(fieldList);
    }
}

int main() {
    FieldList fieldList;

    string fieldName = "MECHANICAL_ENGINEERING";
    Field newField1(fieldName);
    fieldName = "SOFTWARE_ENGINNERING";
    Field newField2(fieldName);
    fieldName = "FOOD_TECHNOLOGY";
    Field newField3(fieldName);
    fieldName = "URBANISM_ARCHITECTURE";
    Field newField4(fieldName);
    fieldName = "VETERINARY_MEDICINE";
    Field newField5(fieldName);

    mainMenu(fieldList);

    return 0;
}
