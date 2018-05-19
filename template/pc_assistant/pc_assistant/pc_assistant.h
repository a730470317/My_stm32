#ifndef PC_ASSISTANT_H
#define PC_ASSISTANT_H
#include "import_lib.h"
#include <QtWidgets/QMainWindow>

#include "ui_pc_assistant.h"
#include "stdio.h"
#include <iostream>
#include "QTime"
#include "qtimer.h"
#include "QSerialPort"
#include <iostream>
using namespace std;

class serial_service
{
public:
    void print_kernel_version()
    {
        cout << "===== " << __FUNCTION__ << " =====" << endl;
        cout << "Build date is " << __DATE__ << "  " << __TIME__ << endl;

    }
    void test_fun()
    {
        cout << __FUNCTION__ << endl;
    };



    virtual void slot_on_serial_timeout() = 0;
    virtual void slot_on_packet_timeout() = 0;
};

class pc_assistant : public QMainWindow, serial_service
{
    Q_OBJECT
public:
    QTimer m_serial_rec_timer;
    QTimer m_packet_rec_timer;

    pc_assistant(QWidget *parent = 0);
    ~pc_assistant();

    QSerialPort m_serial;

    public slots:
    void slot_on_click_start();
    void slot_on_serial_timeout();
    void slot_on_packet_timeout();

    void init_signal_and_slot();

private:
    Ui::pc_assistantClass ui;
};

#endif // PC_ASSISTANT_H
