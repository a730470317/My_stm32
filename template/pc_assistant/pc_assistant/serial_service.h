#ifndef __SERIAL_SERVICE_H__
#define __SERIAL_SERVICE_H__
#include <string>
#include <iostream>
#include <fstream>
#include <QSerialPort>

// For Qjson
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QFile>

#include <thread>
#include <functional>
#include <chrono>      // for thread::sleep.
#include <mutex>
#include "../../Src/common/serial_protocal.h"

#if _WIN32
#include <windows.h>
#define  SYSTEM_PAUSE system("pause");
#endif

#define SERIAL_SERVICE_VERSION              "Serial_service_v0.1"
#define SERIAL_SERVICE_DESC                 "The beta version."
#define MAX_SEND_BUFFER 10000
#define MAX_REC_BUFFER 10000

using namespace std;
using namespace Qt;
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

        //qDebug() << saveData << endl;

        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(saveData, &jsonError);  // 转化为 JSON 文档
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

struct Protocal_packet
{
    int data_length;
    int packet_length;
    int id;
    vector<char>	data;

    Protocal_packet()
    {
        data_length = 0;
        packet_length = 0;
        id = 0;
    }

    void display()
    {
        for (int i = 0; i < data.size(); i++)
        {
            printf("%d, ", data[i]);
        }
        printf("\r\n");
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


    Protocal_to_mcu();
    ~Protocal_to_mcu();

    void init(QSerialPort * serial);
    void send_packet(Protocal_packet & packet);
    void receive_packet(Protocal_packet packet);
public:

private:
};

class Serial_service
{

public:
    QSerialPort     m_serial;
    std::string     m_serial_name;
    Serial_config   m_serial_config;
    std::thread     m_thread;
    std::thread     *m_thread_ptr=NULL;
    Protocal_to_mcu m_packet_mcu;
public:

    void open_serial()
    {
        m_serial_config.load_from_json("serial_config.json");
        m_serial_config.save_to_json("saerial_config.json2");
        m_serial_config.display();

        m_serial.setPortName(m_serial_config.m_com_name.c_str());
        m_serial.setBaudRate(m_serial_config.m_buad_rate);
        m_serial.open(QIODevice::ReadWrite);
        m_serial.clear(QSerialPort::Direction::AllDirections);
        m_serial.setReadBufferSize(1000000);
        
        if (m_serial.isOpen())
        {
            cout << "Open serial success!!\n" << endl;
            cout << "Com = " << m_serial_config.m_com_name << endl; 
            cout << "BuadRate  = " << m_serial_config.m_buad_rate << endl;
        }
        else
        {
            cout << "Open serial fail, please check!!!" << endl;;
        }
        return;
        if (m_thread_ptr == NULL)
        {
            m_thread_ptr = new std::thread(&Serial_service::service, this);
        }
        //m_thread = std::thread(&Serial_service::service, this);
        //m_thread->detach();
    }

    void service()
    {
        QByteArray serial_data;
        char packet_data[MAX_REC_BUFFER];
        Protocal_packet packet;
        int rec_buffer_count = 0;
        while (1)
        {
            //usleep(1.0e3);
            //Sleep(100);
            //cout << __FUNCTION__ << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            if (m_serial.isOpen())
            {
                serial_data.clear();
                serial_data = m_serial.readAll();
                m_serial.clear(QSerialPort::Direction::Input);
                //cout << "----- " << serial_data.size()  << " ----- "<< endl;
                for (int i = 0; i < serial_data.size();i++)
                {
                    //printf("%x ", serial_data[i] & 0xff );
                    if (m_packet_mcu.m_current_rec_index > MAX_REC_BUFFER)
                    {
                        m_packet_mcu.m_current_rec_index = 0;
                    }
                    if (onRec(serial_data[i], m_packet_mcu.m_rec_buffer, &m_packet_mcu.m_current_rec_index, &packet.id, &packet.data_length, packet_data))
                    {
                        rec_buffer_count++;
                        printf("--- Rec data %d --- \r\n", rec_buffer_count);
                        cout << "Index =  " << m_packet_mcu.m_current_rec_index << endl;
                        cout << "packet id = " << packet.id << endl;
                        cout << "data size = " << packet.data_length << endl;
                        if (packet.id == 0x10)
                        {
                            float f_data[2];
                            memcpy((char*)f_data, packet_data, sizeof(float));
                            memcpy((char*)&f_data[1], packet_data + sizeof(float), sizeof(float));
                            printf("%f, %f\r\n", f_data[0], f_data[1]);
                        }
                    }
                }

            }
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