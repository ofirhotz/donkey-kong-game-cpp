#ifndef STEPS_H
#define STEPS_H

#include <string>
#include <vector>

struct Step {
    int time;
    std::string objectId;
    std::string action;
    int direction;

public :
    // Constructor to initialize Step with objectId and action
    Step(int mosh, std::string id,  std::string act , int dir)
        : objectId(id), action(act) ,time(mosh) , direction(dir) {
    }
};

#endif