import cv2
from ultralytics import YOLO

# YOLO model
model = YOLO("yolo11n.pt")

# Laptop camera
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("ERROR: Laptop camera open nahi ho raha.")
    exit()

print("SHIZO Camera Started")
print("Press Q to quit")

while True:
    ret, frame = cap.read()

    if not ret:
        print("ERROR: Camera frame nahi mil raha.")
        break

    # Object detection
    results = model(frame, verbose=False)

    # Draw detections
    annotated_frame = results[0].plot()

    cv2.imshow("SHIZO - Camera", annotated_frame)

    # Q = quit
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()