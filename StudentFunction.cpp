#include "func.h"

void Main_Menu_For_Student(int find){
    extern hcmus NamHoc;
    string choice[5] = {"Your Information", "View", "Log out"};
    GoTo(45,1); cout <<"                                                                " << "\n";
    GoTo(45,2); cout <<" ,---.,--------.,--. ,--.,------.  ,------.,--.  ,--.,--------. " << "\n";
    GoTo(45,3); cout <<"'   .-'--.  .--'|  | |  ||  .-.  \\ |  .---'|  ,'.|  |'--.  .--' " << "\n";
    GoTo(45,4); cout <<"`.  `-.  |  |   |  | |  ||  |  \\  :|  `--, |  |' '  |   |  |    " << "\n";
    GoTo(45,5); cout <<".-'    | |  |   '  '-'  '|  '--'  /|  `---.|  | `   |   |  |    " << "\n";
    GoTo(45,6); cout <<"`-----'  `--'    `-----' `-------' `------'`--'  `--'   `--'    " << "\n";
    GoTo(45,7); cout <<"                                                                " << "\n";
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
    GoTo(66, 7); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
    GoTo(72, 8); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
    DrawBox(60, 10, 7, 30, 3);
    SetColor(7, 0);
    GoTo(65, 12); cout << choice[0];
    TextColor(7);
    GoTo(65, 14); cout << choice[1];
    GoTo(65, 16); cout << choice[2];

    int pos = 0;
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ //Di len
                    TextColor(7);
                    GoTo(65, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 0) pos = 2;
                    else pos--;
                    SetColor(7, 0);
                    GoTo(65, 12 + pos * 2);
                    cout << choice[pos];
                }
                if (c == 80){ //Di Xuong
                    TextColor(7);
                    GoTo(65, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 2) pos = 0;
                    else pos++;
                    SetColor(7, 0);
                    GoTo(65, 12 + pos * 2);
                    cout << choice[pos];
                }
            }
            if (c == 13){ //Enter
                TextColor(7);
                if (pos == 0) MenuInfo(find);
                if (pos == 1) view(find);
                
                TextColor(7);
                system("cls");
                GoTo(45,1); cout <<"                                                                " << "\n";
                GoTo(45,2); cout <<" ,---.,--------.,--. ,--.,------.  ,------.,--.  ,--.,--------. " << "\n";
                GoTo(45,3); cout <<"'   .-'--.  .--'|  | |  ||  .-.  \\ |  .---'|  ,'.|  |'--.  .--' " << "\n";
                GoTo(45,4); cout <<"`.  `-.  |  |   |  | |  ||  |  \\  :|  `--, |  |' '  |   |  |    " << "\n";
                GoTo(45,5); cout <<".-'    | |  |   '  '-'  '|  '--'  /|  `---.|  | `   |   |  |    " << "\n";
                GoTo(45,6); cout <<"`-----'  `--'    `-----' `-------' `------'`--'  `--'   `--'    " << "\n";
                GoTo(45,7); cout <<"                                                                " << "\n";
                n = NamHoc.NumberOfSchoolYear - 1;
                hocky_stt = NamHoc.ptr[n].NumberOfSemester;
                GoTo(66, 7); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
                GoTo(72, 8); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
                DrawBox(60, 10, 7, 30, 3);
                for (int i = 0; i < 3; i++){
                    if (i == pos) SetColor(7, 0);
                    GoTo(65, 12 + i * 2); cout << choice[i];
                    if (i == pos) TextColor(7);
                }

                if (pos == 2)
                    return;
                
            }
        }
    }
}

void view(int find){
    TextColor(7);
    system("cls");
    extern Account* SignIn;
    extern hcmus NamHoc;
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
    if (NamHoc.ptr[n].semester[hocky_stt].HeadList == nullptr){
        SetColor(14,5);
        GoTo(66,5); cout <<"There is no course" << endl;
        TextColor(7);
        system("pause");
        return;
    }
    ifstream ifs1;
    GoTo(59, 0); cout <<"LIST OF COURSE IN THIS SEMESTER";
    SetColor(14, 1);
    for (int i = 0; i <= 147; i++){
        GoTo(i, 2); cout <<' ';
    }
    GoTo(0, 2); cout << "COURSE ID";
    GoTo(20, 2);cout << "COURSE NAME";
    GoTo(43, 2);cout << "CLASS NAME";
    GoTo(58, 2);cout << "TEACHER NAME";
    GoTo(78, 2);cout << "DAY OF WEEK";
    GoTo(91, 2);cout << "SESSION";
    GoTo(100, 2);cout <<"Midterm Mark";
    GoTo(114, 2);cout <<"Final Mark";
    GoTo(126, 2);cout <<"Other Mark";
    GoTo(138, 2);cout <<"Total Mark";
//COURSE ID          COURSE NAME            CLASS NAME      TEACHER NAME         DAY OF WEEK  SESSION  Midterm Mark  Final Mark  Other Mark  Total Mark
//CSC00004    Nhap mon Cong nghe Thong tin    18CTT3      Huynh Thuy Bao Tran        MON        S2          10          10          10         10
    TextColor(7);

    
    string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(NamHoc.ptr[n].semester[hocky_stt].STT);
    ifstream ifs(path + "\\Course.csv");
    char ch;
    int dem = 3;
    while (!ifs.eof()){
        ListOfCourse* node = new ListOfCourse;
        node->pNext = nullptr;
        node->pPrev = nullptr;
        getline(ifs, node->data.CourseID, ',');
        getline(ifs, node->data.CourseName, ',');
        getline(ifs, node->data.ClassName, ',');
        getline(ifs, node->data.TeacherName, ',');
        ifs >> node->data.NumberOfCredit;
        ifs >> ch;
        ifs >> node->data.NumberOfStudent_Max;
        ifs.ignore();
        getline(ifs, node->data.DayOfWeek, ',');
        getline(ifs, node->data.session);
        node->data.student = new StudentInfo[node->data.NumberOfStudent_Max + 1];
        node->data.NumberOfStudent_Current = 0;
               
        ifs1.open(path + '\\' + node->data.CourseID + ".csv");
        if (ifs1){
            int tam;
            char ch1;
            while (!ifs1.eof()){
                ifs1 >> tam;
                ifs1 >> ch1; //Doc dau phay
                getline(ifs1, node->data.student[tam - 1].StudentID, ',');
                getline(ifs1, node->data.student[tam - 1].FirstName, ',');
                getline(ifs1, node->data.student[tam - 1].LastName, ',');
                getline(ifs1, node->data.student[tam - 1].Gender, ',');
                getline(ifs1, node->data.student[tam - 1].DateOfBirth, ',');
                getline(ifs1, node->data.student[tam - 1].SocialID, ',');
                ifs1 >> node->data.student[tam - 1].Midterm_mark;
                ifs1 >> ch1;
                ifs1 >> node->data.student[tam - 1].Final_mark;
                ifs1 >> ch1;
                ifs1 >> node->data.student[tam - 1].Other_mark;
                ifs1 >> ch1;
                ifs1 >> node->data.student[tam - 1].Total_mark;
                ifs1.ignore();
                if (node->data.student[tam - 1].StudentID == SignIn[find].MSSV){
                    GoTo(0, dem); cout << node->data.CourseID;
                    GoTo(13, dem); cout << node->data.CourseName;
                    GoTo(45, dem); cout << node->data.ClassName;
                    GoTo(56, dem); cout << node->data.TeacherName;
                    GoTo(82, dem); cout << node->data.DayOfWeek;
                    GoTo(93, dem); cout << node->data.session;
                    if (node->data.student[tam - 1].Midterm_mark != -1){
                        GoTo(105, dem); 
                        cout << node->data.student[tam - 1].Midterm_mark;
                    }
                    if (node->data.student[tam - 1].Final_mark != -1){
                        GoTo(117, dem); 
                        cout << node->data.student[tam - 1].Final_mark;
                    }
                    if (node->data.student[tam - 1].Other_mark != -1){
                        GoTo(129, dem);
                        cout << node->data.student[tam - 1].Other_mark;
                    }
                    if (node->data.student[tam - 1].Final_mark != -1){
                        GoTo(140, dem); 
                        cout << node->data.student[tam - 1].Total_mark;
                    }
                    dem++;
                    break;
                }
            }
            node->data.NumberOfStudent_Current = tam;
        }
        ifs1.close();
    }
    ifs.close();
    GoTo(0, 20);
    system("pause");
}