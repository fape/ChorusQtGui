#ifndef SPEECINFOHOLDER_H
#define SPEECINFOHOLDER_H

#include <QObject>
#include <QLocale>
#include <QVoice>

class SpeechInfoHolder
{
public:
    SpeechInfoHolder();
    SpeechInfoHolder(const SpeechInfoHolder &other);
    ~SpeechInfoHolder();
    SpeechInfoHolder(const QLocale& locale, const QVoice& voice);

    QLocale locale() const;
    QVoice voice() const;

private:
    QLocale m_locale;
    QVoice m_voice;
};
Q_DECLARE_METATYPE(SpeechInfoHolder)

#endif // SPEECINFOHOLDER_H
