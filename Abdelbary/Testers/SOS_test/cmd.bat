::command line to compile and run SOS_test.c module and redirect output ot a txt file

GCC ..\..\ServiceLayer\SOS\SOS.c ..\..\ServiceLayer\SOS\SOS_cfg.c ..\..\main.c ..\Tester\tester.c ..\Tester\stubFunctions.c .\SOS_test.c -DGCC -DSOS_TEST

.\a.exe > SOStestOutput.txt