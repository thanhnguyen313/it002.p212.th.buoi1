#include <iostream>

using namespace std;

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

struct DATE
{
    int day;
    MONTH month;

    void addDays(int n)
    {
        day += n;
        while (day > month.getDays())
        {
            day -= month.getDays();
            month.month++;
            if(month.month > 12)
            {
                month.month = 1;
                month.year++;
            }
        }
    }
    void subtractDays(int n)
    {
        day -= n;
        while (day < 1)
        {
            month.month--;
            if(month.month < 1)
            {
                month.month = 12;
                month.year--;
            }
            day += month.getDays();
        }
        
    }

    friend istream& operator>>(istream& is, DATE& date) {
        is >> date.day >> date.month.month >> date.month.year;
        return is;
    }
    friend ostream& operator<<(ostream& os, const DATE& date) {
        os << date.day << "/" << date.month.month << "/" << date.month.year;
        return os;
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
};


bool checkDays(const DATE &date)
{
    if(date.day > date.month.getDays() || date.day < 1 || date.month.month < 1 || date.month.month > 12)
        return false;
    return true;
}

int theDayOfYear(DATE &date)
{
    int totalDays = 0;
    MONTH temp = {date.month.year, 1};
    for(int m = 1; m < date.month.month; m++)
    {
        temp.month = m;
        totalDays += temp.getDays();
    }
    totalDays += date.day;
    return totalDays;
}

void Input(DATE &date)
{
    do
    {
        cout << "Nhap ngay thang nam (cach nhau 1 khoang trang): ";
        cin >> date;
        if(!checkDays(date))
        {
            cout << "Vui long nhap ngay thang nam hop le !\n";
            cout << endl;
        }
    } while (!checkDays(date));
}
int main()
{
    DATE date;
    Input(date);
    DATE theDayBefore = date;
    DATE theDayAfter = date;
    cout << "Ngay ban nhap la: ";
    cout << date; cout << endl;
    cout << "Ngay truoc do la: ";
    theDayBefore.subtractDays(1);
    cout << theDayBefore; cout << endl;
    cout << "Ngay sau do la: ";
    theDayAfter.addDays(1); 
    cout << theDayAfter; cout << endl;
    cout << date << " la ngay thu: " << theDayOfYear(date) << " trong nam " << date.month.year;
} 