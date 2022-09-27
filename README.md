# Ardutask
PlatformIO library for running multiple 'Arduino-like' processes simultaneously. Designed to be multi-platform for both embedded and native!

[![Native Build](https://github.com/15jgme/Ardutask/actions/workflows/nativeBuild.yml/badge.svg)](https://github.com/15jgme/Ardutask/actions/workflows/nativeBuild.yml)

[![Teensy Build](https://github.com/15jgme/Ardutask/actions/workflows/teensyBuild.yml/badge.svg)](https://github.com/15jgme/Ardutask/actions/workflows/teensyBuild.yml)

This library introduces a TaskManager class which can be loaded with 'Tasks' which it coordinates to run at a desired rate.
Tasks are added by the user of the library and can do anything! They derive from a simple base task class which closely resembles the standard Arduino setup/loop structure.

## Using this library

Take a look at the example folder for a sample task which prints "bar" on startup and "foo" on loop at a specific frequency.
A sample main.cpp file is also included to show how taskManager should be used. 
Generally you are able to create a new task object, pass it to taskManager using the `addtask` function and then call the `run` function on every iteration of your primary program loop.

On Windows the only additional note is that the function `runMsgPump` must be called on every iteration to operate the windows messages.

One additional note, currently a few defines are required in your .pio file for Ardutask to figure out what timers to use. We want to get rid of this soon but it will be required in the mean time.

## Architecture

This library offers a simple, stipped down, alternative to larger real time operating systems. Execution timings are not guarenteed, however the results should be reasonable. When taskManager is initialized, it spawns five timers operating at five different rates. When you add a task to taskManager using the `addtask` function, it will assign it to one of these times depending on the desired rate. When the timer activates, a call back function checks if any of the tasks assigned to it need to be run. If they do it will add them to a list to be called during the main loop of the code. Critically the tasks are *not* run by the callback function. Instead they are only queued up by it.
Since the main loop will run your tasks, they **cannot** be blocking. Your tasks should be able to run at the desired rate or else it will delay other tasks. As such `sleep()` or `delay()` should generally be avoided, however similar results can be acheived by combinations of tasks or waiting to continue your operation at the next update of your task.

## Extending this library to new platforms
This is desiged to be easy! Platform specific libraries are avoided in this library so all you need to do is impliment a new timer.
You can derive from the base timer class `multiTime` and then all you need to do is setup a timer on your platform that can call multiTime's callback function at a given rate and you're all good! Please contribute your work to make Ardutask widely available :)
