#include "Common_Header.h"
#include "Output_Handler.h"

extern int areValuesUpdated;

void Output_Buff_Fillup(char *out_buff, double *min , double *max , double *sma , char *param_name)
{
	/**sanity check**/
	if( !( (out_buff==0)||(min==0)||(max==0) ||(sma==0)|| (param_name==0) ) )
	{
		if(areValuesUpdated == TRUE)
		{
			sprintf(out_buff , "Streaming Parameter: %s Min_Value: %lf Max_Value: %lf SMA: %lf" ,param_name, *min , *max , *sma);
		}
	}
}


int Msg_Handler(send_type_en passed_send_type ,const char *disp_msg)
{
	int ret = NOT_OK;
	Send_method_st Send_method[1] = {{send_to_console , send2console}};
	if((Send_method[passed_send_type].fn_send2UI != NULL) && (passed_send_type < MAX_send_type))
	{
		if(areValuesUpdated == TRUE)
		{
			ret = Send_method[passed_send_type].fn_send2UI(disp_msg);
			areValuesUpdated = FALSE;
		}
	}
	return ret;
}

#if(TEST_MODE_ON == FALSE)
int send2console(const char *msg)
{
	printf("%s\n" ,msg);
	return OK;
}
#else
int send2console(const char *msg)
{
	char exp_msg[20] = "TEST_MSG";
	if(strcmp(exp_msg , msg) == 0)
		return OK;
	else
		return NOT_OK;
}
#endif