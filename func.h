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
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

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
    float Total_mark = -1;
    float Final_mark = -1;
    float Midterm_mark = -1;
    float Other_mark = -1;
};

struct Course{
    string CourseID;
    string CourseName;
    string ClassName;
    string TeacherName;
    int NumberOfCredit;
    int NumberOfStudent_Max;
    int NumberOfStudent_Current;
    string DayOfWeek;
    string session;
    StudentInfo* student;
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
    int NumberOfStudent_Current;
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
int Login();
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
void AddOneStudentToClass();
void InputStudentFromFile();
//void PrintListOfStudentInClass(string NameOfClass );
void PrintListOfStudentInClass(ClassInfo& temp, int begin, bool isFirst /*1 la dau, 0 la cuoi*/);
void MenuListOfClass(SchoolTime NienKhoa);
void DeleteOneStudent(ClassInfo& temp, int pos); //Xoa sinh vien co vi tri pos trong lop temp
void InputCourseInfo(Course& temp);
void AddCourseToSemester(HocKy& temp);
void PrintListOfCourseInSemester(HocKy& temp);
void EditCourse(Course& temp);
void DeleteCourse(HocKy& temp, ListOfCourse* node);
void AddStudentIntoCourse(Course& temp);
void AddStudentIntoCourse();
void DeleteOneStudent(Course& temp, int pos);
void PrintListOfStudentInCourse(Course& temp);
void ExportFileCSV(Course temp);
bool ImportFileCSV(Course& temp);
void WriteOnFile_Student(StudentInfo *temp, int n, string path);
void WriteOnFile_One_Student(StudentInfo temp, int stt, string path);
void WriteOnFile_One_Course(Course temp, string path);
void WriteOnFile_Course(ListOfCourse* temp, string path);
void EditResult(Course& temp, int pos);
void UploadAllInfor();
void Main_Menu_For_Admin(int find);
void Menu_Create();
void Menu_Add();
void Menu_View();
void Main_Menu_For_Student(int find);
void view(int find);