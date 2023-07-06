#include"func.h"

Account* SignIn = NULL;
int quantity;
hcmus NamHoc;

int main(){
  
    // // SetConsoleTitle("Phan Ba Duc - 22120071");
    // // UploadAccount();
    // // Login();
    NamHoc.NumberOfSchoolYear = 0;
    UploadAllInfor();
    
    // InputSchoolYear(NamHoc);
    // InputSemester(NamHoc);
    // CreateSimpleClass(NamHoc.ptr[0]);
    // InputStudentFromFile("18CTT3");
    // AddCourseToSemester(NamHoc.ptr[0].semester[1]);
    //AddCourseToSemester(NamHoc.ptr[0].semester[1]);
    //AddCourseToSemester(NamHoc.ptr[0].semester[1]);
    // PrintListOfStudentInClass(NamHoc.ptr[0].HeadList->data);
    // InputSemester(NamHoc);
    // AddCourseToSemester(NamHoc.ptr[0].semester[2]);
    // InputSemester(NamHoc);
    // AddCourseToSemester(NamHoc.ptr[0].semester[3]);
    // AddCourseToSemester(NamHoc.ptr[0].semester[0]);
    // AddCourseToSemester(NamHoc.ptr[0].semester[0]);
    //PrintListOfCourseInSemester(NamHoc.ptr[0].semester[1]);
    // EditCourse(NamHoc.ptr[0].semester[0].HeadList->data);
    // system("pause");
    // CreateMultipleClasses(NamHoc.ptr[0]);
    //InputSchoolYear(NamHoc);
    // CreateMultipleClasses(NamHoc.ptr[0]);
    // InputStudentFromFile("22CTT2");
    // InputStudentFromFile("22CTT4");   
    MenuListOfClass(NamHoc.ptr[0]);
    
    // PrintListOfStudentInClass(NamHoc.ptr[0].HeadList->pNext->pNext->data);
    // CreateMultipleClasses(NamHoc.ptr[0]);
    // InputSchoolYear(NamHoc);
    // CreateMultipleClasses(NamHoc.ptr[1]);
    // InputStudentFromFile("19CTT2");
    // AddOneStudentToClass("18CTT3");
    // AddOneStudentToClass("18CTT3");
    // AddOneStudentToClass("18CTT5");
    // InputStudentFromFile("18CTT3");
    // InputSchoolYear(NamHoc);
    // CreateMultipleClasses(NamHoc.ptr[1]);
    // InputStudentFromFile("19CTT2");
    // InputSchoolYear(NamHoc);
    // CreateMultipleClasses(NamHoc.ptr[2]);
    // InputStudentFromFile("22CTT2");
    // // cout <<"*************" << endl;
    // // string st;
    // // cout <<"Nhap lop muon them sinh vien: ";
    // // getline(cin, st);
    // // AddOneStudentToClass(st);

    // // cout <<"Nhap lop muon them sinh vien: ";
    // // getline(cin, st);
    // // AddOneStudentToClass(st);

    // // cout <<"Nhap lop muon them sinh vien: ";
    // // getline(cin, st);
    // // AddOneStudentToClass(st);

    // // for (int j = 0; j < NamHoc.NumberOfSchoolYear; j++){
    // //     cout << endl << endl <<"=======================" << endl;
    //     cout << "NAM HOC "<< NamHoc.ptr[1].SchoolYear << endl;
        // ListOfClasses* temp = NamHoc.ptr[0].EndList;
        // while (temp != nullptr){
        //     cout << temp->data.nameClass <<' ';
        //     cout << temp->data.major << ' ';
        //     cout << temp->data.NumberOfStudent_current <<' ';
        //     cout << temp->data.TimeBegin << endl;
        //     // cout << temp->data.nameClass << endl;
        //     // cout << temp->data.major << endl;
        //     // cout << temp->data.TimeBegin << endl;
        //     // cout << temp->data.NumberOfStudent_max << endl;
        //     // cout << temp->data.NumberOfStudent_current << endl;
        //     if (temp == NamHoc.ptr[0].HeadList) break;
        //     //cout <<"-------------------"<<endl;
        //     temp = temp->pPrev;
        // }
    //PrintListOfStudentInClass("18CTT2");

    // //}
    // string st;
    // while (true){
    //     getline(cin, st);
    //     if (st == "NO") break;
    //     AddOneStudentToClass(st);
    // }
    // cout << "NAM HOC "<< NamHoc.ptr[1].SchoolYear << endl;
    //     temp = NamHoc.ptr[1].HeadList;
    //     while (temp != nullptr){
    //         cout << temp->data.nameClass <<' ';
    //         cout << temp->data.major << ' ';
    //         cout << temp->data.NumberOfStudent_current <<' ';
    //         cout << temp->data.TimeBegin << endl;
    //         // cout << temp->data.nameClass << endl;
    //         // cout << temp->data.major << endl;
    //         // cout << temp->data.TimeBegin << endl;
    //         // cout << temp->data.NumberOfStudent_max << endl;
    //         // cout << temp->data.NumberOfStudent_current << endl;
    //         if (temp == NamHoc.ptr[1].EndList) break;
    //         //cout <<"-------------------"<<endl;
    //         temp = temp->pNext;
    //     }

    //     cout << endl<< "NAM HOC "<< NamHoc.ptr[1].SchoolYear << endl;
    //     temp = NamHoc.ptr[1].HeadList;
    //     while (temp != nullptr){
    //         if (temp->data.NumberOfStudent_current != 0){
    //         cout << temp->data.nameClass << endl;
    //         for (int i = 0; i < temp->data.NumberOfStudent_current; i++){
    //             StudentInfo tam = temp->data.student[i];
    //             cout << tam.FirstName << ' ' << tam.LastName << tam.Gender << ' ' << tam.StudentID << ' ' << tam.SocialID << endl;
    //         }
    //         cout <<"-------------------"<<endl;
    //         }
    //         if (temp == NamHoc.ptr[1].EndList) break;
    //         temp = temp->pNext;
    //     }
    system("pause");
    return 0;
}

