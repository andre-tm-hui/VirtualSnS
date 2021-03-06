#ifndef PASSTHROUGH_H
#define PASSTHROUGH_H

#include <QCheckBox>
#include "audiostream.h"
#include "nlohmann/json.hpp"
using namespace nlohmann;

class Passthrough : public AudioStream
{
public:
    Passthrough(device inputDevice,
                device outputDevice,
                int sampleRate,
                int framesPerBuffer);

    ~Passthrough()
    {
        delete data.reverb;
        delete data.ps;
    }

    void SetFX(json settings);

    std::map<std::string, QCheckBox*> *checkboxes;
};

#endif // PASSTHROUGH_H
