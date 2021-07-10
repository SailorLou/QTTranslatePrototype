#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QLocale>

class QTranslator;
class QQmlEngine;
class Translator:public QObject
{
    Q_OBJECT
public:
    using RobinLanguage = QLocale::Language;

    Translator(QQmlEngine *engine);
    Q_INVOKABLE  void setLanguage(RobinLanguage language);
signals:
    void languageChanged();
private:
    void loadLanguage();
    RobinLanguage askLocalLanguage() const;
private:

    RobinLanguage _currentLanguage;
    QTranslator *_appTranslator;
    QTranslator *_qtTranslator;
    QQmlEngine *_engine;
};

#endif // TRANSLATOR_H
