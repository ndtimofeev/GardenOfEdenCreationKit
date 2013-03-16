// Definition
#include <CustomizableSpinBox.h>

// Core
#include <QtCore/QString>

// Widgets
#include <QtWidgets/QAbstractSpinBox>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>

CustomizableSpinBox::CustomizableSpinBox( QWidget* parent ) :
    QAbstractSpinBox( parent ), changeHandler( nullptr )
{
    this->setValidator( nullptr );
}

CustomizableSpinBox::CustomizableSpinBox( QValidator* v, QWidget* parent ) :
    QAbstractSpinBox( parent ), changeHandler( nullptr )
{
    this->setValidator( v );
}

CustomizableSpinBox::CustomizableSpinBox( ChangeHandler handler, QValidator* v, QWidget* parent ) :
    QAbstractSpinBox( parent ), changeHandler( handler )
{
    this->setValidator( v );
}

CustomizableSpinBox::~CustomizableSpinBox()
{
    // body
}

void CustomizableSpinBox::stepBy( int steps )
{
    QString origStr = this->text();
    const QValidator* v = this->validator();
    QString str = this->changeHandler( origStr, steps, v ? v->locale() : QLocale::system() );
    if ( str != origStr )
        this->setText( str );
}

void CustomizableSpinBox::setText( QString text )
{
    int pos = 0;

    if ( ! this->validator() || this->validator()->validate( text, pos ) != QValidator::Invalid )
    {
        this->lineEdit()->setText( text );
        this->lineEdit()->selectAll();
    }
}

void CustomizableSpinBox::setValidator( QValidator* v )
{
    this->lineEdit()->setValidator( v );
}

const QValidator* CustomizableSpinBox::validator() const
{
    return this->lineEdit()->validator();
}

void CustomizableSpinBox::setChangeHandler( ChangeHandler handler )
{
    this->changeHandler = handler;
}

QAbstractSpinBox::StepEnabled CustomizableSpinBox::stepEnabled() const
{
    return this->changeHandler
        ? QAbstractSpinBox::StepUpEnabled | QAbstractSpinBox::StepDownEnabled
        : QAbstractSpinBox::StepNone;
}
