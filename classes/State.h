#pragma once
static class State {
public:

	// State for input
	static enum STATE { WAITING, INITIALIZING, EXPLODING, RESETTING };

	// State for input
	static STATE state;

	// How many pieces to explode teapot into
	static int groupsOfParticles;
	static bool radial;
	static float slowMotionFactor;
	static bool closeUp;
	static float normalSpeed;
	static float slowSpeed;
	static float slowerSpeed;
};

