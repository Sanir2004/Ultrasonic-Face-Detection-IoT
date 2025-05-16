# Ultrasonic-Face-Detection-IoT  
"Arduino + OpenCV based real-time face detection and proximity alert system."

## Project Overview  
This project integrates Arduino-based ultrasonic sensor hardware with OpenCV face detection using Python. The system triggers LED and buzzer alerts based on proximity and face presence.

## Features  
- Real-time distance measurement with Arduino ultrasonic sensor  
- Face detection via OpenCV using Haar Cascades  
- Serial communication between Python and Arduino for control signals  
- Alert system with LEDs and buzzer for different proximity levels  

## Usage  
1. Upload the Arduino code to your Arduino board using the Arduino IDE  
2. Connect the Arduino to your PC  
3. Run the Python face detection script  
4. Ensure the serial port in the Python script matches your system's port  

## Requirements  
- Arduino board (e.g., Arduino Uno)  
- Ultrasonic sensor (HC-SR04)  
- LEDs and buzzer  
- Python 3.x with `opencv-python` and `pyserial` packages installed  

## Installation  

```bash
pip install opencv-python pyserial
```text

```
## License
MIT License
## Author
Sanir Singh
>>>>>>> 73775d9 (Initial commit: Arduino + OpenCV IoT system)
