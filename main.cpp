// Program: PerPixel.cpp (Perfect Pixel)
// Purpose: A program that manipulate the given
//          bmp image and ask the user for the
//          desired filters and saves the image at the end.
// Author:  Daniel Sameh 20221050, Michael Reda Moussa 20220517, Youssef Ehab 20220388
// Date:    4 October 2023
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char merge [SIZE][SIZE];
unsigned char tmp[SIZE][SIZE],tmpRGB[SIZE][SIZE][RGB];
unsigned char imageRGB[SIZE][SIZE][RGB];
unsigned char mergeRGB[SIZE][SIZE][RGB];
int dx[]={1,0,-1,0,1,-1,1,-1};
int dy[]={0,1,0,-1,1,-1,-1,1};
char m;

void loadImage ();
void loadMergeImage ();
void saveImage ();
void ConvertBW ();
void invertImage();
void Merge();
void flipImage(char direction);
void darken_or_lighten(char x);
void rotateImage(int a);

int filter;
int main()
{
    cout<<"Hello & Welcome to PerPixel! ^_-\n";
    loadImage();
    cout<<"Please select a filter to apply or 0 to exit:\n";
    cout<<"     1- Black & White Filter\n";
    cout<<"     2- Invert Filter\n";
    cout<<"     3- Merge Filter\n";
    cout<<"     4- Flip Image\n";
    cout<<"     5- Darken and Lighten Image\n";
    cout<<"     6- Rotate Image\n";
    while (cin>>filter){
        if (!filter){
            break;
        }else if (filter==1){
            ConvertBW();
        }else if (filter==2){
            invertImage();
        }else if (filter==3){
            loadMergeImage ();
            Merge();
        }else if (filter==4){
            cout<<"Flip (h)orizontally or (v)ertically ? ";
            char fl;
            cin>>fl;
            flipImage(fl);
        }
        else if(filter==5){
           cout<<"if you want to darken the image press d and if you want to lighten it press l:";
            cin>>m;
            darken_or_lighten(m);
        }
        else if(filter==6){
            cout << "Choose (1) tp rotate 90 degrees or (2) to rotate 180 degrees or (3) to rotate 270 degrees: ";
            int angle = 0;
            cin >> angle;
            rotateImage(angle);
        }
    }
    saveImage();
    return 0;
}

//_________________________________________
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void ConvertBW() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (image[i][j] >= 127) //if pixel tends to white
                image[i][j] = 255;  //Assign it to white (255)
            else
                image[i][j] = 0; //else black (0)
        }
    }
}
//_________________________________________
void invertImage() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}
//_________________________________________
void loadMergeImage () {
    char imageFileName[100];


    cout << "Please enter the name of image file to merge with: ";
    cin >> imageFileName;


    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, merge);
}
void Merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=(image[i][j]+merge[i][j])/2;
        }
    }

}
//_________________________________________
void flipImage(char direction) {
    if (direction=='h') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                char temp;
                temp = image[i][j];  //Storing the original pixel in temporary variable
                image[i][j] = image[SIZE - 1 - i][j]; //Putting in the orginal pixel the opposite one from down
                image[SIZE - 1 - i][j] = temp;

                /*
                 * 00  01  02
                 * 10  11  12
                 * 20  21  22
                 *
                 * 20  21  22
                 * 10  11  12
                 * 00  01  02
                 */

            }
        }
    }else{
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {

                char temp;
                temp = image[i][j];
                image[i][j] = image[i][SIZE - 1 - j];
                image[i][SIZE-1-j] = temp;

            }
        }

        /*
        * 00  01  02
        * 10  11  12
        * 20  21  22
        *
        * 02  01  00
        * 12  11  10
        * 22  21  20
        */

    }
}
//_________________________________________
void rotateImage(int a) {
    for (int x = 0; x < a; ++x) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int temp = image[i][j];
                image[i][j] = tmp[j][SIZE - i];
                tmp[j][SIZE - i] = temp;
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = tmp[i][j];
            }
        }
    }
}
//_________________________________________
void darken_or_lighten(char x) {
    if (x == 'd') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] -= (unsigned char) (image[i][j] * 0.5);
            }
        }
    }
    if (x == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (image[i][j]==0){
                    image[i][j]=127;
                } else{
                    image[i][j]=(255+image[i][j])/2;
                }
            }
        }
    }
}
