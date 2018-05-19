#ifndef __SERIAL_SERVICE_H__
#define __SERIAL_SERVICE_H__
#include <string>
#include <iostream>
#include <fstream>
#include <QSerialPort>

#define SERIAL_SERVICE_VERSION              "Serial_service_v0.1"
#define SERIAL_SERVICE_DESC                 "The beta version."
using namespace std;

struct Serial_config
{
    string m_com_name;
    int    m_buad_rate;
    void display()
    {
        cout << "===== Serial_config =====" << endl;
        cout << "Com name  =  " << m_com_name << endl;
        cout << "Buadrate =  " << m_buad_rate << endl;
        cout << "===== end =====" << endl;
    }
};

class Serial_service
{

public:
    QSerialPort m_serial;
    std::string m_serial_name;
    Serial_config m_serial_config;
public:

    void open_serial()
    {
        ifstream ifs;
        ifs.open("serial.config");
        if (ifs.is_open())
        {
            ifs >> m_serial_config.m_com_name;
            ifs >> m_serial_config.m_buad_rate;
        }
        else
        {
            m_serial_config.m_com_name = "COM9";
            m_serial_config.m_buad_rate = 2000000;
        }
        m_serial_config.display();

        m_serial.setPortName(m_serial_config.m_com_name.c_str());
        m_serial.setBaudRate(m_serial_config.m_buad_rate);
        m_serial.open(QIODevice::ReadWrite);
        
        if (m_serial.isOpen())
        {
            cout << "Open serial success!!\n" << endl;
            cout << "Com = " << m_serial_config.m_com_name << endl; 
            cout << "BuadRate  = " << m_serial_config.m_buad_rate;
        }
        else
        {
            cout << "Open serial fail, please check!!!" << endl;;
        }
    }

    void print_serial_service_version()
    {
        cout << "===== SERIAL_SERVICE_VERSION =====" << endl;
        cout << "Version:       " << SERIAL_SERVICE_VERSION << endl;
        cout << "Version desc:  " << SERIAL_SERVICE_DESC << endl;
        cout << "Build date is: " << __DATE__ << "  " << __TIME__ << endl;
        cout << "===== End =====" << endl;
    }

    virtual void slot_on_serial_timeout() = 0;
    virtual void slot_on_packet_timeout() = 0;

};

#endif