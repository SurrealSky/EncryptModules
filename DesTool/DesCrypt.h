#pragma once
#include<string>
#include"openssl//des.h"
#include"../CommonLib/include/BinaryPadding.h"

//DES�����鳤�ȹ̶�Ϊ64���أ���ԿҲ��64λ��ʵ���õ���56λ����8��16��24��32��40��48��56��64λ��У��λ��
//ʹ��ÿ����Կ����������1��


namespace CipherDes
{
	enum CipherMode
	{
		MODE_ECB,
		MODE_CBC,
		MODE_CTR,
		MODE_OFB,
		MODE_CFB
	};

	class CDesCrypt :public CBinaryPadding
	{
	public:
		CDesCrypt(CipherMode = MODE_ECB);
		~CDesCrypt(void);
	private:
		DES_key_schedule	sched1;
		DES_cblock			ivec;
		CipherMode				mode;
	private:
		const unsigned int block_size = sizeof(DES_cblock);
		virtual const unsigned int GetBlockSize(){ return block_size; };
	public:
		static std::string GetSSLeay_version();
		void SetMode(CipherMode m){ mode = m; };
		void SetKey(unsigned char *sid, unsigned int len);
		void SetIv(unsigned char *iv, unsigned int len);
		void Encrypt(unsigned char *, unsigned int, unsigned char*);
		void Decrypt(unsigned char *, unsigned int, unsigned char*);
	};
}
