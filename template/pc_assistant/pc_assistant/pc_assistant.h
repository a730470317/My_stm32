#ifndef PC_ASSISTANT_H
#define PC_ASSISTANT_H
#include "import_lib.h"
#include <QtWidgets/QMainWindow>

#include "ui_pc_assistant.h"
#include "stdio.h"
#include <iostream>
#include "QTime"
#include "qtimer.h"
#include <iostream>
#include <QSerialPort>
#include <serial_service.h>


class pc_assistant : public QMainWindow, public Serial_service
{
    Q_OBJECT
public:
    QTimer m_serial_rec_timer;
    QTimer m_packet_rec_timer;
    MCU_STATE m_mcu_state;
    int ui_busy = 0;
    pc_assistant(QWidget *parent = 0);
    ~pc_assistant();

    signals:

    void signal_on_refresh_mcu_state(MCU_STATE * mcu_state);
    void signal_on_send_serial_packet(Serial_packet *packet);
    void signal_on_serial_error_happen();

    public slots:
    void slot_on_click_start();
    void slot_on_serial_timeout();
    void slot_on_packet_timeout();

    void slot_on_refresh_mcu_state(MCU_STATE *serial_packet);
    void slot_on_send_serial_packet(Serial_packet *packet);

public:
    void init_signal_and_slot();
    void on_serial_callback(Serial_packet packet);
    void on_serial_error_happen()
    { 
        emit signal_on_serial_error_happen();
    };

private:
    Ui::pc_assistantClass ui;
};

#endif // PC_ASSISTANT_H
