# capacitance_using_arduino
A capacitance meter is a device that is used to measure capacitance of a capacitor. 

In this project, we will develop two circuits:

a) CIRCUIT1 - to measure capacitance in the range of 1µF to 4700µF
b) CIRCUIT2 - to measure capacitance in the range of 20pF to 1000nF

BASIC PRINCIPLE - The Time Constant (τ)
An unknown capacitor is charged through a known resistor using Arduino pins. The time taken for the
voltage across capacitor to reach 63.2% of the supply voltage gives us the value of τ.
There is a need for two circuits for small and large capacitance values as:
• All the I/O ports in ATmega328P Microcontroller have an internal pull – up resistor and an internal
capacitor connected between the pin and ground.
• The value of internal capacitance ranges from 20-30pF.
• For large values of capacitance of the test capacitor, voltage drop across the internal capacitor is
negligible and almost the entire supply voltage is obtained across the unknown capacitor.
• But for small values of capacitance of the test capacitor, the supply voltage gets divided among the test
and the internal capacitor in direct ratios of their capacitances.
