#include"stdafx.h"
#include "DesCrypt.h"
#include<Windows.h>
#include<time.h>

using namespace CipherDes;

#ifdef _DEBUG
#pragma comment(lib,"ssleay32MDd.lib")
#pragma comment(lib,"libeay32MDd.lib")
#else
#pragma comment(lib,"ssleay32MD.lib")
#pragma comment(lib,"libeay32MD.lib")
#endif

CDesCrypt::CDesCrypt(CipherMode m) :mode(m)
{
}


CDesCrypt::~CDesCrypt(void)
{
}


std::string CDesCrypt::GetSSLeay_version()
{
	const char *p = SSLeay_version(SSLEAY_VERSION);
	std::string ss;
	ss.append(p, strlen(p));
	return ss;
}

void CDesCrypt::SetKey(unsigned char *sid,unsigned int len)
{
	if (is3des)
	{
		//3des
		DES_cblock block[3];
		memset(block, 0, sizeof(block));
		if (len > sizeof(block)) len = sizeof(block);
		memcpy(block, sid, len);
		DES_set_key(&block[0], &sched1);
		DES_set_key(&block[1], &sched2);
		DES_set_key(&block[2], &sched3);
	}
	else
	{
		//des
		DES_cblock block;
		memset(block, 0, sizeof(block));
		if (len > sizeof(block)) len = sizeof(block);
		memcpy(block, sid, len);
		DES_set_key(&block, &sched1);
	}
}

void CDesCrypt::SetIv(unsigned char *iv,unsigned int len)
{
	//des
	memset(ivec, 0, sizeof(ivec));
	if (len>sizeof(ivec)) len = sizeof(ivec);
	memcpy(ivec, iv, len);
}

void CDesCrypt::Encrypt(unsigned char *src,unsigned int slen,unsigned char *dst)
{
	switch(mode)
	{
	case MODE_ECB:
		{
			for (unsigned int i = 0; i<slen / block_size; i++)
			{
				const_DES_cblock inputText;  
				DES_cblock outputText;
				memcpy(inputText, src + i * block_size, block_size);
				if(is3des)
					DES_ecb3_encrypt(&inputText, &outputText, &sched1, &sched2, &sched3, DES_ENCRYPT);
				else
					DES_ecb_encrypt(&inputText, &outputText, &sched1, DES_ENCRYPT);
				memcpy(dst + i*block_size, outputText, block_size);
			}
		}break;
	case MODE_CBC:
		{
			if(is3des)
			{
				for (unsigned int i = 0; i<slen / block_size; i++)
				{
					DES_ede3_cbc_encrypt(src+i*block_size, dst+i*block_size, slen,&sched1, &sched2, &sched3, &ivec, DES_ENCRYPT);
				}
			}else
				DES_ncbc_encrypt(src,dst,slen,&sched1,&ivec, DES_ENCRYPT);
		}break;
	}
}

void CDesCrypt::Decrypt(unsigned char *src,unsigned int slen,unsigned char *dst)
{
	switch(mode)
	{
	case MODE_ECB:
		{
			for (unsigned int i = 0; i<slen / block_size; i++)
			{
				const_DES_cblock inputText;  
				DES_cblock outputText;
				memcpy(inputText, src + i * block_size, block_size);
				if(is3des)
					DES_ecb3_encrypt(&inputText, &outputText, &sched1, &sched2, &sched3, DES_DECRYPT);
				else
					DES_ecb_encrypt(&inputText, &outputText, &sched1, DES_DECRYPT);
				memcpy(dst + i*block_size, outputText, block_size);
			}
		}break;
	case MODE_CBC:
		{
			if (is3des)
			{
				DES_ede3_cbc_encrypt(src, dst, slen, &sched1, &sched2, &sched3, &ivec, DES_DECRYPT);
			}
			else
				DES_ncbc_encrypt(src,dst,slen,&sched1,&ivec, DES_DECRYPT);
		}break;
	}		
}