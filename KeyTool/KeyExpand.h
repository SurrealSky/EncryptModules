#pragma once
#include<string>


namespace CipherKey
{
	class CKeyExpand
	{
	public:
		CKeyExpand();
		~CKeyExpand();
	public:
		unsigned int GetAesKeyLen(unsigned int bits);
		unsigned int GetDesKeyLen();
		void GetKey_AES(unsigned char *userkey, unsigned int keylen,unsigned int bits, bool isEnc,unsigned char *buffer, unsigned int *len);
		void GetKey_DES(unsigned char *userkey, unsigned int keylen, bool isEnc, unsigned char *buffer, unsigned int *len);
		//�������ݻ�ԭ(128)
		bool GetAesKeyFromExpand(unsigned char *RoundKey, unsigned int *len,unsigned int bits,bool isEnc, unsigned char *userkey);
		//����0x10,0x18,0x20���ݻ�ԭ
		bool GetAesKeyFromExpand128(unsigned char *RoundKey, unsigned int *len, unsigned int bits, bool isEnc, unsigned char *userkey);
		//����0x10,0x18,0x20���ݻ�ԭ
		bool GetAesKeyFromExpand192(unsigned char *RoundKey, unsigned int *len, unsigned int bits, bool isEnc, unsigned char *userkey);
		//����0x10,0x18,0x20���ݻ�ԭ
		bool GetAesKeyFromExpand256(unsigned char *RoundKey, unsigned int *len, unsigned int bits, bool isEnc, unsigned char *userkey);
		//����ɢ������Կ�任Ϊ��ɢ������Կ
		void DecKeyEd2EncKeyEd(unsigned char *dec, unsigned int bits, unsigned int *enc);
	private:
		unsigned char getSBoxValue(unsigned char c);
		unsigned char getRSBoxValue(unsigned char c);
	public:
		static std::string GetSSLeay_version();
	};
}


