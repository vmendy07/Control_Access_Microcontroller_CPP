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

## Hardware Requirements

- Microcontroller (compatible with mbed platform)
- Keypad
- LCD display
- Relay (for door control)

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
  
## Flowcharts

![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/a2927b80-260b-4733-882c-9c64682e8649)

## ComparePassword Function

The ComparePassword function is a critical component of the access control system. It compares the input password with the stored password to determine if access should be granted.
![image](https://github.com/vmendy07/Control_Access_Microcontroller_CPP/assets/165968387/666d5eca-1e73-4cc5-a881-c6f28b03cdc4)



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

[Specify your license here]
