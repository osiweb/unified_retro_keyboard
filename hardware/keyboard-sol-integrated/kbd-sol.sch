EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 5
Title "Sol-20 keyboard"
Date "2020-12-30"
Rev "2.0"
Comp "OSIWeb.org"
Comment1 "Main sheet with connector"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2725 4300 2    50   ~ 0
Col0
Text Label 2725 4200 2    50   ~ 0
Col1
Text Label 2725 4100 2    50   ~ 0
Col2
Text Label 2725 4000 2    50   ~ 0
Col3
Text Label 2725 3900 2    50   ~ 0
Col4
Text Label 2725 3800 2    50   ~ 0
Col5
Text Label 2725 3700 2    50   ~ 0
Col6
Text Label 2725 3600 2    50   ~ 0
Col7
Text Label 2725 1800 2    50   ~ 0
Col0
Text Label 2725 1700 2    50   ~ 0
Col1
Text Label 2725 1600 2    50   ~ 0
Col2
Text Label 2725 1500 2    50   ~ 0
Col3
Text Label 2725 1400 2    50   ~ 0
Col4
Text Label 2725 1300 2    50   ~ 0
Col5
Text Label 2725 1200 2    50   ~ 0
Col6
Text Label 2725 4800 2    50   ~ 0
Row0
Text Label 2725 4700 2    50   ~ 0
Row1
Text Label 2725 4600 2    50   ~ 0
Row2
Text Label 2725 4500 2    50   ~ 0
Row3
Text Label 2725 2350 2    50   ~ 0
Row4
Text Label 2725 2250 2    50   ~ 0
Row5
Text Label 2725 2150 2    50   ~ 0
Row6
Text Label 2725 2050 2    50   ~ 0
Row7
$Sheet
S 775  900  1700 1900
U 5BC3EA0A
F0 "keys2" 60
F1 "keys2.sch" 60
F2 "Col0" I R 2475 1800 50 
F3 "Col1" I R 2475 1700 50 
F4 "Col2" I R 2475 1600 50 
F5 "Col3" I R 2475 1500 50 
F6 "Col4" I R 2475 1400 50 
F7 "Col5" I R 2475 1300 50 
F8 "Col6" I R 2475 1200 50 
F9 "Col7" I R 2475 1100 50 
F10 "Row4" I R 2475 2350 50 
F11 "Row5" I R 2475 2250 50 
F12 "Row6" I R 2475 2150 50 
F13 "Row7" I R 2475 2050 50 
$EndSheet
$Sheet
S 775  3400 1700 1900
U 5BC3E99D
F0 "keys1" 60
F1 "keys1.sch" 60
F2 "Col0" I R 2475 4300 50 
F3 "Col1" I R 2475 4200 50 
F4 "Col2" I R 2475 4100 50 
F5 "Col3" I R 2475 4000 50 
F6 "Col4" I R 2475 3900 50 
F7 "Col5" I R 2475 3800 50 
F8 "Col6" I R 2475 3700 50 
F9 "Col7" I R 2475 3600 50 
F10 "Row0" I R 2475 4800 50 
F11 "Row1" I R 2475 4700 50 
F12 "Row2" I R 2475 4600 50 
F13 "Row3" I R 2475 4500 50 
$EndSheet
Text Notes 580  7070 0    79   ~ 0
For OSI keyboards:\n“@“ (AT symbol) maps to “Shift Lock”, R0 C0\n“[“ (left bracket) maps to “Rub Out”, R6 C2\n“\” maps to “Repeat”, R0 C7\n“Rubout” maps to “Break”, \nDNP: “]” (right bracket), “^”, “Here is”, “Break”, “Repeat”, “Clear”
Text Notes 600  7905 0    79   ~ 0
For Apple II keyboards:\n"@" (AT symbol) maps to "Left arrow"\n"\" maps to "Right Arrow"\n"[" (left bracket) maps to "Reset"\n\nDNP: "]" (right bracket), "^", "Here is", "Rub", "Break", "Repeat", "Clear"
Text Label 2725 1100 2    50   ~ 0
Col7
Entry Wire Line
	2825 1800 2925 1700
Entry Wire Line
	2825 1700 2925 1600
Entry Wire Line
	2825 1600 2925 1500
Entry Wire Line
	2825 1500 2925 1400
Entry Wire Line
	2825 1400 2925 1300
Entry Wire Line
	2825 1300 2925 1200
Entry Wire Line
	2825 1200 2925 1100
Entry Wire Line
	2825 1100 2925 1000
Entry Wire Line
	2825 2350 2925 2250
Entry Wire Line
	2825 2250 2925 2150
Entry Wire Line
	2825 2150 2925 2050
Entry Wire Line
	2825 2050 2925 1950
Entry Wire Line
	2825 4300 2925 4200
Entry Wire Line
	2825 4200 2925 4100
Entry Wire Line
	2825 4100 2925 4000
Entry Wire Line
	2825 4000 2925 3900
Entry Wire Line
	2825 3900 2925 3800
Entry Wire Line
	2825 3800 2925 3700
Entry Wire Line
	2825 3700 2925 3600
Entry Wire Line
	2825 3600 2925 3500
Entry Wire Line
	2825 4800 2925 4700
Entry Wire Line
	2825 4700 2925 4600
Entry Wire Line
	2825 4600 2925 4500
Entry Wire Line
	2825 4500 2925 4400
Wire Wire Line
	2475 1100 2825 1100
Wire Wire Line
	2825 1200 2475 1200
Wire Wire Line
	2475 1300 2825 1300
Wire Wire Line
	2825 1400 2475 1400
Wire Wire Line
	2475 1500 2825 1500
Wire Wire Line
	2825 1600 2475 1600
Wire Wire Line
	2475 1700 2825 1700
Wire Wire Line
	2825 1800 2475 1800
Wire Wire Line
	2475 3600 2825 3600
Wire Wire Line
	2825 3700 2475 3700
Wire Wire Line
	2475 3800 2825 3800
Wire Wire Line
	2825 3900 2475 3900
Wire Wire Line
	2475 4000 2825 4000
Wire Wire Line
	2825 4100 2475 4100
Wire Wire Line
	2475 4200 2825 4200
Wire Wire Line
	2825 4300 2475 4300
Wire Wire Line
	2475 2050 2825 2050
Wire Wire Line
	2825 2150 2475 2150
Wire Wire Line
	2475 2250 2825 2250
Wire Wire Line
	2825 2350 2475 2350
Wire Wire Line
	2475 4500 2825 4500
Wire Wire Line
	2825 4600 2475 4600
Wire Wire Line
	2475 4700 2825 4700
Wire Wire Line
	2825 4800 2475 4800
Wire Bus Line
	2925 700  5820 700 
Text Notes 580  6180 0    79   ~ 0
For Classic ASCII keyboards:\n“@“ (AT symbol) is mapped to R7 C0\n“Rubout” is mapped to R1 C0\n“Power Button” is mapped to R0 C0\n
$Sheet
S 3670 910  1700 1900
U 5E16AC8E
F0 "sheet5E16AC80" 60
F1 "keys3.sch" 60
F2 "Col0" I R 5370 1810 50 
F3 "Col1" I R 5370 1710 50 
F4 "Col2" I R 5370 1610 50 
F5 "Col3" I R 5370 1510 50 
F6 "Col4" I R 5370 1410 50 
F7 "Col5" I R 5370 1310 50 
F8 "Col6" I R 5370 1210 50 
F9 "Col7" I R 5370 1110 50 
F10 "Row9" I R 5370 2310 50 
F11 "Row10" I R 5370 2210 50 
F12 "Row11" I R 5370 2110 50 
F13 "Row12" I R 5370 2010 50 
$EndSheet
Text Label 5620 1810 2    50   ~ 0
Col0
Text Label 5620 1710 2    50   ~ 0
Col1
Text Label 5620 1610 2    50   ~ 0
Col2
Text Label 5620 1510 2    50   ~ 0
Col3
Text Label 5620 1410 2    50   ~ 0
Col4
Text Label 5620 1310 2    50   ~ 0
Col5
Text Label 5620 1210 2    50   ~ 0
Col6
Text Label 5610 2310 2    50   ~ 0
Row9
Text Label 5655 2210 2    50   ~ 0
Row10
Text Label 5660 2110 2    50   ~ 0
Row11
Text Label 5660 2010 2    50   ~ 0
Row12
Text Label 5620 1110 2    50   ~ 0
Col7
Entry Wire Line
	5720 1810 5820 1710
Entry Wire Line
	5720 1710 5820 1610
Entry Wire Line
	5720 1610 5820 1510
Entry Wire Line
	5720 1510 5820 1410
Entry Wire Line
	5720 1410 5820 1310
Entry Wire Line
	5720 1310 5820 1210
Entry Wire Line
	5720 1210 5820 1110
Entry Wire Line
	5720 1110 5820 1010
Entry Wire Line
	5720 2310 5820 2210
Entry Wire Line
	5720 2210 5820 2110
Entry Wire Line
	5720 2110 5820 2010
Entry Wire Line
	5720 2010 5820 1910
Wire Wire Line
	5370 1110 5720 1110
Wire Wire Line
	5720 1210 5370 1210
Wire Wire Line
	5370 1310 5720 1310
Wire Wire Line
	5720 1410 5370 1410
Wire Wire Line
	5370 1510 5720 1510
Wire Wire Line
	5720 1610 5370 1610
Wire Wire Line
	5370 1710 5720 1710
Wire Wire Line
	5720 1810 5370 1810
Wire Wire Line
	5370 2010 5720 2010
Wire Wire Line
	5720 2110 5370 2110
Wire Wire Line
	5370 2210 5720 2210
Wire Wire Line
	5720 2310 5370 2310
Connection ~ 5820 700 
Text Label 7650 2250 0    50   ~ 0
Row9
Text Label 7650 2150 0    50   ~ 0
Row10
Text Label 7650 2050 0    50   ~ 0
Row11
$Comp
L Device:LED LED1
U 1 1 5E34C1C3
P 6980 4010
F 0 "LED1" H 6970 3890 50  0000 C CNN
F 1 "LED" H 6973 3846 50  0001 C CNN
F 2 "LED_THT:LED_D3.0mm" H 6980 4010 50  0001 C CNN
F 3 "~" H 6980 4010 50  0001 C CNN
	1    6980 4010
	-1   0    0    1   
$EndComp
$Comp
L Device:LED LED2
U 1 1 5E34D862
P 6980 4410
F 0 "LED2" H 6950 4300 50  0000 C CNN
F 1 "LED" H 6973 4246 50  0001 C CNN
F 2 "LED_THT:LED_D3.0mm" H 6980 4410 50  0001 C CNN
F 3 "~" H 6980 4410 50  0001 C CNN
	1    6980 4410
	-1   0    0    1   
$EndComp
$Comp
L Device:LED LED3
U 1 1 5E34E748
P 6980 4810
F 0 "LED3" H 6970 4700 50  0000 C CNN
F 1 "LED" H 6973 4646 50  0001 C CNN
F 2 "LED_THT:LED_D3.0mm" H 6980 4810 50  0001 C CNN
F 3 "~" H 6980 4810 50  0001 C CNN
	1    6980 4810
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R3
U 1 1 5FE3FF66
P 7500 4810
F 0 "R3" V 7455 4645 50  0000 C CNN
F 1 "330" V 7450 4940 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7540 4800 50  0001 C CNN
F 3 "~" H 7500 4810 50  0001 C CNN
	1    7500 4810
	0    1    1    0   
$EndComp
Wire Wire Line
	7130 4010 7270 4010
Wire Wire Line
	7650 4010 7690 4010
$Comp
L Device:R_US R4
U 1 1 5FD1B584
P 7500 3910
F 0 "R4" V 7460 3760 50  0000 C CNN
F 1 "330" V 7450 4060 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7540 3900 50  0001 C CNN
F 3 "~" H 7500 3910 50  0001 C CNN
	1    7500 3910
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R6
U 1 1 5FD3023D
P 7500 4710
F 0 "R6" V 7455 4545 50  0000 C CNN
F 1 "330" V 7450 4840 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7540 4700 50  0001 C CNN
F 3 "~" H 7500 4710 50  0001 C CNN
	1    7500 4710
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R5
U 1 1 5FD386C5
P 7500 4310
F 0 "R5" V 7460 4160 50  0000 C CNN
F 1 "330" V 7460 4460 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7540 4300 50  0001 C CNN
F 3 "~" H 7500 4310 50  0001 C CNN
	1    7500 4310
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 3910 7690 3910
Wire Wire Line
	7690 3910 7690 4010
Connection ~ 7690 4010
Wire Wire Line
	7690 4010 7900 4010
Wire Wire Line
	7350 3910 7270 3910
Wire Wire Line
	7270 3910 7270 4010
Connection ~ 7270 4010
Wire Wire Line
	7270 4010 7350 4010
Wire Wire Line
	7130 4810 7260 4810
Wire Wire Line
	7350 4710 7260 4710
Wire Wire Line
	7260 4710 7260 4810
Connection ~ 7260 4810
Wire Wire Line
	7260 4810 7350 4810
Wire Wire Line
	7650 4810 7710 4810
Wire Wire Line
	7650 4710 7710 4710
Wire Wire Line
	7710 4710 7710 4810
Connection ~ 7710 4810
Wire Wire Line
	7710 4810 7900 4810
Wire Wire Line
	7130 4410 7280 4410
Wire Wire Line
	7350 4310 7280 4310
Wire Wire Line
	7280 4310 7280 4410
Connection ~ 7280 4410
Wire Wire Line
	7280 4410 7350 4410
Wire Wire Line
	7650 4410 7710 4410
Wire Wire Line
	7710 4410 7710 4310
Wire Wire Line
	7710 4310 7650 4310
Connection ~ 7710 4410
Wire Wire Line
	7710 4410 7900 4410
NoConn ~ 7240 4100
Wire Wire Line
	6750 3610 6750 4010
Wire Wire Line
	6750 4810 6830 4810
Connection ~ 6750 4410
Wire Wire Line
	6750 4410 6830 4410
Wire Wire Line
	6750 4410 6750 4810
Connection ~ 6750 4010
Wire Wire Line
	6750 4010 6830 4010
Wire Wire Line
	6750 4010 6750 4410
Text Label 7650 1950 0    50   ~ 0
Row12
Wire Wire Line
	7500 3040 7900 3040
Wire Wire Line
	7500 2940 7900 2940
Wire Wire Line
	7500 2840 7900 2840
Wire Wire Line
	7900 2740 7500 2740
Wire Wire Line
	7500 2640 7900 2640
Wire Wire Line
	7900 2540 7500 2540
Wire Wire Line
	7500 2440 7900 2440
Wire Wire Line
	7900 2340 7500 2340
Wire Wire Line
	7500 1660 7900 1660
Wire Wire Line
	7900 1560 7500 1560
Wire Wire Line
	7500 1460 7900 1460
Wire Wire Line
	7900 1360 7500 1360
Wire Wire Line
	7900 1260 7500 1260
Wire Wire Line
	7900 1160 7500 1160
Wire Wire Line
	7500 1060 7900 1060
Wire Wire Line
	7900 960  7500 960 
Entry Wire Line
	7500 960  7400 860 
Entry Wire Line
	7500 1060 7400 960 
Entry Wire Line
	7500 1160 7400 1060
Entry Wire Line
	7500 1260 7400 1160
Entry Wire Line
	7500 1360 7400 1260
Entry Wire Line
	7500 1460 7400 1360
Entry Wire Line
	7500 1560 7400 1460
Entry Wire Line
	7500 1660 7400 1560
Entry Wire Line
	7500 2340 7400 2240
Entry Wire Line
	7500 2440 7400 2340
Entry Wire Line
	7500 2540 7400 2440
Entry Wire Line
	7500 2640 7400 2540
Entry Wire Line
	7500 2740 7400 2640
Entry Wire Line
	7500 2840 7400 2740
Entry Wire Line
	7500 2940 7400 2840
Entry Wire Line
	7500 3040 7400 2940
Text Label 7850 3040 2    50   ~ 0
Row0
Text Label 7850 2940 2    50   ~ 0
Row1
Text Label 7850 2840 2    50   ~ 0
Row2
Text Label 7850 2740 2    50   ~ 0
Row3
Text Label 7850 2640 2    50   ~ 0
Row4
Text Label 7850 2540 2    50   ~ 0
Row5
Text Label 7850 2440 2    50   ~ 0
Row6
Text Label 7850 2340 2    50   ~ 0
Row7
Text Label 7850 1660 2    50   ~ 0
Col0
Text Label 7850 1560 2    50   ~ 0
Col1
Text Label 7850 1360 2    50   ~ 0
Col3
Text Label 7850 1460 2    50   ~ 0
Col2
Text Label 7850 1160 2    50   ~ 0
Col5
Text Label 7850 1260 2    50   ~ 0
Col4
Text Label 7850 1060 2    50   ~ 0
Col6
Text Label 7850 960  2    50   ~ 0
Col7
Entry Wire Line
	7500 1950 7400 1850
Entry Wire Line
	7500 2050 7400 1950
Entry Wire Line
	7500 2150 7400 2050
Entry Wire Line
	7500 2250 7400 2150
Wire Wire Line
	7500 2250 7900 2250
Wire Wire Line
	7900 2150 7500 2150
Wire Wire Line
	7500 2050 7900 2050
Wire Wire Line
	7900 1950 7500 1950
Wire Bus Line
	5820 700  7400 700 
$Sheet
S 7900 800  1670 4420
U 5FEDB7E2
F0 "encoder" 50
F1 "encoder-smt.sch" 50
F2 "Row0" O L 7900 3040 50 
F3 "Row1" O L 7900 2940 50 
F4 "Row2" O L 7900 2840 50 
F5 "Row3" O L 7900 2740 50 
F6 "Row4" O L 7900 2640 50 
F7 "Row5" O L 7900 2540 50 
F8 "Row6" O L 7900 2440 50 
F9 "Row7" O L 7900 2340 50 
F10 "Row9" O L 7900 2250 50 
F11 "Row10" O L 7900 2150 50 
F12 "Row11" O L 7900 2050 50 
F13 "Row12" O L 7900 1950 50 
F14 "Row13" O L 7900 3200 50 
F15 "Row14" O L 7900 3290 50 
F16 "Row15" O L 7900 3370 50 
F17 "LED1" O L 7900 4010 50 
F18 "LED2" O L 7900 4410 50 
F19 "LED3" O L 7900 4810 50 
F20 "Col0" I L 7900 1660 50 
F21 "Col1" I L 7900 1560 50 
F22 "Col2" I L 7900 1460 50 
F23 "Col3" I L 7900 1360 50 
F24 "Col4" I L 7900 1260 50 
F25 "Col5" I L 7900 1160 50 
F26 "Col6" I L 7900 1060 50 
F27 "Col7" I L 7900 960 50 
$EndSheet
Wire Wire Line
	7900 3290 7790 3290
NoConn ~ 7790 3290
NoConn ~ 7790 3370
NoConn ~ 7790 3200
Wire Wire Line
	7790 3200 7900 3200
Wire Wire Line
	7790 3370 7900 3370
$Comp
L power:VCC #PWR0101
U 1 1 6043591C
P 6750 3610
F 0 "#PWR0101" H 6750 3460 50  0001 C CNN
F 1 "VCC" H 6765 3783 50  0000 C CNN
F 2 "" H 6750 3610 50  0001 C CNN
F 3 "" H 6750 3610 50  0001 C CNN
	1    6750 3610
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 5FE42937
P 7500 4410
F 0 "R2" V 7460 4260 50  0000 C CNN
F 1 "330" V 7386 4410 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7540 4400 50  0001 C CNN
F 3 "~" H 7500 4410 50  0001 C CNN
	1    7500 4410
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R1
U 1 1 5FE4484A
P 7500 4010
F 0 "R1" V 7460 3860 50  0000 C CNN
F 1 "330" V 7386 4010 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7540 4000 50  0001 C CNN
F 3 "~" H 7500 4010 50  0001 C CNN
	1    7500 4010
	0    1    1    0   
$EndComp
Wire Bus Line
	5820 700  5820 2210
Wire Bus Line
	7400 700  7400 2940
Wire Bus Line
	2925 700  2925 4700
$EndSCHEMATC
