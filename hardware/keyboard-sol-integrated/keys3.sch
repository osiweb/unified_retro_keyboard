EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title "Sol-20 keyboard"
Date "2020-12-30"
Rev "2.0"
Comp "OSIWeb.org"
Comment1 "Key Matrix part 2"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1450 4500 0    60   Input ~ 0
Row10
Text HLabel 1450 5400 0    60   Input ~ 0
Row11
Text HLabel 1450 6300 0    60   Input ~ 0
Row12
Text HLabel 1450 3600 0    60   Input ~ 0
Row9
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
L Switch:SW_Push SW?
U 1 1 5E1BE0F5
P 3800 3200
AR Path="/5BC3E99D/5E1BE0F5" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE0F5" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0F5" Ref="SW70"  Part="1" 
F 0 "SW70" H 3800 3485 50  0000 C CNN
F 1 "Up Arrow" H 3800 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 3400 50  0001 C CNN
F 3 "" H 3800 3400 50  0001 C CNN
	1    3800 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE0F6
P 4600 3200
AR Path="/5BC3E99D/5E1BE0F6" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE0F6" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0F6" Ref="SW74"  Part="1" 
F 0 "SW74" H 4600 3485 50  0000 C CNN
F 1 "LT Arrow" H 4600 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 3400 50  0001 C CNN
F 3 "" H 4600 3400 50  0001 C CNN
	1    4600 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE0F7
P 7000 3200
AR Path="/5BC3E99D/5E1BE0F7" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE0F7" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0F7" Ref="SW84"  Part="1" 
F 0 "SW84" H 7000 3485 50  0000 C CNN
F 1 "Down Arrow" H 7035 3405 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7000 3400 50  0001 C CNN
F 3 "" H 7000 3400 50  0001 C CNN
	1    7000 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE0F8
P 8600 3200
AR Path="/5BC3E99D/5E1BE0F8" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE0F8" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0F8" Ref="SW88"  Part="1" 
F 0 "SW88" H 8600 3485 50  0000 C CNN
F 1 "Clear" H 8600 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 8600 3400 50  0001 C CNN
F 3 "" H 8600 3400 50  0001 C CNN
	1    8600 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE0F9
P 7800 3200
AR Path="/5BC3E99D/5E1BE0F9" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE0F9" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0F9" Ref="SW87"  Part="1" 
F 0 "SW87" H 7800 3485 50  0000 C CNN
F 1 "Home" H 7800 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7800 3400 50  0001 C CNN
F 3 "" H 7800 3400 50  0001 C CNN
	1    7800 3200
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE0FA
P 4000 3450
AR Path="/5BC3E99D/5E1BE0FA" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE0FA" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0FA" Ref="D67"  Part="1" 
F 0 "D67" V 4046 3371 50  0000 R CNN
F 1 "1N4148" V 3955 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4000 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 3450 50  0001 C CNN
	1    4000 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE0FB
P 4800 3450
AR Path="/5BC3E99D/5E1BE0FB" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE0FB" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0FB" Ref="D71"  Part="1" 
F 0 "D71" V 4846 3371 50  0000 R CNN
F 1 "1N4148" V 4755 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4800 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 3450 50  0001 C CNN
	1    4800 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE0FC
P 7200 3450
AR Path="/5BC3E99D/5E1BE0FC" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE0FC" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0FC" Ref="D81"  Part="1" 
F 0 "D81" V 7246 3371 50  0000 R CNN
F 1 "1N4148" V 7155 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 7200 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 7200 3450 50  0001 C CNN
	1    7200 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE0FD
P 8000 3450
AR Path="/5BC3E99D/5E1BE0FD" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE0FD" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0FD" Ref="D84"  Part="1" 
F 0 "D84" V 8046 3371 50  0000 R CNN
F 1 "1N4148" V 7955 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 8000 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8000 3450 50  0001 C CNN
	1    8000 3450
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE0FE
P 8800 3450
AR Path="/5BC3E99D/5E1BE0FE" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE0FE" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0FE" Ref="D85"  Part="1" 
F 0 "D85" V 8846 3371 50  0000 R CNN
F 1 "1N4148" V 8755 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 8800 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 8800 3450 50  0001 C CNN
	1    8800 3450
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE0FF
P 3800 4100
AR Path="/5BC3E99D/5E1BE0FF" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE0FF" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE0FF" Ref="SW71"  Part="1" 
F 0 "SW71" H 3800 4385 50  0000 C CNN
F 1 "NP 7" H 3840 4300 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 4300 50  0001 C CNN
F 3 "" H 3800 4300 50  0001 C CNN
	1    3800 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE100
P 5400 4100
AR Path="/5BC3E99D/5E1BE100" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE100" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE100" Ref="SW79"  Part="1" 
F 0 "SW79" H 5400 4385 50  0000 C CNN
F 1 "NP 8" H 5400 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 5400 4300 50  0001 C CNN
F 3 "" H 5400 4300 50  0001 C CNN
	1    5400 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE101
P 4600 4100
AR Path="/5BC3E99D/5E1BE101" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE101" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE101" Ref="SW75"  Part="1" 
F 0 "SW75" H 4600 4385 50  0000 C CNN
F 1 "NP asterisk" H 4635 4300 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 4300 50  0001 C CNN
F 3 "" H 4600 4300 50  0001 C CNN
	1    4600 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE102
P 6200 4100
AR Path="/5BC3E99D/5E1BE102" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE102" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE102" Ref="SW82"  Part="1" 
F 0 "SW82" H 6200 4385 50  0000 C CNN
F 1 "NP divide" H 6200 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 6200 4300 50  0001 C CNN
F 3 "" H 6200 4300 50  0001 C CNN
	1    6200 4100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE103
P 7000 4100
AR Path="/5BC3E99D/5E1BE103" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE103" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE103" Ref="SW85"  Part="1" 
F 0 "SW85" H 7000 4385 50  0000 C CNN
F 1 "NP 9" H 7000 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7000 4300 50  0001 C CNN
F 3 "" H 7000 4300 50  0001 C CNN
	1    7000 4100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BC6CD8E
P 4000 4350
AR Path="/5BC3E99D/5BC6CD8E" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5BC6CD8E" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5BC6CD8E" Ref="D68"  Part="1" 
F 0 "D68" V 4046 4271 50  0000 R CNN
F 1 "1N4148" V 3955 4271 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4000 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 4350 50  0001 C CNN
	1    4000 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BC6CD9C
P 4800 4350
AR Path="/5BC3E99D/5BC6CD9C" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5BC6CD9C" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5BC6CD9C" Ref="D72"  Part="1" 
F 0 "D72" V 4846 4271 50  0000 R CNN
F 1 "1N4148" V 4755 4271 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4800 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 4350 50  0001 C CNN
	1    4800 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BC6CDA3
P 5600 4350
AR Path="/5BC3E99D/5BC6CDA3" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5BC6CDA3" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5BC6CDA3" Ref="D76"  Part="1" 
F 0 "D76" V 5646 4271 50  0000 R CNN
F 1 "1N4148" V 5555 4271 50  0000 R CNN
F 2 "unikbd:diode-combined" H 5600 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5600 4350 50  0001 C CNN
	1    5600 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE107
P 6400 4350
AR Path="/5BC3E99D/5E1BE107" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE107" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE107" Ref="D79"  Part="1" 
F 0 "D79" V 6446 4271 50  0000 R CNN
F 1 "1N4148" V 6355 4271 50  0000 R CNN
F 2 "unikbd:diode-combined" H 6400 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6400 4350 50  0001 C CNN
	1    6400 4350
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE108
P 7200 4350
AR Path="/5BC3E99D/5E1BE108" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE108" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE108" Ref="D82"  Part="1" 
F 0 "D82" V 7246 4271 50  0000 R CNN
F 1 "1N4148" V 7155 4271 50  0000 R CNN
F 2 "unikbd:diode-combined" H 7200 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 7200 4350 50  0001 C CNN
	1    7200 4350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE109
P 3000 5000
AR Path="/5BC3E99D/5E1BE109" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE109" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE109" Ref="SW68"  Part="1" 
F 0 "SW68" H 3000 5285 50  0000 C CNN
F 1 "NP 4" H 3030 5195 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3000 5200 50  0001 C CNN
F 3 "" H 3000 5200 50  0001 C CNN
	1    3000 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE10A
P 3800 5000
AR Path="/5BC3E99D/5E1BE10A" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE10A" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE10A" Ref="SW72"  Part="1" 
F 0 "SW72" H 3800 5285 50  0000 C CNN
F 1 "NP 1" H 3800 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 5200 50  0001 C CNN
F 3 "" H 3800 5200 50  0001 C CNN
	1    3800 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE10B
P 5400 5000
AR Path="/5BC3E99D/5E1BE10B" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE10B" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE10B" Ref="SW80"  Part="1" 
F 0 "SW80" H 5400 5285 50  0000 C CNN
F 1 "NP 2" H 5400 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 5400 5200 50  0001 C CNN
F 3 "" H 5400 5200 50  0001 C CNN
	1    5400 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE10C
P 4600 5000
AR Path="/5BC3E99D/5E1BE10C" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE10C" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE10C" Ref="SW76"  Part="1" 
F 0 "SW76" H 4600 5285 50  0000 C CNN
F 1 "NP 5" H 4600 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 5200 50  0001 C CNN
F 3 "" H 4600 5200 50  0001 C CNN
	1    4600 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE10D
P 6200 5000
AR Path="/5BC3E99D/5E1BE10D" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE10D" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE10D" Ref="SW83"  Part="1" 
F 0 "SW83" H 6200 5285 50  0000 C CNN
F 1 "NP 6" H 6200 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 6200 5200 50  0001 C CNN
F 3 "" H 6200 5200 50  0001 C CNN
	1    6200 5000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE10E
P 7000 5000
AR Path="/5BC3E99D/5E1BE10E" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE10E" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE10E" Ref="SW86"  Part="1" 
F 0 "SW86" H 7000 5285 50  0000 C CNN
F 1 "NP 3" H 7000 5194 50  0000 C CNN
F 2 "unikbd:Key_MX" H 7000 5200 50  0001 C CNN
F 3 "" H 7000 5200 50  0001 C CNN
	1    7000 5000
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE10F
P 4000 5250
AR Path="/5BC3E99D/5E1BE10F" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE10F" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE10F" Ref="D69"  Part="1" 
F 0 "D69" V 4046 5171 50  0000 R CNN
F 1 "1N4148" V 3955 5171 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4000 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 5250 50  0001 C CNN
	1    4000 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE110
P 3200 5250
AR Path="/5BC3E99D/5E1BE110" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE110" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE110" Ref="D65"  Part="1" 
F 0 "D65" V 3246 5171 50  0000 R CNN
F 1 "1N4148" V 3155 5171 50  0000 R CNN
F 2 "unikbd:diode-combined" H 3200 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 3200 5250 50  0001 C CNN
	1    3200 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE111
P 4800 5250
AR Path="/5BC3E99D/5E1BE111" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE111" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE111" Ref="D73"  Part="1" 
F 0 "D73" V 4846 5171 50  0000 R CNN
F 1 "1N4148" V 4755 5171 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4800 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 5250 50  0001 C CNN
	1    4800 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE112
P 5600 5250
AR Path="/5BC3E99D/5E1BE112" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE112" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE112" Ref="D77"  Part="1" 
F 0 "D77" V 5646 5171 50  0000 R CNN
F 1 "1N4148" V 5555 5171 50  0000 R CNN
F 2 "unikbd:diode-combined" H 5600 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5600 5250 50  0001 C CNN
	1    5600 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE113
P 6400 5250
AR Path="/5BC3E99D/5E1BE113" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE113" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE113" Ref="D80"  Part="1" 
F 0 "D80" V 6446 5171 50  0000 R CNN
F 1 "1N4148" V 6355 5171 50  0000 R CNN
F 2 "unikbd:diode-combined" H 6400 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6400 5250 50  0001 C CNN
	1    6400 5250
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BC6CF31
P 7200 5250
AR Path="/5BC3E99D/5BC6CF31" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5BC6CF31" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5BC6CF31" Ref="D83"  Part="1" 
F 0 "D83" V 7246 5171 50  0000 R CNN
F 1 "1N4148" V 7155 5171 50  0000 R CNN
F 2 "unikbd:diode-combined" H 7200 5075 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 7200 5250 50  0001 C CNN
	1    7200 5250
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5BC6D0AD
P 3800 5900
AR Path="/5BC3E99D/5BC6D0AD" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5BC6D0AD" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5BC6D0AD" Ref="SW73"  Part="1" 
F 0 "SW73" H 3800 6185 50  0000 C CNN
F 1 "NP period" H 3800 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3800 6100 50  0001 C CNN
F 3 "" H 3800 6100 50  0001 C CNN
	1    3800 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE116
P 4600 5900
AR Path="/5BC3E99D/5E1BE116" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE116" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE116" Ref="SW77"  Part="1" 
F 0 "SW77" H 4600 6185 50  0000 C CNN
F 1 "NP plus" H 4600 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 4600 6100 50  0001 C CNN
F 3 "" H 4600 6100 50  0001 C CNN
	1    4600 5900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE117
P 4000 6150
AR Path="/5BC3E99D/5E1BE117" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE117" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE117" Ref="D70"  Part="1" 
F 0 "D70" V 4046 6071 50  0000 R CNN
F 1 "1N4148" V 3955 6071 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4000 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 6150 50  0001 C CNN
	1    4000 6150
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5BC6D0EC
P 4800 6150
AR Path="/5BC3E99D/5BC6D0EC" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5BC6D0EC" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5BC6D0EC" Ref="D74"  Part="1" 
F 0 "D74" V 4846 6071 50  0000 R CNN
F 1 "1N4148" V 4755 6071 50  0000 R CNN
F 2 "unikbd:diode-combined" H 4800 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4800 6150 50  0001 C CNN
	1    4800 6150
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
Connection ~ 4000 6300
Wire Wire Line
	4000 6300 4800 6300
Wire Wire Line
	4000 5900 4000 6000
Wire Wire Line
	4800 5900 4800 6000
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
Wire Wire Line
	1450 1700 6000 1700
Connection ~ 6000 4100
Wire Wire Line
	6000 4100 6000 5000
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
Wire Wire Line
	1450 1300 7600 1300
Wire Wire Line
	1450 1100 8400 1100
Wire Wire Line
	8400 1100 8400 3200
Connection ~ 3200 5400
Text Notes 1100 7100 0    50   ~ 0
(Install either Row diodes or switch diodes.  Jumper uninstalled diodes.
Text Label 2300 3600 0    50   ~ 0
Row9_keys
Text Label 2300 4500 0    50   ~ 0
Row10_keys
Text Label 2300 5400 0    50   ~ 0
Row11_keys
Wire Wire Line
	6000 1700 6000 3200
Wire Wire Line
	4800 3600 5600 3600
Text Label 2300 6300 0    50   ~ 0
Row12_keys
Wire Wire Line
	1450 4500 3200 4500
Wire Wire Line
	1450 5400 3200 5400
Wire Wire Line
	2800 2500 2800 3200
Wire Wire Line
	1450 3600 3200 3600
Wire Wire Line
	1450 6300 3200 6300
$Comp
L Switch:SW_Push SW?
U 1 1 5E1BE119
P 6200 3200
AR Path="/5BC3E99D/5E1BE119" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E1BE119" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E1BE119" Ref="SW81"  Part="1" 
F 0 "SW81" H 6200 3485 50  0000 C CNN
F 1 "RT Arrow" H 6200 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 6200 3400 50  0001 C CNN
F 3 "" H 6200 3400 50  0001 C CNN
	1    6200 3200
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E1BE11A
P 6400 3450
AR Path="/5BC3E99D/5E1BE11A" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E1BE11A" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E1BE11A" Ref="D78"  Part="1" 
F 0 "D78" V 6446 3371 50  0000 R CNN
F 1 "1N4148" V 6355 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 6400 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6400 3450 50  0001 C CNN
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
L Switch:SW_Push SW?
U 1 1 5E12EFC1
P 3000 3200
AR Path="/5BC3E99D/5E12EFC1" Ref="SW?"  Part="1" 
AR Path="/5BC3EA0A/5E12EFC1" Ref="SW?"  Part="1" 
AR Path="/5E12EFC1" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E12EFC1" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E12EFC1" Ref="SW66"  Part="1" 
F 0 "SW66" H 3000 3485 50  0000 C CNN
F 1 "Local" H 3000 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3000 3400 50  0001 C CNN
F 3 "" H 3000 3400 50  0001 C CNN
	1    3000 3200
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E12EFC7
P 3200 3450
AR Path="/5BC3E99D/5E12EFC7" Ref="D?"  Part="1" 
AR Path="/5BC3EA0A/5E12EFC7" Ref="D?"  Part="1" 
AR Path="/5E12EFC7" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E12EFC7" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E12EFC7" Ref="D63"  Part="1" 
F 0 "D63" V 3246 3371 50  0000 R CNN
F 1 "1N4148" V 3155 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 3200 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 3200 3450 50  0001 C CNN
	1    3200 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 3200 3200 3300
Connection ~ 2800 3200
Wire Wire Line
	2800 3200 2800 4100
Connection ~ 3200 3600
Wire Wire Line
	3200 3600 4000 3600
$Comp
L Switch:SW_Push SW?
U 1 1 5E135ADC
P 5400 3200
AR Path="/5BC3E99D/5E135ADC" Ref="SW?"  Part="1" 
AR Path="/5BC3EA0A/5E135ADC" Ref="SW?"  Part="1" 
AR Path="/5E135ADC" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E135ADC" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E135ADC" Ref="SW78"  Part="1" 
F 0 "SW78" H 5400 3485 50  0000 C CNN
F 1 "Spacebar" H 5400 3394 50  0000 C CNN
F 2 "unikbd:Key_MX" H 5400 3400 50  0001 C CNN
F 3 "" H 5400 3400 50  0001 C CNN
	1    5400 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3200 5600 3300
Connection ~ 5600 3600
Wire Wire Line
	5600 3600 6400 3600
Connection ~ 5200 3200
Wire Wire Line
	5200 3200 5200 4100
$Comp
L Switch:SW_Push SW?
U 1 1 5E13E76B
P 3000 4100
AR Path="/5BC3E99D/5E13E76B" Ref="SW?"  Part="1" 
AR Path="/5BC3EA0A/5E13E76B" Ref="SW?"  Part="1" 
AR Path="/5E13E76B" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E13E76B" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E13E76B" Ref="SW67"  Part="1" 
F 0 "SW67" H 3000 4385 50  0000 C CNN
F 1 "NP Dash" H 3000 4294 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3000 4300 50  0001 C CNN
F 3 "" H 3000 4300 50  0001 C CNN
	1    3000 4100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E13E771
P 3200 4350
AR Path="/5BC3E99D/5E13E771" Ref="D?"  Part="1" 
AR Path="/5BC3EA0A/5E13E771" Ref="D?"  Part="1" 
AR Path="/5E13E771" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E13E771" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E13E771" Ref="D64"  Part="1" 
F 0 "D64" V 3246 4271 50  0000 R CNN
F 1 "1N4148" V 3155 4271 50  0000 R CNN
F 2 "unikbd:diode-combined" H 3200 4175 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 3200 4350 50  0001 C CNN
	1    3200 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 4100 3200 4200
Connection ~ 2800 4100
Wire Wire Line
	2800 4100 2800 5000
Connection ~ 3200 4500
Wire Wire Line
	3200 4500 4000 4500
$Comp
L Switch:SW_Push SW?
U 1 1 5E149AE2
P 3000 5900
AR Path="/5BC3E99D/5E149AE2" Ref="SW?"  Part="1" 
AR Path="/5BC3EA0A/5E149AE2" Ref="SW?"  Part="1" 
AR Path="/5E149AE2" Ref="SW?"  Part="1" 
AR Path="/5E163BE9/5E149AE2" Ref="SW?"  Part="1" 
AR Path="/5E16AC8E/5E149AE2" Ref="SW69"  Part="1" 
F 0 "SW69" H 3000 6185 50  0000 C CNN
F 1 "NP Zero" H 3000 6094 50  0000 C CNN
F 2 "unikbd:Key_MX" H 3000 6100 50  0001 C CNN
F 3 "" H 3000 6100 50  0001 C CNN
	1    3000 5900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D?
U 1 1 5E149AE8
P 3200 6150
AR Path="/5BC3E99D/5E149AE8" Ref="D?"  Part="1" 
AR Path="/5BC3EA0A/5E149AE8" Ref="D?"  Part="1" 
AR Path="/5E149AE8" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E149AE8" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E149AE8" Ref="D66"  Part="1" 
F 0 "D66" V 3246 6071 50  0000 R CNN
F 1 "1N4148" V 3155 6071 50  0000 R CNN
F 2 "unikbd:diode-combined" H 3200 5975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 3200 6150 50  0001 C CNN
	1    3200 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 5900 3200 6000
Connection ~ 3200 6300
Wire Wire Line
	3200 6300 4000 6300
Wire Wire Line
	2800 5000 2800 5900
Connection ~ 2800 5000
Wire Wire Line
	7600 3200 7600 1300
$Comp
L Diode:1N4148 D?
U 1 1 5E135AE2
P 5600 3450
AR Path="/5BC3E99D/5E135AE2" Ref="D?"  Part="1" 
AR Path="/5BC3EA0A/5E135AE2" Ref="D?"  Part="1" 
AR Path="/5E135AE2" Ref="D?"  Part="1" 
AR Path="/5E163BE9/5E135AE2" Ref="D?"  Part="1" 
AR Path="/5E16AC8E/5E135AE2" Ref="D75"  Part="1" 
F 0 "D75" V 5646 3371 50  0000 R CNN
F 1 "1N4148" V 5555 3371 50  0000 R CNN
F 2 "unikbd:diode-combined" H 5600 3275 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5600 3450 50  0001 C CNN
	1    5600 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5200 1900 5200 3200
Wire Wire Line
	4400 2100 4400 3200
$EndSCHEMATC
