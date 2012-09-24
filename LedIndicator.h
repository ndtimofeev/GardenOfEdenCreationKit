#ifndef _LEDINDICATOR_H_57133_
#define _LEDINDICATOR_H_57133_

// Core
#include <QtCore/QEvent>
#include <QtCore/QSize>

// Gui
#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtGui/QPaintEvent>

// Widgets
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QWidget>

class LedIndicator : public QAbstractButton
{
public:
    LedIndicator( QWidget* parent = 0 );
    virtual ~LedIndicator() override;

    virtual QSize minimumSizeHint() const override;
    virtual QSize sizeHint() const override;

protected:
    virtual void changeEvent( QEvent* e ) override;
    virtual void paintEvent( QPaintEvent* e ) override;

private:
    QImage good;
    QImage bad;
    QImage off;
};

#endif /* _LEDINDICATOR_H_57133_ */
