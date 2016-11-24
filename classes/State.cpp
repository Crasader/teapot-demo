#include "pch.h"

// State for input
State::STATE State::state = WAITING;

// How many pieces to explode teapot into
int State::numberOfTeapots = 3;
int State::groupsOfParticles = 25;
bool State::radial = false;
float State::slowMotionFactor = 500.0f;
bool State::closeUp = false;

bool State::normalSpeed = false;
bool State::slowSpeed = false;
bool State::slowerSpeed = true;
