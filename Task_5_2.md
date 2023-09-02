# Task_5_2
## Description:
This file contains the documentation of some self-tested basic Linux commands with some flags.
The following commands are tested upon a sandbox due to the current technical issues with Virtual Machine.
All of these commands are the basic ones required for Linux Navigation and files/directories handling.

## Commands:
### ls:
	This command is used to list the files and directories in the current working directory.
#####	syntax:
		ls [option]...[file/directory]
#####	flags:
		-l: used to list the files in more details, including permissions, file type, size, owner, group and the last date modified.
		-a: used to list additional hidden files.

### cd: 
	This command is used to change the current working directory.
#####	syntax:
		cd [options]...[directory]
#####	flags:
		~: can be used to go to the root directory.
		..: go to the parent directory of the current.

### pwd:
	This command is used to print the current working directory.
#####	syntax:
		pwd [options] -> No parameters

### cal:
	This command is used to print the calendar date.
#####	syntax:
		cal [options] -> No parameters

### echo:
	This command is used to print a given string or expansion into stdout/stderr by default.
	Output can be redirected to a file.
#####	syntax:
		echo [option]...[string]

### chmod:
	This command is used to change the permissions of a file.
#####	syntax:
		chmod [option]...MODE...File
#####	use:
		MODE: u | a | g | o + x | r | w
		Or Binary representation of the permissions.

### vi/vim:
	This is a tect editor that opens a file in a terminal in order to write in it.
#####	syntax:
		vim [option]...file

### touch:
	This command is used to create a file in the given path.
#####	syntax:
		touch [option]...file

### mkdir:
	This command creates a directory.
#####	syntax:
		mkdir [option]...directory

### rmdir:
	This command removes a directory with all its subfiles.
#####	syntax:
		rmdir [option]...directory

### rm:
	This commands deletes a file.
#####	flags:
		-r: can be added to remove a directory recursively with all its files and subdirectories.
#####	syntax:
		rm [option]...file

### mv:
	This command is used to move a file from its location to another directory,
	or used to rename a file.
#####	syntax:
		mv [option]...Source Destination
		Source and Destination might be either files or directories depending on usage.

### cp:
	This command is used to copy a file into another file.
#####	syntax:
		cp [option]...Source Desination
		Source and Destination might be either files or directories depending on usage.

### grep:
	This commang is used to get all the lines containing matching strings to a regex in a file.
#####	syntax:
		grep [option]...Patterns [file]

### wc:
	This command is used to get the size of a file in bytes, count of words, number of lines.
#####	flags:
		-l: used to output only the number of lines in a file.
		-w: used to output only the word count in the file.
		-m: used to output the number of bytes in the file.
		-c: used to output the number of characters in a file.
#####	syntax:
		wc [option]...[file]

### cat:
	This command is used to print the contents of a file.
#####	flags:
		-n: number the lines in the file.
		-b: number the non-empty lines in the file.
#####	syntax:
		cat [option]...[file]

### head:
	This command is used to print the first 10 lines of a file by default.
#####	flags:
		-n: prints a given number of lines from the begining instead.
#####	syntax:
		head [option]...[file]

### tail:
	This command is used to print the last 10 lines of a file by default.
#####	flags:
		-n: prints a given number of lines from the end instead.
#####	syntax:
		tail [option]...[file]
