#include"func.h"

Account* SignIn = NULL;
int quantity;
hcmus NamHoc;

int main(){
  
    // SetConsoleTitle("Phan Ba Duc - 22120071");
    UploadAccount();
    Main_Menu_For_Admin(Login());

    //NamHoc.NumberOfSchoolYear = 0;
    //UploadAllInfor();
    //MenuListOfClass(NamHoc.ptr[0]);
    GoTo(0, 30);
    system("pause");
    return 0;
}

