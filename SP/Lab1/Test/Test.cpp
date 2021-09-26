#include <iostream>
#include <regex>
#include <ctime>
using namespace std;

int main()
{
    string format = "%data% - %%time%% - **message** - *prior*";
    time_t now = time(0);
    tm date_time;
    localtime_s(&date_time, &now);
    char date[20];
    strftime(date, sizeof(date), "%d.%m.%Y", &date_time);
    char time[20];
    strftime(time, sizeof(time), "%H:%M:%S", &date_time);

    regex reg_data("(%data%)");
    string m_text = regex_replace(format, reg_data, date);
    regex reg_time("(%%time%%)");
    m_text = regex_replace(m_text, reg_time, time);
    regex reg_message("(\\*\\*message\\*\\*)");
    m_text = regex_replace(m_text, reg_message, "ERROR in writing to the file!");
    regex reg_prior("(\\*prior\\*)");
    m_text = regex_replace(m_text, reg_prior, "ERROR");
    cout << m_text << "\n";
}
