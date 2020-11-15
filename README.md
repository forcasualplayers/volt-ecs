# volt.ecs 

[![Build Status](https://travis-ci.com/forcasualplayers/volt.ecs.svg?branch=main)](https://travis-ci.com/forcasualplayers/volt.ecs)

A header-only Entity-Component-System written in C++17/20 for the voltech engine.

This project was created for strictly educational reasons.
For fully-featured, stable ECS implementations, I highly recommend either of the following:
* [EnTT](https://github.com/skypjack/entt)
* [flecs](https://github.com/SanderMertens/flecs)

These are the core goals of volt.ecs:
* C++20-compliance
* Platform-independence
* Modularity

And these are the educational targets:
* Project organization
  * IDE integration (clang-tidy)
  * Build tool automation (CMake, Ninja)
* Continuous integration/continuous deployment

Due to technological limitations, some of these goals may not be achieved in the meanwhile (such as proper usage of C++20 features). 

## Installation

Since volt.ecs is a header-only library, the user only needs to drop the `include/volt` directory into their dependencies.

For ease of use, the CMake setup also allows the user to link the library by adding the following line to their `CMakeLists.txt`.
```
target_link_libraries(TARGET_NAME volt_ecs)
```

## Licensing

volt.ecs is developed and released under the MIT License.
