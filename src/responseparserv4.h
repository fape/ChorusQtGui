#ifndef RESPONSEPARSERV4_H
#define RESPONSEPARSERV4_H

#include "responseparser.h"

class ResponseParserV4 : public ResponseParser
{
public:
   ResponseParserV4(ChorusDevice* device);
   void parse(QString cmd) override;
   ~ResponseParserV4() override;
};

#endif // RESPONSEPARSERV4_H
