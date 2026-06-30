# Arduino Obstacle Avoiding Robot

This is my first Arduino-based obstacle avoiding robot project, built and modified during my first semester break.

## Background

This project started from my curiosity during a semester break. I wanted to use my free time to build something simple but functional. The project was inspired by a YouTube tutorial and modified as part of my self-learning process in robotics and embedded systems.

## Components

- Arduino board
- Ultrasonic sensor
- Servo motor
- L298N motor driver
- DC motors
- Battery
- Jumper wires
- Robot chassis

## How It Works

The robot uses an ultrasonic sensor to detect obstacles in front of it. If the path is clear, the robot moves forward. If an obstacle is detected within around 20 cm, the robot stops, moves backward, and scans the right and left sides using a servo motor.

After comparing both distances, the robot turns toward the side with more available space.

## Libraries

- Servo.h
- NewPing.h

## Status

This project is a beginner-level prototype and was created as part of my early learning journey in robotics and embedded systems.
