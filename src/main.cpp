#include "main.h"
#include <iostream>

#include "basicStructures.h"
#include "scene.h"
#include "material.h"

using namespace glm;
using namespace std;


int main(int argc, const char* argv[])
{
	// parametres du programme
    string sceneFilename;
    string outputFilename;
    if(argc == 1) {
		// parametres hardcod�s
        string sceneName = "uniformPlaneSphere";
        sceneFilename  = "scenes/"+sceneName+"/"+sceneName+".scn";
        outputFilename = "output/"+sceneName+".png";
    } else {
		// arguments de la ligne de commande
        sceneFilename  = string(argv[1]);
        outputFilename = string(argv[2]);
    }

	cout << "Chargement de la scene... " << sceneFilename << " ." << endl;
	Scene scene(sceneFilename);
	cout << "Rendu de la scene..." << endl;
	scene.render();
	cout << "enregistrement de " << outputFilename << " ..." << endl;
	scene.saveToFile(outputFilename);
	cout << "Termine!" << endl;

	return 0;
}
