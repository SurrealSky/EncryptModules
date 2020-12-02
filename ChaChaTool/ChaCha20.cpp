#include "stdafx.h"
#include "ChaCha20.h"

#ifdef _DEBUG
#pragma comment(lib,"\\debug\\v142\\dynamic\\libsodium.lib")
#else
#pragma comment(lib,"\\release\\v142\\dynamic\\libsodium.lib")
#endif

ChaCha20::ChaCha20(const char* _type)
{
	if (strcmp("SALSA20", _type) == 0)
	{
		type = CIPHER_SALSA20;
		key_size = crypto_stream_salsa20_KEYBYTES;
		iv_size = crypto_stream_salsa20_NONCEBYTES;
	}
	else if (strcmp("CHACHA20", _type) == 0)
	{
		type = CIPHER_CHACHA20;
		key_size = crypto_stream_chacha20_KEYBYTES;
		iv_size = crypto_stream_chacha20_NONCEBYTES;
	}
	else if (strcmp("XSALSA20", _type) == 0)
	{
		type = CIPHER_XSALSA20;
		key_size = crypto_stream_xsalsa20_KEYBYTES;
		iv_size = crypto_stream_xsalsa20_NONCEBYTES;
	}
	else if (strcmp("XCHACHA20", _type) == 0)
	{
		type = CIPHER_XCHACHA20;
		key_size = crypto_stream_chacha20_KEYBYTES;
		iv_size = crypto_stream_xchacha20_NONCEBYTES;
	}
	else if (strcmp("CHACHA20_IETF", _type) == 0)
	{
		type = CIPHER_CHACHA20_IETF;
		key_size = crypto_stream_chacha20_ietf_KEYBYTES;
		iv_size = crypto_stream_chacha20_ietf_NONCEBYTES;
	}
	memset(key,0,sizeof(key));
	memset(iv, 0, sizeof(iv));
	ic = 0x21;
}


ChaCha20::~ChaCha20()
{
}

std::string ChaCha20::Getsodium_version()
{
	const char *p = sodium_version_string();
	std::string ss;
	ss.append(p, strlen(p));
	return ss;
}

void ChaCha20::InitCipher(const unsigned char *k, const unsigned int len1,const unsigned char *n,const unsigned int len2)
{
	if(len1>sizeof(key))
		memcpy(key, k, sizeof(key));
	else
		memcpy(key, k, len1);
	if(len2>sizeof(iv))
		memcpy(iv, n, sizeof(iv));
	else
		memcpy(iv, n, len2);
}

void ChaCha20::Encrypt(unsigned char *srcBuffer, unsigned long long srcLen, unsigned char **dstBuffer, unsigned long long &dstLen)
{
	*dstBuffer = (unsigned char*)malloc(srcLen);
	dstLen = srcLen;

	switch (type)
	{
		case CIPHER_SALSA20:
			{
				//encryptor_delegate = Sodium.crypto_stream_salsa20_xor_ic;
				crypto_stream_salsa20_xor_ic(*dstBuffer,srcBuffer, srcLen, iv, ic, key);
			}
			break;
		case CIPHER_CHACHA20:
			{
				//encryptor_delegate = Sodium.crypto_stream_chacha20_xor_ic;
				crypto_stream_chacha20_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
			}
			break;
		case CIPHER_XSALSA20:
			{
				//encryptor_delegate = Sodium.crypto_stream_xsalsa20_xor_ic;
				crypto_stream_xsalsa20_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
			}
			break;
		case CIPHER_XCHACHA20:
			{
				//encryptor_delegate = Sodium.crypto_stream_xchacha20_xor_ic;
				crypto_stream_xchacha20_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
			}
			break;
		case CIPHER_CHACHA20_IETF:
			{
				//encryptor_delegate = crypto_stream_chacha20_ietf_xor_ic;
				crypto_stream_chacha20_ietf_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
			}
			break;
	}
	//if (crypto_aead_chacha20poly1305_encrypt(*dstBuffer, &dstLen,
	//	srcBuffer, srcLen,
	//	0, 0,
	//	NULL, iv, key) != 0)
	//{
	//	/* message forged! */
	//}
}

void ChaCha20::Decrypt(unsigned char *srcBuffer, unsigned long long srcLen, unsigned char **dstBuffer, unsigned long long &dstLen)
{
	*dstBuffer = (unsigned char*)malloc(srcLen);
	dstLen = srcLen;
	switch (type)
	{
	case CIPHER_SALSA20:
	{
		//encryptor_delegate = Sodium.crypto_stream_salsa20_xor_ic;
		crypto_stream_salsa20_xor_ic(*dstBuffer,srcBuffer, srcLen, iv, ic, key);
	}
	break;
	case CIPHER_CHACHA20:
	{
		//encryptor_delegate = Sodium.crypto_stream_chacha20_xor_ic;
		crypto_stream_chacha20_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
	}
	break;
	case CIPHER_XSALSA20:
	{
		//encryptor_delegate = Sodium.crypto_stream_xsalsa20_xor_ic;
		crypto_stream_xsalsa20_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
	}
	break;
	case CIPHER_XCHACHA20:
	{
		//encryptor_delegate = Sodium.crypto_stream_xchacha20_xor_ic;
		crypto_stream_xchacha20_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
	}
	break;
	case CIPHER_CHACHA20_IETF:
	{
		//encryptor_delegate = crypto_stream_chacha20_ietf_xor_ic;
		crypto_stream_chacha20_ietf_xor_ic(*dstBuffer, srcBuffer, srcLen, iv, ic, key);
	}
	break;
	}
	//if (crypto_aead_chacha20poly1305_decrypt(*dstBuffer, &dstLen,
	//	NULL,
	//	srcBuffer, srcLen,
	//	0,
	//	0,
	//	iv, key) != 0) {
	//	/* message forged! */
	//}

}

void ChaCha20::DecryptAndNoVerify(unsigned char *srcBuffer, unsigned long long srcLen, unsigned char **dstBuffer, unsigned long long &dstLen)
{
	*dstBuffer = (unsigned char*)malloc(srcLen);

	if (srcLen < crypto_aead_chacha20poly1305_ABYTES) {
		return;
	}
	crypto_stream_chacha20_xor_ic
		(*dstBuffer, srcBuffer, srcLen - crypto_aead_chacha20poly1305_ABYTES, iv, 1U, key);
	dstLen = srcLen - crypto_aead_chacha20poly1305_ABYTES;

}

void ChaCha20::_u64_le_from_ull(unsigned char out[8U], unsigned long long x)
{
	out[0] = (unsigned char)(x & 0xff); x >>= 8;
	out[1] = (unsigned char)(x & 0xff); x >>= 8;
	out[2] = (unsigned char)(x & 0xff); x >>= 8;
	out[3] = (unsigned char)(x & 0xff); x >>= 8;
	out[4] = (unsigned char)(x & 0xff); x >>= 8;
	out[5] = (unsigned char)(x & 0xff); x >>= 8;
	out[6] = (unsigned char)(x & 0xff); x >>= 8;
	out[7] = (unsigned char)(x & 0xff);
}

void ChaCha20::FreeBuffer(unsigned char **buffer)
{
	if (*buffer != 0)
	{
		free(*buffer);
		*buffer = 0;
	}
}