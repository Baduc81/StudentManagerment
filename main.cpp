#include"func.h"

Account* SignIn = NULL;
int quantity;
hcmus NamHoc;

int main(){
    // // SetConsoleTitle("Phan Ba Duc - 22120071");
    // // UploadAccount();
    // // Login();
    NamHoc.NumberOfSchoolYear = 0;
    InputSchoolYear(NamHoc);
    CreateMultipleClasses(NamHoc.ptr[0]);
    //CreateMultipleClasses(NamHoc.ptr[0]);
    //CreateSimpleClass(NamHoc.ptr[0]);
    InputStudentFromFile("22CTT3");
    InputStudentFromFile("22CTT2");
    InputStudentFromFile("22CTT4");

    // PrintListOfStudentInClass("18CTT3");
    // CreateMultipleClasses(NamHoc.ptr[0]);
    // InputSchoolYear(NamHoc);
    // CreateMultipleClasses(NamHoc.ptr[1]);
    // InputStudentFromFile("19CTT2");
    // AddOneStudentToClass("18CTT2");
    MenuListOfClass(NamHoc.ptr[0]);
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
    // PrintListOfStudentInClass("19CTT2");

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
}

