//
// Created by thedoctor on 13/01/24.
//

#ifndef TRAMEAUTHENTIFICATION_H
#define TRAMEAUTHENTIFICATION_H
#include <QVBoxLayout>
#include <QApplication>
#include <QMainWindow>
#include <QFrame>
#include <QHBoxLayout>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <string>
#include <QResizeEvent>
#include <QDebug>
#include "TrameSuperieure.h"
#include "TrameCentrale.h"
#include "TrameGauche.h"
#include "TrameDroite.h"
#include <vector>
#include "../../src/image.h"
#include "../../src/biblio.h"
#include <qobjectdefs.h>
#include <QLineEdit>
#include "../../src/utilisateur.h"

class TrameAuthentification : public QFrame {
    Q_OBJECT
public:
    TrameAuthentification(QWidget *parent): QFrame(parent) {
        // Styling for the login frame
        setStyleSheet("background-color: #f0f0f0; padding: 20px;");

        // Create UI components for the login frame
        QLabel *titleLabel = new QLabel("Login", this);
        titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 20px;");

        usernameLineEdit = new QLineEdit(this);
        usernameLineEdit->setPlaceholderText("Username");

        passwordLineEdit = new QLineEdit(this);
        passwordLineEdit->setPlaceholderText("Password");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        QPushButton *loginButton = new QPushButton("Login", this);
        connect(loginButton, &QPushButton::clicked, this, &TrameAuthentification::onLoginButtonClicked);
        messageLabel = new QLabel(this);
        // Layout setup
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(titleLabel);
        layout->addWidget(usernameLineEdit);
        layout->addWidget(passwordLineEdit);
        layout->addWidget(loginButton);

        setLayout(layout);
    }

    signals:
        void loginSuccess();
    private slots:
        void onLoginButtonClicked() {
            // Perform authentication logic here
            // If authentication is successful, emit the loginSuccess signal
            // emit loginSuccess();
            Utilisateur utilisateur;
            utilisateur.loadCSV("../dta/utilisateurs.csv");

            QString inputValue = usernameLineEdit->text();
            bool user_exist = utilisateur.login(inputValue.toStdString());

            if (!user_exist) {
                messageLabel->setText("Pardon");
            } else {
                emit loginSuccess();
            }
        }

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *messageLabel;
};
#endif //TRAMEAUTHENTIFICATION_H
