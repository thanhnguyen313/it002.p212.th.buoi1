#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

void standardizeNames(string &str); // Chuan hoa lai ten dia diem: hO cHI mINh -> Ho Chi Minh
struct MONTH
{
    int year;
    int month;
    int getDays() const
    {
        switch (month)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            if(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                return 29;
            else
                return 28;
        default:
            return 0;
        }
    }
};
struct DATE //Xu ly dinh dang ngay thang nam, kiem tra ngay co ton tai -> Dang ki chuyen bay
{
    int day;
    MONTH month;

    friend istream& operator>>(istream& is, DATE& date) 
    {
        is >> date.day >> date.month.month >> date.month.year;
        return is;
    }
    friend ostream& operator<<(ostream& os, const DATE& date) 
    {
        os << date.day << "/" << date.month.month << "/" << date.month.year;
        return os;
    }
    bool operator>(const DATE &other) const 
    {
        if (month.year != other.month.year) 
            return month.year > other.month.year;
        if (month.month != other.month.month) 
            return month.month > other.month.month;
        return day > other.day;
    }
    bool operator==(const DATE &other) const 
    {      
        return (day == other.day && month.month == other.month.month && month.year == other.month.year);
    }      
    DATE& operator=(const DATE& other)
    {
        if (this != &other) 
        {
            day = other.day;
            month = other.month; 
        }
        return *this;
    }

    bool checkDays(const DATE &date)
    {
        if(date.day > date.month.getDays() || date.day < 1 || date.month.month < 1 || date.month.month > 12)
            return false;
        return true;
    }
    void Input(DATE &date)
    {
        do
        {
        cin >> date;
        if(!checkDays(date))
        {
            cout << "Vui long nhap ngay thang nam hop le !\n";
            cout << endl;
            cout << "Ngay bay (ngay thang nam): ";
        }
        } while (!checkDays(date));
    }
};
struct TIME //Xu ly chuan dinh dang thoi gian 
{
    int Hour;
    int Minutes;
    int Second;

    friend istream& operator>>(istream& is, TIME &time) {
        is >> time.Hour >> time.Minutes >> time.Second;
        return is;
    }
    friend ostream& operator<<(ostream& os, const TIME &time) {
        os << time.Hour << " Gio " << time.Minutes << " Phut " << time.Second << " Giay ";
        return os;
    }
    bool operator>(const TIME &other) const 
    {
        if (Hour != other.Hour) 
            return Hour > other.Hour;
        if (Minutes != other.Minutes) 
            return Minutes > other.Minutes;
        return Second > other.Second;
    }
    bool CheckTime(const TIME &time)
    {
        if(time.Hour > 23 || time.Hour < 0 || time.Minutes > 59 || time.Minutes < 0 || time.Second > 59 || time.Second < 0)
            return false;
        return true;
    }
    void Input(TIME &time)
    {
        do
        {
            cin >> time;
            if(!CheckTime(time))
            {
                cout << "Vui long nhap thoi gian hop le!\n";
                cout << endl;
                cout << "Gio bay (gio phut giay): ";
            }
        } while (!CheckTime(time));
        
    }
};
struct Flight 
{
    string flightCode;        // Ma chuyen bay
    DATE departureDate;     // Ngay bay
    TIME departureTime;     // Gio bay
    string departureLocation; // Noi di
    string arrivalLocation;   // Noi den
    // Constructor mac dinh -> Tranh xung dot khi dung Flight newFlight;
    Flight() : flightCode(""), departureDate(), departureTime(), departureLocation(""), arrivalLocation("") {}
    // Constructor co tham so -> Ho tro tao danh sach mac dinh;
    Flight(string code, DATE d, TIME t, string dep, string des)
        : flightCode(code), departureDate(d), departureTime(t), departureLocation(dep), arrivalLocation(des) {}

    bool operator>(const Flight &other) const //Toan tu so sanh lich trinh cac chuyen bay
    {
        if (departureDate > other.departureDate) 
            return true;
        if (departureDate == other.departureDate) // Cung ngay thi so sanh thoi gian 
            return departureTime > other.departureTime;
        return false;
    }
    void Input() 
    {
        cout << "\nMa chuyen bay: "; cin.ignore(); getline(cin, flightCode);
        cout << "Ngay bay (ngay thang nam): "; departureDate.Input(departureDate); 
        cout << "Gio bay (gio phut giay): "; departureTime.Input(departureTime);
        cout << "Noi di: "; cin.ignore(); getline(cin, departureLocation); standardizeNames(departureLocation);
        cout << "Noi den: "; getline(cin, arrivalLocation); standardizeNames(arrivalLocation);
    }

    void Display() const
    {
        cout << "\n===================================";
        cout << "\nMa chuyen bay: " << flightCode;
        cout << "\nNgay bay: "      << departureDate;
        cout << "\nGio bay: "       << departureTime;
        cout << "\nNoi di: "        << departureLocation;
        cout << "\nNoi den: "       << arrivalLocation;
        cout << "\n===================================";
    }
};
struct FlightList //Quan ly danh sach chuyen bay
{
    vector<Flight> flights; //Chua cac chuyen bay

    FlightList()
    {
        flights.push_back(Flight("VN123", {25, {2025, 3}}, {14, 30, 0}, "Hanoi", "Ho Chi Minh"));
        flights.push_back(Flight("VN456", {1, {2025, 12}}, {8, 15, 0}, "Da Nang", "Ho Chi Minh"));
        flights.push_back(Flight("VN789", {1, {2025, 5}}, {16, 45, 0}, "Hue", "Ha Noi"));
        flights.push_back(Flight("VN457", {1, {2025, 12}}, {9, 15, 0}, "Da Nang", "Ho Chi Minh"));
        flights.push_back(Flight("VN788", {5, {2025, 5}}, {16, 45, 0}, "Hue", "Ha Noi"));
    }

    void AddFlight() // Them chuyen bay vao danh sach
    {
        Flight newFlight;
        newFlight.Input();
        flights.push_back(newFlight);  
        cout << "\nChuyen bay da duoc them thanh cong!\n";
    }

    void DisplayFlights() const //Xuat danh sach cac chuyen bay ra
    {
        if (flights.empty()) 
        {
            cout << "\nDanh sach chuyen bay dang rong!";
            return;
        }
        cout << "\nDANH SACH CAC CHUYEN BAY\n";
        for (const auto& flight : flights) //Duyet qua tung chuyen bay roi in ra
        {
            flight.Display();
        }
    }
};
struct Account 
{
    string userName;
    string passWord;

    void Input()
    {
        cin.ignore(); 
        cout << "\nTen tai khoan: "; getline(cin, userName);
        cout << "Mat khau : "; getline(cin, passWord);
    }

    void Checking(const Account account, const Account input, bool &accountPermissons) const
    {   
        if(account.userName == input.userName && account.passWord == input.passWord)
        {
            cout << "\nDang nhap thanh cong vao tai khoan " << account.userName;
            accountPermissons = true;
        }
    }
};
void bubbleSort(FlightList &List);
void findFlight(const FlightList &List, string keyword);
void adminManagementProgram(FlightList &List);
void userProgram(FlightList &List);

/*==================================================================================
========================================MAIN========================================*/

int main()
{
    int chooseAccount;
    FlightList List;
    do
    {
        cout << "\n----------CHUONG TRINH DANG KY & QUAN LY CHUYEN BAY----------";
        cout << "\nTruy cap vao?";
        cout << "\n0. admin";
        cout << "\n1. user";
        cout << "\n2. Thoat chuong trinh";
        cout << "\nTai khoan: "; cin >> chooseAccount;
    } while (chooseAccount < 0 || chooseAccount > 2);
    Account account;
    bool accountPermissons = false;
    switch (chooseAccount)
    {
    case 0:
    {
        //Dang nhap tai khoan admin 
        Account accountAdmin = {"admin", "admin@123"}; //Tai khoan admin quan ly cac chuyen bay
        do
        {
            account.Input();
            account.Checking(accountAdmin, account, accountPermissons);
            if(!accountPermissons)
                cout << "\nTai khoan hoac Mat khau khong dung! Vui long nhap lai!";
        } while (!accountPermissons);
        cout << endl;
        adminManagementProgram(List);
        break;
    }
    case 1:
    {
        //Dang nhap tai khoan user
        Account accountUser = {"user", "user@123"}; //Tai khoan user tra cuu va dang ki chuyen bay co san
        do
        {
            account.Input();
            account.Checking(accountUser, account, accountPermissons);
            if(!accountPermissons)
                cout << "\nTai khoan hoac Mat khau khong dung! Vui long nhap lai!";
        } while (!accountPermissons);
        cout << endl;
        userProgram(List);
        break;
        break;
    }
    case 2:
        cout << "\nChuong trinh dang thoat ... ";
        break;
    default:
        break;
    }

    return 0;
}

void adminManagementProgram(FlightList &List)
{
    do
    {
        int choose;
        do
        {
            cout << "\n----------CHUONG TRINH QUAN LY CHUYEN BAY CUA ADMIN----------";
            cout << "\n0. Them chuyen bay";
            cout << "\n1. Sap xep cac chuyen bay";
            cout << "\n2. Thoat chuong trinh Admin";
            cout << "\nChon chuong trinh (0 -> 2): "; cin >> choose;
            if(choose < 0 || choose > 2)
                cout << "Vui long chon chuong trinh hop le! (0 -> 2)";
        } while (choose < 0 || choose > 2);
        switch (choose)
        {
        case 0:
        {
            cout << "----------THEM CHUYEN BAY----------";
            List.AddFlight();
            int in;
            cout << "\nIn danh sach chuyen bay?";
            cout << "\n0. Khong";
            cout << "\n1. Co";
            cout << "\nLua chon: ";
            cin >> in;
            if(in)
                List.DisplayFlights();
            break;
        }
        case 1:
            cout << "----------LICH TRINH CAC CHUYEN BAY----------";
            bubbleSort(List);
            List.DisplayFlights();
            break;
        case 2:
            cout << "\nChuong trinh dang thoat ...";
            return;
        default:
            break;
        }
    } while (true);
    
}
void userProgram(FlightList &List)
{
    do
    {
        int choose;
        do
        {
            cout << "\n----------CHUONG TRINH TRA CUU CHUYEN BAY----------";
            cout << "\n0. Tim kiem chuyen bay";
            cout << "\n1. Danh sach chuyen bay";
            cout << "\n2. Dem so chuyen bay trong ngay";
            cout << "\n3. Dem so chuyen bay cung tuyen";
            cout << "\n4. Thoat chuong trinh";
            cout << "\nChon chuong trinh (0 -> 4): "; cin >> choose;
            if(choose < 0 || choose > 4)
                cout << "Vui long chon chuong trinh hop le! (0 -> 4)";
        } while (choose < 0 || choose > 4);
        switch (choose)
        {
            case 0:
            {
                cout << "\n----------TIM KIEM CHUYEN BAY  ----------";
                cout << "\nNhap ma chuyen bay can tim: "; string code; cin.ignore(); getline(cin, code);
                findFlight(List, code);
                break;
            }
            case 1:
                cout << "\n----------DANH SACH CAC CHUYEN BAY----------";
                bubbleSort(List);
                List.DisplayFlights();
                break;
            case 2:
            {
                cout << "\n----------CAC CHUYEN BAY CUNG THOI GIAN----------";
                DATE date;
                string place;
                cout << "\nNhap ngay thang nam can tim chuyen bay: "; cin >> date;
                cout << "\nNhap noi chuyen bay khoi hanh: "; cin.ignore(); getline(cin, place);
                standardizeNames(place); //Chuan hoa dia diem -> Phong truong hop nguoi dung nhap ko dung dinh dang chuan
                /*Duyet qua danh sach chuyen bay de kiem tra*/
                int n = List.flights.size();
                int count = 0;
                for(int i = 0; i < n; i++)
                {
                    if(List.flights[i].departureDate == date && List.flights[i].departureLocation == place)
                        count++;
                }
                cout << "Co " << count << " chuyen bay khoi hanh tu " << place << " vao ngay " << date;
                cout << "\nCac chuyen bay khoi hanh tu " << place << " vao ngay " << date << endl;
                for(int i = 0; i < n; i++)
                {
                    // Trung ngay thi xuat ra
                    if(List.flights[i].departureDate == date && List.flights[i].departureLocation == place)
                        List.flights[i].Display();
                }
                break;
            }
            case 3:
            {
                cout << "\n----------CAC CHUYEN BAY CUNG TUYEN----------";
                string place, arrival;
                cout << "\nNhap noi chuyen bay khoi hanh: "; cin.ignore(); getline(cin, place);
                cout << "\nNhap noi chuyen bay ha canh: "; getline(cin, arrival);
                standardizeNames(place); //Chuan hoa dia diem -> Phong truong hop nguoi dung nhap ko dung dinh dang chuan
                standardizeNames(arrival);
                /*Duyet qua danh sach chuyen bay de kiem tra*/
                int n = List.flights.size();
                int count = 0;
                for(int i = 0; i < n; i++)
                {
                    if(List.flights[i].arrivalLocation == arrival && List.flights[i].departureLocation == place)
                        count++;
                }
                cout << "Co " << count << " chuyen bay khoi hanh tu " << place << " ha canh o " << arrival;
                cout << "\nCac chuyen bay khoi hanh tu " << place << " ha canh o " << arrival << endl;
                for(int i = 0; i < n; i++)
                {
                    // Trung tuyen thi xuat ra
                    if(List.flights[i].arrivalLocation == arrival&& List.flights[i].departureLocation == place)
                        List.flights[i].Display();
                }
                break;
            }   
            case 4:
                cout << "\nChuong trinh dang thoat ...";
                return;
            default:
                break;
        }
    } while (true);
}
void standardizeNames(string &str) /*Chuan hoa ten cua dia diem de in ra man hinh cho dep */
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
void bubbleSort(FlightList &List) //bubbleSort cho lich trinh cac chuyen bay
{
    int n = List.flights.size();
    for (int i = 0; i < n - 1; i++) 
    {
        bool finished = false;
        for (int j = 0; j < n - i - 1; j++) 
        {
            // So sanh ngay vaf gio cua chuyen bay, cung ngay -> so sanh den gio cua chuyen bay
            if (List.flights[j].departureDate > List.flights[j + 1].departureDate || (List.flights[j].departureDate == List.flights[j + 1].departureDate && List.flights[j].departureTime > List.flights[j + 1].departureTime)) 
            {
                swap(List.flights[j], List.flights[j + 1]); 
                finished = true;
            }
        }
        if (!finished) break; // Day da sap xep xong thi ko can lap tiep nua
    }
}
void findFlight(const FlightList &List, string keyword) /*Ham tim kiem chuyen bay theo ma*/
{
    bool found = false;
    int n = List.flights.size();
    /*Duyet qua danh sach chuyen bay de kiem tra*/
    for(int i = 0; i < n; i++)
    {
        if(List.flights[i].flightCode.find(keyword) != string::npos)
        {
            cout << "\nDa tim thay chuyen bay nay!\n";
            List.flights[i].Display();
            found = true; /*Danh dau da tim thay*/
        }
    }
    if(!found)
        cout << "\nKhong tim thay chuyen bay nay!";
}
