
#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

enum Month{
    January = 1, February = 2, March = 3, April = 4, May = 5, June = 6,
    July = 7, August = 8, September = 9, October = 10, November = 11, December = 12
};


static string Week [7] = {"SUN", "MON", "TUS", "WED", "THU", "FRI", "SAT"};

//{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}

// amount of days from 01/01/year to some date
const int monthLength[2][12] = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
    {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
};


string MonthName[12] = {"January", "February", "March", "April", "May", "June", "July",
                        "August", "September", "October", "November", "December"};


//######################################################################################
//######################        My functions        ####################################
//######################################################################################

/*
*   Next func check is year leap or not
*/

bool IsLeapYear(int year)
{
    return(year % 4 == 0 && !(year % 100 != 0 || year % 400 == 0));
}


/*
*   Next func transform date in the num of days from(00\00\00)
*/

long int DateToDays(int day, int month, int year)
{
    long int days = year*365 + year/4 - year/100 + year/400;
    bool leap = IsLeapYear(year);

    if(leap)
    {
        days--;
    }

    return(days + monthLength[leap][month-1] + day);
}


/*
*   Next func return day of the week
*   P. S. for this func you must use monthes from 1 to 12
*   and use the var "day" in the same way
*/

int Date( int day, int month, int year )
{
    int a, y, m, R;
    a = ( 14 - month ) / 12;
    y = year - a;
    m = month + 12 * a - 2;
    R = 7000 + ( day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12 );
    return R % 7;
}


/*
*   Next func return amount of days in pass year and month
*/

int GetDaysInMonth(int month, int year)
{
    static int monthLenghts [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return monthLenghts[month-1] + (month == February && IsLeapYear(year));
}


/*
*   Next func generate the calendar
*/


int main()
{
    int sYear;//, sMonth, sDay;

    cout << "Date for start point (Year): ";
    cin >> sYear; //>> dump >> sMonth >> dump >> sDay;
    //cout << endl << s_year << dump << s_month << dump << s_day << endl;

    int fYear;//, fMonth, fDay;

    cout << "Date for finish point (Year): ";
    cin >> fYear; //>> dump >> fMonth >> dump >> fDay;
    //cout << endl << f_year << dump << f_month << dump << f_day << endl;

    cout << endl;


    char* fileName = new char[256];
    cout << "Output file: ";
    cin>>fileName;

    ofstream out(fileName);
    if(!out)
    {
        cerr << "\t Error!\n" << "Cann't open the file!\n";
        return(0);
    }

    int dayPosition = 0; // Position of current day in week

    for(int yearIterator = sYear; yearIterator <= fYear; yearIterator++)
    {
        for(int monthIterator = 1; monthIterator <= 12; monthIterator++)
        {
            out << MonthName[monthIterator-1] << "  " << yearIterator << endl;

            for(int i = 0; i < 7; i++){out << setw(4) << Week[i];}

            out << endl;

            dayPosition = Date(1, monthIterator, yearIterator);

            //cout << Week[dayPosition] << endl; // This one show you the day in week

            for(int j = 1; j <= dayPosition; j++){out << "    ";}

            out << setw(4) << 1;

            for(int dayIterator = 2; dayIterator <= GetDaysInMonth(monthIterator, yearIterator); dayIterator++)
            {
                dayPosition += 1;

                if(dayPosition > 6)
                {
                    out << endl;
                    dayPosition = 0;
                }

                out << setw(4) << dayIterator;

            }


            //Sleep(3000);
            out << endl << endl << endl;
        }
    }

    cout << "\tComplite!\n";

    delete[] fileName;
    out.close();

    return(0);
}
