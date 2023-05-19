#include "func.h"

void GoTo(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}
/*
0 = Black      8 = Gray
1 = Blue       9 = Light Blue
2 = Green      10 = Light Green
3 = Aqua       11 = Light Aqua
4 = Red        12 = Light Red
5 = Purple     13 = Light Purple
6 = Yellow     14 = Light Yellow
7 = White      15 = Bright White
*/
void SetColor(int background_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = background_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
// change color text
/*
0 = Black      8 = Gray
1 = Blue       9 = Light Blue
2 = Green      10 = Light Green
3 = Aqua       11 = Light Aqua
4 = Red        12 = Light Red
5 = Purple     13 = Light Purple
6 = Yellow     14 = Light Yellow
7 = White      15 = Bright White
*/
void TextColor(int color_code)//X là mã màu
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color_code);
}

void UploadAccount(){
    extern Account* SignIn;
    extern int quantity;
    ifstream input("Login.txt");
    input >> quantity;
    SignIn = new Account[quantity + 1];
    for (int i = 0; i < quantity; i++){
        input >> SignIn[i].username >> SignIn[i].password >> SignIn[i].IsStaff;
    }
    input.close();

    ifstream ifs("Information.txt");
    for (int i = 0; i < quantity; i++){
        getline(ifs, SignIn[i].name);
        ifs >> SignIn[i].birthday;
        ifs >> SignIn[i].email;
        ifs.ignore();
        getline(ifs, SignIn[i].profession);
        ifs >> SignIn[i].ID;
        ifs >> SignIn[i].contact;
        ifs.ignore();
        getline(ifs, SignIn[i].faulty);
        ifs >> SignIn[i].gender;
        if (!SignIn[i].IsStaff){
            ifs >> SignIn[i].grade;
            ifs >> SignIn[i].MSSV;
        }
        ifs.ignore();
    }
    ifs.close();
}

void DrawBox(int x, int y, int height, int width, int color){
    width++;
    height++;
    TextColor(color);
    for (int i = 0; i <= width; i++){
        GoTo(x + i, y);
        cout <<'*';
        GoTo(x + i, y + height);
        cout <<'*';
    }
    for (int i = 0; i <= height; i++){
        GoTo(x, y + i);
        cout <<'*';
        GoTo(x + width, y + i);
        cout <<'*';
    }
    TextColor(7);
}

void Login(){
    extern Account* SignIn;
    extern int quantity;
    int find = -1;
    while (true){
        GoTo(20, 1); cout <<"  ____  _             _            _     __  __                                   " << "\n";
        GoTo(20, 2); cout <<" / ___|| |_ _   _  __| | ___ _ __ | |_  |  \\/  | __ _ _ __   __ _  __ _  ___ _ __ " << "\n";
        GoTo(20, 3); cout <<" \\___ \\| __| | | |/ _` |/ _ | '_ \\| __| | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ | '__|" << "\n";
        GoTo(20, 4); cout <<"  ___) | |_| |_| | (_| |  __| | | | |_  | |  | | (_| | | | | (_| | (_| |  __| |   " << "\n";
        GoTo(20, 5); cout <<" |____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|   " << "\n";
        GoTo(20, 6); cout <<"                                                                  |___/           " << "\n";

        DrawBox(38, 10, 4, 41, 11);
        GoTo(57, 11); SetColor(5, 14);
        cout <<"LOGIN"<<endl;
        SetColor(15, 3);
        string user, pass;
        GoTo(42, 12); cout <<"Username:";
        GoTo(42, 13); cout <<"Password:";

        TextColor(7);
        GoTo(52, 12); cin >> user;
        GoTo(52, 13); cin >> pass;
            
        for (int i = 0; i < quantity; i++){
            if (SignIn[i].username == user && SignIn[i].password == pass) {
                find = i;
                break;
            }
        }
        
        if (find != -1){
            TextColor(2);
            GoTo(50, 14); cout <<"Login successfully";
        }
        else {
            TextColor(4);
            GoTo(45, 14); cout <<"Invalid username or password";
        }
        TextColor(7);
        sleep(1);
        system("cls");
        if (find != -1) break;
    }
    MenuInfo(find);
    return;
}

void Information(Account person){

    if (person.IsStaff == 1){
        DrawBox(36, 3, 9, 45, 11);
        SetColor(15, 0);
        GoTo(48, 3); cout <<"|I|N|F|O|R|M|A|T|I|O|N|" << "\n";
        
        GoTo(37, 5); SetColor(14, 8);
        cout <<"Ho va ten";
        TextColor(7); cout << ": "<< person.name;
        GoTo(37, 6); SetColor(14, 8);
        cout <<"Gioi tinh";
        TextColor(7);
        cout << ": ";
        (person.gender == 1) ? cout << "Nam" : cout<< "Nu";
        GoTo(37, 7); SetColor(14, 8);
        cout <<"Ngay sinh";
        TextColor(7); cout << ": "<< person.birthday;
        GoTo(37, 8); SetColor(14, 8);
        cout <<"Chuc vu  ";
        TextColor(7); cout << ": "<< person.profession;
        GoTo(37, 9); SetColor(14, 8);
        cout <<"Nganh    ";
        TextColor(7); cout << ": "<< person.faulty;
        GoTo(37, 10); SetColor(14, 8);
        cout <<"CCCD     ";
        TextColor(7); cout << ": "<< person.ID;
        GoTo(37, 11); SetColor(14, 8);
        cout <<"SDT      ";
        TextColor(7); cout << ": "<< person.contact;
        GoTo(37, 12); SetColor(14, 8);
        cout <<"Email    ";
        TextColor(7); cout << ": "<< person.email;  
    }
    else{
        DrawBox(36, 3, 11, 45, 11);
        SetColor(15, 0);
        GoTo(48, 3); cout <<"|I|N|F|O|R|M|A|T|I|O|N|" << "\n";
        GoTo(37, 5); SetColor(14, 8);
        cout <<"Ho va ten";
        TextColor(7); cout <<": "<< person.name;
        GoTo(37, 6); SetColor(14, 8); 
        cout <<"Gioi tinh";
        TextColor(7);
        cout <<": ";
        (person.gender == 1) ? cout << "Nam" : cout <<"Nu";
        GoTo(37, 7); SetColor(14, 8);
        cout <<"Ngay sinh";
        TextColor(7); cout <<": "<< person.birthday;
        GoTo(37, 8); SetColor(14, 8);
        cout <<"Chuc vu  ";
        TextColor(7); cout << ": "<< person.profession;
        GoTo(37, 9); SetColor(14, 8);
        cout <<"Nganh    ";
        TextColor(7); cout << ": "<< person.faulty;
        GoTo(37, 10); SetColor(14, 8);
        cout <<"Lop      ";
        TextColor(7); cout << ": "<< person.grade;
        GoTo(37, 11); SetColor(14, 8);
        cout <<"MSSV     ";
        TextColor(7); cout << ": "<< person.MSSV;
        GoTo(37, 12); SetColor(14, 8);
        cout <<"CCCD     ";
        TextColor(7); cout << ": "<< person.ID;
        GoTo(37, 13); SetColor(14, 8);
        cout <<"SDT      ";
        TextColor(7); cout << ": "<< person.contact;
        GoTo(37, 14); SetColor(14, 8);
        cout <<"Email    ";
        TextColor(7); cout << ": "<< person.email;
    }
    GoTo(0, 16);
    system("pause");
    return;
}

void ChangePassword(int pos){ //pos là vị trí tài khoản lưu trong mảng SignIn
    extern Account* SignIn;
    extern int quantity;
    system("cls");
    while (true){
        DrawBox(38, 3, 4, 41, 11);
        GoTo(53, 4); SetColor(5, 14);
        cout <<"CHANGE PASSWORD"<<endl;
        SetColor(15, 3);
        GoTo(38, 5);
        cout <<"Current password:";
        GoTo(38, 6);
        cout <<"New password    :";
        string matkhau;
        TextColor(7);
        GoTo(56, 5); cin >> matkhau;
        if (matkhau != SignIn[pos].password){
            TextColor(4);
            GoTo(47, 7); cout <<"Invalid current password";
            sleep(1);
            system("cls");
        }
        else break;
    }
    TextColor(7);
    GoTo(56, 6); cin >> SignIn[pos].password;
    TextColor(2);
    GoTo(45, 7); cout <<"Change password successfully";
    sleep(2);
    ofstream ofs("Login.txt");
    ofs << quantity <<"\n";
    for (int i = 0; i < quantity; i++)
        ofs << SignIn[i].username <<' '<< SignIn[i].password<<' '<<SignIn[i].IsStaff<<"\n";
    ofs.close();
    system("cls");
    Login();
}

void MenuInfo(int find){ //find là vị trí tài khoản lưu trong mảng SignIn
    extern Account* SignIn;
    extern int quantity;
    if (!SignIn[find].IsStaff){
        GoTo(29,1); cout <<"                                                                " << "\n";
        GoTo(29,2); cout <<" ,---.,--------.,--. ,--.,------.  ,------.,--.  ,--.,--------. " << "\n";
        GoTo(29,3); cout <<"'   .-'--.  .--'|  | |  ||  .-.  \\ |  .---'|  ,'.|  |'--.  .--' " << "\n";
        GoTo(29,4); cout <<"`.  `-.  |  |   |  | |  ||  |  \\  :|  `--, |  |' '  |   |  |    " << "\n";
        GoTo(29,5); cout <<".-'    | |  |   '  '-'  '|  '--'  /|  `---.|  | `   |   |  |    " << "\n";
        GoTo(29,6); cout <<"`-----'  `--'    `-----' `-------' `------'`--'  `--'   `--'    " << "\n";
        GoTo(29,7); cout <<"                                                                " << "\n";
    }
    else {
        GoTo(41,1); cout <<" ,---.,--------. ,---.  ,------.,------. " << "\n";
        GoTo(41,2); cout <<"'   .-'--.  .--'/  O  \\ |  .---'|  .---' " << "\n";
        GoTo(41,3); cout <<"`.  `-.  |  |  |  .-.  ||  `--, |  `--,  " << "\n";
        GoTo(41,4); cout <<".-'    | |  |  |  | |  ||  |`   |  |`    " << "\n";
        GoTo(41,5); cout <<"`-----'  `--'  `--' `--'`--'    `--'     " << "\n";
        //Goto(33,6); cout <<"                                         " << "\n";
    }


    string choice[] ={"View profile", "Change password", "Log out", "Back"};
    int lens = 4;

    DrawBox(36, 8, 9, 45, 11);
    int yn = 10;
    int stt = 0;

    SetColor(7, 0); 
    GoTo(52, yn);
    cout << choice[0] << endl;
    TextColor(7);

    for (int i = 1; i < lens; i++){
        GoTo(52, i + i + yn ); 
        cout << choice[i] << endl;
    }
 
    while (true){
        if (kbhit()){
            char c = getch();
            if (c == -32){
                c = getch();
                if (c == 72){ //Di len
                    GoTo(52, yn); TextColor(7);
                    cout << choice[stt];
                    yn -= 2;
                    stt--;
                    if (stt < 0) {
                        yn = 2 * (lens - 1) + 10;
                        stt = lens - 1;
                    }
                    GoTo(52, yn); SetColor(7, 0);
                    cout << choice[stt];
                }
                if (c == 80){ //Di xuong
                    GoTo(52, yn); TextColor(7);
                    cout << choice[stt];
                    yn += 2;
                    stt++;
                    if (stt >= lens){
                        stt = 0;
                        yn = 10;
                    } 
                    GoTo(52, yn); SetColor(7, 0);
                    cout << choice[stt];
                }
            }
            if (c == 13) {
                TextColor(7);
                system("cls");
                if (stt == 0){
                    Information(SignIn[find]);
                    system("cls");
                    DrawBox(36, 8, 9, 45, 11);
                    SetColor(7, 0); 
                    GoTo(52, yn);
                    cout << choice[0] << endl;
                    TextColor(7);

                    for (int i = 1; i < lens; i++){
                        GoTo(52, i + i + yn ); 
                        cout << choice[i] << endl;
                    }
                }
                else break;
            }
        }
        //else return;
    }
    if (stt == 1) ChangePassword(find);
    if (stt == 2) Login();
    if (stt == 3) return;
}

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

int ConvertFirst(string st){
    int value = 0;
    for (int i = 0; i < 4; i++) value = value * 10 + st[i] - 48;
    return value;
}

int ConvertLast(string st){
    int value = 0;
    for (int i = 5; i < 9; i++) value = value * 10 + st[i] - 48;
    return value;
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
                cin >> KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].number;
                cin.ignore();
                cout <<"Nhap ngay bat dau : ";
                getline(cin, KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].StartDate);
                cout <<"Nhap ngay ket thuc: ";
                getline(cin, KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].EndDate);
                cout <<"Da nhap hoc ky "<<KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1].number<<" cho nam hoc "<<temp<<endl;
                //KHTN.ptr[i].semester[KHTN.ptr[i].NumberOfSemester - 1] = KHTN.ptr[i].NumberOfSemester;
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
    node->data.NumberOfStudent_current = 0;
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
        node->data.NumberOfStudent_current = 0;
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
    if (node->data.NumberOfStudent_current == node->data.NumberOfStudent_max){
        cout <<"Lop da day sinh vien" << endl;
        return;
    }
    cout <<"Nhap thong tin sinh vien" << endl;
    int i = node->data.NumberOfStudent_current++;
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
        if (tam == temp.EndList){ // neu chay den cuoi danh sach ma khong co ten lop xuat hien thi thoat chuong trinh
            cout << "Khong ton tai lop nay trong nam hoc nay" << endl;
            return; 
        }
        tam = tam->pNext;
    }
    NameOfClass = NameOfClass + ".csv";
    ifstream ifs(NameOfClass);
    if (!ifs){
        cout <<"Khong the mo file" << endl;
        return;
    }

    string num, firstname, lastname, birthday, MSSV, ID, sex;
    getline(ifs, num, ';');
    getline(ifs, firstname, ';');
    getline(ifs, lastname, ';');
    getline(ifs, sex, ';');
    getline(ifs, birthday, ';');
    getline(ifs, MSSV, ';');
    getline(ifs, ID);
    //cout << num <<' '<< firstname <<' '<<lastname<<' '<< sex <<' '<<birthday<<' '<<MSSV <<' '<< ID << endl;
    while (!ifs.eof()){
        if (tam->data.NumberOfStudent_current == tam->data.NumberOfStudent_max){
            cout <<"Lop da day sinh vien" << endl;
            return;
        }
        int i = tam->data.NumberOfStudent_current++;
        getline(ifs, num, ';');
        getline(ifs, tam->data.student[i].FirstName, ';');
        getline(ifs, tam->data.student[i].LastName, ';');
        getline(ifs, tam->data.student[i].Gender, ';');
        getline(ifs, tam->data.student[i].DateOfBirth, ';');
        getline(ifs, tam->data.student[i].StudentID, ';');
        getline(ifs, tam->data.student[i].SocialID);
    }
    ifs.close();
}

//Chỉ áp dụng cho các lớp ở năm học hiện tại. Không áp dụng cho các năm trước
void PrintListOfStudentInClass(string NameOfClass ){
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
    for (int i = 0; i < tam->data.NumberOfStudent_current; i++){
        cout << setw(3)  << i + 1;
        cout << setw(20) << tam->data.student[i].FirstName;
        cout << setw(20) << tam->data.student[i].LastName;
        cout << setw(10) << tam->data.student[i].Gender;
        cout << setw(15) << tam->data.student[i].DateOfBirth;
        cout << setw(15) << tam->data.student[i].StudentID;
        cout << setw(20) << tam->data.student[i].SocialID <<endl;
    }
}

void PrintListOfStudentInClass(ClassInfo temp){
    if (temp.NumberOfStudent_current == 0){
        cout <<"Danh sach sinh vien lop "<< temp.nameClass <<" trong" << endl;
        return;
    }
    GoTo(25, 0); cout <<"Danh sach sinh vien lop " << temp.nameClass << endl;
    SetColor(14, 1);
    cout << setw(3)  << "STT";
    cout << setw(20) << "Ho va Ten Lot";
    cout << setw(20) << "Ten";
    cout << setw(15) << "Gioi tinh";
    cout << setw(15) << "Ngay sinh";
    cout << setw(15) << "MSSV";
    cout << setw(20) << "CCCD" <<endl;
    TextColor(7);
    for (int i = 0; i < temp.NumberOfStudent_current; i++){
        cout << setw(3)  << i + 1;
        cout << setw(20) << temp.student[i].FirstName;
        cout << setw(20) << temp.student[i].LastName;
        cout << setw(15) << temp.student[i].Gender;
        cout << setw(15) << temp.student[i].DateOfBirth;
        cout << setw(15) << temp.student[i].StudentID;
        cout << setw(20) << temp.student[i].SocialID <<endl;
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
        GoTo(i, 2 + NumberOfClasses); cout <<' ';
    }
  
    while (temp != nullptr){
        GoTo(0 , 2 + NumberOfClasses); cout << NumberOfClasses;
        GoTo(10, 2 + NumberOfClasses); cout << temp->data.nameClass;
        GoTo(25, 2 + NumberOfClasses); cout << temp->data.major;
        GoTo(59, 2 + NumberOfClasses); cout << temp->data.NumberOfStudent_current;
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
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_current;
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
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_current;
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
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_current;
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
                    GoTo(59, 2 + dem); cout << temp->data.NumberOfStudent_current;
                    GoTo(72, 2 + dem); cout << temp->data.NumberOfStudent_max;
                    GoTo(84, 2 + dem); cout << ConvertFirst(temp->data.TimeBegin) << endl;
                }
            }
            if (c == 13){
                    TextColor(7);
                    system("cls");
                    PrintListOfStudentInClass(temp->data);
                    system("pause");
                    break;
            }
            if (c == 27){
                    GoTo(0, NumberOfClasses + 5);
                    return;
            }
        }
    }
}
