#include "responseparserfactory.h"

#include "responseparserv2.h"
#include "responseparserv4.h"
#include "responseparserdefault.h"

ResponseParserFactory::ResponseParserFactory()
{

}

std::unique_ptr<ResponseParser> ResponseParserFactory::create(ChorusDevice * device) {

    switch (device->api()) {
    case 2:
        return std::make_unique<ResponseParserV2>(device);
    case 4:
        return std::make_unique<ResponseParserV4>(device);
    default:
       return std::make_unique<ResponseParserDefault>(device);
    }
}
