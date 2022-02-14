# 3DRenderer-megadrive

Sega Megadrive (Genesis) SGDK port of the 3D renderer developed in [3D Graphics Programming from Scratch](https://courses.pikuma.com/courses/learn-computer-graphics-programming) course.

Techs:
- [SGDK 1.7](https://github.com/Stephane-D/SGDK)
- [Doragasu SGDK docker container](https://gitlab.com/doragasu/docker-sgdk)

Bugs:
- After a few seconds there is a division by zero in the draw_line function. The bug is handled and does not affect rendering, but it should be fixed.