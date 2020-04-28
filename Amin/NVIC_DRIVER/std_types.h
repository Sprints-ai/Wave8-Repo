#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#define NULL	((void *)0)

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char sint8_t;
typedef signed int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;
typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;

typedef uint8_t  ERROR_STATUS;
typedef uint8_t  bool_t;

#endif /* STD_TYPES_H_ */