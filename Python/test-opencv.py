import cv2
import time
import numpy as np
from email.mime.base import MIMEBase
from email import encoders
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import smtplib

def email():
    # --- Email credentials ---

    sender_email = "pengterence5@gmail.com"
    receiver_email = "9292299297@tmomail.net"
    password = "wxqp ugqs jhqr wxeg"  # NOT your regular Gmail password

    # --- Email content ---
    
    subject = "Intruder detector email for the system"
    subject = ""
    body = "An intruder was detected."

    # --- Construct email ---
    msg = MIMEMultipart()
    msg["From"] = sender_email
    msg["To"] = receiver_email
    msg["Subject"] = subject
    msg.attach(MIMEText(body, "plain"))

    # --- Send via Gmail SMTP ---
    with smtplib.SMTP_SSL("smtp.gmail.com", 465) as server:
        server.login(sender_email, password)
        """ filename = "img.jpg"
        with open(filename, "rb") as f:
            part = MIMEBase("application", "octet-stream")
            part.set_payload(f.read())
            encoders.encode_base64(part)
            part.add_header("Content-Disposition", f"attachment; filename={filename}")
            msg.attach(part) """
        f=server.sendmail(sender_email, receiver_email, msg.as_string())
        if not f:
            print(f"FAIL TO SEND EMAIL: {f}")

#time.sleep(10)

# 1. Open the default camera (0 usually means the first webcam)
cap = cv2.VideoCapture(1, cv2.CAP_DSHOW)

if not cap.isOpened():
    print("Cannot open camera")
    exit()

import pygame

pygame.mixer.init()
sound = pygame.mixer.Sound(r"C:\Users\teren\Downloads\__trash__\loud.mp3")  # Load your sound file

time.sleep(1)

ret, limg=cap.read()
limg=limg.astype(np.float32)
#limg=cv2.cvtColor(limg, cv2.COLOR_BGR2GRAY)

ft=False

#for _ in range(10000):
while True:
    # 2. Capture one frame
    ret, frame = cap.read()

    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        exit()
    #sobelx = cv2.Sobel(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY),cv2.CV_64F,1,0,ksize=1)
    
    # Calculation of Sobely
    #sobely = cv2.Sobel(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY),cv2.CV_64F,0,1,ksize=1)
    sobelx = cv2.Sobel(frame,cv2.CV_64F,1,0,ksize=1)
    sobely = cv2.Sobel(frame,cv2.CV_64F,0,1,ksize=1)
    sobel=np.sqrt(sobely*sobely+sobelx*sobelx)
    intt=False
    if np.max(np.abs((frame.astype(np.float32)-limg)))>100:
        if not ft:
            ft=True
        else:
            intt=True
            if not pygame.mixer.get_busy():
                sound.play()
            print("intruder")
            timestamp = time.strftime("%Y%m%d-%H%M%S")
            cv2.imwrite(f"img.jpg", sobel.astype(np.uint8))
            email()
            """ cv2.imwrite(f"intruder_{timestamp}.jpg", frame.astype(np.uint8))
            cv2.imwrite(f"intruder_contour_{timestamp}.jpg", sobel.astype(np.uint8))
            cv2.imwrite(f"intruder_contour_diff_{timestamp}.jpg", np.abs((sobel.astype(np.float32)-limg)).astype(np.uint8)) """
    frame=frame.astype(np.float32)
    diffimg=((sobel-limg)*3)
    diffimg=np.clip(np.abs(diffimg), 0, 255).astype(np.uint8)

    limg=frame
    cv2.putText(sobel, time.strftime("%m/%d/%Y %I:%M:%S %p"), (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 
            1, (255, 255, 255), 2)
    # 3. Show the captured image (optional)
    
    #cv2.imwrite(f"all_contour_{time.strftime("%Y%m%d-%H%M%S")}.jpg", sobel.astype(np.uint8))
    if intt:
        cv2.imshow('Intruder', (sobel*2).astype(np.uint8))
    cv2.waitKey(int(1000/60))  # Wait until a key is pressed

# 4. Save the image to a file
cv2.imwrite('captured_photo.jpg', frame)

# 5. Release the camera and close windows
cap.release()
cv2.destroyAllWindows()
