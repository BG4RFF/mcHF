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

#ifndef __I_RX_FILTER_10K_H
#define __I_RX_FILTER_10K_H

#define I_BLOCK_SIZE		1
#define I_NUM_TAPS			89

/*
 	 * Hilbert 0 Degree, "Phase-added" bandpass filter
     * Kaiser Window FIR Filter, Beta = 5.75, Raised Cosine = 0.91
     * Fc = 2.26 kHz
     * BW = 15.5 kHz
     * 89 Taps
     *
     * 20140926 by KA7OEI using Iowa Hills Hilbert Filter Designer
     *
     * This filter used in the "10 kHz" RX filter position of the mcHF
*/

const float i_rx_10k_coeffs[I_NUM_TAPS] =
{
		 0.000050167609691425,
		 0.000025603407918848,
		-0.000118981585848916,
		-0.000170474191765324,
		 0.000048296523157148,
		 0.000256073107769974,
		 727.2794187150840E-9,
		-0.000501261183059805,
		-0.000408327227464192,
		 0.000402666023236487,
		 0.000712863881140397,
		-0.0003308411712395,
		-0.0013996330569958,
		-0.000528641700743514,
		 0.001455738736932886,
		 0.001329912986372006,
		-0.00150961605426034,
		-0.00294679909039784,
		 0.000076369628754364,
		 0.003654850522527691,
		 0.001577905576333736,
		-0.00432377051231776,
		-0.00486833805524385,
		 0.002504357924698762,
		 0.007219173741633013,
		 0.000249124314985597,
		-0.00964993129867818,
		-0.00614913866004667,
		 0.008394400456713639,
		 0.011847880245809284,
		-0.00485256342855596,
		-0.018458064255265,
		-0.00458695963656225,
		 0.020574362746561586,
		 0.016624349270928814,
		-0.0185108281915374,
		-0.0333393467458619,
		 0.005438341796513525,
		 0.049039677508405620,
		 0.020261414347031232,
		-0.0646569743752001,
		-0.0780052456437194,
		 0.073784359346471568,
		 0.307733691067162585,
		 0.421541346382627025,
		 0.307733691067179571,
		 0.073784359346490025,
		-0.0780052456437136,
		-0.0646569743752061,
		 0.020261414347025011,
		 0.049039677508406654,
		 0.005438341796518410,
		-0.0333393467458602,
		-0.01851082819154,
		 0.016624349270926188,
		 0.020574362746562019,
		-0.00458695963656039,
		-0.0184580642552646,
		-0.00485256342855692,
		 0.011847880245808904,
		 0.008394400456714472,
		-0.00614913866004598,
		-0.00964993129867861,
		 0.000249124314984851,
		 0.007219173741633126,
		 0.002504357924699511,
		-0.00486833805524365,
		-0.00432377051231848,
		 0.001577905576332938,
		 0.003654850522527679,
		 0.000076369628754987,
		-0.00294679909039735,
		-0.00150961605426035,
		 0.001329912986371784,
		 0.001455738736932826,
		-0.000528641700743405,
		-0.00139963305699574,
		-0.000330841171239577,
		 0.000712863881140276,
		 0.000402666023236442,
		-0.000408327227464152,
		-0.000501261183059743,
		 727.2794187481990E-9,
		 0.000256073107769969,
		 0.000048296523157126,
		-0.000170474191765341,
		-0.000118981585848918,
		 0.000025603407918855,
		 0.000050167609691430
};

/*
static float32_t 		FirState_I[128];
arm_fir_instance_f32 	FIR_I;
*/
#endif
