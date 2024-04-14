# AAC-Clydespace Avionics Software Challenge

## Task Description
Please write a device driver that implements the following API:
- Get the full-scale configuration
CTRL_REG2 (21h)
Keeping default values for Reboot bit and Soft_reset bit we get following hex values for different configurations:
CONFIG_4GAUSS        0x00
CONFIG_8GAUSS        0x20
CONFIG_12GAUSS       0x40
CONFIG_16GAUSS       0x60
These respectives values can help user to determine what full scale configuration they are on currently.

- Get and set the output data rate
In case of output data rate this data developer can find on CTRL_REG1
Since we are not using data from temperature sensor and selftest feature we keep default values for TEMP_EN and ST bits.
Developer must take a note that when using FAST_ODR i.e. fast data rates (155hz - 1000hz) FAST_ODR bit is SET, otherwise
it should be LOW. 
Below are different data rates mentioned and their corresponding hex input to the registers.
0.625HZ             0x00
1.25HZ              0x04
2.5HZ               0x08
5HZ                 0x0C
10HZ                0x10
20HZ                0x14
40HZ                0x18
80HZ                0x1C
155HZ              0x10
300HZ              0x14
560HZ              0x18
1000HZ             0x1C

- Enable or disable the interrupt pin
This can be achieved by changing the value of IEN bit in the INT_CFG (30h) Register.

- Read the output data of a specified axis
Data for all this axis can be read from registers: 
OUT_X_L (28h), OUT_X_H (29h) for X-axis
OUT_Y_L (2Ah), OUT_Y_H (2Bh) for Y-axis and 
OUT_Z_L (2Ch), OUT_Z_H (2Dh)

Since the data for all three axis is on 2 different registers. We will be storing this data in an uint8_t array of 2 elements
and later by shifting the bits by 8 places and ORing the 2 element. We can easily store it in a uint16_t type variable.



## Extra Thoughts
If you have time, answer the following questions:
- What changes you would make to this interfaces for use in an RTOS
environment?
=> Some of the changes that we can make to the interface for better integration with an RTOS are: adding Callback mechnanisms, 
this will allow the application to continue executing other tasks while waiting for the i2c to finish execution.
Implemenation of mutexes and semaphores this will give us exclusive access to shared resources and help us manage these resources better. 
Error handling capablities, these gives us better error code or notifications in case of errors and help us continue to take appropriate 
actions in case of the errors. Other than these we could also keep priorities to the tasks which are of greater importance.

- How might the I2C API be improved
=> We do have a lot of scope to improve in this I2C API.
Features like Error reporting which can help us troubleshoot the problems and implementing features like timeout mechanisms to prevent 
indefinite blocking in case of communication issues. 
