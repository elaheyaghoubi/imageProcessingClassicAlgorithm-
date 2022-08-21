#include "Image.hpp"
using namespace std;

int main() {
    int choice;
    cout << "Avalible Filters :" << endl;
    cout << " 1 -> Convolve" << endl;
    cout << " 2 ->  imageThresholding" << endl;
    cout << " 3 -> image bit plane slicing" << endl;
    cout << " 4 -> webcam bit plane slicing" << endl;
    cout << "Choice: "; cin >> choice;
    Image img(choice);
    // img.loadImage("pic.png");
    // img.applyFilter();
    // img.imageReader("test.jpeg");
    return 0;
}
