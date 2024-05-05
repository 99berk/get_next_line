# Get Next Line

## Introduction

The primary goal of this project is to implement a function called get_next_line, which reads a line from a file descriptor. This project also serves as an opportunity to learn about static variables in C programming.

## Implementation Details

get_next_line.c :
Contains the implementation of the get_next_line function. This function reads a line from the specified file descriptor and returns it. It handles dynamic memory allocation and buffer management to ensure efficient reading of lines.

get_next_line_utils.c :
Provides utility functions required for the implementation of get_next_line. These functions include string manipulation functions like ft_strlen, ft_strdup, ft_strjoin, ft_substr, and ft_free_stash.

get_next_line.h :
Header file containing function prototypes and necessary includes for the get_next_line project. It defines the get_next_line function and declares utility functions.

## Bonus

- Develop get_next_line using only one static variable.
- Allow get_next_line to manage multiple file descriptors simultaneously.
