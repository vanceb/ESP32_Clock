EESchema Schematic File Version 2
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
LIBS:ESP32-footprints-Shem-Lib
LIBS:switches
LIBS:silabs
LIBS:mcp73831
LIBS:leds
LIBS:ws2812b
LIBS:usb_otg
LIBS:mma8452q
LIBS:apds-9960
LIBS:BA33DD0WHFP
LIBS:ESP32_Clock-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP32-WROOM U2
U 1 1 5A79BBF8
P 2800 1900
F 0 "U2" H 2100 3150 60  0000 C CNN
F 1 "ESP32-WROOM" H 3300 3150 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP32-WROOM" H 3150 3250 60  0001 C CNN
F 3 "" H 2350 2350 60  0001 C CNN
	1    2800 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5AA68913
P 1650 2600
F 0 "#PWR01" H 1650 2350 50  0001 C CNN
F 1 "GND" H 1650 2450 50  0000 C CNN
F 2 "" H 1650 2600 50  0001 C CNN
F 3 "" H 1650 2600 50  0001 C CNN
	1    1650 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5AA6892B
P 3850 2550
F 0 "#PWR02" H 3850 2300 50  0001 C CNN
F 1 "GND" H 3850 2400 50  0000 C CNN
F 2 "" H 3850 2550 50  0001 C CNN
F 3 "" H 3850 2550 50  0001 C CNN
	1    3850 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5AA689A0
P 2350 2950
F 0 "#PWR03" H 2350 2700 50  0001 C CNN
F 1 "GND" H 2350 2800 50  0000 C CNN
F 2 "" H 2350 2950 50  0001 C CNN
F 3 "" H 2350 2950 50  0001 C CNN
	1    2350 2950
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR04
U 1 1 5AA689C0
P 1650 1300
F 0 "#PWR04" H 1650 1150 50  0001 C CNN
F 1 "+3V3" H 1650 1440 50  0000 C CNN
F 2 "" H 1650 1300 50  0001 C CNN
F 3 "" H 1650 1300 50  0001 C CNN
	1    1650 1300
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR05
U 1 1 5AA68A47
P 1050 850
F 0 "#PWR05" H 1050 700 50  0001 C CNN
F 1 "+3V3" H 1050 990 50  0000 C CNN
F 2 "" H 1050 850 50  0001 C CNN
F 3 "" H 1050 850 50  0001 C CNN
	1    1050 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5AA68A63
P 1050 1900
F 0 "#PWR06" H 1050 1650 50  0001 C CNN
F 1 "GND" H 1050 1750 50  0000 C CNN
F 2 "" H 1050 1900 50  0001 C CNN
F 3 "" H 1050 1900 50  0001 C CNN
	1    1050 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5AA68A7B
P 800 1900
F 0 "#PWR07" H 800 1650 50  0001 C CNN
F 1 "GND" H 800 1750 50  0000 C CNN
F 2 "" H 800 1900 50  0001 C CNN
F 3 "" H 800 1900 50  0001 C CNN
	1    800  1900
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5AA68A93
P 1050 1000
F 0 "R1" V 1130 1000 50  0000 C CNN
F 1 "10k" V 1050 1000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 980 1000 50  0001 C CNN
F 3 "" H 1050 1000 50  0001 C CNN
	1    1050 1000
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5AA68ABA
P 1050 1600
F 0 "C3" H 1075 1700 50  0000 L CNN
F 1 "1uF" H 1075 1500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1088 1450 50  0001 C CNN
F 3 "" H 1050 1600 50  0001 C CNN
	1    1050 1600
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW1
U 1 1 5AA68EC5
P 800 1600
F 0 "SW1" H 850 1700 50  0000 L CNN
F 1 "Reset" H 800 1540 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_EVPBF" H 800 1800 50  0001 C CNN
F 3 "" H 800 1800 50  0001 C CNN
	1    800  1600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 5AA69069
P 1050 3500
F 0 "#PWR08" H 1050 3250 50  0001 C CNN
F 1 "GND" H 1050 3350 50  0000 C CNN
F 2 "" H 1050 3500 50  0001 C CNN
F 3 "" H 1050 3500 50  0001 C CNN
	1    1050 3500
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5AA6908D
P 1050 3200
F 0 "C7" H 1075 3300 50  0000 L CNN
F 1 "100nF" H 1075 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1088 3050 50  0001 C CNN
F 3 "" H 1050 3200 50  0001 C CNN
	1    1050 3200
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5AA690CB
P 750 3200
F 0 "C6" H 775 3300 50  0000 L CNN
F 1 "10uF" H 775 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 788 3050 50  0001 C CNN
F 3 "" H 750 3200 50  0001 C CNN
	1    750  3200
	1    0    0    -1  
$EndComp
Text GLabel 1750 1500 0    60   Input ~ 0
VP
Text GLabel 1750 1600 0    60   Input ~ 0
VN
Text GLabel 1750 1900 0    60   BiDi ~ 0
IO32
Text GLabel 1750 2000 0    60   BiDi ~ 0
IO33
Text GLabel 1750 2100 0    60   BiDi ~ 0
IO25
Text GLabel 1750 2200 0    60   BiDi ~ 0
IO26
Text GLabel 1750 2300 0    60   BiDi ~ 0
IO27
Text GLabel 1750 2400 0    60   BiDi ~ 0
IO14
Text GLabel 1750 2500 0    60   BiDi ~ 0
IO12
Text GLabel 3800 1150 2    60   BiDi ~ 0
IO23
Text GLabel 3800 1250 2    60   BiDi ~ 0
IO22
Text GLabel 3800 1550 2    60   BiDi ~ 0
IO21
Text GLabel 3800 1750 2    60   BiDi ~ 0
IO19
Text GLabel 3800 1850 2    60   BiDi ~ 0
IO18
Text GLabel 3800 1950 2    60   BiDi ~ 0
IO5
Text GLabel 3800 2050 2    60   BiDi ~ 0
IO17
Text GLabel 3800 2150 2    60   BiDi ~ 0
IO16
Text GLabel 3800 2250 2    60   BiDi ~ 0
IO4
NoConn ~ 2550 2950
NoConn ~ 2650 2950
NoConn ~ 2750 2950
NoConn ~ 2850 2950
NoConn ~ 2950 2950
NoConn ~ 3050 2950
Text GLabel 3800 1350 2    60   Output ~ 0
TXD0
Text GLabel 3800 1450 2    60   Input ~ 0
RXD0
Text GLabel 1400 5800 2    60   UnSpc ~ 0
VBUS
Text GLabel 1400 6000 2    60   BiDi ~ 0
D+
Text GLabel 1400 6100 2    60   BiDi ~ 0
D-
$Comp
L GND #PWR09
U 1 1 5AA69D96
P 900 6550
F 0 "#PWR09" H 900 6300 50  0001 C CNN
F 1 "GND" H 900 6400 50  0000 C CNN
F 2 "" H 900 6550 50  0001 C CNN
F 3 "" H 900 6550 50  0001 C CNN
	1    900  6550
	1    0    0    -1  
$EndComp
NoConn ~ 1200 6200
$Comp
L CP2104 U4
U 1 1 5AA69F95
P 3300 6200
F 0 "U4" H 3000 7125 50  0000 R CNN
F 1 "CP2104" H 3000 7050 50  0000 R CNN
F 2 "QFN-24:QFN-24" H 3450 5250 50  0001 L CNN
F 3 "" H 2750 7450 50  0001 C CNN
	1    3300 6200
	1    0    0    -1  
$EndComp
Text GLabel 2300 5800 0    60   UnSpc ~ 0
VBUS
Text GLabel 2300 6100 0    60   BiDi ~ 0
D-
Text GLabel 2300 6200 0    60   BiDi ~ 0
D+
NoConn ~ 2600 6900
NoConn ~ 2600 6700
NoConn ~ 2600 6600
NoConn ~ 2600 6500
NoConn ~ 2600 6400
NoConn ~ 4000 6900
NoConn ~ 4000 6800
NoConn ~ 4000 6700
NoConn ~ 4000 5600
NoConn ~ 4000 5700
NoConn ~ 4000 5900
NoConn ~ 4000 6500
$Comp
L GND #PWR010
U 1 1 5AA6B082
P 3400 7350
F 0 "#PWR010" H 3400 7100 50  0001 C CNN
F 1 "GND" H 3400 7200 50  0000 C CNN
F 2 "" H 3400 7350 50  0001 C CNN
F 3 "" H 3400 7350 50  0001 C CNN
	1    3400 7350
	1    0    0    -1  
$EndComp
NoConn ~ 3500 5300
Text GLabel 4300 6100 2    60   Output ~ 0
RXD0
Text GLabel 4300 6200 2    60   Input ~ 0
TXD0
Text GLabel 4300 5800 2    60   BiDi ~ 0
DTR
Text GLabel 4300 6400 2    60   BiDi ~ 0
RTS
$Comp
L Q_DUAL_NPN_NPN_E1B1C2E2B2C1 Q3
U 1 1 5AA6B6C2
P 5350 6450
F 0 "Q3" H 5550 6500 50  0000 L CNN
F 1 "UMH3N" H 5550 6400 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-363_SC-70-6_Handsoldering" H 5550 6550 50  0001 C CNN
F 3 "" H 5350 6450 50  0001 C CNN
	1    5350 6450
	1    0    0    -1  
$EndComp
$Comp
L Q_DUAL_NPN_NPN_E1B1C2E2B2C1 Q3
U 2 1 5AA6B728
P 6000 7150
F 0 "Q3" H 6200 7200 50  0000 L CNN
F 1 "UMH3N" H 6200 7100 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-363_SC-70-6_Handsoldering" H 6200 7250 50  0001 C CNN
F 3 "" H 6000 7150 50  0001 C CNN
	2    6000 7150
	1    0    0    -1  
$EndComp
Text GLabel 5450 6150 2    60   BiDi ~ 0
EN
Text GLabel 5050 6450 0    60   BiDi ~ 0
DTR
Text GLabel 5450 6750 2    60   BiDi ~ 0
RTS
Text GLabel 6100 6850 2    60   BiDi ~ 0
IO0
Text GLabel 6100 7450 2    60   BiDi ~ 0
DTR
Text GLabel 5700 7150 0    60   BiDi ~ 0
RTS
$Comp
L GND #PWR011
U 1 1 5AA6C15C
P 1950 7500
F 0 "#PWR011" H 1950 7250 50  0001 C CNN
F 1 "GND" H 1950 7350 50  0000 C CNN
F 2 "" H 1950 7500 50  0001 C CNN
F 3 "" H 1950 7500 50  0001 C CNN
	1    1950 7500
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5AA6C162
P 1950 7200
F 0 "C9" H 1975 7300 50  0000 L CNN
F 1 "100nF" H 1975 7100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1988 7050 50  0001 C CNN
F 3 "" H 1950 7200 50  0001 C CNN
	1    1950 7200
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5AA6C168
P 1650 7200
F 0 "C8" H 1675 7300 50  0000 L CNN
F 1 "10uF" H 1675 7100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1688 7050 50  0001 C CNN
F 3 "" H 1650 7200 50  0001 C CNN
	1    1650 7200
	1    0    0    -1  
$EndComp
$Comp
L Q_DUAL_PNP_PNP_E1B1C2E2B2C1 Q2
U 1 1 5AA6C214
P 5400 1400
F 0 "Q2" H 5600 1450 50  0000 L CNN
F 1 "BCM857" H 5600 1350 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-363_SC-70-6_Handsoldering" H 5600 1500 50  0001 C CNN
F 3 "" H 5400 1400 50  0001 C CNN
	1    5400 1400
	-1   0    0    1   
$EndComp
$Comp
L Q_DUAL_PNP_PNP_E1B1C2E2B2C1 Q2
U 2 1 5AA6C2EA
P 6100 1400
F 0 "Q2" H 6300 1450 50  0000 L CNN
F 1 "BCM857" H 6300 1350 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-363_SC-70-6_Handsoldering" H 6300 1500 50  0001 C CNN
F 3 "" H 6100 1400 50  0001 C CNN
	2    6100 1400
	1    0    0    1   
$EndComp
$Comp
L R R3
U 1 1 5AA6C39E
P 5300 2050
F 0 "R3" V 5380 2050 50  0000 C CNN
F 1 "10k" V 5300 2050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5230 2050 50  0001 C CNN
F 3 "" H 5300 2050 50  0001 C CNN
	1    5300 2050
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5AA6C401
P 6200 2050
F 0 "R4" V 6280 2050 50  0000 C CNN
F 1 "47k" V 6200 2050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6130 2050 50  0001 C CNN
F 3 "" H 6200 2050 50  0001 C CNN
	1    6200 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5AA6C45F
P 6200 2300
F 0 "#PWR012" H 6200 2050 50  0001 C CNN
F 1 "GND" H 6200 2150 50  0000 C CNN
F 2 "" H 6200 2300 50  0001 C CNN
F 3 "" H 6200 2300 50  0001 C CNN
	1    6200 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5AA6C4B3
P 5300 2300
F 0 "#PWR013" H 5300 2050 50  0001 C CNN
F 1 "GND" H 5300 2150 50  0000 C CNN
F 2 "" H 5300 2300 50  0001 C CNN
F 3 "" H 5300 2300 50  0001 C CNN
	1    5300 2300
	1    0    0    -1  
$EndComp
Text GLabel 5200 900  0    60   BiDi ~ 0
VBUS
$Comp
L +5V #PWR014
U 1 1 5AA6C5E5
P 6300 900
F 0 "#PWR014" H 6300 750 50  0001 C CNN
F 1 "+5V" H 6300 1040 50  0000 C CNN
F 2 "" H 6300 900 50  0001 C CNN
F 3 "" H 6300 900 50  0001 C CNN
	1    6300 900 
	1    0    0    -1  
$EndComp
$Comp
L MCP73831 U1
U 1 1 5AA823B8
P 7950 750
F 0 "U1" H 7750 900 60  0000 C CNN
F 1 "MCP73831" H 7950 750 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 7950 750 60  0001 C CNN
F 3 "" H 7950 750 60  0001 C CNN
	1    7950 750 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR015
U 1 1 5AA8251F
P 7100 800
F 0 "#PWR015" H 7100 650 50  0001 C CNN
F 1 "+5V" H 7100 940 50  0000 C CNN
F 2 "" H 7100 800 50  0001 C CNN
F 3 "" H 7100 800 50  0001 C CNN
	1    7100 800 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5AA8257B
P 8650 1450
F 0 "#PWR016" H 8650 1200 50  0001 C CNN
F 1 "GND" H 8650 1300 50  0000 C CNN
F 2 "" H 8650 1450 50  0001 C CNN
F 3 "" H 8650 1450 50  0001 C CNN
	1    8650 1450
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5AA825D7
P 8650 1200
F 0 "R2" V 8730 1200 50  0000 C CNN
F 1 "2k" V 8650 1200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8580 1200 50  0001 C CNN
F 3 "" H 8650 1200 50  0001 C CNN
	1    8650 1200
	1    0    0    -1  
$EndComp
NoConn ~ 7450 1200
$Comp
L C C1
U 1 1 5AA82B61
P 7100 1100
F 0 "C1" H 7125 1200 50  0000 L CNN
F 1 "4.7uF" H 7125 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7138 950 50  0001 C CNN
F 3 "" H 7100 1100 50  0001 C CNN
	1    7100 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5AA82C16
P 7100 1350
F 0 "#PWR017" H 7100 1100 50  0001 C CNN
F 1 "GND" H 7100 1200 50  0000 C CNN
F 2 "" H 7100 1350 50  0001 C CNN
F 3 "" H 7100 1350 50  0001 C CNN
	1    7100 1350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AA8309F
P 9000 1100
F 0 "C2" H 9025 1200 50  0000 L CNN
F 1 "4.7uF" H 9025 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9038 950 50  0001 C CNN
F 3 "" H 9000 1100 50  0001 C CNN
	1    9000 1100
	1    0    0    -1  
$EndComp
Text GLabel 9100 900  2    60   UnSpc ~ 0
VBAT
$Comp
L GND #PWR018
U 1 1 5AA831D2
P 9000 1350
F 0 "#PWR018" H 9000 1100 50  0001 C CNN
F 1 "GND" H 9000 1200 50  0000 C CNN
F 2 "" H 9000 1350 50  0001 C CNN
F 3 "" H 9000 1350 50  0001 C CNN
	1    9000 1350
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5AA83550
P 8700 2500
F 0 "C5" H 8725 2600 50  0000 L CNN
F 1 "10uF" H 8725 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8738 2350 50  0001 C CNN
F 3 "" H 8700 2500 50  0001 C CNN
	1    8700 2500
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5AA835CA
P 7300 2500
F 0 "C4" H 7325 2600 50  0000 L CNN
F 1 "100nF" H 7325 2400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7338 2350 50  0001 C CNN
F 3 "" H 7300 2500 50  0001 C CNN
	1    7300 2500
	1    0    0    -1  
$EndComp
Text GLabel 7050 2050 1    60   UnSpc ~ 0
VBAT
$Comp
L GND #PWR019
U 1 1 5AA83812
P 8000 2750
F 0 "#PWR019" H 8000 2500 50  0001 C CNN
F 1 "GND" H 8000 2600 50  0000 C CNN
F 2 "" H 8000 2750 50  0001 C CNN
F 3 "" H 8000 2750 50  0001 C CNN
	1    8000 2750
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J1
U 1 1 5AA83C7F
P 10500 950
F 0 "J1" H 10500 1050 50  0000 C CNN
F 1 "Battery" H 10500 750 50  0000 C CNN
F 2 "Connectors_JST:JST_PH_S2B-PH-K_02x2.00mm_Angled" H 10500 950 50  0001 C CNN
F 3 "" H 10500 950 50  0001 C CNN
	1    10500 950 
	1    0    0    -1  
$EndComp
Text GLabel 10150 950  0    60   UnSpc ~ 0
VBAT
$Comp
L GND #PWR020
U 1 1 5AA83E34
P 10050 1050
F 0 "#PWR020" H 10050 800 50  0001 C CNN
F 1 "GND" H 10050 900 50  0000 C CNN
F 2 "" H 10050 1050 50  0001 C CNN
F 3 "" H 10050 1050 50  0001 C CNN
	1    10050 1050
	1    0    0    -1  
$EndComp
$Sheet
S 5050 3300 900  550 
U 5AA846F0
F0 "LEDs" 60
F1 "LEDs.sch" 60
F2 "DIN" U L 5050 3550 60 
F3 "DOUT" I R 5950 3550 60 
$EndSheet
Text Notes 7150 4300 0    60   ~ 0
IO25 - SDA for Gesture\nIO26 - SCL for Gesture\nIO27 - Interrupt for Gesture\n\nIO18 - SDA for Accelerometer\nIO19 - SCL for Accelerometer\nIO22 - Interrupt 2 for Accelerometer\nIO23 - Interrupt 1 for Accelerometer
Text GLabel 1350 1150 1    60   Input ~ 0
EN
Text GLabel 4550 3550 0    60   Input ~ 0
IO21
$Comp
L Conn_01x04 J5
U 1 1 5AA96FDC
P 10500 5150
F 0 "J5" H 10500 5350 50  0000 C CNN
F 1 "Grove 2" H 10500 4850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 10500 5150 50  0001 C CNN
F 3 "" H 10500 5150 50  0001 C CNN
	1    10500 5150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J6
U 1 1 5AA97082
P 9050 5800
F 0 "J6" H 9050 6000 50  0000 C CNN
F 1 "Grove 3" H 9050 5500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 9050 5800 50  0001 C CNN
F 3 "" H 9050 5800 50  0001 C CNN
	1    9050 5800
	1    0    0    -1  
$EndComp
Text GLabel 4550 4700 0    60   Input ~ 0
IO4
Text GLabel 4550 4800 0    60   Input ~ 0
IO5
Text GLabel 9950 5700 0    60   Input ~ 0
IO12
Text GLabel 9950 5800 0    60   Input ~ 0
IO14
$Comp
L Conn_01x04 J4
U 1 1 5AA97EBD
P 9050 5150
F 0 "J4" H 9050 5350 50  0000 C CNN
F 1 "Grove 1" H 9050 4850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 9050 5150 50  0001 C CNN
F 3 "" H 9050 5150 50  0001 C CNN
	1    9050 5150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J7
U 1 1 5AA97F64
P 10500 5800
F 0 "J7" H 10500 6000 50  0000 C CNN
F 1 "Grove 4" H 10500 5500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 10500 5800 50  0001 C CNN
F 3 "" H 10500 5800 50  0001 C CNN
	1    10500 5800
	1    0    0    -1  
$EndComp
Text GLabel 4550 4900 0    60   Input ~ 0
IO16
Text GLabel 4550 5000 0    60   Input ~ 0
IO17
Text GLabel 4550 4400 0    60   Input ~ 0
IO32
Text GLabel 4550 4300 0    60   Input ~ 0
IO33
$Comp
L +3V3 #PWR021
U 1 1 5AA988EE
P 9600 5250
F 0 "#PWR021" H 9600 5100 50  0001 C CNN
F 1 "+3V3" H 9600 5390 50  0000 C CNN
F 2 "" H 9600 5250 50  0001 C CNN
F 3 "" H 9600 5250 50  0001 C CNN
	1    9600 5250
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR022
U 1 1 5AA9898E
P 8150 5900
F 0 "#PWR022" H 8150 5750 50  0001 C CNN
F 1 "+3V3" H 8150 6040 50  0000 C CNN
F 2 "" H 8150 5900 50  0001 C CNN
F 3 "" H 8150 5900 50  0001 C CNN
	1    8150 5900
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR023
U 1 1 5AA98A2E
P 9500 5900
F 0 "#PWR023" H 9500 5750 50  0001 C CNN
F 1 "+3V3" H 9500 6040 50  0000 C CNN
F 2 "" H 9500 5900 50  0001 C CNN
F 3 "" H 9500 5900 50  0001 C CNN
	1    9500 5900
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR024
U 1 1 5AA98ACE
P 8050 5250
F 0 "#PWR024" H 8050 5100 50  0001 C CNN
F 1 "+3V3" H 8050 5390 50  0000 C CNN
F 2 "" H 8050 5250 50  0001 C CNN
F 3 "" H 8050 5250 50  0001 C CNN
	1    8050 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5AA98B6E
P 8050 5350
F 0 "#PWR025" H 8050 5100 50  0001 C CNN
F 1 "GND" H 8050 5200 50  0000 C CNN
F 2 "" H 8050 5350 50  0001 C CNN
F 3 "" H 8050 5350 50  0001 C CNN
	1    8050 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 5AA98C0E
P 9500 6000
F 0 "#PWR026" H 9500 5750 50  0001 C CNN
F 1 "GND" H 9500 5850 50  0000 C CNN
F 2 "" H 9500 6000 50  0001 C CNN
F 3 "" H 9500 6000 50  0001 C CNN
	1    9500 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 5AA98CAE
P 9600 5350
F 0 "#PWR027" H 9600 5100 50  0001 C CNN
F 1 "GND" H 9600 5200 50  0000 C CNN
F 2 "" H 9600 5350 50  0001 C CNN
F 3 "" H 9600 5350 50  0001 C CNN
	1    9600 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 5AA98D4E
P 8150 6000
F 0 "#PWR028" H 8150 5750 50  0001 C CNN
F 1 "GND" H 8150 5850 50  0000 C CNN
F 2 "" H 8150 6000 50  0001 C CNN
F 3 "" H 8150 6000 50  0001 C CNN
	1    8150 6000
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW2
U 1 1 5AA997A2
P 4350 2350
F 0 "SW2" H 4400 2450 50  0000 L CNN
F 1 "Program" H 4350 2290 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_EVPBF" H 4350 2550 50  0001 C CNN
F 3 "" H 4350 2550 50  0001 C CNN
	1    4350 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 5AA99897
P 4700 2350
F 0 "#PWR029" H 4700 2100 50  0001 C CNN
F 1 "GND" H 4700 2200 50  0000 C CNN
F 2 "" H 4700 2350 50  0001 C CNN
F 3 "" H 4700 2350 50  0001 C CNN
	1    4700 2350
	1    0    0    -1  
$EndComp
Text GLabel 4100 2550 3    60   Input ~ 0
IO0
$Comp
L Conn_01x03 J2
U 1 1 5AA9B0F6
P 6500 3550
F 0 "J2" H 6500 3750 50  0000 C CNN
F 1 "LEDs" H 6500 3350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 6500 3550 50  0001 C CNN
F 3 "" H 6500 3550 50  0001 C CNN
	1    6500 3550
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR030
U 1 1 5AA9B216
P 6150 3350
F 0 "#PWR030" H 6150 3200 50  0001 C CNN
F 1 "+3V3" H 6150 3490 50  0000 C CNN
F 2 "" H 6150 3350 50  0001 C CNN
F 3 "" H 6150 3350 50  0001 C CNN
	1    6150 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 5AA9B2CE
P 6150 3650
F 0 "#PWR031" H 6150 3400 50  0001 C CNN
F 1 "GND" H 6150 3500 50  0000 C CNN
F 2 "" H 6150 3650 50  0001 C CNN
F 3 "" H 6150 3650 50  0001 C CNN
	1    6150 3650
	1    0    0    -1  
$EndComp
NoConn ~ 3250 2950
$Comp
L USB_OTG J8
U 1 1 5AA9CCCA
P 900 6000
F 0 "J8" H 700 6450 50  0000 L CNN
F 1 "USB_OTG" H 700 6350 50  0000 L CNN
F 2 "MicroUSB_Custom:MicroUSB" H 1050 5950 50  0001 C CNN
F 3 "" H 1050 5950 50  0001 C CNN
	1    900  6000
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG032
U 1 1 5AA9CFE1
P 1300 5650
F 0 "#FLG032" H 1300 5725 50  0001 C CNN
F 1 "PWR_FLAG" H 1300 5800 50  0000 C CNN
F 2 "" H 1300 5650 50  0001 C CNN
F 3 "" H 1300 5650 50  0001 C CNN
	1    1300 5650
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG033
U 1 1 5AA9D35E
P 6100 750
F 0 "#FLG033" H 6100 825 50  0001 C CNN
F 1 "PWR_FLAG" H 6100 900 50  0000 C CNN
F 2 "" H 6100 750 50  0001 C CNN
F 3 "" H 6100 750 50  0001 C CNN
	1    6100 750 
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5AA9DF28
P 9750 2050
F 0 "R5" V 9830 2050 50  0000 C CNN
F 1 "4k7" V 9750 2050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9680 2050 50  0001 C CNN
F 3 "" H 9750 2050 50  0001 C CNN
	1    9750 2050
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5AA9DFF8
P 9750 2350
F 0 "R7" V 9830 2350 50  0000 C CNN
F 1 "4k7" V 9750 2350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9680 2350 50  0001 C CNN
F 3 "" H 9750 2350 50  0001 C CNN
	1    9750 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 5AA9E28E
P 9750 2500
F 0 "#PWR034" H 9750 2250 50  0001 C CNN
F 1 "GND" H 9750 2350 50  0000 C CNN
F 2 "" H 9750 2500 50  0001 C CNN
F 3 "" H 9750 2500 50  0001 C CNN
	1    9750 2500
	1    0    0    -1  
$EndComp
Text GLabel 9750 1900 1    60   Input ~ 0
VBAT
Text GLabel 9900 2200 2    60   Input ~ 0
VN
$Comp
L R R6
U 1 1 5AA9E857
P 10400 2050
F 0 "R6" V 10480 2050 50  0000 C CNN
F 1 "4k7" V 10400 2050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 10330 2050 50  0001 C CNN
F 3 "" H 10400 2050 50  0001 C CNN
	1    10400 2050
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5AA9E85D
P 10400 2350
F 0 "R8" V 10480 2350 50  0000 C CNN
F 1 "4k7" V 10400 2350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 10330 2350 50  0001 C CNN
F 3 "" H 10400 2350 50  0001 C CNN
	1    10400 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 5AA9E863
P 10400 2500
F 0 "#PWR035" H 10400 2250 50  0001 C CNN
F 1 "GND" H 10400 2350 50  0000 C CNN
F 2 "" H 10400 2500 50  0001 C CNN
F 3 "" H 10400 2500 50  0001 C CNN
	1    10400 2500
	1    0    0    -1  
$EndComp
Text GLabel 10550 2200 2    60   Input ~ 0
VP
$Comp
L +5V #PWR036
U 1 1 5AA9E9BF
P 10400 1900
F 0 "#PWR036" H 10400 1750 50  0001 C CNN
F 1 "+5V" H 10400 2040 50  0000 C CNN
F 2 "" H 10400 1900 50  0001 C CNN
F 3 "" H 10400 1900 50  0001 C CNN
	1    10400 1900
	1    0    0    -1  
$EndComp
NoConn ~ 1850 1700
NoConn ~ 1850 1800
$Comp
L BSS83P Q1
U 1 1 5AAA5C51
P 5750 1000
F 0 "Q1" V 5900 1100 50  0000 L CNN
F 1 "NXP2301P" V 6000 800 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5950 925 50  0001 L CIN
F 3 "" H 5750 1000 50  0001 L CNN
	1    5750 1000
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 5AAA6F55
P 2450 3350
F 0 "D1" H 2450 3450 50  0000 C CNN
F 1 "LED" H 2450 3250 50  0000 C CNN
F 2 "LEDs:LED_0603_HandSoldering" H 2450 3350 50  0001 C CNN
F 3 "" H 2450 3350 50  0001 C CNN
	1    2450 3350
	0    1    1    0   
$EndComp
$Comp
L LED D2
U 1 1 5AAA7040
P 3150 3350
F 0 "D2" H 3150 3450 50  0000 C CNN
F 1 "LED" H 3150 3250 50  0000 C CNN
F 2 "LEDs:LED_0603_HandSoldering" H 3150 3350 50  0001 C CNN
F 3 "" H 3150 3350 50  0001 C CNN
	1    3150 3350
	0    1    1    0   
$EndComp
$Comp
L R R10
U 1 1 5AAA7131
P 3300 3500
F 0 "R10" V 3380 3500 50  0000 C CNN
F 1 "1k" V 3300 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3230 3500 50  0001 C CNN
F 3 "" H 3300 3500 50  0001 C CNN
	1    3300 3500
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 5AAA721D
P 2300 3500
F 0 "R9" V 2380 3500 50  0000 C CNN
F 1 "1k" V 2300 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2230 3500 50  0001 C CNN
F 3 "" H 2300 3500 50  0001 C CNN
	1    2300 3500
	0    1    1    0   
$EndComp
$Comp
L +3V3 #PWR037
U 1 1 5AAA7306
P 3450 3500
F 0 "#PWR037" H 3450 3350 50  0001 C CNN
F 1 "+3V3" H 3450 3640 50  0000 C CNN
F 2 "" H 3450 3500 50  0001 C CNN
F 3 "" H 3450 3500 50  0001 C CNN
	1    3450 3500
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR038
U 1 1 5AAA75E8
P 2150 3500
F 0 "#PWR038" H 2150 3350 50  0001 C CNN
F 1 "+3V3" H 2150 3640 50  0000 C CNN
F 2 "" H 2150 3500 50  0001 C CNN
F 3 "" H 2150 3500 50  0001 C CNN
	1    2150 3500
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J3
U 1 1 5AAB9F14
P 1000 4400
F 0 "J3" H 1000 4600 50  0000 C CNN
F 1 "PWR" H 1000 4100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 1000 4400 50  0001 C CNN
F 3 "" H 1000 4400 50  0001 C CNN
	1    1000 4400
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR039
U 1 1 5AABA03D
P 1400 4300
F 0 "#PWR039" H 1400 4150 50  0001 C CNN
F 1 "+5V" H 1400 4440 50  0000 C CNN
F 2 "" H 1400 4300 50  0001 C CNN
F 3 "" H 1400 4300 50  0001 C CNN
	1    1400 4300
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR040
U 1 1 5AABA125
P 1950 4500
F 0 "#PWR040" H 1950 4350 50  0001 C CNN
F 1 "+3V3" H 1950 4640 50  0000 C CNN
F 2 "" H 1950 4500 50  0001 C CNN
F 3 "" H 1950 4500 50  0001 C CNN
	1    1950 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR041
U 1 1 5AABA20D
P 1400 4650
F 0 "#PWR041" H 1400 4400 50  0001 C CNN
F 1 "GND" H 1400 4500 50  0000 C CNN
F 2 "" H 1400 4650 50  0001 C CNN
F 3 "" H 1400 4650 50  0001 C CNN
	1    1400 4650
	1    0    0    -1  
$EndComp
Text GLabel 1400 4400 2    60   Input ~ 0
VBAT
$Sheet
S 5050 4150 900  1000
U 5AABE210
F0 "sensors" 60
F1 "sensors.sch" 60
F2 "INT0" I L 5050 4500 60 
F3 "SDA0" I L 5050 4300 60 
F4 "SCL0" I L 5050 4400 60 
F5 "SDA1" I L 5050 4700 60 
F6 "SCL1" I L 5050 4800 60 
F7 "INT1" I L 5050 4900 60 
F8 "INT2" I L 5050 5000 60 
$EndSheet
Text GLabel 8600 5800 0    60   Input ~ 0
IO27
Text GLabel 8600 5700 0    60   Input ~ 0
IO26
Text GLabel 4550 4500 0    60   Input ~ 0
IO25
Text GLabel 10050 5050 0    60   Input ~ 0
IO18
Text GLabel 10050 5150 0    60   Input ~ 0
IO19
Text GLabel 8500 5150 0    60   Input ~ 0
IO23
Text GLabel 8500 5050 0    60   Input ~ 0
IO22
$Comp
L +3V3 #PWR042
U 1 1 5AAFF8E4
P 9300 2350
F 0 "#PWR042" H 9300 2200 50  0001 C CNN
F 1 "+3V3" H 9300 2490 50  0000 C CNN
F 2 "" H 9300 2350 50  0001 C CNN
F 3 "" H 9300 2350 50  0001 C CNN
	1    9300 2350
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR043
U 1 1 5AB001AA
P 1050 2800
F 0 "#PWR043" H 1050 2650 50  0001 C CNN
F 1 "+3V3" H 1050 2940 50  0000 C CNN
F 2 "" H 1050 2800 50  0001 C CNN
F 3 "" H 1050 2800 50  0001 C CNN
	1    1050 2800
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR044
U 1 1 5AB00D6B
P 3300 5100
F 0 "#PWR044" H 3300 4950 50  0001 C CNN
F 1 "+3V3" H 3300 5240 50  0000 C CNN
F 2 "" H 3300 5100 50  0001 C CNN
F 3 "" H 3300 5100 50  0001 C CNN
	1    3300 5100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR045
U 1 1 5AB00EF7
P 2300 5450
F 0 "#PWR045" H 2300 5300 50  0001 C CNN
F 1 "+3V3" H 2300 5590 50  0000 C CNN
F 2 "" H 2300 5450 50  0001 C CNN
F 3 "" H 2300 5450 50  0001 C CNN
	1    2300 5450
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR046
U 1 1 5AB01083
P 1950 6800
F 0 "#PWR046" H 1950 6650 50  0001 C CNN
F 1 "+3V3" H 1950 6940 50  0000 C CNN
F 2 "" H 1950 6800 50  0001 C CNN
F 3 "" H 1950 6800 50  0001 C CNN
	1    1950 6800
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x06 J12
U 1 1 5AB005A6
P 7100 5800
F 0 "J12" H 7100 6100 50  0000 C CNN
F 1 "FTDI" H 7100 5400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 7100 5800 50  0001 C CNN
F 3 "" H 7100 5800 50  0001 C CNN
	1    7100 5800
	1    0    0    -1  
$EndComp
Text GLabel 6700 5600 0    60   BiDi ~ 0
DTR
Text GLabel 6700 5700 0    60   Input ~ 0
TXD0
Text GLabel 6700 5800 0    60   Output ~ 0
RXD0
NoConn ~ 6900 6000
$Comp
L +3V3 #PWR047
U 1 1 5AB00BB3
P 6250 5900
F 0 "#PWR047" H 6250 5750 50  0001 C CNN
F 1 "+3V3" H 6250 6040 50  0000 C CNN
F 2 "" H 6250 5900 50  0001 C CNN
F 3 "" H 6250 5900 50  0001 C CNN
	1    6250 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 5AB00CD7
P 6250 6100
F 0 "#PWR048" H 6250 5850 50  0001 C CNN
F 1 "GND" H 6250 5950 50  0000 C CNN
F 2 "" H 6250 6100 50  0001 C CNN
F 3 "" H 6250 6100 50  0001 C CNN
	1    6250 6100
	1    0    0    -1  
$EndComp
$Comp
L BA33DD0WHFP U3
U 1 1 5ABCF33F
P 8000 2450
F 0 "U3" H 7750 2800 60  0000 C CNN
F 1 "BA33DD0WHFP" H 8250 2800 60  0000 C CNN
F 2 "LDO:LDO" H 8000 2450 60  0001 C CNN
F 3 "" H 8000 2450 60  0001 C CNN
	1    8000 2450
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D3
U 1 1 5ABCF960
P 7050 2200
F 0 "D3" H 7050 2300 50  0000 C CNN
F 1 " " H 7050 2100 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 7050 2200 50  0001 C CNN
F 3 "" H 7050 2200 50  0001 C CNN
	1    7050 2200
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR049
U 1 1 5ABCFAB7
P 6750 2350
F 0 "#PWR049" H 6750 2200 50  0001 C CNN
F 1 "+5V" H 6750 2490 50  0000 C CNN
F 2 "" H 6750 2350 50  0001 C CNN
F 3 "" H 6750 2350 50  0001 C CNN
	1    6750 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1300 1850 1300
Wire Wire Line
	1650 2600 1850 2600
Wire Wire Line
	3700 2550 3850 2550
Wire Wire Line
	1050 1750 1050 1900
Wire Wire Line
	800  1800 800  1900
Wire Wire Line
	800  1400 1850 1400
Wire Wire Line
	1050 1150 1050 1450
Connection ~ 1050 1400
Wire Wire Line
	1050 3350 1050 3500
Wire Wire Line
	1050 2800 1050 3050
Wire Wire Line
	750  2800 750  3050
Wire Wire Line
	750  2950 1050 2950
Connection ~ 1050 2950
Wire Wire Line
	750  3350 750  3450
Wire Wire Line
	750  3450 1050 3450
Connection ~ 1050 3450
Wire Wire Line
	3700 2450 3750 2450
Wire Wire Line
	3750 2450 3750 2550
Connection ~ 3750 2550
Wire Wire Line
	1750 1500 1850 1500
Wire Wire Line
	1750 1600 1850 1600
Wire Wire Line
	1750 1900 1850 1900
Wire Wire Line
	1750 2000 1850 2000
Wire Wire Line
	1750 2100 1850 2100
Wire Wire Line
	1750 2200 1850 2200
Wire Wire Line
	1750 2300 1850 2300
Wire Wire Line
	1750 2400 1850 2400
Wire Wire Line
	1750 2500 1850 2500
Wire Wire Line
	3700 1150 3800 1150
Wire Wire Line
	3700 1250 3800 1250
Wire Wire Line
	3700 1550 3800 1550
Wire Wire Line
	3700 1750 3800 1750
Wire Wire Line
	3700 1850 3800 1850
Wire Wire Line
	3700 1950 3800 1950
Wire Wire Line
	3700 2050 3800 2050
Wire Wire Line
	3700 2150 3800 2150
Wire Wire Line
	3700 2250 3800 2250
Wire Wire Line
	3700 2350 4150 2350
Wire Wire Line
	3700 1350 3800 1350
Wire Wire Line
	3700 1450 3800 1450
Wire Wire Line
	1200 5800 1400 5800
Wire Wire Line
	1200 6000 1400 6000
Wire Wire Line
	1200 6100 1400 6100
Wire Wire Line
	900  6400 900  6550
Wire Wire Line
	800  6400 800  6500
Wire Wire Line
	800  6500 900  6500
Connection ~ 900  6500
Wire Wire Line
	2300 5450 2300 5600
Wire Wire Line
	2300 5600 2600 5600
Wire Wire Line
	2300 5800 2600 5800
Wire Wire Line
	2300 6100 2600 6100
Wire Wire Line
	2300 6200 2600 6200
Wire Wire Line
	3300 5100 3300 5300
Wire Wire Line
	3100 5300 3100 5200
Wire Wire Line
	3100 5200 3300 5200
Connection ~ 3300 5200
Wire Wire Line
	3400 7200 3400 7350
Wire Wire Line
	3300 7200 3300 7250
Wire Wire Line
	3300 7250 3400 7250
Connection ~ 3400 7250
Wire Wire Line
	4300 6100 4000 6100
Wire Wire Line
	4300 6200 4000 6200
Wire Wire Line
	4000 5800 4300 5800
Wire Wire Line
	4000 6400 4300 6400
Wire Wire Line
	5050 6450 5150 6450
Wire Wire Line
	5450 6150 5450 6250
Wire Wire Line
	5450 6650 5450 6750
Wire Wire Line
	6100 6850 6100 6950
Wire Wire Line
	5700 7150 5800 7150
Wire Wire Line
	6100 7350 6100 7450
Wire Wire Line
	1950 7350 1950 7500
Wire Wire Line
	1950 6800 1950 7050
Wire Wire Line
	1650 7050 1650 6950
Wire Wire Line
	1650 6950 1950 6950
Connection ~ 1950 6950
Wire Wire Line
	1650 7350 1650 7450
Wire Wire Line
	1650 7450 1950 7450
Connection ~ 1950 7450
Wire Wire Line
	5200 900  5550 900 
Wire Wire Line
	5950 900  6300 900 
Wire Wire Line
	5300 1200 5300 900 
Connection ~ 5300 900 
Wire Wire Line
	6200 1200 6200 900 
Connection ~ 6200 900 
Wire Wire Line
	5300 1600 5300 1900
Wire Wire Line
	6200 1600 6200 1900
Wire Wire Line
	5300 2200 5300 2300
Wire Wire Line
	6200 2200 6200 2300
Wire Wire Line
	5900 1700 5900 1400
Wire Wire Line
	5300 1700 5900 1700
Connection ~ 5300 1700
Wire Wire Line
	5600 1400 5600 1700
Connection ~ 5600 1700
Wire Wire Line
	5750 1200 5750 1800
Wire Wire Line
	5750 1800 6200 1800
Connection ~ 6200 1800
Wire Wire Line
	8450 1050 8650 1050
Wire Wire Line
	8650 1350 8650 1450
Wire Wire Line
	8450 1200 8450 1400
Wire Wire Line
	8450 1400 8650 1400
Connection ~ 8650 1400
Wire Wire Line
	7100 1250 7100 1350
Wire Wire Line
	7100 800  7100 950 
Wire Wire Line
	7450 900  7100 900 
Connection ~ 7100 900 
Wire Wire Line
	8450 900  9100 900 
Wire Wire Line
	9000 950  9000 900 
Connection ~ 9000 900 
Wire Wire Line
	9000 1250 9000 1350
Wire Wire Line
	10150 950  10300 950 
Wire Wire Line
	10050 1050 10300 1050
Wire Wire Line
	4550 3550 5050 3550
Wire Wire Line
	1350 1150 1350 1400
Connection ~ 1350 1400
Wire Wire Line
	10050 5050 10300 5050
Wire Wire Line
	10050 5150 10300 5150
Wire Wire Line
	8600 5700 8850 5700
Wire Wire Line
	8600 5800 8850 5800
Wire Wire Line
	8500 5050 8850 5050
Wire Wire Line
	8500 5150 8850 5150
Wire Wire Line
	9950 5700 10300 5700
Wire Wire Line
	9950 5800 10300 5800
Wire Wire Line
	9600 5250 10300 5250
Wire Wire Line
	9600 5350 10300 5350
Wire Wire Line
	8150 5900 8850 5900
Wire Wire Line
	8150 6000 8850 6000
Wire Wire Line
	8050 5250 8850 5250
Wire Wire Line
	8050 5350 8850 5350
Wire Wire Line
	9500 5900 10300 5900
Wire Wire Line
	9500 6000 10300 6000
Wire Wire Line
	4550 2350 4700 2350
Wire Wire Line
	4100 2350 4100 2550
Connection ~ 4100 2350
Wire Wire Line
	6150 3650 6300 3650
Wire Wire Line
	6300 3450 6150 3450
Wire Wire Line
	6150 3450 6150 3350
Wire Wire Line
	5950 3550 6300 3550
Wire Wire Line
	1300 5650 1300 5800
Connection ~ 1300 5800
Connection ~ 750  2950
Wire Wire Line
	6100 750  6100 900 
Connection ~ 6100 900 
Wire Wire Line
	9750 2200 9900 2200
Wire Wire Line
	10400 2200 10550 2200
Wire Wire Line
	3150 3200 3150 2950
Wire Wire Line
	2450 3200 2450 2950
Wire Wire Line
	1200 4300 1400 4300
Wire Wire Line
	1200 4400 1400 4400
Wire Wire Line
	1200 4500 1950 4500
Wire Wire Line
	1200 4600 1400 4600
Wire Wire Line
	1400 4600 1400 4650
Wire Wire Line
	4550 4300 5050 4300
Wire Wire Line
	4550 4400 5050 4400
Wire Wire Line
	4550 4500 5050 4500
Wire Wire Line
	4550 4700 5050 4700
Wire Wire Line
	4550 4800 5050 4800
Wire Wire Line
	4550 4900 5050 4900
Wire Wire Line
	4550 5000 5050 5000
Wire Wire Line
	6700 5600 6900 5600
Wire Wire Line
	6700 5700 6900 5700
Wire Wire Line
	6700 5800 6900 5800
Wire Wire Line
	6250 5900 6900 5900
Wire Wire Line
	6250 6100 6900 6100
Wire Wire Line
	6750 2350 7500 2350
Connection ~ 7050 2350
Connection ~ 7300 2350
Wire Wire Line
	7300 2650 7300 2750
Wire Wire Line
	7300 2750 9050 2750
Wire Wire Line
	8700 2750 8700 2650
Connection ~ 8000 2750
Wire Wire Line
	8000 2700 8000 2750
$Comp
L CP C45
U 1 1 5ABD0472
P 9050 2500
F 0 "C45" H 9075 2600 50  0000 L CNN
F 1 "CP" H 9075 2400 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 9088 2350 50  0001 C CNN
F 3 "" H 9050 2500 50  0001 C CNN
	1    9050 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2350 9300 2350
Connection ~ 8700 2350
Connection ~ 9050 2350
Wire Wire Line
	9050 2750 9050 2650
Connection ~ 8700 2750
Wire Wire Line
	7500 2250 7400 2250
Wire Wire Line
	7400 2250 7400 2350
Connection ~ 7400 2350
$EndSCHEMATC
