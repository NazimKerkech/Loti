//
// Created by thedoctor on 13/01/24.
//

#ifndef ASPECTRATIOPIXMAPLABEL_H
#define ASPECTRATIOPIXMAPLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class AspectRatioPixmapLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AspectRatioPixmapLabel(QWidget *parent = 0): QLabel(parent){
        this->setMinimumSize(1,1);
        setScaledContents(false);
    }
    virtual int heightForWidth( int width ) const{
    return pix.isNull() ? this->height() : ((qreal)pix.height()*width)/pix.width();
    }
    virtual QSize sizeHint() const {
        int w = this->width();
        return QSize( w, heightForWidth(w) );
    }
    QPixmap scaledPixmap() const {
        return pix.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

public slots:
    void setPixmap ( const QPixmap & p){
        pix = p;
        QLabel::setPixmap(scaledPixmap());
    }
    void resizeEvent(QResizeEvent *){
        if(!pix.isNull())
            QLabel::setPixmap(scaledPixmap());
    }

private:
    QPixmap pix;
};

#endif // ASPECTRATIOPIXMAPLABEL_H

