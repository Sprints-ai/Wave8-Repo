::command line to compile and run TMU_test.c module and redirect output ot a txt file

GCC ..\..\ServiceLayer\TMU\TMU.c ..\..\ServiceLayer\TMU\TMU_cfg.c ..\..\main.c ..\Tester\tester.c .\TMU_test.c ..\Tester\stubFunctions.c -DGCC -DTMU_TEST

.\a.exe > .\TMUtestOutput.txt