#include "Common_Header.h"
#include "Data_Reader.h"

int Data_Collector(char *buffer , int buffer_length)
{
#if 0
	if(fgets(buffer , buffer_length , stdin))
	{
		return OK;
	}
	else
	{
		return NOT_OK;
	}
#endif
	int ret;
#if(TEST_MODE_ON == FALSE)
	ret = scanf("%s",buffer);
#else
	ret = Test_Scanf(buffer);
#endif
	if(ret)
	{
		return OK;
	}
	else if(ret == EOF)
	{
		return END;
	}
	else
	{
		return NOT_OK;
	}
}

#if(TEST_MODE_ON == TRUE)
int Test_Scanf(char *buffer)
{
	char data[15] = "TEST_PATTERN";
	strcpy(buffer , data);
	return OK;
}
#endif