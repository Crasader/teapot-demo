#pragma once
static class State {
public:

	// State for input
	static enum STATE { WAITING, INITIALIZING, EXPLODING, RESETTING };

	// State for input
	static STATE state;

	// How many pieces to explode teapot into
	static int numberOfTeapots;
	static int groupsOfParticles;
	static bool radial;
	static float slowMotionFactor;
	static bool closeUp;
	static bool normalSpeed;
	static bool slowSpeed;
	static bool slowerSpeed;
};

