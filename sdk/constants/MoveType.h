#pragma once

enum MoveType {
	NONE = 0,	// never moves
	ISOMETRIC,			// For players -- in TF2 commander view, etc.
	WALK,				// Player only - moving on the ground
	STEP,				// gravity, special edge handling -- monsters use this
	FLY,				// No gravity, but still collides with stuff
	FLYGRAVITY,		// flies through the air + is affected by gravity
	VPHYSICS,			// uses VPHYSICS for simulation
	PUSH,				// no clip to world, push and crush
	NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	LADDER,			// Used by players only when going onto a ladder
	OBSERVER,			// Observer movement, depends on player's observer mode
	CUSTOM,			// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	LAST = CUSTOM,

	MAX_BITS = 4
};