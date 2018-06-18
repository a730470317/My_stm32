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

    connect(ui.slider_pwm, SIGNAL(sliderMoved(int)), this, SLOT(slot_on_slider_pwm_changed()));

}

void pc_assistant::slot_on_slider_pwm_changed()
{
    Motor_control motor_ctrl;
    m_serial_packet.id = STM32_MCU_SET_PWM;
    m_serial_packet.direction = Serial_packet::e_direction_out;
    char text_char[100];
    sprintf(text_char, "PWM %03d", (int)ui.slider_pwm->value());
    ui.label_pwm->setText(QString(text_char));

    motor_ctrl.if_manaul = 0;
    motor_ctrl.pwm_val[0] = ui.slider_pwm->value();
    motor_ctrl.pwm_val[1] = 0;

    if (ui.checkBox_manual->isChecked())
    {
        cout << "Slider values = " << ui.slider_pwm->value() << endl;
        motor_ctrl.if_manaul = 1;
        
    }
    memcpy(m_serial_packet.data, &(motor_ctrl), sizeof(Motor_control));
    m_serial_packet.data_length = sizeof(Motor_control);
    m_serial_packet.display();
    emit signal_on_send_serial_packet(&m_serial_packet);
}

void pc_assistant::on_serial_callback(Serial_packet packet)
{
    //printf("%s, On rec packet.  \r\n", __FUNCTION__);

    //packet.display();
    CONSOLE_SET_TEXT_YELLOW;
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
    CONSOLE_RESET_DEFAULT;
    packet.id = 255 - packet.id;
    ////send_packet(packet);
    emit signal_on_send_serial_packet(&packet);

    //char data[5];
    //for (int i = 0; i < 5; i++)
    //{
    //    data[i] = i;
    //}
    //m_win_serial->writeSerialPort(data, 5);
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
    ui.lcdNumber_adc_val->display(mcu_state->m_adc_encoder_val);
    ui.lcdNumber_pendulum_pos->display(mcu_state->m_pendulum_pos);
    ui.dial_pedulum_pos->setValue((int)(mcu_state->m_pendulum_pos) % 360);
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