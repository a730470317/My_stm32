#include "serial_service.h"
//Serial_service *g_serial_service;

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



void Serial_service::init_serial()
{
    //g_serial_service = this;
    std::unique_lock<std::mutex> lock(m_mutex_serial_mutex);
    qRegisterMetaType<Serial_packet>("Serial_packet");

    m_serial_config.load_from_json("serial_config.json");
    m_serial_config.save_to_json("saerial_config.json_bak");
    m_serial_config.display();

    m_serial.setPortName(m_serial_config.m_com_name.c_str());
    m_serial.setBaudRate(m_serial_config.m_buad_rate);
    m_serial.open(QIODevice::ReadWrite);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::OddParity);
    //m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.clear(QSerialPort::Direction::AllDirections);
    m_serial.setReadBufferSize(100000000);


    if (m_serial.isOpen())
    {
        cout << "Open serial success!!\n" << endl;
    }
    else
    {
        cout << "Open serial fail, please check!!!" << endl;;
    }

    if (1)
    {
        m_thread_ptr = new std::thread(&Serial_service::service, this);
        m_thread_ptr->detach();
    }
    return;

    //m_thread = std::thread(&Serial_service::service, this);
    //m_thread->detach();

}

void Serial_service::send_packet(Serial_packet packet)
{
    make_packet(packet.data, m_packet_mcu.m_send_buffer, packet.id, packet.data_length, &packet.packet_length);
    m_serial.write(m_packet_mcu.m_send_buffer, packet.packet_length);
    m_serial.waitForBytesWritten(1);
}

void Serial_service::service()
{
    std::unique_lock<std::mutex> lock(m_mutex_serial_mutex);
    QByteArray serial_data;
    char packet_data[MAX_REC_BUFFER];
    Serial_packet packet;
    int rec_buffer_count = 0;
    try
    {
        while (1)
        {
            int get_data = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / m_rec_frequency)));
            if (m_serial.isOpen())
            {

                int b = 0;
                int a = 3 / b;
                //if (m_serial.isDataTerminalReady() && m_serial.isReadable())
                //if ( m_serial.waitForReadyRead(1) )
                if (m_serial.isReadable())
                {
                    serial_data = m_serial.readAll();
                    //serial_data = m_serial.read(100);
                    m_serial.clear();
                    //m_serial.close();
                    //m_serial.open(QIODevice::ReadWrite);
                }
                else
                {
                    continue;
                }

                //catch (...)

                //cout << "----- " << serial_data.size()  << " ----- "<< endl;
                for (int i = 0; i < serial_data.size(); i++)
                {
                    //printf("%x ", serial_data[i] & 0xff );

                    if (m_packet_mcu.m_current_rec_index > MAX_REC_BUFFER)
                    {
                        m_packet_mcu.m_current_rec_index = 0;
                    }
                    if (onRec(serial_data[i], m_packet_mcu.m_rec_buffer, &m_packet_mcu.m_current_rec_index, &packet.id, &packet.data_length, packet.data))
                    {
                        cout << "Serial size = " << serial_data.size() << endl;
                        get_data = 1;
                        rec_buffer_count++;
                        on_serial_callback(packet);
                        //printf("--- Rec data %d --- \r\n", rec_buffer_count);
                        //packet.display();
                        //if (packet.id == 0x10)
                        //{
                        //    float f_data[2];
                        //    memcpy((char*)f_data, packet.data, sizeof(float));
                        //    memcpy((char*)&f_data[1], packet.data + sizeof(float), sizeof(float));
                        //    printf("%f, %f\r\n", f_data[0], f_data[1]);
                        //}
                    }
                }

            }
        }
    }
    catch (...)
    {
        CONSOLE_SET_TEXT_RED;
        cout << "Something error happened!!! " << __FUNCTION__ << "  " << __LINE__ << endl;
        m_serial.close();
        CONSOLE_RESET_DEFAULT;
        delete m_thread_ptr;
        on_serial_error_happen();
        return;
    }
}

void Serial_service::print_serial_service_version()
{
    cout << "===== SERIAL_SERVICE_VERSION =====" << endl;
    cout << "Version:       " << SERIAL_SERVICE_VERSION << endl;
    cout << "Version desc:  " << SERIAL_SERVICE_DESC << endl;
    cout << "Build date is: " << __DATE__ << "  " << __TIME__ << endl;
    cout << "===== End =====" << endl;
}