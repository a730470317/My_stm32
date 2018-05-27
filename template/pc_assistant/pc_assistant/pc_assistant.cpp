#include "pc_assistant.h"

#include <functional>
using namespace std;

pc_assistant::~pc_assistant()
{}

pc_assistant::pc_assistant(QWidget *parent)
    : QMainWindow(parent)
{

    qRegisterMetaType<MCU_STATE>("MCU_STATE");
    cout << "Hello" << endl;

    ui.setupUi(this);
    init_signal_and_slot();
    init_serial();
    m_serial_rec_timer.stop();
    m_packet_rec_timer.stop();

}

void pc_assistant::init_signal_and_slot()
{
    connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(slot_on_click_start()));

    connect(this, SIGNAL(signal_on_refresh_mcu_state(MCU_STATE*)), this, SLOT(slot_on_refresh_mcu_state(MCU_STATE*)), Qt::ConnectionType::UniqueConnection);
    connect(this, SIGNAL(signal_on_send_serial_packet(Serial_packet*)), this, SLOT(slot_on_send_serial_packet(Serial_packet*)), Qt::ConnectionType::UniqueConnection);
    connect(this, SIGNAL(signal_on_serial_error_happen()), this, SLOT(slot_on_click_start()), Qt::ConnectionType::UniqueConnection);


    connect(&m_serial_rec_timer, SIGNAL(timeout()), this, SLOT(slot_on_serial_timeout()));
    connect(&m_packet_rec_timer, SIGNAL(timeout()), this, SLOT(slot_on_packet_timeout()));



}

void pc_assistant::on_serial_callback(Serial_packet packet)
{
    printf("%s, On rec packet.  \r\n", __FUNCTION__);

    //packet.display();
    switch (packet.id)
    {
    case STM32_MCU_STATE_REPORT:
        memcpy((void *)&m_mcu_state, packet.data, sizeof(MCU_STATE));
        cout << "Adc =  " << m_mcu_state.m_adc_encoder_val << " , pos = " << m_mcu_state.m_motor_pos << endl;
        if(ui_busy==0)
            emit signal_on_refresh_mcu_state(&m_mcu_state);
        break;
    default:
        cout << "Unrecongize packet, " << endl;
        packet.display();
        break;
    }

    //packet.id = 255 - packet.id;
    //send_packet(packet);
    //emit signal_on_send_serial_packet(&packet);
};

void pc_assistant::slot_on_send_serial_packet(Serial_packet *packet)
{
    send_packet(*packet);
}

void pc_assistant::slot_on_refresh_mcu_state(MCU_STATE * mcu_state)
{
    //cout <<"Draw -- " <<mcu_state->m_motor_pos << endl;
    ui_busy = 1;
    ui.dial_circle->setValue((int)(mcu_state->m_motor_pos) % 360);
    /*if (((int)mcu_state->m_motor_pos%360) >= 0)
    {
        ui.dial_circle->setValue((int)mcu_state->m_motor_pos % 360);
    }
    else
    {
    }*/
    char show_text[1024];
    sprintf(show_text, " Adc_val = %.2f\r\n Pendulum pos = %.2f\r\n", mcu_state->m_adc_encoder_val,mcu_state->m_pendulum_pos);
    ui.label_message->setText(show_text);
    ui.dial_circle->repaint();
    ui_busy = 0;
}

void pc_assistant::slot_on_click_start()
{
    std::cout << "slot_on_click_start" << std::endl;
    init_serial();
}

void pc_assistant::slot_on_packet_timeout()
{
    cout << __FUNCTION__ << endl;
}

void pc_assistant::slot_on_serial_timeout()
{
    //close();
    cout << __FUNCTION__ << endl;
}