//
// Created by thedoctor on 17/01/24.
//

#ifndef RESCALINGPIXMAPLABEL_H
#define RESCALINGPIXMAPLABEL_H
#include <QLabel>
#include <QResizeEvent>
#include <QPixmap>

class RescalingPixmapLabel : public QLabel {
    Q_OBJECT

public:
    explicit RescalingPixmapLabel(QWidget *parent = nullptr) : QLabel(parent) {
        setScaledContents(true); // Enable scaled contents to allow resizing
    }

    public slots:
        void setPixmap(const QPixmap &pixmap) {
        QLabel::setPixmap(pixmap);
    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        QLabel::resizeEvent(event);
        // Update the pixmap with the new size without maintaining the aspect ratio
        if (!pixmap()->isNull()) {
            QPixmap rescaledPixmap = pixmap()->scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            QLabel::setPixmap(rescaledPixmap);
        }
    }
};
#endif //RESCALINGPIXMAPLABEL_H
