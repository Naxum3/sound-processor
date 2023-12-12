#include "handler.h"
#include "parser.h"
bool sstream::strCompr(const char* f, const char* s)
{
    for (int i = 0; i < 4; i++)
        if (f[i] != s[i])
            return false;
    return true;
}

void sstream::read(std::string filename)
{
    std::ifstream in(filename, std::ios::binary | std::ios::in);
    if (in.fail())
        throw std::exception("File not found");

    in.read((char*)&header, sizeof(WAVHEADER));

    if (!strCompr(header.chunkId, "RIFF"))
        throw std::exception("File is not supported");

    if (!strCompr(header.format, "WAVE"))
        throw std::exception("File is not supported");

    if (!strCompr(header.subchunk1Id, "fmt "))
        throw std::exception("File is not supported");

    if (header.subchunk1Size != 16)
        throw std::exception("File is not supported");

    if (header.audioFormat != 1)
        throw std::exception("File is not supported");

    if (header.numChannels != 1)
        throw std::exception("File is not supported");

    if (header.sampleRate != 44100)
        throw std::exception("File is not supported");

    if (header.byteRate != 88200)
        throw std::exception("File is not supported");

    if (header.blockAlign != 2)
        throw std::exception("File is not supported");

    if (header.bitsPerSample != 16)
        throw std::exception("File is not supported");

    if (strCompr(header.subchunk2Id, "LIST"))
    {
        int skip;
        in.read((char*)&skip, 4);
        for (int i = 0; i < skip; i++)
            in.read((char*)&skip, 1);
        in.read(header.subchunk2Id, 4);
    }
    if (!strCompr(header.subchunk2Id, "data"))
        throw std::exception("File is not supported");

    length = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;

    signals.clear();
    int data_cnt = header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels;
    for (int i = 0; i < data_cnt; i++)
    {
        signals.push_back(0);
        in.read((char*)&(signals.back()), 2);
    }
    in.close();
}

void sstream::save(std::string filename)
{
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    out.write((char*)&header, sizeof(WAVHEADER));
    for (short i : signals)
        out.write((char*)&i, 2);
    out.close();
}

void getFilesList(int argc, char** argv) {
    sstream res;
    std::vector<std::string> files;
    if (argc == 2 && (std::string)argv[1] == "-h") {
        std::cout << "sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> …]";
        exit(0);
    }
    if (argc > 4 && (std::string)argv[1] == "-c")
    {
        std::ifstream conf(argv[2]);
        if (!conf.is_open())
            throw std::exception("No config file");

        res.read(argv[4]);

        for (int i = 5; i < argc; i++)
            files.push_back(argv[i]);

        use_cnf(conf, &res,files);
        res.save(argv[3]);
        exit(0);
    }
    throw std::exception("Wrong command, print -h for help");
};
