#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

#include "chorusdevice.h"


class ResponseParser
{
protected:
    ChorusDevice * device;
public:
    ResponseParser(ChorusDevice * device);
    virtual void parse(QString cmd) = 0;
    virtual ~ResponseParser();

};

#endif // RESPONSEPARSER_H
