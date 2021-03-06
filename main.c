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

// Common
#include "mchf_board.h"

#include <stdio.h>

// Audio Driver
#include "audio_driver.h"
#include "cw_gen.h"

// UI Driver
#include "ui_driver.h"
#include "ui_rotary.h"
#include "ui_lcd_hy28.h"

// Keyboard Driver
#include "keyb_driver.h"

// Misc
#include "softdds.h"

// Eeprom
#include "eeprom.h"
//
//
//

// Transceiver state public structure
__IO TransceiverState ts;

// ----------------------------------------------------
// Create a time reference incremented by 1 mS and 10mS
//__IO uint32_t LocalTime_1MS  = 0;
//__IO uint32_t LocalTime_10MS = 0;
//__IO uint32_t LocalTime_Over = 0;
// ----------------------------------------------------

// USB Host
//extern USB_OTG_CORE_HANDLE          USB_OTG_Core_dev;

// TIM5 publics
//extern __IO uint32_t PeriodValue;
//extern __IO uint32_t CaptureNumber;
//uint16_t tmpCC4[2] = {0, 0};
//
// If more EEPROM variables are added, make sure that you add to this table - and the index to it in "eeprom.h"
const uint16_t VirtAddVarTab[NB_OF_VAR] =
{
		VAR_ADDR_1,
		VAR_ADDR_2,
		VAR_ADDR_3,
		VAR_ADDR_4,
		VAR_ADDR_5,
		VAR_ADDR_6,
		VAR_ADDR_7,
		VAR_ADDR_8,
		VAR_ADDR_9,
		VAR_ADDR_10,
		VAR_ADDR_11,
		VAR_ADDR_12,
		VAR_ADDR_13,
		VAR_ADDR_14,
		VAR_ADDR_15,
		VAR_ADDR_16,
		VAR_ADDR_17,
		VAR_ADDR_18,
		VAR_ADDR_19,
		VAR_ADDR_20,
		VAR_ADDR_21,
		VAR_ADDR_22,
		VAR_ADDR_23,
		VAR_ADDR_24,
		VAR_ADDR_25,
		VAR_ADDR_26,
		VAR_ADDR_27,
		VAR_ADDR_28,
		VAR_ADDR_29,
		VAR_ADDR_30,
		VAR_ADDR_31,
		VAR_ADDR_32,
		VAR_ADDR_33,
		VAR_ADDR_34,
		VAR_ADDR_35,
		VAR_ADDR_36,
		VAR_ADDR_37,
		VAR_ADDR_38,
		VAR_ADDR_39,
		VAR_ADDR_40,
		VAR_ADDR_41,
		VAR_ADDR_42,
		VAR_ADDR_43,
		VAR_ADDR_44,
		VAR_ADDR_45,
		VAR_ADDR_46,
		VAR_ADDR_47,
		VAR_ADDR_48,
		VAR_ADDR_49,
		VAR_ADDR_50,
		VAR_ADDR_51,
		VAR_ADDR_52,
		VAR_ADDR_53,
		VAR_ADDR_54,
		VAR_ADDR_55,
		VAR_ADDR_56,
		VAR_ADDR_57,
		VAR_ADDR_58,
		VAR_ADDR_59,
		VAR_ADDR_60,
		VAR_ADDR_61,
		VAR_ADDR_62,
		VAR_ADDR_63,
		VAR_ADDR_64,
		VAR_ADDR_65,
		VAR_ADDR_66,
		VAR_ADDR_67,
		VAR_ADDR_68,
		VAR_ADDR_69,
		VAR_ADDR_70,
		VAR_ADDR_71,
		VAR_ADDR_72,
		VAR_ADDR_73,
		VAR_ADDR_74,
		VAR_ADDR_75,
		VAR_ADDR_76,
		VAR_ADDR_77,
		VAR_ADDR_78,
		VAR_ADDR_79,
		VAR_ADDR_80,
		VAR_ADDR_81,
		VAR_ADDR_82,
		VAR_ADDR_83,
		VAR_ADDR_84,
		VAR_ADDR_85,
		VAR_ADDR_86,
		VAR_ADDR_87,
		VAR_ADDR_88,
		VAR_ADDR_89,
		VAR_ADDR_90,
		VAR_ADDR_91,
		VAR_ADDR_92,
		VAR_ADDR_93,
		VAR_ADDR_94,
		VAR_ADDR_95,
		VAR_ADDR_96,
		VAR_ADDR_97,
		VAR_ADDR_98,
		VAR_ADDR_99,
		VAR_ADDR_100,
		VAR_ADDR_101,
		VAR_ADDR_102,
		VAR_ADDR_103,
		VAR_ADDR_104,
		VAR_ADDR_105,
		VAR_ADDR_106,
		VAR_ADDR_107,
		VAR_ADDR_108,
		VAR_ADDR_109,
		VAR_ADDR_110,
		VAR_ADDR_111,
		VAR_ADDR_112,
		VAR_ADDR_113,
		VAR_ADDR_114,
		VAR_ADDR_115,
		VAR_ADDR_116,
		VAR_ADDR_117,
		VAR_ADDR_118,
		VAR_ADDR_119,
		VAR_ADDR_120,
		VAR_ADDR_121,
		VAR_ADDR_122,
		VAR_ADDR_123,
		VAR_ADDR_124,
		VAR_ADDR_125,
		VAR_ADDR_126,
		VAR_ADDR_127,
		VAR_ADDR_128,
		VAR_ADDR_129,
		VAR_ADDR_130,
		VAR_ADDR_131,
		VAR_ADDR_132,
		VAR_ADDR_133,
		VAR_ADDR_134,
		VAR_ADDR_135,
		VAR_ADDR_136,
		VAR_ADDR_137,
		VAR_ADDR_138,
		VAR_ADDR_139,
		VAR_ADDR_140,
		VAR_ADDR_141,
		VAR_ADDR_142,
		VAR_ADDR_143,
		VAR_ADDR_144,
		VAR_ADDR_145,
		VAR_ADDR_146,
		VAR_ADDR_147,
		VAR_ADDR_148,
		VAR_ADDR_149,
		VAR_ADDR_150,
		VAR_ADDR_151,
		VAR_ADDR_152,
		VAR_ADDR_153,
		VAR_ADDR_154,
		VAR_ADDR_155,
		VAR_ADDR_156,
		VAR_ADDR_157,
		VAR_ADDR_158,
		VAR_ADDR_159,
		VAR_ADDR_160,
		VAR_ADDR_161,
		VAR_ADDR_162,
		VAR_ADDR_163,
		VAR_ADDR_164,
		VAR_ADDR_165,
		VAR_ADDR_166,
		VAR_ADDR_167,
		VAR_ADDR_168,
		VAR_ADDR_169,
		VAR_ADDR_170,
		VAR_ADDR_171,
		VAR_ADDR_172,
		VAR_ADDR_173,
		VAR_ADDR_174,
		VAR_ADDR_175,
		VAR_ADDR_176,
		VAR_ADDR_177,
		VAR_ADDR_178,
		VAR_ADDR_179,
		VAR_ADDR_180,
		VAR_ADDR_181,
		VAR_ADDR_182,
		VAR_ADDR_183,
		VAR_ADDR_184,
		VAR_ADDR_185,
		VAR_ADDR_186,
		VAR_ADDR_187,
		VAR_ADDR_188,
		VAR_ADDR_189,
		VAR_ADDR_190,
		VAR_ADDR_191
};

// System tick if needed
__IO uint32_t TimingDelay = 0;

uchar wd_init_enabled = 0;

//*----------------------------------------------------------------------------
//* Function Name       : CriticalError
//* Object              : should never be here, really
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void CriticalError(ulong error)
{
	NVIC_SystemReset();
}

//*----------------------------------------------------------------------------
//* Function Name       : NMI_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void NMI_Handler(void)
{
	printf("NMI_Handler called\n\r");
	CriticalError(1);
}

//*----------------------------------------------------------------------------
//* Function Name       : HardFault_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void HardFault_Handler(void)
{
	printf("HardFault_Handler called\n\r");
	CriticalError(2);
}

//*----------------------------------------------------------------------------
//* Function Name       : MemManage_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void MemManage_Handler(void)
{
	printf("MemManage_Handler called\n\r");
	CriticalError(3);
}

//*----------------------------------------------------------------------------
//* Function Name       : BusFault_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void BusFault_Handler(void)
{
	printf("BusFault_Handler called\n\r");
	CriticalError(4);
}

//*----------------------------------------------------------------------------
//* Function Name       : UsageFault_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void UsageFault_Handler(void)
{
	printf("UsageFault_Handler called\n\r");
	CriticalError(5);
}

//*----------------------------------------------------------------------------
//* Function Name       : SVC_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void SVC_Handler(void)
{
	printf("SVC_Handler called\n\r");
	CriticalError(6);
}

//*----------------------------------------------------------------------------
//* Function Name       : DebugMon_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void DebugMon_Handler(void)
{
	printf("DebugMon_Handler called\n\r");
	CriticalError(7);
}

//*----------------------------------------------------------------------------
//* Function Name       : SysTick_Handler
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void SysTick_Handler(void)
{
//!	TimingDelay++;

	// Process UI refresh
	//ui_driver_irq();
}

//*----------------------------------------------------------------------------
//* Function Name       : EXTI0_IRQHandler
//* Object              : paddles dah
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{
	// Checks whether the User Button EXTI line is asserted
	//
	// WARNING:
	// Due to an apparent HARDWARE bug in the MCU this interrupt seems to be occasionally triggered by transitions
	// of lines OTHER than the PADDLE_DAH (PE0) line, specifically the PC4 and PC5 (Step- and Step+) lines.
	//
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		// Call handler
		if(ts.dmod_mode == DEMOD_CW)	{
			if(!GPIO_ReadInputDataBit(PADDLE_DAH_PIO,PADDLE_DAH))	{	// was DAH line low?
				cw_gen_dah_IRQ();		// Yes - go to CW state machine
			}
		}
		//
		// PTT activate
		else if((ts.dmod_mode == DEMOD_USB)||(ts.dmod_mode == DEMOD_LSB) || (ts.dmod_mode == DEMOD_AM))
		{
			if(!GPIO_ReadInputDataBit(PADDLE_DAH_PIO,PADDLE_DAH))	{	// was PTT line low?
				ts.ptt_req = 1;		// yes - ONLY then do we activate PTT!  (e.g. prevent hardware bug from keying PTT!)
			}
		}
	}

	// Clears the EXTI's line pending bit
	EXTI_ClearITPendingBit(EXTI_Line0);
}

//*----------------------------------------------------------------------------
//* Function Name       : EXTI1_IRQHandler
//* Object              : paddles dit
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void EXTI1_IRQHandler(void)
{
	// Checks whether the User Button EXTI line (paddle DIT) is asserted
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		// Call handler
		if(ts.dmod_mode == DEMOD_CW)
			if(!GPIO_ReadInputDataBit(PADDLE_DIT_PIO,PADDLE_DIT))	// was Dit line low?  (Validate to prevent extraneous interrupts)
				cw_gen_dit_IRQ();
	}	// do nothing if not in CW mode!

	// Clears the EXTI's line pending bit
	EXTI_ClearITPendingBit(EXTI_Line1);
}

//*----------------------------------------------------------------------------
//* Function Name       : EXTI15_10_IRQHandler
//* Object              : power button irq here
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void EXTI15_10_IRQHandler(void)
{
	// power button interrupt
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
//		if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))	// Signal power off

	}
	// Clear interrupt pending bit
	EXTI_ClearITPendingBit(EXTI_Line13);
}

/*void TIM5_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)
  {
    // Get the Input Capture value
    tmpCC4[CaptureNumber++] = TIM_GetCapture4(TIM5);

    // Clear CC4 Interrupt pending bit
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);

    if (CaptureNumber >= 2)
    {
      // Compute the period length
      PeriodValue = (uint16_t)(0xFFFF - tmpCC4[0] + tmpCC4[1] + 1);
    }
  }
}*/

//*----------------------------------------------------------------------------
//* Function Name       : TransceiverStateInit
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void TransceiverStateInit(void)
{
	// Defaults always
	ts.txrx_mode 		= TRX_MODE_RX;				// start in RX
	ts.samp_rate		= I2S_AudioFreq_48k;		// set sampling rate

	ts.enc_one_mode 	= ENC_ONE_MODE_AUDIO_GAIN;
	ts.enc_two_mode 	= ENC_TWO_MODE_RF_GAIN;
	ts.enc_thr_mode		= ENC_THREE_MODE_RIT;

	ts.band		  		= BAND_MODE_20;				// band from eeprom
	ts.band_change		= 0;						// used in muting audio during band change
	ts.dmod_mode 		= DEMOD_USB;				// demodulator mode
	ts.audio_gain		= DEFAULT_AUDIO_GAIN;		// Set initial volume
	ts.audio_gain		= MAX_VOLUME_DEFAULT;		// Set max volume default
	ts.audio_gain_active = 1;						// this variable is used in the active RX audio processing function
	ts.rf_gain			= DEFAULT_RF_GAIN;			//
	ts.max_rf_gain		= MAX_RF_GAIN_DEFAULT;		// setting for maximum gain (e.g. minimum S-meter reading)
	ts.rf_codec_gain	= DEFAULT_RF_CODEC_GAIN_VAL;	// Set default RF gain (0 = lowest, 8 = highest, 9 = "Auto")
	ts.rit_value		= 0;						// RIT value
	ts.agc_mode			= AGC_DEFAULT;				// AGC setting
	ts.agc_custom_decay	= AGC_CUSTOM_DEFAULT;		// Default setting for AGC custom setting - higher = slower
	ts.filter_id		= AUDIO_DEFAULT_FILTER;		// startup audio filter
	ts.filter_300Hz_select	= FILTER_300HZ_DEFAULT;	// Select 750 Hz center filter as default
	ts.filter_500Hz_select	= FILTER_500HZ_DEFAULT;	// Select 750 Hz center filter as default
	ts.filter_1k8_select	= FILTER_1K8_DEFAULT;	// Select 1425 Hz center filter as default
	ts.filter_2k3_select	= FILTER_2K3_DEFAULT;	// Select 1412 Hz center filter as default
	ts.filter_3k6_select	= FILTER_3K6_DEFAULT;	// This is enabled by default
	ts.filter_10k_select	= FILTER_10K_DEFAULT;	// This is enabled by default
	//
	ts.st_gain			= DEFAULT_SIDETONE_GAIN;	// Sidetone gain
	ts.keyer_mode		= CW_MODE_IAM_B;			// CW keyer mode
	ts.keyer_speed		= DEFAULT_KEYER_SPEED;		// CW keyer speed
	ts.sidetone_freq	= CW_SIDETONE_FREQ_DEFAULT;	// CW sidetone and TX offset frequency
	ts.paddle_reverse	= 0;						// Paddle defaults to NOT reversed
	ts.cw_rx_delay		= CW_RX_DELAY_DEFAULT;		// Delay of TX->RX turnaround
	ts.unmute_delay_count		= SSB_RX_DELAY;		// Used to time TX->RX delay turnaround
	//
	ts.nb_setting		= 0;						// Noise Blanker setting
	//
	ts.tx_iq_lsb_gain_balance 	= 0;				// Default settings for RX and TX gain and phase balance
	ts.tx_iq_usb_gain_balance 	= 0;
	ts.tx_iq_lsb_gain_balance 	= 0;
	ts.tx_iq_usb_gain_balance 	= 0;
	ts.rx_iq_lsb_gain_balance = 0;
	ts.rx_iq_usb_gain_balance = 0;
	ts.rx_iq_lsb_phase_balance = 0;
	ts.rx_iq_usb_phase_balance = 0;
	//
	ts.tune_freq		= 0;
	ts.tune_freq_old	= 0;
	//
	ts.calib_mode		= 0;						// calibrate mode
	ts.menu_mode		= 0;						// menu mode
	ts.menu_item		= 0;						// menu item selection
	ts.menu_var			= 0;						// menu item change variable
	ts.menu_var_changed	= 0;						// TRUE if a menu variable was changed and that an EEPROM save should be done

	//ts.txrx_lock		= 0;						// unlocked on start
	ts.audio_unmute		= 0;						// delayed un-mute not needed
	ts.buffer_clear		= 0;						// used on return from TX to purge the audio buffers

	ts.tx_audio_source	= TX_AUDIO_MIC;				// default source is microphone
	ts.tx_mic_gain		= MIC_GAIN_DEFAULT;			// default microphone gain
	ts.tx_mic_gain_mult	= ts.tx_mic_gain;			// actual operating value for microphone gain
	ts.mic_boost		= 0;
	ts.tx_line_gain		= LINE_GAIN_DEFAULT;		// default line gain

	ts.tune				= 0;						// reset tuning flag

	ts.tx_power_factor	= 0.50;						// TX power factor

	ts.pa_bias			= DEFAULT_PA_BIAS;			// Use lowest possible voltage as default
	ts.pa_cw_bias		= DEFAULT_PA_BIAS;			// Use lowest possible voltage as default (nonzero sets separate bias for CW mode)
	ts.freq_cal			= 0;							// Initial setting for frequency calibration
	ts.power_level		= PA_LEVEL_DEFAULT;			// See mchf_board.h for setting
	//
//	ts.codec_vol		= 0;						// Holder for codec volume
//	ts.codec_mute_state	= 0;						// Holder for codec mute state
//	ts.codec_was_muted = 0;							// Indicator that codec *was* muted
	//
	ts.powering_down	= 0;						// TRUE if powering down
	//
	ts.scope_speed		= SPECTRUM_SCOPE_SPEED_DEFAULT;	// default rate of spectrum scope update
	ts.scope_filter		= SPECTRUM_SCOPE_FILTER_DEFAULT;	// default filter strength for spectrum scope
	ts.scope_trace_colour	= SPEC_COLOUR_TRACE_DEFAULT;	// default colour for the spectrum scope trace
	ts.scope_grid_colour	= SPEC_COLOUR_GRID_DEFAULT;		// default colour for the spectrum scope grid
	ts.scope_grid_colour_active = Grid;
	ts.scope_scale_colour	= SPEC_COLOUR_SCALE_DEFAULT;	// default colour for the spectrum scope frequency scale at the bottom
	ts.scope_rescale_rate = SPECTRUM_SCOPE_RESCALE_DEFAULT;	// load default spectrum scope rescale rate
	ts.scope_agc_rate	= SPECTRUM_SCOPE_AGC_DEFAULT;		// load default spectrum scope AGC rate
	//
	ts.menu_item		= 0;						// start out with a reasonable menu item
	//
	ts.radio_config_menu_enable = 0;				// TRUE if radio configuration menu is to be enabled
	//
	ts.cat_mode_active	= 0;						// TRUE if CAT mode is active
	//
	ts.xverter_mode		= 0;						// TRUE if transverter mode is active (e.g. offset of display)
	ts.xverter_offset	= 0;						// Frequency offset in transverter mode (added to frequency display)
	//
	ts.refresh_freq_disp	= 1;					// TRUE if frequency/color display is to be refreshed when next called
													// This is NOT reset by the LCD function, but must be enabled/disabled externally
	//
	ts.pwr_80m_5w_adj	= 1;
	ts.pwr_60m_5w_adj	= 1;
	ts.pwr_40m_5w_adj	= 1;
	ts.pwr_30m_5w_adj	= 1;
	ts.pwr_20m_5w_adj	= 1;
	ts.pwr_17m_5w_adj	= 1;
	ts.pwr_15m_5w_adj	= 1;
	ts.pwr_12m_5w_adj	= 1;
	ts.pwr_10m_5w_adj	= 1;
	//
	ts.filter_cw_wide_disable		= 0;			// TRUE if wide filters are to be disabled in CW mode
	ts.filter_ssb_narrow_disable	= 0;			// TRUE if narrow (CW) filters are to be disabled in SSB mdoe
	ts.am_mode_disable				= 0;			// TRUE if AM mode is to be disabled
	//
	ts.tx_meter_mode	= METER_SWR;
	//
	ts.alc_decay		= ALC_DECAY_DEFAULT;		// ALC Decay (release) default value
	ts.alc_tx_postfilt_gain		= ALC_POSTFILT_GAIN_DEFAULT;	// Post-filter added gain default (used for speech processor/ALC)
	ts.tx_comp_level	= 0;		// 0=Release Time/Pre-ALC gain manually adjusted, >=1:  Value calculated by this parameter
	//
	ts.freq_step_config		= 0;			// disabled both marker line under frequency and swapping of STEP buttons
	//
	ts.nb_disable		= 0;				// TRUE if noise blanker is to be disabled
	//
	ts.dsp_active		= 0;				// TRUE if DSP noise reduction is to be enabled
	ts.dsp_active_toggle	= 0xff;			// used to hold the button G2 "toggle" setting.
	ts.dsp_nr_delaybuf_len = DSP_NR_BUFLEN_DEFAULT;
	ts.dsp_nr_strength	= 0;				// "Strength" of DSP noise reduction (0 = weak)
	ts.dsp_notch_delaybuf_len =	DSP_NOTCH_DELAYBUF_DEFAULT;
	ts.dsp_inhibit		= 1;				// TRUE if DSP is to be inhibited - power up with DSP disabled
	ts.dsp_timed_mute	= 0;				// TRUE if DSP is to be muted for a timed amount
	ts.dsp_inhibit_timing = 0;				// used to time inhibiting of DSP when it must be turned off for some reason
	ts.reset_dsp_nr		= 0;				// TRUE if DSP NR coefficients are to be reset when "audio_driver_set_rx_audio_filter()" is called
	ts.lcd_backlight_brightness = 0;		// = 0 full brightness
	//
	ts.tune_step		= 0;				// Used for press-and-hold step size changing mode
	ts.frequency_lock	= 0;				// TRUE if frequency knob is locked
	//
	ts.tx_disable		= 0;				// TRUE if transmitter is to be disabled
	ts.misc_flags1		= 0;				// Used to hold individual status flags, stored in EEPROM location "EEPROM_MISC_FLAGS1"
	ts.sysclock			= 0;				// This counts up from zero when the unit is powered up at precisely 100 Hz over the long term.  This
											// is NEVER reset and is used for timing certain events.
	ts.version_number_build	= 0;			// minor version number - used to hold version number and detect change
	ts.nb_agc_time_const	= 0;			// used to calculate the AGC time constant
	ts.cw_offset_mode	= 0;				// CW offset mode (USB, LSB, etc.)
	ts.cw_lsb			= 0;				// Flag that indicates CW operates in LSB mode when TRUE
	ts.iq_freq_mode		= 0;				// used to set/configure the I/Q frequency/conversion mode
	ts.lsb_usb_auto_select	= 0;			// holds setting of LSB/USB auto-select above/below 10 MHz

}

//*----------------------------------------------------------------------------
//* Function Name       : MiscInit
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void MiscInit(void)
{
	//printf("misc init...\n\r");

	// Init Soft DDS
	softdds_setfreq(0.0,ts.samp_rate,0);
	//softdds_setfreq(500.0,ts.samp_rate,0);
	//softdds_setfreq(1000.0,ts.samp_rate,0);
	//softdds_setfreq(2000.0,ts.samp_rate,0);
	//softdds_setfreq(3000.0,ts.samp_rate,0);
	//softdds_setfreq(4000.0,ts.samp_rate,0);

	//printf("misc init ok\n\r");
}

static void wd_reset(void)
{
	// Init WD
	if(!wd_init_enabled)
	{
		// Start watchdog
		WWDG_Enable(WD_REFRESH_COUNTER);

		// Reset
		wd_init_enabled = 1;
		TimingDelay 	= 0;

		return;
	}

	// 40mS flag for WD reset
	if(TimingDelay > 40)
	{
		TimingDelay = 0;
		//GREEN_LED_PIO->ODR ^= RED_LED;

		// Update WWDG counter
		WWDG_SetCounter(WD_REFRESH_COUNTER);
	}
}

//*----------------------------------------------------------------------------
//* Function Name       : main
//* Object              :
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
int main(void)
{
	uchar i;

	// Set unbuffered mode for stdout (newlib)
	//setvbuf( stdout, 0, _IONBF, 0 );

//	SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);

	// HW init
	mchf_board_init();


	// Power on
	mchf_board_green_led(1);

	// Set default transceiver state
	TransceiverStateInit();

	// Virtual Eeprom init
	ts.ee_init_stat = EE_Init();	// get status of EEPROM initialization

	// Show logo
	UiLcdHy28_ShowStartUpScreen(100);

	// Extra init
	MiscInit();

	// Init the RX Hilbert transform/filter prior
	// to initializing the audio!
	//
	UiCalcRxPhaseAdj();
	//
	// Init TX Hilbert transform/filter
	//
	UiCalcTxPhaseAdj();	//

	UiDriverLoadFilterValue();	// Get filter value so we can init audio with it

	// Audio HW init
	audio_driver_init();

	// Usb Host driver init
	//keyb_driver_init();

	// UI HW init
	ui_driver_init();

	// Audio HW init - again, using EEPROM-loaded values
	audio_driver_init();
	//
	ts.audio_gain_change = 99;		// Force update of volume control
	Codec_Mute(0);					// make sure codec is un-muted

#ifdef DEBUG_BUILD
	printf("== main loop starting ==\n\r");
#endif

	// Transceiver main loop
	for(;;)
	{
		// UI events processing
		ui_driver_thread();

		// Audio driver processing
		//audio_driver_thread();

		// USB Host driver processing
		//usbh_driver_thread();

		// Reset WD - not working
		//wd_reset();
	}
}
