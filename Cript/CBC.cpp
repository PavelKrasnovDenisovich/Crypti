#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include <string>
#include <fstream>
#include <random>
#include <sstream>
#include <iomanip>
#include "interface.h"
#include "cipher.h"

using namespace std;


int main(int argc, char **argv)
{
Opts op(argc, argv);
op.CheckFiles();
cipher cip(op.orig_file, op.key);
if (op.encrypt){
	if (op.crypto_file != "NotSet"){
	cip.setEncrFile(op.crypto_file);}
	cip.encrypt();}
if (op.decrypt){
	if (op.crypto_file != "NotSet"){
	cip.setDecrFile(op.crypto_file);
	cout<<"decrfile"<<(op.crypto_file)<<endl;}
	cip.decrypt();}
}
