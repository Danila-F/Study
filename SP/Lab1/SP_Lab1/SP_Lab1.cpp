#include <iostream>
#include <fstream>
#include <regex>
#include <ctime>
using namespace std;

class Logger
{
private:

    string m_filename;
    ofstream m_file;
    string m_format;
    regex m_reg_data;
    regex m_reg_time;
    regex m_reg_message;
    regex m_reg_prior;

    void printFileCml(string text)
    {
        if (m_filename == "")
        {
            cout << text << "\n";
        }
        else
        {
            m_file << text << "\n";
        }
    }

    string formatting(string message, string prior)
    {
        time_t now = time(0);
        tm date_time;
        localtime_s(&date_time, &now);
        char date[20];
        strftime(date, sizeof(date), "%d.%m.%Y", &date_time);
        char time[20];
        strftime(time, sizeof(time), "%H:%M:%S", &date_time);

        string text = regex_replace(m_format, m_reg_data, date);
        text = regex_replace(text, m_reg_time, time);
        text = regex_replace(text, m_reg_message, message);
        text = regex_replace(text, m_reg_prior, prior);
        return text;
    }

public:

    Logger() // Конструктор для вывода в консоль
    {
        m_format = "%data% - %%time%% - **message** - *prior*";
        m_reg_data = regex("(%data%)");
        m_reg_time = regex("(%%time%%)");
        m_reg_message = regex("(\\*\\*message\\*\\*)");
        m_reg_prior = regex("(\\*prior\\*)");
    }

    Logger(string filename): Logger() // Конструктор для вывода в файл
    {
        m_filename = filename;
        m_file.open(m_filename, ios::app);
    }

    ~Logger()
    {
        m_file.close();
    }

    void setFormat(string format)
    {
        m_format = format;
    }

    void printError(string text)
    {
        printFileCml(formatting(text, "ERROR"));
    }

    void printDebug(string text)
    {
        printFileCml(formatting(text, "DEBUG"));
    }

    void printTrace(string text)
    {
        printFileCml(formatting(text, "TRACE"));
    }
};

int main()
{
    Logger logger1;
    logger1.setFormat("Date and time: %data% / %%time%%      Message: **message**      Priority type: *prior*");
    logger1.printError("ERROR with opening file!");
    logger1.printTrace("Don't worry, be happy!");

    Logger logger2("Log_file.txt");
    logger2.printTrace("Everything is GOOD!");

    logger2.setFormat("Message: **message**      %%time%%      Priority type: *prior*      %%time%%      ");
    logger2.printDebug("Calling function \"adding\".");

    system("pause");
    return 0;
}
