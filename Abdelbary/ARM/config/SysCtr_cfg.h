
#ifndef E15_ARM_REPO_CONFIG_SYSCTR_CFG_H_
#define E15_ARM_REPO_CONFIG_SYSCTR_CFG_H_

/********************INCLUDES***********************************************/

#include "../mcal/SysCtr/SysCtr_types.h"
/********************DEFINES***********************************************/
/* crystal frequencies */
#define F_OSC_16MHZ                 (0x15)
#define F_OSC_8MHZ                  (0x0E)
#define F_OSC_6MHZ                  (0x0B)
/*Clock sources options*/
#define MOSC            (0x0) /* Main oscillator */
#define PIOSC           (0x1) /* Precision internal oscillator */
#define PIOSC_DIV_4     (0x2) /* Precision internal oscillator / 4 */
#define LFIOSC          (0x3) /*Low-frequency internal oscillator*/
#define HIBERNATION_CLK (0x7) /* 32.768 kHz */

/* allowable values for system clock frequencies */
#define SYS_CLK_FREQ_80_000         ( 0   )
#define SYS_CLK_FREQ_66_667         ( 1   )
#define SYS_CLK_FREQ_50_000         ( 2   )
#define SYS_CLK_FREQ_44_444         ( 3   )
#define SYS_CLK_FREQ_40_000         ( 4   )
#define SYS_CLK_FREQ_36_364         ( 5   )
#define SYS_CLK_FREQ_33_333         ( 6   )
#define SYS_CLK_FREQ_30_769         ( 7   )
#define SYS_CLK_FREQ_28_571         ( 8   )
#define SYS_CLK_FREQ_26_667         ( 9   )
#define SYS_CLK_FREQ_25_000         ( 10  )
#define SYS_CLK_FREQ_23_529         ( 11  )
#define SYS_CLK_FREQ_22_222         ( 12  )
#define SYS_CLK_FREQ_21_053         ( 13  )
#define SYS_CLK_FREQ_20_000         ( 14  )
#define SYS_CLK_FREQ_19_048         ( 15  )
#define SYS_CLK_FREQ_18_182         ( 16  )
#define SYS_CLK_FREQ_17_391         ( 17  )
#define SYS_CLK_FREQ_16_667         ( 18  )
#define SYS_CLK_FREQ_16_000         ( 19  )
#define SYS_CLK_FREQ_15_385         ( 20  )
#define SYS_CLK_FREQ_14_815         ( 21  )
#define SYS_CLK_FREQ_14_286         ( 22  )
#define SYS_CLK_FREQ_13_793         ( 23  )
#define SYS_CLK_FREQ_13_333         ( 24  )
#define SYS_CLK_FREQ_12_903         ( 25  )
#define SYS_CLK_FREQ_12_500         ( 26  )
#define SYS_CLK_FREQ_12_121         ( 27  )
#define SYS_CLK_FREQ_11_765         ( 28  )
#define SYS_CLK_FREQ_11_429         ( 29  )
#define SYS_CLK_FREQ_11_111         ( 30  )
#define SYS_CLK_FREQ_10_811         ( 31  )
#define SYS_CLK_FREQ_10_526         ( 32  )
#define SYS_CLK_FREQ_10_256         ( 33  )
#define SYS_CLK_FREQ_10_000         ( 34  )
#define SYS_CLK_FREQ_9_756          ( 35  )
#define SYS_CLK_FREQ_9_524          ( 36  )
#define SYS_CLK_FREQ_9_302          ( 37  )
#define SYS_CLK_FREQ_9_091          ( 38  )
#define SYS_CLK_FREQ_8_889          ( 39  )
#define SYS_CLK_FREQ_8_696          ( 40  )
#define SYS_CLK_FREQ_8_511          ( 41  )
#define SYS_CLK_FREQ_8_333          ( 42  )
#define SYS_CLK_FREQ_8_163          ( 43  )
#define SYS_CLK_FREQ_8_000          ( 44  )
#define SYS_CLK_FREQ_7_843          ( 45  )
#define SYS_CLK_FREQ_7_692          ( 46  )
#define SYS_CLK_FREQ_7_547          ( 47  )
#define SYS_CLK_FREQ_7_407          ( 48  )
#define SYS_CLK_FREQ_7_273          ( 49  )
#define SYS_CLK_FREQ_7_143          ( 50  )
#define SYS_CLK_FREQ_7_018          ( 51  )
#define SYS_CLK_FREQ_6_897          ( 52  )
#define SYS_CLK_FREQ_6_780          ( 53  )
#define SYS_CLK_FREQ_6_667          ( 54  )
#define SYS_CLK_FREQ_6_557          ( 55  )
#define SYS_CLK_FREQ_6_452          ( 56  )
#define SYS_CLK_FREQ_6_349          ( 57  )
#define SYS_CLK_FREQ_6_250          ( 58  )
#define SYS_CLK_FREQ_6_154          ( 59  )
#define SYS_CLK_FREQ_6_061          ( 60  )
#define SYS_CLK_FREQ_5_970          ( 61  )
#define SYS_CLK_FREQ_5_882          ( 62  )
#define SYS_CLK_FREQ_5_797          ( 63  )
#define SYS_CLK_FREQ_5_714          ( 64  )
#define SYS_CLK_FREQ_5_634          ( 65  )
#define SYS_CLK_FREQ_5_556          ( 66  )
#define SYS_CLK_FREQ_5_479          ( 67  )
#define SYS_CLK_FREQ_5_405          ( 68  )
#define SYS_CLK_FREQ_5_333          ( 69  )
#define SYS_CLK_FREQ_5_263          ( 70  )
#define SYS_CLK_FREQ_5_195          ( 71  )
#define SYS_CLK_FREQ_5_128          ( 72  )
#define SYS_CLK_FREQ_5_063          ( 73  )
#define SYS_CLK_FREQ_5_000          ( 74  )
#define SYS_CLK_FREQ_4_938          ( 75  )
#define SYS_CLK_FREQ_4_878          ( 76  )
#define SYS_CLK_FREQ_4_819          ( 77  )
#define SYS_CLK_FREQ_4_762          ( 78  )
#define SYS_CLK_FREQ_4_706          ( 79  )
#define SYS_CLK_FREQ_4_651          ( 80  )
#define SYS_CLK_FREQ_4_598          ( 81  )
#define SYS_CLK_FREQ_4_545          ( 82  )
#define SYS_CLK_FREQ_4_494          ( 83  )
#define SYS_CLK_FREQ_4_444          ( 84  )
#define SYS_CLK_FREQ_4_396          ( 85  )
#define SYS_CLK_FREQ_4_348          ( 86  )
#define SYS_CLK_FREQ_4_301          ( 87  )
#define SYS_CLK_FREQ_4_255          ( 88  )
#define SYS_CLK_FREQ_4_211          ( 89  )
#define SYS_CLK_FREQ_4_167          ( 90  )
#define SYS_CLK_FREQ_4_124          ( 91  )
#define SYS_CLK_FREQ_4_082          ( 92  )
#define SYS_CLK_FREQ_4_040          ( 93  )
#define SYS_CLK_FREQ_4_000          ( 94  )
#define SYS_CLK_FREQ_3_960          ( 95  )
#define SYS_CLK_FREQ_3_922          ( 96  )
#define SYS_CLK_FREQ_3_883          ( 97  )
#define SYS_CLK_FREQ_3_846          ( 98  )
#define SYS_CLK_FREQ_3_810          ( 99  )
#define SYS_CLK_FREQ_3_774          ( 100 )
#define SYS_CLK_FREQ_3_738          ( 101 )
#define SYS_CLK_FREQ_3_704          ( 102 )
#define SYS_CLK_FREQ_3_670          ( 103 )
#define SYS_CLK_FREQ_3_636          ( 104 )
#define SYS_CLK_FREQ_3_604          ( 105 )
#define SYS_CLK_FREQ_3_571          ( 106 )
#define SYS_CLK_FREQ_3_540          ( 107 )
#define SYS_CLK_FREQ_3_509          ( 108 )
#define SYS_CLK_FREQ_3_478          ( 109 )
#define SYS_CLK_FREQ_3_448          ( 110 )
#define SYS_CLK_FREQ_3_419          ( 111 )
#define SYS_CLK_FREQ_3_390          ( 112 )
#define SYS_CLK_FREQ_3_361          ( 113 )
#define SYS_CLK_FREQ_3_333          ( 114 )
#define SYS_CLK_FREQ_3_306          ( 115 )
#define SYS_CLK_FREQ_3_279          ( 116 )
#define SYS_CLK_FREQ_3_252          ( 117 )
#define SYS_CLK_FREQ_3_226          ( 118 )
#define SYS_CLK_FREQ_3_200          ( 119 )
#define SYS_CLK_FREQ_3_175          ( 120 )
#define SYS_CLK_FREQ_3_150          ( 121 )
#define SYS_CLK_FREQ_3_125          ( 122 )


extern str_sysCtrCfg_t str_sysCtlCfg;

#endif /* E15_ARM_REPO_CONFIG_SYSCTR_CFG_H_ */
