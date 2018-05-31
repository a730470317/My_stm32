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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pc_assistantClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_start;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_exit;
    QLabel *label_message;
    QDial *dial_circle;

    void setupUi(QMainWindow *pc_assistantClass)
    {
        if (pc_assistantClass->objectName().isEmpty())
            pc_assistantClass->setObjectName(QStringLiteral("pc_assistantClass"));
        pc_assistantClass->resize(253, 221);
        centralWidget = new QWidget(pc_assistantClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pushButton_start->setFont(font);

        gridLayout->addWidget(pushButton_start, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 2, 1, 1);

        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setFont(font);

        gridLayout->addWidget(pushButton_exit, 2, 2, 1, 1);

        label_message = new QLabel(centralWidget);
        label_message->setObjectName(QStringLiteral("label_message"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_message->sizePolicy().hasHeightForWidth());
        label_message->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_message->setFont(font1);

        gridLayout->addWidget(label_message, 0, 1, 1, 1);

        dial_circle = new QDial(centralWidget);
        dial_circle->setObjectName(QStringLiteral("dial_circle"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dial_circle->sizePolicy().hasHeightForWidth());
        dial_circle->setSizePolicy(sizePolicy1);
        dial_circle->setMinimum(0);
        dial_circle->setMaximum(360);
        dial_circle->setPageStep(0);
        dial_circle->setValue(360);
        dial_circle->setOrientation(Qt::Vertical);
        dial_circle->setInvertedAppearance(true);
        dial_circle->setInvertedControls(true);
        dial_circle->setWrapping(true);
        dial_circle->setNotchTarget(5);
        dial_circle->setNotchesVisible(true);

        gridLayout->addWidget(dial_circle, 1, 1, 2, 1);

        pc_assistantClass->setCentralWidget(centralWidget);

        retranslateUi(pc_assistantClass);

        QMetaObject::connectSlotsByName(pc_assistantClass);
    } // setupUi

    void retranslateUi(QMainWindow *pc_assistantClass)
    {
        pc_assistantClass->setWindowTitle(QApplication::translate("pc_assistantClass", "pc_assistant", 0));
        pushButton_start->setText(QApplication::translate("pc_assistantClass", "Start", 0));
        pushButton_exit->setText(QApplication::translate("pc_assistantClass", "Exit", 0));
        label_message->setText(QApplication::translate("pc_assistantClass", "The is message", 0));
    } // retranslateUi

};

namespace Ui {
    class pc_assistantClass: public Ui_pc_assistantClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PC_ASSISTANT_H
