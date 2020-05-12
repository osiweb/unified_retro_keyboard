EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Unified Retro Keyboard ASCII Interface (2560)"
Date ""
Rev "3.2"
Comp ""
Comment1 "Keyboard connector pinout"
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
	3700 1700 4700 1700
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
	3700 2400 4700 2400
Wire Wire Line
	3700 2300 4700 2300
Wire Wire Line
	3700 2000 4700 2000
Wire Wire Line
	3700 1900 4700 1900
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
L Connector_Generic:Conn_02x20_Odd_Even J11
U 1 1 60C38260
P 3400 2500
F 0 "J11" H 3435 3525 50  0000 C CNN
F 1 "Keyboard Connector" H 3530 1310 100 0000 C CNN
F 2 "unikbd:PinHeader_2x20_P2.54mm_Vertical" H 3400 2500 50  0001 C CNN
F 3 "~" H 3400 2500 50  0001 C CNN
	1    3400 2500
	1    0    0    -1  
$EndComp
Text Notes 2235 6495 0    50   ~ 0
Special Keys:\n\nThe keys at (Row 7, Col 0), (Row 1, Col 0), and (Row7 , Col 0) are not\nwired into the matrix at the keyboard PCB, since these keys may have\nspecial handling for the OSI keyboard.\n\nFor OSI:\n(Row 7, Col 0) is Shift Lock.  Since the original Push-ON/Push-OFF keys\nare not always available, a flip-flop circuit may be substituted for the\nphysical push-on/push-off mechanism.  The row and column lines are\nbrought to the interface board for connection to the matrix.\n\n(Row1, Col 0) is BREAK, which is not wired into the matrix, but instead \ninitiates a RESET signal, after a time delay.\n\n(Row 0, Col 0) is not wired into the matrix by default\n\nFor Apple 2:\n(Row 7, Col 0) is LEFT ARROW, and is wired into the matrix.\n\n(Row1, Col 0) is not wired into the matrix\n\n(Row 0, Col 0) is the POWER indicator key, and is wired into the matrix.\n\nFor the Classic layout:\n\n(Row 7, Col 0) is “@“, and is wired into the matrix.\n\n(Row1, Col 0) is Rubout, and is wired into the matrix\n\n(Row 0, Col 0) is the POWER indicator key, and is wired into the matrix
NoConn ~ 2500 1600
NoConn ~ 2500 1700
NoConn ~ 2500 1800
NoConn ~ 2500 1900
NoConn ~ 2500 2000
NoConn ~ 2500 2100
NoConn ~ 2500 2200
NoConn ~ 2500 2300
NoConn ~ 2500 2400
NoConn ~ 2500 2500
NoConn ~ 2500 2600
NoConn ~ 2500 2700
NoConn ~ 2500 2800
NoConn ~ 2500 2900
NoConn ~ 2500 3000
NoConn ~ 2500 3100
NoConn ~ 2500 3200
NoConn ~ 2500 3300
NoConn ~ 2500 3400
NoConn ~ 2500 3500
NoConn ~ 4700 1600
NoConn ~ 4700 1700
NoConn ~ 4700 1800
NoConn ~ 4700 1900
NoConn ~ 4700 2000
NoConn ~ 4700 2100
NoConn ~ 4700 2200
NoConn ~ 4700 2300
NoConn ~ 4700 2400
NoConn ~ 4700 2500
NoConn ~ 4700 2600
NoConn ~ 4700 2700
NoConn ~ 4700 3200
NoConn ~ 4700 3300
NoConn ~ 4700 3400
NoConn ~ 4700 3500
Wire Notes Line style solid
	3826 1700 4026 1700
Wire Notes Line style solid
	3976 1650 3976 1750
Wire Notes Line
	3977 1700 3977 1693
Wire Notes Line
	3977 1693 3963 1693
Wire Notes Line
	3963 1693 3963 1684
Wire Notes Line
	3963 1684 3956 1684
Wire Notes Line
	3956 1684 3956 1676
Wire Notes Line
	3956 1676 3949 1676
Wire Notes Line
	3949 1676 3949 1665
Wire Notes Line
	3949 1665 3938 1665
Wire Notes Line
	3938 1665 3938 1656
Wire Notes Line
	3938 1656 3928 1656
Wire Notes Line style solid
	3928 1656 3928 1753
Wire Notes Line
	3928 1753 3936 1753
Wire Notes Line
	3936 1753 3936 1742
Wire Notes Line
	3936 1742 3944 1742
Wire Notes Line
	3944 1742 3944 1734
Wire Notes Line
	3944 1734 3950 1734
Wire Notes Line
	3950 1734 3950 1726
Wire Notes Line
	3950 1726 3958 1726
Wire Notes Line
	3958 1726 3958 1718
Wire Notes Line
	3958 1718 3966 1718
Wire Notes Line
	3966 1718 3966 1708
Wire Notes Line
	3966 1708 3973 1708
Wire Notes Line
	3973 1708 3973 1704
Wire Notes Line
	3973 1704 3972 1704
Wire Notes Line style solid
	3841 2098 4041 2098
Wire Notes Line style solid
	3991 2048 3991 2148
Wire Notes Line
	3992 2098 3992 2091
Wire Notes Line
	3992 2091 3978 2091
Wire Notes Line
	3978 2091 3978 2082
Wire Notes Line
	3978 2082 3971 2082
Wire Notes Line
	3971 2082 3971 2074
Wire Notes Line
	3971 2074 3964 2074
Wire Notes Line
	3964 2074 3964 2063
Wire Notes Line
	3964 2063 3953 2063
Wire Notes Line
	3953 2063 3953 2054
Wire Notes Line
	3953 2054 3943 2054
Wire Notes Line style solid
	3943 2054 3943 2151
Wire Notes Line
	3951 2151 3951 2140
Wire Notes Line
	3951 2140 3959 2140
Wire Notes Line
	3959 2140 3959 2132
Wire Notes Line
	3959 2132 3965 2132
Wire Notes Line
	3965 2132 3965 2124
Wire Notes Line
	3965 2124 3973 2124
Wire Notes Line
	3973 2124 3973 2116
Wire Notes Line
	3973 2116 3981 2116
Wire Notes Line
	3981 2116 3981 2106
Wire Notes Line
	3981 2106 3988 2106
Wire Notes Line
	3988 2106 3988 2102
Wire Notes Line
	3988 2102 3987 2102
Wire Notes Line style solid
	3850 2499 4050 2499
Wire Notes Line style solid
	4000 2449 4000 2549
Wire Notes Line
	4001 2499 4001 2492
Wire Notes Line
	4001 2492 3987 2492
Wire Notes Line
	3987 2492 3987 2483
Wire Notes Line
	3987 2483 3980 2483
Wire Notes Line
	3980 2483 3980 2475
Wire Notes Line
	3980 2475 3973 2475
Wire Notes Line
	3973 2475 3973 2464
Wire Notes Line
	3973 2464 3962 2464
Wire Notes Line
	3962 2464 3962 2455
Wire Notes Line
	3962 2455 3952 2455
Wire Notes Line style solid
	3952 2455 3952 2552
Wire Notes Line
	3960 2552 3960 2541
Wire Notes Line
	3960 2541 3968 2541
Wire Notes Line
	3968 2541 3968 2533
Wire Notes Line
	3968 2533 3974 2533
Wire Notes Line
	3974 2533 3974 2525
Wire Notes Line
	3974 2525 3982 2525
Wire Notes Line
	3982 2525 3982 2517
Wire Notes Line
	3982 2517 3990 2517
Wire Notes Line
	3990 2517 3990 2507
Wire Notes Line
	3990 2507 3997 2507
Wire Notes Line
	3997 2507 3997 2503
Wire Notes Line
	3997 2503 3996 2503
Wire Wire Line
	3700 2100 4700 2100
Wire Wire Line
	3700 2500 4700 2500
$EndSCHEMATC
