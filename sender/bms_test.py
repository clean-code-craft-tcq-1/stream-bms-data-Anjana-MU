import unittest
import bms_data_handler

class test_battery_current_ranges(unittest.TestCase):
    
  def test_battery_range(self):    
    self.assertTrue(bms_data_handler.process_vitals(["Charge_rate" ,"Temperature"],"Console"))    
    
  def test_alertType(self):
      self.assertTrue(bms_data_handler.process_vitals(["Charge_rate" ,"Temperature", "Soc"],"Console"))
    
  def test_wrong_alertType(self):
      with self.assertRaises(KeyError) as context:
            bms_data_handler.process_vitals(["Charge_rate" ,"Temperature", "Soc"],"PDF")
      self.assertTrue('Supplied AlertType is wrong' in str(context.exception))
      
  def test_wrong_batteryParam(self):
      with self.assertRaises(KeyError) as context:
            bms_data_handler.process_vitals(["Voltage" ,"Temperature", "Soc"],"Email")
      self.assertTrue('Supplied battery paramenter is wrong' in str(context.exception))         
      
  def test_empty_alertType(self):
      with self.assertRaises(ValueError) as context:
            bms_data_handler.process_vitals(["Charge_rate" ,"Temperature", "Soc"],"")
      self.assertTrue('Alerttype value is missing' in str(context.exception))
      
  def test_empty_batteryParam(self):
      with self.assertRaises(ValueError) as context:
            bms_data_handler.process_vitals([],"Email")
      self.assertTrue('Battery parameter value is missing' in str(context.exception))               


#if __name__ == '__main__':
  #unittest.main()
