#include<iostream>
#include<windows.h>
#include<fstream>
#include<unistd.h>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<iomanip>


using namespace std;

struct Account{
    string username;
    string password;
    string name;
    string birthday;
    string email;
    string profession;
    string grade;
    string MSSV;
    string ID;
    string contact;
    string faulty;
    bool gender;
    bool IsStaff;
};

struct StudentInfo{
    string StudentID;
    string FirstName;
    string LastName;
    string Gender;
    string DateOfBirth;
    string SocialID;
};

struct Course{
    string CourseID;
    string CourseName;
    string ClassName;
    string TeacherName;
    int NumberOfCredit;
    int NumberOfStudent_Max;
    string DayOfWeek;
    string session;
};

struct ListOfCourse{
    Course data;
    ListOfCourse* pNext;
    ListOfCourse* pPrev;
};

struct HocKy{
    short STT;
    string StartDate;
    string EndDate;
    ListOfCourse* HeadList = nullptr;
    ListOfCourse* EndList = nullptr;
};

struct ClassInfo{
    string TimeBegin;
    string nameClass;
    string major;
    int NumberOfStudent_max;
    int NumberOfStudent_current;
    StudentInfo* student;
};

struct ListOfClasses{
    ClassInfo data;
    ListOfClasses* pNext;
    ListOfClasses* pPrev; //Tạo ra để làm menu lên xuống
};

struct SchoolTime{
    int NumberOfSemester;
    string SchoolYear;
    HocKy semester[4];
    ListOfClasses* HeadList;
    ListOfClasses* EndList;
};

struct hcmus{
    int NumberOfSchoolYear;
    SchoolTime* ptr;
};



void GoTo(SHORT posX, SHORT posY);
void SetColor(int background_color, int text_color);
void TextColor(int color_code);
void UploadAccount();
void DrawBox(int x, int y, int height, int width, int color);
void Login();
void ChangePassword(int pos);
void Information(Account person);
void MenuInfo(int find);
void reallocate(hcmus &NamHoc);
int ConvertFirst(string st);
int ConvertLast(string st);
void InputSchoolYear(hcmus &NamHoc);
void InputSemester(hcmus &NamHoc);
string IntToString(int value);
void CreateSimpleClass(SchoolTime& temp);
void CreateMultipleClasses(SchoolTime& temp);
ListOfClasses* FindClass(SchoolTime temp, string NameOfClass);
void AddOneStudentToClass(string NameOfClass);
void InputStudentFromFile(string NameOfClass);
void PrintListOfStudentInClass(string NameOfClass );
void PrintListOfStudentInClass(ClassInfo& temp);
void MenuListOfClass(SchoolTime NienKhoa);
void DeleteOneStudent(ClassInfo& temp, int pos); //Xoa sinh vien co vi tri pos trong lop temp
void InputCourseInfo(Course& temp);
void AddCourseToSemester(HocKy& temp);
void PrintListOfCourseInSemester(HocKy& temp);
void EditCourse(Course& temp);
void DeleteCourse(HocKy& temp, ListOfCourse* node);