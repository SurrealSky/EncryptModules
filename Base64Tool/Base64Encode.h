#pragma once
#include<string>


namespace CipherBase64
{
	class CBase64Encode
	{
	public:
		CBase64Encode();
		~CBase64Encode();
	public:
		std::string base64Encode(const char *buffer, int length, bool newLine);
		std::string base64Decode(char *input, int length, bool newLine);
	};
}


