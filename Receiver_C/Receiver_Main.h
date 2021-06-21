#ifndef RECEIVER_MAIN_H
#define RECEIVER_MAIN_H

typedef int (*pfn_DataCollector)(char *buffer , int buffer_length);
typedef int (*pfn_DataStorage)(char *data_buff,double *min_value , double *max_value , double *sam_val , char *param_name);
typedef void (*pfn_OutputBufferFillup)(char *out_buff, double *min , double *max , double *sma , char *param_name);
typedef int (*pfn_Msg_Hndlr)(send_type_en send_type , const char *data);


typedef struct
{
	pfn_DataCollector datacollector;
	pfn_DataStorage datastorage;
	pfn_OutputBufferFillup opbuff_fillup;
	pfn_Msg_Hndlr MsgHndlr;
}Receiver_st;

void Receiver_main(void);

#endif