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
    reallocate(KHTN);
    bool check;
    int n = KHTN.NumberOfSchoolYear - 1;
    KHTN.ptr[n].HeadList = nullptr;
    KHTN.ptr[n].EndList = nullptr;
    do {
        check = 0;
        cout <<"Input School Year (ex: 2018-2019): ";
        getline(cin, KHTN.ptr[n].SchoolYear);
        for (int i = 0; i < n; i++){
            if (KHTN.ptr[i].SchoolYear == KHTN.ptr[KHTN.NumberOfSchoolYear - 1].SchoolYear){
                TextColor(4);
                cout << "Nam hoc da trung"<< endl;
                sleep(1);
                system("cls");
                TextColor(7);
                check = 1;
                break;
            }
        }
    }while (check);
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
}

void InputSemester(hcmus &KHTN){
    string temp;
    while(true){
        cout <<"Nhap nam hoc cua hoc ky: ";
        getline(cin, temp);
        for (int i = 0; i < KHTN.NumberOfSchoolYear; i++){
            if (KHTN.ptr[i].SchoolYear == temp){
                if (KHTN.ptr[i].NumberOfSemester == 3){
                    cout <<"Nam hoc da co du 3 ky" << endl;
                    return;
                }
                KHTN.ptr[i].NumberOfSemester++;
                cout <<"Nhap hoc ky       : ";
                cin >> KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].STT;
                cin.ignore();
                cout <<"Nhap ngay bat dau : ";
                getline(cin, KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].StartDate);
                cout <<"Nhap ngay ket thuc: ";
                getline(cin, KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].EndDate);
                cout <<"Da nhap hoc ky "<<KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].STT<<" cho nam hoc "<<temp<<endl;
                //KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1] = KHTN.ptr[i].NumberOfSemester;
                KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].HeadList = nullptr;
                KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].EndList = nullptr;
                return;
            }
        }
        TextColor(4);
        cout <<"Khong ton tai nam hoc nay" << endl;
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
    ListOfClasses* node = new ListOfClasses;

    do{
        cout <<"Nhap ten lop: ";
        getline(cin, node->data.nameClass);
        if (FindClass(temp, node->data.nameClass) != nullptr) cout << "Da ton tai lop hoc nay, vui long nhap lai" << endl;
        else break;
    }while(true);

    cout <<"Nhap chuyen nganh: ";
    getline(cin, node->data.major);
    node->data.TimeBegin = temp.SchoolYear;
    cout <<"Nhap so luong sinh vien: ";
    cin >> node->data.NumberOfStudent_max;
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
    //NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1] = temp;
}

void CreateMultipleClasses(SchoolTime& temp){
    //extern hcmus NamHoc;
    //SchoolTime temp = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1];
    string name;
    cout <<"Nhap ten viet tat cua lop (Ex: CLC, APCS, CTT,...): ";
    getline(cin, name);
    name = temp.SchoolYear[3] + name;
    name = temp.SchoolYear[2] + name;
    string chuyenNganh;
    cout <<"Nhap chuyen nganh: ";
    getline(cin, chuyenNganh);
    cout <<"Nhap so luong lop: ";
    int NumberStudent, NumberClasses;
    cin >> NumberClasses;
    cout <<"Nhap so luong sinh vien moi lop: ";
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
    }
    //NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1] = temp;
}

//Chỉ áp dụng cho các lớp ở năm học hiện tại. Không áp dụng cho các năm trước
void AddOneStudentToClass(string NameOfClass){
    extern hcmus NamHoc;
    ListOfClasses* node = FindClass(NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1], NameOfClass);
    if (node == nullptr) {
        cout <<"Khong ton tai lop nay hoac lop nay da tot nghiep" << endl;
        return;
    }
    if (node->data.NumberOfStudent_Current == node->data.NumberOfStudent_max){
        cout <<"Lop da day sinh vien" << endl;
        return;
    }
    cout <<"Nhap thong tin sinh vien" << endl;
    int i = node->data.NumberOfStudent_Current++;
    cout <<"\t Nhap ho                            : ";
    getline(cin, node->data.student[i].FirstName);
    cout <<"\t Nhap ten                           : ";
    getline(cin, node->data.student[i].LastName);
    cout <<"\t Nhap gioi tinh                     : ";
    getline(cin, node->data.student[i].Gender);
    cout <<"\t Nhap ngay thang nam sinh (dd/mm/yy): ";
    getline(cin, node->data.student[i].DateOfBirth);
    cout <<"\t Nhap ma so sinh vien               : ";
    getline(cin, node->data.student[i].StudentID);
    cout <<"\t Nhap CCCD                          : ";
    getline(cin, node->data.student[i].SocialID);
}

//Chỉ áp dụng cho các lớp ở năm học hiện tại. Không áp dụng cho các năm trước
void InputStudentFromFile(string NameOfClass){
    extern hcmus NamHoc;
    SchoolTime temp = NamHoc.ptr[NamHoc.NumberOfSchoolYear - 1];
    ListOfClasses* tam = temp.HeadList;
    while (tam != nullptr){
        if (tam->data.nameClass == NameOfClass) break;
        if (tam == temp.EndList || tam->pNext == nullptr){ // neu chay den cuoi danh sach ma khong co ten lop xuat hien thi thoat chuong trinh
            cout << "Khong ton tai lop nay trong nam hoc nay" << endl;
            return; 
        }
        tam = tam->pNext;
    }
    
    NameOfClass = "Data\\" + NameOfClass + ".csv";
    ifstream ifs(NameOfClass);
    if (!ifs){
        cout <<"Khong the mo file" << endl;
        return;
    }

    string num, firstname, lastname, birthday, MSSV, ID, sex;
    getline(ifs, num, ',');
    getline(ifs, firstname, ',');
    getline(ifs, lastname, ',');
    getline(ifs, sex, ',');
    getline(ifs, birthday, ',');
    getline(ifs, MSSV, ',');
    getline(ifs, ID);
    //cout << num <<' '<< firstname <<' '<<lastname<<' '<< sex <<' '<<birthday<<' '<<MSSV <<' '<< ID << endl;
    while (!ifs.eof()){
        if (tam->data.NumberOfStudent_Current == tam->data.NumberOfStudent_max){ //lop hoc con du bao nhieu slot thi se them hs vao, so con lai thi khong them vao
            cout <<"Lop da day sinh vien" << endl;
            return;
        }
        int i = tam->data.NumberOfStudent_Current++;
        getline(ifs, num, ',');
        getline(ifs, tam->data.student[i].FirstName, ',');
        getline(ifs, tam->data.student[i].LastName, ',');
        getline(ifs, tam->data.student[i].Gender, ',');
        getline(ifs, tam->data.student[i].DateOfBirth, ',');
        getline(ifs, tam->data.student[i].StudentID, ',');
        getline(ifs, tam->data.student[i].SocialID);
    }
    ifs.close();
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
    for (int i = pos; i < temp.NumberOfStudent_Current; i++){
        temp.student[i] = temp.student[i + 1];
    }
    temp.NumberOfStudent_Current--;
}

void PrintListOfStudentInClass(ClassInfo& temp){
    system("cls");
    if (temp.NumberOfStudent_Current == 0){
        cout <<"Danh sach sinh vien lop "<< temp.nameClass <<" trong" << endl;
        system("pause");
        return;
    }
    GoTo(25, 0); cout <<"Danh sach sinh vien lop " << temp.nameClass << endl;
    SetColor(14, 1);
    for (int i = 0; i <= 102; i++){
        GoTo(i, 2); cout <<' ';
    }
    GoTo(0, 2);  cout << "STT";
    GoTo(5, 2);  cout << "Ho va Ten Lot";
    GoTo(35, 2); cout << "Ten";
    GoTo(45, 2); cout << "Gioi tinh";
    GoTo(60, 2); cout << "Ngay sinh";
    GoTo(77, 2); cout << "MSSV";
    GoTo(94, 2); cout << "CCCD" <<endl;
    SetColor(7, 0);
    for (int i = 0; i <= 102; i++){
        GoTo(i, 3); cout <<' ';
    }
    for (int i = 0; i < temp.NumberOfStudent_Current; i++){
        GoTo(0, 3 + i); cout << i + 1;
        GoTo(5, 3 + i); cout << temp.student[i].FirstName;
        GoTo(35,3 + i);cout << temp.student[i].LastName;
        GoTo(48,3 + i);cout << temp.student[i].Gender;
        GoTo(60,3 + i);cout << temp.student[i].DateOfBirth;
        GoTo(75,3 + i);cout << temp.student[i].StudentID;
        GoTo(90,3 + i);cout << temp.student[i].SocialID <<endl;
        if (i == 0) TextColor(7);
    }
    int pos = 0;//Biến chỉ vị trí đang chọn ở dòng nào
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){// Đi lên
                    TextColor(7);
                    for (int i = 0; i <= 102; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName;
                    GoTo(35,3 + pos);cout << temp.student[pos].LastName;
                    GoTo(48,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(60,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(75,3 + pos);cout << temp.student[pos].StudentID;
                    GoTo(90,3 + pos);cout << temp.student[pos].SocialID <<endl;
                    if (pos == 0) pos = temp.NumberOfStudent_Current - 1;
                    else pos--;
                    SetColor(7, 0);
                    for (int i = 0; i <= 102; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName;
                    GoTo(35,3 + pos);cout << temp.student[pos].LastName;
                    GoTo(48,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(60,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(75,3 + pos);cout << temp.student[pos].StudentID;
                    GoTo(90,3 + pos);cout << temp.student[pos].SocialID <<endl;
                }
                if (c == 80){// Đi xuống
                    TextColor(7);
                    for (int i = 0; i <= 102; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName;
                    GoTo(35,3 + pos);cout << temp.student[pos].LastName;
                    GoTo(48,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(60,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(75,3 + pos);cout << temp.student[pos].StudentID;
                    GoTo(90,3 + pos);cout << temp.student[pos].SocialID <<endl;
                    if (pos == temp.NumberOfStudent_Current - 1) pos = 0;
                    else pos++;
                    SetColor(7, 0);
                    for (int i = 0; i <= 102; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos); cout << pos + 1;
                    GoTo(5, 3 + pos); cout << temp.student[pos].FirstName;
                    GoTo(35,3 + pos);cout << temp.student[pos].LastName;
                    GoTo(48,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(60,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(75,3 + pos);cout << temp.student[pos].StudentID;
                    GoTo(90,3 + pos);cout << temp.student[pos].SocialID <<endl;
                }
            }
            if (c == 27) {TextColor(7);return;}
            if (c == 8) { //backspace
                TextColor(7);
                system("cls");
                DeleteOneStudent(temp, pos);
                PrintListOfStudentInClass(temp);
                return;
            }
        }
    }
}

void MenuListOfClass(SchoolTime NienKhoa){
    system("cls");
    //extern hcmus NamHoc;
    cout <<"DANH SACH CAC LOP NAM HOC " << NienKhoa.SchoolYear << endl;
    ListOfClasses* temp = NienKhoa.HeadList;
    int NumberOfClasses = 1;

    SetColor(14, 1);
    for (int i = 0; i <= 92; i++){
        GoTo(i, 2); cout <<' ';
    }
    GoTo(0, 2);  cout << "STT";
    GoTo(10, 2); cout << "Ten Lop";
    GoTo(28, 2); cout << "Chuyen Nganh";
    GoTo(55, 2); cout << "So Luong SV";
    GoTo(70, 2); cout << "MAX_SV";
    GoTo(80, 2); cout << "Nam Nhap Hoc" << endl;

    SetColor(7, 0);
    for (int i = 0; i <= 92; i++){
        GoTo(i, 3); cout <<' ';
    }
  
    while (temp != nullptr){
        GoTo(0 , 2 + NumberOfClasses); cout << NumberOfClasses;
        GoTo(10, 2 + NumberOfClasses); cout << temp->data.nameClass;
        GoTo(25, 2 + NumberOfClasses); cout << temp->data.major;
        GoTo(59, 2 + NumberOfClasses); cout << temp->data.NumberOfStudent_Current;
        GoTo(72, 2 + NumberOfClasses); cout << temp->data.NumberOfStudent_max;
        GoTo(84, 2 + NumberOfClasses); cout << ConvertFirst(temp->data.TimeBegin) << endl;
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
                    for (int i = 0; i <= 92; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0 , 2 + dem); cout << dem;
                    GoTo(10, 2 + dem); cout << temp->data.nameClass;
                    GoTo(25, 2 + dem); cout << temp->data.major;
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_Current;
                    GoTo(72, 2 + dem); cout << temp->data.NumberOfStudent_max;
                    GoTo(84, 2 + dem); cout << ConvertFirst(temp->data.TimeBegin) << endl;
                    dem--;
                    if (dem == 0){
                        dem = NumberOfClasses;
                        temp = NienKhoa.EndList;
                    }
                    else temp = temp->pPrev;
                    SetColor(7, 0);
                    for (int i = 0; i <= 92; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0 , 2 + dem); cout << dem;
                    GoTo(10, 2 + dem); cout << temp->data.nameClass;
                    GoTo(25, 2 + dem); cout << temp->data.major;
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_Current;
                    GoTo(72, 2 + dem); cout << temp->data.NumberOfStudent_max;
                    GoTo(84, 2 + dem); cout << ConvertFirst(temp->data.TimeBegin) << endl;
                }
                if (c == 80){ // Di Xuong
                    TextColor(7);
                    for (int i = 0; i <= 92; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0 , 2 + dem); cout << dem;
                    GoTo(10, 2 + dem); cout << temp->data.nameClass;
                    GoTo(25, 2 + dem); cout << temp->data.major;
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_Current;
                    GoTo(72, 2 + dem); cout << temp->data.NumberOfStudent_max;
                    GoTo(84, 2 + dem); cout << ConvertFirst(temp->data.TimeBegin) << endl;
                    dem++;
                    if (dem > NumberOfClasses){
                        dem = 1;
                        temp = NienKhoa.HeadList;
                    }
                    else temp = temp->pNext;
                    SetColor(7, 0);
                    for (int i = 0; i <= 92; i++){
                        GoTo(i, 2 + dem); cout <<' ';
                    }
                    GoTo(0 , 2 + dem); cout << dem;
                    GoTo(10, 2 + dem); cout << temp->data.nameClass;
                    GoTo(25, 2 + dem); cout << temp->data.major;
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_Current;
                    GoTo(72, 2 + dem); cout << temp->data.NumberOfStudent_max;
                    GoTo(84, 2 + dem); cout << ConvertFirst(temp->data.TimeBegin) << endl;
                }
            }
            if (c == 13){ //Enter
                TextColor(7);
                system("cls");
                PrintListOfStudentInClass(temp->data);
                system("cls");
                ListOfClasses* tam = temp;
                int pos = dem;
                /*----------------------------------*/
                /*In lai danh sach lop*/
                NumberOfClasses = 1;
                temp = NienKhoa.HeadList;
                SetColor(14, 1);
                for (int i = 0; i <= 92; i++){
                    GoTo(i, 2); cout <<' ';
                }
                GoTo(0, 2);  cout << "STT";
                GoTo(10, 2); cout << "Ten Lop";
                GoTo(28, 2); cout << "Chuyen Nganh";
                GoTo(55, 2); cout << "So Luong SV";
                GoTo(70, 2); cout << "MAX_SV";
                GoTo(80, 2); cout << "Nam Nhap Hoc" << endl;
                
                TextColor(7);
                
                while (temp != nullptr){
                    if (temp == tam){ //quay trở lại danh sách thì dừng tại vị trí bấm vào trước đó
                        SetColor(7, 0);
                        for (int i = 0; i <= 92; i++){
                        GoTo(i, 2 + pos); cout <<' ';
                        }
                    }
                    GoTo(0 , 2 + NumberOfClasses); cout << NumberOfClasses;
                    GoTo(10, 2 + NumberOfClasses); cout << temp->data.nameClass;
                    GoTo(25, 2 + NumberOfClasses); cout << temp->data.major;
                    GoTo(59, 2 + NumberOfClasses); cout << temp->data.NumberOfStudent_Current;
                    GoTo(72, 2 + NumberOfClasses); cout << temp->data.NumberOfStudent_max;
                    GoTo(84, 2 + NumberOfClasses); cout << ConvertFirst(temp->data.TimeBegin) << endl;
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
    cout <<"Enter course ID: ";
    getline(cin, temp.CourseID);
    cout <<"Enter course name: ";
    getline(cin, temp.CourseName);
    cout <<"Enter class name: ";
    getline(cin, temp.ClassName);
    cout <<"Enter teacher name: ";
    getline(cin, temp.TeacherName);
    cout <<"Enter number of credits: ";
    cin >> temp.NumberOfCredit;
    cin.ignore();
    cout <<"Enter the maximum number of student: ";
    cin >> temp.NumberOfStudent_Max;
    cin.ignore();
    cout <<"Enter day of week (MON / TUE / WED / THU / FRI / SAT): ";
    getline(cin, temp.DayOfWeek);
    cout <<"Enter session: S1(07:30); S2(09:30); S3(13:30); S4(15:30): ";
    getline(cin, temp.session); 
    temp.student = new StudentInfo[temp.NumberOfStudent_Max + 1];
    temp.NumberOfStudent_Current = 0;
}

// AddCourseToSemester(KHTN.ptr[0].semester[1])
void AddCourseToSemester(HocKy& temp){
    ListOfCourse* node = new ListOfCourse;
    InputCourseInfo(node->data);
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
}

void PrintListOfCourseInSemester(HocKy& temp){
    system("cls");
    ListOfCourse* node = temp.HeadList;
    SetColor(14, 1);
    for (int i = 0; i <= 147; i++){
        GoTo(i, 2); cout <<' ';
    }
    GoTo(0, 2); cout << "STT";
    GoTo(5, 2); cout << "COURSE ID";
    GoTo(22, 2);cout << "COURSE NAME";
    GoTo(42, 2);cout << "CLASS NAME";
    GoTo(57, 2);cout << "TEACHER NAME";
    GoTo(80, 2);cout << "CREDITs";
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
        GoTo(44, 2 + dem);cout << node->data.ClassName;
        GoTo(57, 2 + dem);cout << node->data.TeacherName;
        GoTo(83, 2 + dem);cout << node->data.NumberOfCredit;
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
                    GoTo(44, 2 + dem);cout << node->data.ClassName;
                    GoTo(57, 2 + dem);cout << node->data.TeacherName;
                    GoTo(83, 2 + dem);cout << node->data.NumberOfCredit;
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
                    GoTo(44, 2 + dem);cout << node->data.ClassName;
                    GoTo(57, 2 + dem);cout << node->data.TeacherName;
                    GoTo(83, 2 + dem);cout << node->data.NumberOfCredit;
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
                    GoTo(44, 2 + dem);cout << node->data.ClassName;
                    GoTo(57, 2 + dem);cout << node->data.TeacherName;
                    GoTo(83, 2 + dem);cout << node->data.NumberOfCredit;
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
                    GoTo(44, 2 + dem);cout << node->data.ClassName;
                    GoTo(57, 2 + dem);cout << node->data.TeacherName;
                    GoTo(83, 2 + dem);cout << node->data.NumberOfCredit;
                    GoTo(99, 2 + dem);cout << node->data.NumberOfStudent_Current;
                    GoTo(116, 2 + dem);cout << node->data.NumberOfStudent_Max;
                    GoTo(129, 2 + dem);cout << node->data.DayOfWeek;
                    GoTo(142, 2 + dem);cout << node->data.session;
                }
            }
            if (c == 13){ //Enter
                TextColor(7);
                EditCourse(node->data); //Enter
                system("cls");
                ListOfCourse* tam = temp.HeadList;
                SetColor(14, 1);
                for (int i = 0; i <= 147; i++){
                    GoTo(i, 2); cout <<' ';
                }
                GoTo(0, 2); cout << "STT";
                GoTo(5, 2); cout << "COURSE ID";
                GoTo(22, 2);cout << "COURSE NAME";
                GoTo(42, 2);cout << "CLASS NAME";
                GoTo(57, 2);cout << "TEACHER NAME";
                GoTo(80, 2);cout << "CREDITs";
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
                    GoTo(44, 2 + dem_sub); cout << tam->data.ClassName;
                    GoTo(57, 2 + dem_sub); cout << tam->data.TeacherName;
                    GoTo(83, 2 + dem_sub); cout << tam->data.NumberOfCredit;
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
            if (c == 27) {GoTo(0, 10);return;} //ESC
        }
    }
}
void EditCourse(Course& temp){
    system("cls");
    SetColor(15, 0);
    GoTo(35, 1); cout << "|A|D|J|U|S|T| |C|O|U|R|S|E| |I|N|F|O|R|M|A|T|I|O|N|" << endl;
    // TextColor(7);
    string str[11];
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
    str[10]= "Export to CSV file  ";

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
    res[10] = "";
    
    int lens = 50; 
    //lens la bien luu do dai cua o chu

    SetColor(1, 14);
    for (int i = 0; i <= lens; i++){
        GoTo(i, 3);
        cout <<' ';
    }
    GoTo(0, 3); cout << str[0] << res[0] << endl;
    for (int i = 1; i <= 8; i++){
        GoTo(0, 3 + i);
        SetColor(14, 1);
        cout << str[i];
        TextColor(7);
        cout << res[i];
    }  
    for (int i = 9; i <= 10; i++){
        GoTo(0, 3 + i);
        cout << str[i] << res[i];
    }
    int i = 0;
    while (true) {
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ // Di len
                    GoTo(0, 3 + i); 
                    if (i != 9 && i != 10) SetColor(14, 1); 
                    else TextColor(7);
                    cout << str[i];
                    TextColor(7);
                    for (int j = 20; j <= lens; j++){
                        GoTo(j, 3 + i);
                        cout <<' ';
                    }
                    GoTo(19, 3 + i);
                    cout << res[i];
                    if (i == 0) i = 10;
                    else i--;
                    
                    if (i == 5) i--; //Bỏ qua i = 5 vì current student sẽ tự thay đổi khi thêm hoặc xóa sv
                    SetColor(1, 14);
                    for (int j = 0; j <= lens; j++){
                        GoTo(j, 3 + i);
                        cout <<' ';
                    }
                    GoTo(0, 3 + i); cout << str[i] << res[i] << endl;
                }
                if (c == 80){ //Di Xuong
                    GoTo(0, 3 + i); 
                    if (i != 9 && i != 10) SetColor(14, 1); 
                    else TextColor(7);
                    cout << str[i];
                    TextColor(7);
                    for (int j = 20; j <= lens; j++){
                        GoTo(j, 3 + i);
                        cout <<' ';
                    }
                    GoTo(19, 3 + i);
                    cout << res[i];
                    if (i == 10) i = 0;
                    else i++;
                    
                    if (i == 5) i++; //Bỏ qua i = 5 vì current student sẽ tự thay đổi khi thêm hoặc xóa sv
                    
                    SetColor(1, 14);
                    for (int j = 0; j <= lens; j++){
                        GoTo(j, 3 + i);
                        cout <<' ';
                    }
                    GoTo(0, 3 + i); cout << str[i] << res[i] << endl;
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
                    GoTo(35, 1); cout << "|A|D|J|U|S|T| |C|O|U|R|S|E| |I|N|F|O|R|M|A|T|I|O|N|" << endl;
                    SetColor(1, 14);
                    for (int j = 0; j <= lens; j++){
                        GoTo(j, 3);
                        cout <<' ';
                    }
                    GoTo(0, 3); cout << str[0] << res[0] << endl;
                    for (int i = 1; i <= 8; i++){
                        GoTo(0, 3 + i);
                        SetColor(14, 1);
                        cout << str[i];
                        TextColor(7);
                        cout << res[i];
                    }  
                    for (int i = 9; i <= 10; i++){
                        GoTo(0, 3 + i);
                        cout << str[i] << res[i];
                    }
                    i = 0;
                }
            }
            if (c == 8){ //BackSpace
                SetColor(1, 14);
                for (int j = 19; j <= lens; j++){
                    GoTo(j, 3 + i);
                    cout <<' ';
                }
                GoTo(20, 3 + i);
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
            }
            if (c == 27) {GoTo(0, 15);TextColor(7);return;} //ESC
        }
    }
    TextColor(7);
}

void DeleteCourse(HocKy& temp, ListOfCourse* node){
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
        cout <<"Nhap lop cua sinh vien do: ";
        getline(cin, CMPnameClass);
        while (DS_Lop_Head != nullptr){
            if (DS_Lop_Head->data.nameClass == CMPnameClass){kt = 0; break;}
            if (DS_Lop_Head == DS_Lop_End) break;
            DS_Lop_Head = DS_Lop_Head->pNext;
        }
        if (kt){
            TextColor(4);
            cout <<"Lop hoc khong ton tai, vui long nhap lai" << endl;
            TextColor(7);
        }
    }
    string ID = "";
    kt = 1;
    StudentInfo res;
    while (kt){
        cout <<"Nhap ma so sinh vien: ";
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
            cout << "Ma so sinh vien khong ton tai" << endl;
            TextColor(7);
        }
        else{
            for (int i = 0; i < temp.NumberOfStudent_Current; i++){
                if (ID == temp.student[i].StudentID){
                    kt = 1;
                    break;
                }
            }
            if (kt){
                TextColor(4);
                cout << "Ma so sinh vien da ton tai trong khoa hoc" << endl;
                TextColor(7);
            }
        }
    }
    cout << res.FirstName << endl;
    cout << res.LastName << endl;
    cout << res.Gender << endl;
    cout << res.DateOfBirth << endl;
    cout << res.StudentID << endl;
    cout << res.SocialID << endl;
    temp.student[temp.NumberOfStudent_Current] = res;
    TextColor(2);
    cout <<"Da them sinh vien nay vao khoa hoc" << endl;
    TextColor(7);
    system("pause");
    temp.NumberOfStudent_Current++;
}

void DeleteOneStudent(Course& temp, int pos){ //Xoa sinh vien co vi tri pos trong lop temp
    for (int i = pos; i < temp.NumberOfStudent_Current; i++){
        temp.student[i] = temp.student[i + 1];
    }
    temp.NumberOfStudent_Current--;
}

//chieu ngang khung hinh la 149 => o giua la o thu 75
void PrintListOfStudentInCourse(Course& temp){
    GoTo(120, 1); 
    TextColor(2);
    cout <<"Press f9 to add student";
    GoTo(120, 2);
    cout <<"Press f10 to export file csv";
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
                (67,3 + i);cout << temp.student[i].Midterm_mark;
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
                if (c == 67){
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
                        cout <<"Press f9 to add student";
                        GoTo(120, 2);
                        cout <<"Press f10 to export file csv";
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
                                (67,3 + i);cout << temp.student[i].Midterm_mark;
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
                if (c == 68){
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
            } 
            if (c == -32 && temp.NumberOfStudent_Current != 0){
                c = getch();
                if (c == 72){ //Di len, 80 di xuong
                    TextColor(7);
                    for (int i = 0; i <= 107; i++){
                        GoTo(i, 3 + pos); cout <<' ';
                    }
                    GoTo(0, 3 + pos);cout << pos + 1;
                    GoTo(5, 3 + pos);cout << temp.student[pos].FirstName + ' ' +temp.student[pos].LastName;
                    GoTo(28,3 + pos);cout << temp.student[pos].Gender;
                    GoTo(38,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(53,3 + pos);cout << temp.student[pos].StudentID;
                    if (temp.student[pos].Midterm_mark != -1){
                        (67,3 + pos);cout << temp.student[pos].Midterm_mark;
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
                    GoTo(30,3 + pos);cout << temp.student[pos].DateOfBirth;
                    GoTo(53,3 + pos);cout << temp.student[pos].StudentID;
                    if (temp.student[pos].Midterm_mark != -1){
                        (67,3 + pos);cout << temp.student[pos].Midterm_mark;
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
                        (67,3 + pos);cout << temp.student[pos].Midterm_mark;
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
                        (67,3 + pos);cout << temp.student[pos].Midterm_mark;
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
            if (c == 27) {GoTo(0, 15);TextColor(7);return;} //ESC
        }
    }
    system("pause");
}

void ExportFileCSV(Course temp){
    string filename = temp.CourseName + '_' + temp.ClassName + ".csv";
    ofstream ofs(filename);
    if (!ofs){
        cout << "Co loi, khong mo duoc file";
        return;
    }
    ofs << "No,Name,Gender,Date of Birth,Student ID" << endl;
    for (int i = 0; i < temp.NumberOfStudent_Current; i++){
        ofs << i + 1 << ',';
        ofs << temp.student[i].FirstName + ' ' + temp.student[i].LastName  << ',';
        ofs << temp.student[i].Gender << ',';
        ofs << temp.student[i].DateOfBirth << ',';
        ofs << temp.student[i].StudentID <<',';
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