#pragma once
#include"openssl//aes.h"
#include"../CommonLib/include/BinaryPadding.h"
#include <string>

//AES�����鳤�ȹ̶�Ϊ128 ���أ���Կ�����������128��192��256���أ�
//����ʱʹ�õ�����Կ˳�������ʱ�෴(����������Կ������ͬ)������ʹ��ͬ��������Կ��
//CFB��OFB��CTRģʽ�н���Ҳ�����õļ��������ǽ�����,��������Կͬ��ʹ��AES_set_encrypt_key����

namespace CipherAes
{
	enum CipherMode
	{
		MODE_ECB,
		MODE_CBC,
		MODE_CTR,
		MODE_OFB,
		MODE_CFB
	};

	enum KeyMode
	{
		MODE_128,
		MODE_192,
		MODE_256
	};

	class CAesCrypt :public CBinaryPadding
	{
	public:
		CAesCrypt(CipherMode = MODE_ECB);
		~CAesCrypt(void);
	private:
		AES_KEY			key1;
		AES_KEY			key2;
		unsigned char	ivec[AES_BLOCK_SIZE];
		CipherMode			cMode;
	private:
		const unsigned int block_size = AES_BLOCK_SIZE;
		virtual const unsigned int GetBlockSize(){ return block_size; };
		void SetEncKey(AES_KEY&, unsigned char *sid, unsigned int len);
		void SetDecKey(AES_KEY&, unsigned char *sid, unsigned int len);
		void SetIv(unsigned char *iv, unsigned int len);
	public:
		static std::string GetSSLeay_version();
		void initMode(CipherMode cm, KeyMode km, unsigned char *key, unsigned int kenlen, unsigned char *iv, unsigned int ivlen);
		void Encrypt(unsigned char *, unsigned int, unsigned char*);
		void Decrypt(unsigned char *, unsigned int, unsigned char*);
	};
}


