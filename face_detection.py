import cv2
import serial
import time

# Initialize Serial Communication
arduino = serial.Serial('/dev/tty.usbserial-110', 9600, timeout=1)  # Replace with your port
time.sleep(2)  # Allow time for the Arduino to reset

# Initialize Webcam
cap = cv2.VideoCapture(0)  # Change camera index if needed

# Load Haar Cascade for Face Detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

last_signal_time = time.time()
cooldown_time = 1  # seconds cooldown to prevent spamming Arduino

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to capture video")
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 5, minSize=(30, 30))

    if len(faces) > 0:
        if time.time() - last_signal_time > cooldown_time:
            arduino.write(b'1')
            last_signal_time = time.time()
    else:
        if time.time() - last_signal_time > cooldown_time:
            arduino.write(b'0')
            last_signal_time = time.time()

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
        cv2.putText(frame, "Face Detected", (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 0, 0), 2)

    cv2.imshow('Face Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
