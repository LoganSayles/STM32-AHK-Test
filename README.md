
# STM32-AHK-Test

This firmware is a proof-of-concept test to gain an understanding of how keyboard HID inputs are entered into a system and how a system reacts to those keyboard HIDs.

This test was used to prove a further idea of modifying existing peripheral firmware updaters with a malicious payload such that execution of malicious key inputs can be entered into a system, then resume regular peripheral function.

## Motivations

My motivation for this project lies within my final year dissertation project. I wanted to display how a peripheral device, such as a computer mouse, could be modified to include a basic script to complete a series of pre-defined keyboard inputs in a potentially malicious manner.

## Setup

The setup for this is relatively simple. For this project, I used an STM32-103rb; however, it should work with any equivalent STM32 device, albeit I will be talking through this setup from the context of the microcontroller I've chosen.

Once the firmware has been updated, a 1.5kΩ resistor needs to be added such that the receiving device can register the USB Full-Speed connection.

I used a breadboard for this due to my extreme lack of electrical engineering understanding and needed a simple solution.

<p align="center"><img width="965" height="528" alt="image" src="https://github.com/user-attachments/assets/3e302e2b-f426-4740-af15-a465420420a7" /></p>

Once the 1.5kΩ resistor has been added, a stripped USB Cable can be connected to the STM32 Device like so.

<p align="center"><img width="800" height="443" alt="image" src="https://github.com/user-attachments/assets/b8d0e844-012f-4089-b158-3c20042f4a82" /></p>

Every physical part of the setup is now complete, and a connection can now be made.

## Usage

This part is fully automated, and assuming that everything in the setup has been completed correctly, all that's left to do is make the connection.

<p align="center"><img width="645" height="240" alt="image" src="https://github.com/user-attachments/assets/ba8055f3-72b9-46e9-8cb3-c8ef79850e5d" /></p>

As per the pre-defined keyboard HIDs, keyboard shortcuts will be utilised to enter command prompt and enter "some evil stuff" into a text file. This was intended to be a non-malicious method to show how any USB device can be modified to enter more or less whatever you'd like.

## Further Study

In the future, I'd like to look into this further. Being very aware of particular computer mice that utilise STM32 Microcontrollers, this makes it an easy next step.

That being said, the read-write lock provides a task of its own to be able to write to the microcontroller to update the firmware to contain a "malicious payload". This can be bypassed with A.) Hardware hacking B.) Reverse Engineering and exploiting a factory firmware updater

The latter of these 2 methods is harder than the former; however, the latter is the only method I know how to do. That being said, it is extremely time-consuming; hence the proof-of-concept test on this repo.

## Authors

* **Logan Sayles** - *Primary Contributer*
