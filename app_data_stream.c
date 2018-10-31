
//#include "i2c_comms.h"
#include "app_data_stream.h"
#include "debug_interface.h"/* Application debug routines */
#include <i2c.h>

#if 1
#define GND_ADDR 0X52
#define VCC_ADDR 0X92
#else
#define GND_ADDR 0X29
#define VCC_ADDR 0X49

#endif
#define CMD 0X80
#define CLEAR 0X40
#define WORDS 0X20

#define CONTAL_ADDR 0X00
#define TIMING_ADDR 0X01
#define ID 0x0a
#define D0_L 0X0C
#define D0_H 0X0D
#define D1_L 0X0E
#define D1_H 0X0F
extern void I2CcommsInit(void);
extern bool I2CWriteRegisterBytes(uint8 base_address, uint8 reg, 
                              uint8 *register_value, int len);
extern bool I2CReadRegisters(uint8 base_address, uint8 start_reg, 
                              uint8 num_bytes, uint8 *p_buffer);
typedef enum
{
    i2c_bus_released = 0x00,
    i2c_bus_acquired = 0x01
} i2c_bus_status;
i2c_bus_status bus_I2C_status = i2c_bus_released;
bool i2c_initialised = FALSE;
static bool I2CAcquire(void)
{
    /* If I2C bus is in Released state, acquire it and return success */
    if(bus_I2C_status == i2c_bus_released)
    {
        bus_I2C_status = i2c_bus_acquired;
        return TRUE;
    }
    else /* Else return Failure */
    {
        return FALSE;
    }
}
static void I2CRelease(void)
{
    bus_I2C_status = i2c_bus_released;
    I2cReset();
}
/*-----------------------------------------------------------------------------*
 *  NAME
 *      I2CWriteRegister
 *
 *  DESCRIPTION
 *      This function writes one byte of data to a specified register on the 
 *      specified device
 *
 *  RETURNS
 *      TRUE if successful
 *
 *----------------------------------------------------------------------------*/
extern bool I2CWriteRegister(uint8 base_address, uint8 reg, 
                              uint8 register_value);

/*-----------------------------------------------------------------------------*
 *  NAME
 *      I2CReadRegister
 *
 *  DESCRIPTION
 *      This function reads the specified register from the specified device
 *
 *  RETURNS
 *      TRUE if successful
 *
 *----------------------------------------------------------------------------*/
extern bool I2CReadRegister(uint8 base_address, uint8 reg, 
                             uint8 *p_register_value);
//csrmesh lightmodel powermodel firmwaremodel 
//bearermodel batterymodel pingmodel attentionmodel streammodel meshAuto 
void read_9300(uint8 addr)
{

	bool ret;
	uint8 value,d0_l,d0_h,d1_l,d1_h;

	ret=I2CWriteRegister(addr,CONTAL_ADDR|CMD|CLEAR,0X03);//POWER UP
	if(!ret)
		DebugIfWriteString("1\n");

	value=0;
	ret=I2CReadRegister(addr,CONTAL_ADDR|CMD|CLEAR,&value);//POWER UP
	if(!ret)
		DebugIfWriteString("2\n");
	
	if(value != 0x03)
	{
		//DEBUG_U8(value);
		//DEBUG_STR("x3\n");
		//return;
	}
	
	ret=I2CReadRegister(addr,D0_L|CMD|CLEAR,&d0_l);//POWER UP
	if(!ret)
		DebugIfWriteString("4\n");
	
	ret=I2CReadRegister(addr,D0_H|CMD|CLEAR,&d0_h);//POWER UP
	if(!ret)
		DebugIfWriteString("5\n");
	
	ret=I2CReadRegister(addr,D1_L|CMD|CLEAR,&d1_l);//POWER UP
	if(!ret)
		DebugIfWriteString("6\n");
	
	ret=I2CReadRegister(addr,D1_H|CMD|CLEAR,&d1_h);//POWER UP
	if(!ret)
		DebugIfWriteString("7\n");
	
	uint16 d0,d1;
	d0 = d0_h << 8 | d0_l;
	d1 = d1_h << 8 | d1_l;
#if 0
	uint16 del,ref_del;
	del = d1*100 / d0;
	uint32 lux;
	ref_del = del;
		
	if(ref_del > 130)
	{
		lux = 0;
	}
	else if(ref_del > 80)
	{
		lux = 36*d0 - 26*d1;
	}
	else if(ref_del > 65)
	{
		lux = 157*d0 - 180*d1;
	}
	else if(ref_del > 52)
	{
		lux = 229 *d0 - 291*d1;
	}
	else
	{
		lux = 315*d0 - 593*d0*((del << 2) - (del >> 1));
	}
#endif
	DebugIfWriteString("light ");
	//DEBUG_U8(addr);
	if(addr == 0x92)
		DebugIfWriteString("down ch0 ");
	else
		DebugIfWriteString("up ch0 ");
	DebugIfWriteUint16(d0);
	
	DebugIfWriteString(" ch1 ");

	DebugIfWriteUint16(d1);
	
	DebugIfWriteString("\n");


}
void apds_9300_read(void)
{
	if(I2CAcquire())
	{
	/* Initialise I2C communication. */
		I2CcommsInit();

		read_9300(GND_ADDR);
		//read_9300(VCC_ADDR);
	
	/* Release the I2C bus */
		I2CRelease();
	}
	
}

