# Example code from *Macintosh C Programming By Example*

*Macintosh C Programming By Example* by Kurt W. G. Matthies and Thom Hogan is a
very useful primer for developing software for the System 6-7 era Macintosh, and
includes example code on a floppy disk that builds up from a trivial "Hello
World" example, to an actually-useful multi-window hex editor.

However, the book and its code date back to 1991, and were written for the
Symantec THINK C development environment, and as a result it is not
straightforward to build this code under modern tools such as
[Retro68](https://github.com/autc04/Retro68) or even later versions of Apple's
MPW development environment.

This repo contains the example projects from the book, restructured and modified
to build under [Retro68](https://github.com/autc04/Retro68). The initial commit
made to this repo contains the code as-is, so that the changes I made are
documented in the commit history.

The changes are as follows:

- Converting source file encoding from MacRoman with CR line breaks, to UTF-8
  with LF line breaks.

- Adding Toolbox `#includes` to source files (THINK C included all Toolbox
  headers in a compiler preamble.)

- Writing equivalents for missing THINK C helper functions and macros (see
  `ThinkHelpers.c` and `ThinkHelpers.h`).

- Decompiling resource files (binary resource forks only usable on Macintosh
  systems) to text-based `Rez` format.

- Adding a Retro68 `cmake` build system.

- Fixing bugs found in the original code (!).

## Descriptions of example applications

### Chapter 4: Hey Mac

A minimal "Hello World" program that creates a window on the screen and draws
some text to it.

### Chapter 6: MiniGeneric

A simple single-window application with menus and dialog boxes.

### Chapter 7: MultiGeneric

An expanded version of MiniGeneric that supports multiple windows.

### Chapter 8: NonGeneric

A further-expanded version of MultiGeneric that demonstrates scrolling.

### Chapter 9: Loser

A utility to set and clear the "invisible" file attribute, illustrating how to
work with the filesystem, and how to use `DialogHook` functions to extend the
standard system file dialog boxes.

### Chapter 11: Browser

A simple file viewer application based on the framework laid out in
MultiGeneric. Can view the data and resource forks as files either as text, or
as a hex-dump.

## Building

### Retro68

From the root of this repository:

```bash
RETRO68_HOME=$HOME/Retro68-build # or wherever you installed Retro68 to
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$RETRO68_HOME/toolchain/m68k-apple-macos/cmake/retro68.toolchain.cmake
make
```

## Bugs

A number of bugs came to light while trying to get these projects to build -
I've tried to fix the ones that caused build failures, egregious compiler
warnings, or crashes, but there are probably a few left in there.

## Ownership

I do not claim any ownership over this code, but since the book is long out of
print and programming textbooks for 30+ year old computers aren't exactly
commercially viable these days, I don't feel too bad about distributing this
code. If whoever the current copyright owner is, wants it taken down, I'll
oblige, but keep in mind that this book and an archive of the accompanying disk
are readily available all over the retrocomputing web.
