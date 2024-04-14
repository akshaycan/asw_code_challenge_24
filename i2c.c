/*
* AAC Clyde Space coding test
* Candidate: Akshay G Jadhav
* Date:14/04/2024
*/

/*
* Get the full-scale configuration
* Get and set the output data rate
* Enable or disable the interrupt pin
* Read the output data of a specified axis
*/
#include "i2c.h"
#include <stdint.h>
#include <stdio.h>

status_t i2c_read(uint8_t bus_address, uint8_t register_address, uint16_t length, uint8_t *buffer)
{
    printf("read [%d] bytes from bus [%d] for register [%d]\n", length, bus_address, register_address);

    /* Setting the output to some arbitrary value */
    for (size_t i = 0; i < length; ++i) 
    {
        buffer[i] = 0xff;
    }
    return STATUS_OK;
}
status_t i2c_write(uint8_t bus_address, uint8_t register_address, uint16_t length, uint8_t *buffer)
{
    printf("write [%d] bytes to bus [%d] for register [%d]\n\t", length, bus_address, register_address);

    for (size_t i = 0; i < length; ++i) {
        printf("%p", buffer);
    }
    printf("\n");
    return STATUS_OK;
}

status_t get_full_scale_config(uint8_t bus_address, uint8_t *full_scale_selection)
{

    return(i2c_read(bus_address, CTRL_REG2, 1, full_scale_selection));
}
/*
* 
* Function Description: This function helps us to Enable and disable interrupt pin.
* FUnction type: status_t
* Returns: Bus address, Register address, Length of data and 
* Interrupt status ( 1: Enable 0: Disable)
* 
*/
status_t interrupt_mode(uint8_t bus_address, uint8_t intrupt_pin_status)
{
    uint8_t reg3;
    status_t status = i2c_read(bus_address, INT_CFG, 1, &reg3);
    if (status != STATUS_OK)
        return status;

    if (intrupt_pin_status)
        reg3 |= INTERRUPT_ENABLE;
    else
        reg3 &= INTERRUPT_DISABLE;

    return (i2c_write(bus_address, INT_CFG, 1, &reg3));
}
/*
*
* Function Description: This function can be used to set the Data output rate
* Function type: status_t 
* Returns: Bus address, Register address, length and the set value of output data rate.
*
*/
status_t set_data_output_rate(uint8_t bus_address, uint8_t data_rate)      // Set DOR. 
{
    return(i2c_write(bus_address, CTRL_REG1, 1, &data_rate));
}
/*
*
* Function Description: Helps us to Enable and disable interrupt pin.
* Function type: status_t
* Returns: Bus Address, Register address, current data rate.
*
*/
status_t get_data_output_rate(uint8_t bus_address, uint8_t *data_rate)      // Get DOR.
{
    return(i2c_read(bus_address, CTRL_REG1, 1, data_rate));
}
/*
*
* Function Description: This function can be used to read data from specific axis(X - Y - Z) 
* Function type: status_t
* Returns: Bus address, Register address and the Axis data of the selected axis.
*
*/
status_t read_axis_data(uint8_t bus_address, char axis, int8_t* output)        
{
    int8_t axis_data[2];
    uint8_t reg_address;
    switch (axis)
    {
    case 'X':
        axis_data[0] = OUT_X_L;
        axis_data[1] = OUT_X_H;
        break;

    case 'Y':
        axis_data[0] = OUT_Y_L;
        axis_data[1] = OUT_Y_H;
        break;

    case 'Z':
        axis_data[0] = OUT_Z_L;
        axis_data[1] = OUT_Z_H;
        break;

    default:
        return STATUS_ERROR;

    }
    status_t status = i2c_read(bus_address, reg_address, 2, axis_data);
    if (status != STATUS_OK)
        return status;

    *output = (int16_t)((axis_data[1] << 8) | axis_data[0]);                 // Combine the two bytes into a signed 16-bit integer
    return STATUS_OK;
}