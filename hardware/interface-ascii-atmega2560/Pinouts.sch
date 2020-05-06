EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2650 2700 0    50   ~ 0
Row4
Text Label 2650 2600 0    50   ~ 0
Row5
Text Label 2650 2500 0    50   ~ 0
Row6
Text Label 2650 2400 0    50   ~ 0
Row7
Text Label 2650 2800 0    50   ~ 0
Row3
Text Label 2650 2900 0    50   ~ 0
Row2
Text Label 2650 3000 0    50   ~ 0
Row1
Text Label 2650 3100 0    50   ~ 0
Row0
Text Label 2650 1600 0    50   ~ 0
Col7
Text Label 2650 1700 0    50   ~ 0
Col6
Text Label 2650 1800 0    50   ~ 0
Col5
Text Label 2650 1900 0    50   ~ 0
Col4
Text Label 2650 2000 0    50   ~ 0
Col3
Text Label 2650 2100 0    50   ~ 0
Col2
Text Label 2650 2200 0    50   ~ 0
Col1
Text Label 2650 2300 0    50   ~ 0
Col0
Wire Wire Line
	2500 1800 3200 1800
Wire Wire Line
	2500 1700 3200 1700
Wire Wire Line
	2500 1600 3200 1600
Wire Wire Line
	2500 3000 3200 3000
Wire Wire Line
	2500 2900 3200 2900
Wire Wire Line
	2500 2800 3200 2800
Wire Wire Line
	2500 2600 3200 2600
Wire Wire Line
	2500 2500 3200 2500
Wire Wire Line
	2500 2400 3200 2400
Wire Wire Line
	2500 2300 3200 2300
Wire Wire Line
	2500 2200 3200 2200
Wire Wire Line
	2500 2000 3200 2000
Wire Wire Line
	2500 1900 3200 1900
Wire Wire Line
	2500 2100 3200 2100
Text Label 3765 3200 0    50   ~ 0
Row8
Text Label 3765 3300 0    50   ~ 0
Row9
Text Label 3765 3400 0    50   ~ 0
Row10
Wire Wire Line
	2500 3100 3200 3100
Text Label 3765 3500 0    50   ~ 0
Row11
Text Label 2650 3500 0    50   ~ 0
Row12
Text Label 2650 3300 0    50   ~ 0
Row14
Text Label 2650 3400 0    50   ~ 0
Row13
Text Label 2650 3200 0    50   ~ 0
Row15
Wire Wire Line
	2500 3200 3200 3200
Wire Wire Line
	3200 3300 2500 3300
Wire Wire Line
	2500 3400 3200 3400
Wire Wire Line
	3200 3500 2500 3500
Wire Wire Line
	2500 2700 3200 2700
Wire Wire Line
	3700 1700 3800 1700
Wire Wire Line
	3805 2100 3700 2100
Wire Wire Line
	3805 2500 3700 2500
Text Notes 4025 2500 0    50   ~ 0
Rubout
Text Notes 4095 2090 0    50   ~ 0
@
Text Notes 4045 1690 0    50   ~ 0
Power
Wire Wire Line
	3700 3200 4700 3200
Wire Wire Line
	3700 3300 4700 3300
Wire Wire Line
	3700 3400 4700 3400
Wire Wire Line
	3700 3500 4700 3500
Wire Wire Line
	3700 2700 4700 2700
Wire Wire Line
	4105 2500 4700 2500
Wire Wire Line
	3700 2400 4700 2400
Wire Wire Line
	3700 2300 4700 2300
Wire Wire Line
	4105 2100 4700 2100
Wire Wire Line
	3700 2000 4700 2000
Wire Wire Line
	3700 1900 4700 1900
Wire Wire Line
	4100 1700 4700 1700
Wire Wire Line
	3700 1600 4700 1600
NoConn ~ 3700 2800
NoConn ~ 3700 2900
NoConn ~ 3700 3000
NoConn ~ 3700 3100
Text Notes 4720 1630 0    50   ~ 0
Col 0
Text Notes 4720 1730 0    50   ~ 0
Row 0
Text Notes 4720 1830 0    50   ~ 0
LED1 +
Text Notes 4720 1930 0    50   ~ 0
LED1 -
Text Notes 4720 2030 0    50   ~ 0
Col 0
Text Notes 4720 2130 0    50   ~ 0
Row 7
Text Notes 4720 2230 0    50   ~ 0
LED2 +
Text Notes 4720 2330 0    50   ~ 0
LED2 -
Text Notes 4720 2630 0    50   ~ 0
LED3 +
Text Notes 4720 2730 0    50   ~ 0
LED3 -
Text Notes 4720 2430 0    50   ~ 0
Col 0
Text Notes 4720 2530 0    50   ~ 0
Row 1
Wire Wire Line
	3700 2600 4700 2600
Wire Wire Line
	3700 2200 4700 2200
Wire Wire Line
	3700 1800 4700 1800
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J9
U 1 1 60C38260
P 3400 2500
F 0 "J9" H 3435 3525 50  0000 C CNN
F 1 "Keyboard Connector" H 3530 1310 100 0000 C CNN
F 2 "unikbd:PinHeader_2x20_P2.54mm_Vertical" H 3400 2500 50  0001 C CNN
F 3 "~" H 3400 2500 50  0001 C CNN
	1    3400 2500
	1    0    0    -1  
$EndComp
Text Notes 2235 6495 0    50   ~ 0
Special Keys:\n\nThe keys at (Row 7, Col 0), (Row 1, Col 0), and (Row7 , Col 0) are not\nwired into the matrix at the keyboard PCB, since these keys may have\nspecial handling for the OSI keyboard.\n\nFor OSI:\n(Row 7, Col 0) is Shift Lock.  Since the original Push-ON/Push-OFF keys\nare not always available, a flip-flop circuit may be substituted for the\nphysical push-on/push-off mechanism.  The row and column lines are\nbrought to the interface board for connection to the matrix.\n\n(Row1, Col 0) is BREAK, which is not wired into the matrix, but instead \ninitiates a RESET signal, after a time delay.\n\n(Row 0, Col 0) is not wired into the matrix by default\n\nFor Apple 2:\n(Row 7, Col 0) is LEFT ARROW, and is wired into the matrix.\n\n(Row1, Col 0) is not wired into the matrix\n\n(Row 0, Col 0) is the POWER indicator key, and is wired into the matrix.\n\nFor the Classic layout:\n\n(Row 7, Col 0) is “@“, and is wired into the matrix.\n\n(Row1, Col 0) is Rubout, and is wired into the matrix\n\n(Row 0, Col 0) is the POWER indicator key, and is wired into the matrix
$EndSCHEMATC
