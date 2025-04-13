#include "widget.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QFrame>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // Set up main widget properties
    setWindowTitle("User Information Form");
    setFixedSize(400, 300);

    // Create a main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create a frame for the form with shadow effect
    QFrame *formFrame = new QFrame(this);
    formFrame->setFrameShape(QFrame::StyledPanel);
    formFrame->setFrameShadow(QFrame::Raised);
    formFrame->setStyleSheet("background-color: #f8f9fa; border-radius: 10px;");

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(15);
    shadowEffect->setColor(QColor(0, 0, 0, 150));
    shadowEffect->setOffset(3, 3);
    formFrame->setGraphicsEffect(shadowEffect);

    QVBoxLayout *formLayout = new QVBoxLayout(formFrame);
    formLayout->setContentsMargins(20, 20, 20, 20);
    formLayout->setSpacing(15);

    // Title label
    QLabel *titleLabel = new QLabel("User Information", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2c3e50;");

    // First name field
    QHBoxLayout *firstNameLayout = new QHBoxLayout(this);
    QLabel *firstNameLabel = new QLabel("First Name:", this);
    firstNameLabel->setStyleSheet("font-weight: bold; color: #34495e;");

    QLineEdit *first_name_line = new QLineEdit(formFrame);
    first_name_line->setPlaceholderText("Enter your first name");
    first_name_line->setStyleSheet("QLineEdit {"
                                   "border: 1px solid #bdc3c7;"
                                   "border-radius: 5px;"
                                   "color: black;"
                                   "padding: 8px;"
                                   "background: white;"
                                   "}"
                                   "QLineEdit:focus {"
                                   "border: 1px solid #3498db;"
                                   "color: green;"
                                   "}");

    firstNameLayout->addWidget(firstNameLabel);
    firstNameLayout->addWidget(first_name_line);

    // Last name field
    QHBoxLayout *lastNameLayout = new QHBoxLayout(this);
    QLabel *lastNameLabel = new QLabel("Last Name:", this);
    lastNameLabel->setStyleSheet("font-weight: bold; color: #34495e;");

    QLineEdit *last_name_edit = new QLineEdit(this);
    last_name_edit->setPlaceholderText("Enter your last name");
    last_name_edit->setStyleSheet("QLineEdit {"
                                  "color: black;"
                                  "border: 1px solid #bdc3c7;"
                                  "border-radius: 5px;"
                                  "padding: 8px;"
                                  "background: white;"
                                  "}"
                                  "QLineEdit:focus {"
                                  "border: 1px solid #3498db;"
                                  "color: green;"
                                  "}");

    lastNameLayout->addWidget(lastNameLabel);
    lastNameLayout->addWidget(last_name_edit);

    // Save button
    QPushButton *button = new QPushButton("Save", formFrame);
    button->setStyleSheet("QPushButton {"
                          "background-color: #3498db;"
                          "color: white;"
                          "border: none;"
                          "border-radius: 5px;"
                          "padding: 10px;"
                          "font-weight: bold;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #2980b9;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #1a5276;"
                          "}");
    button->setCursor(Qt::PointingHandCursor);

    // Add widgets to form layout
    formLayout->addWidget(titleLabel);
    formLayout->addLayout(firstNameLayout);
    formLayout->addLayout(lastNameLayout);
    formLayout->addWidget(button);
    formLayout->addStretch();

    // Add form frame to main layout
    mainLayout->addWidget(formFrame);

    // Set background gradient
    setStyleSheet("Widget {"
                  "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                  "stop:0 #ecf0f1, stop:1 #bdc3c7);"
                  "}");

    // Connect signals
    connect(last_name_edit, &QLineEdit::textChanged, []() {
        qDebug() << "Text has changed";
    });

    connect(button, &QPushButton::clicked, [=]() {
        QString first = first_name_line->text();
        QString last = last_name_edit->text();

        if(!first.isEmpty() && !last.isEmpty()) {
            qDebug() << first << " " << last;

            // Show success message
            QMessageBox::information(this, "Success",
                                     QString("User information saved:\nFirst Name: %1\nLast Name: %2").arg(first).arg(last));

            // Clear fields after save
            first_name_line->clear();
            last_name_edit->clear();
            first_name_line->setFocus();
        } else {
            qDebug() << "Some fields are empty";

            // Show error message
            QMessageBox::warning(this, "Error",
                                 "Please fill in all fields before saving.");
        }
    });
}

Widget::~Widget() {}
