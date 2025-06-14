--------------------------------------------------------------------------------

             xlCANdemo - Demoprogram for the 'XL Family Driver Library'

                      Vector Informatik GmbH, Stuttgart

--------------------------------------------------------------------------------

Vector Informatik GmbH
Ingersheimer Stra�e 24
D-70499 Stuttgart

Tel.:  0711-80670-200
Fax.:  0711-80670-555
EMAIL: support@vector.com
WEB:   www.vector.com

--------------------------------------------------------------------------------

xlCANdemo is a small test application for the CAN functionality on Vector devices

For further information look into the 'XL Driver Library - Description.pdf' 
document.

--------------------------------------------------------------------------------

Function:

You can use the xlCANdemo sample to generate and log messages to/from the CAN bus.
This sample utilizes all important functions from the 'XL Family Driver Library'.
While the program is running you can change the options by pressing the appropriate key.

xlCANdemo will operate in CAN-FD mode if it finds a CAN-FD capable device and otherwise
in classical CAN mode.

Usage: xlCANdemo <BaudRate> <ApplicationName> <Identifier>

Options:

  xlCANdemo:
  ----------

  Keyboard commands: 

  't'      Transmit a message
  'b'      Transmit a message burst
  'm'      Transmit a remote message
  'g'      Request chipstate 
  's'      Start/Stop
  'r'      Reset clock
  '+'      Select channel      (up)
  '-'      Select channel      (down)
  'i'      Select transmit Id  (up)
  'I'      Select transmit Id  (down)
  'x'      Toggle extended/standard Id
  'o'      Toggle output mode
  'a'      Toggle timer
  'v'      Toggle logging to screen
  'p'      Show hardware configuration
  'y'      Trigger HW-Sync pulse
  'h'      Help
  'ESC'    Exit

 
To compile a new exe file you will need the import library, header file and the dll.



