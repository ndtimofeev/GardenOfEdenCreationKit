#ifndef CUSTOMIZABLESPINBOX_H
#define CUSTOMIZABLESPINBOX_H

// STL
#include <functional>

// Core
#include <QtCore/QString>
#include <QtCore/QLocale>

// Gui
#include <QtGui/QValidator>

// Widgets
#include <QtWidgets/QAbstractSpinBox>
#include <QtWidgets/QWidget>

class CustomizableSpinBox : public QAbstractSpinBox
{
    // using ChangeHandler = QString (*)( const QString&, int, const QLocale& );
    using ChangeHandler = std::function<QString(const QString &, int, const QLocale & )>;

public:
    CustomizableSpinBox( QWidget* parent = 0 );
    CustomizableSpinBox( QValidator* v, QWidget* parent = 0 );
    CustomizableSpinBox( ChangeHandler handler, QValidator* v, QWidget* parent = 0 );
    virtual ~CustomizableSpinBox() override;

    virtual void              stepBy( int steps ) override;

    const QValidator*         validator() const;
    void                      setValidator(  QValidator* v );

    void                      setText( QString text );

    void                      setChangeHandler( ChangeHandler handler );

protected:
    virtual StepEnabled stepEnabled() const;

private:
    ChangeHandler changeHandler;
};

#endif /* end of include guard: CUSTOMIZABLESPINBOX_H */
