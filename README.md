# ap_savegame_editor

this is a savegame editor for alpha protocol. It allows changing the following aspects of a savegame
* money
* number of free stat points
* gadgets (EMP grenades etc)
* ammunition

The same could be achieved loading the file into a hex editor, but I found this more convenient.

**THE PROGRAM CRASHES ON A NEWLY CREATED SAVE. YOU HAVE TO FINISH TRAINING AT LEAST AND GO TILL SAUDI ARABIA**

The software was created with Visual Studio 2019 using Qt5. It can be freely distributed or modified.

# How to obtain it

go to [releases](https://github.com/odom11/ap_savegame_editor/releases) and download the zip files. If you want to build
it from scratch, clone the repository, use visual studio to build the program and qt tools to import all the dependencies.

# How to use it

Should be pretty self-explanatory. Run the program, click on the folder button to edit a new savegame. This should open in %USERDIRECTORY%\Documents\Alpha Protocol\Checkpoints. The savefiles are the ones ending with sav (duh...). If it isn't there, I am sorry. 
