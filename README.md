# MenuLibrary
### An Arduino library for making menus written in C++
===

I wanted a menu library where the code was easy to read, easy to extend, and made sense.
Most menu libraries I found to be hard to read for a beginner, so I made this library as an alternative.

#### Note:
There is a reason other libraries are so hard to read: they are optimized for minimal RAM usage (so that you can actually use them on an AVR lol).
This library favours simpler code over memory usage most of the time. As a result, I wouldn't currently recommend it for actual deployment unless you are on a platform with lots of RAM.
As it stands currently, even small menus will run into memory issues on an arduino uno.

If you can make the memory footprint smaller while maintaining beginner-friendliness, please submit a pull request.
