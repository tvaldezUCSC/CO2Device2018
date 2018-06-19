# CO2Device2018
Files necessary to create a CO2 device based on our specifications

This is a collection of files relevant to our open-source CO2 device. It includes 3 folders:

CO2Test
F3D files
STL files

CO2Test is all the source code for full operation of the chamber. In order to compile and use it, do the following:
- Download and install the Arduino IDE (https://www.arduino.cc/en/Main/Software?)
- Download and install the Teensyduino add-on (https://www.pjrc.com/teensy/td_download.html)
- Within the Arduino IDE, go to "manage libraries" and download the libraries called "Adafruit Unified Sensor" and "Adafruit TSL2561"
- Open, compile, and use CO2Test.ino

F3D files is all the CAD files we created relevant to this project. They are opened in Fusion 360 (https://www.autodesk.com/products/fusion-360/overview).
"Valve 4" is the model of the valve we used in our design. You can turn this file into an STL file yourself, or use the one we provided in the other folder.
"Chamber" is an example model of what a completed device looks like. Nothing needs to be printed off this; it is for reference only.
"Miscellaneous" includes several brackets and miscellaneous models we used to get our prototype to behave as expected. You may find them useful; you may not.

STL files is all the .stl files we 3D-printed in order to create our prototype.
Our valve is comprised of "Door" and "Housing"
"bearing" and "tabs" are two extra parts we created in order to mount our valve. Depending on your application, you may find them useful, or you may not.

Every file in this repository is commpletely free for anyone to use for any purpose at all.
