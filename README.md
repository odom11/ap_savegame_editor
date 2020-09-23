# ap_savegame_editor

this is a savegame editor for alpha protocol. It allows changing the following aspects of a savegame
* money
* number of free stat points
* gadgets (EMP grenades etc)
* ammunition
* number of suave/aggressive/professional dialog choices (important for killing Marburg in Rome)

The same could be achieved loading the file into a hex editor, but I found this more convenient.

~**THE PROGRAM CRASHES ON A NEWLY CREATED SAVE. YOU HAVE TO FINISH TRAINING AT LEAST AND GO TILL SAUDI ARABIA**~

The software was created with Visual Studio 2019 using Qt5. It can be freely distributed or modified.

# How to obtain it

go to [releases](https://github.com/odom11/ap_savegame_editor/releases) and download the zip files. If you want to build
it from scratch, clone the repository, use visual studio to build the program and qt tools to import all the dependencies.

# How to use it

MAKE A BACKUP COPY OF YOUR SAVEGAME FIRST IN CASE ANYTHING GOES WRONG! 

The rest is self-explanatory. Run the program, click on the folder button to edit a new savegame. A file selection menu opens in %USERDIRECTORY%\Documents\Alpha Protocol\Checkpoints. The savefiles are the ones ending with sav. 

In case of an error, contact me with a problem description (What have you done - What did you expect - What happened) and I will do my best to fix the issue.
