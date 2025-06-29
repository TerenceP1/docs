import cv2
import numpy as np
from scipy.fft import fft2,ifft2
from scipy.signal import filtfilt,butter
import pyttsx3

engine = pyttsx3.init()


# load initial video

frameRate=60

videoFnm=input("Video path: ")
videoFle=cv2.VideoCapture(videoFnm)
frames=[]
frameRate=videoFle.get(cv2.CAP_PROP_FPS)
while videoFle.isOpened():
    ret, frame = videoFle.read()
 
    # if frame is read correctly ret is True
    if not ret:
        print("Video done loading")
        engine.say("Video done loading")
        engine.runAndWait()
        break
    frames.append(cv2.GaussianBlur(frame, (5, 5), 0))
print(f"Framerate is {frameRate}")
frames = [f.astype(np.float32)/255.0 for f in frames]

# Riesz transform

def riesz(frame):
    r1=fft2(frame)
    #print("R FFT")
    r2=r1
    h, w = frame.shape
    fx = np.fft.fftfreq(w).reshape(1, w)   # shape (1, width)
    fy = np.fft.fftfreq(h).reshape(h, 1)   # shape (height, 1)
    WX, WY = np.meshgrid(fx, fy)
    magnitude = np.sqrt(WX**2 + WY**2)
    magnitude[magnitude == 0] = 1e-16
    H1 = 1j * WX / magnitude
    H2 = 1j * WY / magnitude
    R1 = r1 * H1
    R2 = r2 * H2
    #print("R MLT")
    r1 = np.fft.ifft2(R1).real
    r2 = np.fft.ifft2(R2).real
    #print("R iFFT")
    return (r1,r2)

def iriesz(r1, r2):
    h, w = r1.shape
    fx = np.fft.fftfreq(w).reshape(1, w)
    fy = np.fft.fftfreq(h).reshape(h, 1)
    WX, WY = np.meshgrid(fx, fy)
    magnitude = np.sqrt(WX**2 + WY**2)
    magnitude[magnitude == 0] = 1e-16  # avoid div by zero

    H1_conj = -1j * WX / magnitude
    H2_conj = -1j * WY / magnitude

    R1 = fft2(r1)
    R2 = fft2(r2)
    #print("iR FFT")

    F_hat = R1 * H1_conj + R2 * H2_conj
    #print("iR MLT")
    f_reconstructed = ifft2(F_hat).real
    #print("iR iFFT")
    return f_reconstructed

# Motion amplify

def butter_bandpass(lowcut, highcut, fs, order=4):
    nyq = 0.5 * fs  # Nyquist frequency
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def bandpass_filter_video_vectorized(video, lowcut, highcut, fs, order=4):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    frames, height, width = video.shape
    reshaped = video.reshape(frames, -1)  # shape (frames, height*width)
    filtered_reshaped = filtfilt(b, a, reshaped, axis=0)
    filtered = filtered_reshaped.reshape(frames, height, width)
    return filtered

def mAmp(frames):
    amps=[]
    phases=[]
    rots=[]
    ind=0
    print("-Doing Riesz transform")
    engine.say("Doing Riesz transform")
    engine.runAndWait()
    print("-Reisz frame number 0 out of "+str(len(frames)),end="",flush=True)
    for frame in frames:
        R=riesz(frame)
        amps.append(np.sqrt(frame**2+R[0]**2+R[1]**2))
        phases.append(np.arccos(frame/(amps[-1]+1e-8)))
        rots.append(np.arctan2(R[1],R[0]))
        if ind==len(frames):
            break
        print("\x1b["+str(len(str(ind)+" out of "+str(len(frames))))+"D"+str(ind+1)+" out of "+str(len(frames)),end="",flush=True)
        ind+=1
    
    print("\n-Riesz complete!\n-Multiplying...")
    engine.say("Riesz complete! Multiplying")
    engine.runAndWait()
    phases=np.array(phases)
    print("--Calculating bandpass")
    engine.say("Calculating bandpass")
    engine.runAndWait()
    phases=phases+bandpass_filter_video_vectorized(phases,0.3,2,frameRate)*10
    amps=np.array(amps)
    rots=np.array(rots)
    print("--Calculating original image...")
    engine.say("Calculating original image")
    engine.runAndWait()
    nf=amps*np.cos(phases)
    print("--Calculating new R1 coefficient...")
    engine.say("Calculating new R1 coefficient")
    engine.runAndWait()
    nr1=amps*np.sin(phases)*np.cos(rots)
    print("--Calculating new R2 coefficient...")
    engine.say("Calculating new R2 coefficient")
    engine.runAndWait()
    nr2=amps*np.sin(phases)*np.sin(rots)
    out = []
    print("-Done multiplying\n-Beginning inverse Riesz transform")
    engine.say("Done multiplying! Beginning inverse Riesz transform")
    engine.runAndWait()
    print("-Inverse Reisz frame number 0 out of "+str(len(frames)),end="",flush=True)
    ind=0

    for t in range(len(frames)):
        out.append(np.clip((iriesz(nr1[t], nr2[t])+0.5)*255, 0, 255).astype(np.uint8))
        if ind==len(frames):
            break
        print("\x1b["+str(len(str(ind)+" out of "+str(len(frames))))+"D"+str(ind+1)+" out of "+str(len(frames)),end="",flush=True)
        ind+=1
    return out
def mAmp_luminance(frames_bgr):
    frames_bgr = np.array(frames_bgr).astype(np.float32) / 255.0
    frames_yuv = np.array([cv2.cvtColor(f, cv2.COLOR_BGR2YUV) for f in frames_bgr])
    Y = frames_yuv[..., 0]
    U = frames_yuv[..., 1]
    V = frames_yuv[..., 2]

    # Amplify only luminance
    Y_amp = mAmp(Y)

    # Recombine channels
    out_color = []
    for i in range(len(frames_bgr)):
        yuv = np.stack([Y_amp[i], U[i], V[i]], axis=-1)
        bgr = cv2.cvtColor(yuv.astype(np.float32), cv2.COLOR_YUV2BGR)
        bgr = np.clip(bgr * 255, 0, 255).astype(np.uint8)
        out_color.append(bgr)

    return out_color
def mAmp_color(frames):
    # frames shape: (num_frames, height, width, 3), dtype float32 normalized [0..1] ideally
    
    # Separate channels
    frames = np.array(frames)
    R_ch = frames[..., 0]
    G_ch = frames[..., 1]
    B_ch = frames[..., 2]
    
    # Amplify each channel separately
    print("Calculating red channel")
    engine.say("Calculating red channel")
    engine.runAndWait()
    R_out = mAmp(R_ch)
    print("\nCalculating green channel")
    engine.say("Calculating green channel")
    engine.runAndWait()
    G_out = mAmp(G_ch)
    print("\nCalculating blue channel")
    engine.say("Calculating blue channel")
    engine.runAndWait()
    B_out = mAmp(B_ch)
    
    # Stack back channels
    out_color = []
    for i in range(len(frames)):
        # Stack channels along last dim and clip
        merged = np.stack([R_out[i], G_out[i], B_out[i]], axis=-1)
        merged = np.clip(merged, 0, 255).astype(np.uint8)
        out_color.append(merged)
        
    return out_color
videoO=mAmp_color(frames)
fourcc = cv2.VideoWriter_fourcc(*'mp4v')  # or 'XVID' for .avi
height, width,_ = frames[0].shape
out = cv2.VideoWriter("res.mp4", fourcc, frameRate, (width,height))


ind=0
print("\nVideo write frame number 0 out of "+str(len(frames)),end="",flush=True)
for frame in videoO:
    #frame_bgr = cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR)
    out.write(frame)
    if ind==len(frames):
        break
    print("\x1b["+str(len(str(ind)+" out of "+str(len(frames))))+"D"+str(ind+1)+" out of "+str(len(frames)),end="",flush=True)
    ind+=1

out.release()

engine.say("Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. Your video is done. ")
engine.runAndWait()