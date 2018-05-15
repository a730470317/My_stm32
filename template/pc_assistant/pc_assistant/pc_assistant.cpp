#include "pc_assistant.h"
using namespace std;
pc_assistant::pc_assistant(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    cout << "Hello" << endl;
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