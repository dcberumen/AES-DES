#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
	string CipherName = argv[1];
	char* key = argv[2];
	string EncDec = argv[3];
	ifstream in;
	ofstream out;
	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL; 
	
	if(CipherName == "AES")
	{
		cipher = new AES();
		FILE* infile = fopen(argv[4], "r");
		FILE* outfile = fopen(argv[5], "w");
		/* Error checks */
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		unsigned char* plaintext = new unsigned char[17];
		unsigned char* block = new unsigned char[17];
		
		if(EncDec == "ENC")
		{
			key[0] = '0';
			if(!cipher->setKey((unsigned char*)key))
			{
				fprintf(stderr,"ERROR: something went wrong with key\n");
				exit (-1);
			}
			bool encrypting = true;
			while(encrypting)
			{
				memset(plaintext, '0', 16);
				if(fread(plaintext,1, 16, infile))
				{
					//encrypt 8 bytes at a time and write to out file
					block = cipher->encrypt(plaintext);
					fwrite(block,1,16,outfile);
				}
				else
					encrypting = false;
			}
		}
		/* Perform decryption */
		else if(EncDec == "DEC")
		{
			key[0] = '1';
			if(!cipher->setKey((unsigned char*)key))
			{
				fprintf(stderr,"ERROR: something went wrong with key\n");
				exit (-1);
			}
			bool decrypting = true;
			while(decrypting)
			{
				memset(plaintext, '0', 16);
				if(fread(plaintext, 1, 16, infile))
				{
					//decrypt 16 bytes at a time and write to out file
					block = cipher->decrypt(plaintext);
					fwrite(block,1,16,outfile);
				}
				else
					decrypting = false;
			}
		}
		
		else
		{
			out.close();
			fprintf(stderr, "ERROR invalid paramaters ./cipher <cipher> <key> <ENC/DEC> <infile> <outfile>\n");
			exit(-1);
		}
		delete plaintext;
		delete block;

	}
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
	else if(CipherName == "DES")
	{
		FILE* infile = fopen(argv[4], "r");
		FILE* outfile = fopen(argv[5], "w");
		cipher = new DES();
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		if(!cipher->setKey((unsigned char*)key))
		{
			fprintf(stderr, "ERROR: DES key error");
			exit(-1);
		}
		unsigned char* plaintext = new unsigned char[9];
		unsigned char* block = new unsigned char[9];
		
		//move text file data to string
		
		/* Perform encryption */
		if(EncDec == "ENC")
		{
			bool encrypting = true;
			
			while(encrypting)
			{
				memset(plaintext, '0', 8);
				if(fread(plaintext,1, 8, infile))
				{
					//encrypt 8 bytes at a time and write to out file
					block = cipher->encrypt(plaintext);
					fwrite(block,1,8,outfile);
				}
				else
					encrypting = false;
			}
			
		}
		/* Perform decryption */
		else if(EncDec == "DEC")
		{
			bool decrypting = true;
			
			while(decrypting)
			{
				memset(plaintext, '0', 8);
				if(fread(plaintext, 1, 8, infile))
				{
					//encrypt 8 bytes at a time and write to out file
					block = cipher->decrypt(plaintext);
					fwrite(block,1,8,outfile);
				}
				else
					decrypting = false;
			}
			
		}
		
		
		//valid cipher choice but invalid enc/dec choice
		else
		{
			out.close();
			fprintf(stderr, "ERROR invalid paramaters ./cipher <cipher> <key> <ENC/DEC> <infile> <outfile>\n");
			exit(-1);
		}
		delete plaintext;
		delete block;
		fclose(infile);
		fclose(outfile);
	}
	
	else
	{
		fprintf(stderr, "ERROR: invalid cipher choice (AES, DES)\n");
		return 0;
	}
}
