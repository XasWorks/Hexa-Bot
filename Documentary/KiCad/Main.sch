EESchema Schematic File Version 2
LIBS:Main-cache
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ZEPHYR Main control board"
Date "2016-02-20"
Rev "v0.1"
Comp "Xasin"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328-P MCU1
U 1 1 56C4C1EE
P 1725 3550
F 0 "MCU1" H 975 4800 50  0000 L BNN
F 1 "ATMEGA328-P" H 2125 2150 50  0000 L BNN
F 2 "Housings_DIP:DIP-28_W7.62mm" H 1725 3550 50  0001 C CIN
F 3 "" H 1725 3550 50  0000 C CNN
	1    1725 3550
	1    0    0    -1  
$EndComp
$Comp
L Crystal QRZ1
U 1 1 56C4C3FD
P 3425 3100
F 0 "QRZ1" H 3425 3250 50  0000 C CNN
F 1 "Crystal" H 3425 2950 50  0000 C CNN
F 2 "Crystals:Crystal_HC49-U_Vertical" H 3425 3100 50  0001 C CNN
F 3 "" H 3425 3100 50  0000 C CNN
	1    3425 3100
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C1
U 1 1 56C4C766
P 3775 2950
F 0 "C1" H 3785 3020 50  0000 L CNN
F 1 "C_Small" H 3785 2870 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 3775 2950 50  0001 C CNN
F 3 "" H 3775 2950 50  0000 C CNN
	1    3775 2950
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C0
U 1 1 56C4C801
P 3775 3250
F 0 "C0" H 3785 3320 50  0000 L CNN
F 1 "C_Small" H 3785 3170 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 3775 3250 50  0001 C CNN
F 3 "" H 3775 3250 50  0000 C CNN
	1    3775 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	3125 3250 3675 3250
Wire Wire Line
	3125 2950 3675 2950
$Comp
L GND #PWR01
U 1 1 56C4C925
P 4025 3350
F 0 "#PWR01" H 4025 3100 50  0001 C CNN
F 1 "GND" H 4025 3200 50  0000 C CNN
F 2 "" H 4025 3350 50  0000 C CNN
F 3 "" H 4025 3350 50  0000 C CNN
	1    4025 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3875 2950 4025 2950
Wire Wire Line
	4025 2950 4025 3350
Wire Wire Line
	3875 3250 4025 3250
Wire Wire Line
	2725 3150 3125 3150
Wire Wire Line
	3125 3150 3125 3250
Connection ~ 3425 3250
Wire Wire Line
	2725 3050 3125 3050
Wire Wire Line
	3125 3050 3125 2950
Connection ~ 3425 2950
Connection ~ 4025 3250
$Comp
L +5V #PWR02
U 1 1 56C6169B
P 725 2300
F 0 "#PWR02" H 725 2150 50  0001 C CNN
F 1 "+5V" H 725 2440 50  0000 C CNN
F 2 "" H 725 2300 50  0000 C CNN
F 3 "" H 725 2300 50  0000 C CNN
	1    725  2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	825  2450 725  2450
Wire Wire Line
	725  2300 725  3050
Wire Wire Line
	725  2750 825  2750
Connection ~ 725  2450
Wire Wire Line
	725  3050 825  3050
Connection ~ 725  2750
$Comp
L GND #PWR03
U 1 1 56C6174D
P 725 5100
F 0 "#PWR03" H 725 4850 50  0001 C CNN
F 1 "GND" H 725 4950 50  0000 C CNN
F 2 "" H 725 5100 50  0000 C CNN
F 3 "" H 725 5100 50  0000 C CNN
	1    725  5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	725  4650 725  5100
Wire Wire Line
	725  4750 825  4750
Wire Wire Line
	725  4650 825  4650
Connection ~ 725  4750
$Comp
L 7805 U1
U 1 1 56C61DD4
P 1950 6800
F 0 "U1" H 2100 6604 50  0000 C CNN
F 1 "7805" H 1950 7000 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220_Neutral123_Vertical" H 1950 6800 50  0001 C CNN
F 3 "" H 1950 6800 50  0000 C CNN
	1    1950 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 7050 2550 7050
$Comp
L +12V #PWR04
U 1 1 56C62924
P 1100 6550
F 0 "#PWR04" H 1100 6400 50  0001 C CNN
F 1 "+12V" H 1100 6690 50  0000 C CNN
F 2 "" H 1100 6550 50  0000 C CNN
F 3 "" H 1100 6550 50  0000 C CNN
	1    1100 6550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 56C62CC2
P 2350 6550
F 0 "#PWR05" H 2350 6400 50  0001 C CNN
F 1 "+5V" H 2350 6690 50  0000 C CNN
F 2 "" H 2350 6550 50  0000 C CNN
F 3 "" H 2350 6550 50  0000 C CNN
	1    2350 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 6750 2350 6550
$Comp
L GND #PWR06
U 1 1 56C6321A
P 1100 7150
F 0 "#PWR06" H 1100 6900 50  0001 C CNN
F 1 "GND" H 1100 7000 50  0000 C CNN
F 2 "" H 1100 7150 50  0000 C CNN
F 3 "" H 1100 7150 50  0000 C CNN
	1    1100 7150
	1    0    0    -1  
$EndComp
$Comp
L A4988 STP2
U 1 1 56C65531
P 7475 3250
F 0 "STP2" H 7075 4300 60  0000 C CNN
F 1 "A4988" H 7525 3300 60  0000 C CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 7525 3300 60  0001 C CNN
F 3 "" H 7525 3300 60  0000 C CNN
	1    7475 3250
	1    0    0    -1  
$EndComp
$Comp
L A4988 STP3
U 1 1 56C655DA
P 9625 3250
F 0 "STP3" H 9225 4300 60  0000 C CNN
F 1 "A4988" H 9675 3300 60  0000 C CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 9675 3300 60  0001 C CNN
F 3 "" H 9675 3300 60  0000 C CNN
	1    9625 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4525 3500 4525 3600
Wire Wire Line
	8925 3500 8925 3600
$Comp
L GND #PWR07
U 1 1 56C65C1E
P 4525 3600
F 0 "#PWR07" H 4525 3350 50  0001 C CNN
F 1 "GND" H 4525 3450 50  0000 C CNN
F 2 "" H 4525 3600 50  0000 C CNN
F 3 "" H 4525 3600 50  0000 C CNN
	1    4525 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 56C65C9E
P 6775 3600
F 0 "#PWR08" H 6775 3350 50  0001 C CNN
F 1 "GND" H 6775 3450 50  0000 C CNN
F 2 "" H 6775 3600 50  0000 C CNN
F 3 "" H 6775 3600 50  0000 C CNN
	1    6775 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 56C65D27
P 8925 3600
F 0 "#PWR09" H 8925 3350 50  0001 C CNN
F 1 "GND" H 8925 3450 50  0000 C CNN
F 2 "" H 8925 3600 50  0000 C CNN
F 3 "" H 8925 3600 50  0000 C CNN
	1    8925 3600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 56C65F4E
P 4325 2300
F 0 "#PWR010" H 4325 2150 50  0001 C CNN
F 1 "+5V" H 4325 2440 50  0000 C CNN
F 2 "" H 4325 2300 50  0000 C CNN
F 3 "" H 4325 2300 50  0000 C CNN
	1    4325 2300
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR011
U 1 1 56C65F74
P 4525 2300
F 0 "#PWR011" H 4525 2150 50  0001 C CNN
F 1 "+12V" H 4525 2440 50  0000 C CNN
F 2 "" H 4525 2300 50  0000 C CNN
F 3 "" H 4525 2300 50  0000 C CNN
	1    4525 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4525 2350 4525 2300
Wire Wire Line
	4525 2500 4325 2500
Wire Wire Line
	4325 2500 4325 2300
$Comp
L +12V #PWR012
U 1 1 56C6652A
P 6775 2300
F 0 "#PWR012" H 6775 2150 50  0001 C CNN
F 1 "+12V" H 6775 2440 50  0000 C CNN
F 2 "" H 6775 2300 50  0000 C CNN
F 3 "" H 6775 2300 50  0000 C CNN
	1    6775 2300
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR013
U 1 1 56C665BC
P 8925 2300
F 0 "#PWR013" H 8925 2150 50  0001 C CNN
F 1 "+12V" H 8925 2440 50  0000 C CNN
F 2 "" H 8925 2300 50  0000 C CNN
F 3 "" H 8925 2300 50  0000 C CNN
	1    8925 2300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR014
U 1 1 56C665E2
P 8725 2300
F 0 "#PWR014" H 8725 2150 50  0001 C CNN
F 1 "+5V" H 8725 2440 50  0000 C CNN
F 2 "" H 8725 2300 50  0000 C CNN
F 3 "" H 8725 2300 50  0000 C CNN
	1    8725 2300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR015
U 1 1 56C666A1
P 6575 2300
F 0 "#PWR015" H 6575 2150 50  0001 C CNN
F 1 "+5V" H 6575 2440 50  0000 C CNN
F 2 "" H 6575 2300 50  0000 C CNN
F 3 "" H 6575 2300 50  0000 C CNN
	1    6575 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6775 2350 6775 2300
Wire Wire Line
	6775 2500 6575 2500
Wire Wire Line
	6575 2500 6575 2300
Wire Wire Line
	8925 2350 8925 2300
Wire Wire Line
	8925 2500 8725 2500
Wire Wire Line
	8725 2500 8725 2300
$Comp
L CONN_01X04 P2
U 1 1 56C6742E
P 8325 1950
F 0 "P2" H 8325 2200 50  0000 C CNN
F 1 "CONN_01X04" V 8425 1950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8325 1950 50  0001 C CNN
F 3 "" H 8325 1950 50  0000 C CNN
	1    8325 1950
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X04 P3
U 1 1 56C67619
P 10475 1950
F 0 "P3" H 10475 2200 50  0000 C CNN
F 1 "CONN_01X04" V 10575 1950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 10475 1950 50  0001 C CNN
F 3 "" H 10475 1950 50  0000 C CNN
	1    10475 1950
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X04 P1
U 1 1 56C67702
P 6075 1950
F 0 "P1" H 6075 2200 50  0000 C CNN
F 1 "CONN_01X04" V 6175 1950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 6075 1950 50  0001 C CNN
F 3 "" H 6075 1950 50  0000 C CNN
	1    6075 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5925 2350 5925 2150
Wire Wire Line
	5925 2450 6025 2450
Wire Wire Line
	6025 2450 6025 2150
Wire Wire Line
	5925 2550 6125 2550
Wire Wire Line
	6125 2550 6125 2150
Wire Wire Line
	5925 2650 6225 2650
Wire Wire Line
	6225 2650 6225 2150
Wire Wire Line
	8175 2350 8175 2150
Wire Wire Line
	8175 2450 8275 2450
Wire Wire Line
	8275 2450 8275 2150
Wire Wire Line
	8175 2550 8375 2550
Wire Wire Line
	8375 2550 8375 2150
Wire Wire Line
	8175 2650 8475 2650
Wire Wire Line
	8475 2650 8475 2150
Wire Wire Line
	10325 2350 10325 2150
Wire Wire Line
	10325 2450 10425 2450
Wire Wire Line
	10425 2450 10425 2150
Wire Wire Line
	10325 2550 10525 2550
Wire Wire Line
	10525 2550 10525 2150
Wire Wire Line
	10325 2650 10625 2650
Wire Wire Line
	10625 2650 10625 2150
Wire Wire Line
	5925 2850 5925 2950
Wire Wire Line
	8175 2850 8175 2950
Wire Wire Line
	10325 2850 10325 2950
$Comp
L A4988 STP1
U 1 1 56C6A70C
P 5225 3250
F 0 "STP1" H 4825 4300 60  0000 C CNN
F 1 "A4988" H 5275 3300 60  0000 C CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 5275 3300 60  0001 C CNN
F 3 "" H 5275 3300 60  0000 C CNN
	1    5225 3250
	1    0    0    -1  
$EndComp
Wire Bus Line
	10525 3850 2925 3850
Wire Bus Line
	10525 3250 10525 3850
Wire Bus Line
	8375 3250 8375 3850
Entry Wire Line
	6025 3500 6125 3600
Entry Wire Line
	6025 3600 6125 3700
Entry Wire Line
	8275 3500 8375 3600
Entry Wire Line
	8275 3600 8375 3700
Entry Wire Line
	10425 3500 10525 3600
Entry Wire Line
	10425 3600 10525 3700
Wire Wire Line
	10325 3500 10425 3500
Wire Wire Line
	10325 3600 10425 3600
Wire Wire Line
	8175 3600 8275 3600
Wire Wire Line
	8175 3500 8275 3500
Wire Wire Line
	5925 3600 6025 3600
Wire Wire Line
	5925 3500 6025 3500
Entry Wire Line
	2825 4050 2925 3950
Entry Wire Line
	2825 4150 2925 4050
Entry Wire Line
	2825 4250 2925 4150
Entry Wire Line
	2825 4350 2925 4250
Entry Wire Line
	2825 4450 2925 4350
Entry Wire Line
	2825 4550 2925 4450
Wire Wire Line
	2725 4550 2825 4550
Wire Wire Line
	2725 4450 2825 4450
Wire Wire Line
	2725 4350 2825 4350
Wire Wire Line
	2725 4250 2825 4250
Wire Wire Line
	2725 4150 2825 4150
Wire Wire Line
	2725 4050 2825 4050
Text Label 2725 4050 0    39   ~ 0
ST0
Text Label 2725 4150 0    39   ~ 0
DR0
Text Label 2725 4250 0    39   ~ 0
ST1
Text Label 2725 4350 0    39   ~ 0
DR1
Text Label 2725 4450 0    39   ~ 0
ST2
Text Label 2725 4550 0    39   ~ 0
DR2
Text Label 5925 3500 0    39   ~ 0
ST0
Text Label 5925 3600 0    39   ~ 0
DR0
Text Label 8175 3500 0    39   ~ 0
ST1
Text Label 8175 3600 0    39   ~ 0
DR1
Text Label 10325 3500 0    39   ~ 0
ST2
Text Label 10325 3600 0    39   ~ 0
DR2
$Comp
L SPST SW1
U 1 1 56C77A08
P 9625 4350
F 0 "SW1" H 9625 4450 50  0000 C CNN
F 1 "SPST" H 9625 4250 50  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_DIP_x1_Slide" H 9625 4350 50  0001 C CNN
F 3 "" H 9625 4350 50  0000 C CNN
	1    9625 4350
	1    0    0    -1  
$EndComp
$Comp
L SPST SW2
U 1 1 56C77CDD
P 9625 4650
F 0 "SW2" H 9625 4750 50  0000 C CNN
F 1 "SPST" H 9625 4550 50  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_DIP_x1_Slide" H 9625 4650 50  0001 C CNN
F 3 "" H 9625 4650 50  0000 C CNN
	1    9625 4650
	1    0    0    -1  
$EndComp
$Comp
L SPST SW3
U 1 1 56C77D22
P 9625 4950
F 0 "SW3" H 9625 5050 50  0000 C CNN
F 1 "SPST" H 9625 4850 50  0000 C CNN
F 2 "Buttons_Switches_ThroughHole:SW_DIP_x1_Slide" H 9625 4950 50  0001 C CNN
F 3 "" H 9625 4950 50  0000 C CNN
	1    9625 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9125 4350 9125 5000
Connection ~ 9125 4650
Connection ~ 9125 4950
$Comp
L GND #PWR016
U 1 1 56C78B2B
P 9125 5000
F 0 "#PWR016" H 9125 4750 50  0001 C CNN
F 1 "GND" H 9125 4850 50  0000 C CNN
F 2 "" H 9125 5000 50  0000 C CNN
F 3 "" H 9125 5000 50  0000 C CNN
	1    9125 5000
	1    0    0    -1  
$EndComp
Entry Wire Line
	10025 3850 10125 3950
Entry Wire Line
	10125 3850 10225 3950
Entry Wire Line
	10225 3850 10325 3950
Wire Wire Line
	10125 4350 10125 3950
Wire Wire Line
	10125 4650 10225 4650
Wire Wire Line
	10225 4650 10225 3950
Wire Wire Line
	10125 4950 10325 4950
Wire Wire Line
	10325 4950 10325 3950
Text Label 10125 4300 1    39   ~ 0
MS0
Text Label 10225 4600 1    39   ~ 0
MS1
Text Label 10325 4900 1    39   ~ 0
MS2
Entry Wire Line
	8275 3150 8375 3250
Entry Wire Line
	8275 3250 8375 3350
Entry Wire Line
	8275 3350 8375 3450
Wire Wire Line
	8175 3150 8275 3150
Wire Wire Line
	8175 3250 8275 3250
Wire Wire Line
	8175 3350 8275 3350
Text Label 8175 3150 0    39   ~ 0
MS0
Text Label 8175 3250 0    39   ~ 0
MS1
Text Label 8175 3350 0    39   ~ 0
MS2
Text Label 10325 3150 0    39   ~ 0
MS0
Text Label 10325 3250 0    39   ~ 0
MS1
Text Label 10325 3350 0    39   ~ 0
MS2
Wire Wire Line
	10325 3350 10425 3350
Wire Wire Line
	10325 3250 10425 3250
Wire Wire Line
	10325 3150 10425 3150
Entry Wire Line
	10425 3150 10525 3250
Entry Wire Line
	10425 3250 10525 3350
Entry Wire Line
	10425 3350 10525 3450
Entry Wire Line
	6025 3150 6125 3250
Entry Wire Line
	6025 3250 6125 3350
Entry Wire Line
	6025 3350 6125 3450
Wire Wire Line
	5925 3150 6025 3150
Wire Wire Line
	5925 3250 6025 3250
Wire Wire Line
	5925 3350 6025 3350
Text Label 5925 3150 0    39   ~ 0
MS0
Text Label 5925 3250 0    39   ~ 0
MS1
Text Label 5925 3350 0    39   ~ 0
MS2
$Comp
L CP C3
U 1 1 56C7C9B9
P 6725 2900
F 0 "C3" H 6750 3000 50  0000 L CNN
F 1 "CP" H 6750 2800 50  0000 L CNN
F 2 "" H 6763 2750 50  0000 C CNN
F 3 "" H 6725 2900 50  0000 C CNN
	1    6725 2900
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 56C7D082
P 4475 2900
F 0 "C2" H 4500 3000 50  0000 L CNN
F 1 "CP" H 4500 2800 50  0000 L CNN
F 2 "" H 4513 2750 50  0000 C CNN
F 3 "" H 4475 2900 50  0000 C CNN
	1    4475 2900
	1    0    0    -1  
$EndComp
$Comp
L CP C4
U 1 1 56C7D8F2
P 8875 2900
F 0 "C4" H 8900 3000 50  0000 L CNN
F 1 "CP" H 8900 2800 50  0000 L CNN
F 2 "" H 8913 2750 50  0000 C CNN
F 3 "" H 8875 2900 50  0000 C CNN
	1    8875 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4475 3050 4475 3500
Wire Wire Line
	4475 3500 4525 3500
Wire Wire Line
	4475 2750 4475 2350
Wire Wire Line
	4475 2350 4525 2350
Wire Wire Line
	6725 2750 6725 2350
Wire Wire Line
	6725 2350 6775 2350
Wire Wire Line
	6725 3050 6725 3500
Wire Wire Line
	6775 3500 6775 3600
Wire Wire Line
	6725 3500 6775 3500
Wire Wire Line
	8875 3050 8875 3500
Wire Wire Line
	8875 3500 8925 3500
Wire Wire Line
	8875 2750 8875 2350
Wire Wire Line
	8875 2350 8925 2350
NoConn ~ 6725 2500
NoConn ~ 8875 2500
NoConn ~ 4475 2500
Wire Notes Line
	9025 4150 9025 5250
Wire Notes Line
	9025 5250 10425 5250
Wire Notes Line
	10425 5250 10425 4150
Wire Notes Line
	10425 4150 9025 4150
Text Notes 9025 4100 0    59   ~ 0
Switches\n
$Comp
L CONN_01X03 P4
U 1 1 56C754D0
P 8625 4200
F 0 "P4" H 8625 4400 50  0000 C CNN
F 1 "CONN_01X03" V 8725 4200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8625 4200 50  0001 C CNN
F 3 "" H 8625 4200 50  0000 C CNN
	1    8625 4200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P5
U 1 1 56C76127
P 8625 4700
F 0 "P5" H 8625 4900 50  0000 C CNN
F 1 "CONN_01X03" V 8725 4700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8625 4700 50  0001 C CNN
F 3 "" H 8625 4700 50  0000 C CNN
	1    8625 4700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P6
U 1 1 56C761EA
P 8625 5200
F 0 "P6" H 8625 5400 50  0000 C CNN
F 1 "CONN_01X03" V 8725 5200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8625 5200 50  0001 C CNN
F 3 "" H 8625 5200 50  0000 C CNN
	1    8625 5200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P7
U 1 1 56C76251
P 8625 5700
F 0 "P7" H 8625 5900 50  0000 C CNN
F 1 "CONN_01X03" V 8725 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 8625 5700 50  0001 C CNN
F 3 "" H 8625 5700 50  0000 C CNN
	1    8625 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8425 4300 8325 4300
Wire Wire Line
	8325 4300 8325 5850
Wire Wire Line
	8325 4800 8425 4800
Wire Wire Line
	8325 5300 8425 5300
Connection ~ 8325 4800
Connection ~ 8325 5300
Wire Wire Line
	8425 4200 8275 4200
Wire Wire Line
	8275 4200 8275 5850
Wire Wire Line
	8275 4700 8425 4700
Wire Wire Line
	8275 5200 8425 5200
Connection ~ 8275 4700
Wire Wire Line
	8275 5700 8425 5700
Connection ~ 8275 5200
$Comp
L GND #PWR017
U 1 1 56C78962
P 8325 5850
F 0 "#PWR017" H 8325 5600 50  0001 C CNN
F 1 "GND" H 8325 5700 50  0000 C CNN
F 2 "" H 8325 5850 50  0000 C CNN
F 3 "" H 8325 5850 50  0000 C CNN
	1    8325 5850
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR018
U 1 1 56C789A2
P 8025 5850
F 0 "#PWR018" H 8025 5700 50  0001 C CNN
F 1 "+5V" H 8025 5990 50  0000 C CNN
F 2 "" H 8025 5850 50  0000 C CNN
F 3 "" H 8025 5850 50  0000 C CNN
	1    8025 5850
	1    0    0    -1  
$EndComp
Connection ~ 8275 5700
Entry Wire Line
	8125 4000 8225 4100
Entry Wire Line
	8125 4500 8225 4600
Entry Wire Line
	8125 5000 8225 5100
Entry Wire Line
	8125 5500 8225 5600
Wire Wire Line
	8275 5850 8025 5850
Wire Wire Line
	8425 5800 8325 5800
Connection ~ 8325 5800
Wire Wire Line
	8425 5600 8225 5600
Wire Wire Line
	8425 5100 8225 5100
Wire Wire Line
	8425 4600 8225 4600
Wire Bus Line
	8125 3850 8125 5500
Wire Wire Line
	8225 4100 8425 4100
Text Label 8225 4100 3    39   ~ 0
SN0
Text Label 8225 4600 3    39   ~ 0
SN1
Text Label 8225 5100 3    39   ~ 0
SN2
Text Label 8225 5600 3    39   ~ 0
SN3
Entry Wire Line
	2825 3300 2925 3400
Entry Wire Line
	2825 3400 2925 3500
Entry Wire Line
	2825 3500 2925 3600
Entry Wire Line
	2825 3600 2925 3700
Wire Wire Line
	2725 3300 2825 3300
Wire Wire Line
	2725 3400 2825 3400
Wire Wire Line
	2725 3500 2825 3500
Wire Wire Line
	2725 3600 2825 3600
Text Label 2725 3300 0    39   ~ 0
SN0
Text Label 2725 3400 0    39   ~ 0
SN1
Text Label 2725 3500 0    39   ~ 0
SN2
Text Label 2725 3600 0    39   ~ 0
SN3
Wire Bus Line
	6125 3250 6125 3850
Wire Notes Line
	8825 3900 7875 3900
Wire Notes Line
	7875 3900 7875 6050
Wire Notes Line
	7875 6050 8825 6050
Wire Notes Line
	8825 6050 8825 3900
Text Notes 7875 6175 0    59   ~ 0
Sensor inputs\n
$Comp
L CONN_02X03 SPI1
U 1 1 56C7B4DC
P 3225 2050
F 0 "SPI1" H 3225 2250 50  0000 C CNN
F 1 "CONN_02X03" H 3225 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_2x03" H 3225 850 50  0001 C CNN
F 3 "" H 3225 850 50  0000 C CNN
	1    3225 2050
	1    0    0    -1  
$EndComp
$Comp
L CP C5
U 1 1 56C7D957
P 2550 6900
F 0 "C5" H 2575 7000 50  0000 L CNN
F 1 "CP" H 2575 6800 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L13_P5" H 2588 6750 50  0001 C CNN
F 3 "" H 2550 6900 50  0000 C CNN
	1    2550 6900
	1    0    0    -1  
$EndComp
Connection ~ 1950 7050
Wire Wire Line
	2550 6750 2350 6750
$Comp
L +5V #PWR019
U 1 1 56C7F2A3
P 3775 1950
F 0 "#PWR019" H 3775 1800 50  0001 C CNN
F 1 "+5V" H 3775 2090 50  0000 C CNN
F 2 "" H 3775 1950 50  0000 C CNN
F 3 "" H 3775 1950 50  0000 C CNN
	1    3775 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 56C7F737
P 3775 2150
F 0 "#PWR020" H 3775 1900 50  0001 C CNN
F 1 "GND" H 3775 2000 50  0000 C CNN
F 2 "" H 3775 2150 50  0000 C CNN
F 3 "" H 3775 2150 50  0000 C CNN
	1    3775 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3475 1950 3775 1950
Wire Wire Line
	3475 2150 3775 2150
Wire Bus Line
	2775 2050 2775 2300
Wire Bus Line
	2775 2300 3475 2300
Wire Bus Line
	3075 2300 3075 3700
Wire Wire Line
	3025 3900 3075 3900
Wire Wire Line
	3025 3800 3025 3925
Entry Wire Line
	3475 2300 3575 2200
Entry Wire Line
	2775 2050 2875 1950
Entry Wire Line
	2775 2150 2875 2050
Entry Wire Line
	2775 2250 2875 2150
Wire Wire Line
	2875 1950 2975 1950
Wire Wire Line
	2875 2050 2975 2050
Wire Wire Line
	2875 2150 2975 2150
Wire Wire Line
	3475 2050 3575 2050
Wire Wire Line
	3575 2050 3575 2200
Entry Wire Line
	2975 2950 3075 2850
Entry Wire Line
	2975 2850 3075 2750
Entry Wire Line
	2975 2750 3075 2650
Wire Wire Line
	2725 2750 2975 2750
Wire Wire Line
	2725 2850 2975 2850
Wire Wire Line
	2725 2950 2975 2950
Text Label 2875 1950 0    39   ~ 0
MISO
Text Label 2875 2050 0    39   ~ 0
SCK
Text Label 2875 2150 0    39   ~ 0
RST
Text Label 3575 2050 0    39   ~ 0
MOSI
Text Label 2775 2850 0    39   ~ 0
MISO
Text Label 2775 2750 0    39   ~ 0
MOSI
Text Label 2775 2950 0    39   ~ 0
SCK
Text Label 2725 3900 0    39   ~ 0
RST
$Comp
L R_Small R1
U 1 1 56C881F4
P 3075 4000
F 0 "R1" H 3105 4020 50  0000 L CNN
F 1 "1M" H 3105 3960 50  0000 L CNN
F 2 "Resistors_ThroughHole:Resistor_Vertical_RM5mm" H 3075 4000 50  0001 C CNN
F 3 "" H 3075 4000 50  0000 C CNN
	1    3075 4000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 56C88E16
P 3325 4100
F 0 "#PWR021" H 3325 3950 50  0001 C CNN
F 1 "+5V" H 3325 4240 50  0000 C CNN
F 2 "" H 3325 4100 50  0000 C CNN
F 3 "" H 3325 4100 50  0000 C CNN
	1    3325 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3075 4100 3325 4100
$Comp
L CONN_02X02 P8
U 1 1 56C8A0A7
P 7375 4250
F 0 "P8" H 7375 4400 50  0000 C CNN
F 1 "CONN_02X02" H 7375 4100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x02" H 7375 3050 50  0001 C CNN
F 3 "" H 7375 3050 50  0000 C CNN
	1    7375 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2725 3700 2825 3700
Entry Wire Line
	2825 3700 2925 3800
Entry Wire Line
	2825 3800 2925 3900
Wire Wire Line
	2725 3800 2825 3800
Wire Bus Line
	2925 3400 2925 4450
Entry Wire Line
	3025 3800 3125 3700
Wire Bus Line
	3075 3700 3125 3700
Wire Wire Line
	2725 3900 2850 3900
Wire Wire Line
	2850 3900 2850 3925
Wire Wire Line
	2850 3925 3025 3925
Connection ~ 3025 3900
Text Label 2725 3700 0    39   ~ 0
SDA
Text Label 2725 3800 0    39   ~ 0
SCL
Wire Wire Line
	7125 4200 6975 4200
Wire Wire Line
	6975 4200 6975 4300
$Comp
L GND #PWR022
U 1 1 56C919A7
P 6975 4300
F 0 "#PWR022" H 6975 4050 50  0001 C CNN
F 1 "GND" H 6975 4150 50  0000 C CNN
F 2 "" H 6975 4300 50  0000 C CNN
F 3 "" H 6975 4300 50  0000 C CNN
	1    6975 4300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR023
U 1 1 56C91AD9
P 7750 4125
F 0 "#PWR023" H 7750 3975 50  0001 C CNN
F 1 "+5V" H 7750 4265 50  0000 C CNN
F 2 "" H 7750 4125 50  0000 C CNN
F 3 "" H 7750 4125 50  0000 C CNN
	1    7750 4125
	1    0    0    -1  
$EndComp
Wire Wire Line
	7625 4200 7750 4200
Wire Wire Line
	7750 4200 7750 4125
Entry Wire Line
	7550 3850 7650 3950
Entry Wire Line
	6975 3850 7075 3950
Wire Wire Line
	7125 4300 7075 4300
Wire Wire Line
	7075 4300 7075 3950
Wire Wire Line
	7625 4300 7650 4300
Wire Wire Line
	7650 4300 7650 3950
Text Label 7075 4100 0    39   ~ 0
SDA
Text Label 7650 4100 2    39   ~ 0
SCL
Wire Notes Line
	7850 3900 6875 3900
Wire Notes Line
	6875 3900 6875 4500
Wire Notes Line
	6875 4500 7850 4500
Wire Notes Line
	7850 4500 7850 3900
Text Notes 6875 4625 0    59   ~ 0
TWI Interface
Connection ~ 2350 6750
$Comp
L CONN_01X02 P9
U 1 1 56C77931
P 700 6800
F 0 "P9" H 700 6950 50  0000 C CNN
F 1 "CONN_01X02" V 800 6800 50  0000 C CNN
F 2 "Connect:AK300-2" H 700 6800 50  0001 C CNN
F 3 "" H 700 6800 50  0000 C CNN
	1    700  6800
	-1   0    0    1   
$EndComp
$Comp
L D_Small D1
U 1 1 56C78247
P 900 7025
F 0 "D1" H 850 7105 50  0000 L CNN
F 1 "D_Small" H 750 6945 50  0000 L CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Vertical_AnodeUp" V 900 7025 50  0001 C CNN
F 3 "" V 900 7025 50  0000 C CNN
	1    900  7025
	0    1    1    0   
$EndComp
Wire Wire Line
	900  6850 900  6925
Wire Wire Line
	1100 7050 1100 7150
Connection ~ 1100 7050
Wire Wire Line
	900  7125 1100 7125
Connection ~ 1100 7125
Wire Wire Line
	900  6750 1550 6750
Wire Wire Line
	1100 6750 1100 6550
Connection ~ 1100 6750
$EndSCHEMATC