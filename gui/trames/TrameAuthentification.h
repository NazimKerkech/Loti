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
        QLabel *titleLabel = new QLabel("Authentification", this);
        titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 20px;");

        codeLineEdit = new QLineEdit(this);
        codeLineEdit->setPlaceholderText("Code");
        codeLineEdit->setText("01-aa-01");

        QPushButton *loginButton = new QPushButton("Se connecter", this);
        connect(loginButton, &QPushButton::clicked, this, &TrameAuthentification::onLoginButtonClicked);
        messageLabel = new QLabel(this);
        // Layout setup
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(titleLabel);
        layout->addWidget(codeLineEdit);
        layout->addWidget(loginButton);

        setLayout(layout);
    }

    signals:
        void loginSuccess(string id);
    private slots:
        void onLoginButtonClicked() {
            // Perform authentication logic here
            // If authentication is successful, emit the loginSuccess signal
            // emit loginSuccess();
            const string LOTI_DIR(SOURCE_DIR);

            Utilisateur utilisateur;
            utilisateur.loadCSV(LOTI_DIR+"/dta/utilisateurs.txt");

            QString inputValue = codeLineEdit->text();
            bool user_exist = utilisateur.login(inputValue.toStdString());

            if (!user_exist) {
                messageLabel->setText("Erreur");
            } else {
                emit loginSuccess(inputValue.toStdString());
            }
        }

private:
    QLineEdit *codeLineEdit;
    QLabel *messageLabel;
};
#endif //TRAMEAUTHENTIFICATION_H
