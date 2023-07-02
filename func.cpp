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
    ifstream input("Data\\Login.txt");
    input >> quantity;
    SignIn = new Account[quantity + 1];
    for (int i = 0; i < quantity; i++){
        input >> SignIn[i].username >> SignIn[i].password >> SignIn[i].IsStaff;
    }
    input.close();

    ifstream ifs("Data\\Information.txt");
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
    ofstream ofs("Data\\Login.txt");
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

