
::ultraSonic Run test

gcc .\UltraSonic_Test.c ..\..\main.c ..\..\HAL\UltraSonic\UltraSonic.c ..\Tester\tester.c -DGCC -DULTRA_SONIC

.\a.exe > .\UltraSonictestOutput.txt
