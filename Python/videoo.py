import cv2
import glob

# 1. Get all image files matching the pattern, sorted alphabetically
image_files = sorted(glob.glob("intruder_*.jpg"))

if not image_files:
    print("No images found.")
    exit()

# 2. Read the first image to get frame dimensions
first_frame = cv2.imread(image_files[0])
if first_frame is None:
    print(f"Could not read {image_files[0]}")
    exit()

height, width, _ = first_frame.shape
fps = 30  # You can change the frame rate

# 3. Create the video writer
fourcc = cv2.VideoWriter_fourcc(*'mp4v')  # For .mp4 output
video_writer = cv2.VideoWriter("output_all_video.mp4", fourcc, fps, (width, height))

# 4. Write each image to the video
for filename in image_files:
    print(filename)
    frame = cv2.imread(filename)
    if frame is None:
        print(f"Warning: Skipping unreadable file {filename}")
        continue
    video_writer.write(frame)

# 5. Release the video writer
video_writer.release()
print("Video created: output_video.mp4")