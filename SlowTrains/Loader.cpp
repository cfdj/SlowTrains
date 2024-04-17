#include "Loader.h"

Loader::Loader(SDL_Renderer* renderer)
{
	std::ifstream trainsFile("Data/Trains.CSV");
	if (trainsFile.is_open()) //To do: Multiple whistles
	{
		char trainLine[256];
		//Removing the header
		trainsFile.getline(trainLine, 256);
		printf(trainLine);
		printf("\n");
		while (trainsFile.getline(trainLine,255)) {
			printf(trainLine);
			printf("\n");
			std::string currentLine = std::string(trainLine);
			int imageSubstringEnd = currentLine.find(',');
			int funnelXEnd = currentLine.find(',',imageSubstringEnd+1);
			int funnelYEnd = currentLine.find(',',funnelXEnd+1);

			std::string funnelXString = currentLine.substr(imageSubstringEnd+1, funnelXEnd);
			std::string funnelYString = currentLine.substr(funnelXEnd+1, funnelYEnd);
			printf("Y position: ");
			printf(funnelYString.c_str());
			printf("\n");
			int funnelX = std::stoi(funnelXString);
			int funnelY = std::stoi(funnelYString);
			std::string path = trainPath;
			path.append(currentLine.substr(0, imageSubstringEnd));
			AnimatedSprite tempTrain = AnimatedSprite(path,width,height,4,1, renderer);
			trains.push_back(tempTrain);
			funnelXposes.push_back(funnelX);
			funnelYposes.push_back(funnelY);
		}
		trainsFile.close();
	}
}

Loader::~Loader()
{
	trains.clear();
	carriges.clear();
	funnelXposes.clear();
	funnelYposes.clear();
}

AnimatedSprite Loader::getTrain(int trainNum)
{
	return trains[trainNum%trains.size()];
}

Sprite Loader::getCarrige(int carrigeNum)
{
	return carriges[carrigeNum % carriges.size()];
}

int Loader::getNumTrains()
{
	return trains.size();
}

int Loader::getFunnelX(int trainNum)
{
	return funnelXposes[trainNum%funnelXposes.size()];
}

int Loader::getFunnelY(int trainNum)
{
	return funnelYposes[trainNum % funnelYposes.size()];;
}
