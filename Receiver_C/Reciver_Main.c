#include "Common_Header.h"
#include "Data_Reader.h"
#include "Data_Analyzer.h"
#include "Output_Handler.h"
#include "Receiver_Main.h"

#if(TEST_MODE_ON == FALSE)
int areValuesUpdated = FALSE;
#else
int areValuesUpdated = TRUE;
#endif

#if(TEST_MODE_ON == FALSE)
int main()
{
	Receiver_main();
	return(0);
}
#endif

void Receiver_main(void)
{
	int i=0;
	char buffer[50] , Param_name[50];
	double max_val , min_val , SMA_val;
	char Out_Buff[100];
    const Receiver_st Receiver = {Data_Collector , data_Storage , Output_Buff_Fillup , Msg_Handler};
	while(1)
	{
		/***************Data Read***********************/
		if(Receiver.datacollector(buffer , sizeof(buffer)) != OK)
		{
			exit(0);
		}
		/***********************************************/

		/*****************Data save in buffer***********/
		if(Receiver.datastorage(buffer , &min_val , &max_val , &SMA_val , Param_name) != OK)
		{
			exit(0);
		}
		(void)Receiver.opbuff_fillup(Out_Buff , &min_val , &max_val , &SMA_val , Param_name);
		/************************************************/

		/**************Data output to UI*******************/
		(void)Receiver.MsgHndlr(send_to_console , Out_Buff);
		/**************************************************/
	}
}

