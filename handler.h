#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
struct WAVHEADER
{
    // WAV-формат начинается с RIFF-заголовка:

    //"RIFF"
    char chunkId[4];

    // 36 + subchunk2Size, или более точно:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    unsigned long chunkSize;

    //"WAVE"
    char format[4];

    // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
    // Подцепочка "fmt " описывает формат звуковых данных:

    // Содержит символы "fmt "
    char subchunk1Id[4];

    // 16 для формата PCM.
    unsigned long subchunk1Size;

    // Для PCM = 1 (то есть, Линейное квантование).
    unsigned short audioFormat;

    // Количество каналов.
    unsigned short numChannels;

    // Частота дискретизации.
    unsigned long sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    unsigned long byteRate;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    unsigned short blockAlign;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    unsigned short bitsPerSample;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    char subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    unsigned long subchunk2Size;
};
class sstream
{
private:
    bool strCompr(const char*, const char*);
public:
    std::vector<short int> signals;
    void read(std::string);
    float length = 0;
    WAVHEADER header = {};
    void save(std::string);
};
void getFilesList(int argc, char** argv);