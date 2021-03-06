#ifndef __SERIAL_SERVICE_H__
#define __SERIAL_SERVICE_H__
#include <string>
#include <iostream>
#include <fstream>
#include <QMainWindow>
#include <QSerialPort>
#include <stdlib.h>

// For Qjson
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QFile>
#include <QDate>
#include <QDateTime>

#include <thread>
#include <functional>
#include <chrono>      // for thread::sleep.
#include <mutex>
#include <exception>  

#include "../../Src/common/serial_protocal.h"
#include "../../Src/communication_id.h"
#include "color_print.h"


#ifdef _WIN32
#define USING_WIN_SERIAL 1
#include "win_serial.h"
#include <windows.h>
#define  SYSTEM_PAUSE system("pause");
class Win_serial_port;
#else
#define USING_WIN_SERIAL 0
#endif


#define SERIAL_SERVICE_VERSION              "Serial_service_v0.1"
#define SERIAL_SERVICE_DESC                 "The beta version."
#define MAX_SEND_BUFFER 10000
#define MAX_REC_BUFFER  10000

using namespace std;
//using namespace Qt;
class Serial_config
{
public:
    string m_com_name;
    int    m_buad_rate;

    Serial_config()
    {
        m_com_name = string("COM9");
        m_buad_rate = 2000000;
    }

    void display()
    {
        CONSOLE_SET_STYLE(CONSOLE_COLOR_BLUE, CONSOLE_COLOR_BLACK);
        cout << "===== Serial_config =====" << endl;
        cout << "Com name  =  " << m_com_name << endl;
        cout << "Buadrate =  " << m_buad_rate << endl;
        cout << "===== end =====" << endl;
        CONSOLE_RESET_DEFAULT;
    }

    int load_from_json(const char* file_name)
    {
        cout << "Load config form "<< file_name << endl;
        QFile file(file_name);
        QByteArray saveData;
        if (!file.open(QIODevice::ReadOnly)) 
        {
            qWarning("Couldn't open save file.");
        }

        if (file.isOpen())
        {
            saveData = file.readAll();
            file.close();
        }
        else
        {
            return 0;
        }

        // you can loop k higher to see more color 
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(saveData, &jsonError);
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) 
        {
            QJsonObject obj = doucment.object();
            m_com_name = obj.take("COM").toString().toStdString();
            m_buad_rate = obj.take("BuadRate").toInt();
            display();
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int save_to_json(const char * file_name)
    {
        cout << "Save config to " << file_name << endl;
        QFile file(file_name);

        if (!file.open(QIODevice::WriteOnly)) 
        {
            qWarning("Couldn't open save file.");
            return false;
        }

        QJsonObject gameObject;
        gameObject.insert("COM", QString(m_com_name.c_str()));
        gameObject.insert("BuadRate", m_buad_rate);
        QJsonDocument saveDoc(gameObject);
        file.write(saveDoc.toJson());
        file.close(); 
    }

};

struct Serial_packet
{
    enum Serial_direction
    {
        e_direction_unset = 0,
        e_direction_in = 1,
        e_direction_out = -1,
    };
    int data_length;
    int packet_length;
    int id;
    Serial_direction direction;

    char data[1024];

    Serial_packet()
    {
        //data = new char[1024];
        data_length = 0;
        packet_length = 0;
        id = 0;
        direction = e_direction_unset;
    }
    ~Serial_packet()
    {
        //delete data;
    }
    void display()
    {
        CONSOLE_SET_STYLE(CONSOLE_COLOR_YELLOW, CONSOLE_COLOR_BLACK);
        switch (direction)
        {
        case e_direction_unset:break;
        case e_direction_in : printf("==> "); break;
        case e_direction_out: printf("<== "); break;
        };
        printf("id=%d, size=%d, ", id, data_length);
        for (int i = 0; i < data_length; i++)
        {
            printf("%d, ", data[i]);
        }
        printf("\r\n");
        CONSOLE_RESET_DEFAULT;
    }

};

class Protocal_to_mcu
{
public:
    int  m_busy = 0;
    char m_send_buffer[MAX_SEND_BUFFER];
    char m_rec_buffer[MAX_REC_BUFFER];
    int m_current_rec_index = 0;;
    std::mutex m_mutex;
    QSerialPort * m_serial;
#if _WIN32
    Win_serial_port *m_win_serial;
    void init(Win_serial_port *serial);
#endif
    Protocal_to_mcu();
    ~Protocal_to_mcu();
    void display(int count,int direction=1 ); // direction =1 out, =0 in;
    void init(QSerialPort * serial);
    void send_packet(Serial_packet & packet);
    void receive_packet(Serial_packet packet);
public:

private:
};

typedef void(*service_callback)(Serial_packet serial_packet);

class Serial_service
{
public:
    std::mutex      m_mutex_serial_mutex;
    QSerialPort     m_serial;
#if _WIN32
    Win_serial_port *m_win_serial;
#endif
    std::string     m_serial_name;
    Serial_config   m_serial_config;
    std::thread     m_thread;
    std::thread     *m_thread_ptr=NULL;
    int             m_rec_frequency = 100;   //rec frequency  = 50hz
    Protocal_to_mcu m_packet_mcu;
    ofstream        m_logger_ofs;
public:
    Serial_service() = default;
    ~Serial_service()
    {
        delete m_thread_ptr;
    };
    virtual void on_serial_callback(Serial_packet packet)
    {
        cout << "You receive serial packet, but you do not inherit " << __FUNCTION__ << " in  your class, please check this." << endl;
    };

    virtual void on_serial_error_happen(){};

    void send_packet(Serial_packet packet);

    void init_serial();

    void service();

    void print_serial_service_version();
};

#endif