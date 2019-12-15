Features:
- Executing bash commands with n amt of args(as long as each arg is separated by a single space)
ex:(A a1 a2 a3...)

- Executing commands no matter how many trailing spaces are behind or in front of commands
ex:(  A)(A  )( A )

- Executing multiple commands in one line using semicolons
ex:(A;B)

- Redirecting stdin and stdout from or to files
ex:(A < B) (A > B)

- Double redirection(as long as there are only 3 args and they are separated by '<' and '>', in that order)
ex:(A < B > C)

- Piping from a command to a file
ex:(A | B)

- Can cd and exit






Bugs:
- Parser will not split args properly that are separated by multiple spaces

- Parser will not split commands properly that have multiple operators on them
ex: (A||||B) (A;;B)

- Parser does not recognize (<<) or (>>)

- Spamming commands messes up stdout







Functions:

-------char ** parse_args(char * line,char * s,int size);---------
- parses args by a delimiter and returns a split array

Inputs:
char * line: the string to be parsed
char * s: the string with delimiter(s)
int size: the amount of elements in the output array

Output:
char **: array of size 'size', split by the delimiter(s)



-------int count_occurence(char * string, char * c);----------
- counts the amount of times a character appears in a string


Inputs:
char * string: the string to be examined
char * c: the char to be counted(only c[0] counted)

Output:
int: amount of times c[0] appears in string



--------char * replace_char(char * string, char * c, char * r);---------
- replaces every one type of character with another type

Inputs:
char * string: the string to be iterated through
char * c: the char to be replaced(only c[0] compared)
char * r: the char that replaces c(only r[0] compared)

Output:
char*: the same string but with all characters of c[0] replaced with r[0]



-------char * remove_trailing(char * string, char * c);-----------
- removes trailing characters

Inputs:
char * string: the string to be iterated through
char * c: the char to be trimmed(only c[0] compared)

Output:
char*: the same string but with all characters of c[0] at the front and back ends of the string removed



-------int shell();--------
- runs the shell until 'exit' is called, cwd printed, waits for stdin input from user and calls run_line when input is made



------void run_line(char * input);---------
- takes input from shell and parses through the commands and args, calls forkxec to run the command(s)

Input:
char * input: stdin input from shell



------void forkxec(char ** args);---------
- forks and execs a command from run_line

Input:
char ** args: array of strings with a command and its args
