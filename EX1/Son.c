#include "main.h"


/*
* 1. get input from user V
* 2. parse input V
* 3. open input file 
* 4. go to the wanted 16 bytes in in put file and encrypt them
* 5. write new encrypted string into a new file
*/

/*
 1. get user input (input file, message offset, key file) V
 2. parse input V
 3. open+read input + key files
 4. create encrypted message
 5. write to target file

 API:
 - read user input V
 - read file
 - write file
 - encrypt message

*/

//char* SReadFile(char* path, int offset, int length);
//int SWriteFile(char* path, char* message, int length);
//int EncryptMessage(char* key, char* message, int length, char** encryptedMessage);


int main()
{
	const wchar_t TARGET_FILE[] =   L"C://projects//HW/EX1//EX1//Encrypted_message.txt";//"Encrypted_message.txt";//
	//const LPCTSTR TARGET_FILE = &TARGET_FILE_Name;
	const char INPUT_LENGTH = 17;
	char* FileName = NULL;
	int * OffSet = NULL;
	int location = 1;
	char* KeyFileName = NULL;
	char * pch;
	char** res = NULL;
	char* Message = NULL;
	char* Key = NULL;
	char* EncryptedMessage = NULL;




	// restore this later please
	//printf("please enter the input in this order: file namename file ,offset, name file key\n");
	//char* UserInput = getline();
	
	char UserInput[] = "./plaintext.txt 16 ./key.txt";
	split_str(UserInput, &FileName, &OffSet, &KeyFileName);
	printf("FileName = %s \n", FileName);
	printf("offset= %d\n", OffSet);
	printf("KeyFileName = %s \n", KeyFileName);
	 
	SReadFile(&FileName, &Message, INPUT_LENGTH);
	printf("Message = %s \n", Message);
	SReadFile(&KeyFileName, &Key, INPUT_LENGTH);
	printf("Key = %s \n", Key);
	location = (int)OffSet / 16;
	EncryptMessage(&Key, &Message, INPUT_LENGTH, &EncryptedMessage);
	printf("EncryptedMessage = %s \n", EncryptedMessage);
	WinWriteToFile(TARGET_FILE, &EncryptedMessage, INPUT_LENGTH);

	/*
	HANDLE hFile = CreateFile(
		L"C://projects//HW/EX1//EX1//Encrypted_message.txt",     // Filename
		GENERIC_WRITE,          // Desired access
		FILE_SHARE_READ,        // Share mode
		NULL,                   // Security attributes
		CREATE_NEW,             // Creates a new file, only if it doesn't already exist
		FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
		NULL);                  // Template file handle

	if (hFile == INVALID_HANDLE_VALUE)
	{
		// Failed to create file meaning mybe thers a file thats alredy exsits try to open exsiting
		hFile = CreateFile(
			L"C://projects//HW/EX1//EX1//Encrypted_message.txt",     // Filename
			GENERIC_WRITE,          // Desired access
			FILE_SHARE_READ,        // Share mode
			NULL,                   // Security attributes
			OPEN_EXISTING,            // Opens a file or device, only if it exists.
			FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
			NULL);                  // Template file handle
		if (hFile == INVALID_HANDLE_VALUE)
		{
			// // Failed to create file and to open exsiting
			return 2;
		}

	}
	*/
	
	//writeToFile(TARGET_FILE, &EncryptedMessage);
	//char* key = SReadFile(KeyFileName, 0, INPUT_LENGTH);
	//char* encrypted = NULL;
	//EncryptMessage(key, message, INPUT_LENGTH, &encrypted);

	//SWriteFile(TARGET_FILE, encrypted, INPUT_LENGTH);

	
	
	return 0;

}
/*
this function takes a string of unkwon size input from the user
taken from https://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c
*/
char * getline(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF || c == '\n')
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

/* this function fecives a point to a str and pointrs to the relvent wanted input values
* and split the input str to the FileName OffSet KeyFileName wnated input values
* based on https://stackoverflow.com/questions/11198604/c-split-string-into-an-array-of-strings
*/

void split_str(char* str, char** FileName, int** OffSet, char** KeyFileName)
{
	/*
		TYPE + * = POINTER OF TYPE (int*)
		& + VAR = GET POINTER TO VAL (int x = 3,  int* px = &x)
		* + VAR = GET VAL OF POINTER (int* py = ..., int y = *p)
		*/
	
	char** res = NULL;
	char* p = strtok(str, " ");
	int  i = 0, n_spaces=0;


	/* split string and append tokens to 'res' */
	while (p) {
		res = realloc(res, sizeof(char*) * ++n_spaces);

		if (res == NULL)
			exit(-1); /* memory allocation failed */

		res[n_spaces - 1] = p;

		p = strtok(NULL, " ");
	}

	/* realloc one extra element for the last NULL */

	res = realloc(res, sizeof(char*) * (n_spaces + 1));
	res[n_spaces] = 0;

	/* print the result */

	for (i = 0; i < (n_spaces + 1); ++i)
		printf("res[%d] = %s\n", i, res[i]);

	/* free the memory allocated */
	*FileName = res[0];
	*OffSet = atoi( res[1]) ;
	*KeyFileName = res[2];
	 free(res);
	
}

/*
* the folllowing function gets a file path , a pointer to array
* and lentgh of each cell in the array filled the dynamic array with the file vals
* based on https://stackoverflow.com/questions/66112939/how-to-read-a-text-file-and-store-in-an-array-in-c
*/

void SReadFile(char** path, char** WordArr, int length)
{
	int i = 0;
	errno_t retval;
	FILE* fp = NULL;
	char** res =  malloc(sizeof(char) * length);
	// OPENS THE FILE
	//FILE* fp = fopen(*path, "r");
	retval = fopen_s(&fp, *path, "r");
	if (0 != retval)
	{
		printf("Failed to open file.\n");
		return STATUS_CODE_FAILURE;
	}
	
	char* word = malloc(sizeof(char) * length);
	// CHECKS IF THE FILE EXISTS, IF IT DOESN'T IT WILL PRINT OUT A STATEMENT SAYING SO     
	/*
	if (fp == NULL)
	{
		printf("file not found");
		return 1;
	}
	*/
	while (fgets(word, length, fp) != NULL)
	{
		printf("%s \n", word);
		res = realloc(res, sizeof(word) * (++i));
		if (res == NULL)
			exit(-1); /* memory allocation failed */


		//strcpy(res[i - 1], word);
		res[i - 1] =word;
		
	}
	fclose( fp);
	
	*WordArr = *res;
	//free(word);
	free(res);

}
/*
this func recives two pointers to 
*/
void EncryptMessage(char** key, char** message, int length, char** encryptedMessage)
{
	int i = 0;
	char *Encrypt= NULL;
	char* Ptrkey = *key;
	char* PtrMessge = *message;
	Encrypt =  malloc(sizeof(char) * length);
	/*if (NULL == strcpy(*Encrypt, *message))
	{
		printf("failed to copy string \n");
	}*/
	
	
	for (i = 0; i < length; ++i) {
		printf("message[i]= %c\n", *PtrMessge);
		Encrypt[i] = *PtrMessge ^ *Ptrkey;
		
		PtrMessge++;
		Ptrkey++;
	}
	printf("Encrypt= %s\n", Encrypt);
	
	*encryptedMessage = Encrypt;
}

//This function prints current string into Computation.txt.
int writeToFile(char pathToFile[], char** stringToAppend)
{
	FILE* pFile;
	errno_t retval;
	retval = fopen_s(&pFile, pathToFile, "a");

	if (0 != retval)
	{
		printf("Failed to open file.\n");
		return STATUS_CODE_FAILURE;
	}

	// Write lines
	retval = fputs(*stringToAppend, pFile);
	if (0 > retval)
	{
		printf("Failed to write to file.\n");
		// Don't return. Try and close the file first.
	}

	// Close file
	retval = fclose(pFile);
	if (0 != retval)
	{
		printf("Failed to close file.\n");
		return STATUS_CODE_FAILURE;
	}

	return STATUS_CODE_SUCCESS;
}

// shoof
	/*
	pFile = fopen(pathToFile, "a");
	if (pFile == NULL) {
		perror("Error opening file.");
	}
	else
	{
		char* toAdd;
		fprintf(pFile, *stringToAppend);
		fprintf(pFile, "\n");
	}
	fclose(pFile);
	
}*/
/*
* write to a file using the win API lib
* based on the example from:
* https://riptutorial.com/winapi/example/5736/create-a-file-and-write-to-it
*/
int WinWriteToFile(wchar_t  pathToFile[] , char** stringToAppend,int MessegeLen)
{
	// Open a handle to the file
	HANDLE hFile = CreateFile(
		(LPCTSTR)(pathToFile),     // Filename
		GENERIC_WRITE,          // Desired access
		FILE_SHARE_READ,        // Share mode
		NULL,                   // Security attributes
		CREATE_NEW,             // Creates a new file, only if it doesn't already exist
		FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
		NULL);                  // Template file handle

	if (hFile == INVALID_HANDLE_VALUE)
	{
		// Failed to create file meaning mybe thers a file thats alredy exsits try to open exsiting
		hFile = CreateFile(
			(LPCTSTR)(pathToFile),     // Filename
			GENERIC_WRITE,          // Desired access
			FILE_SHARE_READ,        // Share mode
			NULL,                   // Security attributes
			OPEN_EXISTING,            // Opens a file or device, only if it exists.
			FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
			NULL);                  // Template file handle
		if (hFile == INVALID_HANDLE_VALUE)
		{
			// // Failed to create file and to open exsiting
			return 2;
		}
		
	}

	// Write data to the file
	//std::string strText = "Hello World!"; // For C use LPSTR (char*) or LPWSTR (wchar_t*)
	DWORD bytesWritten;
	WriteFile(
		hFile,            // Handle to the file
		(DWORD )*stringToAppend,  // Buffer to write
		MessegeLen,   // Buffer size
		stringToAppend,    // Bytes written
		NULL);         // Overlapped

	 // Close the handle once we don't need it.
	CloseHandle(hFile);
}
