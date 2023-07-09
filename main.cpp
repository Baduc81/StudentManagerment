#include"func.h"

Account* SignIn = NULL;
int quantity;
hcmus NamHoc;

int main(){
    NamHoc.NumberOfSchoolYear = 0;
    UploadAllInfor();
    //PrintListOfCourseInSemester(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].semester[1]);
    //MenuListOfClass(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1]);
    //cout << endl <<"Hello";
    //SetConsoleTitle("Phan Ba Duc - 22120071");
    UploadAccount();
    Main_Menu_For_Admin(Login());

    //MenuListOfClass(NamHoc.ptr[0]);
    GoTo(0, 30);
    system("pause");
    return 0;
}

