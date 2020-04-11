# rgrep
a simple, restricted grep utility. rgrep is “restricted” in the sense that the patterns it matches only support a few regular operators (the easier ones).

grep is a UNIX utility that is used to search for patterns in text files. It’s a powerful and versatile tool: rgrep, while simplified, is still useful.

The way rgrep is used is that a pattern is specified on the command line. rgrep then reads lines from its standard input and prints them out on its standard output if and only if the pattern “matches” the line. For example, we can use rgrep to search for lines that contain text file names that are at least 3 characters long (plus the extension) in a file like the following:
# so you can see what lines are in the file:
$ cat testin

a.out
hello.txt
world.pdf
hello_world.txt
nope.pdf
.txt

$ ./rgrep ‘.\.txt’ < testin

hello.txt hello_world.txt

rgrep was given the pattern ".\.txt"; it printed only the lines from its standard input that matched this pattern.

To compile the code, download it and navigate to the working directory. Open a terminal and run `make`.
To run a against a particular pattern, run `./rgrep pattern` 
