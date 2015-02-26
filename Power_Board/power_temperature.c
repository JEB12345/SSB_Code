#include "power_temperature.h"
#include "power_i2c.h"
#include "power_state.h"
#include "power_can.h"

temperature_data temperature_state;

return_value_t temperature_init() {
    //I2C SHOULD HAVE BEEN INITIALIZED WHEN TRYING TO USE THIS MODULE
    temperature_state.temperature = -1;
    temperature_state.state = RET_OK;
    return RET_OK;
}

return_value_t temperature_update() {
    CO(adc_state_C_temp) = temperature_state.temperature;
    
    if(temperature_state.state==RET_OK || temperature_state.state==RET_ERROR){
        //start a new read operation
        if(i2c_1_read(0b1001101,0x00,1,&temperature_state.temperature,&temperature_state.state)==RET_OK){
            //success!
        } else {
            //couldn't start an operation, will try again later
            temperature_state.state=RET_ERROR;
        }
    } else {
        //still running, do nothing
    }
}
