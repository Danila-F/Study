#pragma once

#ifdef LOGGERLIBRARY_EXPORTS
#define LOGGERLIBRARY_API __declspec(dllexport)
#else
#define LOGGERLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <regex>
#include <ctime>
using namespace std;

// Logger class
class LOGGERLIBRARY_API Logger
{
private:

    string m_filename;
    ofstream m_file;
    string m_format;
    regex m_reg_data;
    regex m_reg_time;
    regex m_reg_message;
    regex m_reg_prior;
    bool isfileout;

    void printFileCml(string text)
    {
        if (isfileout)
        {
            m_file << text << "\n";
        }
        else
        {
            cout << text << "\n";
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

    Logger() // ����������� ��� ������ � �������
    {
        m_format = "%data% - %%time%% - **message** - *prior*";
        m_reg_data = regex("(%data%)");
        m_reg_time = regex("(%%time%%)");
        m_reg_message = regex("(\\*\\*message\\*\\*)");
        m_reg_prior = regex("(\\*prior\\*)");
        isfileout = false;
    }

    Logger(string filename) : Logger() // ����������� ��� ������ � ����
    {
        m_filename = filename;
        m_file.open(m_filename, ios::app, _SH_DENYNO);
        isfileout = true;
    }

    ~Logger()
    {
        if (isfileout && m_file.is_open())
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

extern "C" LOGGERLIBRARY_API Logger* createMyClass();