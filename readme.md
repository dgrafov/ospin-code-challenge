# OSPIN Take Home - Senior Engineer

## Introduction
As a next step, we are excited to ask you to complete a small take home task! This task is designed to be high level and short. We respect your time, and will be assessing it based on general completeness, as opposed to detailed implementation. Please do not spend more than two hours working on this!

As a senior engineer, we expect you to be able to take a rough feature request and flesh it out into a fully fledged, working, maintainable solution. Please feel free to ask those clarifying questions you would have, were this to be presented to you in reality.

## Challenge
For this challenge, we will be emulating a real technical implementation that OSPIN had need for: designing (and minimally implementing) a remote access option for our devices.

With a fleet of devices running bioprocesses around the world, it is important that, at any moment, an OSPIN employee has ssh access to the machine. Assume the following about our architecture and constraints:

- Some of OSPIN's customers are making super top secret stem cell recipes in their attempt to regrow their organs (naturally). As a result, they won't be able to do any NAT configuration, or port forwarding, for the OSPIN device.

- Luckily, the device has unrestricted internet access, which it regularly uses with the MQTT protocol to communicate with the web application. The device can also make http/s requests to the OSPIN server.

- Many OSPIN employees who would like to use this remote ssh access need this option to be as easy as possible.

- Multiple users need to be able to connect to the device at the same time. (Bonus if they can somehow screen-share their ssh session!)

### Architecture
The OSPIN device should build a reverse SSH tunnel to the OSPIN server upon the MQTT request. The payload of a responding MQTT message should contain the number of the server port, which is forwarded to the device.
Then an OSPIN employee could login into the server and use this tunnel to connect to the device using ssh, without the need of the device to have a public IP address. Even more, screen sharing for ssh session can be achieved with the tool `screen` (available on Debian-based systems - I assume that OSPIN device is still based on RPi and therefore has Raspbian or something Debian-based).

The client-side solution consists of two parts. One is a service which must be installed ([this one](https://github.com/jfathman/ssh-tunnel) is used almost as it is for demonstrating the solution) alongside the firmware. See **Device Setup** section of this file for details.
The second part is the firmware program, which handles MQTT messages (out of scope of this solution - I assume it's implemented already and can provide sample implementation for that part upon the request), starts and stops the service the service. See **Firmware** section of this file for details.

### Implementation

#### Server Setup
OSPIN Server requies some additional basic setup:

- a new user (let's call it **ssh-tunnel**) for port-forwarding should be added
- the user should have access to ssh
- the user should not have access to the shell or to super-user privilegies
- ssh config should be changed for that user: disable password authorization, allow only remote tcp port forwarding
- all the ssh public keys of the OSPIN devices should be stored on the server for that user (so that each device could connect without a password)

#### Device Setup
I assume that the firmware is installed and runs with superuser rights.

- auto ssh should be installed
- [ssh-tunnel](ssh-tunnel) script should be installed as a service
- ssh public and private keys should be generated and public key should be copied to the OSPIN server (to ssh-tunnel user's authorized_keys file)

#### Firmware
C++ code is presented in file [main.cpp](main.cpp).
The firmware must be run from a super-user session (to have access to ssh ports).
I saw here two options for implementing the solution: to implement everything inside a firmware program (e.g. using [libssh](https://www.libssh.org/) library) or to use OpenSSH client (via autossh) and call it from C++ code using `system()` function.
I chose the latter approach based on the time given and the fact, that those two tools are well-tested and proven working for this task. The disadvantage of this approach is lack of control (comparing to the first one): e.g. OpenSSH client returns only one error code for everything. So if the functionality provided by those two tools appears to be unsifficient after first prototype testing, I leave the possibility for custom implementation.

Another problem is selection of the port number on the OSPIN server for the tunnel. As the feature is supposed to be used by OSPIN employees, I think it's fair to assume, that 150 ports should be enough for now - roughly 5-10 ports per person at once (newer firmwares can get broader/different port ranges). For the test program I limited the range of ports to try by 10 ports (for demonstration).
Another approach would be to add desired port to the MQTT open-ssh message payload. Then the OSPIN employee would have to check available ports on OSPIN server, or additional implementation is required for the Web app so that it gets the list of free ports.

#### Possible Improvements

- Fully implement establishing of the SSH tunnel in C++ within the client's firmware (will improve possibility to control the behaviour, e.g. error handling)
- With better error handling MQTT response payload can be enriched with more meaningful error messages/error codes.
- Develop more robust port selection strategy
- Investigate security-related configuration of the OSPIN server. I named some basic measurements for **ssh-tunnel** user, however I can imagine, that they are not complete - additional investigation is required.
