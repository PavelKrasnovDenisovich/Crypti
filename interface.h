#pragma once
#include <string>
#include <map>

using namespace std;

class Opts
{
private:
    void usage(const char* progName);
public:
	std::string orig_file = "";
	std::string crypto_file = "NotSet";
	std::string key = "";
	std::string mode;
	bool encrypt = false;
	bool decrypt = false;
    Opts(int argc, char **argv);
    bool CheckFiles();
};
