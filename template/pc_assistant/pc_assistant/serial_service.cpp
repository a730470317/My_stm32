#include "serial_service.h"
Protocal_to_mcu::Protocal_to_mcu()
{
    //InitializeCriticalSection(&m_cs_lock);
}



Protocal_to_mcu::~Protocal_to_mcu()
{
}

void Protocal_to_mcu::init(QSerialPort * serial)
{
    m_serial = serial;
}

void Protocal_to_mcu::send_packet(Serial_packet & packet)
{
    m_busy = 1;
    //Protocol_auto_lock auto_lock(m_cs_lock);
    std::unique_lock<mutex> lock(m_mutex);
    //packet.data_length = packet.packet_length;
    char *send_data = (char*)malloc(packet.data_length*sizeof(char));
    for (int i = 0; i < packet.data_length; i++)
    {
        send_data[i] = packet.data[i];
        //cout << (int)send_data[i] << endl;
    }

    make_packet(send_data, m_send_buffer, packet.id, packet.data_length, &packet.packet_length);
    for (int i = 0; i < packet.packet_length; i++)
    {
        m_serial->putChar(m_send_buffer[i]);
    }

    m_serial->flush();
    m_serial->waitForBytesWritten(1);
    m_busy = 0;
}

void Protocal_to_mcu::receive_packet(Serial_packet packet)
{
}