#include <iostream>
#include <string>

#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/des.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hmac.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>

#include "cipher.h"


cipher::cipher(std::string o_file, std::string key){
orig_file = o_file.c_str();
pwd = key;
}

using namespace CryptoPP;

void cipher::encrypt()
{
    try {
    	CryptoPP::AutoSeededRandomPool prng;
    	CryptoPP::byte key[CryptoPP::DES::DEFAULT_KEYLENGTH];
    	
    	ArraySink as(key, sizeof(key));
    	
    	Weak::MD5 hash;
    	StringSource(pwd, true, new HashFilter(hash, new Redirector(as)));
    	
        CryptoPP::StringSource (key, sizeof(key), true,
                                new CryptoPP::HexEncoder(
                                    new CryptoPP::FileSink(enc_key_file)));
        std::cout << "Key generated and stored to file " << enc_key_file << std::endl;
        // generate random IV (not secret)
        CryptoPP::byte iv[CryptoPP::DES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));
        // save IV to iv_file in hex format
        CryptoPP::StringSource(iv, sizeof(iv), true,
                               new CryptoPP::HexEncoder(
                                   new CryptoPP::FileSink(iv_file)));
        std::cout << "IV generated and stored to file " << iv_file << std::endl;

        // encryption

        // cipher DES in CBC mode for encryption: encr
        CryptoPP::CBC_Mode<CryptoPP::DES>::Encryption encr;
        // set IV and Key to cipher
        encr.SetKeyWithIV(key, sizeof(key), iv );
        // read from orig_file -> encrypt -> save to encr_file
        CryptoPP::FileSource (orig_file, true,
                              new CryptoPP::StreamTransformationFilter(encr,
                                      new CryptoPP::FileSink(encr_file)));
        std::cout << "File " << orig_file << " encrypted and stored to " << encr_file << std::endl;

    } catch( const CryptoPP::Exception& e ) {    // catch exception
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

void cipher::decrypt()
{
    try {
    	CryptoPP::byte key[CryptoPP::DES::DEFAULT_KEYLENGTH];
    	
    	ArraySink as(key, sizeof(key));
    	
    	Weak::MD5 hash;
    	StringSource(pwd, true, new HashFilter(hash, new Redirector(as)));
    	
    	CryptoPP::StringSource (key, sizeof(key), true,
                                new CryptoPP::HexEncoder(
                                    new CryptoPP::FileSink(dec_key_file)));
        std::cout << "Key generated and stored to file " << dec_key_file << std::endl;
    

        // read IV from file iv_file
        CryptoPP::byte iv[CryptoPP::DES::BLOCKSIZE];
        CryptoPP::FileSource(iv_file, true,
                             new CryptoPP::HexDecoder(
                                 new CryptoPP::ArraySink(iv, sizeof iv)));
        std::cout << "IV readed from file " << iv_file << std::endl;

        // decryption

        // cipher DES in CBC mode for decryption: decr
        CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption decr;
        // set IV and Key to cipher
        decr.SetKeyWithIV(key, sizeof(key), iv);
        // read from orig_file -> encrypt -> save to encr_file
        std::cout << "decr_file " << decr_file << std::endl;
        CryptoPP::FileSource (orig_file, true,
                              new CryptoPP::StreamTransformationFilter(decr,
                                      new CryptoPP::FileSink(decr_file)));
        std::cout << "File " << orig_file << " decrypted and stored to " << decr_file << std::endl;

    } catch( const CryptoPP::Exception& e ) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
