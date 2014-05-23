wsss
====

Web Site Slide Show - Display a series of web sites with timed display duration and refresh intervals. Written in QT

WSSS is a Qt based program that will display a series of web pages for a specified duration. 
It is intended to be used on a main office screen.

WSSS was developed by me to show the weather and pilot status for our helicopter company.
This allows the pilots to easy look up from their desks and keep informed as to what the weather is doing.

There is no defined limit to the number of sites to show. 
However, You may find that anything more than 8-10 tends to take too long to cycle round. It does depend on the content you wish to show.

The URL is a standard http web address. If you want to load from the local PCs drive the file:// type url works. 

The timers in the code work in milliseconds so all values are given in milliseconds.

ShowTime is the time in milliseconds to show the page to the user
RefreshTime is the time in milliseconds to wait before refreshing the web page. This helps in reducing the amount of data the program consumes.

Each web page will have its own optimum size but may not visually work on the screen you are using.
You are able to specify a ZoomRatio to get the page to look right.  

The list of pages to show and the display properties are kept in a text file that uses the JSON format.
It is a very simple way of formatting the data without having to get too clever.

If no file is specified in the command line of the program, the program will attempt to load a file called “settings.json” in the programs base directory. If it cant find that file, it will load a set of dummy sites.  


Keyboard Navigation

	Right Arrow: Advance to next page
	Left Arrow: Go back to previous page
	Up and Down Arrow: Scroll the page up and down
	P: Pause the the page
	ESC or F11: Toggle between full and normal screen.
	F2: Zoom in 
	F3: Zoom Out
	F5:  Reload the page



Code

The code uses the QT C++ library. It should build and run on any OS platform. 
That's the claim Qt makes but there are always problems.
 
The main reason for using QT is that I can use WebKit Widgets to show the web pages – same core code that chrome uses. 

Qt also has plenty of timers that I make use to control the duration and refresh times of the pages.
