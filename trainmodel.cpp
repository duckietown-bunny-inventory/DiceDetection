#include "opencv2/opencv.hpp"
#include "dicedetection.hpp"
#include "KNearestOcr.h"

using namespace cv;
using namespace std;

int n = 3;

int main(int argc, char** argv)
{
    VideoCapture cap(0);
    if(!cap.isOpened()) 
        return -1;

    KNearestOcr modele;


    namedWindow("debug",1);
    for(int i =1;i <= 6;i++)
    {
        for (int j = 0; j<n;j++) { 
            cout << "learning " << i << " sample " << j << endl;
            Mat lastgood;
            for(;;) {
                Mat number = getNumberEdgeMat(cap);
                if(number.size().height != 0 
                        && number.size().width != 0 
                        && number.size().width < 300 
                        && number.size().height < 300) { 

                    lastgood = number.clone();
                    imshow("debug",lastgood);
                }

                if(waitKey(30) >= 0) {
                    cout << "learning " << i << endl;
                    modele.learn(lastgood,(float) i);
                    break;
                }
            }
        }
    }
    modele.saveTrainingData();

    return 0;
}

