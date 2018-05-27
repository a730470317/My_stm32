#include "pc_assistant.h"

#include <functional>
using namespace std;

pc_assistant::~pc_assistant()
{}

pc_assistant::pc_assistant(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    cout << "Hello" << endl;
    init_signal_and_slot();
    init_serial();
}

void pc_assistant::init_signal_and_slot()
{

    connect(&m_serial_rec_timer, SIGNAL(timeout()), this, SLOT(slot_on_serial_timeout()));
    connect(&m_packet_rec_timer, SIGNAL(timeout()), this, SLOT(slot_on_packet_timeout()));

    connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(slot_on_click_start()));
}

void pc_assistant::on_serial_callback(Serial_packet packet)
{
    printf("%s, On rec packet.  \r\n", __FUNCTION__ );
    //packet.display();
    switch (packet.id)
    {
    case STM32_MCU_STATE_REPORT :
        MCU_STATE mcu_state;
        memcpy((void *)&mcu_state, packet.data, sizeof(MCU_STATE));
        cout << "Adc =  " << mcu_state.m_adc_encoder << " , pos = " << mcu_state.m_motor_pos << endl;
        break;
    default: 
        cout << "Unrecongize packet, " << endl;
        packet.display();
        break;
    }
};

void pc_assistant::slot_on_click_start()
{
  std::cout << "slot_on_click_start" << std::endl;
  Serial_packet packet;
  emit signal_on_rec_serial_packet(packet);
}

void pc_assistant::slot_on_packet_timeout()
{
    cout << __FUNCTION__ << endl;
}

void pc_assistant::slot_on_serial_timeout()
{
    close();
    cout << __FUNCTION__ << endl;
}