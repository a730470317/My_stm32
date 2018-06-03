/********************************************************************************
** Form generated from reading UI file 'pc_assistant.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PC_ASSISTANT_H
#define UI_PC_ASSISTANT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pc_assistantClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_message;
    QHBoxLayout *horizontalLayout;
    QDial *dial_circle;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLCDNumber *lcdNumber_adc_val;
    QLabel *label_2;
    QLCDNumber *lcdNumber_pendulum_pos;
    QDial *dial_pedulum_pos;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_start;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_exit;

    void setupUi(QMainWindow *pc_assistantClass)
    {
        if (pc_assistantClass->objectName().isEmpty())
            pc_assistantClass->setObjectName(QStringLiteral("pc_assistantClass"));
        pc_assistantClass->resize(989, 946);
        centralWidget = new QWidget(pc_assistantClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        label_message = new QLabel(centralWidget);
        label_message->setObjectName(QStringLiteral("label_message"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_message->sizePolicy().hasHeightForWidth());
        label_message->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_message->setFont(font);

        verticalLayout_2->addWidget(label_message);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        dial_circle = new QDial(centralWidget);
        dial_circle->setObjectName(QStringLiteral("dial_circle"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dial_circle->sizePolicy().hasHeightForWidth());
        dial_circle->setSizePolicy(sizePolicy1);
        dial_circle->setMinimum(0);
        dial_circle->setMaximum(360);
        dial_circle->setPageStep(10);
        dial_circle->setValue(360);
        dial_circle->setOrientation(Qt::Vertical);
        dial_circle->setInvertedAppearance(true);
        dial_circle->setInvertedControls(true);
        dial_circle->setWrapping(true);
        dial_circle->setNotchTarget(5);
        dial_circle->setNotchesVisible(true);

        horizontalLayout->addWidget(dial_circle);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        verticalLayout->addWidget(label);

        lcdNumber_adc_val = new QLCDNumber(centralWidget);
        lcdNumber_adc_val->setObjectName(QStringLiteral("lcdNumber_adc_val"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lcdNumber_adc_val->sizePolicy().hasHeightForWidth());
        lcdNumber_adc_val->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(30);
        lcdNumber_adc_val->setFont(font2);
        lcdNumber_adc_val->setFrameShape(QFrame::NoFrame);
        lcdNumber_adc_val->setDigitCount(5);
        lcdNumber_adc_val->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_adc_val->setProperty("value", QVariant(7));
        lcdNumber_adc_val->setProperty("intValue", QVariant(7));

        verticalLayout->addWidget(lcdNumber_adc_val);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        lcdNumber_pendulum_pos = new QLCDNumber(centralWidget);
        lcdNumber_pendulum_pos->setObjectName(QStringLiteral("lcdNumber_pendulum_pos"));
        sizePolicy2.setHeightForWidth(lcdNumber_pendulum_pos->sizePolicy().hasHeightForWidth());
        lcdNumber_pendulum_pos->setSizePolicy(sizePolicy2);
        lcdNumber_pendulum_pos->setFont(font2);
        lcdNumber_pendulum_pos->setFrameShape(QFrame::NoFrame);
        lcdNumber_pendulum_pos->setSmallDecimalPoint(false);
        lcdNumber_pendulum_pos->setDigitCount(6);
        lcdNumber_pendulum_pos->setMode(QLCDNumber::Dec);
        lcdNumber_pendulum_pos->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_pendulum_pos->setProperty("value", QVariant(666.66));

        verticalLayout->addWidget(lcdNumber_pendulum_pos);

        dial_pedulum_pos = new QDial(centralWidget);
        dial_pedulum_pos->setObjectName(QStringLiteral("dial_pedulum_pos"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dial_pedulum_pos->sizePolicy().hasHeightForWidth());
        dial_pedulum_pos->setSizePolicy(sizePolicy3);
        dial_pedulum_pos->setMaximum(360);
        dial_pedulum_pos->setInvertedAppearance(false);
        dial_pedulum_pos->setWrapping(true);
        dial_pedulum_pos->setNotchTarget(5);
        dial_pedulum_pos->setNotchesVisible(true);

        verticalLayout->addWidget(dial_pedulum_pos);

        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 2);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_start->sizePolicy().hasHeightForWidth());
        pushButton_start->setSizePolicy(sizePolicy4);
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton_start->setFont(font3);

        verticalLayout_3->addWidget(pushButton_start);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        sizePolicy4.setHeightForWidth(pushButton_exit->sizePolicy().hasHeightForWidth());
        pushButton_exit->setSizePolicy(sizePolicy4);
        pushButton_exit->setFont(font3);

        verticalLayout_3->addWidget(pushButton_exit);


        horizontalLayout_2->addLayout(verticalLayout_3);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        pc_assistantClass->setCentralWidget(centralWidget);

        retranslateUi(pc_assistantClass);
        QObject::connect(pushButton_exit, SIGNAL(clicked()), pc_assistantClass, SLOT(close()));

        QMetaObject::connectSlotsByName(pc_assistantClass);
    } // setupUi

    void retranslateUi(QMainWindow *pc_assistantClass)
    {
        pc_assistantClass->setWindowTitle(QApplication::translate("pc_assistantClass", "pc_assistant", 0));
        label_message->setText(QApplication::translate("pc_assistantClass", "The is message", 0));
        label->setText(QApplication::translate("pc_assistantClass", "ADC_val:", 0));
        label_2->setText(QApplication::translate("pc_assistantClass", "Pendulum pos(angle):", 0));
        pushButton_start->setText(QApplication::translate("pc_assistantClass", "Start", 0));
        pushButton_exit->setText(QApplication::translate("pc_assistantClass", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class pc_assistantClass: public Ui_pc_assistantClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PC_ASSISTANT_H
