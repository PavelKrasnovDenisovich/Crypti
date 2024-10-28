#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <string>
#include <fstream>



int main(int argc, char **argv)
{
    using namespace CryptoPP;
	const char * file = "strings.txt";
	std::string strHash;
    Weak::MD5 hash;
    FileSource(file, true, new HashFilter(hash, new HexEncoder(new StringSink (strHash))));
    std::cout<<strHash<<std::endl;
    return 0;
}
