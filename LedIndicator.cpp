// Core
#include <QtCore/QEvent>
#include <QtCore/QRect>
#include <QtCore/QSize>

// Gui
#include <QtGui/QImage>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>

// Widgets
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QWidget>

// Internal
#include <LedIndicator.h>

LedIndicator::LedIndicator( QWidget* parent ) :
    QAbstractButton( parent ),
    good( ":/images/greenLedOn.png" ),
    bad( ":/images/redLedOn.png" ),
    off( ":/images/greenLedOff.png" )
{
    Q_INIT_RESOURCE( GardenOfEdenCreationKit );

    this->setMaximumSize( 21, 21 );
    this->setCheckable( true );
}

LedIndicator::~LedIndicator()
{}

QSize LedIndicator::minimumSizeHint() const
{
    return QSize( 21, 21 );
}

QSize LedIndicator::sizeHint() const
{
    return QSize( 21, 21 );
}

void LedIndicator::paintEvent( QPaintEvent* e )
{
    const int size = qMin( e->rect().width(), e->rect().height() );
    const QRect rect( 0, 0, size, size );
    QPainter painter( this );

    painter.setRenderHint( QPainter::Antialiasing );

    if ( this->isEnabled() )
    {
        QImage img =
            this->isCheckable() && this->isChecked() ? this->bad : this->good;
        painter.drawImage( rect, img, img.rect() );
    }
    else
        painter.drawImage( rect, this->off, this->off.rect() );
}

void LedIndicator::changeEvent( QEvent* e )
{
    if ( e->type() == QEvent::EnabledChange )
        this->update();

    this->QWidget::changeEvent( e );
}
