#include "WavFileManager.h"

using namespace std;

int main()
try
{
    auto* mgr = new WavFileManager();
    auto wav = mgr->ReadAll("C:/Users/Beton-kun/source/repos/AudioEffectsLibrary/AudioEffectsLibrary/x64/Debug/input.wav");
    mgr->WriteAll(wav, "C:/Users/Beton-kun/source/repos/AudioEffectsLibrary/AudioEffectsLibrary/x64/Debug/output.wav");
}
catch (runtime_error& e)
{
    cerr << "Error! " << e.what() << '\n';
}