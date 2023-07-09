#include"func.h"

Account* SignIn = NULL;
int quantity;
hcmus NamHoc;

int main(){
    NamHoc.NumberOfSchoolYear = 0;
    UploadAllInfor();
    //system("pause");
    //PrintListOfCourseInSemester(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].semester[1]);
    //MenuListOfClass(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1]);
    //cout << endl <<"Hello";
    //SetConsoleTitle("Phan Ba Duc - 22120071");
    UploadAccount();
    while (true){
        system("cls");
        int k = Login();
        if (SignIn[k].IsStaff == 1) Main_Menu_For_Admin(k);
        else Main_Menu_For_Student(k);
    }
   

    //MenuListOfClass(NamHoc.ptr[0]);
    GoTo(0, 30);
    system("pause");
    return 0;
}

