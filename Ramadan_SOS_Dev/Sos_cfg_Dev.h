#ifndef Sos_cfg_H_
#define	Sos_cfg_H_

#include "std_types.h"

#define Sos_TIMER_CH0	(0)			 /* defines Timer 0 */
#define Sos_TIMER_CH1	(1)			 /* defines Timer 1 */
#define Sos_TIMER_CH2	(2)			 /* defines Timer 2 */

#define Res1			(1)
#define Res2			(2)
#define Res3			(3)

typedef struct Sos_cfg_Init{
	uint8_t  Sos_Ch_Timer;			 /* To choose the Timer number */
	uint8_t  Sos_Res;      			 /*To choose the resolution we work with*/
}Sos_ConfigType;					



//don't create any object in .h "forbidden"
extern const Sos_ConfigType ConfigPtr;





#endif



