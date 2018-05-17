#include "pc_assistant.h"
using namespace std;
pc_assistant::pc_assistant(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    cout << "Hello" << endl;
    init_signal_and_slot();
}

void pc_assistant::init_signal_and_slot()
{
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