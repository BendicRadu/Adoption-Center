#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Domain.h"
#include "Adopt.h"
#include "Repository.h"
#include "Ctrl.h"
#include "UI.h"
#include <sstream>
#include <cstdlib>
#include <crtdbg.h>

int main(int argc, char *argv[])
{

		Dog d{};
		Repository r{"data.txt"};
		AdoptList l{true};
		l.setVector(r.getDogs());
		Controller c{ r, l };

		//c.addDogToRepository("Siberian Husky", "Alexander", 3, 10, "https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/JAA_3538-2.jpg/220px-JAA_3538-2.jpg");
		//c.addDogToRepository("English Bulldog", "Melanie", 2, 10, "http://www.englishbulldogpuppychase.com/english-bulldog-females/images/small/ginger-01.jpg");
		//c.addDogToRepository("Chow chow", "Bagel", 5, 10, "http://primitivedogs.com/wp-content/uploads/2015/11/Chow-Chow-dog.jpg");

		//c.addDogToRepository("Border Collie", "Edward", 4, 50, "http://cdn1-www.dogtime.com/assets/uploads/gallery/border-collie-dog-breed-pictures/4-frisbee.jpg");
		//c.addDogToRepository("German Shepheard", "Hans", 5, 50, "http://www.insidedogsworld.com/wp-content/uploads/2016/03/German-shepherd-dog-hd-wallpapers-beautiful-desktop-images-widescreen-1024x640.jpg");

		//c.addDogToRepository("Corgi", "Tina", 2, 10, "http://dinoanimals.pl/wp-content/uploads/2016/07/Welsh_Corgi_Pembroke-1.jpg");
		//c.addDogToRepository("Shetland Sheepdog", "Peachy", 4, 100, "http://training-dogs.biz/wp-content/uploads/2008/01/Shetland-Sheepdog.jpg");
		//c.addDogToRepository("Shetland Sheepdog", "Beauty", 4, 100, "http://elelur.com/data_images/dog-breeds/shetland-sheepdog/shetland-sheepdog-06.jpg");

		//c.addDogToRepository("Fox terrier", "Skippy", 3, 100, "http://www.tuttogreen.it/wp-content/uploads/2016/09/Fox-terrier-a-pelo-ruvido-500x375.jpg");
	
	QApplication a(argc, argv);
	GUI w{c};
	return a.exec();
	
    _CrtDumpMemoryLeaks();

}
