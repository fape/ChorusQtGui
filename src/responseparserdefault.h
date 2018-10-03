#ifndef RESPONSEPARSERDEFAULT_H
#define RESPONSEPARSERDEFAULT_H

#include "responseparser.h"

class ResponseParserDefault : public ResponseParser
{
public:
   ResponseParserDefault(ChorusDevice* device);
   void parse(QString cmd) override;
   ~ResponseParserDefault() override;
};

#endif // RESPONSEPARSERDEFAULT_H
