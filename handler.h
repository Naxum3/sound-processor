#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
struct WAVHEADER
{
    // WAV-������ ���������� � RIFF-���������:

    //"RIFF"
    char chunkId[4];

    // 36 + subchunk2Size, ��� ����� �����:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    unsigned long chunkSize;

    //"WAVE"
    char format[4];

    // ������ "WAVE" ������� �� ���� ����������: "fmt " � "data":
    // ���������� "fmt " ��������� ������ �������� ������:

    // �������� ������� "fmt "
    char subchunk1Id[4];

    // 16 ��� ������� PCM.
    unsigned long subchunk1Size;

    // ��� PCM = 1 (�� ����, �������� �����������).
    unsigned short audioFormat;

    // ���������� �������.
    unsigned short numChannels;

    // ������� �������������.
    unsigned long sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    unsigned long byteRate;

    // numChannels * bitsPerSample/8
    // ���������� ���� ��� ������ ������, ������� ��� ������.
    unsigned short blockAlign;

    // ��� ���������� "��������" ��� �������� ��������. 8 ���, 16 ��� � �.�.
    unsigned short bitsPerSample;

    // ���������� "data" �������� �����-������ � �� ������.

    // �������� ������� "data"
    char subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // ���������� ���� � ������� ������.
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