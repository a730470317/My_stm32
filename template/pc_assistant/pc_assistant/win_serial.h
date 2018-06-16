#ifndef WIN_SERIALPORT_H
#define WIN_SERIALPORT_H
#ifdef _WIN32
#define ARDUINO_WAIT_TIME 1000
#define MAX_DATA_LENGTH 1024


#include "serial_service.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial_config;

class Win_serial_port
{
public:
#if _WIN32
    HANDLE m_comm;
    bool m_is_connected;
    COMSTAT m_status;
    DWORD m_errors;
    Serial_config *m_serial_config;
    DCB dcbSerialParameters ;
public:
    Win_serial_port();
    Win_serial_port(char *portName);
    ~Win_serial_port();
    void init(Serial_config config);
    void init(const char *portName);
    void clear_buffer();
    int  readSerialPort(char *buffer, unsigned int buf_size);
    bool writeSerialPort(char *buffer, unsigned int buf_size);
    bool isConnected();
#else
    Win_serial_port()=default;
#endif
};
#endif
#endif // SERIALPORT_H
