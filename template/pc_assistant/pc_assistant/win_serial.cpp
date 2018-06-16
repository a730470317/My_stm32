#include "win_serial.h"
#include <iostream>
#ifdef _WIN32
using namespace std;
void Win_serial_port::clear_buffer()
{
    PurgeComm(this->m_comm, PURGE_RXCLEAR | PURGE_TXCLEAR);
}

Win_serial_port::Win_serial_port()
{
    dcbSerialParameters.BaudRate = 2000000;
    dcbSerialParameters.ByteSize = 8;
    dcbSerialParameters.StopBits = ONESTOPBIT;
    dcbSerialParameters.Parity = NOPARITY;
    dcbSerialParameters.fDtrControl = DTR_CONTROL_DISABLE;
}


Win_serial_port::Win_serial_port(char * portName)
{
    Win_serial_port();
    init(portName);
}

void Win_serial_port::init(Serial_config config)
{
    dcbSerialParameters.BaudRate = config.m_buad_rate;
    init(config.m_com_name.c_str());
}

void Win_serial_port::init(const char *portName)
{
    this->m_is_connected = false;

    this->m_comm = CreateFileA(static_cast<LPCSTR>(portName),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (this->m_comm == INVALID_HANDLE_VALUE){
        if (GetLastError() == ERROR_FILE_NOT_FOUND){
            printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else {
        if (!GetCommState(this->m_comm, &dcbSerialParameters)) 
        {
            printf("failed to get current serial parameters");
        }
        else 
        {
            
            if (!SetCommState(m_comm, &dcbSerialParameters))
            {
                printf("ALERT: could not set Serial port parameters\n");
            }
            else {
                this->m_is_connected = true;
                PurgeComm(this->m_comm, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }

            _COMMTIMEOUTS time_out;
            time_out.ReadIntervalTimeout = 10;
            time_out.ReadTotalTimeoutMultiplier = 10;
            time_out.ReadTotalTimeoutConstant = 10;
            time_out.WriteTotalTimeoutMultiplier = 10;
            time_out.WriteTotalTimeoutConstant = 10;
            SetCommTimeouts(m_comm, &time_out);
        }
        clear_buffer();
    }
}

Win_serial_port::~Win_serial_port()
{
    if (this->m_is_connected){
        this->m_is_connected = false;
        CloseHandle(this->m_comm);
    }
}

#define READ_TIMEOUT      1      // milliseconds
int Win_serial_port::readSerialPort(char *buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    unsigned int toRead = 0;
#if 0
    DWORD dwRead;
    BOOL fWaitingOnRead = FALSE;
    OVERLAPPED osReader = { 0 };

    // Create the overlapped event. Must be closed before exiting
    // to avoid a handle leak.
    osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (osReader.hEvent == NULL)
    {
        cout << "// Error in communications; report it." << endl;
    }

    // Error creating overlapped event; abort.
    if (!fWaitingOnRead)
    {
        // Issue read operation.
        if (!ReadFile(m_comm, buffer, buf_size, &dwRead, &osReader))
        {
            if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
            {
                cout << " Error in communications; report it." << endl;
            }
            else
            {
                fWaitingOnRead = TRUE;
            }
        }
        else
        {
            // read completed immediately
            //cout << "HandleASuccessfulRead " << endl;
            //HandleASuccessfulRead(buffer, dwRead);
        }
    }

    DWORD dwRes;
    if (fWaitingOnRead)
    {
        dwRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
        switch (dwRes)
        {
            // Read completed.
        case WAIT_OBJECT_0:
            if (!GetOverlappedResult(m_comm, &osReader, &dwRead, FALSE))
            {
                cout << "// Error in communications; report it." << endl;
            }
            else
            {
                cout << "HandleASuccessfulRead " << endl;
            }
            //  Reset flag so that another opertion can be issued.
            fWaitingOnRead = FALSE;
            break;

        case WAIT_TIMEOUT:
            // Operation isn't complete yet. fWaitingOnRead flag isn't
            // changed since I'll loop back around, and I don't want
            // to issue another read until the first one finishes.
            //
            // This is a good time to do some background work.
            break;

        default:
            // Error in the WaitForSingleObject; abort.
            // This indicates a problem with the OVERLAPPED structure's
            // event handle.
            break;
        }
    }
    return dwRead;
#endif
    ClearCommError(this->m_comm, &this->m_errors, &this->m_status);

    if (this->m_status.cbInQue > 0)
    {
        if (this->m_status.cbInQue > buf_size)
        {
            toRead = buf_size;
        }
        else toRead = this->m_status.cbInQue;
    }

    if (ReadFile(this->m_comm, buffer, toRead, &bytesRead, NULL))
    {
        return bytesRead;
    }
    return 0;
}

bool Win_serial_port::writeSerialPort(char *buffer, unsigned int buf_size)
{
    DWORD bytesSend;

    if (!WriteFile(this->m_comm, (void*)buffer, buf_size, &bytesSend, 0)){
        ClearCommError(this->m_comm, &this->m_errors, &this->m_status);
        return false;
    }
    else return true;
}

bool Win_serial_port::isConnected()
{
    return this->m_is_connected;
}
#endif