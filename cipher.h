#include <iostream>
#include <string>

#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/des.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>

class cipher{
private:
const char * orig_file;
const char * encr_file = "encr_file.bin";
const char * decr_file = "decr_file.txt";
const char * iv_file = "iv.hex";
const char * enc_key_file = "ekey.hex";
const char * dec_key_file = "dkey.hex";
std::string pwd;
public:
cipher(std::string o_file, std::string key);
void setEncrFile(std::string EFName){encr_file = EFName.c_str();}
void setDecrFile(std::string DFName){decr_file = DFName.c_str();}
void encrypt();
void decrypt();
};
