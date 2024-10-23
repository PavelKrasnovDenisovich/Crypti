#include <iostream>
#include <cstdlib> // для функций strtol, exit
#include <unistd.h> // для функции getopt
#include <string>
#include "interface.h"
#include <fstream>
#include <map>
#include <exception>
// реализация интерфейса в виде класса
using namespace std;

Opts::Opts(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "k:o:m:f:h")) != -1) {
        switch (opt) {
        case 'k':
            key = string(optarg);
            break;
        case 'o':
            orig_file = string(optarg);
            break;
        case 'm':
            mode = string(optarg);
            if (mode == "e"){
            	encrypt = true;}
            else if (mode == "d"){
            	decrypt = true;
            } else usage(argv[0]);
            break;
        case 'f': // file
            crypto_file = string(optarg);
            break;  
        case 'h': // -h help
        case '?': // неверный параметр
        case ':': // нет значения у параметра
            usage(argv[0]); // сообщить и завершить
        }
    }
    
    if (orig_file == "")
    	{usage(argv[0]);}
	if (key == "")
		{usage(argv[0]);}
	if ((!encrypt)&&(!decrypt))
		{usage(argv[0]);}
    
}

void Opts::usage(const char* progName)
{
    std::cout<<"Usage: "<<progName<<" -k Password -o Original_file -f Encrypted/Decrypted_file -m e|d \n";
    exit(1);
}

bool Opts::CheckFiles()
{
    try {
        std::ifstream o_file(orig_file);
        if (o_file.bad()) {
            throw std::invalid_argument("what");
        }
    } catch(std::invalid_argument err) {
        cout<<err.what()<<std::endl;
        exit(1);
    }
    return true;
}
