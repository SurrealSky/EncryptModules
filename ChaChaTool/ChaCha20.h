#pragma once
#include<sodium.h>
#include<string>

#define CIPHER_SALSA20  1
#define CIPHER_CHACHA20 2
#define CIPHER_CHACHA20_IETF 3
#define CIPHER_XSALSA20 4 + 1
#define CIPHER_XCHACHA20 4 + 2

class ChaCha20
{
public:
	ChaCha20(const char *_type);
	~ChaCha20();
private:
	unsigned char key[crypto_aead_chacha20poly1305_KEYBYTES];
	unsigned char iv[crypto_aead_chacha20poly1305_KEYBYTES];
	unsigned int ic;
	unsigned int key_size;
	unsigned int iv_size;
	unsigned int type;
public:
	static std::string Getsodium_version();
	void InitCipher(const unsigned char *key, const unsigned int len1,const unsigned char *nonce, const unsigned int len2,unsigned int ic);
	void Encrypt(unsigned char *srcBuffer,unsigned long long srcLen,unsigned char **dstBuffer,unsigned long long &dstLen);
	void Decrypt(unsigned char *srcBuffer, unsigned long long srcLen, unsigned char **dstBuffer, unsigned long long &dstLen);
	void DecryptAndNoVerify(unsigned char *srcBuffer, unsigned long long srcLen, unsigned char **dstBuffer, unsigned long long &dstLen);
	void _u64_le_from_ull(unsigned char out[8U], unsigned long long x);
	void FreeBuffer(unsigned char **buffer);
};

