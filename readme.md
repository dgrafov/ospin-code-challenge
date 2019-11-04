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

#### Architecture
Please provide a _high level_ architectural overview of how you would go about implementing this on the firmware/device side of our stack. Use this repository in whatever way you believe is most effective at communicating your thoughts. Please use and edit this README file as the entry point to understanding your implementation.

#### Implementation
Please provide a _minimal_ implementation of how this would work in your language of choice. Your program should represent an application that is running on an OSPIN device.

Assume that, at the start of your application, it has just received an MQTT request for an ssh session that was originally fired from a device fleet management view in a web app. Upon execution, the application should print a JSON payload to the terminal that could theoretically be sent in an MQTT message back to the web application.

Be mindful of your time, and do not implement everything that you may in a real production environment. Instead, implement the minimum, and take the time two tell us what you would expect the branch to need to be considered 'production ready'.

## Submitting
- When complete, please make a PR to this repository and shoot me an email: daniel.seehausen@ospin.de

- _do not_ place your name, or any other identifying information, anywhere in your submission's code or README (in the interest of fairness, we review applications blindly).
