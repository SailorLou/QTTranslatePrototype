#include "Translator.h"
#include <QDebug>
#include <QGuiApplication>
#include <QDir>
#include <QTranslator>
#include <QQmlEngine>

Translator::Translator(QQmlEngine *engine)
{
    _appTranslator = nullptr;
    _engine = engine;

    _currentLanguage = askLocalLanguage();
    loadLanguage();
}

Translator::RobinLanguage Translator::askLocalLanguage() const
{
    QLocale locale;
    return locale.language();
}

void Translator::loadLanguage()
{
    QLocale locale(_currentLanguage);
    if(locale.language() == RobinLanguage::English)
    {
        if(_appTranslator)
            qApp->removeTranslator(_appTranslator);

        if(_qtTranslator)
            qApp->removeTranslator(_qtTranslator);
    }
    else
    {
        if(_appTranslator)
            qApp->removeTranslator(_appTranslator);

        if(_qtTranslator)
             qApp->removeTranslator(_qtTranslator);

        _appTranslator = new QTranslator();
        _qtTranslator = new QTranslator();

        qDebug() << "load Qt translator:" << locale.name()
                 << _qtTranslator->load(locale, "qt", "_", ":/");
        QCoreApplication::installTranslator(_qtTranslator);

        qDebug() << "load app translator:" << locale.name()
                 << _appTranslator->load(locale.name()+".qm");
        QCoreApplication::installTranslator(_appTranslator);
    }

    //_engine->retranslate();

    emit languageChanged();
}

void Translator::setLanguage(RobinLanguage language)
{
    _currentLanguage = language;
    loadLanguage();
}

