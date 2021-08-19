## 42-minitalk
> ![Peers](https://img.shields.io/badge/peers-125-brightgreen)

# About
> The goal of this project is to code a server and client that can talk to each other using `UNIX` signals

# Mandatory
- [x] Code `server` & `client` executables
- [x] `client` has to communicate a string passed as a parameter to the `server` (referenced by it's process ID) and the `server` has to display it
- [x] Use `SIGUSR1` & `SIGUSR2` signals ONLY

# Bonus
- [x] Add reception acknowledgement system
- [x] Support `Unicode` characters

# Allowed Functions
- `malloc`
- `free`
- `write`
- `getpid`
- `signal`
- `sigemptyset`
- `sigaddset`
- `sigaction`
- `pause`
- `kill`
- `sleep`
- `usleep`
- `exit`
