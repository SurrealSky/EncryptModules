#include "stdafx.h"
#include "Base64Encode.h"
#include <openssl/evp.h>  
#include <openssl/bio.h>  
#include <openssl/buffer.h>    
#include <string>  
#include <iostream> 

using namespace CipherBase64;

#ifdef _DEBUG
#pragma comment(lib,"ssleay32MDd.lib")
#pragma comment(lib,"libeay32MDd.lib")
#else
#pragma comment(lib,"ssleay32MD.lib")
#pragma comment(lib,"libeay32MD.lib")
#endif

CBase64Encode::CBase64Encode()
{
}


CBase64Encode::~CBase64Encode()
{
}

std::string CBase64Encode::base64Encode(const char *buffer, int length, bool newLine)
{
	BIO *bmem = NULL;
	BIO *b64 = NULL;
	BUF_MEM *bptr;

	b64 = BIO_new(BIO_f_base64());
	if (!newLine) {
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	}
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, buffer, length);
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);
	BIO_set_close(b64, BIO_NOCLOSE);

	char *buff = (char *)malloc(bptr->length + 1);
	memcpy(buff, bptr->data, bptr->length);
	buff[bptr->length] = 0;
	BIO_free_all(b64);

	std::string str;
	str.append(buff, bptr->length);
	free(buff);
	buff = 0;

	return str;
}

std::string CBase64Encode::base64Decode(char *input, int length, bool newLine)
{
	BIO *b64 = NULL;
	BIO *bmem = NULL;
	char *buffer = (char *)malloc(length);
	memset(buffer, 0, length);
	b64 = BIO_new(BIO_f_base64());
	if (!newLine) {
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	}
	bmem = BIO_new_mem_buf(input, length);
	bmem = BIO_push(b64, bmem);
	length=BIO_read(bmem, buffer, length);
	BIO_free_all(bmem);

	std::string str;
	str.append(buffer, length);
	free(buffer);
	buffer = 0;

	return str;
}