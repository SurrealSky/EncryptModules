#pragma once
#include<string>
#include<vector>

//char username[] = "SAM//SAM//Domains//Account//Users//Names//administrator";
//unsigned char passwordtype[5][100] = { "LMPASSWORD","NTPASSWORD","LMPASSWORDHISTORY","NTPASSWORDHISTORY","MISCCREDDATA" };

typedef struct _SamInfo
{
    std::string user_V;
}SamInfo,*PSamInfo;

class SamDecrypt
{
private:
    unsigned long uid = 0x1F4;
    unsigned char syskey[0x10];
    unsigned char ensamnt[0x10];
    unsigned char ensamlm[0x10];
    unsigned char sessionkey[0x10];
    unsigned char buf[0x400];
    unsigned char sampsecretsessionkey[0x10];
    unsigned char lmhash[0x10];
    unsigned char nthash[0x10];
    unsigned char fkey[0x30];
    unsigned long ss;
    DWORD regtype;
    DWORD regint;
public:
    SamInfo samInfo;
public:
    SamDecrypt();
public:
    std::string getidname(std::string _V);
    std::string getensamnt(std::string _V);
    std::string getensamlm(std::string _V);
    std::string getsyskey(std::string _JD,std::string _Skew1,std::string _GBG,std::string _Data);
};

