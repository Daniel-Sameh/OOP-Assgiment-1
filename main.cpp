// Program: PerPixel.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Daniel Sameh 20221050, Michael Rafaat Moussa 2022, Youssef Ehab 20220388
// Date:    4 October 2023
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void ConvertBW ();

void flipImage(char direction);

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

        }else if (filter==3){

        }else if (filter==4){
            cout<<"Flip (h)orizontally or (v)ertically ? ";
            char fl;
            cin>>fl;
            flipImage(fl);
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
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
//_________________________________________
void flipImage(char direction) {
    if (direction=='h') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                char tmp;
                tmp = image[i][j];  //Storing the original pixel in temporary variable
                image[i][j] = image[SIZE - 1 - i][j]; //Putting in the orginal pixel the opposite one from down
                image[SIZE - 1 - i][j] = tmp;

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

                char tmp;
                tmp = image[i][j];
                image[i][j] = image[i][SIZE - 1 - j];
                image[i][SIZE-1-j] = tmp;

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
void Darken() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]-=0.5*image[i][j];
        }
    }
}

void Merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
           image[i][j]=(image[i][j]+merge[i][j])/2;
        }
    }

}
