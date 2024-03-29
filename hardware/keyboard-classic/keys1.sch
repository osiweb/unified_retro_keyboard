EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title "Unified Retro Keyboard"
Date "2021-11-24"
Rev "1.12"
Comp "OSIWeb.org"
Comment1 "Key Matrix part 2"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1450 4500 0    60   Input ~ 0
Row1
Text HLabel 1450 5400 0    60   Input ~ 0
Row2
Text HLabel 1450 6300 0    60   Input ~ 0
Row3
Text HLabel 1450 3600 0    60   Input ~ 0
Row0
Text HLabel 1450 1100 0    60   Input ~ 0
Col7
Text HLabel 1450 1300 0    60   Input ~ 0
Col6
Text HLabel 1450 1500 0    60   Input ~ 0
Col5
Text HLabel 1450 1700 0    60   Input ~ 0
Col4
Text HLabel 1450 1900 0    60   Input ~ 0
Col3
Text HLabel 1450 2100 0    60   Input ~ 0
Col2
Text HLabel 1450 2300 0    60   Input ~ 0
Col1
Text HLabel 1450 2500 0    60   Input ~ 0
Col0
$Comp
L Switch:SW_Push SW35
U 1 1 5BC3FD26
P 3800 3200
F 0 "SW35" H 3800 3485 50  0000 C CNN
F 1 "R_Shift" H 3800 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 3400 50  0001 C CNN
F 3 "" H 3800 3400 50  0001 C CNN
F 4 "Common to all layouts" H 3800 3200 50  0001 C CNN "Comment"
F 5 "YES" H 3800 3200 50  0001 C CNN "Fitted"
F 6 "NO" H 3800 3200 50  0001 C CNN "Substitution OK"
	1    3800 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW39
U 1 1 5BC3FE57
P 4600 3200
F 0 "SW39" H 4600 3485 50  0000 C CNN
F 1 "L_Shift" H 4600 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 3400 50  0001 C CNN
F 3 "" H 4600 3400 50  0001 C CNN
F 4 "Common to all layouts" H 4600 3200 50  0001 C CNN "Comment"
F 5 "YES" H 4600 3200 50  0001 C CNN "Fitted"
F 6 "NO" H 4600 3200 50  0001 C CNN "Substitution OK"
	1    4600 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW49
U 1 1 5BC3FF69
P 7000 3200
F 0 "SW49" H 7000 3485 50  0000 C CNN
F 1 "TAB" H 7000 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7000 3400 50  0001 C CNN
F 3 "" H 7000 3400 50  0001 C CNN
F 4 "Common to all layouts" H 7000 3200 50  0001 C CNN "Comment"
F 5 "YES" H 7000 3200 50  0001 C CNN "Fitted"
F 6 "NO" H 7000 3200 50  0001 C CNN "Substitution OK"
	1    7000 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW57
U 1 1 5BC3FF70
P 8600 3200
F 0 "SW57" H 8600 3485 50  0000 C CNN
F 1 "Backslash" H 8600 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 8600 3400 50  0001 C CNN
F 3 "" H 8600 3400 50  0001 C CNN
F 4 "Common to all layouts" H 8600 3200 50  0001 C CNN "Comment"
F 5 "YES" H 8600 3200 50  0001 C CNN "Fitted"
F 6 "NO" H 8600 3200 50  0001 C CNN "Substitution OK"
	1    8600 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW53
U 1 1 5BC3FF77
P 7800 3200
F 0 "SW53" H 7800 3485 50  0000 C CNN
F 1 "CTRL" H 7800 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7800 3400 50  0001 C CNN
F 3 "" H 7800 3400 50  0001 C CNN
F 4 "Common to all layouts" H 7800 3200 50  0001 C CNN "Comment"
F 5 "YES" H 7800 3200 50  0001 C CNN "Fitted"
F 6 "NO" H 7800 3200 50  0001 C CNN "Substitution OK"
	1    7800 3200
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D36
U 1 1 5BC6C862
P 4000 3450
F 0 "D36" V 4046 3371 50  0000 R CNN
F 1 "1N4148" V 3955 3371 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4000 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 3450 50  0001 C CNN
F 4 "YES" H 4000 3450 50  0001 C CNN "Fitted"
F 5 " YES " H 4000 3450 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4000 3450 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4000 3450 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4000 3450 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4000 3450 50  0001 C CNN "Package"
F 10 "C118751" H 4000 3450 50  0001 C CNN "LCSC"
	1    4000 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D40
U 1 1 5BC6CA8E
P 4800 3450
F 0 "D40" V 4846 3371 50  0000 R CNN
F 1 "1N4148" V 4755 3371 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4800 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 3450 50  0001 C CNN
F 4 "YES" H 4800 3450 50  0001 C CNN "Fitted"
F 5 " YES " H 4800 3450 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4800 3450 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4800 3450 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4800 3450 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4800 3450 50  0001 C CNN "Package"
F 10 "C118751" H 4800 3450 50  0001 C CNN "LCSC"
	1    4800 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D50
U 1 1 5BC6CB1B
P 7200 3450
F 0 "D50" V 7246 3371 50  0000 R CNN
F 1 "1N4148" V 7155 3371 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7200 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 7200 3450 50  0001 C CNN
F 4 "YES" H 7200 3450 50  0001 C CNN "Fitted"
F 5 " YES " H 7200 3450 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 7200 3450 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 7200 3450 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 7200 3450 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 7200 3450 50  0001 C CNN "Package"
F 10 "C118751" H 7200 3450 50  0001 C CNN "LCSC"
	1    7200 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D54
U 1 1 5BC6CB46
P 8000 3450
F 0 "D54" V 8046 3371 50  0000 R CNN
F 1 "1N4148" V 7955 3371 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8000 3450 50  0001 C CNN
F 4 "YES" H 8000 3450 50  0001 C CNN "Fitted"
F 5 " YES " H 8000 3450 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8000 3450 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8000 3450 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8000 3450 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8000 3450 50  0001 C CNN "Package"
F 10 "C118751" H 8000 3450 50  0001 C CNN "LCSC"
	1    8000 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D58
U 1 1 5BC6CB6F
P 8800 3450
F 0 "D58" V 8846 3371 50  0000 R CNN
F 1 "1N4148" V 8755 3371 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8800 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8800 3450 50  0001 C CNN
F 4 "YES" H 8800 3450 50  0001 C CNN "Fitted"
F 5 " YES " H 8800 3450 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8800 3450 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8800 3450 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8800 3450 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8800 3450 50  0001 C CNN "Package"
F 10 "C118751" H 8800 3450 50  0001 C CNN "LCSC"
	1    8800 3450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW36
U 1 1 5BC6CD5D
P 3800 4100
F 0 "SW36" H 3800 4385 50  0000 C CNN
F 1 "P" H 3800 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 4300 50  0001 C CNN
F 3 "" H 3800 4300 50  0001 C CNN
F 4 "Common to all layouts" H 3800 4100 50  0001 C CNN "Comment"
F 5 "YES" H 3800 4100 50  0001 C CNN "Fitted"
F 6 "NO" H 3800 4100 50  0001 C CNN "Substitution OK"
	1    3800 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW43
U 1 1 5BC6CD64
P 5400 4100
F 0 "SW43" H 5400 4385 50  0000 C CNN
F 1 "Fwd_Slash" H 5400 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 5400 4300 50  0001 C CNN
F 3 "" H 5400 4300 50  0001 C CNN
F 4 "Common to all layouts" H 5400 4100 50  0001 C CNN "Comment"
F 5 "YES" H 5400 4100 50  0001 C CNN "Fitted"
F 6 "NO" H 5400 4100 50  0001 C CNN "Substitution OK"
	1    5400 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW40
U 1 1 5BC6CD6B
P 4600 4100
F 0 "SW40" H 4600 4385 50  0000 C CNN
F 1 "Semicolon" H 4600 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 4300 50  0001 C CNN
F 3 "" H 4600 4300 50  0001 C CNN
F 4 "Common to all layouts" H 4600 4100 50  0001 C CNN "Comment"
F 5 "YES" H 4600 4100 50  0001 C CNN "Fitted"
F 6 "NO" H 4600 4100 50  0001 C CNN "Substitution OK"
	1    4600 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW46
U 1 1 5BC6CD72
P 6200 4100
F 0 "SW46" H 6200 4385 50  0000 C CNN
F 1 "SPACE" H 6200 4294 50  0000 C CNN
F 2 "unikbd:Key_MX_Spacebar_5.25" H 6200 4300 50  0001 C CNN
F 3 "" H 6200 4300 50  0001 C CNN
F 4 "Common to all layouts" H 6200 4100 50  0001 C CNN "Comment"
F 5 "YES" H 6200 4100 50  0001 C CNN "Fitted"
F 6 "NO" H 6200 4100 50  0001 C CNN "Substitution OK"
	1    6200 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW50
U 1 1 5BC6CD79
P 7000 4100
F 0 "SW50" H 7000 4385 50  0000 C CNN
F 1 "Z" H 7000 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7000 4300 50  0001 C CNN
F 3 "" H 7000 4300 50  0001 C CNN
F 4 "Common to all layouts" H 7000 4100 50  0001 C CNN "Comment"
F 5 "YES" H 7000 4100 50  0001 C CNN "Fitted"
F 6 "NO" H 7000 4100 50  0001 C CNN "Substitution OK"
	1    7000 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW58
U 1 1 5BC6CD80
P 8600 4100
F 0 "SW58" H 8600 4385 50  0000 C CNN
F 1 "Q" H 8600 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 8600 4300 50  0001 C CNN
F 3 "" H 8600 4300 50  0001 C CNN
F 4 "Common to all layouts" H 8600 4100 50  0001 C CNN "Comment"
F 5 "YES" H 8600 4100 50  0001 C CNN "Fitted"
F 6 "NO" H 8600 4100 50  0001 C CNN "Substitution OK"
	1    8600 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW54
U 1 1 5BC6CD87
P 7800 4100
F 0 "SW54" H 7800 4385 50  0000 C CNN
F 1 "A" H 7800 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7800 4300 50  0001 C CNN
F 3 "" H 7800 4300 50  0001 C CNN
F 4 "Common to all layouts" H 7800 4100 50  0001 C CNN "Comment"
F 5 "YES" H 7800 4100 50  0001 C CNN "Fitted"
F 6 "NO" H 7800 4100 50  0001 C CNN "Substitution OK"
	1    7800 4100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D37
U 1 1 5BC6CD8E
P 4000 4350
F 0 "D37" V 4046 4271 50  0000 R CNN
F 1 "1N4148" V 3955 4271 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4000 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 4350 50  0001 C CNN
F 4 "YES" H 4000 4350 50  0001 C CNN "Fitted"
F 5 " YES " H 4000 4350 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4000 4350 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4000 4350 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4000 4350 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4000 4350 50  0001 C CNN "Package"
F 10 "C118751" H 4000 4350 50  0001 C CNN "LCSC"
	1    4000 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D41
U 1 1 5BC6CD9C
P 4800 4350
F 0 "D41" V 4846 4271 50  0000 R CNN
F 1 "1N4148" V 4755 4271 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4800 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 4350 50  0001 C CNN
F 4 "YES" H 4800 4350 50  0001 C CNN "Fitted"
F 5 " YES " H 4800 4350 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4800 4350 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4800 4350 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4800 4350 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4800 4350 50  0001 C CNN "Package"
F 10 "C118751" H 4800 4350 50  0001 C CNN "LCSC"
	1    4800 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D44
U 1 1 5BC6CDA3
P 5600 4350
F 0 "D44" V 5646 4271 50  0000 R CNN
F 1 "1N4148" V 5555 4271 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5600 4350 50  0001 C CNN
F 4 "YES" H 5600 4350 50  0001 C CNN "Fitted"
F 5 " YES " H 5600 4350 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 5600 4350 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 5600 4350 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 5600 4350 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 5600 4350 50  0001 C CNN "Package"
F 10 "C118751" H 5600 4350 50  0001 C CNN "LCSC"
	1    5600 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D47
U 1 1 5BC6CDAA
P 6400 4350
F 0 "D47" V 6446 4271 50  0000 R CNN
F 1 "1N4148" V 6355 4271 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6400 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6400 4350 50  0001 C CNN
F 4 "YES" H 6400 4350 50  0001 C CNN "Fitted"
F 5 " YES " H 6400 4350 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 6400 4350 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 6400 4350 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 6400 4350 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 6400 4350 50  0001 C CNN "Package"
F 10 "C118751" H 6400 4350 50  0001 C CNN "LCSC"
	1    6400 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D51
U 1 1 5BC6CDB1
P 7200 4350
F 0 "D51" V 7246 4271 50  0000 R CNN
F 1 "1N4148" V 7155 4271 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7200 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 7200 4350 50  0001 C CNN
F 4 "YES" H 7200 4350 50  0001 C CNN "Fitted"
F 5 " YES " H 7200 4350 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 7200 4350 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 7200 4350 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 7200 4350 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 7200 4350 50  0001 C CNN "Package"
F 10 "C118751" H 7200 4350 50  0001 C CNN "LCSC"
	1    7200 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D55
U 1 1 5BC6CDB8
P 8000 4350
F 0 "D55" V 8046 4271 50  0000 R CNN
F 1 "1N4148" V 7955 4271 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8000 4350 50  0001 C CNN
F 4 "YES" H 8000 4350 50  0001 C CNN "Fitted"
F 5 " YES " H 8000 4350 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8000 4350 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8000 4350 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8000 4350 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8000 4350 50  0001 C CNN "Package"
F 10 "C118751" H 8000 4350 50  0001 C CNN "LCSC"
	1    8000 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D59
U 1 1 5BC6CDBF
P 8800 4350
F 0 "D59" V 8846 4271 50  0000 R CNN
F 1 "1N4148" V 8755 4271 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8800 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8800 4350 50  0001 C CNN
F 4 "YES" H 8800 4350 50  0001 C CNN "Fitted"
F 5 " YES " H 8800 4350 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8800 4350 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8800 4350 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8800 4350 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8800 4350 50  0001 C CNN "Package"
F 10 "C118751" H 8800 4350 50  0001 C CNN "LCSC"
	1    8800 4350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW33
U 1 1 5BC6CED6
P 3000 5000
F 0 "SW33" H 3000 5285 50  0000 C CNN
F 1 "Break" H 3000 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3000 5200 50  0001 C CNN
F 3 "" H 3000 5200 50  0001 C CNN
F 4 "NO" H 3000 5000 50  0001 C CNN "Fitted"
F 5 "NO" H 3000 5000 50  0001 C CNN "Substitution OK"
	1    3000 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW37
U 1 1 5BC6CEDD
P 3800 5000
F 0 "SW37" H 3800 5285 50  0000 C CNN
F 1 "Comma" H 3800 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 5200 50  0001 C CNN
F 3 "" H 3800 5200 50  0001 C CNN
F 4 "Common to all layouts" H 3800 5000 50  0001 C CNN "Comment"
F 5 "YES" H 3800 5000 50  0001 C CNN "Fitted"
F 6 "NO" H 3800 5000 50  0001 C CNN "Substitution OK"
	1    3800 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW44
U 1 1 5BC6CEE4
P 5400 5000
F 0 "SW44" H 5400 5285 50  0000 C CNN
F 1 "N" H 5400 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 5400 5200 50  0001 C CNN
F 3 "" H 5400 5200 50  0001 C CNN
F 4 "Common to all layouts" H 5400 5000 50  0001 C CNN "Comment"
F 5 "YES" H 5400 5000 50  0001 C CNN "Fitted"
F 6 "NO" H 5400 5000 50  0001 C CNN "Substitution OK"
	1    5400 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW41
U 1 1 5BC6CEEB
P 4600 5000
F 0 "SW41" H 4600 5285 50  0000 C CNN
F 1 "M" H 4600 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 5200 50  0001 C CNN
F 3 "" H 4600 5200 50  0001 C CNN
F 4 "Common to all layouts" H 4600 5000 50  0001 C CNN "Comment"
F 5 "YES" H 4600 5000 50  0001 C CNN "Fitted"
F 6 "NO" H 4600 5000 50  0001 C CNN "Substitution OK"
	1    4600 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW47
U 1 1 5BC6CEF2
P 6200 5000
F 0 "SW47" H 6200 5285 50  0000 C CNN
F 1 "B" H 6200 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 6200 5200 50  0001 C CNN
F 3 "" H 6200 5200 50  0001 C CNN
F 4 "Common to all layouts" H 6200 5000 50  0001 C CNN "Comment"
F 5 "YES" H 6200 5000 50  0001 C CNN "Fitted"
F 6 "NO" H 6200 5000 50  0001 C CNN "Substitution OK"
	1    6200 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW51
U 1 1 5BC6CEF9
P 7000 5000
F 0 "SW51" H 7000 5285 50  0000 C CNN
F 1 "V" H 7000 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7000 5200 50  0001 C CNN
F 3 "" H 7000 5200 50  0001 C CNN
F 4 "Common to all layouts" H 7000 5000 50  0001 C CNN "Comment"
F 5 "YES" H 7000 5000 50  0001 C CNN "Fitted"
F 6 "NO" H 7000 5000 50  0001 C CNN "Substitution OK"
	1    7000 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW59
U 1 1 5BC6CF00
P 8600 5000
F 0 "SW59" H 8600 5285 50  0000 C CNN
F 1 "X" H 8600 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 8600 5200 50  0001 C CNN
F 3 "" H 8600 5200 50  0001 C CNN
F 4 "Common to all layouts" H 8600 5000 50  0001 C CNN "Comment"
F 5 "YES" H 8600 5000 50  0001 C CNN "Fitted"
F 6 "NO" H 8600 5000 50  0001 C CNN "Substitution OK"
	1    8600 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW55
U 1 1 5BC6CF07
P 7800 5000
F 0 "SW55" H 7800 5285 50  0000 C CNN
F 1 "C" H 7800 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7800 5200 50  0001 C CNN
F 3 "" H 7800 5200 50  0001 C CNN
F 4 "Common to all layouts" H 7800 5000 50  0001 C CNN "Comment"
F 5 "YES" H 7800 5000 50  0001 C CNN "Fitted"
F 6 "NO" H 7800 5000 50  0001 C CNN "Substitution OK"
	1    7800 5000
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D38
U 1 1 5BC6CF0E
P 4000 5250
F 0 "D38" V 4046 5171 50  0000 R CNN
F 1 "1N4148" V 3955 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4000 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 5250 50  0001 C CNN
F 4 "YES" H 4000 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 4000 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4000 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4000 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4000 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4000 5250 50  0001 C CNN "Package"
F 10 "C118751" H 4000 5250 50  0001 C CNN "LCSC"
	1    4000 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D34
U 1 1 5BC6CF15
P 3200 5250
F 0 "D34" V 3246 5171 50  0000 R CNN
F 1 "1N4148" V 3155 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3200 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 3200 5250 50  0001 C CNN
F 4 "YES" H 3200 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 3200 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 3200 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 3200 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 3200 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 3200 5250 50  0001 C CNN "Package"
F 10 "C118751" H 3200 5250 50  0001 C CNN "LCSC"
	1    3200 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D42
U 1 1 5BC6CF1C
P 4800 5250
F 0 "D42" V 4846 5171 50  0000 R CNN
F 1 "1N4148" V 4755 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4800 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 5250 50  0001 C CNN
F 4 "YES" H 4800 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 4800 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4800 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4800 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4800 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4800 5250 50  0001 C CNN "Package"
F 10 "C118751" H 4800 5250 50  0001 C CNN "LCSC"
	1    4800 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D45
U 1 1 5BC6CF23
P 5600 5250
F 0 "D45" V 5646 5171 50  0000 R CNN
F 1 "1N4148" V 5555 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5600 5250 50  0001 C CNN
F 4 "YES" H 5600 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 5600 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 5600 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 5600 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 5600 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 5600 5250 50  0001 C CNN "Package"
F 10 "C118751" H 5600 5250 50  0001 C CNN "LCSC"
	1    5600 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D48
U 1 1 5BC6CF2A
P 6400 5250
F 0 "D48" V 6446 5171 50  0000 R CNN
F 1 "1N4148" V 6355 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6400 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6400 5250 50  0001 C CNN
F 4 "YES" H 6400 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 6400 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 6400 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 6400 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 6400 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 6400 5250 50  0001 C CNN "Package"
F 10 "C118751" H 6400 5250 50  0001 C CNN "LCSC"
	1    6400 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D52
U 1 1 5BC6CF31
P 7200 5250
F 0 "D52" V 7246 5171 50  0000 R CNN
F 1 "1N4148" V 7155 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7200 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 7200 5250 50  0001 C CNN
F 4 "YES" H 7200 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 7200 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 7200 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 7200 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 7200 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 7200 5250 50  0001 C CNN "Package"
F 10 "C118751" H 7200 5250 50  0001 C CNN "LCSC"
	1    7200 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D56
U 1 1 5BC6CF38
P 8000 5250
F 0 "D56" V 8046 5171 50  0000 R CNN
F 1 "1N4148" V 7955 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8000 5250 50  0001 C CNN
F 4 "YES" H 8000 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 8000 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8000 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8000 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8000 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8000 5250 50  0001 C CNN "Package"
F 10 "C118751" H 8000 5250 50  0001 C CNN "LCSC"
	1    8000 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D60
U 1 1 5BC6CF3F
P 8800 5250
F 0 "D60" V 8846 5171 50  0000 R CNN
F 1 "1N4148" V 8755 5171 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8800 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8800 5250 50  0001 C CNN
F 4 "YES" H 8800 5250 50  0001 C CNN "Fitted"
F 5 " YES " H 8800 5250 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8800 5250 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8800 5250 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8800 5250 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8800 5250 50  0001 C CNN "Package"
F 10 "C118751" H 8800 5250 50  0001 C CNN "LCSC"
	1    8800 5250
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW38
U 1 1 5BC6D0AD
P 3800 5900
F 0 "SW38" H 3800 6185 50  0000 C CNN
F 1 "K" H 3800 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 6100 50  0001 C CNN
F 3 "" H 3800 6100 50  0001 C CNN
F 4 "Common to all layouts" H 3800 5900 50  0001 C CNN "Comment"
F 5 "YES" H 3800 5900 50  0001 C CNN "Fitted"
F 6 "NO" H 3800 5900 50  0001 C CNN "Substitution OK"
	1    3800 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW45
U 1 1 5BC6D0B4
P 5400 5900
F 0 "SW45" H 5400 6185 50  0000 C CNN
F 1 "H" H 5400 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 5400 6100 50  0001 C CNN
F 3 "" H 5400 6100 50  0001 C CNN
F 4 "Common to all layouts" H 5400 5900 50  0001 C CNN "Comment"
F 5 "YES" H 5400 5900 50  0001 C CNN "Fitted"
F 6 "NO" H 5400 5900 50  0001 C CNN "Substitution OK"
	1    5400 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW42
U 1 1 5BC6D0BB
P 4600 5900
F 0 "SW42" H 4600 6185 50  0000 C CNN
F 1 "J" H 4600 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 6100 50  0001 C CNN
F 3 "" H 4600 6100 50  0001 C CNN
F 4 "Common to all layouts" H 4600 5900 50  0001 C CNN "Comment"
F 5 "YES" H 4600 5900 50  0001 C CNN "Fitted"
F 6 "NO" H 4600 5900 50  0001 C CNN "Substitution OK"
	1    4600 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW48
U 1 1 5BC6D0C2
P 6200 5900
F 0 "SW48" H 6200 6185 50  0000 C CNN
F 1 "G" H 6200 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 6200 6100 50  0001 C CNN
F 3 "" H 6200 6100 50  0001 C CNN
F 4 "Common to all layouts" H 6200 5900 50  0001 C CNN "Comment"
F 5 "YES" H 6200 5900 50  0001 C CNN "Fitted"
F 6 "NO" H 6200 5900 50  0001 C CNN "Substitution OK"
	1    6200 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW52
U 1 1 5BC6D0C9
P 7000 5900
F 0 "SW52" H 7000 6185 50  0000 C CNN
F 1 "F" H 7000 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7000 6100 50  0001 C CNN
F 3 "" H 7000 6100 50  0001 C CNN
F 4 "Common to all layouts" H 7000 5900 50  0001 C CNN "Comment"
F 5 "YES" H 7000 5900 50  0001 C CNN "Fitted"
F 6 "NO" H 7000 5900 50  0001 C CNN "Substitution OK"
	1    7000 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW60
U 1 1 5BC6D0D0
P 8600 5900
F 0 "SW60" H 8600 6185 50  0000 C CNN
F 1 "S" H 8600 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 8600 6100 50  0001 C CNN
F 3 "" H 8600 6100 50  0001 C CNN
F 4 "Common to all layouts" H 8600 5900 50  0001 C CNN "Comment"
F 5 "YES" H 8600 5900 50  0001 C CNN "Fitted"
F 6 "NO" H 8600 5900 50  0001 C CNN "Substitution OK"
	1    8600 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW56
U 1 1 5BC6D0D7
P 7800 5900
F 0 "SW56" H 7800 6185 50  0000 C CNN
F 1 "D" H 7800 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7800 6100 50  0001 C CNN
F 3 "" H 7800 6100 50  0001 C CNN
F 4 "Common to all layouts" H 7800 5900 50  0001 C CNN "Comment"
F 5 "YES" H 7800 5900 50  0001 C CNN "Fitted"
F 6 "NO" H 7800 5900 50  0001 C CNN "Substitution OK"
	1    7800 5900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D39
U 1 1 5BC6D0DE
P 4000 6150
F 0 "D39" V 4046 6071 50  0000 R CNN
F 1 "1N4148" V 3955 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4000 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 6150 50  0001 C CNN
F 4 "YES" H 4000 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 4000 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4000 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4000 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4000 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4000 6150 50  0001 C CNN "Package"
F 10 "C118751" H 4000 6150 50  0001 C CNN "LCSC"
	1    4000 6150
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D43
U 1 1 5BC6D0EC
P 4800 6150
F 0 "D43" V 4846 6071 50  0000 R CNN
F 1 "1N4148" V 4755 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4800 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 6150 50  0001 C CNN
F 4 "YES" H 4800 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 4800 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 4800 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 4800 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 4800 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 4800 6150 50  0001 C CNN "Package"
F 10 "C118751" H 4800 6150 50  0001 C CNN "LCSC"
	1    4800 6150
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D46
U 1 1 5BC6D0F3
P 5600 6150
F 0 "D46" V 5646 6071 50  0000 R CNN
F 1 "1N4148" V 5555 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 5600 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5600 6150 50  0001 C CNN
F 4 "YES" H 5600 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 5600 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 5600 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 5600 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 5600 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 5600 6150 50  0001 C CNN "Package"
F 10 "C118751" H 5600 6150 50  0001 C CNN "LCSC"
	1    5600 6150
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D49
U 1 1 5BC6D0FA
P 6400 6150
F 0 "D49" V 6446 6071 50  0000 R CNN
F 1 "1N4148" V 6355 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6400 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6400 6150 50  0001 C CNN
F 4 "YES" H 6400 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 6400 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 6400 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 6400 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 6400 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 6400 6150 50  0001 C CNN "Package"
F 10 "C118751" H 6400 6150 50  0001 C CNN "LCSC"
	1    6400 6150
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D53
U 1 1 5BC6D101
P 7200 6150
F 0 "D53" V 7246 6071 50  0000 R CNN
F 1 "1N4148" V 7155 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 7200 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 7200 6150 50  0001 C CNN
F 4 "YES" H 7200 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 7200 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 7200 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 7200 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 7200 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 7200 6150 50  0001 C CNN "Package"
F 10 "C118751" H 7200 6150 50  0001 C CNN "LCSC"
	1    7200 6150
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D57
U 1 1 5BC6D108
P 8000 6150
F 0 "D57" V 8046 6071 50  0000 R CNN
F 1 "1N4148" V 7955 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8000 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8000 6150 50  0001 C CNN
F 4 "YES" H 8000 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 8000 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8000 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8000 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8000 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8000 6150 50  0001 C CNN "Package"
F 10 "C118751" H 8000 6150 50  0001 C CNN "LCSC"
	1    8000 6150
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D61
U 1 1 5BC6D10F
P 8800 6150
F 0 "D61" V 8846 6071 50  0000 R CNN
F 1 "1N4148" V 8755 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8800 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8800 6150 50  0001 C CNN
F 4 "YES" H 8800 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 8800 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 8800 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 8800 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 8800 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 8800 6150 50  0001 C CNN "Package"
F 10 "C118751" H 8800 6150 50  0001 C CNN "LCSC"
	1    8800 6150
	0    -1   -1   0   
$EndComp
Connection ~ 4000 3600
Wire Wire Line
	4000 3600 4800 3600
Connection ~ 4800 3600
Connection ~ 7200 3600
Wire Wire Line
	7200 3600 8000 3600
Connection ~ 8000 3600
Wire Wire Line
	8000 3600 8800 3600
Connection ~ 4000 4500
Wire Wire Line
	4000 4500 4800 4500
Connection ~ 4800 4500
Wire Wire Line
	4800 4500 5600 4500
Connection ~ 5600 4500
Wire Wire Line
	5600 4500 6400 4500
Connection ~ 6400 4500
Wire Wire Line
	6400 4500 7200 4500
Connection ~ 7200 4500
Wire Wire Line
	7200 4500 8000 4500
Connection ~ 8000 4500
Wire Wire Line
	8000 4500 8800 4500
Wire Wire Line
	3200 5400 4000 5400
Connection ~ 4000 5400
Wire Wire Line
	4000 5400 4800 5400
Connection ~ 4800 5400
Wire Wire Line
	4800 5400 5600 5400
Connection ~ 5600 5400
Wire Wire Line
	5600 5400 6400 5400
Connection ~ 6400 5400
Wire Wire Line
	6400 5400 7200 5400
Connection ~ 7200 5400
Wire Wire Line
	7200 5400 8000 5400
Connection ~ 8000 5400
Wire Wire Line
	8000 5400 8800 5400
Connection ~ 4000 6300
Wire Wire Line
	4000 6300 4800 6300
Connection ~ 4800 6300
Wire Wire Line
	4800 6300 5600 6300
Connection ~ 5600 6300
Wire Wire Line
	5600 6300 6400 6300
Connection ~ 6400 6300
Wire Wire Line
	6400 6300 7200 6300
Connection ~ 7200 6300
Wire Wire Line
	7200 6300 8000 6300
Connection ~ 8000 6300
Wire Wire Line
	8000 6300 8800 6300
Wire Wire Line
	4000 5900 4000 6000
Wire Wire Line
	4800 5900 4800 6000
Wire Wire Line
	5600 5900 5600 6000
Wire Wire Line
	6400 5900 6400 6000
Wire Wire Line
	7200 5900 7200 6000
Wire Wire Line
	8000 5900 8000 6000
Wire Wire Line
	8800 6000 8800 5900
Wire Wire Line
	8800 5000 8800 5100
Wire Wire Line
	8000 5000 8000 5100
Wire Wire Line
	7200 5000 7200 5100
Wire Wire Line
	5600 5100 5600 5000
Wire Wire Line
	6400 5100 6400 5000
Wire Wire Line
	4800 5100 4800 5000
Wire Wire Line
	4000 5100 4000 5000
Wire Wire Line
	3200 5100 3200 5000
Wire Wire Line
	4000 3200 4000 3300
Wire Wire Line
	4000 4100 4000 4200
Wire Wire Line
	4800 4100 4800 4200
Wire Wire Line
	5600 4200 5600 4100
Wire Wire Line
	6400 4200 6400 4100
Wire Wire Line
	7200 4200 7200 4100
Wire Wire Line
	8000 4200 8000 4100
Wire Wire Line
	8800 4200 8800 4100
Wire Wire Line
	4800 3300 4800 3200
Wire Wire Line
	7200 3200 7200 3300
Wire Wire Line
	8000 3200 8000 3300
Wire Wire Line
	8800 3200 8800 3300
Wire Wire Line
	1450 2500 2800 2500
Wire Wire Line
	1450 2300 3600 2300
Wire Wire Line
	3600 2300 3600 3200
Connection ~ 3600 3200
Wire Wire Line
	3600 3200 3600 4100
Connection ~ 3600 4100
Wire Wire Line
	3600 4100 3600 5000
Connection ~ 3600 5000
Wire Wire Line
	3600 5000 3600 5900
Wire Wire Line
	1450 2100 4400 2100
Wire Wire Line
	4400 2100 4400 3200
Connection ~ 4400 3200
Wire Wire Line
	4400 3200 4400 4100
Connection ~ 4400 4100
Wire Wire Line
	4400 4100 4400 5000
Connection ~ 4400 5000
Wire Wire Line
	4400 5000 4400 5900
Wire Wire Line
	1450 1900 5200 1900
Connection ~ 5200 4100
Wire Wire Line
	5200 4100 5200 5000
Connection ~ 5200 5000
Wire Wire Line
	5200 5000 5200 5900
Wire Wire Line
	1450 1700 6000 1700
Connection ~ 6000 4100
Wire Wire Line
	6000 4100 6000 5000
Connection ~ 6000 5000
Wire Wire Line
	6000 5000 6000 5900
Wire Wire Line
	1450 1500 6800 1500
Wire Wire Line
	6800 1500 6800 3200
Connection ~ 6800 3200
Wire Wire Line
	6800 3200 6800 4100
Connection ~ 6800 4100
Wire Wire Line
	6800 4100 6800 5000
Connection ~ 6800 5000
Wire Wire Line
	6800 5000 6800 5900
Wire Wire Line
	1450 1300 7600 1300
Wire Wire Line
	7600 1300 7600 3200
Connection ~ 7600 3200
Wire Wire Line
	7600 3200 7600 4100
Connection ~ 7600 4100
Wire Wire Line
	7600 4100 7600 5000
Connection ~ 7600 5000
Wire Wire Line
	7600 5000 7600 5900
Wire Wire Line
	1450 1100 8400 1100
Wire Wire Line
	8400 1100 8400 3200
Connection ~ 8400 3200
Wire Wire Line
	8400 3200 8400 4100
Connection ~ 8400 4100
Wire Wire Line
	8400 4100 8400 5000
Connection ~ 8400 5000
Wire Wire Line
	8400 5000 8400 5900
Connection ~ 3200 5400
Text Notes 1100 7100 0    50   ~ 0
(Install either Row diodes or switch diodes.  Jumper uninstalled diodes.
Text Label 2300 3600 0    50   ~ 0
Row0_keys
Text Label 2300 4500 0    50   ~ 0
Row1_keys
Text Label 2300 5400 0    50   ~ 0
Row2_keys
Wire Wire Line
	5200 1900 5200 4100
Wire Wire Line
	6000 1700 6000 3200
Wire Wire Line
	4800 3600 6400 3600
Text Label 2300 6300 0    50   ~ 0
Row3_keys
Wire Wire Line
	1450 4500 4000 4500
Wire Wire Line
	1450 5400 3200 5400
Wire Wire Line
	2800 2500 2800 5000
Wire Wire Line
	1450 3600 4000 3600
Wire Wire Line
	1450 6300 3200 6300
Text Notes 2960 4200 0    50   ~ 0
Rubout
$Comp
L Switch:SW_Push SW62
U 1 1 5E0AC938
P 6200 3200
F 0 "SW62" H 6200 3485 50  0000 C CNN
F 1 "ESC" H 6200 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 6200 3400 50  0001 C CNN
F 3 "" H 6200 3400 50  0001 C CNN
F 4 "NO" H 6200 3200 50  0001 C CNN "Fitted"
F 5 "NO" H 6200 3200 50  0001 C CNN "Substitution OK"
	1    6200 3200
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D1
U 1 1 5E0AC93E
P 6400 3450
F 0 "D1" V 6446 3371 50  0000 R CNN
F 1 "1N4148" V 6355 3371 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6400 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6400 3450 50  0001 C CNN
F 4 "YES" H 6400 3450 50  0001 C CNN "Fitted"
F 5 " YES " H 6400 3450 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 6400 3450 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 6400 3450 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 6400 3450 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 6400 3450 50  0001 C CNN "Package"
F 10 "C118751" H 6400 3450 50  0001 C CNN "LCSC"
	1    6400 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6400 3200 6400 3300
Connection ~ 6000 3200
Wire Wire Line
	6000 3200 6000 4100
Connection ~ 6400 3600
Wire Wire Line
	6400 3600 7200 3600
$Comp
L Switch:SW_Push SW63
U 1 1 5E423211
P 3000 5900
F 0 "SW63" H 3000 6185 50  0000 C CNN
F 1 "Spare" H 3000 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3000 6100 50  0001 C CNN
F 3 "" H 3000 6100 50  0001 C CNN
F 4 "NO" H 3000 5900 50  0001 C CNN "Fitted"
F 5 "NO" H 3000 5900 50  0001 C CNN "Substitution OK"
	1    3000 5900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D35
U 1 1 5E423217
P 3200 6150
F 0 "D35" V 3246 6071 50  0000 R CNN
F 1 "1N4148" V 3155 6071 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3200 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 3200 6150 50  0001 C CNN
F 4 "YES" H 3200 6150 50  0001 C CNN "Fitted"
F 5 " YES " H 3200 6150 50  0001 C CNN "Substitution OK"
F 6 "<1.25V forward voltage.  " H 3200 6150 50  0001 C CNN "Comment"
F 7 "ON Semiconductor" H 3200 6150 50  0001 C CNN "Manufacturer"
F 8 "MMBD914LT3G " H 3200 6150 50  0001 C CNN "Manufacturer Part Number"
F 9 " SOT-23-3 " H 3200 6150 50  0001 C CNN "Package"
F 10 "C118751" H 3200 6150 50  0001 C CNN "LCSC"
	1    3200 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 5900 3200 6000
Wire Wire Line
	2800 5000 2800 5900
Connection ~ 2800 5000
Connection ~ 3200 6300
Wire Wire Line
	3200 6300 4000 6300
$EndSCHEMATC
