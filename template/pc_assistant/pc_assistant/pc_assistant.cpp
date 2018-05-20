#include "pc_assistant.h"
using namespace std;
pc_assistant::pc_assistant(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    cout << "Hello" << endl;
    init_signal_and_slot();
    //m_packet_rec_timer.start(2);
    //m_serial_rec_timer.start(2);
    open_serial();
}

void pc_assistant::init_signal_and_slot()
{

    connect(&m_serial_rec_timer, SIGNAL(timeout()), this, SLOT(slot_on_serial_timeout()));
    connect(&m_packet_rec_timer, SIGNAL(timeout()), this, SLOT(slot_on_packet_timeout()));

    connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(slot_on_click_start()));
}

pc_assistant::~pc_assistant()
{

}

void pc_assistant::slot_on_click_start()
{
  std::cout << "slot_on_click_start" << std::endl;
}

void pc_assistant::slot_on_packet_timeout()
{
    cout << __FUNCTION__ << endl;
}

void pc_assistant::slot_on_serial_timeout()
{
    cout << __FUNCTION__ << endl;
}