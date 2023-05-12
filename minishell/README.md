# **minishell**
This project was graded <strong>101/100</strong>.

## 📝 **Authorship**

- [**João Caetano**](https://github.com/jscaetano) **- joacaeta**
- [**Nuno Jesus**](https://github.com/Nuno-Jesus) **- ncarvalh**

## 📒 **About**
Ever thought about how shells work? How commands are executed? How your input is decyphered into commands and arguments? This is a chance of learning about input parsing, processes, signals, pipelines and more!

The implementation of this project is based on the original ``Bourne-Again Shell (BASH)`` although some details were customized or not implemented (e.g. unclosed pipes).

## **Mandatory Part**

<div align=center>
	
![minishell](https://github.com/jscaetano/minishell/assets/93390807/2559e36d-9d22-4b72-81a5-81983a76f8bf)
	
</div>

Here's a list of features our minishell has:

	- A prompt with powerlevel10k inspired theme;
	- Lexer and parser for the input;
	- A working history;
	- Builtin commands such as echo, cd, pwd, export, unset, env and exit;
	- Signal handling for ctrl-C, ctrl-D and ctrl-\\;
	- Pipelining of commands;
	- Redirection of input and output;
	- Environment variables;
	- Direct declaration of temporary environment variables (A=3);
	- Expansion of environment variables ($HOME, $PWD, etc) and exit status ($?);

## 🚨 **Disclaimer**
At 42, the C projects are built following a bunch of rules that enforce good coding style. Some of them are:

	- No for, do while, switch, case or goto are allowed
	- No more than 25 lines per function and 5 functions per file
	- No assigns and declarations in the same line (unless static)
	- No more than 5 variables in 1 function
	... 

## 🔧 **Implementation**

<table align=center>
	<thead>
		<tr>
			<th>File Name</th>
			<th>Functionality</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><strong>libft/</strong> </td>
			<td>Contains 42 library functions and a few others added in the project</td>
		</tr>
		<tr>
			<td><strong>srcs/</strong> </td>
			<td>Contains all the source files</td>
		</tr>
		<tr>
			<td><strong>srcs/commands/</strong> </td>
			<td>Contains all the builtin commands</td>
		</tr>
		<tr>
			<td><strong>srcs/debug/</strong> </td>
			<td>A file with debugging helper functions</td>
		</tr>
		<tr>
			<td><strong>srcs/executor/</strong> </td>
			<td>Pre and post execution of processes handling</td>
		</tr>
		<tr>
			<td><strong>srcs/parser/</strong> </td>
			<td>Lexeme list and AST formation when input is received</td>
		</tr>
		<tr>
			<td><strong>srcs/signals/</strong> </td>
			<td>Has the signal installers and signal handlers</td>
		</tr>
		<tr>
			<td><strong>srcs/utils/</strong> </td>
			<td>Contains all the utility functions</td>
		</tr>
		<tr>
			<td><strong>input.c</strong> </td>
			<td>Infinite while loop to read input and where the main stages of input parsing are called</td>
		</tr>
		<tr>
			<td><strong>main.c</strong> </td>
			<td>Entry point of the program</td>
		</tr>
	</tbody>
</table>


## 📦 **Compilation**
To compile minishell you should run `make` in the terminal.

This rule will generate a `minishell` file, which is the zipped version of all the object files. To launch the executable you should follow this syntax...

```sh
$ ./minishell
```

## 💫 **Testing**

This project was tested using self-made tests and other colleagues pressure tests.


## 📞 **Contact me**

Feel free to ask me any questions through Slack (**ncarvalh**).
