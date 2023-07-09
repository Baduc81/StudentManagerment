#include "func.h"

void reallocate(hcmus &KHTN){
    if (KHTN.NumberOfSchoolYear == 0){
        KHTN.NumberOfSchoolYear++;
        KHTN.ptr = new SchoolTime[1];
        KHTN.ptr[0].NumberOfSemester = 0;
        return;
    }
    SchoolTime* temp = new SchoolTime[KHTN.NumberOfSchoolYear + 1];
    for (int i = 0; i < KHTN.NumberOfSchoolYear; i++)
        temp[i] = KHTN.ptr[i];
    delete[] KHTN.ptr;
    KHTN.NumberOfSchoolYear++;
    KHTN.ptr = new SchoolTime[KHTN.NumberOfSchoolYear];
    for (int i = 0; i < KHTN.NumberOfSchoolYear - 1; i++)
        KHTN.ptr[i] = temp[i];
    KHTN.ptr[KHTN.NumberOfSchoolYear - 1].NumberOfSemester = 0;
    delete[] temp;
}

void InputSchoolYear(hcmus &KHTN){
    TextColor(7);
    system("cls");
    reallocate(KHTN);
    bool check;
    int n = KHTN.NumberOfSchoolYear - 1;
    KHTN.ptr[n].HeadList = nullptr;
    KHTN.ptr[n].EndList = nullptr;
    do {
        check = 0;
        GoTo(53, 8); cout <<"Input School Year (ex: 2018-2019): ";
        getline(cin, KHTN.ptr[n].SchoolYear);
        for (int i = 0; i < n; i++){
            if (KHTN.ptr[i].SchoolYear == KHTN.ptr[KHTN.NumberOfSchoolYear - 1].SchoolYear){
                TextColor(4);
                GoTo(53, 9); cout << "This school year already exists" << endl;
                sleep(1);
                system("cls");
                TextColor(7);
                check = 1;
                break;
            }
        }
    }while (check);
    TextColor(2);
    GoTo(53, 9); cout << "The new school year has been added" << endl;
    TextColor(7);
    ofstream ofs1("Data\\SchoolYear.txt", ios:: app);
    if (ofs1) ofs1 << endl<< KHTN.ptr[n].SchoolYear;
    ofs1.close();
    string path = "Data\\" + KHTN.ptr[n].SchoolYear; //Địa chỉ thư mục năm học
    int kiemtra = mkdir(path.c_str());
    if (kiemtra < 0){
        GoTo(0, 0); cout <<"Error creating folder for new school year" << endl;
        system("pause");
    }
    path = path + "\\Class";
    kiemtra = mkdir(path.c_str());
    if (kiemtra < 0){
        GoTo(0, 0); cout <<"Error creating class folder for new school year" << endl;
        system("pause");
    }

    if (n == 0) return;
    ListOfClasses* temp = KHTN.ptr[n - 1].HeadList;
    while (temp != nullptr){
        if (ConvertLast(KHTN.ptr[n].SchoolYear) - ConvertFirst(temp->data.TimeBegin) <= 4){
            KHTN.ptr[n].HeadList = temp;
            break;
        }
        temp = temp->pNext;
    }
    KHTN.ptr[n].EndList = KHTN.ptr[n - 1].EndList;

    /*Ghi lại danh sách sinh viên năm học mới lên file*/
    temp = KHTN.ptr[n].HeadList;
    ofstream ofs("Data\\" + KHTN.ptr[n].SchoolYear + "\\List Of Classes.csv");
    while (temp != nullptr){
        string address = path + '\\' + temp->data.nameClass;
        WriteOnFile_Student(temp->data.student, temp->data.NumberOfStudent_Current, address);
        /*Ghi danh sach lop len List Of Classes*/
        ofs << temp->data.nameClass << ',';
        ofs << temp->data.major << ',';
        ofs << temp->data.TimeBegin << ',';
        ofs << temp->data.NumberOfStudent_max;
        /*---------*/
        if (temp == KHTN.ptr[n].EndList) break;
        else ofs << endl;
        temp = temp->pNext;
    }
    ofs.close();
}

void InputSemester(hcmus &KHTN){
    TextColor(7);
    system("cls");
    string temp;
    while(true){
        GoTo(55, 8); cout <<"Enter the school year of new semester: ";
        getline(cin, temp);
        for (int i = 0; i < KHTN.NumberOfSchoolYear; i++){
            if (KHTN.ptr[i].SchoolYear == temp){
                if (KHTN.ptr[i].NumberOfSemester == 3){
                    GoTo(55, 9); cout <<"This school year has full 3 semesters" << endl;
                    return;
                }
                KHTN.ptr[i].NumberOfSemester++;
                short hocky;
                bool ktra = 1;
                while (ktra){
                    ktra = 0;
                    GoTo(55, 8); cout <<"Enter the school year of new semester: " << temp;
                    GoTo(55, 9); cout <<"Enter semester  : ";
                    cin >> hocky;
                    cin.ignore();
                    for (int j = 1; j < KHTN.ptr[i].NumberOfSemester; j++){
                        if (hocky == KHTN.ptr[i].semester[j].STT){
                            TextColor(4);
                            GoTo(55,10);
                            cout <<"School year " << KHTN.ptr[i].SchoolYear <<" has already had this semester";
                            TextColor(7);
                            ktra = 1;
                            sleep(1);
                            system("cls");
                            break;
                        }
                    }
                }
                KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].STT = hocky;
                GoTo(55, 10);cout <<"Enter start date: ";
                getline(cin, KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].StartDate);
                GoTo(55, 11);cout <<"Enter end date  : ";
                getline(cin, KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].EndDate);
                TextColor(2);
                GoTo(55,12); cout <<"Successfully" << endl;
                TextColor(7);
                system("pause");
                //KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1] = KHTN.ptr[i].NumberOfSemester;
                KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].HeadList = nullptr;
                KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].EndList = nullptr;

                ofstream ofs("Data\\" + temp + "\\List Of Semester.csv", ios::app);
                if (ofs){
                    if (KHTN.ptr[i].NumberOfSemester != 1) ofs << endl;
                    ofs << KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].STT << ',';
                    ofs << KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].StartDate << ',';
                    ofs << KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].EndDate;
                }
                ofs.close();

                string path = "Data\\" + temp + '\\' + "Semester" + to_string(KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester].STT);
                int check = mkdir(path.c_str());
                if (check < 0) cout << "Error creating folder for new semester" << endl;

                // path = path + "\\Course.csv";
                // ofs.open(path, ios::out);
                // if (!ofs) cout << "Co loi khi tao file thong tin khoa hoc";
                // ofs << "COURSE ID,";
                // ofs << "COURSE NAME,";
                // ofs << "CLASS NAME,";
                // ofs << "TEACHER NAME,";
                // ofs << "CREDITs,";
                // ofs << "STUDENT_Max,";
                // ofs << "DAY OF WEEK,";
                // ofs << "SESSION" << endl;
                // ofs.close();
                return;
            }
        }
        TextColor(4);
        GoTo(55, 9); cout <<"This school year doesn't exist" << endl;
        TextColor(7);
        sleep(1);
        system("cls");
    }
}

ListOfClasses* FindClass(SchoolTime temp, string NameOfClass){
    ListOfClasses* node = temp.HeadList;
    while (node != nullptr){
        if (node->data.nameClass == NameOfClass) return node;
        if (node == temp.EndList) return nullptr;
        node = node->pNext;
    }
    return nullptr;
}

string IntToString(int value){
    string st = "";
    while (value != 0){
        st = char(value % 10 + 48) + st;
        value /= 10;
    }
    return st;
}

void CreateSimpleClass(SchoolTime& temp){
    //extern hcmus NamHoc;
    //SchoolTime temp = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1];
    TextColor(7);
    system("cls");
    ListOfClasses* node = new ListOfClasses;

    do{
        GoTo(56, 9); cout <<"Enter new name class: ";
        getline(cin, node->data.nameClass);
        if (FindClass(temp, node->data.nameClass) != nullptr){
            GoTo(56, 10); TextColor(4);
            cout << "This class name already exists, please enter another name" << endl;
            TextColor(7);
        }
        else break;
    }while(true);
    /*Tao thu muc lop moi*/
    string path = "Data\\" + temp.SchoolYear + "\\Class\\" + node->data.nameClass + ".csv";
    ofstream ofs(path);
    if (!ofs) {
        TextColor(4);
        GoTo(0, 0); cout <<"Error creating file for new class" << node->data.nameClass << endl;
        TextColor(2);
        return;
    }
    // ofs << "STT,";
    // ofs << "First Name,";
    // ofs << "Last Name,";
    // ofs << "Gender,";
    // ofs << "Birthday,";
    // ofs << "Student ID,";
    // ofs << "Social ID,";
    // ofs << "Midterm Mark,";
    // ofs << "Final Mark,";
    // ofs << "Other Mark,";
    // ofs << "Total Mark" << endl;
    ofs.close();
    /*-----------------*/
    GoTo(56, 10); cout <<"Enter the major: ";
    getline(cin, node->data.major);
    node->data.TimeBegin = temp.SchoolYear;
    GoTo(56, 11); cout <<"Enter the maximum number of student: ";
    cin >> node->data.NumberOfStudent_max;
    TextColor(2);
    GoTo(56, 12); cout << "Successfully" << endl;
    TextColor(7);
    system("pause");
    TextColor(7);
    cin.ignore();
    node->data.student = new StudentInfo[node->data.NumberOfStudent_max + 1];
    node->data.NumberOfStudent_Current = 0;
    node->pNext = nullptr;
    node->pPrev = nullptr;

    if (temp.HeadList == nullptr) temp.HeadList = node;
    else if (temp.EndList == nullptr){
        temp.EndList = node;
        temp.HeadList->pNext = temp.EndList;
        temp.EndList->pPrev = temp.HeadList;
    }
    else {
        node->pPrev = temp.EndList;
        temp.EndList->pNext = node;
        temp.EndList = node;
    }
    /*Ghi danh sach lop*/
    path = "Data\\" + temp.SchoolYear + "\\List Of Classes.csv";
    ofs.open(path, ios::app);
    if (ofs){
        if (node != temp.HeadList) ofs << endl;
        ofs << node->data.nameClass << ',';
        ofs << node->data.major << ',';
        ofs << node->data.TimeBegin << ',';
        ofs << node->data.NumberOfStudent_max;

    }
    ofs.close();
    /*--------------*/
    //NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1] = temp;
}

void CreateMultipleClasses(SchoolTime& temp){
    TextColor(7);
    system("cls");
    //extern hcmus NamHoc;
    //SchoolTime temp = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1];
    string name;
    GoTo(45, 8); cout <<"Enter the class abbreviation (Ex: CLC, APCS, CTT,...): ";
    getline(cin, name);
    name = temp.SchoolYear[3] + name;
    name = temp.SchoolYear[2] + name;
    string chuyenNganh;
    GoTo(45, 9); cout <<"Enter major: ";
    getline(cin, chuyenNganh);
    GoTo(45, 10);cout <<"Enter the number of classes: ";
    int NumberStudent, NumberClasses;
    cin >> NumberClasses;
    GoTo(45, 11);cout <<"Enter the maximum number of student: ";
    cin >> NumberStudent;
    cin.ignore();

    for (int i = 1; i <= NumberClasses; i++){
        
        //Vi day la tao lop tu dong danh so tu 1 den n, nen nhieu khi co lop da tao thu cong 
        //tu truoc. Vi vay ta phai kiem tra lop da ton tai chua roi moi tao
        if (FindClass(temp, name + IntToString(i)) != nullptr) continue;
        
        ListOfClasses* node = new ListOfClasses;
        node->data.nameClass = name + IntToString(i);
        node->data.major = chuyenNganh;
        node->data.NumberOfStudent_Current = 0;
        node->data.NumberOfStudent_max = NumberStudent;
        node->data.TimeBegin = temp.SchoolYear;
        node->data.student = new StudentInfo[node->data.NumberOfStudent_max + 1];
        node->pNext = nullptr;
        node->pPrev = nullptr;

        if (temp.HeadList == nullptr) temp.HeadList = node;
            else if (temp.EndList == nullptr){
                temp.EndList = node;
                temp.HeadList->pNext = temp.EndList;
                temp.EndList->pPrev = temp.HeadList;
            }
                else {
                    node->pPrev = temp.EndList;
                    temp.EndList->pNext = node;
                    temp.EndList = node;
                }
        /*Tao thu muc lop moi*/
        string path = "Data\\" + temp.SchoolYear + "\\Class\\" + node->data.nameClass + ".csv";
        ofstream ofs(path);
        if (!ofs) {
            GoTo(0, 0);cout <<"Error creating file for new class " << node->data.nameClass << endl;
            return;
        }
        // ofs << "STT,";
        // ofs << "First Name,";
        // ofs << "Last Name,";
        // ofs << "Gender,";
        // ofs << "Birthday,";
        // ofs << "Student ID,";
        // ofs << "Social ID,";
        // ofs << "Midterm Mark,";
        // ofs << "Final Mark,";
        // ofs << "Other Mark,";
        // ofs << "Total Mark" << endl;
        ofs.close();
        /*-------------*/
         /*Ghi danh sach lop*/
        path = "Data\\" + temp.SchoolYear + "\\List Of Classes.csv";
        ofs.open(path, ios::app);
        if (ofs){
            if (node != temp.HeadList) ofs << endl;
            ofs << node->data.nameClass << ',';
            ofs << node->data.major << ',';
            ofs << node->data.TimeBegin << ',';
            ofs << node->data.NumberOfStudent_max;

        }
        ofs.close();
        /*--------------*/
    }
    TextColor(2);
    GoTo(45, 12); cout <<"Successfully" << endl;
    TextColor(7);
    system("pause");
    //NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1] = temp;
}

//Chỉ áp dụng cho các lớp ở năm học hiện tại. Không áp dụng cho các năm trước
void AddOneStudentToClass(){
    TextColor(7);
    system("cls");
    extern hcmus NamHoc;
    string NameOfClass;
    GoTo(45, 8); cout << "Enter name of class: ";
    getline(cin, NameOfClass);

    ListOfClasses* node = FindClass(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1], NameOfClass);
    if (node == nullptr) {
        TextColor(4);
        GoTo(45, 9); cout <<"Khong ton tai lop nay hoac lop nay da tot nghiep" << endl;
        TextColor(7);
        system("pause");
        return;
    }
    if (node->data.NumberOfStudent_Current == node->data.NumberOfStudent_max){
        TextColor(4);
        GoTo(45, 9); cout <<"Lop da day sinh vien" << endl;
        TextColor(7);
        system("pause");
        return;
    }
    GoTo(45, 9); cout <<"Enter student's information" << endl;
    int i = node->data.NumberOfStudent_Current++;
    GoTo(45, 10); cout <<"\t Enter first name              : ";
    getline(cin, node->data.student[i].FirstName);
    GoTo(45, 11); cout <<"\t Enter last name               : ";
    getline(cin, node->data.student[i].LastName);
    GoTo(45, 12); cout <<"\t Enter gender                  : ";
    getline(cin, node->data.student[i].Gender);
    GoTo(45, 13); cout <<"\t Enter date of birth (dd/mm/yy): ";
    getline(cin, node->data.student[i].DateOfBirth);
    GoTo(45, 14); cout <<"\t Enter student ID              : ";
    getline(cin, node->data.student[i].StudentID);
    GoTo(45, 15); cout <<"\t Enter social ID               : ";
    getline(cin, node->data.student[i].SocialID);
    TextColor(2);
    GoTo(45, 16); cout << "This student has been added to the class" << endl;
    TextColor(7);
    system("pause");
    /*Ghi thong tin len file*/
    string path = "Data\\" + NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].SchoolYear + "\\Class\\" + node->data.nameClass;
    WriteOnFile_One_Student(node->data.student[i], i, path);
}

//Chỉ áp dụng cho các lớp ở năm học hiện tại. Không áp dụng cho các năm trước
void InputStudentFromFile(){
    TextColor(7);
    system("cls");
    string link, NameOfClass;
    extern hcmus NamHoc;
    GoTo(45, 8); cout <<"Link: ";
    getline(cin, link);
    for (int i = link.length() - 5; i >= 0; i--){
        if (link[i] == '\\') break;
        NameOfClass = link[i] + NameOfClass;
    }
    //cout << "Name: "<<NameOfClass << endl;
    //system("pause");
    SchoolTime temp = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1];
    ListOfClasses* tam = temp.HeadList;
    while (tam != nullptr){
        if (tam->data.nameClass == NameOfClass) break;
        if (tam == temp.EndList || tam->pNext == nullptr){ // neu chay den cuoi danh sach ma khong co ten lop xuat hien thi thoat chuong trinh
            TextColor(4);
            GoTo(45, 9); cout << "This class doesn't exist" << endl;
            TextColor(7);
            system("pause");
            return; 
        }
        tam = tam->pNext;
    }
    
    //NameOfClass = "Data\\" + NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].SchoolYear + "\\Class\\" + NameOfClass + ".csv";
    ifstream ifs(link);
    if (!ifs){
        GoTo(45,9); cout <<"Can not open file" << endl;
        system("pause");
        return;
    }

    string num, firstname, lastname, birthday, MSSV, ID, sex;
    getline(ifs, num, ',');
    getline(ifs, MSSV, ',');
    getline(ifs, firstname, ',');
    getline(ifs, lastname, ',');
    getline(ifs, sex, ',');
    getline(ifs, birthday, ',');
    getline(ifs, ID);
    //cout << num <<' '<< firstname <<' '<<lastname<<' '<< sex <<' '<<birthday<<' '<<MSSV <<' '<< ID << endl;
    while (!ifs.eof()){
        if (tam->data.NumberOfStudent_Current == tam->data.NumberOfStudent_max){ //lop hoc con du bao nhieu slot thi se them hs vao, so con lai thi khong them vao
            GoTo(45, 9);cout <<"The class is full of students, only a few members can be added" << endl;
            break;
        }
        int i = tam->data.NumberOfStudent_Current++;
        getline(ifs, num, ',');
        getline(ifs, tam->data.student[i].StudentID, ',');
        getline(ifs, tam->data.student[i].FirstName, ',');
        getline(ifs, tam->data.student[i].LastName, ',');
        getline(ifs, tam->data.student[i].Gender, ',');
        getline(ifs, tam->data.student[i].DateOfBirth, ',');
        getline(ifs, tam->data.student[i].SocialID);
        //cout << tam->data.student[i].StudentID <<' '<<tam->data.student[i].FirstName  <<' '<<tam->data.student[i].LastName;
        //cout << ' '<<tam->data.student[i].Gender<<' '<<tam->data.student[i].DateOfBirth << ' '<<tam->data.student[i].SocialID << endl;
        //system("pause");
    }
    if (ifs.eof()){
        GoTo(45, 9);
        TextColor(2);
        cout <<"Successfully";
        system("pause");
        TextColor(7);
    }
    ifs.close();
    string path = "Data\\" + NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].SchoolYear + "\\Class\\" + tam->data.nameClass;
    WriteOnFile_Student(tam->data.student, tam->data.NumberOfStudent_Current, path);
}

//Chỉ áp dụng cho các lớp ở năm học hiện tại. Không áp dụng cho các năm trước
void PrintListOfStudentInClass(string NameOfClass ){
    system("cls");
    extern hcmus NamHoc;
    SchoolTime temp = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1];
    ListOfClasses* tam = temp.HeadList;
    while (tam != nullptr){
        if (tam->data.nameClass == NameOfClass) break;
        if (tam == temp.EndList){ // neu chay den cuoi danh sach ma khong co ten lop xuat hien thi thoat chuong trinh
            cout << "Khong ton tai lop nay trong nam hoc nay" << endl;
            return; 
        }
        tam = tam->pNext;
    }
    for (int i = 0; i < tam->data.NumberOfStudent_Current; i++){
        cout << setw(3)  << i + 1;
        cout << setw(20) << tam->data.student[i].FirstName;
        cout << setw(20) << tam->data.student[i].LastName;
        cout << setw(10) << tam->data.student[i].Gender;
        cout << setw(15) << tam->data.student[i].DateOfBirth;
        cout << setw(15) << tam->data.student[i].StudentID;
        cout << setw(20) << tam->data.student[i].SocialID <<endl;
    }
}

void DeleteOneStudent(ClassInfo& temp, int pos){ //Xoa sinh vien co vi tri pos trong lop temp
    extern hcmus NamHoc;
    for (int i = pos; i < temp.NumberOfStudent_Current; i++){
        temp.student[i] = temp.student[i + 1];
    }
    temp.NumberOfStudent_Current--;
    string path = "Data\\" + NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].SchoolYear + "\\Class\\" + temp.nameClass;
    WriteOnFile_Student(temp.student, temp.NumberOfStudent_Current, path);
}

void PrintListOfStudentInClass(ClassInfo& temp, int begin, bool isFirst /*1 la dau, 0 la cuoi*/){
    system("cls");
    if (temp.NumberOfStudent_Current == 0){
        SetColor(14, 4);
        GoTo(57,0);cout <<"Danh sach sinh vien lop "<< temp.nameClass <<" trong" << endl;
        TextColor(7);
        system("pause");
        return;
    }
    SetColor(14, 5);
    GoTo(60, 0); cout <<"DANH SACH SINH VIEN LOP " << temp.nameClass << endl;
    SetColor(14, 1);
    for (int i = 24; i <= 126; i++){
        GoTo(i, 2); cout <<' ';
    }
    GoTo(24, 2); cout << "STT";
    GoTo(29, 2); cout << "Ho va Ten Lot";
    GoTo(59, 2); cout << "Ten";
    GoTo(69, 2); cout << "Gioi tinh";
    GoTo(84, 2); cout << "Ngay sinh";
    GoTo(101, 2);cout << "MSSV";
    GoTo(118, 2);cout << "CCCD" <<endl;
    SetColor(7, 0);
    if (isFirst){
        for (int i = 24; i <= 126; i++){
            GoTo(i, 3); cout <<' ';
        }
    }
    else {
        for (int i = 24; i <= 126; i++){
            GoTo(i, 3 + min(26, temp.NumberOfStudent_Current - 1 - begin)); cout <<' ';
        }
    }
    TextColor(7);
    for (int i = begin; i < min(begin + 27, temp.NumberOfStudent_Current); i++){
        if ((isFirst == 1 && i == begin) || (isFirst == 0 && i == min(begin + 27, temp.NumberOfStudent_Current) -1)) SetColor(7, 0);
        GoTo(24, 3 + i - begin);cout << i + 1;
        GoTo(29, 3 + i - begin);cout << temp.student[i].FirstName;
        GoTo(59, 3 + i - begin);cout << temp.student[i].LastName;
        GoTo(71, 3 + i - begin);cout << temp.student[i].Gender;
        GoTo(84, 3 + i - begin);cout << temp.student[i].DateOfBirth;
        GoTo(99, 3 + i - begin);cout << temp.student[i].StudentID;
        GoTo(114,3 + i - begin);cout << temp.student[i].SocialID <<endl;
        if (i == begin) TextColor(7);
    }
    TextColor(7);
    int pos;//Biến chỉ vị trí đang chọn ở dòng nào
    if (isFirst) pos = 0;
    else pos = min(26, temp.NumberOfStudent_Current - 1 - begin);
    int NumberOfPages = temp.NumberOfStudent_Current / 27;
    GoTo(73, 31); cout << begin / 27 + 1 <<'/'<< NumberOfPages + (temp.NumberOfStudent_Current % 27 == 0?0:1);
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){// Đi lên
                    TextColor(7);
                    for (int i = 24; i <= 126; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(24, 3 + pos);cout << begin + pos + 1;
                    GoTo(29, 3 + pos);cout << temp.student[begin + pos].FirstName;
                    GoTo(59, 3 + pos);cout << temp.student[begin + pos].LastName;
                    GoTo(71, 3 + pos);cout << temp.student[begin + pos].Gender;
                    GoTo(84, 3 + pos);cout << temp.student[begin + pos].DateOfBirth;
                    GoTo(99, 3 + pos);cout << temp.student[begin + pos].StudentID;
                    GoTo(114,3 + pos);cout << temp.student[begin + pos].SocialID <<endl;
                    if (pos == 0) {
                        if (begin == 0){
                            if (temp.NumberOfStudent_Current % 27 != 0) PrintListOfStudentInClass(temp, 27 * NumberOfPages, 0);
                            else PrintListOfStudentInClass(temp, 27 * (NumberOfPages - 1), 0);
                        }
                        else PrintListOfStudentInClass(temp, begin - 27, 0);
                        return;
                    }
                    else pos--;
                    SetColor(7, 0);
                    for (int i = 24; i <= 126; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(24, 3 + pos);cout << begin + pos + 1;
                    GoTo(29, 3 + pos);cout << temp.student[begin + pos].FirstName;
                    GoTo(59, 3 + pos);cout << temp.student[begin + pos].LastName;
                    GoTo(71, 3 + pos);cout << temp.student[begin + pos].Gender;
                    GoTo(84, 3 + pos);cout << temp.student[begin + pos].DateOfBirth;
                    GoTo(99, 3 + pos);cout << temp.student[begin + pos].StudentID;
                    GoTo(114,3 + pos);cout << temp.student[begin + pos].SocialID <<endl;
                }
                if (c == 80){// Đi xuống
                    TextColor(7);
                    for (int i = 24; i <= 126; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(24, 3 + pos);cout << begin + pos + 1;
                    GoTo(29, 3 + pos);cout << temp.student[begin + pos].FirstName;
                    GoTo(59, 3 + pos);cout << temp.student[begin + pos].LastName;
                    GoTo(71, 3 + pos);cout << temp.student[begin + pos].Gender;
                    GoTo(84, 3 + pos);cout << temp.student[begin + pos].DateOfBirth;
                    GoTo(99, 3 + pos);cout << temp.student[begin + pos].StudentID;
                    GoTo(114,3 + pos);cout << temp.student[begin + pos].SocialID <<endl;
                    if (begin + pos == temp.NumberOfStudent_Current - 1){PrintListOfStudentInClass(temp, 0, 1);return;}
                        else if (pos == 26){PrintListOfStudentInClass(temp, begin + 27, 1);return;}
                            else pos++;
                    SetColor(7, 0);
                    for (int i = 24; i <= 126; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(24, 3 + pos);cout << begin + pos + 1;
                    GoTo(29, 3 + pos);cout << temp.student[begin + pos].FirstName;
                    GoTo(59, 3 + pos);cout << temp.student[begin + pos].LastName;
                    GoTo(71, 3 + pos);cout << temp.student[begin + pos].Gender;
                    GoTo(84, 3 + pos);cout << temp.student[begin + pos].DateOfBirth;
                    GoTo(99, 3 + pos);cout << temp.student[begin + pos].StudentID;
                    GoTo(114,3 + pos);cout << temp.student[begin + pos].SocialID <<endl;
                }
            }
            if (c == 27) {TextColor(7);return;}
            if (c == 8) { //backspace
                TextColor(7);
                system("cls");
                DeleteOneStudent(temp, begin + pos);
                PrintListOfStudentInClass(temp, begin, isFirst);
                return;
            }
        }
    }
}

void MenuListOfClass(SchoolTime NienKhoa){
    TextColor(7);
    system("cls");
    //extern hcmus NamHoc;
    GoTo(57,0); cout <<"DANH SACH CAC LOP NAM HOC " << NienKhoa.SchoolYear << endl;
    ListOfClasses* temp = NienKhoa.HeadList;
    int NumberOfClasses = 1;

    SetColor(14, 1);
    for (int i = 29; i <= 121; i++){
        GoTo(i, 2); cout <<' ';
    }
    GoTo(29, 2); cout << "STT";
    GoTo(39, 2); cout << "Ten Lop";
    GoTo(57, 2); cout << "Chuyen Nganh";
    GoTo(84, 2); cout << "So Luong SV";
    GoTo(99, 2); cout << "MAX_SV";
    GoTo(109, 2);cout << "Nam Nhap Hoc" << endl;

    SetColor(7, 0);
    for (int i = 29; i <= 121; i++){
        GoTo(i, 3); cout <<' ';
    }
  
    while (temp != nullptr){
        GoTo(29, 2 + NumberOfClasses); cout << NumberOfClasses;
        GoTo(39, 2 + NumberOfClasses); cout << temp->data.nameClass;
        GoTo(54, 2 + NumberOfClasses); cout << temp->data.major;
        GoTo(88, 2 + NumberOfClasses); cout << temp->data.NumberOfStudent_Current;
        GoTo(101,2 + NumberOfClasses); cout << temp->data.NumberOfStudent_max;
        GoTo(113, 2 + NumberOfClasses);cout << ConvertFirst(temp->data.TimeBegin) << endl;
        if (temp == NienKhoa.HeadList) TextColor(7);
        temp = temp->pNext;
        NumberOfClasses++;
    }
    NumberOfClasses--;
    int dem = 1;
    temp = NienKhoa.HeadList;
    while(true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ //Di len
                    TextColor(7);
                    for (int i = 29; i <= 121; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(29, 2 + dem);cout << dem;
                    GoTo(39, 2 + dem);cout << temp->data.nameClass;
                    GoTo(54, 2 + dem);cout << temp->data.major;
                    GoTo(88, 2 + dem);cout << temp->data.NumberOfStudent_Current;
                    GoTo(101,2 + dem);cout << temp->data.NumberOfStudent_max;
                    GoTo(113,2 + dem);cout << ConvertFirst(temp->data.TimeBegin) << endl;
                    dem--;
                    if (dem == 0){
                        dem = NumberOfClasses;
                        temp = NienKhoa.EndList;
                    }
                    else temp = temp->pPrev;
                    SetColor(7, 0);
                    for (int i = 29; i <= 121; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(29, 2 + dem);cout << dem;
                    GoTo(39, 2 + dem);cout << temp->data.nameClass;
                    GoTo(54, 2 + dem);cout << temp->data.major;
                    GoTo(88, 2 + dem);cout << temp->data.NumberOfStudent_Current;
                    GoTo(101,2 + dem);cout << temp->data.NumberOfStudent_max;
                    GoTo(113,2 + dem);cout << ConvertFirst(temp->data.TimeBegin) << endl;
                }
                if (c == 80){ // Di Xuong
                    TextColor(7);
                    for (int i = 29; i <= 121; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(29, 2 + dem);cout << dem;
                    GoTo(39, 2 + dem);cout << temp->data.nameClass;
                    GoTo(54, 2 + dem);cout << temp->data.major;
                    GoTo(88, 2 + dem);cout << temp->data.NumberOfStudent_Current;
                    GoTo(101,2 + dem);cout << temp->data.NumberOfStudent_max;
                    GoTo(113,2 + dem);cout << ConvertFirst(temp->data.TimeBegin) << endl;
                    dem++;
                    if (dem > NumberOfClasses){
                        dem = 1;
                        temp = NienKhoa.HeadList;
                    }
                    else temp = temp->pNext;
                    SetColor(7, 0);
                    for (int i = 29; i <= 121; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(29, 2 + dem);cout << dem;
                    GoTo(39, 2 + dem);cout << temp->data.nameClass;
                    GoTo(54, 2 + dem);cout << temp->data.major;
                    GoTo(88, 2 + dem);cout << temp->data.NumberOfStudent_Current;
                    GoTo(101,2 + dem);cout << temp->data.NumberOfStudent_max;
                    GoTo(113,2 + dem);cout << ConvertFirst(temp->data.TimeBegin) << endl;
                }
            }
            if (c == 13){ //Enter
                TextColor(7);
                system("cls");
                PrintListOfStudentInClass(temp->data, 0, 1);
                system("cls");
                ListOfClasses* tam = temp;
                int pos = dem;
                /*----------------------------------*/
                /*In lai danh sach lop*/
                NumberOfClasses = 1;
                temp = NienKhoa.HeadList;
                SetColor(14, 1);
                for (int i = 29; i <= 121; i++){
                    GoTo(i, 2); cout <<' ';
                }
               GoTo(29, 2); cout << "STT";
                GoTo(39, 2); cout << "Ten Lop";
                GoTo(57, 2); cout << "Chuyen Nganh";
                GoTo(84, 2); cout << "So Luong SV";
                GoTo(99, 2); cout << "MAX_SV";
                GoTo(109, 2);cout << "Nam Nhap Hoc" << endl;
                
                TextColor(7);
                
                while (temp != nullptr){
                    if (temp == tam){ //quay trở lại danh sách thì dừng tại vị trí bấm vào trước đó
                        SetColor(7, 0);
                        for (int i = 29; i <= 121; i++){
                        GoTo(i, 2 + pos); cout <<' ';
                        }
                    }
                    GoTo(29, 2 + NumberOfClasses); cout << NumberOfClasses;
                    GoTo(39, 2 + NumberOfClasses); cout << temp->data.nameClass;
                    GoTo(54, 2 + NumberOfClasses); cout << temp->data.major;
                    GoTo(88, 2 + NumberOfClasses); cout << temp->data.NumberOfStudent_Current;
                    GoTo(101,2 + NumberOfClasses); cout << temp->data.NumberOfStudent_max;
                    GoTo(113, 2 + NumberOfClasses);cout << ConvertFirst(temp->data.TimeBegin) << endl;
                    if (temp == tam) TextColor(7);
                    temp = temp->pNext;
                    NumberOfClasses++;
                }
                NumberOfClasses--;
                dem = pos;
                temp = tam;
                /*----------------------------------*/
            } 
            if (c == 27){ //Esc
                GoTo(0, NumberOfClasses + 5);
                return;
            }
        }
    }
}

void InputCourseInfo(Course& temp){
    GoTo(61, 8); cout <<"Enter course ID: ";
    getline(cin, temp.CourseID);
    GoTo(61, 9); cout <<"Enter course name: ";
    getline(cin, temp.CourseName);
    GoTo(61, 10);cout <<"Enter class name: ";
    getline(cin, temp.ClassName);
    GoTo(61, 11);cout <<"Enter teacher name: ";
    getline(cin, temp.TeacherName);
    GoTo(61, 12);cout <<"Enter number of credits: ";
    cin >> temp.NumberOfCredit;
    cin.ignore();
    GoTo(61, 13);cout <<"Enter the maximum number of student: ";
    cin >> temp.NumberOfStudent_Max;
    cin.ignore();
    GoTo(61, 14);cout <<"Enter day of week (MON / TUE / WED / THU / FRI / SAT): ";
    getline(cin, temp.DayOfWeek);
    GoTo(61, 15);cout <<"Enter session: S1(07:30); S2(09:30); S3(13:30); S4(15:30): ";
    getline(cin, temp.session); 
    temp.student = new StudentInfo[temp.NumberOfStudent_Max + 1];
    temp.NumberOfStudent_Current = 0;
}

// AddCourseToSemester(KHTN.ptr[0].semester[1])
void AddCourseToSemester(HocKy& temp){
    TextColor(7);
    system("cls");
    extern hcmus NamHoc;
    ListOfCourse* node = new ListOfCourse;
    InputCourseInfo(node->data);
    
    //Viet thong tin khoa hoc vao file Course.csv
    string path = "Data\\" + NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].SchoolYear + "\\Semester" + to_string(temp.STT) + "\\Course";
    WriteOnFile_One_Course(node->data, path);
    //Tao file .csv chua thong tin SV dky khoa hoc
    // path = "Data\\" + NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].SchoolYear + "\\Semester" + to_string(temp.STT) + '\\' + node->data.CourseID + ".csv";
    // ofstream ofs(path);
    // if (!ofs){
    //     cout <<"Co loi khi tao file chua thong tin SV dky khoa hoc" << endl;
    // }
    // else{
    //     ofs << "First Name,";
    //     ofs << "Last Name,";
    //     ofs << "Gender,";
    //     ofs << "Birthday,";
    //     ofs << "Student ID,";
    //     ofs << "Social ID,";
    //     ofs << "Midterm Mark,";
    //     ofs << "Final Mark,";
    //     ofs << "Other Mark,";
    //     ofs << "Total Mark" << endl;
    // }
    // ofs.close();

    node->pNext = nullptr;
    node->pPrev = nullptr;
    if (temp.HeadList == nullptr) temp.HeadList = node;
    else if (temp.EndList == nullptr){
            temp.HeadList->pNext = node;
            node->pPrev = temp.HeadList;
            temp.EndList = node;
        }
        else {
            temp.EndList->pNext = node;
            node->pPrev = temp.EndList;
            temp.EndList = node;
        }
    TextColor(2);
    GoTo(61, 16); cout << "Successfully" << endl;
    TextColor(7);
    system("pause");
}

void PrintListOfCourseInSemester(HocKy& temp){
    TextColor(7);
    system("cls");
    ListOfCourse* node = temp.HeadList;
    if (node == nullptr){
        SetColor(14, 4);
        cout <<"Chua co mon hoc nao duoc tao trong hoc ky nay" << endl;
        TextColor(7);
        system("pause");
        return;
    }
    SetColor(14, 1);
    for (int i = 0; i <= 147; i++){
        GoTo(i, 2); cout <<' ';
    }
    GoTo(0, 2); cout << "STT";
    GoTo(5, 2); cout << "COURSE ID";
    GoTo(22, 2);cout << "COURSE NAME";
    GoTo(47, 2);cout << "CLASS NAME";
    GoTo(61, 2);cout << "TEACHER NAME";
    GoTo(83, 2);cout << "CREDITs";
    GoTo(93, 2);cout << "STUDENT_Current";
    GoTo(112, 2);cout << "STUDENT_Max";
    GoTo(126, 2);cout << "DAY OF WEEK";
    GoTo(140, 2);cout << "SESSION";
    int dem = 1;
    SetColor(7, 0);
    for (int i = 0; i <= 147; i++){
        GoTo(i, 3); cout <<' ';
    }
    while (node != nullptr){
        GoTo(0, 2 + dem); cout << dem;
        GoTo(5, 2 + dem); cout << node->data.CourseID;
        GoTo(19, 2 + dem);cout << node->data.CourseName;
        GoTo(49, 2 + dem);cout << node->data.ClassName;
        GoTo(61, 2 + dem);cout << node->data.TeacherName;
        GoTo(86, 2 + dem);cout << node->data.NumberOfCredit;
        GoTo(99, 2 + dem);cout << node->data.NumberOfStudent_Current;
        GoTo(116, 2 + dem);cout << node->data.NumberOfStudent_Max;
        GoTo(129, 2 + dem);cout << node->data.DayOfWeek;
        GoTo(142, 2 + dem);cout << node->data.session;
        node = node->pNext;
        if (dem == 1) TextColor(7);
        dem++;
    }
    int NumberOfCourse = dem - 1;
    dem = 1;
    node = temp.HeadList;
    while(true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72) { //Di len
                    TextColor(7);
                    for (int i = 0; i <= 147; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0, 2 + dem); cout << dem;
                    GoTo(5, 2 + dem); cout << node->data.CourseID;
                    GoTo(19, 2 + dem);cout << node->data.CourseName;
                    GoTo(49, 2 + dem);cout << node->data.ClassName;
                    GoTo(61, 2 + dem);cout << node->data.TeacherName;
                    GoTo(86, 2 + dem);cout << node->data.NumberOfCredit;
                    GoTo(99, 2 + dem);cout << node->data.NumberOfStudent_Current;
                    GoTo(116, 2 + dem);cout << node->data.NumberOfStudent_Max;
                    GoTo(129, 2 + dem);cout << node->data.DayOfWeek;
                    GoTo(142, 2 + dem);cout << node->data.session;
                    dem--;
                    if (dem == 0){ 
                        dem = NumberOfCourse; 
                        node = temp.EndList; 
                    }
                    else node = node->pPrev;
                    SetColor(7, 0);
                    for (int i = 0; i <= 147; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0, 2 + dem); cout << dem;
                    GoTo(5, 2 + dem); cout << node->data.CourseID;
                    GoTo(19, 2 + dem);cout << node->data.CourseName;
                    GoTo(49, 2 + dem);cout << node->data.ClassName;
                    GoTo(61, 2 + dem);cout << node->data.TeacherName;
                    GoTo(86, 2 + dem);cout << node->data.NumberOfCredit;
                    GoTo(99, 2 + dem);cout << node->data.NumberOfStudent_Current;
                    GoTo(116, 2 + dem);cout << node->data.NumberOfStudent_Max;
                    GoTo(129, 2 + dem);cout << node->data.DayOfWeek;
                    GoTo(142, 2 + dem);cout << node->data.session;
                }
                if (c == 80){ //Di xuong
                    TextColor(7);
                    for (int i = 0; i <= 147; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0, 2 + dem); cout << dem;
                    GoTo(5, 2 + dem); cout << node->data.CourseID;
                    GoTo(19, 2 + dem);cout << node->data.CourseName;
                    GoTo(49, 2 + dem);cout << node->data.ClassName;
                    GoTo(61, 2 + dem);cout << node->data.TeacherName;
                    GoTo(86, 2 + dem);cout << node->data.NumberOfCredit;
                    GoTo(99, 2 + dem);cout << node->data.NumberOfStudent_Current;
                    GoTo(116, 2 + dem);cout << node->data.NumberOfStudent_Max;
                    GoTo(129, 2 + dem);cout << node->data.DayOfWeek;
                    GoTo(142, 2 + dem);cout << node->data.session;
                    dem++;
                    if (dem == NumberOfCourse + 1){ 
                        dem = 1; 
                        node = temp.HeadList; 
                    }
                    else node = node->pNext;
                    SetColor(7, 0);
                    for (int i = 0; i <= 147; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0, 2 + dem); cout << dem;
                    GoTo(5, 2 + dem); cout << node->data.CourseID;
                    GoTo(19, 2 + dem);cout << node->data.CourseName;
                    GoTo(49, 2 + dem);cout << node->data.ClassName;
                    GoTo(61, 2 + dem);cout << node->data.TeacherName;
                    GoTo(86, 2 + dem);cout << node->data.NumberOfCredit;
                    GoTo(99, 2 + dem);cout << node->data.NumberOfStudent_Current;
                    GoTo(116, 2 + dem);cout << node->data.NumberOfStudent_Max;
                    GoTo(129, 2 + dem);cout << node->data.DayOfWeek;
                    GoTo(142, 2 + dem);cout << node->data.session;
                }
            }
            if (c == 13){ //Enter
                TextColor(7);
                EditCourse(node->data); //Edit Course
                system("cls");
                ListOfCourse* tam = temp.HeadList;
                SetColor(14, 1);
                for (int i = 0; i <= 147; i++){
                    GoTo(i, 2); cout <<' ';
                }
                GoTo(0, 2); cout << "STT";
                GoTo(5, 2); cout << "COURSE ID";
                GoTo(22, 2);cout << "COURSE NAME";
                GoTo(47, 2);cout << "CLASS NAME";
                GoTo(61, 2);cout << "TEACHER NAME";
                GoTo(83, 2);cout << "CREDITs";
                GoTo(93, 2);cout << "STUDENT_Current";
                GoTo(112, 2);cout << "STUDENT_Max";
                GoTo(126, 2);cout << "DAY OF WEEK";
                GoTo(140, 2);cout << "SESSION";
                int dem_sub = 1;
                TextColor(7);
                while (tam != nullptr){
                    if (dem_sub == dem) {
                        SetColor(7, 0);
                        for (int i = 0; i <= 147; i++){
                            GoTo(i, 2 + dem); cout <<' ';
                        }
                    }
                    GoTo(0, 2 + dem_sub);  cout << dem_sub;
                    GoTo(5, 2 + dem_sub);  cout << tam->data.CourseID;
                    GoTo(19, 2 + dem_sub); cout << tam->data.CourseName;
                    GoTo(49, 2 + dem_sub); cout << tam->data.ClassName;
                    GoTo(61, 2 + dem_sub); cout << tam->data.TeacherName;
                    GoTo(86, 2 + dem_sub); cout << tam->data.NumberOfCredit;
                    GoTo(99, 2 + dem_sub); cout << tam->data.NumberOfStudent_Current;
                    GoTo(116, 2 + dem_sub);cout << tam->data.NumberOfStudent_Max;
                    GoTo(129, 2 + dem_sub);cout << tam->data.DayOfWeek;
                    GoTo(142, 2 + dem_sub);cout << tam->data.session;
                    tam = tam->pNext;
                    if (dem_sub == dem) TextColor(7);
                    dem_sub++;
                }
            }
            if (c == 8){ //Backspace
                DeleteCourse(temp, node);
                TextColor(7);
                PrintListOfCourseInSemester(temp);
            }
            if (c == 27) {GoTo(0, 0);return;} //ESC
        }
    }
}
void EditCourse(Course& temp){
    extern hcmus NamHoc;
    system("cls");
    SetColor(15, 0);
    GoTo(49, 1); cout << "|A|D|J|U|S|T| |C|O|U|R|S|E| |I|N|F|O|R|M|A|T|I|O|N|" << endl;
    // TextColor(7);
    string str[10];
    str[0] = "COURSE ID         :";
    str[1] = "COURSE NAME       :"; 
    str[2] = "CLASS NAME        :"; 
    str[3] = "TEACHER NAME      :";  
    str[4] = "NUMBER OF CREDIT  :"; 
    str[5] = "CURRENT STUDENTs  :";
    str[6] = "MAXIMUM STUDENTs  :"; 
    str[7] = "DAY OF WEEK       :";
    str[8] = "SESSION           :";
    str[9] = "View List Of Student";
    //str[10]= "Export to CSV file  ";

    string res[11];
    res[0] = ' '+ temp.CourseID;
    res[1] = ' '+ temp.CourseName;
    res[2] = ' '+ temp.ClassName;
    res[3] = ' '+ temp.TeacherName;
    res[4] = ' '+ to_string(temp.NumberOfCredit);
    res[5] = ' '+ to_string(temp.NumberOfStudent_Current);
    res[6] = ' '+ to_string(temp.NumberOfStudent_Max);
    res[7] = ' '+ temp.DayOfWeek;
    res[8] = ' '+ temp.session;
    res[9] = "";
    //res[10] = "";
    
    int lens = 50; 
    //lens la bien luu do dai cua o chu

    SetColor(1, 14);
    for (int i = 0; i <= lens; i++){
        GoTo(i + 50, 3);
        cout <<' ';
    }
    GoTo(50, 3); cout << str[0] << res[0] << endl;
    for (int i = 1; i <= 8; i++){
        GoTo(50, 3 + i);
        SetColor(14, 1);
        cout << str[i];
        TextColor(7);
        cout << res[i];
    }  
    GoTo(50, 12);
    cout << str[9] << res[9];
    
    int i = 0;
    while (true) {
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ // Di len
                    GoTo(50, 3 + i); 
                    if (i != 9) SetColor(14, 1); 
                    else TextColor(7);
                    cout << str[i];
                    TextColor(7);
                    for (int j = 20; j <= lens; j++){
                        GoTo(j + 50, 3 + i);
                        cout <<' ';
                    }
                    GoTo(69, 3 + i);
                    cout << res[i];
                    if (i == 0) i = 9;
                    else i--;
                    
                    if (i == 5) i--; //Bỏ qua i = 5 vì current student sẽ tự thay đổi khi thêm hoặc xóa sv
                    SetColor(1, 14);
                    for (int j = 0; j <= lens; j++){
                        GoTo(j + 50, 3 + i);
                        cout <<' ';
                    }
                    GoTo(50, 3 + i); cout << str[i] << res[i] << endl;
                }
                if (c == 80){ //Di Xuong
                    GoTo(50, 3 + i); 
                    if (i != 9) SetColor(14, 1); 
                    else TextColor(7);
                    cout << str[i];
                    TextColor(7);
                    for (int j = 20; j <= lens; j++){
                        GoTo(j + 50, 3 + i);
                        cout <<' ';
                    }
                    GoTo(69, 3 + i);
                    cout << res[i];
                    if (i == 9) i = 0;
                    else i++;
                    
                    if (i == 5) i++; //Bỏ qua i = 5 vì current student sẽ tự thay đổi khi thêm hoặc xóa sv
                    
                    SetColor(1, 14);
                    for (int j = 0; j <= lens; j++){
                        GoTo(j + 50, 3 + i);
                        cout <<' ';
                    }
                    GoTo(50, 3 + i); cout << str[i] << res[i] << endl;
                }
            }
            if (c == 13){  //ENTER
                if (i == 9){
                    SetColor(0, 7);
                    system("cls");
                    PrintListOfStudentInCourse(temp);
                    res[5] = ' '+ to_string(temp.NumberOfStudent_Current);
                    system("cls");
                    SetColor(15, 0);
                    GoTo(49, 1); cout << "|A|D|J|U|S|T| |C|O|U|R|S|E| |I|N|F|O|R|M|A|T|I|O|N|" << endl;
                    SetColor(1, 14);
                    for (int j = 0; j <= lens; j++){
                        GoTo(j + 50, 3);
                        cout <<' ';
                    }
                    GoTo(50, 3); cout << str[0] << res[0] << endl;
                    for (int i = 1; i <= 8; i++){
                        GoTo(50, 3 + i);
                        SetColor(14, 1);
                        cout << str[i];
                        TextColor(7);
                        cout << res[i];
                    }  
                    for (int i = 9; i <= 10; i++){
                        GoTo(50, 3 + i);
                        cout << str[i] << res[i];
                    }
                    i = 0;
                }
            }
            if (c == 8){ //BackSpace
                SetColor(1, 14);
                for (int j = 19; j <= lens; j++){
                    GoTo(j + 50, 3 + i);
                    cout <<' ';
                }
                GoTo(70, 3 + i);
                switch (i){
                    case 0:{
                        getline(cin, temp.CourseID);
                        res[i] = ' ' + temp.CourseID;
                        break;
                    }
                    case 1:{
                        getline(cin, temp.CourseName);
                        res[i] = ' ' + temp.CourseName;
                        break;
                    }
                    case 2:{
                        getline(cin, temp.ClassName);
                        res[i] = ' ' + temp.ClassName;
                        break;
                    }
                    case 3:{
                        getline(cin, temp.TeacherName);
                        res[i] = ' ' + temp.TeacherName;
                        break;
                    }
                    case 4:{
                        cin >> temp.NumberOfCredit;
                        cin.ignore();
                        res[i] = ' ' + to_string(temp.NumberOfCredit);
                        break;
                    }
                    case 6:{
                        cin >> temp.NumberOfStudent_Max;
                        res[i] = ' ' + to_string(temp.NumberOfStudent_Max);
                        cin.ignore();
                        break;
                    }
                    case 7:{
                        getline(cin, temp.DayOfWeek);
                        res[i] = ' ' + temp.DayOfWeek;
                        break;
                    }
                    case 8:{
                        getline(cin, temp.session);
                        res[i] = ' ' + temp.session;
                        break;
                    }
                }
                int n = NamHoc.NumberOfSchoolYear - 1;
                int stt_hocky = NamHoc.ptr[n].NumberOfSemester;
                string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(NamHoc.ptr[n].semester[stt_hocky].STT) + "\\Course";
                WriteOnFile_Course(NamHoc.ptr[n].semester[stt_hocky].HeadList,path);
            }
            if (c == 27) {GoTo(50, 15);TextColor(7);return;} //ESC
        }
    }
    TextColor(7);
}

void DeleteCourse(HocKy& temp, ListOfCourse* node){
    extern hcmus NamHoc;
    if (node == temp.HeadList){
        temp.HeadList = node->pNext;
        if (temp.HeadList != nullptr) temp.HeadList->pPrev = nullptr;
    }
    else if (node == temp.EndList){
            temp.EndList = node->pPrev;
            if (temp.EndList != nullptr) temp.EndList->pNext = nullptr;
        }
        else {
            ListOfCourse* node_pre = node->pPrev;
            ListOfCourse* node_next = node->pNext;
            node_pre->pNext = node_next;
            node_next->pPrev = node_pre;
        }
    int n = NamHoc.NumberOfSchoolYear - 1;
    string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(temp.STT) + "\\Course";
    WriteOnFile_Course(temp.HeadList, path);
}

void AddStudentIntoCourse(Course& temp){
    TextColor(7);
    system("cls");
    extern hcmus NamHoc;
    ListOfClasses* DS_Lop_Head;
    ListOfClasses* DS_Lop_End = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].EndList;
    string CMPnameClass = "";
    if (temp.NumberOfStudent_Current >= temp.NumberOfStudent_Max) return;

    bool kt = 1;
    while (kt){
        //kt = 1;
        DS_Lop_Head = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].HeadList;
        GoTo(54, 5); cout <<"Enter student's class: ";
        getline(cin, CMPnameClass);
        while (DS_Lop_Head != nullptr){
            if (DS_Lop_Head->data.nameClass == CMPnameClass){kt = 0; break;}
            if (DS_Lop_Head == DS_Lop_End) break;
            DS_Lop_Head = DS_Lop_Head->pNext;
        }
        if (kt){
            TextColor(4);
            GoTo(54, 6); cout <<"This class doesn't exist" << endl;
            sleep(1);
            system("cls");
            TextColor(7);
        }
    }
    string ID = "";
    kt = 1;
    StudentInfo res;
    while (kt){
        GoTo(54, 5); cout << "Enter student's class: " << CMPnameClass;
        GoTo(54, 6); cout <<"Enter studen ID: ";
        getline(cin, ID);
        for (int i = 0; i < DS_Lop_Head->data.NumberOfStudent_Current; i++){
            if (ID == DS_Lop_Head->data.student[i].StudentID) { 
                kt = 0; 
                res = DS_Lop_Head->data.student[i];
                break;
            }
        }
        if (kt){
            TextColor(4);
            GoTo(54, 7); cout << "Student ID doesn't exist" << endl;
            sleep(1);
            system("cls");
            TextColor(7);
        }
        else{
            for (int i = 0; i < temp.NumberOfStudent_Current; i++){ //Kiem tra xem sinh vien nay da co trong khoa hoc chua
                if (ID == temp.student[i].StudentID){
                    kt = 1;
                    break;
                }
            }
            if (kt){
                TextColor(4);
                GoTo(54, 7); cout << "This student ID has already existed in course" << endl;
                sleep(1);
                system("cls");
                TextColor(7);
            }
        }
    }
    GoTo(54, 7); cout << res.FirstName << endl;
    GoTo(54, 8); cout << res.LastName << endl;
    GoTo(54, 9); cout << res.Gender << endl;
    GoTo(54, 10);cout << res.DateOfBirth << endl;
    GoTo(54, 11);cout << res.StudentID << endl;
    GoTo(54, 12);cout << res.SocialID << endl;
    temp.student[temp.NumberOfStudent_Current] = res;
    TextColor(2);
    GoTo(54, 13); cout <<"Successfully" << endl;
    TextColor(7);
    system("pause");
    temp.NumberOfStudent_Current++;

    extern hcmus NamHoc;
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky = NamHoc.ptr[n].NumberOfSemester;
    string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(NamHoc.ptr[n].semester[hocky].STT) + '\\' + temp.CourseID;
    WriteOnFile_One_Student(res, temp.NumberOfStudent_Current - 1, path);
}

void AddStudentIntoCourse(){
    TextColor(7);
    system("cls");
    extern hcmus NamHoc;
    string courseName, className;
    GoTo(54, 5); cout <<"Enter name of course: ";
    getline(cin, courseName);
    GoTo(54, 6); cout <<"Enter class name of the course: ";
    getline(cin, className);
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
    ListOfCourse* tam = NamHoc.ptr[n].semester[hocky_stt].HeadList;
    bool kt = 0;
    while (tam != nullptr){
        if (tam->data.ClassName == className && tam->data.CourseName == courseName){kt = 1; break;}
        tam = tam->pNext;
    }
    if (!kt){
        TextColor(4);
        GoTo(54, 7); cout << "This course does not exist" << endl;
        TextColor(7);
        system("pause");
        return;
    }
    Course temp = tam->data;
    ListOfClasses* DS_Lop_Head;
    ListOfClasses* DS_Lop_End = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].EndList;
    string CMPnameClass = "";
    if (temp.NumberOfStudent_Current >= temp.NumberOfStudent_Max) return;

    kt = 1;
    while (kt){
        //kt = 1;
        DS_Lop_Head = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1].HeadList;
        GoTo(54, 7); cout <<"Enter student's class: ";
        getline(cin, CMPnameClass);
        while (DS_Lop_Head != nullptr){
            if (DS_Lop_Head->data.nameClass == CMPnameClass){kt = 0; break;}
            if (DS_Lop_Head == DS_Lop_End) break;
            DS_Lop_Head = DS_Lop_Head->pNext;
        }
        if (kt){
            TextColor(4);
            GoTo(54,8); cout <<"This class doesn't exist" << endl;
            TextColor(7);
        }
    }
    string ID = "";
    kt = 1;
    StudentInfo res;
    while (kt){
        GoTo(54, 8); cout <<"Enter student ID: ";
        getline(cin, ID);
        for (int i = 0; i < DS_Lop_Head->data.NumberOfStudent_Current; i++){
            if (ID == DS_Lop_Head->data.student[i].StudentID) { 
                kt = 0; 
                res = DS_Lop_Head->data.student[i];
                break;
            }
        }
        if (kt){
            TextColor(4);
            GoTo(54, 9); cout << "Student ID doesn't exist" << endl;
            TextColor(7);
        }
        else{
            for (int i = 0; i < temp.NumberOfStudent_Current; i++){ //Kiem tra xem sinh vien nay da co trong khoa hoc chua
                if (ID == temp.student[i].StudentID){
                    kt = 1;
                    break;
                }
            }
            if (kt){
                TextColor(4);
                GoTo(54, 9); cout << "This student ID has already existed in course" << endl;
                TextColor(7);
            }
        }
    }
    GoTo(54, 9);  cout << res.FirstName << endl;
    GoTo(54, 10); cout << res.LastName << endl;
    GoTo(54, 11); cout << res.Gender << endl;
    GoTo(54, 12); cout << res.DateOfBirth << endl;
    GoTo(54, 13); cout << res.StudentID << endl;
    GoTo(54, 14); cout << res.SocialID << endl;
    temp.student[temp.NumberOfStudent_Current] = res;
    TextColor(2);
    GoTo(54, 15); cout <<"Successfully" << endl;
    TextColor(7);
    system("pause");
    temp.NumberOfStudent_Current++;
    tam->data = temp;

    n = NamHoc.NumberOfSchoolYear - 1;
    int hocky = NamHoc.ptr[n].NumberOfSemester;
    string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(NamHoc.ptr[n].semester[hocky].STT) + '\\' + temp.CourseID;
    WriteOnFile_One_Student(res, temp.NumberOfStudent_Current - 1, path);
}

void DeleteOneStudent(Course& temp, int pos){ //Xoa sinh vien co vi tri pos trong lop temp
    for (int i = pos; i < temp.NumberOfStudent_Current; i++){
        temp.student[i] = temp.student[i + 1];
    }
    temp.NumberOfStudent_Current--;
    extern hcmus NamHoc;
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky = NamHoc.ptr[n].NumberOfSemester;
    string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(NamHoc.ptr[n].semester[hocky].STT) + '\\' + temp.CourseID;
    WriteOnFile_Student(temp.student, temp.NumberOfStudent_Current, path);
}

//chieu ngang khung hinh la 149 => o giua la o thu 75
void PrintListOfStudentInCourse(Course& temp){
    GoTo(120, 1); 
    TextColor(2);
    cout <<"Press f8 to add student";
    GoTo(120, 2);
    cout <<"Press f9 to export file csv";
    GoTo(120, 3);
    cout <<"Press f10 to import file csv";
    TextColor(7);
    if (temp.NumberOfStudent_Current == 0){
        GoTo(75 - (43 + temp.CourseName.length() + temp.ClassName.length() )/ 2, 0);
        SetColor(7, 3);
        cout <<"Danh sach sinh vien hoc mon "<< temp.CourseName <<" cua lop "<< temp.ClassName <<" trong" << endl;
        TextColor(7);
    }
    else {
        SetColor(14, 7);
        GoTo(75 - (37 + temp.CourseName.length() + temp.ClassName.length() )/ 2, 0); cout <<"Danh sach sinh vien hoc mon "<< temp.CourseName <<" cua lop "<< temp.ClassName << endl;
        SetColor(14, 1);
        for (int i = 0; i <= 107; i++){
            GoTo(i, 2); cout <<' ';
        }
        GoTo(0, 2);  cout << "STT";
        GoTo(7, 2);  cout << "Ho va Ten";
        GoTo(25, 2); cout << "Gioi tinh";
        GoTo(38, 2); cout << "Ngay sinh";
        GoTo(55, 2); cout << "MSSV";
        GoTo(65, 2); cout << "Diem GK";
        GoTo(75, 2); cout << "Diem CK";
        GoTo(85, 2); cout << "Diem cong";
        GoTo(97, 2); cout << "Tong Phay" << endl;

        SetColor(7, 0);
        for (int i = 0; i <= 107; i++){
            GoTo(i, 3); cout <<' ';
        }
        for (int i = 0; i < temp.NumberOfStudent_Current; i++){
            GoTo(0, 3 + i);cout << i + 1;
            GoTo(5, 3 + i);cout << temp.student[i].FirstName + ' ' + temp.student[i].LastName;
            GoTo(28,3 + i);cout << temp.student[i].Gender;
            GoTo(38,3 + i);cout << temp.student[i].DateOfBirth;
            GoTo(53,3 + i);cout << temp.student[i].StudentID;
            if (temp.student[i].Midterm_mark != -1){
                GoTo(67,3 + i);cout << temp.student[i].Midterm_mark;
            }
            if (temp.student[i].Final_mark != -1){
                GoTo(77,3 + i);cout << temp.student[i].Final_mark;
            }
            if (temp.student[i].Other_mark != -1){
                GoTo(88,3 + i);cout << temp.student[i].Other_mark;
            }
            if (temp.student[i].Total_mark != -1){
                GoTo(100,3 + i);cout << temp.student[i].Total_mark << endl;
            }
            if (i == 0) TextColor(7);
        }
    }
    int pos = 0;
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == 0){
                c = getch();
                if (c == 66){
                    if (temp.NumberOfStudent_Current == temp.NumberOfStudent_Max){
                        GoTo(58, 1);
                        SetColor(11, 4);
                        cout <<"DA QUA SO LUONG SINH VIEN DANG KY";
                        sleep(1);
                        TextColor(7);
                        for (int i = 58; i <= 91; i++){
                            GoTo(i, 1);
                            cout <<' ';
                        }
                    }
                    else {
                        AddStudentIntoCourse(temp);
                        TextColor(7);
                        system("cls");
                        GoTo(120, 1); 
                        TextColor(2);
                        cout <<"Press f8 to add student";
                        GoTo(120, 2);
                        cout <<"Press f9 to export file csv";
                        GoTo(120, 3);
                        cout <<"Press f10 to import file csv";
                        TextColor(7);
                        SetColor(14, 7);
                        GoTo(75 - (37 + temp.CourseName.length() + temp.ClassName.length() )/ 2, 0); 
                        cout <<"Danh sach sinh vien hoc mon "<< temp.CourseName <<" cua lop "<< temp.ClassName << endl;
                        SetColor(14, 1);
                        for (int i = 0; i <= 107; i++){
                            GoTo(i, 2); cout <<' ';
                        }
                        GoTo(0, 2);  cout << "STT";
                        GoTo(7, 2);  cout << "Ho va Ten";
                        GoTo(25, 2); cout << "Gioi tinh";
                        GoTo(38, 2); cout << "Ngay sinh";
                        GoTo(55, 2); cout << "MSSV";
                        GoTo(65, 2); cout << "Diem GK";
                        GoTo(75, 2); cout << "Diem CK";
                        GoTo(85, 2); cout << "Diem cong";
                        GoTo(97, 2); cout << "Tong Phay" << endl;
                        SetColor(7, 0);
                        for (int i = 0; i <= 107; i++){
                            GoTo(i, 3); cout <<' ';
                        }
                        for (int i = 0; i < temp.NumberOfStudent_Current; i++){
                            GoTo(0, 3 + i);cout << i + 1;
                            GoTo(5, 3 + i);cout << temp.student[i].FirstName + ' ' + temp.student[i].LastName;
                            GoTo(28,3 + i);cout << temp.student[i].Gender;
                            GoTo(38,3 + i);cout << temp.student[i].DateOfBirth;
                            GoTo(53,3 + i);cout << temp.student[i].StudentID;
                            if (temp.student[i].Midterm_mark != -1){
                                GoTo(67,3 + i);cout << temp.student[i].Midterm_mark;
                            }
                            if (temp.student[i].Final_mark != -1){
                                GoTo(77,3 + i);cout << temp.student[i].Final_mark;
                            }
                            if (temp.student[i].Other_mark != -1){
                                GoTo(88,3 + i);cout << temp.student[i].Other_mark;
                            }
                            if (temp.student[i].Total_mark != -1){
                                GoTo(100,3 + i);cout << temp.student[i].Total_mark << endl;
                            }
                            if (i == 0) TextColor(7);
                        }
                        pos = 0;
                    }
                }
                if (c == 67){
                    if (temp.NumberOfStudent_Current != 0) ExportFileCSV(temp);
                    else {
                        GoTo(54, 7);
                        SetColor(14, 4);
                        cout <<"Danh sach dang trong, khong the xuat file";
                        TextColor(7);
                        sleep(1);
                        for (int i = 54; i <= 95; i++){
                            GoTo(i, 7); cout <<' ';
                        }
                    }
                }
                if (c == 68){
                    if (ImportFileCSV(temp)){
                        extern hcmus NamHoc;
                        int n = NamHoc.NumberOfSchoolYear - 1;
                        int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
                        string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(NamHoc.ptr[n].semester[hocky_stt].STT) + '\\' + temp.CourseID;
                        //cout << path  << endl;
                        //system("pause");
                        WriteOnFile_Student(temp.student, temp.NumberOfStudent_Current, path);
                        TextColor(7);
                        system("cls");
                        GoTo(120, 1); 
                        TextColor(2);
                        cout <<"Press f8 to add student";
                        GoTo(120, 2);
                        cout <<"Press f9 to export file csv";
                        GoTo(120, 3);
                        cout <<"Press f10 to import file csv";
                        TextColor(7);
                        SetColor(14, 7);
                        GoTo(75 - (37 + temp.CourseName.length() + temp.ClassName.length() )/ 2, 0); 
                        cout <<"Danh sach sinh vien hoc mon "<< temp.CourseName <<" cua lop "<< temp.ClassName << endl;
                        SetColor(14, 1);
                        for (int i = 0; i <= 107; i++){
                            GoTo(i, 2); cout <<' ';
                        }
                        GoTo(0, 2);  cout << "STT";
                        GoTo(7, 2);  cout << "Ho va Ten";
                        GoTo(25, 2); cout << "Gioi tinh";
                        GoTo(38, 2); cout << "Ngay sinh";
                        GoTo(55, 2); cout << "MSSV";
                        GoTo(65, 2); cout << "Diem GK";
                        GoTo(75, 2); cout << "Diem CK";
                        GoTo(85, 2); cout << "Diem cong";
                        GoTo(97, 2); cout << "Tong Phay" << endl;
                        SetColor(7, 0);
                        for (int i = 0; i <= 107; i++){
                            GoTo(i, 3); cout <<' ';
                        }
                        for (int i = 0; i < temp.NumberOfStudent_Current; i++){
                            GoTo(0, 3 + i);cout << i + 1;
                            GoTo(5, 3 + i);cout << temp.student[i].FirstName + ' ' + temp.student[i].LastName;
                            GoTo(28,3 + i);cout << temp.student[i].Gender;
                            GoTo(38,3 + i);cout << temp.student[i].DateOfBirth;
                            GoTo(53,3 + i);cout << temp.student[i].StudentID;
                            if (temp.student[i].Midterm_mark != -1){
                                GoTo(67,3 + i);cout << temp.student[i].Midterm_mark;
                            }
                            if (temp.student[i].Final_mark != -1){
                                GoTo(77,3 + i);cout << temp.student[i].Final_mark;
                            }
                            if (temp.student[i].Other_mark != -1){
                                GoTo(88,3 + i);cout << temp.student[i].Other_mark;
                            }
                            if (temp.student[i].Total_mark != -1){
                                GoTo(100,3 + i);cout << temp.student[i].Total_mark << endl;
                            }
                            if (i == 0) TextColor(7);
                        }
                        pos = 0;
                    }
                }
            }
            if (c == -32 && temp.NumberOfStudent_Current != 0){
                c = getch();
                if (c == 72){ //Di len, 80 di xuong
                    TextColor(7);
                    for (int i = 0; i <= 107; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName + ' ' + temp.student[pos].LastName;
                    GoTo(28,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(38,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(53,3 + pos);cout << temp.student[pos].StudentID;
                    if (temp.student[pos].Midterm_mark != -1){
                        GoTo(67,3 + pos);cout << temp.student[pos].Midterm_mark;
                    }
                    if (temp.student[pos].Final_mark != -1){
                        GoTo(77,3 + pos);cout << temp.student[pos].Final_mark;
                    }
                    if (temp.student[pos].Other_mark != -1){
                        GoTo(88,3 + pos);cout << temp.student[pos].Other_mark;
                    }
                    if (temp.student[pos].Total_mark != -1){
                        GoTo(100,3 + pos);cout << temp.student[pos].Total_mark << endl;
                    }
                    if (pos == 0) pos = temp.NumberOfStudent_Current - 1;
                    else pos--;
                    SetColor(7, 0);
                    for (int i = 0; i <= 107; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName + ' ' + temp.student[pos].LastName;
                    GoTo(28,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(38,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(53,3 + pos);cout << temp.student[pos].StudentID;
                    if (temp.student[pos].Midterm_mark != -1){
                        GoTo(67,3 + pos);cout << temp.student[pos].Midterm_mark;
                    }
                    if (temp.student[pos].Final_mark != -1){
                        GoTo(77,3 + pos);cout << temp.student[pos].Final_mark;
                    }
                    if (temp.student[pos].Other_mark != -1){
                        GoTo(88,3 + pos);cout << temp.student[pos].Other_mark;
                    }
                    if (temp.student[pos].Total_mark != -1){
                        GoTo(100,3 + pos);cout << temp.student[pos].Total_mark << endl;
                    }
                }
                if (c == 80){ //Di Xuong
                    TextColor(7);
                    for (int i = 0; i <= 107; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName + ' ' + temp.student[pos].LastName;
                    GoTo(28,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(38,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(53,3 + pos);cout << temp.student[pos].StudentID;
                    if (temp.student[pos].Midterm_mark != -1){
                        GoTo(67,3 + pos);cout << temp.student[pos].Midterm_mark;
                    }
                    if (temp.student[pos].Final_mark != -1){
                        GoTo(77,3 + pos);cout << temp.student[pos].Final_mark;
                    }
                    if (temp.student[pos].Other_mark != -1){
                        GoTo(88,3 + pos);cout << temp.student[pos].Other_mark;
                    }
                    if (temp.student[pos].Total_mark != -1){
                        GoTo(100,3 + pos);cout << temp.student[pos].Total_mark << endl;
                    }
                    if (pos == temp.NumberOfStudent_Current - 1) pos = 0;
                    else pos++;
                    SetColor(7, 0);
                    for (int i = 0; i <= 107; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName + ' ' + temp.student[pos].LastName;
                    GoTo(28,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(38,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(53,3 + pos);cout << temp.student[pos].StudentID;
                    if (temp.student[pos].Midterm_mark != -1){
                        GoTo(67,3 + pos);cout << temp.student[pos].Midterm_mark;
                    }
                    if (temp.student[pos].Final_mark != -1){
                        GoTo(77,3 + pos);cout << temp.student[pos].Final_mark;
                    }
                    if (temp.student[pos].Other_mark != -1){
                        GoTo(88,3 + pos);cout << temp.student[pos].Other_mark;
                    }
                    if (temp.student[pos].Total_mark != -1){
                        GoTo(100,3 + pos);cout << temp.student[pos].Total_mark << endl;
                    }
                }
            }
            if (c == 8 && temp.NumberOfStudent_Current != 0){ //backspace
                DeleteOneStudent(temp, pos);
                TextColor(7);
                system("cls");
                PrintListOfStudentInCourse(temp);
                return;
            }
            if (c == 13){
                EditResult(temp, pos);
                TextColor(7);
                system("cls");
                GoTo(120, 1); 
                TextColor(2);
                cout <<"Press f8 to add student";
                GoTo(120, 2);
                cout <<"Press f9 to export file csv";
                GoTo(120, 3);
                cout <<"Press f10 to import file csv";
                TextColor(7);
                SetColor(14, 7);
                GoTo(75 - (37 + temp.CourseName.length() + temp.ClassName.length() )/ 2, 0); 
                cout <<"Danh sach sinh vien hoc mon "<< temp.CourseName <<" cua lop "<< temp.ClassName << endl;
                SetColor(14, 1);
                for (int i = 0; i <= 107; i++){
                    GoTo(i, 2); cout <<' ';
                }
                GoTo(0, 2);  cout << "STT";
                GoTo(7, 2);  cout << "Ho va Ten";
                GoTo(25, 2); cout << "Gioi tinh";
                GoTo(38, 2); cout << "Ngay sinh";
                GoTo(55, 2); cout << "MSSV";
                GoTo(65, 2); cout << "Diem GK";
                GoTo(75, 2); cout << "Diem CK";
                GoTo(85, 2); cout << "Diem cong";
                GoTo(97, 2); cout << "Tong Phay" << endl;
                SetColor(7, 0);
                for (int i = 0; i <= 107; i++){
                    GoTo(i, 3); cout <<' ';
                }
                for (int i = 0; i < temp.NumberOfStudent_Current; i++){
                    GoTo(0, 3 + i);cout << i + 1;
                    GoTo(5, 3 + i);cout << temp.student[i].FirstName + ' ' + temp.student[i].LastName;
                    GoTo(28,3 + i);cout << temp.student[i].Gender;
                    GoTo(38,3 + i);cout << temp.student[i].DateOfBirth;
                    GoTo(53,3 + i);cout << temp.student[i].StudentID;
                    if (temp.student[i].Midterm_mark != -1){
                        GoTo(67,3 + i);cout << temp.student[i].Midterm_mark;
                    }
                    if (temp.student[i].Final_mark != -1){
                        GoTo(77,3 + i);cout << temp.student[i].Final_mark;
                    }
                    if (temp.student[i].Other_mark != -1){
                        GoTo(88,3 + i);cout << temp.student[i].Other_mark;
                    }
                    if (temp.student[i].Total_mark != -1){
                        GoTo(100,3 + i);cout << temp.student[i].Total_mark << endl;
                    }
                    if (i == 0) TextColor(7);
                }
                pos = 0;
            }
            if (c == 27) {GoTo(0, 15);TextColor(7);return;} //ESC
        }
    }
    system("pause");
}

void EditResult(Course& temp, int pos){
    TextColor(7);
    system("cls");
    cout <<"Sinh vien: " << temp.student[pos].FirstName + ' ' + temp.student[pos].LastName << endl;
    cout <<"MSSV     : " << temp.student[pos].StudentID << endl;
    string str[4];
    str[0] = "Midterm Mark: ";
    str[1] = "Final Mark  : ";
    str[2] = "Other Mark  : ";
    str[3] = "Total Mark  : ";
    float res[4];
    res[0] = temp.student[pos].Midterm_mark;
    res[1] = temp.student[pos].Final_mark;
    res[2] = temp.student[pos].Other_mark;
    res[3] = temp.student[pos].Total_mark;
    
    SetColor(7, 0);
    GoTo(0, 5); cout << str[0] << res[0];
    TextColor(7);
    for (int i = 1; i < 4; i++){
        GoTo(0, 5 + i);
        cout << str[i] << res[i];
    }
    int i = 0;
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ //Di len
                    TextColor(7);
                    GoTo(0, 5 + i);
                    cout << str[i] << res[i];
                    if (i == 0) i = 3;
                    else i--;
                    SetColor(7, 0);
                    GoTo(0, 5 + i);
                    cout << str[i] << res[i];
                    TextColor(7);
                }
                if (c == 80){ //Di xuong
                    TextColor(7);
                    GoTo(0, 5 + i);
                    cout << str[i] << res[i];
                    if (i == 3) i = 0;
                    else i++;
                    SetColor(7, 0);
                    GoTo(0, 5 + i);
                    cout << str[i] << res[i];
                    TextColor(7);
                }
            }
            if (c == 8){ //backspace
                TextColor(7);
                for (int j = 14; j <= 18; j++) {
                    GoTo(j, 5 + i);
                    cout <<' ';
                }
                GoTo(14, 5 + i);
                switch (i){
                    case 0:{
                        cin >> temp.student[pos].Midterm_mark;
                        res[0] = temp.student[pos].Midterm_mark;
                        break;
                    }
                    case 1:{
                        cin >> temp.student[pos].Final_mark;
                        res[1] = temp.student[pos].Final_mark;
                        break;
                    }
                    case 2:{
                        cin >> temp.student[pos].Other_mark;
                        res[2] = temp.student[pos].Other_mark;
                        break;
                    }
                    case 3:{
                        cin >> temp.student[pos].Total_mark;
                        res[3] = temp.student[pos].Total_mark;
                        break;
                    }
                }
                extern hcmus NamHoc;
                int n = NamHoc.NumberOfSchoolYear - 1;
                int hocky = NamHoc.ptr[n].NumberOfSemester;
                string path = "Data\\" + NamHoc.ptr[n].SchoolYear + "\\Semester" + to_string(NamHoc.ptr[n].semester[hocky].STT) + '\\' + temp.CourseID;
                WriteOnFile_Student(temp.student, temp.NumberOfStudent_Current, path);
            }
            if (c == 27) return;
        }
    }
}

void ExportFileCSV(Course temp){
    string filename = temp.CourseName + '_' + temp.ClassName + ".csv";
    ofstream ofs(filename);
    if (!ofs){
        cout << "Error opening file";
        return;
    }
    ofs << "No,Name,Gender,Date of Birth,Student ID,Midterm Mark,Final Mark,Other Mark,Total Mark" << endl;
    for (int i = 0; i < temp.NumberOfStudent_Current; i++){
        ofs << i + 1 << ',';
        ofs << temp.student[i].FirstName << ' ' << temp.student[i].LastName  << ',';
        ofs << temp.student[i].Gender << ',';
        ofs << temp.student[i].DateOfBirth << ',';
        ofs << temp.student[i].StudentID << endl;
    }
    ofs.close();
    TextColor(2);
    GoTo(63, 1);
    cout <<"Da xuat file thanh cong";
    TextColor(7);
    sleep(1);
    for (int i = 63; i <= 86; i++){
        GoTo(i, 1); cout <<' ';
    }
}
//Score Board file
bool ImportFileCSV(Course& temp){
    if (temp.NumberOfStudent_Current == 0){
        GoTo(52, 7);
        SetColor(14, 4);
        cout <<"Danh sach dang trong, khong the cap nhat file";
        TextColor(7);
        sleep(1);
        for (int i = 52; i <= 98; i++){
            GoTo(i, 7); cout <<' ';
        }
        return 0;
    }
    ifstream ifs(temp.CourseName + '_' + temp.ClassName  + ".csv");
    if (!ifs){
        TextColor(2);
        GoTo(57, 1);
        cout <<"Mon hoc nay chua duoc cap nhap diem";
        TextColor(7);
        sleep(1);
        for (int i = 57; i <= 92; i++){
            GoTo(i, 1); cout <<' ';
        }
        return 0;
    }
    string no, name, gender, date_of_birth, studentID, diem_gk, diem_ck, diem_cong,tong_phay;
    getline(ifs, no, ',');
    getline(ifs, name, ',');
    getline(ifs, gender, ',');
    getline(ifs, date_of_birth, ',');
    getline(ifs, studentID, ',');
    getline(ifs, diem_gk, ',');
    getline(ifs, diem_ck, ',');
    getline(ifs, diem_cong, ',');
    getline(ifs, tong_phay);
    char comma;
    for (int i = 0; i < temp.NumberOfStudent_Current; i++){
        getline(ifs, no, ',');
        getline(ifs, name, ',');
        getline(ifs, gender, ',');
        getline(ifs, date_of_birth, ',');
        getline(ifs, studentID, ',');
        ifs >> temp.student[i].Midterm_mark;
        ifs >> comma; //doc dau phay
        ifs >> temp.student[i].Final_mark;
        ifs >> comma;
        ifs >> temp.student[i].Other_mark;
        ifs >> comma;
        ifs >> temp.student[i].Total_mark;
        ifs.ignore();
    }
    return 1;
}

void WriteOnFile_One_Student(StudentInfo temp, int stt, string path){
    path = path +".csv";
    ofstream ofs(path, ios::app);
    if (!ofs){
        cout << "Co loi khong mo duoc file";
        return;
    }
    if (stt != 0) ofs << endl;
    ofs << stt + 1 << ',';
    ofs << temp.StudentID << ',';
    ofs << temp.FirstName << ',';
    ofs << temp.LastName << ',';
    ofs << temp.Gender << ',';
    ofs << temp.DateOfBirth << ',';
    ofs << temp.SocialID << ',';
    ofs << temp.Midterm_mark << ',';
    ofs << temp.Final_mark << ',';
    ofs << temp.Other_mark << ',';
    ofs << temp.Total_mark;
    ofs.close();
}

void WriteOnFile_Student(StudentInfo *temp, int n, string path){
    path = path +".csv";
    ofstream ofs(path);
    if (!ofs){
        cout << "Co loi khong mo duoc file";
        //system("pause");
        return;
    }
    //cout <<"Hello";
    //system("pause");
    // ofs << "First Name,";
    // ofs << "Last Name,";
    // ofs << "Gender,";
    // ofs << "Birthday,";
    // ofs << "Student ID,";
    // ofs << "Social ID,";
    // ofs << "Midterm Mark,";
    // ofs << "Final Mark,";
    // ofs << "Other Mark,";
    // ofs << "Total Mark" << endl;

    for (int i = 0; i < n; i++){
        if (i != 0) ofs << endl;
        ofs << i + 1 << ',';
        ofs << temp[i].StudentID << ',';
        ofs << temp[i].FirstName << ',';
        ofs << temp[i].LastName << ',';
        ofs << temp[i].Gender << ',';
        ofs << temp[i].DateOfBirth << ',';
        ofs << temp[i].SocialID << ',';
        ofs << temp[i].Midterm_mark << ',';
        ofs << temp[i].Final_mark << ',';
        ofs << temp[i].Other_mark << ',';
        ofs << temp[i].Total_mark;
    }
    ofs.close();
}
void WriteOnFile_One_Course(Course temp, string path){
    extern hcmus NamHoc;
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;

    path = path + ".csv";
    ofstream ofs(path, ios::app);
    if (!ofs){
        cout <<"Co loi, khong ghi len file duoc" << endl;
        return;
    }
    if (NamHoc.ptr[n].semester[hocky_stt].HeadList != nullptr) ofs << endl;
    ofs << temp.CourseID << ',';
    ofs << temp.CourseName << ',';
    ofs << temp.ClassName << ',';
    ofs << temp.TeacherName << ',';
    ofs << temp.NumberOfCredit << ',';
    ofs << temp.NumberOfStudent_Max << ',';
    ofs << temp.DayOfWeek << ',';
    ofs << temp.session;
    ofs.close();
}

void WriteOnFile_Course(ListOfCourse* tam, string path){
    path = path + ".csv";
    ofstream ofs(path);
    if (!ofs){
        cout <<"Co loi, khong ghi len file duoc" << endl;
        return;
    }
    // ofs << "COURSE ID,";
    // ofs << "COURSE NAME,";
    // ofs << "CLASS NAME,";
    // ofs << "TEACHER NAME,";
    // ofs << "CREDITs,";
    // ofs << "STUDENT_Max,";
    // ofs << "DAY OF WEEK,";
    // ofs << "SESSION" << endl;
    ListOfCourse* temp = tam;
    while (temp != nullptr){
        if (temp != tam) ofs << endl;
        ofs << temp->data.CourseID << ',';
        ofs << temp->data.CourseName << ',';
        ofs << temp->data.ClassName << ',';
        ofs << temp->data.TeacherName << ',';
        ofs << temp->data.NumberOfCredit << ',';
        ofs << temp->data.NumberOfStudent_Max << ',';
        ofs << temp->data.DayOfWeek << ',';
        ofs << temp->data.session;
        temp = temp->pNext;
    }
    ofs.close();
}

void UploadAllInfor(){
    extern hcmus NamHoc;
    ifstream ifs("Data\\SchoolYear.txt");
    ifstream ifs1,ifs2, ifs3;
    if (!ifs){
        cout << "Co loi khi mo file nam hoc" << endl;
        return;
    }
    string schoolyear_stt;
    string path = "Data\\";
    //string s1, s2, s3, s4;
    char ch;
    while (!ifs.eof()){
        getline(ifs, schoolyear_stt);
        reallocate(NamHoc);
        int n = NamHoc.NumberOfSchoolYear - 1;
        NamHoc.ptr[n].SchoolYear = schoolyear_stt;
        NamHoc.ptr[n].HeadList = nullptr;
        NamHoc.ptr[n].EndList = nullptr;
        //cout << NamHoc.NumberOfSchoolYear <<' '<<NamHoc.ptr[n].SchoolYear <<' '<<path + schoolyear_stt + "\\List Of Classes.csv"<< endl;
        //cout << path + schoolyear_stt + "\\List Of Classes.csv" << endl;
        //system("pause");
        ifs1.open(path + schoolyear_stt + "\\List Of Classes.csv");
        if (!ifs1){
            cout <<"Co loi, khong mo duoc file" << endl;
            return;
        }
        while (!ifs1.eof()){ //Lop
            ListOfClasses* node = new ListOfClasses;
            node->pNext = nullptr;
            node->pPrev = nullptr;
            node->data.NumberOfStudent_Current = 0;
            getline(ifs1, node->data.nameClass, ',');
            getline(ifs1, node->data.major, ',');
            getline(ifs1, node->data.TimeBegin, ',');
            //ifs1 >> ch; //doc dau phay
            ifs1 >> node->data.NumberOfStudent_max;
            node->data.student = new StudentInfo[node->data.NumberOfStudent_max + 1];
            ifs1.ignore();
            //cout << node->data.nameClass << ' '<< node->data.major <<' ' << node->data.TimeBegin << ' ' << node->data.NumberOfStudent_max << endl;
            //cout << path + schoolyear_stt + "\\Class\\" + node->data.nameClass + ".csv" << endl;
            //system("pause");
            ifs2.open(path + schoolyear_stt + "\\Class\\" + node->data.nameClass + ".csv");
            if (!ifs2){
                cout <<"Co loi khong mo duoc file 1" << endl;
                return;
            }
            int i = 0;
            while (!ifs2.eof()){ //Sinh Vien trong lop
                ifs2 >> i;
                ifs2 >> ch; //Doc dau phay
                //ifs2.ignore();
                getline(ifs2, node->data.student[i - 1].StudentID, ',');
                getline(ifs2, node->data.student[i - 1].FirstName, ',');
                getline(ifs2, node->data.student[i - 1].LastName, ',');
                getline(ifs2, node->data.student[i - 1].Gender, ',');
                getline(ifs2, node->data.student[i - 1].DateOfBirth, ',');
                getline(ifs2, node->data.student[i - 1].SocialID, ',');
                ifs2 >> node->data.student[i - 1].Midterm_mark;
                ifs2 >> ch;
                ifs2 >> node->data.student[i - 1].Final_mark;
                ifs2 >> ch;
                ifs2 >> node->data.student[i - 1].Other_mark;
                ifs2 >> ch;
                ifs2 >> node->data.student[i - 1].Total_mark;
                ifs2.ignore();
                //cout << i <<' '<<ch <<' '<<node->data.student[i - 1].StudentID <<' '<<node->data.student[i-1].FirstName<< endl;
            }
            ifs2.close();
            node->data.NumberOfStudent_Current = i;
            if (NamHoc.ptr[n].HeadList == nullptr) NamHoc.ptr[n].HeadList = node;
            else if (NamHoc.ptr[n].EndList == nullptr){
                NamHoc.ptr[n].EndList = node;
                NamHoc.ptr[n].HeadList->pNext = NamHoc.ptr[n].EndList;
                NamHoc.ptr[n].EndList->pPrev = NamHoc.ptr[n].HeadList;
            }
            else {
                node->pPrev = NamHoc.ptr[n].EndList;
                NamHoc.ptr[n].EndList->pNext = node;
                NamHoc.ptr[n].EndList = node;
            }
        }
        ifs1.close();
        /*--------Update Course--------*/
        ifs1.open(path + schoolyear_stt + "\\List Of Semester.csv");
        if (!ifs1){
            //cout  << path + schoolyear_stt + "\\List Of Semester.csv"  << endl;
            cout <<"Co loi, khong mo duoc file 2" << endl;
            return;
        }
        while (!ifs1.eof()){ //Course
            int Number_Semester = ++NamHoc.ptr[n].NumberOfSemester;
            ifs1 >> NamHoc.ptr[n].semester[Number_Semester].STT;
            ifs1 >> ch;
            getline(ifs1, NamHoc.ptr[n].semester[Number_Semester].StartDate, ',');
            getline(ifs1, NamHoc.ptr[n].semester[Number_Semester].EndDate, ',');
            NamHoc.ptr[n].semester[Number_Semester].HeadList = nullptr;
            NamHoc.ptr[n].semester[Number_Semester].EndList = nullptr;
            //cout << path + schoolyear_stt + "\\Semester" + to_string(NamHoc.ptr[n].semester[Number_Semester].STT) + "\\Course.csv" << endl;
            //system("pause");
            ifs2.open(path + schoolyear_stt + "\\Semester" + to_string(NamHoc.ptr[n].semester[Number_Semester].STT) + "\\Course.csv");
            if (!ifs2){
                cout <<"Co loi khong mo duoc file 3" << endl;
                return;
            }
            //cout <<path + schoolyear_stt + "\\Semester" + to_string(NamHoc.ptr[n].semester[Number_Semester].STT) + "\\Course.csv" << endl;
            while (!ifs2.eof()){
                ListOfCourse* node = new ListOfCourse;
                node->pNext = nullptr;
                node->pPrev = nullptr;
                getline(ifs2, node->data.CourseID, ',');
                getline(ifs2, node->data.CourseName, ',');
                getline(ifs2, node->data.ClassName, ',');
                getline(ifs2, node->data.TeacherName, ',');
                ifs2 >> node->data.NumberOfCredit;
                ifs2 >> ch;
                ifs2 >> node->data.NumberOfStudent_Max;
                ifs2.ignore();
                getline(ifs2, node->data.DayOfWeek, ',');
                getline(ifs2, node->data.session);
                node->data.student = new StudentInfo[node->data.NumberOfStudent_Max + 1];
                node->data.NumberOfStudent_Current = 0;
                //cout << node->data.CourseID <<' '<< node->data.CourseName << ' '<< node->data.ClassName <<' ';
                //cout << node->data.TeacherName <<' '<< node->data.NumberOfCredit <<' '<< node->data.NumberOfStudent_Max <<' '<<node->data.DayOfWeek <<' '<<node->data.session << endl;
                //cout << path + schoolyear_stt + "\\Semester" + to_string(NamHoc.ptr[n].semester[Number_Semester].STT) + '\\' + node->data.CourseID + ".csv" << endl;
                
                ifs3.open(path + schoolyear_stt + "\\Semester" + to_string(NamHoc.ptr[n].semester[Number_Semester].STT) + '\\' + node->data.CourseID + ".csv");
                if (ifs3){
                    int tam;
                    char ch1;
                    //cout << node->data.CourseID << endl;
                    while (!ifs3.eof()){
                        ifs3 >> tam;
                        ifs3 >> ch1; //Doc dau phay
                        //ifs3.ignore();
                        getline(ifs3, node->data.student[tam - 1].StudentID, ',');
                        getline(ifs3, node->data.student[tam - 1].FirstName, ',');
                        getline(ifs3, node->data.student[tam - 1].LastName, ',');
                        getline(ifs3, node->data.student[tam - 1].Gender, ',');
                        getline(ifs3, node->data.student[tam - 1].DateOfBirth, ',');
                        getline(ifs3, node->data.student[tam - 1].SocialID, ',');
                        ifs3 >> node->data.student[tam - 1].Midterm_mark;
                        ifs3 >> ch1;
                        ifs3 >> node->data.student[tam - 1].Final_mark;
                        ifs3 >> ch1;
                        ifs3 >> node->data.student[tam - 1].Other_mark;
                        ifs3 >> ch1;
                        ifs3 >> node->data.student[tam - 1].Total_mark;
                        ifs3.ignore();
                        //cout <<"\t" << tam <<' '<<node->data.student[tam - 1].StudentID<<' '<<node->data.student[tam - 1].FirstName<<' '<<node->data.student[tam - 1].LastName<<' '<<node->data.student[tam - 1].Gender<<' '<<node->data.student[tam - 1].DateOfBirth;
                        //cout << node->data.student[tam - 1].SocialID << ' '<<node->data.student[tam - 1].Midterm_mark <<' '<<node->data.student[tam - 1].Final_mark<<' '<<node->data.student[tam - 1].Other_mark<<' '<<node->data.student[tam - 1].Total_mark << endl;
                    }
                    node->data.NumberOfStudent_Current = tam;
                }
                ifs3.close();
                if (NamHoc.ptr[n].semester[Number_Semester].HeadList == nullptr) NamHoc.ptr[n].semester[Number_Semester].HeadList = node;
                else if (NamHoc.ptr[n].semester[Number_Semester].EndList == nullptr){
                        NamHoc.ptr[n].semester[Number_Semester].HeadList->pNext = node;
                        node->pPrev = NamHoc.ptr[n].semester[Number_Semester].HeadList;
                        NamHoc.ptr[n].semester[Number_Semester].EndList = node;
                    }
                    else {
                        NamHoc.ptr[n].semester[Number_Semester].EndList->pNext = node;
                        node->pPrev = NamHoc.ptr[n].semester[Number_Semester].EndList;
                        NamHoc.ptr[n].semester[Number_Semester].EndList = node;
                    }
            }
            ifs2.close();
        }
        ifs1.close();
    }
    ifs.close();
}

void Main_Menu_For_Admin(int find){
    extern hcmus NamHoc;
    string choice[5] = {"Your Information", "Create", "Add", "View", "Log out"};
    GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
    GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
    GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
    GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
    GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
    GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
    GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
    DrawBox(60, 10, 11, 30, 3);
    SetColor(7, 0);
    GoTo(65, 12); cout << choice[0];
    TextColor(7);
    GoTo(65, 14); cout << choice[1];
    GoTo(65, 16); cout << choice[2];
    GoTo(65, 18); cout << choice[3];
    GoTo(65, 20); cout << choice[4];
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
                    if (pos == 0) pos = 4;
                    else pos--;
                    SetColor(7, 0);
                    GoTo(65, 12 + pos * 2);
                    cout << choice[pos];
                }
                if (c == 80){ //Di Xuong
                    TextColor(7);
                    GoTo(65, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 4) pos = 0;
                    else pos++;
                    SetColor(7, 0);
                    GoTo(65, 12 + pos * 2);
                    cout << choice[pos];
                }
            }
            if (c == 13){ //Enter
                TextColor(7);
                if (pos == 0) MenuInfo(find);
                if (pos == 1) Menu_Create();
                if (pos == 2) Menu_Add();
                if (pos == 3) Menu_View();
                TextColor(7);
                system("cls");
                GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
                GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
                GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
                GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
                GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
                n = NamHoc.NumberOfSchoolYear - 1;
                hocky_stt = NamHoc.ptr[n].NumberOfSemester;
                GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
                GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
                DrawBox(60, 10, 11, 30, 3);
                for (int i = 0; i < 5; i++){
                    if (i == pos) SetColor(7, 0);
                    GoTo(65, 12 + i * 2); cout << choice[i];
                    if (i == pos) TextColor(7);
                }
                if (pos == 4) return;
            }
        }
    }
}

void Menu_Create(){
    extern hcmus NamHoc;
    TextColor(7);
    system("cls");
    GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
    GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
    GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
    GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
    GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
    GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
    GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
    string choice[5] = {"Create new School Year", "Create new semester", "Create new simple class", "Create new multiple classes", "Back"};
    DrawBox(57, 10, 11, 36, 3);
    SetColor(7, 0);
    GoTo(62, 12); cout << choice[0];
    TextColor(7);
    GoTo(62, 14); cout << choice[1];
    GoTo(62, 16); cout << choice[2];
    GoTo(62, 18); cout << choice[3];
    GoTo(62, 20); cout << choice[4];
    int pos = 0;
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ //Di len
                    TextColor(7);
                    GoTo(62, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 0) pos = 4;
                    else pos--;
                    SetColor(7, 0);
                    GoTo(62, 12 + pos * 2);
                    cout << choice[pos];
                }
                if (c == 80){ //Di Xuong
                    TextColor(7);
                    GoTo(62, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 4) pos = 0;
                    else pos++;
                    SetColor(7, 0);
                    GoTo(62, 12 + pos * 2);
                    cout << choice[pos];
                }
            }
            if (c == 13){ //Enter
                if (pos == 0) InputSchoolYear(NamHoc);
                if (pos == 1) InputSemester(NamHoc);
                if (pos == 2) CreateSimpleClass(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1]);
                if (pos == 3) CreateMultipleClasses(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1]);
                if (pos == 4) return;
                TextColor(7);
                system("cls");
                GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
                GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
                GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
                GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
                GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
                n = NamHoc.NumberOfSchoolYear - 1;
                hocky_stt = NamHoc.ptr[n].NumberOfSemester;
                GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
                GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
                string choice[5] = {"Create new School Year", "Create new semester", "Create new simple class", "Create new multiple classes", "Back"};
                DrawBox(57, 10, 11, 36, 3);
                for (int i = 0; i < 5; i++){
                    if (i == pos) SetColor(7, 0);
                    GoTo(62, 12 + i * 2); cout << choice[i];
                    if (i == pos) TextColor(7);
                }
            }
        }
    }
}

void Menu_Add(){
    extern hcmus NamHoc;
    TextColor(7);
    system("cls");
    GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
    GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
    GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
    GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
    GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
    GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
    GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
    string choice[5] = {"Add one student to class", "Import list of student from file", "Add course to semester", "Add one student to Course" , "Back"};
    DrawBox(54, 10, 11, 42, 3);
    SetColor(7, 0);
    GoTo(60, 12); cout << choice[0];
    TextColor(7);
    GoTo(60, 14); cout << choice[1];
    GoTo(60, 16); cout << choice[2];
    GoTo(60, 18); cout << choice[3];
    GoTo(60, 20); cout << choice[4];
    int pos = 0;
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ //Di len
                    TextColor(7);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 0) pos = 4;
                    else pos--;
                    SetColor(7, 0);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                }
                if (c == 80){ //Di Xuong
                    TextColor(7);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 4) pos = 0;
                    else pos++;
                    SetColor(7, 0);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                }
            }
            if (c == 13){ //Enter
                if (pos == 0) AddOneStudentToClass();
                if (pos == 1) InputStudentFromFile();
                if (pos == 2) AddCourseToSemester(NamHoc.ptr[n].semester[hocky_stt]);
                if (pos == 3) AddStudentIntoCourse();
                if (pos == 4) return;
                TextColor(7);
                system("cls");
                GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
                GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
                GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
                GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
                GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
                int n = NamHoc.NumberOfSchoolYear - 1;
                int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
                GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
                GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
                string choice[5] = {"Add one student to class", "Import list of student from file", "Add course to semester", "Add one student to Course" , "Back"};
                DrawBox(54, 10, 11, 42, 3);
                TextColor(7);
                for (int i = 0; i < 5; i++){
                    if (i == pos) SetColor(7, 0);
                    GoTo(60, 12 + 2 * i);
                    cout << choice[i];
                    if (i == pos) TextColor(7);
                }
            }
        }
    }
}

void Menu_View(){
    extern hcmus NamHoc;
    TextColor(7);
    system("cls");
    GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
    GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
    GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
    GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
    GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
    int n = NamHoc.NumberOfSchoolYear - 1;
    int hocky_stt = NamHoc.ptr[n].NumberOfSemester;
    GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
    GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
    string choice[3] = {"View list of classes", "View list of courses", "Back"};
    DrawBox(54, 10, 7, 42, 3);
    SetColor(7, 0);
    GoTo(60, 12); cout << choice[0];
    TextColor(7);
    GoTo(60, 14); cout << choice[1];
    GoTo(60, 16); cout << choice[2];

    int pos = 0;
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ //Di len
                    TextColor(7);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 0) pos = 2;
                    else pos--;
                    SetColor(7, 0);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                }
                if (c == 80){ //Di Xuong
                    TextColor(7);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                    if (pos == 2) pos = 0;
                    else pos++;
                    SetColor(7, 0);
                    GoTo(60, 12 + pos * 2);
                    cout << choice[pos];
                }
            }
            if (c == 13){ //Enter
                if (pos == 0) MenuListOfClass(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1]);
                if (pos == 1) PrintListOfCourseInSemester(NamHoc.ptr[n].semester[hocky_stt]);
                if (pos == 2) return;
                TextColor(7);
                system("cls");
                GoTo(57,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
                GoTo(57,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---'" << "\n";
                GoTo(57,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
                GoTo(57,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
                GoTo(57,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
                //n = NamHoc.NumberOfSchoolYear - 1;
                //hocky_stt = NamHoc.ptr[n].NumberOfSemester;
                GoTo(66, 6); cout << "School Year "<<NamHoc.ptr[n].SchoolYear;
                GoTo(72, 7); cout << "Semester " << (hocky_stt == 0 ? 0 :NamHoc.ptr[n].semester[hocky_stt].STT);
                string choice[5] = {"View list of classes", "View list of courses", "Back"};
                DrawBox(54, 10, 7, 42, 3);
                for (int i = 0; i < 3; i++){
                    if (i == pos) SetColor(7, 0);
                    GoTo(60, 12 + i * 2); cout << choice[i];
                    if (i == pos) TextColor(7);
                }
            }
        }
    }
}