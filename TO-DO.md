# To-do List
- Plan out how screen 'ownership' will be managed
- Model the main menu
- Implement Bluetooth
- Implement WiFi
- Implement ArduinoJson Info Transfer
- Connection Keep-Alive Service (When in 'Sleep' mode, ocassionally come out of DeepSleep to keep Connections on)

# Features
- Flash Light (Turns the screen white, should be easy to access)

## SSH Automatization Buttons
Up to 6 buttons that send ssh commands back into the host phone (possible as client only? It doesn't need to receive info back, other than making sure it sent)

# Main Menu Features
## Menu Icons
- 4 big icons for important stuff
- 8 small icons for less important stuff
- One big clock for both battery display and analog time
- Within the big clock, a small label displaying current time
- Below the big clock, current date
- Above the big clock, steps taken
- In the middle of the big clock, a button that opens 

# Display Manager Features
- In charge of adjusting and maintaining brightness
- In charge of managing who gets screen control
- In charge of forwarding rotary switch input

# Battery App Features
- In charge of adjusting watch sleep and power management cycles, as well as to allow or disallow Network Manager Keep Alive

# Network Manager App Features
- In charge of displaying the WiFi Active info bar icon and the Bluetooth Battery Icon
- All network access, http requests, bluetooth communications, and even SSH, should be done through here

# Sound Manager App Features
- In charge of displaying Muted info bar icon
- Manages Volume, sounds should be played through here

# User Health App Features
- In charge of displaying step counter
- Counts steps taken

# System Settings Struct Features
- Primarily act as a construct to avoid class coupling, by storing common options like Enabling/Disabling Network Keep Alive