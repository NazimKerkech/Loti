//
// Created by thedoctor on 12/01/24.
//
#ifndef TRAMESUPERIEURE_H
#define TRAMESUPERIEURE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include <string>
//class FenetrePrincipale;
#include "TrameCentrale.h"

using namespace std;

class TrameSuperieure : public QFrame {
    Q_OBJECT
public:
    TrameSuperieure(string id, QWidget *parent = nullptr) : QFrame(parent) {
        this->id = id;
        setObjectName("TrameSuperieure");  // Set a unique object name for the QFrame
        setStyleSheet("#TrameSuperieure { border: 3px solid black; }");

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(10, 10, 10, 10);  // Adjust margins as needed

        // Create the colored disc with user initials
        iconLabel = new QLabel(this);
        iconLabel->setFixedSize(30, 30);  // Adjust size as needed
        //iconLabel->setAlignment(Qt::AlignCenter);
        updateIcon("");  // Replace with user's initials

        // Create a label for the user's name
        QLabel *nameLabel = new QLabel(QString::fromStdString(id), this);  // Replace with the user's name
        //nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        //layout->setDirection(QBoxLayout::RightToLeft);
        layout->addStretch();
        layout->addWidget(iconLabel);
        layout->addWidget(nameLabel);
        //layout->addStretch();

        this->setFixedWidth(parent->size().width());
        this->setFixedHeight(parent->size().height() / 10);
    }

    void updateIcon(const QString &initials) {
        // Function to update the colored disc with user initials
        QPixmap pixmap(30, 30);  // Adjust size as needed
        pixmap.fill(QColor("#00FFFFFF"));  // Replace with the desired color

        QPen pen(Qt::red);
        pen.setBrush(Qt::red);  // Set brush color (fill color)
        pen.setColor(QColor(0, 0, 0, 0));  // Set pen color (border color) with alpha 0 for transparency

        QPainter painter(&pixmap);
        painter.setPen(pen);
        painter.setBrush(Qt::red);
        painter.drawEllipse(0, 0, 25, 25);  // Example: Draw an ellipse

        painter.setRenderHint(QPainter::Antialiasing, true);
        //painter.setBrush(Qt::red);
        //painter.drawEllipse(0, 0, 30, 30);  // Adjust size as needed
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(pixmap.rect(), Qt::AlignCenter, initials);

        iconLabel->setPixmap(pixmap);
    }
private:
    QLabel *iconLabel;
    string id;
};

#endif //TRAMESUPERIEURE_H
