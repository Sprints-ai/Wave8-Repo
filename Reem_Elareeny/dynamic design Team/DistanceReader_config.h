/*
 * DistanceReader_config.h
 *
 * Created: 3/30/2020 7:00:01 PM
 *  Author: M.Ramadan
 */ 


#ifndef DISTANCEREADER_CONFIG_H_
#define DISTANCEREADER_CONFIG_H_

#define ULTRASONIC 		1
#define SENSOR1			2
#define SENSOR2			3
#define SENSOR3			4

/************************************************************************/
/*			  Structures Declaration		                            */
/************************************************************************/
typedef struct DistanceReader_cfg
{
	uint8_t   Sensor_Version;
	uint16_t *D_R_Value;
}DistanceReader_Cfg;



#endif /* DISPLAYER_CONFIG_H_ */