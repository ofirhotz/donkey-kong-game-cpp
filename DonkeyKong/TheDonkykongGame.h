#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include "io_utils.h"
#include "Mario.h"
#include "Steps.h"
#include <vector>




class TheDonkykongGame {
	enum { ESC = 27 };
	Mario m[1];
	
	
public:
	int mX, mY;
	
	void init();
	void run();
	void spawnBarrel(int monkeyX, int monkeyY);
	void updateBarrels();
	void resetGame();
	void checkCollisions();
	void checkFallDamage();
	bool loadLevel(const string& filename);
	void nextLevel();
	bool checkWinCondition() const;
	void spawnGhosts();
	void updateSGhosts();
	void updateGhosts();
	void removeGhost(int ghostIndex);
	void removeSGhost(int ghostIndex);
	void removeBarrel(int barrelIndex);
	void loadSteps(const std::string& stepsFile);
	void runReplay();
	void runSilent(const std::string& resultsFile);
	void runAndSave(const std::string& stepsFile, const std::string& resultsFile);
	void updateGame();
	void renderGame();
	std::vector<Step> getRelevantSteps(int currentTime);
	void executeAction(const std::string& objectId, const std::string& action , int dir);
	bool isGameOver() const;

		

};

#endif