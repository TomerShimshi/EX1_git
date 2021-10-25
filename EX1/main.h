#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>



static const int ERR_CODE_NOT_ENOUGH_ARGUMENTS = -1;
static const int ERR_CODE_TOO_MANY_ARGUMENTS = -2;

void split_str(char* str, char* FileName, char* OffSet, char* KeyFileName);
char* getline(void);
void SReadFile(char* path, char* WordArr, int length);
void EncryptMessage(char** key, char** message, int length, char** encryptedMessage);