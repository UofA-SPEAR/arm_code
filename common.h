#ifndef COMMON
#define COMMON
#include <Arduino.h>
#include <stdint.h>

//Constants for array index of each motor
#define BASE 0
#define SHOULDER 1
#define ELBOW 2
#define WRIST_PITCH 3
#define WRIST_ROLL 4
#define FINGERS 5

#define NUM_MOTORS 4

#ifndef UINT32_MAX
#define UINT32_MAX 4294967295u
#endif

#ifndef INT32_MAX
#define INT32_MAX 2147483647
#endif

#ifndef INT32_MIN
#define INT32_MIN -2147483648
#endif

#ifndef INT16_MAX
#define INT16_MAX 32767
#endif

#ifndef INT16_MIN
#define INT16_MIN -32768
#endif

#endif
