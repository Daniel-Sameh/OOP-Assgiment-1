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
void interface();
void saveImage ();
void ConvertBW ();
void invertImage();
void Merge();
void flipImage(char direction);
void darken_or_lighten(char x);
void rotateImage(int degree);

char filter;
char type;

//RGB filters
void loadRGBImage ();
void saveRGB();
void convertRGBToBW();
void invertRGBImage();
void loadRGBMergeImage ();
void MergeRGBImage();
void flipRGBImage(char fl);
void darken_or_lightenRGB(char mode);
void rotateRGBImage(int degree);

int main()
{
    cout<<"Hello & Welcome to PerPixel! ^_-\n";
    cout <<"==================================\n";
    cout<<"What kind of images you will enter? (c)oloured or (g)ray: ";
    cin>>type;
    if (type=='g'){
        loadImage();
        interface();
        while (cin>>filter){
            if (filter=='0'||filter=='s'){
                break;
            }else if (filter=='1'){
                ConvertBW();
            }else if (filter=='2'){
                invertImage();
            }else if (filter=='3'){
                loadMergeImage ();
                Merge();
            }else if (filter=='4'){
                cout<<"Flip (h)orizontally or (v)ertically ? ";
                char fl;
                cin>>fl;
                flipImage(fl);
            }
            else if(filter=='5'){
                cout<<"if you want to darken the image press d and if you want to lighten it press l:";
                cin>>m;
                darken_or_lighten(m);
            }else if(filter=='6'){
                cout<<"Rotate (90), (180) or (270) degrees? ";
                int deg;
                cin>>deg;
                rotateImage(deg);
            }
        }
        saveImage();
    }else{
        loadRGBImage();
        interface();
        while (cin>>filter){
            if (filter=='0'){
                break;
            }else if (filter=='1'){
                convertRGBToBW();
            }else if (filter=='2'){
                invertRGBImage();
            }else if (filter=='3'){
                loadRGBMergeImage ();
                MergeRGBImage();
            }else if (filter=='4'){
                cout<<"Flip (h)orizontally or (v)ertically ? ";
                char fl;
                cin>>fl;
                flipRGBImage(fl);
            }
            else if(filter=='5'){
                cout<<"if you want to darken the image press d and if you want to lighten it press l:";
                cin>>m;
                darken_or_lightenRGB(m);
            }else if(filter=='6'){
                cout<<"Rotate (90), (180) or (270) degrees? ";
                int deg;
                cin>>deg;
                rotateRGBImage(deg);
            }
        }
        saveRGB();
    }
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
void interface(){
    cout<<"Please select a filter to apply or 0 to exit:\n";
    cout<<"     1- Black & White Filter\n";
    cout<<"     2- Invert Filter\n";
    cout<<"     3- Merge Filter\n";
    cout<<"     4- Flip Image\n";
    cout<<"     5- Darken and Lighten Image\n";
    cout<<"     6- Rotate Image\n";
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
            image[i][j] = 255 - image[i][j]; // getting the complement of each pixel
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
void rotateImage(int degree) {
    // 90 degree rotation is done each time, degree/90 to see how many times we'll rotate the image.
    for (int x = 0; x < degree / 90; ++x) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int temp_pixel = image[i][j];
                image[i][j] = temporary[j][SIZE - i];
                temporary[j][SIZE - i] = temp_pixel;
            }
        }
        /*
         x y z           d a x
         a b c    ===>   e b y
         d e f           f c z
         image[i][j] becomes image[j][SIZE-i]
         we are swapping the pixels from image to temporary using temp_pixel.
         */
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = temporary[i][j]; // moving the rotated pixels from temporary to image again as it is the one used in the save function
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


//_____RGB FILTERS_____________________________
void loadRGBImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, imageRGB);
}
void saveRGB(){
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, imageRGB);
}
void convertRGBToBW(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            unsigned char temp= imageRGB[i][j][0]+imageRGB[i][j][1]+imageRGB[i][j][2];
//            imageRGB[i][j][0]+=(imageRGB[i][j][1]+imageRGB[i][j][2]);
//            imageRGB[i][j][0]/=3;
//            imageRGB[i][j][1]=0,imageRGB[i][j][2]=0;
            if (temp<(unsigned char )384) {
                imageRGB[i][j][0] = 0;
                imageRGB[i][j][1] = 0;
                imageRGB[i][j][2] = 0;
            }else{
                imageRGB[i][j][0] = 255;
                imageRGB[i][j][1] = 255;
                imageRGB[i][j][2] = 255;
            }
        }
    }
}
