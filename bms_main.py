import bms_data_handler
   
def main():    
  bms_data_handler.process_vitals(["Charge_rate" ,"Temperature"],"Console")
  
if __name__ == '__main__':
  main()  
