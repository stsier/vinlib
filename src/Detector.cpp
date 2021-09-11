#include "include/Detector.h"
#include <string>   

using namespace std; 
using namespace cv; 

Detector::Detector(string cascadeFileName) {
    load(cascadeFileName);
}

Detector::~Detector() {

}

void Detector::load(string cascadeFileName) {

    if (!_cascade.load(cascadeFileName))
    {
        cerr << "Cascade could not be loaded" << endl;
        return;
    }
    

}
 
vector<Rect> Detector::process(Mat& img, double scale) {

    // horloge système
    double t = 0;
    // vector qui va contenir les visages détectés
    vector<Rect> objects;
    // matrices des pixels intérmédiaires

    Mat imgTmp, gray, smallImg;
    imgTmp = img;

    //conversion de l'image originale en image monochrome
    cvtColor(imgTmp, gray, COLOR_BGR2GRAY);
    
    double fx = 1 / scale;
    // redimensionner l'image monochrome
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT);

    // calculer l'histogramme des niveaux du signal monochrome
    // et re-écrire l'égalisation dans la même image
    equalizeHist(smallImg, smallImg);

    // commencer compter le temps de détection
    t = (double)getTickCount();
    // détection des objets 
    // (dont la nature - visages - a été définie par un ficher xml)
    // dans une image monochrome 
    _cascade.detectMultiScale(smallImg, 
                            objects, // vector des rectagles contenant les objects détectés 
                            1.1, // facteur de mise l'échelle
                            2, // nombre d'objets voisins minimal 
                            CASCADE_SCALE_IMAGE, // des drapeaux pour optimiser la détection
                            Size(50, 50)); // taille minimal ddu visage à détecter 
    // calcul du temps nécessaire pour la détection des visages
    t = (double)getTickCount() - t;
    cout << "Vinlib found " << objects.size() << " objects in the image" << endl;
    cout << "It took " << t * 1000 / getTickFrequency() << "ms\n";

    return objects;
}

