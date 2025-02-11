#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const size_t HASH_LENGTH = 128 / 8 + 1;

int hash_md5(unsigned char *fio, unsigned char *md);

unsigned char *buf = "ивановвадимниколаевич21.06.19653d2cb093-f1b9-4a8d-b8ec-f15ada921033";

int main(int argc, char **argv)
{
    int exit_code = 0;
    unsigned char md[HASH_LENGTH];

    //OPENSSL_init_ssl(0, NULL);
   
    int err = hash_md5(buf, md);
    if(err)
        exit(err);
    
    printf("Hash code:\n");
    for(size_t i = 0; i < HASH_LENGTH - 1; i++)
        printf("%02x", md[i]);

    //OPENSSL_cleanup();
    printf("\n");

    exit(err);
    
}

int hash_md5(unsigned char *fio, unsigned char *md)
{
    int exit_code = 0;
    
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    int ok = EVP_DigestInit(ctx, EVP_md5());
    
    
    size_t nbytes = strlen((const char*)fio);
    ok = EVP_DigestUpdate(ctx, fio, nbytes);
    
    ok = EVP_DigestFinal(ctx, md, NULL);
    
    if (!ok) {
        printf("Message digest calculation error\n");
        exit_code = 1;
    }

    EVP_MD_CTX_free(ctx);

    return exit_code;
}


