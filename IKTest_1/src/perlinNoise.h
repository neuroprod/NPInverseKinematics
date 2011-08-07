// perlinNoise.h
// Class to implement coherent noise over 1, 2, or 3 dimensions.
// Implementation based on the Perlin noise function. Thanks to 
// Ken Perlin of NYU for publishing his algorithm online.
/////////////////////////////////////////////////////////////////////
// Copyright (c) 2001, Matt Zucker
// You may use this source code as you wish, but it is provided
// with no warranty. Please email me at mazucker@vassar.edu if 
// you find it useful.
/////////////////////////////////////////////////////////////////////

#ifndef _NOISE_CLASS_H_
#define _NOISE_CLASS_H_

#include <stdlib.h>

// It must be true that (x % NOISE_WRAP_INDEX) == (x & NOISE_MOD_MASK)
// so NOISE_WRAP_INDEX must be a power of two, and NOISE_MOD_MASK must be
// that power of 2 - 1.  as indices are implemented, as unsigned chars,
// NOISE_WRAP_INDEX shoud be less than or equal to 256.
// There's no good reason to change it from 256, really.

#define NOISE_WRAP_INDEX	256
#define NOISE_MOD_MASK		255

// A large power of 2, we'll go for 4096, to add to negative numbers
// in order to make them positive

#define NOISE_LARGE_PWR2	4096

class perlinNoise {
  private:
    static unsigned initialized;
  
    static unsigned permutationTable[NOISE_WRAP_INDEX*2 + 2];	// permutation table
    static float    gradientTable1d[NOISE_WRAP_INDEX*2 + 2];	// 1d gradient lookup table.
    static float    gradientTable2d[NOISE_WRAP_INDEX*2 + 2][2];	// 2d gradient lookup table.
    static float    gradientTable3d[NOISE_WRAP_INDEX*2 + 2][3];	// 3d gradient lookup table.
    
    static float    randNoiseFloat();			// generate a random float in [-1,1]
    static void     normalize2d(float vector[2]);	// normalize a 2d vector
    static void     normalize3d(float vector[3]);	// normalize a 3d vector
    static void     generateLookupTables();		// fill in table entries
    
  public:
    static void     reseed();			// reseed random generator & regenerate tables
    static void     reseed(unsigned int rSeed);	// same, but with specified seed

    static float    noise1d(float pos[1]);	// 1D call using an array for passing pos
    static float    noise2d(float pos[2]);	// 2D call using an array for passing pos
    static float    noise3d(float pos[3]);	// 3D call using an array for passing pos

    static float    noise(float);		// use individual elements for passing pos
    static float    noise(float, float);
    static float    noise(float, float, float);
};

#endif

