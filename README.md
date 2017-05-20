# Arcade Controller

## What is this?

This program is meant for arduino micro/leonardo type devices to allow
keyboard or other HID type input via usb connection.

## Is it really that easy?

If you're not afraid to connect a few wires together and make yourself some
form of button to press, it is that easy.  

## Why use a keypad grid instead of connecting buttons directly to GPIO and ground?

Sometimes there just isn't enough GPIO pins available so you need to be crafty.  Imagine having only 5 GPIO pins available when you need to have 6 buttons.  In a grid that's 2 x 3, you can have your 6 buttons.  If you have 10 GPIO pins available, you can have a grid that is 5 x 5 which is more than double the amount of GPIO pins available.

## So how do I wire this thing up?

After you decide what GPIO pins you want to use, you wire things up according to your grid in the code.

Here's an example of a 3 x 3 grid.

--- | Pin 2 | Pin 3 | Pin 4
--- | --- | --- | ---
Pin 6 | A | B | C
Pin 7 | D | E | F
Pin 8 | G | H | I

Imagine the letters are your buttons.  Button A is connected to Pin 2 and Pin 6. Button E is connected to Pin 3 and Pin 7. Button I is connected to Pin 4 and Pin 8.

## What kind of limitations are there?

I have not tested this yet but I read that there is a limit of 10 keys being pressed at the same time.  For an arcade system, this probably not going to be a problem.  

## Known problems?

In Windows 10, the arduino micro pro might not be recognized as a HID device.  This means that the computer was not allowing the device to send in commands as if it were a device like a keyboard.

My fix is kind of strange but it works.  Go to device manager, find your Arduino Micro under Ports. Right click, update driver, "Browse my computer for driver software", "Let me pick from a list of available drivers", and now you'll see a couple of options.  I selected the one that says "USB Serial Device" and voila! It works.  

This is not an issue on RaspberryPi devices and most likely not a problem on linux systems either.
