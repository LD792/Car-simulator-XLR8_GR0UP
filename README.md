# Car-simulator-XLR8_GR0UP
“We’re not a big studio — just a group of friends without experience making the kind of car simulator we wish existed. Fast cars, cool vibes, pure fun.” 

# [+]📍The project map :

xlr8_sim/
│
├── src/                      All C source code
│   ├── main.c                Main loop and Raylib window setup
│   ├── engine.c              Engine simulation logic (RPM, torque)
│   ├── engine.h
│   ├── car.c                 Car physics and control (speed, position)
│   ├── car.h
│   ├── audio.c               Sound engine: pitch by RPM
│   ├── audio.h
│   ├── graphics.c            Drawing engine, pistons, car, UI
│   ├── graphics.h
│   └── input.c               Handle keyboard/controller inputs
│       input.h
│
├── assets/                   Audio & texture files
│   ├── sounds/
│   │   ├── engine_base.wav
│   ├── textures/
│   │   ├── car.png
│   │   └── piston.png
│
├── shaders/                 Optional: Raylib GLSL shaders for effects
│   └── glow.fs
│
├── scripts/                 Python helpers (e.g., precompute audio pitch maps, tuning)
│   └── sound_tuner.py
│
├── include/                # Shared headers if needed
│   └── config.h
│
├── Makefile                # Build configuration
└── README.md

and more inchaallah .
