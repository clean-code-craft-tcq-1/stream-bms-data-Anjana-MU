#include "ctype.h"
#include "Common_Header.h"
#include "Data_Analyzer.h"
#include "Output_Handler.h"


extern int areValuesUpdated;

int data_Storage(char *data_buff,double *min_value , double *max_value , double *sam_val , char *param_name)
{   
	static storage_state_en state = Header_storage;
	static double Value_arr[MAX_STREAM_DATA_NUMBERS] ;
	static int idx = 0;
	int retVal = OK;
	/**sanity check**/
	if( (data_buff==0)||(min_value==0)||(max_value==0)   \
		||(sam_val==0)|| (param_name==0) \
	  )
	{
		retVal = NOT_OK;
	}
	else
	{
		switch(state)
		{
			case Header_storage:
			{
				if(Data_analyzer(data_buff[0]) == TYPE_ALPHABET)
				{
					strcpy(param_name , data_buff);
					state = Value_Handling;
				}
				else
				{
					retVal = NOT_OK;
				}
				break;
			}
			case Value_Handling:
			{
				if(Data_analyzer(data_buff[0]) == TYPE_VALUE)
				{
						Value_arr[idx] = atof(data_buff);
						idx++;
						//remain in same state , since array fillup is ongoing
					if(idx == MAX_STREAM_DATA_NUMBERS)
					{
						idx = 0;
						state = Header_storage;
						if(Min_Max_finder(Value_arr , MAX_STREAM_DATA_NUMBERS , min_value , max_value) == OK)
						{
							if(Calculate_SMA(&Value_arr[MAX_STREAM_DATA_NUMBERS - MAX_VALUE_COUNT_SMA] , MAX_VALUE_COUNT_SMA , sam_val) == OK)
							{
								areValuesUpdated = TRUE; // update the global variable
								state = Header_storage;
							}
							else
							{
								retVal = NOT_OK;
							}
						}
						else
						{
							retVal = NOT_OK;
						}
					}				
				}
				else
				{
					//error case , not expected from Sender
					retVal = NOT_OK;
				}			
				break;
			}
			default:
			{
				//error case
			}
		}
	}
	return retVal;
}


int Data_analyzer(char data)
{
	if(isalpha(data))
	{
		return TYPE_ALPHABET ;
	}
	else
	{
		return TYPE_VALUE ;
	}
}

int Min_Max_finder(double *arr , int arr_size , double *min , double *max)
{
	int idx =0;
	if((arr == 0) || (arr_size == 0) || (min == 0) || (max == 0))
	{
		//sanity check
		return NOT_OK;
	}
	*min = arr[0];
	*max = arr[0];
 	for( idx =1 ; idx < (arr_size) ; idx++)
	{
		if(*min > arr[idx])
		{
			*min = arr[idx];
		}
		if(*max < arr[idx])
		{
			*max = arr[idx];
		}
	}
	return OK;
}


int Calculate_SMA(double *arr , int arr_size , double *SMA_Val)
{
	int idx;
	float sum = 0;
	if((arr == 0) || (arr_size == 0) || (SMA_Val == 0))
	{
		//sanity check
		return NOT_OK;
	}
	for(idx = 0 ; idx < arr_size ; idx ++)
	{
		sum += arr[idx];
	}
	*SMA_Val = sum / arr_size ;
	return OK;
}