#include "WavFileManager.h"
#include "SampleDataManager.h"

using namespace std;

int main()
try
{
    auto fileManager = new WavFileManager();
    auto sampleManager = new SampleDataManager();

    auto wav = fileManager->ReadAll("C:/source/repos/AudioEffectsLibrary/AudioEffectsLibrary/x64/Debug/input.wav");

    auto samples = sampleManager->UnpackAll(wav.Data);

    wav.Data = sampleManager->PackAll(samples);

    fileManager->WriteAll(wav, "C:/source/repos/AudioEffectsLibrary/AudioEffectsLibrary/x64/Debug/output.wav");
}
catch (runtime_error& e)
{
    cerr << "Error! " << e.what() << '\n';
}