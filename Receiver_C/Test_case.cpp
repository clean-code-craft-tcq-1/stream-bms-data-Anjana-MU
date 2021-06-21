#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Test_case.h"
#include "Common_Header.h"
#include "Data_Reader.h"
#include "Data_Analyzer.h"
#include "Output_Handler.h"
#include "Receiver_Main.h"

TEST_CASE("Positive_case: Calculate SMA on given array") 
{
	double derived_SMA , data[5] = {1.0,3.0,5.0,7.0,9.0};	
	double expected_SMA = 5.000000;
    int retVal ; 	
	retVal = Calculate_SMA( data , (sizeof(data)/(sizeof(data[0]))) , &derived_SMA );
	REQUIRE( (retVal == OK) );
	REQUIRE((derived_SMA == expected_SMA));		  
}

TEST_CASE("Negetive_case: Calculate SMA on given array") 
{	
    int retVal ; 	
	retVal = Calculate_SMA( 0 , 0 , 0 );
	REQUIRE(retVal == NOT_OK);		  
}


TEST_CASE("Positive_case: Find min and max on given array") 
{
	double min , max , data[5] = {1.0,3.0,5.0,7.0,9.0};	
    int retVal ; 	
	retVal = Min_Max_finder( data , (sizeof(data)/(sizeof(data[0]))) , &min , &max );
	REQUIRE( (retVal == OK) );
	REQUIRE((min == 1.000000));
	REQUIRE((max == 9.000000));		  
}

TEST_CASE("Negetive_case: Find min and max on given array") 
{	
    int retVal ; 	
	retVal = Min_Max_finder( 0 , 0 , 0 , 0);
	REQUIRE(retVal == NOT_OK);		  
}

TEST_CASE("Test the Data analyzer function") 
{	
    int idx , Result = OK; 
    char buffer[4][2] = { {'A' , TYPE_ALPHABET} , {'a' , TYPE_ALPHABET} , {'0' , TYPE_VALUE} , {'1' , TYPE_VALUE} };	
	for(idx = 0; idx < 4 ; idx ++)
	{
		if( (Data_analyzer(buffer[idx][0])) != (buffer[idx][1]) )
		{
			Result = NOT_OK;
		}	
	}
	REQUIRE(Result == OK);		  
}
/*
TEST_CASE("Positive_case: Data storage validation") 
{	
    int retVal , idx;
    double min , max , sma ;
    const char par_name[50] ,  buffer[16][5] = {"gg" ,"1","2","3","6","6","7","54","96","74","65","8","5","4","6","4"}; 	
	for(idx = 0 ; idx < 16 ; idx++)
	{
		retVal = data_Storage( &buffer[idx] , &min , &max , &sma , par_name);
		if(retVal == NOT_OK)
		{
			break;
		}
	}
	REQUIRE( (retVal == OK) && (min == 1.000000) && (max == 96.000000) && (sma == 5.400000) && (strcmp(par_name , &buffer[0]) == 0) );		  
}

*/
TEST_CASE("Negetive_case: Data storage validation") 
{	
    int retVal ; 	
	retVal = data_Storage( 0 , 0 , 0 , 0 , 0);
	REQUIRE(retVal == NOT_OK);		  
}
/*
TEST_CASE("Negetive_case: Data storage validation") 
{	
	int retVal , idx;
    double min , max , sma ;
    const char par_name[50] ,  buffer[17][5] = {"gg" ,"1","2","3","6","6","7","54","96","74","65","8","5","4","6","4","6"}; 	
	for(idx = 0 ; idx < 17 ; idx++)
	{
		retVal = data_Storage( &buffer[idx] , &min , &max , &sma , par_name);
		if(retVal == NOT_OK)
		{
			break;
		}
	}
	REQUIRE(retVal == NOT_OK);		  
}

TEST_CASE("Negetive_case: Data storage validation") 
{	
	int retVal , idx;
    double min , max , sma ;
    char par_name[50] ,  buffer[17][5] = {"55" ,"1","2","3","6","6","7","54","96","74","65","8","5","4","6","4","6"}; 	
	for(idx = 0 ; idx < 17 ; idx++)
	{
		retVal = data_Storage( &buffer[idx] , &min , &max , &sma , par_name);
		if(retVal == NOT_OK)
		{
			break;
		}
	}
	REQUIRE(retVal == NOT_OK);		  
}
*/
TEST_CASE("Test data collector : Fake function") 
{	
	int retVal; 
    char update_buff[15] , exp_buffer[15] =  "TEST_PATTERN" ; 
	retVal = Data_Collector(update_buff , 15);
	REQUIRE((strcmp(update_buff , exp_buffer) == 0) && (retVal == OK));		  
}

TEST_CASE("Positive case : Test Out Buffer fillup function") 
{	
	double min= 0.000000 , max = 5.000000 , sma = 2.200000 ;
	char update_buff[100], par_name[20] = "TEST";
	char exp_buff[100] = "Streaming Parameter: TEST Min_Value: 0.000000 Max_Value: 5.000000 SMA: 2.200000";
	Output_Buff_Fillup(update_buff , &min , &max , &sma , par_name);
	REQUIRE((strcmp(update_buff , exp_buff) == 0));		  
}

TEST_CASE("Negetive case : Test Out Buffer fillup function") 
{	
	double sma = 2.200000 ;
	char update_buff[100], par_name[20] = "TEST";
	char exp_buff[100] = "Streaming Parameter: TEST Min_Value: 0.000000 Max_Value: 5.000000 SMA: 2.200000";
	Output_Buff_Fillup(update_buff , 0, 0, &sma , par_name);
	REQUIRE((strcmp(update_buff , exp_buff) == 1));		  
}

TEST_CASE("Positive case : Test UI control : Fake function") 
{	
	int retVal; 
    char buffer[15] =  "TEST_MSG" ; 
	retVal = Msg_Handler(send_to_console , buffer);
	REQUIRE(retVal == OK);		  
}

TEST_CASE("Negetive case : Test UI control") 
{	
	int retVal; 
    char buffer[15] =  "TEST_MSG" ; 
	retVal = Msg_Handler((send_type_en)10 , buffer);
	REQUIRE(retVal == NOT_OK);		  
}

TEST_CASE("Negetive case : Test UI control : Fake function") 
{	
	int retVal; 
    char buffer[20] =  "TEST_MSG_MODIFIED" ; 
	retVal = Msg_Handler(send_to_console , buffer);
	REQUIRE(retVal == NOT_OK);		  
}
