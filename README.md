# salahtime

salahtime is a small command line application written in C for Linux and BSD that displays the Islamic prayer times for Europe/Copenhagen.

salahtime uses a multidimensional array to store the time table and the table can easily be substituted for another if needed.

## Changing city
It can simply be done by creating a file named in the format: `region_city.c` (you can copy that file to cities folder as well, and make a pull request to add the city in the main repo https://github.com/unixsheikh/salahtime).
Then in the main directory of this git repo, enter something like:
`sed -i 's/europe_copenhagen/<your region>_<your_city>/g' salahtime.c`
So, if for example your city is Riyadh in Saudi Arabia, your data file should be named `asia_riyadh.c` and the command you enter has to be:
`sed -i 's/europe_copenhagen/asia_riyadh/g' salahtime.c`

## Installation

Clone this repository or download the zip version.

```
$ git clone https://github.com/unixsheikh/salahtime
```

The Makefile uses clang, but if you want to use gcc instead just change the `CC` variable to gcc, then run the make command:

```
$ cd salahtime
$ make
```

Or:

```
$ make CC=gcc
```

Then simply copy the `salahtime` executable to somewhere in your home directory and add that directory to your `$PATH` variable.

The following example uses the Bash shell.

```
$ mkdir $HOME/bin
$ cp -f salahtime $HOME/bin/
```

Edit `.bashrc` in your home directory with your favorite text editor and add the "bin" folder to your $PATH variable.

```
export PATH=$HOME/bin:$PATH
```

Remember to reload bash.

```
$ exec bash
```

And if you need to uninstall salahtime just remove it from the "bin" folder.

If, however, you want to, you can also install this system-wide (requires root).
```
$ make CC=gcc
$ sudo mkdir -p /usr/local/bin
$ sudo cp -f ./salahtime /usr/local/bin/
```

See the man page for usage information.
For an ad-hoc way of reading the manpage, inside the main directory of salahtime:
```
$ man ./salahtime.1
```

To get the manpage of salahtime from anywhere:
```
$ sudo mkdir -p /usr/local/share/man/man1/
$ sudo cp -f ./salahtime.1 /usr/local/share/man/man1/
$ man salahtime
```
