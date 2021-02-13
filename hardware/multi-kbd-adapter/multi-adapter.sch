EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLedger 17000 11000
encoding utf-8
Sheet 1 1
Title "Unified Retro Keyboard multi-adapter"
Date "2021-02-13"
Rev "1.0"
Comp "OSIWeb.org"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x16 J2
U 1 1 5BCB9E1D
P 5330 8420
F 0 "J2" H 5340 9230 50  0000 C CNN
F 1 "Apple 1" H 5545 8395 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 5330 8420 50  0001 C CNN
F 3 "~" H 5330 8420 50  0001 C CNN
F 4 "YES" H 5330 8420 50  0001 C CNN "Substitution OK"
F 5 "NO" H 5330 8420 50  0001 C CNN "Fitted"
F 6 "16-pin DIP socket" H 5330 8420 50  0001 C CNN "Parameters"
F 7 "TH" H 5330 8420 50  0001 C CNN "Mount Style"
F 8 "16-pin DIP socket" H 5330 8420 50  0001 C CNN "Package"
	1    5330 8420
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x16 J1
U 1 1 5D9AB54A
P 5330 6220
F 0 "J1" H 5330 7030 50  0000 C CNN
F 1 "Apple 2" H 5555 6175 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 5330 6220 50  0001 C CNN
F 3 "~" H 5330 6220 50  0001 C CNN
F 4 "YES" H 5330 6220 50  0001 C CNN "Substitution OK"
F 5 "NO" H 5330 6220 50  0001 C CNN "Fitted"
F 6 "16-pin DIP socket" H 5330 6220 50  0001 C CNN "Parameters"
F 7 "TH" H 5330 6220 50  0001 C CNN "Mount Style"
F 8 "16-pin DIP socket" H 5330 6220 50  0001 C CNN "Package"
	1    5330 6220
	-1   0    0    -1  
$EndComp
Text Label 5630 6620 0    50   ~ 0
D0
Text Label 5630 9020 0    50   ~ 0
~STROBE
Text Label 5630 6520 0    50   ~ 0
D3
Text Label 5630 8120 0    50   ~ 0
D0
Text Label 5630 7720 0    50   ~ 0
~RESET
Text Label 5630 6420 0    50   ~ 0
D2
Text Label 5630 5620 0    50   ~ 0
~STROBE
Text Label 5630 5720 0    50   ~ 0
~RESET
Text Label 5630 7820 0    50   ~ 0
D3
Text Label 5630 8420 0    50   ~ 0
D6
Text Label 5630 8320 0    50   ~ 0
D5
Text Label 5630 6020 0    50   ~ 0
D4
Text Label 5630 5920 0    50   ~ 0
D5
Text Label 5630 8220 0    50   ~ 0
D4
Text Label 5630 6720 0    50   ~ 0
D1
Text Label 5630 8020 0    50   ~ 0
D1
Text Label 5630 6120 0    50   ~ 0
D6
Text Label 5630 7920 0    50   ~ 0
D2
Wire Wire Line
	5530 9220 6230 9220
Wire Wire Line
	6230 9220 6230 9120
Wire Wire Line
	5530 9120 6230 9120
Text Label 5630 8820 0    50   ~ 0
CLR-LOCAL
Text Notes 5515 9115 0    50   ~ 0
(D7 to +5V)
NoConn ~ 5530 8920
NoConn ~ 5530 8620
NoConn ~ 5530 8720
NoConn ~ 5530 5820
NoConn ~ 5530 6320
NoConn ~ 5530 6820
NoConn ~ 5530 6920
NoConn ~ 5530 7020
$Comp
L Connector_Generic:Conn_01x20 J5
U 1 1 5E5FA80F
P 5320 3520
F 0 "J5" H 5238 4637 50  0000 C CNN
F 1 "SOL-20" H 5555 3500 50  0000 C CNN
F 2 "unikbd:SOL20-header-vertical" H 5320 3520 50  0001 C CNN
F 3 "~" H 5320 3520 50  0001 C CNN
F 4 "YES" H 5320 3520 50  0001 C CNN "Substitution OK"
F 5 "YES" H 5320 3520 50  0001 C CNN "Fitted"
F 6 "2x10 0.1\" right angle pin header" H 5320 3520 50  0001 C CNN "Parameters"
F 7 "TH" H 5320 3520 50  0001 C CNN "Mount Style"
	1    5320 3520
	-1   0    0    -1  
$EndComp
Text Label 5660 3020 0    50   ~ 0
D0
Text Label 5660 3120 0    50   ~ 0
D1
Text Label 5660 3220 0    50   ~ 0
D2
Text Label 5660 3320 0    50   ~ 0
D3
Text Label 5670 4020 0    50   ~ 0
D4
Text Label 5670 4120 0    50   ~ 0
D5
Text Label 5670 4220 0    50   ~ 0
D6
Text Label 5670 4320 0    50   ~ 0
D7
Text Label 5660 2820 0    50   ~ 0
~STROBE
Text Label 5670 3820 0    50   ~ 0
~RESET
Text Label 5670 3920 0    50   ~ 0
CLR-LOCAL
Text Label 5840 1820 0    50   ~ 0
~RESET
Text Label 5845 1620 0    50   ~ 0
CLR-LOCAL
$Comp
L Connector_Generic:Conn_01x05 J4
U 1 1 5E83DEBE
P 5430 1720
F 0 "J4" H 5348 1295 50  0000 C CNN
F 1 "Outputs" H 5348 1386 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 5430 1720 50  0001 C CNN
F 3 "~" H 5430 1720 50  0001 C CNN
F 4 "YES" H 5430 1720 50  0001 C CNN "Substitution OK"
F 5 "NO" H 5430 1720 50  0001 C CNN "Fitted"
F 6 "1x5 0.1\" right angle header" H 5430 1720 50  0001 C CNN "Parameters"
F 7 "TH" H 5430 1720 50  0001 C CNN "Mount Style"
	1    5430 1720
	-1   0    0    1   
$EndComp
Text Label 5845 1720 0    50   ~ 0
BREAK
$Comp
L power:GND #PWR04
U 1 1 5F6EFA9F
P 6100 9390
F 0 "#PWR04" H 6100 9140 50  0001 C CNN
F 1 "GND" H 6105 9217 50  0000 C CNN
F 2 "" H 6100 9390 50  0001 C CNN
F 3 "" H 6100 9390 50  0001 C CNN
	1    6100 9390
	1    0    0    -1  
$EndComp
Wire Wire Line
	5530 8520 6100 8520
Wire Wire Line
	6100 8520 6100 9390
Wire Wire Line
	5520 2620 6130 2620
Wire Wire Line
	6130 2620 6130 3520
$Comp
L power:GND #PWR06
U 1 1 5F8830B3
P 6130 4720
F 0 "#PWR06" H 6130 4470 50  0001 C CNN
F 1 "GND" H 6135 4547 50  0000 C CNN
F 2 "" H 6130 4720 50  0001 C CNN
F 3 "" H 6130 4720 50  0001 C CNN
	1    6130 4720
	1    0    0    -1  
$EndComp
Wire Wire Line
	5520 4520 6130 4520
Connection ~ 6130 4520
Wire Wire Line
	6130 4520 6130 4720
Wire Wire Line
	5520 3520 6130 3520
Connection ~ 6130 3520
Wire Wire Line
	6130 3520 6130 3620
Wire Wire Line
	6130 3620 5520 3620
Connection ~ 6130 3620
Wire Wire Line
	6130 3620 6130 4520
Wire Wire Line
	5520 4420 6330 4420
Wire Wire Line
	6330 4420 6330 3720
Wire Wire Line
	5520 3420 6330 3420
Connection ~ 6330 3420
Wire Wire Line
	6330 3420 6330 2720
Wire Wire Line
	5520 2720 6330 2720
Connection ~ 6330 2720
Wire Wire Line
	6330 2720 6330 2520
Wire Wire Line
	5520 3720 6330 3720
Connection ~ 6330 3720
Wire Wire Line
	6330 3720 6330 3420
Wire Wire Line
	5520 2820 6530 2820
Wire Wire Line
	5520 2920 6530 2920
Text Label 5660 2920 0    50   ~ 0
BREAK
Wire Wire Line
	5630 1520 6330 1520
Wire Wire Line
	6330 1520 6330 1320
Wire Wire Line
	5630 1920 6130 1920
Wire Wire Line
	6130 1920 6130 2020
$Comp
L power:GND #PWR05
U 1 1 5F9FA5EE
P 6130 2020
F 0 "#PWR05" H 6130 1770 50  0001 C CNN
F 1 "GND" H 6135 1847 50  0000 C CNN
F 2 "" H 6130 2020 50  0001 C CNN
F 3 "" H 6130 2020 50  0001 C CNN
	1    6130 2020
	1    0    0    -1  
$EndComp
Wire Wire Line
	6530 1620 5630 1620
Wire Wire Line
	6530 1720 5630 1720
Wire Wire Line
	6530 1820 5630 1820
Wire Wire Line
	6530 3020 5520 3020
Wire Wire Line
	6530 3120 5520 3120
Wire Wire Line
	6530 3220 5520 3220
Wire Wire Line
	6530 3820 5520 3820
Wire Wire Line
	6530 3920 5520 3920
Wire Wire Line
	6530 4020 5520 4020
Wire Wire Line
	6530 4120 5520 4120
Wire Wire Line
	6530 4220 5520 4220
Wire Wire Line
	6530 4320 5520 4320
Wire Wire Line
	6530 3320 5520 3320
Wire Wire Line
	5530 5520 6230 5520
Wire Wire Line
	6230 5320 6230 5520
Wire Wire Line
	5530 6220 6030 6220
Wire Wire Line
	6530 7720 5530 7720
Wire Wire Line
	6530 7820 5530 7820
Wire Wire Line
	6530 7920 5530 7920
Wire Wire Line
	6530 8020 5530 8020
Wire Wire Line
	6530 8120 5530 8120
Wire Wire Line
	6530 8220 5530 8220
Wire Wire Line
	6530 5920 5530 5920
Wire Wire Line
	6530 6020 5530 6020
Wire Wire Line
	6530 6120 5530 6120
Wire Wire Line
	6530 5620 5530 5620
Wire Wire Line
	6530 5720 5530 5720
Wire Wire Line
	6530 8320 5530 8320
Wire Wire Line
	6530 8420 5530 8420
Wire Wire Line
	6530 8820 5530 8820
Wire Wire Line
	5530 9020 6530 9020
Wire Wire Line
	6230 9120 6230 7620
Connection ~ 6230 9120
Wire Wire Line
	6530 6420 5530 6420
Wire Wire Line
	6530 6520 5530 6520
Wire Wire Line
	6530 6620 5530 6620
Wire Wire Line
	6530 6720 5530 6720
Entry Wire Line
	6530 2820 6630 2920
Entry Wire Line
	6530 2920 6630 3020
Entry Wire Line
	6530 3020 6630 3120
Entry Wire Line
	6530 3120 6630 3220
Entry Wire Line
	6530 3220 6630 3320
Entry Wire Line
	6530 3320 6630 3420
Entry Wire Line
	6530 1620 6630 1720
Entry Wire Line
	6530 1720 6630 1820
Entry Wire Line
	6530 1820 6630 1920
Entry Wire Line
	6530 3820 6630 3920
Entry Wire Line
	6530 3920 6630 4020
Entry Wire Line
	6530 4020 6630 4120
Entry Wire Line
	6530 4120 6630 4220
Entry Wire Line
	6530 4220 6630 4320
Entry Wire Line
	6530 4320 6630 4420
Entry Wire Line
	6530 7720 6630 7620
Entry Wire Line
	6530 7820 6630 7720
Entry Wire Line
	6530 7920 6630 7820
Entry Wire Line
	6530 8020 6630 7920
Entry Wire Line
	6530 8120 6630 8020
Entry Wire Line
	6530 8220 6630 8120
Entry Wire Line
	6530 8320 6630 8220
Entry Wire Line
	6530 8420 6630 8320
Entry Wire Line
	6530 8820 6630 8720
Entry Wire Line
	6530 9020 6630 8920
Entry Wire Line
	6530 5620 6630 5520
Entry Wire Line
	6530 5720 6630 5620
Entry Wire Line
	6530 5920 6630 5820
Entry Wire Line
	6530 6020 6630 5920
Entry Wire Line
	6530 6120 6630 6020
Entry Wire Line
	6530 6420 6630 6320
Entry Wire Line
	6530 6520 6630 6420
Entry Wire Line
	6530 6620 6630 6520
Entry Wire Line
	6530 6720 6630 6620
NoConn ~ 6130 9420
$Comp
L power:GND #PWR03
U 1 1 5F4E6EA5
P 6030 7020
F 0 "#PWR03" H 6030 6770 50  0001 C CNN
F 1 "GND" H 6035 6847 50  0000 C CNN
F 2 "" H 6030 7020 50  0001 C CNN
F 3 "" H 6030 7020 50  0001 C CNN
	1    6030 7020
	1    0    0    -1  
$EndComp
Wire Wire Line
	6030 6220 6030 7020
$Comp
L power:VCC #PWR09
U 1 1 5F6991B1
P 6330 1320
F 0 "#PWR09" H 6330 1170 50  0001 C CNN
F 1 "VCC" H 6347 1493 50  0000 C CNN
F 2 "" H 6330 1320 50  0001 C CNN
F 3 "" H 6330 1320 50  0001 C CNN
	1    6330 1320
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR010
U 1 1 5F70BC32
P 6330 2520
F 0 "#PWR010" H 6330 2370 50  0001 C CNN
F 1 "VCC" H 6347 2693 50  0000 C CNN
F 2 "" H 6330 2520 50  0001 C CNN
F 3 "" H 6330 2520 50  0001 C CNN
	1    6330 2520
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR07
U 1 1 5F727A3A
P 6230 5320
F 0 "#PWR07" H 6230 5170 50  0001 C CNN
F 1 "VCC" H 6247 5493 50  0000 C CNN
F 2 "" H 6230 5320 50  0001 C CNN
F 3 "" H 6230 5320 50  0001 C CNN
	1    6230 5320
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR08
U 1 1 5F7602B8
P 6230 7620
F 0 "#PWR08" H 6230 7470 50  0001 C CNN
F 1 "VCC" H 6247 7793 50  0000 C CNN
F 2 "" H 6230 7620 50  0001 C CNN
F 3 "" H 6230 7620 50  0001 C CNN
	1    6230 7620
	1    0    0    -1  
$EndComp
Text Notes 8115 7790 0    50   ~ 0
Notes:\n\nSOL-20:\n~STROBE~ = PIN 3\n~RESET~ = PIN 13\nBREAK = PIN 4\nLOCAL = PIN 14\n\n\nApple 1:\nD7 on socket is tied high\n~STROBE~ = PIN 14\n~RESET~ = PIN 1\nCLRSCR = PIN 12\n\nApple 2:\n~STROBE~ = PIN 2\n~RESET~ = PIN 3\n\n
Wire Bus Line
	6630 1720 6630 8920
$EndSCHEMATC
