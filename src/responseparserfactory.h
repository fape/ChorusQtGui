#ifndef RESPONSEPARSERFACTORY_H
#define RESPONSEPARSERFACTORY_H

#include <memory>
#include "chorusdevice.h"
#include "responseparser.h"

class ResponseParserFactory
{
private:
    ResponseParserFactory();
public:
    static std::unique_ptr<ResponseParser> create(ChorusDevice * device);
};

#endif // RESPONSEPARSERFACTORY_H
