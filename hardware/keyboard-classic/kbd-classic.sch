EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 3
Title "Unified Retro Keyboard"
Date "2019-08-25"
Rev "1.3"
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
$Comp
L Switch:SW_Push_LED SW9
U 1 1 5DF7D21E
P 9250 2875
F 0 "SW9" V 9170 3115 50  0000 C CNN
F 1 "Caps_Lock" V 9000 2875 50  0000 C CNN
F 2 "unikbd:Key_MX_LED" H 9250 3175 50  0001 C CNN
F 3 "~" H 9250 3175 50  0001 C CNN
	1    9250 2875
	0    1    -1   0   
$EndComp
$Comp
L Switch:SW_Push_LED SW32
U 1 1 5DF7DA75
P 9425 1850
F 0 "SW32" H 9150 2025 50  0000 C CNN
F 1 "@ (OSI shift lock)" H 9300 2125 50  0000 C CNN
F 2 "unikbd:Key_MX_LED" H 9425 2150 50  0001 C CNN
F 3 "~" H 9425 2150 50  0001 C CNN
	1    9425 1850
	-1   0    0    -1  
$EndComp
NoConn ~ 7900 2850
NoConn ~ 7900 2950
NoConn ~ 7900 3050
NoConn ~ 7900 3150
$Comp
L Switch:SW_Push_LED SW61
U 1 1 5DF0C543
P 8730 1450
F 0 "SW61" H 8600 1660 50  0000 C CNN
F 1 "Power light" H 8760 1750 50  0000 C CNN
F 2 "unikbd:Key_MX_LED" H 8730 1750 50  0001 C CNN
F 3 "~" H 8730 1750 50  0001 C CNN
	1    8730 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8400 1450 8530 1450
Wire Wire Line
	9000 1550 8400 1550
Wire Wire Line
	9000 1450 9000 1550
Wire Wire Line
	8930 1450 9000 1450
Wire Wire Line
	8990 1350 8930 1350
Wire Wire Line
	8990 1070 8990 1350
Wire Wire Line
	8400 1070 8990 1070
Wire Wire Line
	8400 1250 8400 1070
Wire Wire Line
	8530 1350 8400 1350
NoConn ~ 8400 3150
NoConn ~ 8400 3050
NoConn ~ 8400 2950
NoConn ~ 8400 2850
NoConn ~ 8400 2750
NoConn ~ 8400 2650
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J1
U 1 1 5D1E4169
P 8100 2150
F 0 "J1" H 8150 3267 50  0000 C CNN
F 1 "Controller" H 8150 3176 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical" H 8100 2150 50  0001 C CNN
F 3 "~" H 8100 2150 50  0001 C CNN
	1    8100 2150
	1    0    0    -1  
$EndComp
Text Label 2725 1100 2    50   ~ 0
Col7
Text Label 7850 1250 2    50   ~ 0
Col7
Text Label 7850 1350 2    50   ~ 0
Col6
Text Label 7850 1550 2    50   ~ 0
Col4
Text Label 7850 1450 2    50   ~ 0
Col5
Text Label 7850 1750 2    50   ~ 0
Col2
Text Label 7850 1650 2    50   ~ 0
Col3
Text Label 7850 1850 2    50   ~ 0
Col1
Text Label 7850 1950 2    50   ~ 0
Col0
Text Label 7850 2050 2    50   ~ 0
Row7
Text Label 7850 2150 2    50   ~ 0
Row6
Text Label 7850 2250 2    50   ~ 0
Row5
Text Label 7850 2350 2    50   ~ 0
Row4
Text Label 7850 2450 2    50   ~ 0
Row3
Text Label 7850 2550 2    50   ~ 0
Row2
Text Label 7850 2650 2    50   ~ 0
Row1
Text Label 7850 2750 2    50   ~ 0
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
	7500 2750 7400 2650
Entry Wire Line
	7500 2650 7400 2550
Entry Wire Line
	7500 2550 7400 2450
Entry Wire Line
	7500 2450 7400 2350
Entry Wire Line
	7500 2350 7400 2250
Entry Wire Line
	7500 2250 7400 2150
Entry Wire Line
	7500 2150 7400 2050
Entry Wire Line
	7500 2050 7400 1950
Entry Wire Line
	7500 1950 7400 1850
Entry Wire Line
	7500 1850 7400 1750
Entry Wire Line
	7500 1750 7400 1650
Entry Wire Line
	7500 1650 7400 1550
Entry Wire Line
	7500 1550 7400 1450
Entry Wire Line
	7500 1450 7400 1350
Entry Wire Line
	7500 1350 7400 1250
Entry Wire Line
	7500 1250 7400 1150
Wire Wire Line
	7900 1250 7500 1250
Wire Wire Line
	7500 1350 7900 1350
Wire Wire Line
	7900 1450 7500 1450
Wire Wire Line
	7900 1550 7500 1550
Wire Wire Line
	7900 1650 7500 1650
Wire Wire Line
	7500 1750 7900 1750
Wire Wire Line
	7900 1850 7500 1850
Wire Wire Line
	7500 1950 7900 1950
Wire Wire Line
	7900 2050 7500 2050
Wire Wire Line
	7500 2150 7900 2150
Wire Wire Line
	7900 2250 7500 2250
Wire Wire Line
	7500 2350 7900 2350
Wire Wire Line
	7900 2450 7500 2450
Wire Wire Line
	7500 2550 7900 2550
Wire Wire Line
	7500 2650 7900 2650
Wire Wire Line
	7500 2750 7900 2750
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
	2925 700  7400 700 
Wire Wire Line
	9250 2250 9250 2675
Entry Wire Line
	10200 2670 10300 2570
Entry Wire Line
	10200 3075 10300 2975
Wire Bus Line
	10300 700  7400 700 
Connection ~ 7400 700 
Text Label 9850 2670 2    50   ~ 0
Row5
Text Label 9850 3075 2    50   ~ 0
Col2
$Comp
L Diode:1N4148 D?
U 1 1 5DFE048B
P 9550 2670
AR Path="/5BC3E99D/5DFE048B" Ref="D?"  Part="1" 
AR Path="/5BC3EA0A/5DFE048B" Ref="D?"  Part="1" 
AR Path="/5DFE048B" Ref="D10"  Part="1" 
F 0 "D10" H 9596 2591 50  0000 R CNN
F 1 "1N4148" H 9625 2770 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9550 2495 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 9550 2670 50  0001 C CNN
	1    9550 2670
	-1   0    0    1   
$EndComp
Wire Wire Line
	10200 2670 9700 2670
Wire Wire Line
	8400 2050 9700 2050
$Comp
L Switch:SW_Push SW?
U 1 1 5D6C3751
P 9900 2050
AR Path="/5BC3E99D/5D6C3751" Ref="SW?"  Part="1" 
AR Path="/5D6C3751" Ref="SW34"  Part="1" 
F 0 "SW34" H 9650 2100 50  0000 C CNN
F 1 "Rubout (OSI Break)" H 9770 2000 50  0000 C CNN
F 2 "unikbd:Key_MX" H 9900 2250 50  0001 C CNN
F 3 "" H 9900 2250 50  0001 C CNN
	1    9900 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9225 1750 8400 1750
Wire Wire Line
	9625 1750 9900 1750
Wire Wire Line
	9900 1750 9900 1525
Wire Wire Line
	9900 1525 9175 1525
Wire Wire Line
	9175 1525 9175 1650
Wire Wire Line
	9175 1650 8400 1650
Wire Wire Line
	8400 1850 9225 1850
Wire Wire Line
	9625 1850 9775 1850
Wire Wire Line
	9775 1850 9775 1950
Wire Wire Line
	9775 1950 8400 1950
Wire Wire Line
	10100 2050 10150 2050
Wire Wire Line
	10150 2050 10150 2150
Wire Wire Line
	10150 2150 8400 2150
NoConn ~ 8400 2550
NoConn ~ 8400 2450
Text Notes 580  6180 0    79   ~ 0
For Classic ASCII keyboards:\n“@“ (AT symbol) is mapped to R7 C0\n“Rubout” is mapped to R1 C0\n“Power Button” is mapped to R0 C0\n
Wire Wire Line
	9350 3075 10200 3075
Wire Wire Line
	9400 2670 9350 2670
Wire Wire Line
	9350 2670 9350 2675
Wire Wire Line
	8790 2350 8400 2350
Wire Wire Line
	8790 3075 8790 2350
Wire Bus Line
	10300 700  10300 2975
Wire Bus Line
	7400 700  7400 2650
Wire Bus Line
	2925 700  2925 4700
Wire Wire Line
	8920 3075 8790 3075
Wire Wire Line
	9250 3075 8920 3075
Connection ~ 8920 3075
Wire Wire Line
	8920 3020 8920 3075
Wire Wire Line
	8920 2250 9250 2250
Wire Wire Line
	8400 2250 8920 2250
Connection ~ 8920 2250
Wire Wire Line
	8920 2720 8920 2250
$Comp
L Device:LED D33
U 1 1 5E12925F
P 8920 2870
F 0 "D33" V 8959 2753 50  0000 R CNN
F 1 "LED" V 8868 2753 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 8920 2870 50  0001 C CNN
F 3 "~" H 8920 2870 50  0001 C CNN
	1    8920 2870
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
