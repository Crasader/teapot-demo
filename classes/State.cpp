#include "pch.h"

// State for input
State::STATE State::state = WAITING;

// How many pieces to explode teapot into
int State::groupsOfParticles = 25;
bool State::radial = true;
float State::slowMotionFactor = 1.0f;
bool State::closeUp = false;

float State::normalSpeed;
float State::slowSpeed;
float State::slowerSpeed;
