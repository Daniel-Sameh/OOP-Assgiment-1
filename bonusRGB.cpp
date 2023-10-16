// Program: CS213-2023-20221050-20220517-20220388-A1-Part1.cpp
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
char ratio;

void loadRGBImage ();
void interface();
void saveRGB();
char filter;


//RGB filters
void convertRGBToBW();
void invertRGBImage();
void loadRGBMergeImage ();
void mergeRGBImage();
void flipRGBImage(char fl);
void darken_or_lightenRGB(char mode);
void rotateRGBImage(int degree);
void detectRGBEdges();
void mirrorRGBImage(char dir);
void shrinkRGBImage(char ratio);
void cropRGBImage(int x, int y, int l, int w);
//void enlargeRGBImage(int x);


int main()
{
    cout<<"Hello & Welcome to PerPixel ^_-\n";
    cout<<"              Your Perfect Pixel!\n";
    cout<<"=================================\n";
    bool first= true,ok= true;
    loadRGBImage();
    interface();
    while (ok){
        if (first)
            first= false;
        else
            cout<<"Apply another filter or press (s) to save or (0) to exit: ";
        cin>>filter;
        if (filter=='0'){
            ok= false;
        }else if (filter=='1'){
            convertRGBToBW();
        }else if (filter=='2'){
            invertRGBImage();
        }else if (filter=='3'){
            loadRGBMergeImage();
            mergeRGBImage();
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
        }else if (filter=='7'){
            detectRGBEdges();
        }else if (filter=='8'){

        }
        else if(filter=='9'){
            cout<<"for (h)alf,for (t)hird,for (q)uarter";
            cin>>ratio;
            shrinkRGBImage( ratio );
        }
        else if (filter=='a'){
            cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
            cin>>m;
            mirrorRGBImage(m);
        }
        else if(filter=='d'){
            int x,y,l,w;
            cin>>x>>y>>l>>w;
            cropRGBImage( x,  y,  l,  w);
        }
        else if (filter=='s')
            saveRGB();
    }

    return 0;
}



//_________________________________________
void loadRGBImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, imageRGB);
}
void interface(){
    cout<<"Please select a filter to apply or 0 to exit:\n";
    cout<<"     1- Black & White Filter\n";
    cout<<"     2- Invert Filter\n";
    cout<<"     3- Merge Filter\n";
    cout<<"     4- Flip Image\n";
    cout<<"     5- Darken and Lighten Image\n";
    cout<<"     6- Rotate Image\n";
    cout<<"     7- Detect Image Edges\n";
    cout<<"     8- Enlarge Image\n";
    cout<<"     9- Shrink Image\n";
    cout<<"     a- Mirror 1/2 Image\n";
    cout<<"     b- Shuffle Image\n";
    cout<<"     c- Blur Image\n";
    cout<<"     d- Crop Image\n";
    cout<<"     e- Skew Image Right\n";
    cout<<"     f- Skew Image Up\n";
}
//_________________________________________



//_____RGB FILTERS_____________________________
void saveRGB(){
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, imageRGB);
}
//______________________________________________
void convertRGBToBW(){
    for (int x = 1; x < RGB; ++x) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int temp = imageRGB[i][j][0] + imageRGB[i][j][1] + imageRGB[i][j][2];
                if (temp < 384) {
                    imageRGB[i][j][0] = 0;
                    imageRGB[i][j][1] = 0;
                    imageRGB[i][j][2] = 0;
                } else {
                    imageRGB[i][j][0] = 255;
                    imageRGB[i][j][1] = 255;
                    imageRGB[i][j][2] = 255;
                }
            }
        }
    }
}
//_____________________________________________
void invertRGBImage(){
    for (int x = 0; x < RGB; ++x) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                imageRGB[i][j][x] = 255 - imageRGB[i][j][x];
            }
        }
    }
}
//_____________________________________________
void loadRGBMergeImage () {
    char imageFileName[100];


    cout << "Please enter the name of image file to merge with: ";
    cin >> imageFileName;


    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, mergeRGB);
}
void mergeRGBImage() {
    for (int x = 0; x < RGB; ++x) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                imageRGB[i][j][x] = (imageRGB[i][j][x] + mergeRGB[i][j][x])/2;
            }
        }
    }
}
//___________________________________________
void flipRGBImage(char direction) {
    if (direction=='v') {
        for (int x = 0; x < RGB; ++x) {
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {

                    unsigned char temp;
                    temp = imageRGB[i][j][x];  //Storing the original pixel in temporary variable
                    imageRGB[i][j][x] = imageRGB[SIZE - 1 - i][j][x]; //Putting in the original pixel the opposite one from down
                    imageRGB[SIZE - 1 - i][j][x] = temp;
                }
            }
        }
    }else{
        for (int x = 0; x < RGB; ++x) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    unsigned char temp;
                    temp = imageRGB[i][j][x];
                    imageRGB[i][j][x] = imageRGB[i][SIZE - 1 - j][x];
                    imageRGB[i][SIZE - 1 - j][x] = temp;
                }
            }
        }
    }
}
//___________________________________________
void darken_or_lightenRGB(char mode) {
    if (mode == 'd') {
        for (int k = 0; k < RGB; ++k) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    imageRGB[i][j][k] -= (unsigned char) (imageRGB[i][j][k] * 0.5);
                }
            }
        }
    }
    if (mode == 'l') {
        for (int k = 0; k < RGB; ++k) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (imageRGB[i][j][k] == 0) {
                        imageRGB[i][j][k] = 127;
                    } else {
                        imageRGB[i][j][k] = (255 + imageRGB[i][j][k]) / 2;
                    }
                }
            }
        }
    }
}
//___________________________________________
void rotateRGBImage(int degree) {
    // 90-degree rotation is done each time, degree/90 to see how many times we'll rotate the image.
    for (int x = 0; x < degree / 90; ++x) {
        for (int k = 0; k < RGB; ++k) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    unsigned char temp_pixel = imageRGB[i][j][k];
                    imageRGB[i][j][k] = tmpRGB[j][SIZE - i][k];
                    tmpRGB[j][SIZE - i][k] = temp_pixel;
                }
            }
        }
        /*
         x y z           d a x
         a b c    ===>   e b y
         d e f           f c z
         imageRGB[i][j][k] becomes imageRGB[j][SIZE-i][k]
         we are swapping the pixels from image to temporary using temp_pixel.
         */
        for (int k = 0; k < RGB; ++k) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    // moving the rotated pixels from temporary
                    // to image again as it is the one used in the save function
                    imageRGB[i][j][k] = tmpRGB[i][j][k];
                }
            }
        }
    }
}
//___________________________________________
void detectRGBEdges(){
    for (int x = 0; x < RGB; ++x) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                tmpRGB[i][j][x] = imageRGB[i][j][x];
            }
        }
    }
//    for (int x = 0; x < RGB; ++x) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 4; ++k) {
                    int nx = dx[k] + i, ny = dy[k] + j;
                    if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                        int x=0;
                        for (int l = 0; l < RGB; ++l)
                            x=abs(tmpRGB[i][j][l] - tmpRGB[nx][ny][l]);
                        if (x > 40) {
                            imageRGB[nx][ny][0] = 0,imageRGB[nx][ny][1]=0;
                            imageRGB[nx][ny][2]=0;
//                        break;
                        } else if (imageRGB[nx][ny][0]+imageRGB[nx][ny][1]+imageRGB[nx][ny][2] != 0)
                            imageRGB[nx][ny][0] = 255,imageRGB[nx][ny][1]=255,imageRGB[nx][ny][2]=255;
                        else
                            imageRGB[nx][ny][0] =0,imageRGB[nx][ny][1]=0,imageRGB[nx][ny][2]=0;
                    }
                }
            }
        }
//    }

}
//___________________________________________
void shrinkRGBImage(char ratio) {
    if (ratio == 'h') {
        for(int k=0;k<RGB;k++) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    tmpRGB[i / 2][j / 2][k] = imageRGB[i][j][k];
                }
            }
        }
    } else if (ratio == 'q') {
        for(int k=0;k<RGB;k++) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    tmpRGB[i / 4][j / 4][k] = imageRGB[i][j][k];
                }
            }
        }
    } else if (ratio == 't') {
        for(int k=0;k<RGB;k++) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    tmpRGB[i / 3][j / 3][k] = imageRGB[i][j][k];
                }
            }
        }
    }
    for(int k=0;k<RGB;k++) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (((ratio == 'h') && (i < SIZE / 2) && (j < SIZE / 2)) ||
                    ((ratio == 't') && (i < SIZE / 3) && (j < SIZE / 3)) ||
                    ((ratio == 'q') && (i < SIZE / 4) && (j < SIZE / 4)))
                    imageRGB[i][j][k] = tmpRGB[i][j][k];
                else
                    imageRGB[i][j][k] = 255;
            }
        }
    }
}
//___________________________________________
void mirrorRGBImage(char d) {
    if (tolower(d)=='r'){
        for (int x = 0; x < RGB; ++x) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    imageRGB[i][j][x] = imageRGB[i][SIZE - 1 - j][x];
                }
            }
        }
    }else if (tolower(d)=='l'){
        for (int x = 0; x < RGB; ++x) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    imageRGB[i][SIZE - 1 - j][x] = imageRGB[i][j][x];
                }
            }
        }
    }else if (tolower(d)=='u'){
        for (int x = 0; x < RGB; ++x) {
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    imageRGB[SIZE - 1 - i][j][x] = imageRGB[i][j][x];
                }
            }
        }
    }else{
        for (int x = 0; x < RGB; ++x) {
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    imageRGB[i][j][x] = imageRGB[SIZE - 1 - i][j][x];
                }
            }
        }
    }
}
//___________________________________________
void cropRGBImage(int x, int y, int l, int w) {
    for (int k = 0; k < RGB; ++k) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i < x || j < y)
                    imageRGB[i][j][k] = 255;
                else if (i > x + l || j > y + w)
                    imageRGB[i][j][k] = 255;
//            if (i<(x-(l/2))||i>(x+(l/2))||j<(y-(w/2))||j>(y+(w/2)))
//                image[i][j]=255;
            }
        }
    }
}
