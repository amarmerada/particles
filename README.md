# particles

Implements particle demos

![7i12e9](https://user-images.githubusercontent.com/67133103/231828319-b09e8c60-5409-4251-9036-9073cf674754.gif)


## How to build

*Windows*

Open git bash to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake ..
particles/build $ start particles.sln
```

Your solution file should contain four projects.
To run from the git bash command shell, 

```
particles/build $ ../bin/Debug/billboard-axis.exe
particles/build $ ../bin/Debug/explosion.exe
particles/build $ ../bin/Debug/sparkle-trail.exe
particles/build $ ../bin/Debug/sparkles.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake ..
particles/build $ make
```

To run each program from build, you would type

```
particles/build $ ../bin/billboard-axis
particles/build $ ../bin/sparkles
particles/build $ ../bin/sparkle-trail
particles/build $ ../bin/explosion
```

## Demo of basic features

Sparkle Trail - generates star with trailing sparkles

Explosion -animates explosion using spritesheet

Billboard axis - billboard always faces camera
## Unique features 


Snow - snow falls and collects at a specific threshold
Waterfall - waterfall animation

