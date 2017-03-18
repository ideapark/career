// C99

float *fPtr = (float[]){ -0.5, 0.0, +0.5 };

#include "database.h" // struct Pair { long ken; char value[32]; };
insertPair(&db, &(struct Pair){ 1000L, "New York JFK Airport" });
