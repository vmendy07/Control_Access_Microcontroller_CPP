# Control_Access_Microcontroller_CPP

This project implements a secure access control system using a microcontroller. It provides two levels of access control: a lower level for normal users to operate a relay (open a door) and a higher level for supervisors to set entry codes for both levels of access control.

## Features

- Written in C++ for microcontroller implementation
- Permanent storage of user codes in flash memory
- Robust user input for code entry
- LCD display for user feedback and last 4 key entries
- Two-level access control:
  - Lower level: Normal user access to operate relay
  - Higher level: Supervisor access to set entry codes

## Hardware Specifications

This access control system is designed with the following hardware specifications:

1. **Processor**: Based on the MKL46Z processor from the Mbed platform.

2. **Power Supply**: 
   - Mains operated
   - Backup power for 30 minutes of operation during power failure

3. **Memory**: 
   - Permanent storage for user codes (utilizing on-chip Flash memory)

4. **User Interface**:
   - Robust keypad for code entry
   - LCD display for messages and last 4 key entries

5. **Output**:
   - Relay output for standard door-strike mechanism operation

6. **Design Considerations**:
   - Simple and ergonomic circuit design
   - Optimized for volume production
   - Compatible for installation anywhere in the UK

7. **Durability**:
   - Robust construction for reliable operation in various environments

These specifications ensure that the access control system is reliable, user-friendly, and suitable for widespread deployment in various settings across the UK. The use of the MKL46Z processor, combined with permanent storage and a backup power system, provides a solid foundation for a secure and dependable access control solution.

## High Level Hardware Design

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/0fc2d871-ee4a-4401-84ec-2b542bae8989)

## Hardware Schematic

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/1746a7c3-07f1-450d-ad85-7259b83c41cd)


## Mbed MKL46Z Microcontroller

This project utilizes the Mbed MKL46Z microcontroller, which is based on the ARM Cortex-M0+ processor. The MKL46Z is well-suited for this application due to its:

- Low power consumption: Ideal for continuous operation in an access control system.
- Integrated Flash memory: Used for permanent storage of user codes.
- Sufficient I/O ports: Allows easy interfacing with the keypad, LCD display, and relay.
- Mbed OS compatibility: Enables the use of Mbed libraries for rapid development.

## Key features of the MKL46Z:

![frdm-kl46z-components](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/87b39ba7-4ee2-469c-9b8e-b64663a18cba)

- Flash memory operations: Utilized for storing and retrieving passwords securely.
- GPIO pins: Used for interfacing with the keypad and controlling the LCD display.
- Timer functionality: Implemented for creating delays and managing display updates.
- Low-power modes: Employed to optimize energy consumption during idle periods.

The MKL46Z's capabilities allow for efficient implementation of the access control logic, secure storage of passwords, and responsive user interface, making it an excellent choice for this security-focused application.

## Power Supply Unit Schematic

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/08d48565-5446-4085-a287-2072de226768)

## Battery Charger Unit

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/6b27a2ae-4373-4e5d-9ede-5487ba294496)

## Relay Unit

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/26a10f65-0731-4f75-924d-238349348022)

## LCD Unit

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/5656bc7c-615b-436b-bf46-74397c84a35b)

## Keypad Unit

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/055c7661-f691-4170-b1f2-056f42c6d1b2)

## Crystal Clock Unit

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/7717fd9b-789e-4515-b66d-92ec26ad4ea6)

## Capacitor Resovoir

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/7c5cff1d-2139-4260-9298-4ea9cba03093)


## Software Description

The software follows this general flow:

1. Initial setup: Prompts for admin password
2. Operational phase: Displays "Enter Code" message
3. Code entry and validation:
   - Checks against User Passcode (Lower Level)
   - If match, unlocks device
   - If no match, checks against Admin Passcode (Higher Level)
4. Admin access:
   - Option to change User or Admin passcode
   - Displays confirmation messages

The system is designed to operate continuously, returning to the "Enter Code" prompt after each interaction.

## Key Components

- `Keypad`: Handles user input
- `SLCD`: Manages LCD display
- `FlashIAP`: Handles flash memory operations for permanent code storage
- Password management functions:
  - `ChangePassword()`
  - `GetPassword()`
  - `ComparePassword()`
- `displayMessage()`: Handles flashing LCD messages
- `saveFlash()` and `loadflash()`: Manage password storage in flash memory
  
## General Flowchart

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/c7e819e8-9bba-4c0c-a1e2-3e031d7adb23)


## ComparePassword Function Flowchart

The ComparePassword function is a critical component of the access control system. It compares the input password with the stored password to determine if access should be granted.

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/535e1600-b840-4929-b898-96c6f8df90f0)

## Setup and Usage

1. Flash the code to your compatible microcontroller
2. On first run, enter the initial admin password
3. Use the keypad to enter access codes:
   - 8-digit code for normal access
   - Admin code for supervisor functions

## Security Considerations

- Uses 8-digit codes for increased security
- Passwords are stored in flash memory
- Different access levels for users and administrators

## Future Improvements

- Implement timeout for failed attempts
- Add logging functionality
- Integrate with external systems (e.g., network-based access control)

## Contributing

Contributions to improve the system are welcome. Please submit pull requests or open issues to discuss proposed changes.

## License

