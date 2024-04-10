# Wafer Stage Move

## Task

Write a program that demonstrates a so-called '*triangular move profile*'.


## Context

A move-profile describes an object's motion from one position to another.
You can think of it as a graph of velocities through time.

A triangular move profile describes a motion that consists of a period of
constant acceleration followed by a period of constant deceleration:

```
max velocity
    /\
   /  \
0 /    \
```

Note that the X axis is *time*, not position. Acceleration is the *slope* of
the triangle's legs. [This](https://www.linearmotiontips.com/how-to-calculate-velocity/)
may be a useful reference for the relationship between velocity, time, 
acceleration, and distance.


## Functional Requirements

1. The program shall visualize motion in real time.
   The visualization may be done in a terminal.

2. The program shall read pairs of (`target position`, `acceleration`) from
   some sort of input. This may be `stdin`, a file, etc.

   *Note: The units are unspecified and may be chosen as convenient.*

3. For each pair of inputs, the program shall demonstrate a motion from
   the current position to the `target position`.
   The motion shall have a triangular profile with the specified `acceleration`.

4. The program shall log to a text file the current position at some time
   interval such that the motion can be examined (e.g. plotted) externally.


## Test Requirements

1. Major calculations and/or logical sequences shall be covered by unit tests.
2. There shall be example input appropriate for manual testing.


## Architectural Requirements

1. The software shall be logically separated into modules.
2. The software shall be buildable on Linux.
3. A CMake project is preferable, but not required.
   If another build system is chosen, please include build instructions.
