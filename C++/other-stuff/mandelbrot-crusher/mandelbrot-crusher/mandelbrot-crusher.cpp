// mandelbrot-crusher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
#pragma comment(lib, "C:\\Users\\teren\\Docs and Files\\Github_Repos\\others\\opencv\\build\\x64\\vc16\\lib\\opencv_world4110.lib")
using namespace std;
using namespace cv;

int speclen;

#define width 3840 // 4K width
#define height 2160 // 4K height
#define threads 16

void hueToRGB(float hue, int& r, int& g, int& b) {
    // ChatGPT code hue to rgb (saving me from a nightmare)
    float s = 1.0f;
    float v = 1.0f;

    float c = v * s;
    float x = c * (1 - abs(fmod(hue / 60.0, 2) - 1));
    float m = v - c;

    float rf = 0, gf = 0, bf = 0;
    if (hue < 60) { rf = c; gf = x; bf = 0; }
    else if (hue < 120) { rf = x; gf = c; bf = 0; }
    else if (hue < 180) { rf = 0; gf = c; bf = x; }
    else if (hue < 240) { rf = 0; gf = x; bf = c; }
    else if (hue < 300) { rf = x; gf = 0; bf = c; }
    else { rf = c; gf = 0; bf = x; }

    r = static_cast<int>((rf + m) * 255);
    g = static_cast<int>((gf + m) * 255);
    b = static_cast<int>((bf + m) * 255);
}

void threader(int id, Mat& img, double x, double y, int max_itr, double zoom) {
    int ctr = 0;
    double aspect = (double)width / height;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (ctr % threads == id) {
                double x0 = x + ((double)j / (double)width * 2.0 - 1.0) * zoom * aspect;
                double y0 = y + ((double)i / (double)height * 2.0 - 1.0) * zoom;
                double cx = 0, cy = 0;
                bool black = true;
                for (int k = 0; k < max_itr; k++) {
					double cxsq = cx * cx;
					double cysq = cy * cy;
                    double nx = cxsq - cysq + x0;
                    double ny = 2 * cx * cy + y0;
                    if (cxsq + cysq > 4.0) {
                        black = false;
                        int r, g, b;
                        hueToRGB(static_cast<float>((int)((k % speclen) / (double)speclen * 360.0) % 360), r, g, b); // Color based on iteration count
                        img.at<Vec3b>(i, j) = Vec3b(b, g, r);
                        break;
                    }
                    cx = nx;
                    cy = ny;
                }
                if (black) {
                    img.at<Vec3b>(i, j) = Vec3b(0, 0, 0); // Set black for points inside the set
                }
            }
            ctr++;
        }
    }
}

Mat genImg(double x, double y, int max_itr, double zoom) {
    Mat res(height, width, CV_8UC3, Scalar(0, 0, 0)); // Create a blank image
    vector<thread> threadsv; // Vector to hold threads
    for (int i = 0; i < threads; i++) {
        threadsv.emplace_back(threader, i, ref(res), x, y, max_itr, zoom);
    }
    for (auto& t : threadsv) {
        t.join(); // Wait for all threads to finish
    }
    return res;
}

int main()
{
    // Create a blank black image (3-channel BGR)
    /*Mat res = genImg(0.0, 0.0, 1000, 1.5);
    imwrite("mandelbrot.png", res);
    imshow("Mandelbrot Set", res);
    waitKey(0);
    destroyAllWindows(); // Close all OpenCV windows*/
    double x, y, zoom;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    cout << "zoom: ";
    cin >> zoom;
    cout << "MaxItr (default 1000): ";
    int maxitr;
    cin >> maxitr;
    cout << "Spectrum length (default 100): ";
    cin >> speclen;
    double scale;
    cout << "Scale for display (reletive to 4k) (default 1): ";
    cin >> scale;
    zoom = 1.0 / zoom;
    int ind = 0;
    std::string path = "frames";
    cout << "File output name: ";
    string path2;
    cin >> path2;
    cout << "The generation is very CPU intensive so your computer may freeze. Intermediate frames before video finishes will be in the frames folder. A popup will appear with the current frame. Please fullscreen it or else it will make your tasknar disappear (IDK why). Are you sure?" << endl;
    system("pause > nul | <nul set /p \"=Are you 100% sure about this? Press any key to continue and close this window to cancel...\"");
    if (!filesystem::exists(path)) {
        filesystem::create_directory(path);
    }
    VideoWriter writer(path2, VideoWriter::fourcc('M', 'J', 'P', 'G'), 60, Size(width, height));
    for (double czoom = 1.0; czoom >= zoom; czoom /= 1.0116194403) {
        cout << ind << endl;
        Mat img = genImg(x, y, maxitr, czoom);
        string filename = "frames/mandelbrot_" + to_string(ind++) + ".png";
        Mat resized;
        //double scale = 0.5; // or whatever fits your screen nicely
        resize(img, resized, Size(), scale, scale, INTER_LINEAR);
        imshow("Preview", resized);
        imwrite(filename, img);
        waitKey(1);
        writer.write(img); // Write the frame to the video file
    }
    writer.release();
    system("start cmd /k echo DONE GENERATING MANDELBROT SET");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file