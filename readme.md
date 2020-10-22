#Project RTOS

Welcome to my nightmare, yes. 
Everyone who reads this needs lots of beers and understanding for a such of sorcery.

***
This is what it needs to be in the final state a fully working project using FreeRTOS operating system on an embedded system.
Why RTOS?
Well , an embedded system needs a functional code to be written on a microcontroller to do tasks in a certain way in a system.
Of course, for a beginner in embedded system the term RTOS is basically "what the hell is this and what does this stuff wants from my life".
Complicated things eh

Every microcontroller-based system does tasks in a certain time. 
Well , some tasks are so-called ~critical time-tasks~ , like the control systems in the cars, ESP ABS and so on.
These things needs to reat very fast when the master system needs that assistance from them. So execution time in some tasks is critical to be minimal.
For that is needed the RTOS. Basically an RTOS is like an extension for the microcontroller functionalities , which manages to do tasks in a certain time and in a certain way.
Yeah, some codes are not worthy to be implemented with some sort of operating system or other sorceries , but some do .. and needs to be coded properly indeed.

This project is a learning experience for me, so for that i really started from the ground zero.

***
What i did in this project for now:
- Configured FreeRTOS10 properly for working with Atmel Studio 7 IDE
- Started a new project with the ~new~ depedencies
- Well, here comes de fun part: configuring the FreeRTOS to work properly with my microcontroller, and compile also (another fun part..no)
- I did my first ever task using this system : a blink :)
- Started to mess with some delay functions to see who is the best to use and why
- Added another task to the first one to see how the scheduler reacts
- And yes, the inevitable part in every emsys programmer life: messing with the system interrupts

What to do for next?
Well first of all will be what the hell i am going to implement for this project, what sensor , what communication protocol etc. ... damn,is tuff.
Second , well this is going to be first for sure .. starting to mess with queues , semaphors , notifications and so on
Third , i am totally sure that this point will be the one star , start to add some peripherals to the board , like an LCD , some RS232 communication.
Third star , will see what sensor i add to this thing..
