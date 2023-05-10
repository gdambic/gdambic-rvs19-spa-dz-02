#pragma once
#define get_rnd(min, max) ((int) rand() % (max - min + 1) + min) //rand generator macro
#define get_rgb() ((int) rand()%255) //rand rgb generator macro