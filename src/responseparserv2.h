#ifndef RESPONSEPARSERV2_H
#define RESPONSEPARSERV2_H

#include "responseparser.h"

class ResponseParserV2 : public ResponseParser
{
public:
   ResponseParserV2(ChorusDevice* device);
   void parse(QString cmd) override;
   ~ResponseParserV2() override;
};

#endif // RESPONSEPARSERV2_H
