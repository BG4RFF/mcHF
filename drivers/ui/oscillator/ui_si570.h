/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014                            **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:                                                                     **
**  Description:                                                                   **
**  Last Modified:                                                                 **
**  Licence:		For radio amateurs experimentation, non-commercial use only!   **
************************************************************************************/

#ifndef __UI_SI570
#define __UI_SI570

#define 	HIGHER_PRECISION
//#define 	LOWER_PRECISION

// -------------------------------------------------------------------------------------
// Local Oscillator
// ------------------
#define SI570_ADDRESS			(0x55 << 1)			// R/W bit = LSB

#define SI570_MIN_FREQ			 7200000	// 2 MHz 10000000			// 2.5 Mhz
#define SI570_MAX_FREQ			128000000			// 32 Mhz

#define SI570_RECALL			(1<<0)
#define SI570_FREEZE_DCO		(1<<4)
#define SI570_FREEZE_M			(1<<5)
#define SI570_NEW_FREQ			(1<<6)

#define SI570_REG_7				7
#define SI570_REG_135			135
#define SI570_REG_137			137

// Enter in the Startup frequency
#define FOUT_START_UP    		56.32  // MHz
#define FACTORY_FXTAL			114.285

// VCO range
#define	FDCO_MAX 				5670
#define FDCO_MIN 	 			4850

#define POW_2_28          		268435456.0
// -------------------------------------------------------------------------------------
// Temperature sensor
// ------------------
#define MCP_ADDR        		(0x90)

// MCP registers
#define MCP_TEMP        		(0x00)
#define MCP_CONFIG      		(0x01)
#define MCP_HYSTR       		(0x02)
#define MCP_LIMIT       		(0x03)

// MCP CONFIG register bits
#define MCP_ONE_SHOT    		(7)
#define MCP_ADC_RES     		(5)
#define MCP_FAULT_QUEUE 		(3)
#define MCP_ALERT_POL   		(2)
#define MCP_INT_MODE    		(1)
#define MCP_SHUTDOWN    		(0)
#define R_BIT           		(1)
#define W_BIT           		(0)

#define	MCP_ADC_RES_9			0
#define	MCP_ADC_RES_10			1
#define	MCP_ADC_RES_11			2
#define	MCP_ADC_RES_12			3

#define	MCP_POWER_UP			0
#define	MCP_POWER_DOWN			1

typedef struct OscillatorState
{
	long double		rfreq;
	long double 	rfreq_old;

	float 			fxtal;

	uchar			regs[6];

#ifdef LOWER_PRECISION
	uchar 			init_n1;
	uchar			init_hsdiv;
	ulong 			init_rfreq;
#endif

} OscillatorState;

// -------------------------------------------------------------------------------------
// Exports
// ------------------

uchar 	ui_si570_get_configuration(void);
uchar 	ui_si570_set_frequency(ulong freq,int calib,int temp_factor);

uchar 	ui_si570_init_temp_sensor(void);
uchar 	ui_si570_read_temp(int *temp);
void 	ui_si570_conv_temp(uchar *temp,int *dtemp);

#endif
