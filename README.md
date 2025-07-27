# Custom Shell Implementation

This project implements a custom shell in C language that mimics basic functionalities of the bash shell while adding some unique features. The shell supports various commands, I/O redirection, piping, background processes, and more.

## Features

### Basic Shell Functionality
- Custom prompt showing username, system name, and current directory path
- Support for executing system commands
- Multiple command execution using ';' separator
- Background process execution using '&' operator

### Built-in Commands

#### `hop` - Directory Navigation
- Changes the current directory
- Supports absolute and relative paths
- Special arguments: `.`, `..`, `~`, and `-`
- Shows full path after changing directory
- Usage: `hop [directory]`

#### `reveal` - List Files and Directories
- Lists files and directories in lexicographic order
- Color-coded output (green for executables, white for files, blue for directories)
- Supports flags:
  - `-l`: Display extra information
  - `-a`: Display all files including hidden files
- Usage: `reveal [flags] [directory]`

#### `log` - Command History
- Displays the last 15 commands
- Commands are stored across sessions
- Usage:
  - `log`: Display command history
  - `log purge`: Clear command history
  - `log execute <index>`: Execute a command from history

#### `proclore` - Process Information
- Displays information about a specified process
- Information includes pid, status, process group, virtual memory, and executable path
- Usage: `proclore [pid]`

#### `seek` - File/Directory Search
- Searches for files/directories in a specified target directory
- Supports flags:
  - `-d`: Search for directories only
  - `-f`: Search for files only
  - `-e`: Execute or navigate to the found item
- Usage: `seek [flags] <search_term> [target_directory]`

#### `activities` - List Running Processes
- Lists all running processes spawned by the shell
- Displays process name, pid, and state
- Usage: `activities`

#### `ping` - Send Signals to Processes
- Sends signals to processes
- Usage: `ping <pid> <signal_number>`

#### `fg` - Bring Background Process to Foreground
- Brings a background process to the foreground
- Usage: `fg <pid>`

#### `bg` - Resume Background Process
- Resumes a stopped background process
- Usage: `bg <pid>`

### Advanced Features
- I/O redirection using `>`, `>>`, and `<`
- Piping capabilities using `|`
- Combined I/O redirection and piping
- `.myshrc` configuration file for custom aliases and functions
- Signal handling (Ctrl+C, Ctrl+D)

## Compilation and Execution

```bash
make
./a.out
```

## Implementation Details
### Input Processing

- Tokenizes input using strtok
- Handles random spaces and tabs
- Processes multiple commands separated by ; or &

### Process Management

- Manages foreground and background processes
- Displays process information on completion
- Tracks process execution time for foreground processes

### File System Operations

- Handles file and directory operations
- Supports relative and absolute paths
- Manages file permissions for I/O redirection

### Signal Handling

- Implements custom signal handlers
- Manages process state changes

## Assumptions and Limitations

- Path/directory names do not contain whitespace characters
- Maximum command history is limited to 15 entries
- Custom commands (hop, reveal, log, etc.) are not supported in background mode
- For I/O redirection, only one input and one output redirection is supported per command

## .myshrc Configuration
- The shell supports a custom configuration file .myshrc that can be used to define aliases and custom functions. The file is loaded at startup and applies the defined aliases and functions to the shell session.
