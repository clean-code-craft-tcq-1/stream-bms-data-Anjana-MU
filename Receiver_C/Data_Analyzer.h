#ifndef DATA_ANALYZER_H
#define DATA_ANALYZER_H


#define TYPE_ALPHABET  0x0A
#define TYPE_VALUE   0x0B
#define MAX_VALUE_COUNT_SMA 5

typedef enum
{
	Header_storage,
	Value_Handling
}storage_state_en;


int Data_analyzer(char data);
int data_Storage(char *data_buff,double *min_value , double *max_value , double *sam_val , char *param_name);
int Min_Max_finder(double *arr , int arr_size , double *min , double *max);
int Calculate_SMA(double *arr , int arr_size , double *SMA_Val);



#endif