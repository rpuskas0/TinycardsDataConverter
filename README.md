# Tinycards Data Converter
### What is it?
This is a simple program for converting the csv file you get after exporting your decks from Duolingo's Tinycards.

### Why was it created?
Because the original Tinycards csv format is somewhat unique, which makes it hard to use with other programs.

### What can the original file be converted to?
There are several output formats available:

- _JSON_: contains cards + deck metadata
- _XML_: contains cards + deck metadata
- _CSV_ : contains only cards for simple importing into MS Excel (see note #2)

Additionally, there is an option for controlling the number of output files:

- _1 File / All decks_: a single file contains all the decks
- _1 File / 1 Deck_: each deck is put into its own separate file

### Is it a feature complete program?
Definitely not, this is the bare minimum. Some of the possible missing features include:

- Input file checking: right now, the program will simply assume it is OK, no checks whatsoever are performed. 
- Naming files based on deck metadata: could be useful, but not worth the time for implementing.
- Exporting decks based on metadata: same as previous.
- Choosing CSV delimiter character: same as previous.

### Notes
1. Make sure you do not have double quotes ( " ) in your cards' "Front" or "Back" section, as it _will_ prevent the program from parsing your decks properly.
2. Although it will not affect the conversion process itself, make sure you do not have semicolon ( ; ) characters in your cards' "Front" or "Back" section, as it might interfere with importing into MS Excel.
3. The code is not perfect, so if you have any thoughts on it, please feel free to comment.

### Building
The simplest way to do it is with Qt Creator (project file is included).

### License and Copyright
Copyright (C) Robert Puskas
Program licensed under GPLv3

