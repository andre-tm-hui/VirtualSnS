#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "passthrough.h"
#include "player.h"
#include "recorder.h"
#include <QCheckBox>
#include <nlohmann/json.hpp>
using namespace nlohmann;

// struct containing all settings related to a keybind
typedef struct{
    int type;
    bool recordInput;
    bool recordLoopback;
    bool padAudio;

    int fxType;

    float roomsize;
    float damp;
    float width;
    float wet;
    float dry;
} keybind;

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    std::map<std::string, int> deviceList;
    std::map<std::string, int> apiMap;
    std::map<std::string, device> inputDevices;
    std::map<std::string, device> outputDevices;
    std::map<std::string, device> loopbackDevices;

    int inputDevice, outputDevice, loopbackDevice, virtualInputDevice, virtualOutputDevice;

    void ResetInputRecorder();
    void ResetLoopbackRecorder();
    void ResetPassthrough();
    void ResetPlayer();
    void ResetMonitor();
    void Reset(int input, int output, int loopback, int vInput, int vOutput);

    void Rebind(int keycode);
    void SetNewBind(int keycode, bool isSoundboard);
    void RemoveBind(int keycode);
    void SaveBinds();
    void SetCheckboxes(std::map<std::string, QCheckBox*> *checkboxes);
    void OverrideConfig(std::string keycode);
    void OverrideSound(std::string fname, int keycode);

    void WaitForReady();

    Recorder *inputDeviceRecorder, *loopbackRecorder;
    Passthrough *passthrough;
    Player *player, *monitor;
    std::map<int, keybind> keybinds;
    json soundboardHotkeys;
    json voiceFXHotkeys;

    bool recording = false;

private:
    std::map<std::string, QCheckBox*> *checkboxes;
    int sampleRate, framesPerBuffer;
    int rebindAt = -1;

    std::string appdata;
    std::string dirName = "/Virtual SoundTool/";

    std::map<std::string, int> settings;

    void SaveSettings();

    device GetDeviceByIndex(int i);
    void GetDeviceSettings();

    json baseSoundboardHotkey = R"(
        {
            "label": "",
            "recordInput": true,
            "recordLoopback": true,
            "syncStreams": true
        }
        )"_json;

    json baseFXHotkey = R"(
        {
            "label": "",
            "reverb": { "enabled": false, "roomsize": 0.5, "mix": 0.5, "width": 0.5, "damp": 0.5 },
            "autotune": { "enabled": false, "speed": 0.5 },
            "pitch": { "enabled": false, "pitch": 1.0 }
        }
        )"_json;
};

#endif // AUDIOMANAGER_H
