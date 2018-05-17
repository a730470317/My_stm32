#ifndef PC_ASSISTANT_H
#define PC_ASSISTANT_H

#include <QtWidgets/QMainWindow>

#include "ui_pc_assistant.h"
#include "stdio.h"
#include <iostream>
#include "QTime"
#include "qtimer.h"

class pc_assistant : public QMainWindow
{
    Q_OBJECT

public:
    pc_assistant(QWidget *parent = 0);
    ~pc_assistant();
    QTimer m_serial_rec_timer;
    QTimer m_packet_rec_timer;
    
    void init_signal_and_slot();

    public slots:
    void slot_on_click_start();
private:
    Ui::pc_assistantClass ui;
};

#endif // PC_ASSISTANT_H
