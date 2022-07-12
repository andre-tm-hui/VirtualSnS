#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "passthrough.h"
#include "player.h"
#include "recorder.h"

// struct containing all settings related to a keybind
typedef struct{
    bool recordInput;
    bool recordLoopback;
    bool padAudio;
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

    int inputDevice, outputDevice, loopbackDevice, virtualInputDevice;

    void ResetInputRecorder();
    void ResetLoopbackRecorder();
    void ResetPassthrough();
    void ResetPlayer();
    void ResetMonitor();
    void Reset();

    void Rebind(int keycode);
    void SetNewBind(int keycode);
    void RemoveBind(int keycode);
    void SaveBinds();

    Recorder *inputDeviceRecorder, *loopbackRecorder;
    Passthrough *passthrough;
    Player *player, *monitor;
    std::map<int, keybind> keybinds;
    bool recording = false;

private:
    int sampleRate, framesPerBuffer, rebindAt;

    std::string appdata;
    std::string dirName = "/Virtual Soundboard and Sampler/";

    std::map<std::string, int> settings;

    void SaveSettings();

    device GetDeviceByIndex(int i);
};

#endif // AUDIOMANAGER_H
