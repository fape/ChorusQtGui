#include "speechinfoholder.h"

SpeechInfoHolder::SpeechInfoHolder(){
}

SpeechInfoHolder::~SpeechInfoHolder(){

}

SpeechInfoHolder::SpeechInfoHolder(const SpeechInfoHolder &other){
    m_locale = other.m_locale;
    m_voice = other.m_voice;
}

SpeechInfoHolder::SpeechInfoHolder(const QLocale& locale,  const QVoice& voice)
{
    m_locale = locale;
    m_voice = voice;
}

QLocale SpeechInfoHolder::locale() const {
    return m_locale;
}

QVoice SpeechInfoHolder::voice() const {
    return m_voice;
}
