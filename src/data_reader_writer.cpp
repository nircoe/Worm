#include "data_management/data_reader_writer.hpp"
#include <fstream>
#include <stdexcept>
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
#include "cryptopp/base64.h"

// Fixed Encryption Key (Warning: This is Insecure, I'm using it for learning purposes only!)
const CryptoPP::byte fixedKey[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

std::string DataReaderWriter::encrypt(const std::string &data)
{
    CryptoPP::AutoSeededRandomPool rng; // random generator
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; // initialization vector (IV)
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE); // generate random IV
    // creating AES Encryption object using the fixed key and the generated IV
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption(fixedKey, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

    std::string ciphertext;
    try
    {
        // will write the output into ciphertext
        CryptoPP::StringSink sink(ciphertext); 
        // will encrypt the data using AES and send the output into the StringSink
        CryptoPP::StreamTransformationFilter filter(encryption, &sink);
        // will take the data and send it through the StreamTransformationFilter, 
        // which will encrypt it with AES and send it to the StringSink and it will write the output into ciphertext
        CryptoPP::StringSource stringsource(data, true, &filter);
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "Encryption Error: " << e.what() << std::endl;
        return "";
    }
    
    // reinterpret the IV byte array as const char array, then create an AES::BLOCKSIZE size string out of it
    std::string ivString(reinterpret_cast<const char*>(iv), CryptoPP::AES::BLOCKSIZE);
    // combine the IV string (not encrypted) with the ciphertext (encrypted)
    std::string combinedData = ivString + ciphertext;

    std::string encoded;
    try
    {
        // will write the output into encoded
        CryptoPP::StringSink sink(encoded);
        // will encode the data into Base64 binary code and send the output into the StringSink
        CryptoPP::Base64Encoder encoder(&sink);
        // will take the combinedData and send it through the Base64Encoder, 
        // which will encode it into Base64 binary code and send it to the StringSink,
        // and it will write the output into encoded
        CryptoPP::StringSource stringsource(combinedData, true, &encoder);
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "Binary Encoding Error: " << e.what() << std::endl;
        return "";
    }
    
    // if we came this far, we succeed :)
    return encoded;
}
std::string DataReaderWriter::decrypt(const std::string &encodedData)
{
    std::string decoded;
    try
    {
        // will write the output into decoded
        CryptoPP::StringSink sink(decoded);
        // will decode the data from Base64 binary code and send the output into the StringSink
        CryptoPP::Base64Decoder decoder(&sink);
        // will take the encodedData and send it through the Base64Decoder, 
        // which will decode it from Base64 binary code and send it to the StringSink,
        // and it will write the output into decoded
        CryptoPP::StringSource stringsource(encodedData, true, &decoder);
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "Binary Decoding Error: " << e.what() << std::endl;
        return "";
    }

    if(decoded.length() <= CryptoPP::AES::BLOCKSIZE) // need to have the IV in it and more info after that
    {
        std::cerr << "Decryption Error: Invalid Encoded Data" << std::endl;
        return "";
    }

    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    // copy the saved IV into byte array
    memcpy(iv, decoded.c_str(), CryptoPP::AES::BLOCKSIZE);
    // extract only the ciphertext out of decoded
    std::string ciphertext = decoded.substr(CryptoPP::AES::BLOCKSIZE);

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption(fixedKey, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

    std::string plaintext;
    try
    {
        // will write the output into plaintext
        CryptoPP::StringSink sink(plaintext); 
        // will decrypt the data using AES and send the output into the StringSink
        CryptoPP::StreamTransformationFilter filter(decryption, &sink);
        // will take the ciphertext and send it through the StreamTransformationFilter, 
        // which will decrypt it with AES and send it to the StringSink and it will write the output into plaintext
        CryptoPP::StringSource stringsource(ciphertext, true, &filter);
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << "Decryption Error: " << e.what() << std::endl;
        return "";
    }

    // if we came this far, we succeed :)
    return plaintext;
}

bool DataReaderWriter::writeData(const GameData &gamedata, const std::string &filename)
{
    std::ofstream file(filename, std::ios::binary);
    if(!file.is_open())
        return false;

    std::string jsonData = gamedata.toJson().dump();

    std::string encryptedData = encrypt(jsonData);
    if(encryptedData.empty()) // the encryption failed
        return false;

    file.write(encryptedData.c_str(), encryptedData.size());
    file.close();
    
    return true;
}

std::optional<GameData> DataReaderWriter::readData(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open())
    {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return std::nullopt;
    }
    // reading the whole file using range iterators (from begin to end, aka the whole file), and writes it into string
    std::string encodedData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::string decryptedData = decrypt(encodedData);
    try 
    {
        json j = json::parse(decryptedData);
        return GameData::fromJson(j);
    }
    catch(const std::exception& e)
    {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        return std::nullopt;
    }
}
