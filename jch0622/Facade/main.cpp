#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>

class Codec
{
public:
    Codec()
    {
        std::cout << "Codec is created." << std::endl;
    };
};

class OggCompressionCodec : public Codec
{
public:
    OggCompressionCodec()
    {
        std::cout << "OggCompressionCodec is created." << std::endl;
    };
};

class MPEG4CompressionCodec : public Codec
{
public:
    MPEG4CompressionCodec()
    {
        std::cout << "MPEG4CompressionCodec is created." << std::endl;
    };

};

class VideoFile
{
    public:
    std::string m_filename;
public:
    VideoFile(const std::string& filename) : m_filename(filename)
    {
        std::cout << m_filename << " is created." << std::endl;
    };
};

class AudioMixer
{
public:
    static std::vector<uint8_t> Fix(const std::vector<uint8_t>& buffer)
    { 
        std::cout << "AudioMixer::Fix is called." << std::endl;
        return {}; 
    }
};

class BitrateReader
{
public:
    static std::vector<uint8_t> Read(const std::string& filename, const Codec& codec)
    {
        std::cout << "BitrateReader::Read is called." << std::endl;
        return {};
    }

    static std::vector<uint8_t> Convert(const std::vector<uint8_t>& buffer, const Codec& codec)
    {
        std::cout << "BitrateReader::Convert is called." << std::endl;
        return {};
    }
};

class CodecFactory
{
public:
    static std::unique_ptr<Codec> Extract(const VideoFile& file)
    {
        std::cout << "CodecFactory::Extract is called." << std::endl;
        return std::make_unique<OggCompressionCodec>();
    }
};


class VideoConverter
{
public:
    std::vector<uint8_t> ConvertVideo(const std::string& filename, const std::string& format)
    {
        // file read -> VideoFile
        // current format -> CodecFactory
        // convert format -> Ogg or MPEG class
        // data read, convert -> Bitrate
        // sound fix -> AudiooMixer

        VideoFile file(filename);
        auto sourceCodec = CodecFactory::Extract(file);

        std::unique_ptr<Codec> destCodec;
        if (format == "mp4")
            destCodec = std::make_unique<MPEG4CompressionCodec>();
        else
            destCodec = std::make_unique<OggCompressionCodec>();

        auto buffer = BitrateReader::Read(filename, *sourceCodec);
        auto result = BitrateReader::Convert(buffer, *destCodec);
        result = AudioMixer::Fix(result);
        return result;
    }
};
int main()
{
    VideoConverter converter;
    auto mp4Convert = converter.ConvertVideo("cherry_blossom_in_pangyo.ogg", "mp4");

    std::ofstream output("cherry_blossom_in_pangyo.mp4", std::ios::binary);
    output.write(reinterpret_cast<const char*>(mp4Convert.data()), mp4Convert.size());
}

/*
// output
cherry_blossom_in_pangyo.ogg is created.
CodecFactory::Extract is called.
Codec is created.
OggCompressionCodec is created.
Codec is created.
MPEG4CompressionCodec is created.
BitrateReader::Read is called.
BitrateReader::Convert is called.
AudioMixer::Fix is called.
*/