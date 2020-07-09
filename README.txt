
Copyright (C) 2008, Adrian Raul Mos

Warning:
  I strongly recommend to refactor the code if you use anything from this project.
  No effort has been invested in code readability during development.

System Overview:

  The system includes 3 hardware modules able to wirelessly communicate to each other. 
  Each module includes an ATMega16 microcontroller, an RFM12B wireless transceiver (868MHz ISM band, FSK modulation) and different I/Os.

  A task scheduling algorithm allows a customizable cyclic task execution.

  The wireless communication protocol:
    - the main module coordinates the communication
    - the peripheral modules wait for transmission requests from the main module
    - Hamming encoding is used for bit error detection
