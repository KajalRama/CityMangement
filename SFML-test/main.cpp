#include <SFML/Graphics.hpp>
#include <iostream>
#include "ImageButton.h"
#include "TextButton.h"
#include <vector>
#include "Tile.h"
#include "Transit.h"
#include "Security.h"
#include "Jobs.h"
#include "Environmental.h"
#include "housing.h"

#include <sstream>

using namespace std;
struct cityStatsStruct {					 //structure to hold city stats
	int population;
	int safety;
	int employment;
	int pollution;
	int income;
	int accessibility;
	int transportation;
	long unsigned money;
	int year;
};

bool checkWin(cityStatsStruct myCity, cityStatsStruct cityWin);        //function to check if player won the game

int main()
{
	//constants for adjusting building costs and starting money
	const int STARTING_MONEY = 25000;                                             //starting money that player will be given form the beginning

	const int LOW_HOUSE_COST = 1250;                                              //cost of a low house construction
	const int MID_HOUSE_COST = 2000;												//cost of a mid house construction
	const int HIGH_HOUSE_COST = 2500;												//cost of a high house construction

	const int BUS_STATION_COST = 6000;												//cost of a bus station construction
	const int TRAIN_STATION_COST = 8000;											//cost of a train station construction					
	const int SUBWAY_STATION_COST = 14000;                                          //cost of a subway station construction

	const int POLICE_STATION_COST = 4000;											//cost of a police station construction
	const int FIRE_STATION_COST = 6000;												//cost of a fire station construction
	const int HOSPITAL_COST = 7000;													//cost of a hospital construction

	const int MALL_COST = 13000;                                                    //cost of a mall construction
	const int OFFICE_COST = 7000;												    //cost of a office construction
	const int FACTORY_COST = 23000;													//cost of a factory construction

	const int PARK_COST = 2000;														//cost to build a park
	const int RECYCLE_COST = 7000;													//cost to build a recycling plant
	const int WATER_COST = 6000;                                                   //cost to build a water treatment plant
	
	//upgrade costs
	const int POPULATION_UPGRADE_COST = 500;                                       //cost to upgrade the population
	const int POLLUTION_UPGRADE_COST = 700;										   //cost to upgrade the pollution
	const int EMPLOYMENT_UPGRADE_COST = 800;									   //cost to upgrade the employment
	const int INCOME_UPGRADE_COST = 700;										  //cost to upgrade the income
	const int SAFETY_UPGRADE_COST = 600;										  //cost to upgrade the safety
	const int TRANSIT_UPGRADE_COST = 500;										   //cost to upgrade the transportation
	const int ACCESSIBILITY_UPGRADE_COST = 500;										//cost to upgrade the accessibility

	//bool test = true; // whats this for? can we remove?

	bool mouseRelease = true;											// bool to keep track of mouse clicks - prevents button reuse before mouse button release


	
	//font for city stats
	sf::Font font;
	if (!font.loadFromFile("font/contb.ttf"))//http://www.dafont.com/continuum.font    //this will load the fonts 
	{
		std::cerr << "Could not find contb.ttf font." << std::endl;
	}
	// init City Stats
	cityStatsStruct myCity, cityWin;         //structure to store the current stats and requirement stats
	myCity.accessibility = 0;
	myCity.employment = 0;
	myCity.income = 0;
	myCity.pollution = 0;
	myCity.population = 0;                //This will hold the status of the current stats 
	myCity.safety = 0;
	myCity.transportation = 0;
	myCity.money = STARTING_MONEY;
	myCity.year = 2017;

	cityWin.accessibility = 50;
	cityWin.employment = 100;
	cityWin.pollution = 200;        
	cityWin.population = 100;             //this will hold the actual requirement for each stats in order to win the game
	cityWin.safety = 50;
	cityWin.transportation = 50;
	cityWin.year = 2030;

	//constants
	const int BUTTON_SIZE = 50;							//button size
	const int FIRST_BUTTON_X = 10;						//x position of the first button
	const int FIRST_BUTTON_Y = 10;						//Y position of the first button
	const float WINDOW_WIDTH = 1200;					// window width
	const float WINDOW_HEIGHT = 800;					// window height
	stringstream msg;									//this will store the message that needs to be desplayed on the screen
	string msg1 = "\n";										//this will also store the message that needs to be desplayed on the screen
	msg << "Each buttons \nhas sub buttons";		// store the message to show the discription of the game

	// Background music of the game

	sf::SoundBuffer backgroundSoundBuffer;
	if (!backgroundSoundBuffer.loadFromFile("awesomeness.wav")) {      //load the sound file
		std::cout << "cannot open audio";
		sf::sleep(sf::seconds(5));
		return EXIT_FAILURE;
	}
	sf::Sound backgroundSound(backgroundSoundBuffer);
	backgroundSound.play(); // play background music

	//this will be played whenever any type of construction is done in the game (housing, mall, offices)

	sf::SoundBuffer constructionSoundBuffer;
	if (!constructionSoundBuffer.loadFromFile("Construction.wav")) {    //load the sound file
		std::cout << "cannot open audio";
		sf::sleep(sf::seconds(5));
		return EXIT_FAILURE;
	}
	sf::Sound constructionSound(constructionSoundBuffer);

	//this sound file will be played when player adds (subway station, train station, bus station) 

	sf::SoundBuffer hornSoundBuffer;
	if (!hornSoundBuffer.loadFromFile("TrainHorn.wav")) {             //load the sound file
		std::cout << "cannot open audio";
		sf::sleep(sf::seconds(5));
		return EXIT_FAILURE;
	}
	sf::Sound hornSound(hornSoundBuffer);

	//this sound file will be played when player adds (hospital, fire station, police station) 


	sf::SoundBuffer emergeSoundBuffer;
	if (!emergeSoundBuffer.loadFromFile("emergencySiren.wav")) {      //load the sound file
		std::cout << "cannot open audio";
		sf::sleep(sf::seconds(5));
		return EXIT_FAILURE;
	}
	sf::Sound emergeSound(emergeSoundBuffer);

	//	//this sound file will be played when player adds water treatment plant


	sf::SoundBuffer waterSoundBuffer;
	if (!waterSoundBuffer.loadFromFile("Water.wav")) {    //load the sound file
		std::cout << "cannot open audio";
	}
	sf::Sound waterSound(waterSoundBuffer);

	//	//this sound file will be played when player adds factory to the game


	sf::SoundBuffer factorySoundBuffer;
	if (!factorySoundBuffer.loadFromFile("Factory.wav")) {  //load the sound file
		std::cout << "cannot open audio";
	}
	sf::Sound factorySound(factorySoundBuffer);

	//this sound file will be played when player adds park in the game


	sf::SoundBuffer parkSoundBuffer;
	if (!parkSoundBuffer.loadFromFile("Park.wav")) {    //load the sound file
		std::cout << "cannot open audio";
	}
	sf::Sound parkSound(parkSoundBuffer);

	//this sound file will be played when player adds recycle plant in the game


	sf::SoundBuffer recycleSoundBuffer;
	if (!recycleSoundBuffer.loadFromFile("Recycle.wav")) {    //load the sound file
		std::cout << "cannot open audio";
	}
	sf::Sound recycleSound(recycleSoundBuffer);


	sf::RectangleShape drawingArea(sf::Vector2f(WINDOW_WIDTH - 200 - 5, WINDOW_HEIGHT - 120));		// this will create actual drawing area
	drawingArea.setPosition(200, 5);																// set the position of the drawing area
	drawingArea.setFillColor(sf::Color::White);														// this will set the drawing area color to white

	sf::Texture emptyTileTexture;																	//this will set empty tile background texture to the game 
	if (!emptyTileTexture.loadFromFile("emptyTile.png")) {
		cout << "Error Loading emptyTile.png" << endl;
	}
	emptyTileTexture.setRepeated(true);

	sf::Sprite emptyTileSprite;
	emptyTileSprite.setTexture(emptyTileTexture);
	emptyTileSprite.setTextureRect(sf::IntRect(0, 0, drawingArea.getSize().x, drawingArea.getSize().y));
	emptyTileSprite.setScale(40 / emptyTileTexture.getSize().x, 40 / emptyTileTexture.getSize().y);
	emptyTileSprite.setPosition(drawingArea.getPosition().x, drawingArea.getPosition().y);
	emptyTileSprite.setTextureRect(sf::IntRect(drawingArea.getPosition().x, drawingArea.getPosition().y, drawingArea.getSize().x, drawingArea.getSize().y));
	
	sf::RenderWindow window(sf::VideoMode(1200, 850), "Sustainable City!");              //creates the actual window of the game

	//buttons for the 5 main sections
	ImageButton houseSec("houseSectionIcon.png", BUTTON_SIZE, FIRST_BUTTON_X, FIRST_BUTTON_Y);
	ImageButton transitSec("trasitSectionIcon.png", BUTTON_SIZE, houseSec.getShapeX() + (BUTTON_SIZE / 2), houseSec.getShapeY() + BUTTON_SIZE);
	ImageButton securitySec("securitySectionIcon.png", BUTTON_SIZE, houseSec.getShapeX() + BUTTON_SIZE, houseSec.getShapeY());
	ImageButton commerceSec("commerceSectionIcon.png", BUTTON_SIZE, securitySec.getShapeX() + BUTTON_SIZE, houseSec.getShapeY());
	ImageButton enviormentSec("enviormentSectionIcon.png", BUTTON_SIZE, transitSec.getShapeX() + BUTTON_SIZE, transitSec.getShapeY());

	//sub buttons
	//housing
	ImageButton lowHouse("lowHouseIcon.png", BUTTON_SIZE, FIRST_BUTTON_X, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	ImageButton midHouse("midHouseIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + BUTTON_SIZE, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5 + BUTTON_SIZE);
	ImageButton highHouse("highHouseIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + (BUTTON_SIZE * 2), (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	//transit
	ImageButton busStation("busStationIcon.png", BUTTON_SIZE, FIRST_BUTTON_X, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	ImageButton trainStation("trainStationIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + BUTTON_SIZE, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5 + BUTTON_SIZE);
	ImageButton subwaySation("subwayStationIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + (BUTTON_SIZE * 2), (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	//security
	ImageButton policeStation("policeStationIcon.png", BUTTON_SIZE, FIRST_BUTTON_X, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	ImageButton fireStation("fireStationIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + BUTTON_SIZE, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5 + BUTTON_SIZE);
	ImageButton hospital("hospitalIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + (BUTTON_SIZE * 2), (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	//commerce
	ImageButton mall("mallIcon.png", BUTTON_SIZE, FIRST_BUTTON_X, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	ImageButton office("officeIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + BUTTON_SIZE, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5 + BUTTON_SIZE);
	ImageButton factory("factoryIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + (BUTTON_SIZE * 2), (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	//enviorment
	ImageButton park("parkIcon.png", BUTTON_SIZE, FIRST_BUTTON_X, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);
	ImageButton recyclePlant("recyclePlantIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + BUTTON_SIZE, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5 + BUTTON_SIZE);
	ImageButton waterTreatment("waterTreatmentIcon.png", BUTTON_SIZE, FIRST_BUTTON_X + (BUTTON_SIZE * 2), (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5);

	//pointers that point to the active subsection and initialize them so the UI appears properly when first loaded
	vector<ImageButton*> subButtons(3);
	subButtons.at(0) = &lowHouse;
	subButtons.at(1) = &midHouse;
	subButtons.at(2) = &highHouse;

	ImageButton *mainSelection = NULL; //this needs to be set to something, doesnt actually matter what
	ImageButton *subSelection = NULL; //same as above

									  //textButtons
	TextButton DiscriptionButton(msg.str(), 20, sf::Color::White, FIRST_BUTTON_X, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5 + (BUTTON_SIZE * 2));       // this will setup discription button
	TextButton UpgradeButton("Upgrade info\nper tile", 20, sf::Color::White, FIRST_BUTTON_X, 600);       // this will setup discription button
	TextButton CityStatus("Shows the city Status", 20, sf::Color::White, (FIRST_BUTTON_X + (3 * BUTTON_SIZE)), 700);
	TextButton RequireButton("City Requirement", 20, sf::Color::White, (FIRST_BUTTON_X + (9 * BUTTON_SIZE)), 700);
	TextButton EndButton("End Game", 20, sf::Color::White, 1000, 700);
	TextButton turnButton("Next Year", 20, sf::Color::White, 800, 700);

	//upgrade buttons vector
	//this will create the upgrade button of the game and provides all the cost information
	vector<TextButton*> upgradeOptions(4);
	stringstream upgradeMessage;
	upgradeMessage << "Upgrade Transportation\nCost: " << TRANSIT_UPGRADE_COST;
	TextButton upgradeTransportation(upgradeMessage.str(), 12, sf::Color::White, FIRST_BUTTON_X, 612);
	upgradeMessage.str("");
	upgradeMessage << "Upgrade Population\nCOST: " << POPULATION_UPGRADE_COST;
	TextButton upgradeHousing(upgradeMessage.str(), 12, sf::Color::White, FIRST_BUTTON_X, 612);
	upgradeMessage.str("");
	upgradeMessage << "Upgrade Polution\nCOST: " << POLLUTION_UPGRADE_COST;
	TextButton upgradePollution(upgradeMessage.str(), 12, sf::Color::White, FIRST_BUTTON_X, 612);
	upgradeMessage.str("");
	upgradeMessage << "Upgrade Security\nCOST: " << SAFETY_UPGRADE_COST;
	TextButton upgradeSecurity(upgradeMessage.str(), 12, sf::Color::White, FIRST_BUTTON_X, 612);
	upgradeMessage.str("");
	upgradeMessage << "Upgrade Employment\nCOST: " << EMPLOYMENT_UPGRADE_COST;
	TextButton upgradeEmployment(upgradeMessage.str(), 12, sf::Color::White, FIRST_BUTTON_X, 612);
	upgradeMessage.str("");
	upgradeMessage << "Upgrade Income\nCOST: " << INCOME_UPGRADE_COST;
	TextButton upgradeIncome(upgradeMessage.str(), 12, sf::Color::White, FIRST_BUTTON_X, 612);
	upgradeMessage.str("");
	upgradeMessage << "Upgrade Accessibility\nCOST: " << ACCESSIBILITY_UPGRADE_COST;
	TextButton upgradeAccessibility(upgradeMessage.str(), 12, sf::Color::White, FIRST_BUTTON_X, 612);

	//text for city stats;
	stringstream cityStatsString;

	cityStatsString <<"Current Year: "<<myCity.year << "\nPopulation: " << myCity.population << "\nEmployment: " << myCity.employment << "\nSafety: " << myCity.safety <<
		"\nPollution: " << myCity.pollution << "\nIncome: " << myCity.income << "\nTransportation: " << myCity.transportation <<
		"\nAccessibility: " << myCity.accessibility << "\nMoney: " << myCity.money;        //this will display the current status of the game 

	//text for city requirements // seperate for color changing on meeting goals
	stringstream cityRequirementString;
	stringstream winYear;
	stringstream winPopulation;
	stringstream winEmployment;
	stringstream winSafety;
	stringstream winPollution;
	stringstream winTransportation;
	stringstream winAccessibility;

	//this will display the city requirement to win the game

	winYear << "Complete by: " << cityWin.year;
	winPopulation << "Population: >= " << cityWin.population;
	winEmployment << "Employment: >= " << cityWin.employment;
	winSafety << "Safety: >= " << cityWin.safety;
	winPollution << "Pollution: < " << cityWin.pollution;
	winTransportation << "Transportation: >=" << cityWin.transportation;
	winAccessibility << "Accessibility: >= " << cityWin.accessibility;

	// font properties for the city stats of the game

	sf::Text cityStatsText;
	cityStatsText.setFont(font);
	cityStatsText.setCharacterSize(12);
	cityStatsText.setFillColor(sf::Color::Cyan);
	cityStatsText.setString(cityStatsString.str());
	cityStatsText.setPosition(sf::Vector2f(200, 725));


							// font properties for the city requirement of the game


	sf::Text winYearText;
	winYearText.setFont(font);
	winYearText.setCharacterSize(12);
	winYearText.setFillColor(sf::Color::Red);
	winYearText.setString(winYear.str());
	winYearText.setPosition(sf::Vector2f(500, 735));

	sf::Text winPopulationText;
	winPopulationText.setFont(font);
	winPopulationText.setCharacterSize(12);
	winPopulationText.setFillColor(sf::Color::Red);
	winPopulationText.setString(winPopulation.str());
	winPopulationText.setPosition(sf::Vector2f(500, 745));

	sf::Text winEmploymentText;
	winEmploymentText.setFont(font);
	winEmploymentText.setCharacterSize(12);
	winEmploymentText.setFillColor(sf::Color::Red);
	winEmploymentText.setString(winEmployment.str());
	winEmploymentText.setPosition(sf::Vector2f(500, 755));

	sf::Text winSafetyText;
	winSafetyText.setFont(font);
	winSafetyText.setCharacterSize(12);
	winSafetyText.setFillColor(sf::Color::Red);
	winSafetyText.setString(winSafety.str());
	winSafetyText.setPosition(sf::Vector2f(500, 765));

	sf::Text winPollutionText;
	winPollutionText.setFont(font);
	winPollutionText.setCharacterSize(12);
	winPollutionText.setFillColor(sf::Color::Red);
	winPollutionText.setString(winPollution.str());
	winPollutionText.setPosition(sf::Vector2f(500, 775));

	sf::Text winTransportationText;
	winTransportationText.setFont(font);
	winTransportationText.setCharacterSize(12);
	winTransportationText.setFillColor(sf::Color::Red);
	winTransportationText.setString(winTransportation.str());
	winTransportationText.setPosition(sf::Vector2f(500, 785));

	sf::Text winAccessibilityText;
	winAccessibilityText.setFont(font);
	winAccessibilityText.setCharacterSize(12);
	winAccessibilityText.setFillColor(sf::Color::Red);
	winAccessibilityText.setString(winAccessibility.str());
	winAccessibilityText.setPosition(sf::Vector2f(500, 795));
	
	sf::Text winText;
	winText.setString("You Win!");
	winText.setFont(font);
	winText.setCharacterSize(40);
	winText.setFillColor(sf::Color::Cyan);
	winText.setPosition(sf::Vector2f(400, 600));

	sf::Text loseText;
	loseText.setString("You Lose!");
	loseText.setFont(font);
	loseText.setCharacterSize(40);
	loseText.setFillColor(sf::Color::Red);
	loseText.setPosition(sf::Vector2f(400, 600));


	//vector for adding buildings to the drawing grid
	vector<Tile*> gameTiles;
	const int rows = 30, cols = 20; // constants for tracking array
	Tile* gridArray[rows][cols]; // array to keep track of spots with buildings
								 // initialize tracking grid
	Tile* selectedTile = NULL;
	for (int i = 0; i <= rows; i++) {
		for (int j = 0; j <= cols; j++) {
			gridArray[i][j] = NULL;
		}
	}

	//fill in empty tiles
	for (int i = drawingArea.getPosition().x; i < 1200; i += 40) {
		for (int j = drawingArea.getPosition().y; j < drawingArea.getSize().y; j += 40) {
			gameTiles.push_back(new Tile(40, 40, i, j, "emptyTile.png", "empty",0));
		}
	}


	while (window.isOpen())					// game  main loop
	{
		sf::Event event;
		while (window.pollEvent(event))       //if end button or close button is pressed then close the window
		{
			if ((event.type == sf::Event::Closed) || (EndButton.contains(event.mouseButton.x, event.mouseButton.y)))
				window.close();
		}
		if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {
			mouseRelease = true; // set to true to allow the next button click after a mouse button release
		}
		
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ) { //if player clicks something
			
			if (turnButton.contains(event.mouseButton.x, event.mouseButton.y) && mouseRelease == true) {         // Next Year
				mouseRelease = false;
				myCity.year += 1;														// update current year
				myCity.money += 5000 + 1000 * myCity.income + 100 * myCity.employment; // add funds based on income generating tiles
			}
			if (houseSec.contains(event.mouseButton.x, event.mouseButton.y)) {			//if player clicked the housing section
				if (mainSelection != NULL) {											//remove prior active if it isnt NULL (program will crash if it is)
					mainSelection->unmakeActive();

					if (subSelection != NULL) {
						subSelection->unmakeActive();										//since the main catergory was changed, unset the sub selection
						subSelection = NULL;
					}
				}
				mainSelection = &houseSec;								 //point to new active
				mainSelection->makeActive();					//reset active status

					//set sub buttons
				subButtons.at(0) = &lowHouse;              //sub buttons address stored in the vector
				subButtons.at(1) = &midHouse;
				subButtons.at(2) = &highHouse;
				msg.str("");
				msg << "Choose\n1.Small house\nCost: "<< LOW_HOUSE_COST << "\n2.Mid house\nCost: " << MID_HOUSE_COST << "\n3.High house\nCost: " << HIGH_HOUSE_COST;            //this will rpint the message with cost information
			}
			else if (transitSec.contains(event.mouseButton.x, event.mouseButton.y)) {							//these follow the same pattern so I wont comment them all
				if (mainSelection != NULL) {
					mainSelection->unmakeActive();

					if (subSelection != NULL) {
						subSelection->unmakeActive();
						subSelection = NULL;
					}
				}
				mainSelection = &transitSec;               //if transit button is clicked make it active
				mainSelection->makeActive();

				subButtons.at(0) = &busStation;              //sub buttons address is stored in the vector
				subButtons.at(1) = &trainStation;
				subButtons.at(2) = &subwaySation;
				msg.str("");
				msg << "Choose\n1.Bus\nCost: " << BUS_STATION_COST << "\n2.Subway\nCost: " << TRAIN_STATION_COST << "\n3.Train\nCost: " <<SUBWAY_STATION_COST;
				
			}
			else if (securitySec.contains(event.mouseButton.x, event.mouseButton.y)) {
				if (mainSelection != NULL) {
					mainSelection->unmakeActive();

					if (subSelection != NULL) {
						subSelection->unmakeActive();
						subSelection = NULL;
					}
				}
				mainSelection = &securitySec;              //if security button is clicked make it active
				mainSelection->makeActive();

				subButtons.at(0) = &policeStation;           //sub buttons address stored in the vector
				subButtons.at(1) = &fireStation;
				subButtons.at(2) = &hospital;
				msg.str("");
				msg << "Choose\n1.Police station\nCost: " << POLICE_STATION_COST << "\n2.Hospital\nCost: " << HOSPITAL_COST << "\n3.Fire station\nCost: " << FIRE_STATION_COST;
				
			}
			else if (commerceSec.contains(event.mouseButton.x, event.mouseButton.y)) {
				if (mainSelection != NULL) {
					mainSelection->unmakeActive();

					if (subSelection != NULL) {
						subSelection->unmakeActive();
						subSelection = NULL;
					}
				}
				mainSelection = &commerceSec;                 //if commercial button is clicked make it active
				mainSelection->makeActive();

				subButtons.at(0) = &mall;
				subButtons.at(1) = &office;										 //sub buttons address stored in the vector
				subButtons.at(2) = &factory;
				msg.str("");
				msg << "Choose\n1.Mall\nCost: " << MALL_COST << "\n2.Factory\nCost: " << FACTORY_COST << "\n3.Office\nCost: " << OFFICE_COST;
				
			}
			else if (enviormentSec.contains(event.mouseButton.x, event.mouseButton.y)) {
				if (mainSelection != NULL) {
					mainSelection->unmakeActive();

					if (subSelection != NULL) {
						subSelection->unmakeActive();
						subSelection = NULL;
					}
				}
				mainSelection = &enviormentSec;                    //if transit environmental button is clicked make it active
				mainSelection->makeActive();

				subButtons.at(0) = &park;							 
				subButtons.at(1) = &recyclePlant;				 //sub buttons address stored in the vector
				subButtons.at(2) = &waterTreatment;					
				msg.str("");
				msg << "Choose\n1.Park\nCost: " << PARK_COST << "\n2.Water treatment\nCost: " << WATER_COST << "\n3.Recycle plant\nCost: " << RECYCLE_COST;           //print the message with sub buttons cost				
				
			}
			else if (subButtons.at(0)->contains(event.mouseButton.x, event.mouseButton.y)) {					//a sub button was clicked, this follows a slightly diferent set of instructions from the main buttons
				if (subSelection != NULL) {							//make the previous active inactive
					subSelection->unmakeActive();
				}
				subSelection = subButtons.at(0);			//select the clicked sub button
				subSelection->makeActive();						 //make the sub button active
			}
			else if (subButtons.at(1)->contains(event.mouseButton.x, event.mouseButton.y)) {				//a sub button was clicked, this follows a slightly diferent set of instructions from the main buttons			
				if (subSelection != NULL) {							
					subSelection->unmakeActive();						//make the previous active inactive
				}
				subSelection = subButtons.at(1);			//select the clicked sub button
				subSelection->makeActive();					//make the sub button active
			}
			else if (subButtons.at(2)->contains(event.mouseButton.x, event.mouseButton.y)) {				//a sub button was clicked, this follows a slightly diferent set of instructions from the main buttons
				if (subSelection != NULL) {
					subSelection->unmakeActive();								//make the previous active inactive
				}
				subSelection = subButtons.at(2);								//select the clicked sub button
				subSelection->makeActive();										//make the sub button active
			}


			//following will print the subbuttons discription that are at position 0 in vector
			if (subButtons.at(0)->contains(event.mouseButton.x, event.mouseButton.y))
			{
				if ((subButtons.at(0)) == &lowHouse)
				{
					msg1 = "\n\nLowHouse selected";
				}
				else if ((subButtons.at(0)) == &busStation)
					msg1 = "\n\nBusStn selected";
				else if ((subButtons.at(0)) == &policeStation)
					msg1 = "\n\nPoliceStn selected";
				else if ((subButtons.at(0)) == &mall)
					msg1 = "\n\nMall selected";
				if ((subButtons.at(0)) == &park)
					msg1 = "\n\nPark selected";
			}
			//following will print the subbuttons discription that are at position 1 in vector
			if (subButtons.at(1)->contains(event.mouseButton.x, event.mouseButton.y))
			{
				if ((subButtons.at(1)) == &midHouse)
					msg1 = "\n\nMidHouse selected";
				else if ((subButtons.at(1)) == &trainStation)
					msg1 = "\n\nTrainStn selected";
				else if ((subButtons.at(1)) == &fireStation)
					msg1 = "\n\nFireStn selected";
				else if ((subButtons.at(1)) == &office)
					msg1 = "\n\nOffice selected";
				if ((subButtons.at(1)) == &recyclePlant)
					msg1 = "\n\nRecycle selected";
			}
			//following will print the subbuttons discription that are at position 2 in vector
			if (subButtons.at(2)->contains(event.mouseButton.x, event.mouseButton.y))
			{
				if ((subButtons.at(2)) == &highHouse)
					msg1 = "\n\nHighHouse selected";
				else if ((subButtons.at(2)) == &subwaySation)
					msg1 = "\n\nSubwayStn selected";
				else if ((subButtons.at(2)) == &hospital)
					msg1 = "\n\nHospital selected";
				else if ((subButtons.at(2)) == &factory)
					msg1 = "\n\nFactory selected";
				if ((subButtons.at(2)) == &waterTreatment)
					msg1 = "\n\nWaterTrt selected";
			}


			else if (event.mouseButton.x >= 200 && event.mouseButton.x < WINDOW_WIDTH - 5 && event.mouseButton.y > 5 && event.mouseButton.y < WINDOW_HEIGHT - 120 && mouseRelease == true) {
				mouseRelease = false;
				// find grid location based off mouse cursor
				int x = event.mouseButton.x - event.mouseButton.x % 40;
				int y = event.mouseButton.y - (event.mouseButton.y % 40) + 5;
				//check if grid is empty
				if (gridArray[x / 40][y / 40] == NULL) {
					//clicked on empty grid - add building of selected subtype
					//select type
					if (subSelection == NULL) { // incase no subtype is selected

												//add message to click sub selection
					}
					else if (subSelection == &lowHouse && myCity.money>=LOW_HOUSE_COST) { // to do change to housing class // for low house sub selection
						Housing*  temp = new Housing(15, 30, 15, 40, 40, x, y, "lowHouse.png",  LOW_HOUSE_COST); // create new Tile
						gameTiles.push_back(temp); // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						//add stats to city and pay for building
						myCity.employment += temp->getEmployment();
						myCity.pollution += temp->getPollution();
						myCity.population += temp->getPopulation();
						myCity.money -= temp->getCost();
						constructionSound.play();
						
					}
					else if (subSelection == &midHouse && myCity.money >=  MID_HOUSE_COST) {// to do change to housing class // for mid house sub selection
						Housing*  temp = new Housing(10, 10, 5, 40, 40, x, y, "midHouse.png", MID_HOUSE_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						//add stats to city and pay for building
						myCity.employment += temp->getEmployment();
						myCity.pollution += temp->getPollution();
						myCity.population += temp->getPopulation();
						myCity.money -= temp->getCost();
						constructionSound.play();
					}
					else if (subSelection == &highHouse && myCity.money >= HIGH_HOUSE_COST) {// to do change to housing class
						Housing*  temp = new Housing(5, 5, 5, 40, 40, x, y, "highHouse.png", HIGH_HOUSE_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						 //add stats to city and pay for building								  
						myCity.employment += temp->getEmployment();
						myCity.pollution += temp->getPollution();
						myCity.population += temp->getPopulation();
						myCity.money -= temp->getCost();
						constructionSound.play();
					}
					else if (subSelection == &busStation && myCity.money >=  BUS_STATION_COST) {
						Transit*  temp = new Transit(10, -10, -5, 10, 40, 40, x, y, "busStop.png",  BUS_STATION_COST);
						gameTiles.push_back(temp);				// add tile to drawing vector
						gridArray[x / 40][y / 40] = temp;			// add tile to tracking array
						//add stats to city and pay for building
						myCity.transportation += temp->getTransportation();
						myCity.accessibility += temp->getAccessibility();
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						hornSound.play();
					}
					else if (subSelection == &trainStation && myCity.money >=  TRAIN_STATION_COST) {
						Transit*  temp = new Transit(20, -5, -10, 15, 40, 40, x, y, "trainStation.png",  TRAIN_STATION_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						//add stats to city and pay for building
						myCity.transportation += temp->getTransportation();
						myCity.accessibility += temp->getAccessibility();
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						hornSound.play();
					}
					else if (subSelection == &subwaySation && myCity.money >= SUBWAY_STATION_COST) {
						Transit*  temp = new Transit(25, -10, 0, 20, 40, 40, x, y, "subwayStation.png", SUBWAY_STATION_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						//add stats to city and pay for building
						myCity.transportation += temp->getTransportation();
						myCity.accessibility += temp->getAccessibility();
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						hornSound.play();
					}
					else if (subSelection == &policeStation && myCity.money >=  POLICE_STATION_COST) {
						Security*  temp = new Security(30, 10, 40, 40, x, y, "policeStation.png",  POLICE_STATION_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						emergeSound.play();
					}
					else if (subSelection == &fireStation && myCity.money >= FIRE_STATION_COST) {
						Security*  temp = new Security(20, 20, 40, 40, x, y, "fireStation.png", FIRE_STATION_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						emergeSound.play();
					}
					else if (subSelection == &hospital && myCity.money >=  HOSPITAL_COST) {
						Security*  temp = new Security(25, 25, 40, 40, x, y, "hospital.png", HOSPITAL_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost(); 
						emergeSound.play();
					}
					else if (subSelection == &mall && myCity.money >= MALL_COST) {
						Jobs*  temp = new Jobs(9, -15, 10, 25, 40, 40, x, y, "mall.png", MALL_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.income += temp->getIncome();
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						constructionSound.play();
					}
					else if (subSelection == &office && myCity.money >= OFFICE_COST ){
						Jobs*  temp = new Jobs(5, -5, 5, 10, 40, 40, x, y, "office.png",  OFFICE_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.income += temp->getIncome();
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						constructionSound.play();
					}
					else if (subSelection == &factory && myCity.money >= FACTORY_COST) {
						Jobs*  temp = new Jobs(15, -30, 30, 40, 40, 40, x, y, "factory.png",  FACTORY_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.income += temp->getIncome();
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						factorySound.play();
					}
					else if (subSelection == &park && myCity.money >=  PARK_COST) {
						Environmental*  temp = new Environmental(-10, -5, 5, 40, 40, x, y, "park.png", PARK_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						parkSound.play();
					}
					else if (subSelection == &recyclePlant && myCity.money >= RECYCLE_COST) {
						Environmental*  temp = new Environmental(5, 20, 10, 40, 40, x, y, "recyclePlant.png", RECYCLE_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						recycleSound.play();
					}
					else if (subSelection == &waterTreatment && myCity.money >= WATER_COST) {
						Environmental*  temp = new Environmental(5, 10, 15, 40, 40, x, y, "waterTreatmentPlant.png", WATER_COST);
						gameTiles.push_back(temp);  // add tile to drawing vector
						gridArray[x / 40][y / 40] = temp; // add tile to tracking array
						myCity.employment += temp->getEmployment();//add stats to city and pay for building
						myCity.pollution += temp->getPollution();
						myCity.safety += temp->getSafety();
						myCity.money -= temp->getCost();
						waterSound.play();
					}


				}
				else {
					// clicked on an existing building

					//to do: add display of selected buildings stats
					if (selectedTile != NULL) {//reset color of last selected tile
						selectedTile->setColor(sf::Color::White);
					}
					selectedTile = gridArray[x / 40][y / 40]; //selected clicked tile
					selectedTile->setColor(sf::Color::Blue); //visual feedback for selected tile via color change

					//selectedTile->setFillColor(sf::Color::Blue);
					//show upgradable stats
					if (selectedTile->getType() == "environmental") {		//an enviormental button is selected
						upgradeOptions.at(0) = &upgradePollution;				//upgrade the stats according to the player choice
						upgradeOptions.at(0)->setPosition(FIRST_BUTTON_X, 640);
						upgradeOptions.at(1) = &upgradeSecurity;
						upgradeOptions.at(1)->setPosition(FIRST_BUTTON_X, 662);
						upgradeOptions.at(2) = &upgradeEmployment;
						upgradeOptions.at(2)->setPosition(FIRST_BUTTON_X, 684);
						if (upgradeOptions.at(3) != NULL) {
							upgradeOptions.at(3) = NULL;
						}
					}
					else if (selectedTile->getType() == "housing") {//an enviormental button is selected
						upgradeOptions.at(0) = &upgradeHousing;						//upgrade the stats according to the player choice
						upgradeOptions.at(0)->setPosition(FIRST_BUTTON_X, 640);
						upgradeOptions.at(1) = &upgradePollution;
						upgradeOptions.at(1)->setPosition(FIRST_BUTTON_X, 662);
						upgradeOptions.at(2) = &upgradeEmployment;
						upgradeOptions.at(2)->setPosition(FIRST_BUTTON_X, 684);
						if (upgradeOptions.at(3) != NULL) {
							upgradeOptions.at(3) = NULL;
						}
					}
					else if (selectedTile->getType() == "jobs") {//an enviormental button is selected
						upgradeOptions.at(0) = &upgradeIncome;
						upgradeOptions.at(0)->setPosition(FIRST_BUTTON_X, 640);			//upgrade the stats according to the player choice
						upgradeOptions.at(1) = &upgradeSecurity;
						upgradeOptions.at(1)->setPosition(FIRST_BUTTON_X, 662);
						upgradeOptions.at(2) = &upgradeEmployment;
						upgradeOptions.at(2)->setPosition(FIRST_BUTTON_X, 684);
						upgradeOptions.at(3) = &upgradePollution;
						upgradeOptions.at(3)->setPosition(FIRST_BUTTON_X, 706);
					}
					else if (selectedTile->getType() == "security") {//an enviormental button is selected
						upgradeOptions.at(0) = &upgradeSecurity;					//upgrade the stats according to the player choice
						upgradeOptions.at(0)->setPosition(FIRST_BUTTON_X, 640);
						upgradeOptions.at(1) = &upgradeEmployment;
						upgradeOptions.at(1)->setPosition(FIRST_BUTTON_X, 662);
						if (upgradeOptions.at(2) != NULL) {
							upgradeOptions.at(2) = NULL;
						}
						if (upgradeOptions.at(3) != NULL) {
							upgradeOptions.at(3) = NULL;
						}
					}
					else if (selectedTile->getType() == "transit") {//an enviormental button is selected
						upgradeOptions.at(0) = &upgradeTransportation;						//upgrade the stats according to the player choice
						upgradeOptions.at(0)->setPosition(FIRST_BUTTON_X, 640);
						upgradeOptions.at(1) = &upgradeSecurity;
						upgradeOptions.at(1)->setPosition(FIRST_BUTTON_X, 662);
						upgradeOptions.at(2) = &upgradePollution;
						upgradeOptions.at(2)->setPosition(FIRST_BUTTON_X, 684);
						upgradeOptions.at(3) = &upgradeAccessibility;
						upgradeOptions.at(3)->setPosition(FIRST_BUTTON_X, 706);
					}
				}
			}

			else if (event.mouseButton.x >= FIRST_BUTTON_X && event.mouseButton.x < 200 && event.mouseButton.y >= 640 && event.mouseButton.y < 662 && mouseRelease == true) { //upgrade button zero is pressed
			 //find out what upgrade button zero is and carry its upgrade out
				mouseRelease = false;//prevent multiple upgrades on one click
				if (selectedTile->getType() == "environmental" && myCity.money >= POLLUTION_UPGRADE_COST) { //upgrade tile stats
					static_cast<Environmental*>(selectedTile)->setPollution(static_cast<Environmental*>(selectedTile)->getPollution() + 1);
					cout << "Pollution value is now: " << static_cast<Environmental*>(selectedTile)->getPollution() << endl;
					myCity.pollution -= 1; //upgrade city stats
					myCity.money -= POLLUTION_UPGRADE_COST;
				}
				else if (selectedTile->getType() == "housing" && myCity.money >= POPULATION_UPGRADE_COST) {
					static_cast<Housing*>(selectedTile)->setPopulation(static_cast<Housing*>(selectedTile)->getPopulation() + 1);
					cout << "Housing value is now: " << static_cast<Housing*>(selectedTile)->getPopulation() << endl;
					myCity.population += 1;			//make changes to the pollution	
					myCity.money -= POPULATION_UPGRADE_COST;					//make changes to the money
				}
				else if (selectedTile->getType() == "jobs" && myCity.money >= INCOME_UPGRADE_COST) {
					static_cast<Jobs*>(selectedTile)->setIncome(static_cast<Jobs*>(selectedTile)->getIncome() + 1);
					cout << "Income value is now: " << static_cast<Jobs*>(selectedTile)->getIncome() << endl;
					myCity.income += 1;				//make changes to the income
					myCity.money -= INCOME_UPGRADE_COST;        //make changes to the money
				}
				else if (selectedTile->getType() == "security" && myCity.money >= SAFETY_UPGRADE_COST) {
					static_cast<Security*>(selectedTile)->setSafety(static_cast<Security*>(selectedTile)->getSafety() + 1);
					cout << "Saftey value is now: " << static_cast<Security*>(selectedTile)->getSafety() << endl;
					myCity.safety += 1;					//make changes to the safety
					myCity.money -= SAFETY_UPGRADE_COST;				//make changes to the money
				}
				else if (selectedTile->getType() == "transit" && myCity.money >= TRANSIT_UPGRADE_COST) {
					static_cast<Transit*>(selectedTile)->setTransportation(static_cast<Transit*>(selectedTile)->getTransportation() + 1);
					cout << "Transformation value is now: " << static_cast<Transit*>(selectedTile)->getTransportation() << endl;
					myCity.transportation += 1;						//make changes to the transportation
					myCity.money -= TRANSIT_UPGRADE_COST;						//make changes to the money
				}
			}
			else if (event.mouseButton.x >= FIRST_BUTTON_X && event.mouseButton.x < 200 && event.mouseButton.y >= 662 && event.mouseButton.y < 684 && mouseRelease == true) { //upgrade button one is pressed
				mouseRelease = false;
				//find out what upgrade button one is and carry its upgrade out
				if (selectedTile->getType() == "environmental" && myCity.money >= SAFETY_UPGRADE_COST) {
					static_cast<Environmental*>(selectedTile)->setSafety(static_cast<Environmental*>(selectedTile)->getSafety() + 1);
					cout << "Saftey value is now: " << static_cast<Environmental*>(selectedTile)->getSafety() << endl;
					myCity.safety += 1;							//make changes to the safety
					myCity.money -= SAFETY_UPGRADE_COST;			//make changes to the money
				}
				else if (selectedTile->getType() == "housing" && myCity.money >= POLLUTION_UPGRADE_COST) {
					static_cast<Housing*>(selectedTile)->setPollution(static_cast<Housing*>(selectedTile)->getPollution() + 1);
					cout << "Pollution value is now: " << static_cast<Housing*>(selectedTile)->getPollution() << endl;
					myCity.pollution -= 1;						////make changes to the pollution
					myCity.money -= POLLUTION_UPGRADE_COST;				//make changes to the money
				}
				else if (selectedTile->getType() == "jobs" && myCity.money >= SAFETY_UPGRADE_COST) {
					static_cast<Jobs*>(selectedTile)->setSafety(static_cast<Jobs*>(selectedTile)->getSafety() + 1);
					cout << "Saftey value is now: " << static_cast<Jobs*>(selectedTile)->getSafety() << endl;
					myCity.safety += 1;						//make changes to the safety
					myCity.money -= SAFETY_UPGRADE_COST;						//make changes to the money
				}
				else if (selectedTile->getType() == "security" && myCity.money >= EMPLOYMENT_UPGRADE_COST) {
					static_cast<Security*>(selectedTile)->setEmployment(static_cast<Security*>(selectedTile)->getEmployment() + 1);
					cout << "Employment value is now: " << static_cast<Security*>(selectedTile)->getEmployment() << endl;
					myCity.employment += 1;								//make changes to the employment
					myCity.money -= EMPLOYMENT_UPGRADE_COST;			//make changes to the money
				}
				else if (selectedTile->getType() == "transit" && myCity.money >= SAFETY_UPGRADE_COST) {
					static_cast<Transit*>(selectedTile)->setSafety(static_cast<Transit*>(selectedTile)->getSafety() + 1);
					cout << "Safety value is now: " << static_cast<Transit*>(selectedTile)->getSafety() << endl;
					myCity.safety += 1;									//make changes to the safety
					myCity.money -= SAFETY_UPGRADE_COST;				//make changes to the money
				}
			}
			else if (event.mouseButton.x >= FIRST_BUTTON_X && event.mouseButton.x < 200 && event.mouseButton.y >= 684 && event.mouseButton.y < 706 && mouseRelease == true) { //upgrade button two is pressed
				mouseRelease = false;
				 //find out what upgrade button two is and carry its upgrade out
				if (selectedTile->getType() == "environmental" && myCity.money >= EMPLOYMENT_UPGRADE_COST) {
					static_cast<Environmental*>(selectedTile)->setEmployment(static_cast<Environmental*>(selectedTile)->getEmployment() + 1);
					cout << "Employment value is now: " << static_cast<Environmental*>(selectedTile)->getEmployment() << endl;
					myCity.employment += 1;								//make changes to the employment
					myCity.money -= EMPLOYMENT_UPGRADE_COST;				//make changes to the money
				}
				else if (selectedTile->getType() == "housing" && myCity.money >= EMPLOYMENT_UPGRADE_COST) {
					static_cast<Housing*>(selectedTile)->setEmployment(static_cast<Housing*>(selectedTile)->getEmployment() + 1);
					cout << "Employment value is now: " << static_cast<Housing*>(selectedTile)->getEmployment() << endl;
					myCity.employment += 1;								//make changes to the employment
					myCity.money -= EMPLOYMENT_UPGRADE_COST;					//make changes to the money
				}
				else if (selectedTile->getType() == "jobs" && myCity.money >= EMPLOYMENT_UPGRADE_COST) {
					static_cast<Jobs*>(selectedTile)->setEmployment(static_cast<Jobs*>(selectedTile)->getEmployment() + 1);
					cout << "Employment value is now: " << static_cast<Jobs*>(selectedTile)->getEmployment() << endl;
					myCity.employment += 1;						//make changes to the employment
					myCity.money -= EMPLOYMENT_UPGRADE_COST;				//make changes to the money
				}
				else if (selectedTile->getType() == "transit" && myCity.money >= POLLUTION_UPGRADE_COST) {
					static_cast<Transit*>(selectedTile)->setPollution(static_cast<Transit*>(selectedTile)->getPollution() + 1);
					cout << "Pollution value is now: " << static_cast<Transit*>(selectedTile)->getPollution() << endl;
					myCity.pollution -= 1;						//make changes to the pollution
					myCity.money -= POLLUTION_UPGRADE_COST;						//make changes to the money
				}
			}
			else if (event.mouseButton.x >= FIRST_BUTTON_X && event.mouseButton.x < 200 && event.mouseButton.y >= 706 && event.mouseButton.y < 730 && mouseRelease == true) { //upgrade button three is pressed
				mouseRelease = false;
				//find out what upgrade button three is and carry its upgrade out
				if (selectedTile->getType() == "jobs" && myCity.money >= POLLUTION_UPGRADE_COST) {
					static_cast<Jobs*>(selectedTile)->setPollution(static_cast<Jobs*>(selectedTile)->getPollution() + 1);
					cout << "Pollution value is now: " << static_cast<Jobs*>(selectedTile)->getPollution();
					myCity.pollution -= 1;						//make changes to the pollution
					myCity.money -= POLLUTION_UPGRADE_COST;			//make changes to the money
				}
				else if (selectedTile->getType() == "tranist" && myCity.money>= ACCESSIBILITY_UPGRADE_COST) {
					static_cast<Transit*>(selectedTile)->setAccessibility(static_cast<Transit*>(selectedTile)->getAccessibility() + 1);
					cout << "Accessibility value is now: " << static_cast<Transit*>(selectedTile)->getAccessibility();
					myCity.accessibility += 1;					//make changes to the accessibility
					myCity.money -= ACCESSIBILITY_UPGRADE_COST;			//make changes to the money
				}
			}
		}
		TextButton DiscriptionButton(msg.str() + msg1, 20, sf::Color::White, FIRST_BUTTON_X, (FIRST_BUTTON_Y + BUTTON_SIZE) * 2.5 + (BUTTON_SIZE * 2));       //this will create a discription button
		

		//change color of city requirements when goals have been met - Red when not met / Green when met
		if (myCity.year >= cityWin.year) {
			winYearText.setFillColor(sf::Color::Green);
		}
		else {
			winYearText.setFillColor(sf::Color::Red);
		}
		if (myCity.population >= cityWin.population) {
			winPopulationText.setFillColor(sf::Color::Green);
		}
		else {
			winPopulationText.setFillColor(sf::Color::Red);
		}
		if (myCity.employment >= cityWin.employment) {
			winEmploymentText.setFillColor(sf::Color::Green);
		}
		else {
			winEmploymentText.setFillColor(sf::Color::Red);
		}
		if (myCity.safety >= cityWin.safety) {
			winSafetyText.setFillColor(sf::Color::Green);
		}
		else {
			winSafetyText.setFillColor(sf::Color::Red);
		}																		//change the color to red when the city requirement is not met or green if the city requirement is met
		if (myCity.pollution < cityWin.pollution) {
			winPollutionText.setFillColor(sf::Color::Green);
		}
		else {
			winPollutionText.setFillColor(sf::Color::Red);
		}		
		if (myCity.transportation >= cityWin.transportation) {
			winTransportationText.setFillColor(sf::Color::Green);
		}
		else {
			winTransportationText.setFillColor(sf::Color::Red);
		}
		if (myCity.accessibility >= cityWin.accessibility) {
			winAccessibilityText.setFillColor(sf::Color::Green);
		}
		else {
			winAccessibilityText.setFillColor(sf::Color::Red);
		}
		
	
		//clear city stats
		cityStatsString.str("");
		//update city stats
		cityStatsString << "Current Year: " << myCity.year << "\nPopulation: " << myCity.population << "\nEmployment: " << myCity.employment << "\nSafety: " << myCity.safety <<
			"\nPollution: " << myCity.pollution << "\nIncome: " << myCity.income << "\nTransportation: " << myCity.transportation <<
			"\nAccessibility: " << myCity.accessibility << "\nMoney: " << myCity.money;
		cityStatsText.setString(cityStatsString.str());
		//clear window
		window.clear(sf::Color::Black);
		//draw objects
		window.draw(emptyTileSprite);							//draw empty tiles
		window.draw(drawingArea);								//draw drawing area
		window.draw(houseSec.getShape());						//draw house section
		window.draw(transitSec.getShape());						//draw transition section
		window.draw(securitySec.getShape());					//draw security section
		window.draw(commerceSec.getShape());					//draw commercial section
		window.draw(enviormentSec.getShape());					//draw environmental section
		for (int i = 0; i < subButtons.size(); i++) {				// draw sub buttons
			window.draw(subButtons.at(i)->getShape());
		}
		for (int i = 0; i < gameTiles.size(); i++) {			// draw game tiles
			window.draw(gameTiles.at(i)->getShape());
		}
		window.draw(cityStatsText);					//draw city stats text
		window.draw(winYearText);					//draw win year text
		window.draw(winPopulationText);				//draw win popullation text
		window.draw(winEmploymentText);				//draw win employment text
		window.draw(winSafetyText);				//draw win safety twxt
		window.draw(winPollutionText);				//draw win poppulation text
		window.draw(winTransportationText);			//draw win transportation text
		window.draw(winAccessibilityText);				//draw win accessibility text

		window.draw(DiscriptionButton.getText());       //draws Discription button
		window.draw(UpgradeButton.getText());        //draws the upgrade button
		window.draw(CityStatus.getText());        //draws the cityStatus button
		window.draw(RequireButton.getText());        //draws the cityStatus button
		window.draw(EndButton.getText());        //draws the cityStatus button
		window.draw(turnButton.getText());      //draw turn buttons

		//draw upgrade buttons
		for (int i = 0; i < upgradeOptions.size(); i++) {
			if (upgradeOptions.at(i) != NULL) {
				window.draw(upgradeOptions.at(i)->getText());
			}
		}
		if (myCity.year >= 2030) {
			if (checkWin(myCity, cityWin)) {
				window.draw(winText);
			}
			else {
				window.draw(loseText);
			}
		}
		window.display();
	}

	//delete tiles made with new
	for (int i = 0; i < gameTiles.size(); i++) {
		delete gameTiles.at(i);
	}

	return 0;
}

bool checkWin(cityStatsStruct myCity, cityStatsStruct cityWin) {            //function to check if the player won the game or not

	if (myCity.employment >= cityWin.employment &&
		myCity.pollution < cityWin.pollution &&
		myCity.population >= cityWin.population &&
		myCity.accessibility >=cityWin.accessibility &&
		myCity.transportation >= cityWin.transportation &&
		myCity.safety >= cityWin.safety)
		return true;
	else
		return false;
}