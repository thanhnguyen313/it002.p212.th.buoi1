#include <iostream>
#include <cstring>
#include <string>
#include <algorithm> 
#include <iomanip>

using namespace std;

struct STUDENT
{
    string name;
    float DiemToan;
    float DiemVan;
    float DiemAV;
    float dtb;

    /*Dinh nghia toan tu << */
    friend std::ostream& operator<<(std::ostream& os, const STUDENT& student) 
    {
        os << "Ho va ten: " << student.name << "\n"
           << "Diem Toan: " << student.DiemToan << "\n"
           << "Diem Van : " << student.DiemVan << "\n"
           << "Diem Anh : " << student.DiemAV << "\n"
           << "Diem TB  : " << student.dtb << "\n";
        return os;
    }
};
struct StudenList
{
    STUDENT* student;
    int NumOfStudent;
};
bool isValidName(const string& name) /*Ham kiem tra ten hop le*/
{
    if(name.length() < 2) return false; /*Ten phai co it nhat 2 ky tu*/
    bool hasAlpha = false; /*Kiem tra xem co chu cai ko*/
    for(size_t i = 0; i < name.length(); i++)
    {
        if(isalpha(name[i])) /*Tim thay it nhat mot chu cai*/
            hasAlpha = true;
        else if(!isspace(name[i]) || !isalpha(name[i])) /*Neu khong phai chu cai hoacj khoang trang -> Khong hop le*/
            return false;
    }
    return hasAlpha;
}
void standardizeNames(string &str) /*Chuan hoa ten cua hoc sinh sao cho dung dinh dang*/
{
    int i = 0;
    /*Xoa cac khoang trang du thua do nguoi dung nhap*/
    while(i < str.length())
    {
        if(i > 0 && str[i] == '.' && str[i - 1] == ' ')
        {
            str.erase(i - 1, 1);
            i--;
        }   
        if(i > 0 && str[i] == ' ' && str[i - 1] == ' ')
        {
            str.erase(i - 1, 1);
            i--;
        }
        if(i == 0 && str[i] == ' ')
        {
            str.erase(i, 1);
            i--;
        }  
        if(i > 0 && str[i] != ' ' && str[i - 1] == '.')
        {
            str.insert(i, " ");
            i++;
        }
        else
            i++;
    }
    /*Viet hoa chu cai dau*/
    for(int i=0; i<str.length(); i++)
    {
        if(str[i]>=65 && str[i]<=90)
            str[i]+=32;
    }
    if(str[0]!=' ')
        str[0]=toupper(str[0]);
    for(int i=0; i<str.length(); i++)
    {
        if (str[i]!=' ' && str[i-1]==' ')
            str[i]=toupper(str[i]);
    }
}
void Input(STUDENT &student) /*Ham nhap du lieu cua 1 Hoc sinh*/
{
    do
    {
        cout << "\nHo va ten: ";  cin.ignore(); getline(cin, student.name); /*Nhap vao Ho va ten Hoc sinh*/
    } while (isValidName(student.name));
    /*Nhap diem Toan, Van, Anh cua Hoc sinh*/
    do
    {
        cout << "\nDiem Toan: "; cin >> student.DiemToan;
        if(student.DiemToan < 0 || student.DiemToan > 10)
            cout << "\nVui long nhap diem hop le! (Trong khoang tu 0 -> 10)";
    } while (student.DiemToan < 0 || student.DiemToan > 10); /*Sai diem thi nhap lai*/
    do
    {
        cout << "\nDiem Van: "; cin >> student.DiemVan;
        if(student.DiemVan < 0 || student.DiemVan > 10)
            cout << "\nVui long nhap diem hop le! (Trong khoang tu 0 -> 10)";
    } while (student.DiemVan < 0 || student.DiemVan > 10);
    do
    {
        cout << "\nDiem Anh: "; cin >> student.DiemAV;
        if(student.DiemAV < 0 || student.DiemAV > 10)
            cout << "\nVui long nhap diem hop le! (Trong khoang tu 0 -> 10)";
    } while (student.DiemAV < 0 || student.DiemAV > 10);
    student.dtb = (2.0*student.DiemToan + student.DiemVan + student.DiemAV)/ 4.0;
    cout << fixed << setprecision(2); /*Lam tron toi chu so thap phan thu 2*/
}
void ClassifyStudent(STUDENT student) /*Ham phan loai 1 Hoc Sinh*/
{
    if(student.dtb >= 9)
        cout << "\nHoc sinh Xuat Xac !";
    else if(student.dtb >= 8 && student.dtb < 9)
        cout << "\nHoc sinh Gioi !";
    else if(student.dtb >= 6.5 && student.dtb < 8) 
        cout << "\nHoc sinh Kha !";
    else if(student.dtb >= 5 && student.dtb < 6.5)
        cout << "\nHoc sinh Trung Binh !";
    else
        cout << "\nHoc sinh Yeu !";
}
void EnterStudentList(StudenList &List) /*Ham nhap vao danh sach Hoc sinh*/
{
    cout << "\nNhap so luong hoc sinh: "; cin >> List.NumOfStudent;
    List.student = new STUDENT[List.NumOfStudent]; /*Cap phat dong mang List.student*/
    for(int i = 0; i < List.NumOfStudent; i++)
    {
        Input(List.student[i]);
        standardizeNames(List.student[i].name);
    }

}
void findTopScore(StudenList List) /*Ham tim hoc sinh co diem trung binh cao nhat va xuat thong tin cua hoc sinh do*/
{
    STUDENT bestStudent = List.student[0]; /*Dat cho hoc sinh dau tien la hoc sinh gioi nhat*/
    for(int i = 0; i < List.NumOfStudent; i++)
    {
        if(List.student[i].dtb > bestStudent.dtb)
        {
            bestStudent = List.student[i];
        }
    }
    cout << "\nHoc sinh co diem trung binh cao nhat la " << bestStudent.name << " voi so diem la: " << bestStudent.dtb; 
    cout << "\nThong tin hoc sinh\n";
    cout << bestStudent;
}
/*Chuyen chuoi ve chu thuong*/
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
void findStudent(const StudenList &List, string keyword) /*Ham tim kiem hoc sinh theo ten*/
{
    string keyLower = toLower(keyword); /*Chuyen tu khoa tim kiem ve chu thuong*/
    bool found = false;
    /*Duyet qua danh sach hoc sinh de kiem tra*/
    for(int i = 0; i < List.NumOfStudent; i++)
    {
        if(toLower(List.student[i].name).find(keyLower) != string::npos)
        {
            cout << "\nDa tim thay hoc sinh nay!\n" << List.student[i];
            found = true; /*Danh dau da tim thay*/
        }
    }
    if(!found)
        cout << "\nKhong tim thay hoc sinh!";
}
void worstStudenInMath(StudenList List) /*Ham in danh sach hoc sinh co diem thap*/
{
    float worstPointInMath = List.student[0].DiemToan; /*Cho diem toan hoc sinh thap nhat bang diem cua hoc sinh dau danh sach*/
    for(int i = 0; i < List.NumOfStudent; i++)
    {
        /*Tim ra diem toan thap nhat trong danh sach hoc sinh*/
        if(List.student[i].DiemToan < worstPointInMath)
            worstPointInMath = List.student[i].DiemToan;
    }
    cout << "\nDiem toan thap nhat trong danh sach hoc sinh la: " << worstPointInMath;
    cout << "\nDanh sach hoc sinh co diem toan thap nhat la: \n";
    for(int i = 0; i < List.NumOfStudent; i++)
    {
        /*Duyet qua danh sach HS, neu la diem thap thi xuat ten ra man hinh*/
        if(List.student[i].DiemToan == worstPointInMath)
            cout << List.student[i].name << endl;
    }
}

bool isValidName(const string& name); /*Ham kiem tra ten hop le*/
void standardizeNames(string &str); /*Chuan hoa ten cua hoc sinh sao cho dung dinh dang*/
void Input(STUDENT &student); /*Ham nhap du lieu cua 1 Hoc sinh*/
void ClassifyStudent(STUDENT student); /*Ham phan loai 1 Hoc Sinh*/
void EnterStudentList(StudenList &List); /*Ham nhap vao danh sach Hoc sinh*/
void findTopScore(StudenList List); /*Ham tim hoc sinh co diem trung binh cao nhat va xuat thong tin cua hoc sinh do*/
void findStudent(const StudenList &List, string keyword); /*Ham tim kiem hoc sinh theo ten*/
void worstStudenInMath(StudenList List); /*Ham in danh sach hoc sinh co diem thap*/

int main()
{
    StudenList List;
    EnterStudentList(List);
    int choose;
    do
    {
        cout << "\n----------------CHUONG TRINH QUAN LY HOC SINH----------------";
        cout << "\n0. Thoat khoi chuong trinh";
        cout << "\n1. Tinh diem trung binh va phan loai hoc sinh";
        cout << "\n2. Tim kiem va xuat thong tin hoc sinh co diem trung binh cao nhat";
        cout << "\n3. Tim kiem hoc sinh theo ten";
        cout << "\n4. Xuat danh sach hoc sinh co diem toan thap nhat";
        do
        {
            cout << "\nLua chon cua ban (0 -> 4) la: "; cin >> choose;
            if(choose < 0 || choose > 4)
                cout << "\n Vui long nhap lua chon hop le !!! (0 -> 4)";
        } while (choose < 0 || choose > 4);
        switch (choose)
        {
        case 0:
            cout << "Chuong trinh dang thoat ... ";
            break;
        case 1:
            cout << "\nDiem trung binh cua cac hoc sinh la ";
            for(int i = 0; i < List.NumOfStudent; i++)
            {
                cout << endl << "\n" << List.student[i].name << ": " << List.student[i].dtb;
                ClassifyStudent(List.student[i]);
            }
            break;
        case 2:
            findTopScore(List);
            break;
        case 3:
        {
            string keyword;
            cin.ignore(); /*Loai bo ky tu thua tu \n (nhan Enter)*/
            cout << "\nNhap ten hoc sinh can tim kiem: "; getline(cin, keyword);
            findStudent(List, keyword);
            break;
        }
        case 4:
            worstStudenInMath(List);
            break;
        default:
            break;
        }
    } while (choose != 0);

    delete[] List.student;
    return 0;
}