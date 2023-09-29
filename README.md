# LogitechLEDApp

Customized Logitech light controller application. Allows for light controls beyond what is offered by Logitech Ghub application.

This application was built using C++ and the logitech SDK in Visual Studio. 

The application can be launched via the LED App.exe file. Please also check the Logitech LED Program Presentation.pdf for more details.

The primary source file used for the application can be found in LogitechLEDApp/Src/G910_SAMPLEDlg.cpp file. There you will find the functions responsible for applying light controls to the application.

---DESCRIPTION

While this application works with all standard logitech devices equipped with LEDs, the main focus of the application is to allow for custom light controls for the Logitech G560 Speakers. 
This device has 4 LED zones that are controlled by the application, and other devices with more zonal lighting may not experience the same effects.
The application allows for custom ranges of color selections, various custom made effects, and zonal lighting controls. 


---USAGE

To use this application, plug in a a logitech LED equipped device, preferably the G560 speakers, and use the left most panel to set a primary and secondary color option. 
To apply the effects, click on the set lighting option.
There is a "Na'il's Test" button which will play my own custom animation.
In this panel there is also a slider section that allows for easy color selection which will allow you to view color settings easily.  

In the second panel, you can select which zones you would like to enable or disable, as well as how many loops you would like the animation to play for by entering a count number. This panel also allows you to save and load custom profiles.

