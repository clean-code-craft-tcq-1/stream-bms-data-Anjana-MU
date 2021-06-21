import random
import report_vitals

bms_attribute_limits = {'TEMPERATURE': [0, 45],
                        'SOC': [20, 80],
                        'CHARGE_RATE': [0, 0.8]} 

def random_number_generator(min,max):
  #Generates random numbers between min and max
  if isinstance((min+max) , int):
    return random.sample(range(min, max), 15)
  elif isinstance((min+max) , float):
    random_floats=[]
    for i in range(15):
        random_floats.append(random.uniform(min,max))
    return random_floats   

def process_vitals(battery_parameters,alert_type):
    validate_vitals(battery_parameters,alert_type)    
    for battery_parameter in battery_parameters:
        parameter_values = generate_vitals(battery_parameter.upper())      
        publish_data(parameter_values,battery_parameter,alert_type.upper())
    return True

def validate_vitals(battery_parameters,alert_type):
    validate_size(battery_parameters,alert_type)
    validate_bms_keys(battery_parameters)
    validate_alertType_key(alert_type)

def validate_size(battery_parameters,alert_type):    
    if len(battery_parameters)== 0: 
        raise ValueError('Battery parameter value is missing')
    elif len(alert_type) == 0:
        raise ValueError('Alerttype value is missing')
    
def validate_bms_keys(battery_parameters):
    for item in battery_parameters:
        if not item.upper() in bms_attribute_limits.keys():
            raise KeyError('Supplied battery paramenter is wrong')
            
def validate_alertType_key(alert_type):
    if not alert_type.upper() in report_vitals.alertTarget_type.keys():
        raise KeyError("Supplied AlertType is wrong")             
            
def generate_vitals(battery_parameter):
    min,max = bms_attribute_limits[battery_parameter]
    return random_number_generator(min,max)
 
def publish_data(parameter_values,battery_parameter,alert_type):
    return report_vitals.check_and_alert(parameter_values, battery_parameter,alert_type)
