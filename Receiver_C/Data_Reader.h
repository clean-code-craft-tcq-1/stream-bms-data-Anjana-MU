#ifndef DATA_READER_H
#define DATA_READER_H


int Data_Collector(char *buffer , int buffer_length);

#if(TEST_MODE_ON == TRUE)
int Test_Scanf(char *buffer);
#endif

#endif