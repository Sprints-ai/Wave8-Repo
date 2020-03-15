/*final
 * App.c
 *
 * Created: 3/11/2020 10:25:29 AM
 * Author : Mohamed Ramadan
 */ 

#include "Sos.h"
#include "avr/interrupt.h"

#define  F_CPU  (16000000UL)	 
	 

int main(){
	/**enable global interrupt**/
	sei();
	
	/**Initialize the SOS **/
	Sos_Init(&ConfigPtr);
	
	/**SOS start three tasks**/
	Create_Task(&Sos_cfg_start_Fun1);
	Create_Task(&Sos_cfg_start_Fun2);
	Create_Task(&Sos_cfg_start_Fun3);
	
	while(1)
	{
		/**perform the tasks**/
		Sos_Run();
		
	}
	
	
	
}
