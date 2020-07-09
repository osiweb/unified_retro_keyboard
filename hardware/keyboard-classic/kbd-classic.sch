EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 3
Title "Unified Retro Keyboard"
Date "2020-06-17"
Rev "1.7"
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
For Apple II keyboards:\n“@“ (AT symbol) maps to “Left arrow”\n“\” maps to “Right Arrow\n“[“ (left bracket) maps to “Reset”\nDNP: “]” (right bracket), “^”, “Here is”, “Rub”, “Break”, “Repeat”, “Clear”
$Comp
L Switch:SW_Push_LED SW9
U 1 1 5DF7D21E
P 8085 2875
F 0 "SW9" V 8005 3115 50  0000 C CNN
F 1 "Caps_Lock" V 7835 2875 50  0000 C CNN
F 2 "unikbd:Key_MX_LED" H 8085 3175 50  0001 C CNN
F 3 "~" H 8085 3175 50  0001 C CNN
F 4 "NO" H 8085 2875 50  0001 C CNN "Fitted"
F 5 "NO" H 8085 2875 50  0001 C CNN "Substitution OK"
	1    8085 2875
	0    1    -1   0   
$EndComp
NoConn ~ 6045 2850
NoConn ~ 6045 2950
NoConn ~ 6045 3050
NoConn ~ 6045 3150
Wire Wire Line
	6545 1250 6545 895 
NoConn ~ 6545 3150
NoConn ~ 6545 3050
NoConn ~ 6545 2950
NoConn ~ 6545 2850
NoConn ~ 6545 2750
NoConn ~ 6545 2650
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J1
U 1 1 5D1E4169
P 6245 2150
F 0 "J1" H 6295 3267 50  0000 C CNN
F 1 "Controller" H 6295 3176 50  0000 C CNN
F 2 "unikbd:kbd_header_and_mounting_holes" H 6245 2150 50  0001 C CNN
F 3 "~" H 6245 2150 50  0001 C CNN
F 4 "YES" H 6245 2150 50  0001 C CNN "Fitted"
F 5 " YES " H 6245 2150 50  0001 C CNN "Substitution OK"
F 6 "20x2 0.1\" socket header. Mount on bottom side" H 6245 2150 50  0001 C CNN "Comment"
	1    6245 2150
	1    0    0    -1  
$EndComp
Text Label 2725 1100 2    50   ~ 0
Col7
Text Label 5995 1250 2    50   ~ 0
Col7
Text Label 5995 1350 2    50   ~ 0
Col6
Text Label 5995 1550 2    50   ~ 0
Col4
Text Label 5995 1450 2    50   ~ 0
Col5
Text Label 5995 1750 2    50   ~ 0
Col2
Text Label 5995 1650 2    50   ~ 0
Col3
Text Label 5995 1850 2    50   ~ 0
Col1
Text Label 5995 1950 2    50   ~ 0
Col0
Text Label 5995 2050 2    50   ~ 0
Row7
Text Label 5995 2150 2    50   ~ 0
Row6
Text Label 5995 2250 2    50   ~ 0
Row5
Text Label 5995 2350 2    50   ~ 0
Row4
Text Label 5995 2450 2    50   ~ 0
Row3
Text Label 5995 2550 2    50   ~ 0
Row2
Text Label 5995 2650 2    50   ~ 0
Row1
Text Label 5995 2750 2    50   ~ 0
Row0
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
Entry Wire Line
	5645 2750 5545 2650
Entry Wire Line
	5645 2650 5545 2550
Entry Wire Line
	5645 2550 5545 2450
Entry Wire Line
	5645 2450 5545 2350
Entry Wire Line
	5645 2350 5545 2250
Entry Wire Line
	5645 2250 5545 2150
Entry Wire Line
	5645 2150 5545 2050
Entry Wire Line
	5645 2050 5545 1950
Entry Wire Line
	5645 1950 5545 1850
Entry Wire Line
	5645 1850 5545 1750
Entry Wire Line
	5645 1750 5545 1650
Entry Wire Line
	5645 1650 5545 1550
Entry Wire Line
	5645 1550 5545 1450
Entry Wire Line
	5645 1450 5545 1350
Entry Wire Line
	5645 1350 5545 1250
Entry Wire Line
	5645 1250 5545 1150
Wire Wire Line
	6045 1250 5645 1250
Wire Wire Line
	5645 1350 6045 1350
Wire Wire Line
	6045 1450 5645 1450
Wire Wire Line
	6045 1550 5645 1550
Wire Wire Line
	6045 1650 5645 1650
Wire Wire Line
	5645 1750 6045 1750
Wire Wire Line
	6045 1850 5645 1850
Wire Wire Line
	5645 1950 6045 1950
Wire Wire Line
	6045 2050 5645 2050
Wire Wire Line
	5645 2150 6045 2150
Wire Wire Line
	6045 2250 5645 2250
Wire Wire Line
	5645 2350 6045 2350
Wire Wire Line
	6045 2450 5645 2450
Wire Wire Line
	5645 2550 6045 2550
Wire Wire Line
	5645 2650 6045 2650
Wire Wire Line
	5645 2750 6045 2750
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
Entry Wire Line
	9035 2670 9135 2570
Entry Wire Line
	9035 3075 9135 2975
Text Label 8685 2670 2    50   ~ 0
Row5
Text Label 8685 3075 2    50   ~ 0
Col2
$Comp
L Diode:1N4148 D?
U 1 1 5DFE048B
P 8385 2670
AR Path="/5BC3E99D/5DFE048B" Ref="D?"  Part="1" 
AR Path="/5BC3EA0A/5DFE048B" Ref="D?"  Part="1" 
AR Path="/5DFE048B" Ref="D10"  Part="1" 
F 0 "D10" H 8431 2591 50  0000 R CNN
F 1 "1N4148" H 8460 2770 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8385 2495 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8385 2670 50  0001 C CNN
F 4 "YES" H 8385 2670 50  0001 C CNN "Fitted"
F 5 " YES " H 8385 2670 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8385 2670 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8385 2670 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8385 2670 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8385 2670 50  0001 C CNN "Package"
	1    8385 2670
	-1   0    0    1   
$EndComp
Wire Wire Line
	9035 2670 8535 2670
$Comp
L Switch:SW_Push SW?
U 1 1 5D6C3751
P 7500 2275
AR Path="/5BC3E99D/5D6C3751" Ref="SW?"  Part="1" 
AR Path="/5D6C3751" Ref="SW34"  Part="1" 
F 0 "SW34" H 7250 2325 50  0000 C CNN
F 1 "Rubout (OSI Break)" H 7370 2225 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7500 2475 50  0001 C CNN
F 3 "" H 7500 2475 50  0001 C CNN
F 4 "Common to all layouts" H 7500 2275 50  0001 C CNN "Comment"
F 5 "YES" H 7500 2275 50  0001 C CNN "Fitted"
F 6 "NO" H 7500 2275 50  0001 C CNN "Substitution OK"
	1    7500 2275
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8755 1750 9000 1750
Wire Wire Line
	9000 1750 9000 1525
Wire Wire Line
	9000 1525 8295 1525
Wire Wire Line
	8295 1525 8295 1650
NoConn ~ 6545 2550
NoConn ~ 6545 2450
Text Notes 580  6180 0    79   ~ 0
For Classic ASCII keyboards:\n“@“ (AT symbol) is mapped to R7 C0\n“Rubout” is mapped to R1 C0\n“Power Button” is mapped to R0 C0\n
Wire Wire Line
	8185 3075 9035 3075
Wire Wire Line
	8235 2670 8185 2670
Wire Wire Line
	8185 2670 8185 2675
$Comp
L Device:LED D33
U 1 1 5E12925F
P 8535 2045
F 0 "D33" H 8750 2095 50  0000 R CNN
F 1 "LED" H 8445 2100 50  0001 R CNN
F 2 "LED_THT:LED_D5.0mm" H 8535 2045 50  0001 C CNN
F 3 "~" H 8535 2045 50  0001 C CNN
F 4 "NO" H 8535 2045 50  0001 C CNN "Fitted"
F 5 " YES " H 8535 2045 50  0001 C CNN "Substitution OK"
F 6 "3mm Through-hole LED, 0.1\" spacing" H 8535 2045 50  0001 C CNN "Comment"
	1    8535 2045
	-1   0    0    -1  
$EndComp
Wire Bus Line
	2925 700  5545 700 
Wire Wire Line
	6545 2350 6700 2350
Wire Wire Line
	6700 2350 6700 3075
Wire Wire Line
	6545 1650 8295 1650
Wire Wire Line
	6545 1750 8355 1750
Wire Wire Line
	8995 1850 8755 1850
Wire Wire Line
	8245 1850 8245 2045
Wire Wire Line
	8245 2045 8385 2045
Wire Wire Line
	8245 1850 8355 1850
Wire Wire Line
	8685 2045 8995 2045
Connection ~ 8995 2045
Wire Wire Line
	8995 2045 8995 1850
Wire Wire Line
	6700 3075 7435 3075
$Comp
L Device:R_US R2
U 1 1 5FEAB402
P 7500 1850
F 0 "R2" V 7465 1635 50  0000 C CNN
F 1 "470" V 7465 2010 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7540 1840 50  0001 C CNN
F 3 "~" H 7500 1850 50  0001 C CNN
F 4 "If R1-R3 installed, then DNP R4-R6" H 7500 1850 50  0001 C CNN "Comment"
F 5 "NO" H 7500 1850 50  0001 C CNN "Fitted"
F 6 "Generic Through hole" H 7500 1850 50  0001 C CNN "Manufacturer"
F 7 " YES " H 7500 1850 50  0001 C CNN "Substitution OK"
F 8 "1%" H 7500 1850 50  0001 C CNN "tolerance"
	1    7500 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	6545 1850 7115 1850
Wire Wire Line
	7650 1850 7850 1850
Connection ~ 8245 1850
$Comp
L Device:R_US R1
U 1 1 5FED4095
P 7050 1450
F 0 "R1" V 7010 1255 50  0000 C CNN
F 1 "470" V 7010 1590 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7090 1440 50  0001 C CNN
F 3 "~" H 7050 1450 50  0001 C CNN
F 4 "If R1-R3 installed, then DNP R4-R6" H 7050 1450 50  0001 C CNN "Comment"
F 5 "NO" H 7050 1450 50  0001 C CNN "Fitted"
F 6 "Generic Through hole" H 7050 1450 50  0001 C CNN "Manufacturer"
F 7 " YES " H 7050 1450 50  0001 C CNN "Substitution OK"
F 8 "1%" H 7050 1450 50  0001 C CNN "tolerance"
	1    7050 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	6545 1450 6750 1450
Wire Bus Line
	5545 700  9135 700 
Connection ~ 5545 700 
$Comp
L unikbd:SW_Push_LED SW32
U 1 1 5EEA388A
P 8555 1850
F 0 "SW32" H 8660 2050 50  0000 C CNN
F 1 "@ (OSI ShiftLock)" H 8645 2115 50  0000 C CNN
F 2 "unikbd:Key_MX_LED" H 8555 2150 50  0001 C CNN
F 3 "~" H 8555 2150 50  0001 C CNN
F 4 "Common to all layouts" H 8555 1850 50  0001 C CNN "Comment"
F 5 "YES" H 8555 1850 50  0001 C CNN "Fitted"
F 6 "NO" H 8555 1850 50  0001 C CNN "Substitution OK"
	1    8555 1850
	1    0    0    -1  
$EndComp
$Comp
L unikbd:SW_Push_LED SW61
U 1 1 5EE9EA4F
P 7830 1260
F 0 "SW61" H 7960 1465 50  0000 C CNN
F 1 "Power Light" H 7830 1550 50  0000 C CNN
F 2 "unikbd:Key_MX_LED" H 7830 1560 50  0001 C CNN
F 3 "~" H 7830 1560 50  0001 C CNN
F 4 "NO" H 7830 1260 50  0001 C CNN "Fitted"
F 5 "NO" H 7830 1260 50  0001 C CNN "Substitution OK"
	1    7830 1260
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1450 7400 1450
Wire Wire Line
	7490 1450 7490 1260
Wire Wire Line
	7490 1260 7630 1260
Wire Wire Line
	6545 1350 6620 1350
Wire Wire Line
	6620 1350 6620 1160
Wire Wire Line
	6620 1160 7630 1160
Wire Wire Line
	6545 895  8270 895 
Wire Wire Line
	8270 895  8270 1160
Wire Wire Line
	8270 1160 8030 1160
Wire Wire Line
	6545 1550 8270 1550
Wire Wire Line
	8270 1260 8030 1260
Wire Wire Line
	8270 1260 8270 1450
$Comp
L Device:LED D62
U 1 1 5EE7A83E
P 7825 1450
F 0 "D62" H 8040 1500 50  0000 R CNN
F 1 "LED" H 7735 1505 50  0001 R CNN
F 2 "LED_THT:LED_D2.0mm_W4.8mm_H2.5mm_FlatTop" H 7825 1450 50  0001 C CNN
F 3 "~" H 7825 1450 50  0001 C CNN
F 4 "NO" H 7825 1450 50  0001 C CNN "Fitted"
F 5 " YES " H 7825 1450 50  0001 C CNN "Substitution OK"
F 6 "3mm Through-hole LED, 0.1\" spacing" H 7825 1450 50  0001 C CNN "Comment"
	1    7825 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7675 1450 7490 1450
Connection ~ 7490 1450
Wire Wire Line
	7975 1450 8270 1450
Connection ~ 8270 1450
Wire Wire Line
	8270 1450 8270 1550
$Comp
L Device:LED D63
U 1 1 5EE84B07
P 7745 2870
F 0 "D63" V 7830 3015 50  0000 R CNN
F 1 "LED" V 7845 2845 50  0001 R CNN
F 2 "LED_THT:LED_D2.0mm_W4.8mm_H2.5mm_FlatTop" H 7745 2870 50  0001 C CNN
F 3 "~" H 7745 2870 50  0001 C CNN
F 4 "NO" H 7745 2870 50  0001 C CNN "Fitted"
F 5 " YES " H 7745 2870 50  0001 C CNN "Substitution OK"
F 6 "3mm Through-hole LED, 0.1\" spacing" H 7745 2870 50  0001 C CNN "Comment"
	1    7745 2870
	0    1    -1   0   
$EndComp
Wire Wire Line
	7745 3020 7745 3075
Connection ~ 7745 3075
Wire Wire Line
	7745 3075 8085 3075
Wire Wire Line
	7745 2720 7745 2655
Wire Wire Line
	7745 2655 8085 2655
Connection ~ 8085 2655
Wire Wire Line
	8085 2655 8085 2675
Wire Wire Line
	8995 2370 8995 2245
Wire Wire Line
	8190 2370 8995 2370
$Comp
L Device:LED D64
U 1 1 5EE9DF56
P 8535 2245
F 0 "D64" H 8735 2295 50  0000 R CNN
F 1 "LED" V 8635 2220 50  0001 R CNN
F 2 "LED_THT:LED_D2.0mm_W4.8mm_H2.5mm_FlatTop" H 8535 2245 50  0001 C CNN
F 3 "~" H 8535 2245 50  0001 C CNN
F 4 "NO" H 8535 2245 50  0001 C CNN "Fitted"
F 5 " YES " H 8535 2245 50  0001 C CNN "Substitution OK"
F 6 "3mm Through-hole LED, 0.1\" spacing" H 8535 2245 50  0001 C CNN "Comment"
	1    8535 2245
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8385 2245 8245 2245
Wire Wire Line
	8245 2245 8245 2045
Connection ~ 8245 2045
Wire Wire Line
	8685 2245 8995 2245
Connection ~ 8995 2245
Wire Wire Line
	8995 2245 8995 2045
$Comp
L Switch:SW_Push_LED SW17
U 1 1 5EE923F1
P 8085 3675
F 0 "SW17" V 8005 3915 50  0000 C CNN
F 1 "Line_Feed" V 7835 3675 50  0000 C CNN
F 2 "unikbd:Key_MX_LED" H 8085 3975 50  0001 C CNN
F 3 "~" H 8085 3975 50  0001 C CNN
F 4 "Common to all layouts" H 8085 3675 50  0001 C CNN "Comment"
F 5 "YES" H 8085 3675 50  0001 C CNN "Fitted"
F 6 "NO" H 8085 3675 50  0001 C CNN "Substitution OK"
	1    8085 3675
	0    1    -1   0   
$EndComp
Entry Wire Line
	9035 3470 9135 3370
Entry Wire Line
	9035 3875 9135 3775
Text Label 8685 3470 2    50   ~ 0
Row5
Text Label 8685 3875 2    50   ~ 0
Col4
$Comp
L Diode:1N4148 D?
U 1 1 5EE923FB
P 8385 3470
AR Path="/5BC3E99D/5EE923FB" Ref="D?"  Part="1" 
AR Path="/5BC3EA0A/5EE923FB" Ref="D?"  Part="1" 
AR Path="/5EE923FB" Ref="D18"  Part="1" 
F 0 "D18" H 8431 3391 50  0000 R CNN
F 1 "1N4148" H 8460 3570 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8385 3295 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8385 3470 50  0001 C CNN
F 4 "YES" H 8385 3470 50  0001 C CNN "Fitted"
F 5 " YES " H 8385 3470 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8385 3470 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8385 3470 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8385 3470 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8385 3470 50  0001 C CNN "Package"
	1    8385 3470
	-1   0    0    1   
$EndComp
Wire Wire Line
	9035 3470 8535 3470
Wire Wire Line
	8185 3875 9035 3875
Wire Wire Line
	8235 3470 8185 3470
Wire Wire Line
	8185 3470 8185 3475
Wire Wire Line
	8085 3455 8085 3475
$Comp
L Device:R_US R3
U 1 1 5FED3098
P 7500 2540
F 0 "R3" V 7450 2645 50  0000 L CNN
F 1 "470" V 7455 2290 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7540 2530 50  0001 C CNN
F 3 "~" H 7500 2540 50  0001 C CNN
F 4 "If R1-R3 installed, then DNP R4-R6" H 7500 2540 50  0001 C CNN "Comment"
F 5 "NO" H 7500 2540 50  0001 C CNN "Fitted"
F 6 "Generic Through hole" H 7500 2540 50  0001 C CNN "Manufacturer"
F 7 " YES " H 7500 2540 50  0001 C CNN "Substitution OK"
F 8 "1%" H 7500 2540 50  0001 C CNN "tolerance"
	1    7500 2540
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6545 2250 6800 2250
Wire Wire Line
	7650 2540 8085 2540
Wire Wire Line
	7435 3875 7435 3075
Connection ~ 7435 3075
Wire Wire Line
	7435 3075 7745 3075
Wire Wire Line
	7745 2655 7605 2655
Wire Wire Line
	7605 2655 7605 3455
Wire Wire Line
	7605 3455 7745 3455
Connection ~ 7745 2655
$Comp
L Device:LED D65
U 1 1 5EECE7DC
P 7745 3670
F 0 "D65" V 7830 3815 50  0000 R CNN
F 1 "LED" V 7845 3645 50  0001 R CNN
F 2 "LED_THT:LED_D2.0mm_W4.8mm_H2.5mm_FlatTop" H 7745 3670 50  0001 C CNN
F 3 "~" H 7745 3670 50  0001 C CNN
F 4 "NO" H 7745 3670 50  0001 C CNN "Fitted"
F 5 " YES " H 7745 3670 50  0001 C CNN "Substitution OK"
F 6 "3mm Through-hole LED, 0.1\" spacing" H 7745 3670 50  0001 C CNN "Comment"
	1    7745 3670
	0    1    -1   0   
$EndComp
Wire Wire Line
	7745 3820 7745 3875
Wire Wire Line
	7435 3875 7745 3875
Connection ~ 7745 3875
Wire Wire Line
	7745 3875 8085 3875
Wire Wire Line
	7745 3520 7745 3455
Connection ~ 7745 3455
Wire Wire Line
	7745 3455 8085 3455
Wire Wire Line
	8085 2540 8085 2655
Wire Wire Line
	6800 2250 6800 2540
Wire Wire Line
	6800 2540 7200 2540
$Comp
L Device:R_US R6
U 1 1 5F057BC7
P 7500 2425
F 0 "R6" V 7455 2540 50  0000 L CNN
F 1 "470" V 7460 2185 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7540 2415 50  0001 C CNN
F 3 "https://industrial.panasonic.com/cdbs/www-data/pdf/RDA0000/DMA0000COL9.pdf~" H 7500 2425 50  0001 C CNN
F 4 "If R4-R6 installed, then DNP R1-R3" H 7500 2425 50  0001 C CNN "Comment"
F 5 "YES" H 7500 2425 50  0001 C CNN "Fitted"
F 6 "Panasonic" H 7500 2425 50  0001 C CNN "Manufacturer"
F 7 "ERJ-3EKF3300V" H 7500 2425 50  0001 C CNN "Manufacturer Part Number"
F 8 " YES " H 7500 2425 50  0001 C CNN "Substitution OK"
F 9 "1%" H 7500 2425 50  0001 C CNN "tolerance"
	1    7500 2425
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8190 2085 8190 2370
$Comp
L Device:R_US R5
U 1 1 5F082E1F
P 7500 1950
F 0 "R5" V 7465 1735 50  0000 C CNN
F 1 "470" V 7465 2110 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7540 1940 50  0001 C CNN
F 3 "https://industrial.panasonic.com/cdbs/www-data/pdf/RDA0000/DMA0000COL9.pdf~" H 7500 1950 50  0001 C CNN
F 4 "If R4-R6 installed, then DNP R1-R3" H 7500 1950 50  0001 C CNN "Comment"
F 5 "YES" H 7500 1950 50  0001 C CNN "Fitted"
F 6 "Panasonic" H 7500 1950 50  0001 C CNN "Manufacturer"
F 7 "ERJ-3EKF3300V" H 7500 1950 50  0001 C CNN "Manufacturer Part Number"
F 8 " YES " H 7500 1950 50  0001 C CNN "Substitution OK"
F 9 "1%" H 7500 1950 50  0001 C CNN "tolerance"
	1    7500 1950
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R4
U 1 1 5F08C312
P 7050 1350
F 0 "R4" V 7010 1155 50  0000 C CNN
F 1 "470" V 7010 1490 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7090 1340 50  0001 C CNN
F 3 "https://industrial.panasonic.com/cdbs/www-data/pdf/RDA0000/DMA0000COL9.pdf~" H 7050 1350 50  0001 C CNN
F 4 "If R4-R6 installed, then DNP R1-R3" H 7050 1350 50  0001 C CNN "Comment"
F 5 "YES" H 7050 1350 50  0001 C CNN "Fitted"
F 6 "Panasonic" H 7050 1350 50  0001 C CNN "Manufacturer"
F 7 "ERJ-3EKF3300V" H 7050 1350 50  0001 C CNN "Manufacturer Part Number"
F 8 " YES " H 7050 1350 50  0001 C CNN "Substitution OK"
F 9 "1%" H 7050 1350 50  0001 C CNN "tolerance"
	1    7050 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	6750 1450 6750 1350
Wire Wire Line
	6750 1350 6900 1350
Connection ~ 6750 1450
Wire Wire Line
	6750 1450 6900 1450
Wire Wire Line
	7200 1350 7400 1350
Wire Wire Line
	7400 1350 7400 1450
Connection ~ 7400 1450
Wire Wire Line
	7400 1450 7490 1450
Wire Wire Line
	7350 2425 7200 2425
Wire Wire Line
	7200 2425 7200 2540
Connection ~ 7200 2540
Wire Wire Line
	7200 2540 7350 2540
Wire Wire Line
	7650 2425 8085 2425
Wire Wire Line
	8085 2540 8085 2425
Connection ~ 8085 2540
Wire Wire Line
	7650 1950 7850 1950
Wire Wire Line
	7850 1950 7850 1850
Connection ~ 7850 1850
Wire Wire Line
	7850 1850 8245 1850
Wire Wire Line
	7350 1950 7115 1950
Wire Wire Line
	7115 1950 7115 1850
Connection ~ 7115 1850
Wire Wire Line
	7115 1850 7350 1850
Wire Wire Line
	6545 1950 7075 1950
Wire Wire Line
	7075 1950 7075 2085
Wire Wire Line
	7075 2085 8190 2085
Wire Wire Line
	6545 2050 6990 2050
Wire Wire Line
	6990 2050 6990 2115
Wire Wire Line
	6990 2115 7825 2115
Wire Wire Line
	7825 2115 7825 2275
Wire Wire Line
	7825 2275 7700 2275
Wire Wire Line
	7300 2275 6850 2275
Wire Wire Line
	6850 2275 6850 2150
Wire Wire Line
	6850 2150 6545 2150
Wire Bus Line
	9135 700  9135 3775
Wire Bus Line
	5545 700  5545 2650
Wire Bus Line
	2925 700  2925 4700
$EndSCHEMATC
