Lab 1 README ECE 13 F24 

Author: <Sean_Manger> (smanger@ucsc.edu)

Collaborators: I did not collaborate with anyone for this Lab. All code is my own orignal work. I did however discuss the lab with / assist Donny Tang & Nic Jorgenson.

Part 0 Hello World on a Terminal & Embedded:

For Part I we were asked to run a simple "Hello World!" program using the provided code on both the terminal & in an embedded enviroment on our Nucleo board. Here are my results:

Terminal:

![Alt text](<Screenshot 2024-09-30 202729.png>)

Embedded:

![Alt text](<Part 0 Hello World.jpeg>)

Part 1 Sorting An Array:

For Part 1, following the provided directions I set a breakpoint and stepped through the array and recorded as it was sorted and changed. I recorded what I saw under "Part 1 Values". After this, the debugger continued to the final print statement after the for loop and the final value of the sorted array was displayed. Which I also recorded down below.

Part 1 Values (Using Debugger): 

[45,207,70,41,4] // i = 0
[45,207,70,41,4] // i = 1
[45,207,70,41,4] // i = 2
[45,70,207,41,4] // i = 3
[41,45,70,207,4] // i = 4

Final Result (After exiting Breakpoint): 
[4, 41, 45, 70, 207]

I also took the following two screenshots for Part 1 to further verify functionality: 

![alt text](<Part 1 Debugger.jpeg>)

![alt text](<Part I Final Result.jpeg>)


Part 2 Temperature Conversion Tables:

For Part 2, I followed the provided instructions and wrote the desired code for both the Farenheit to Celcius Table & Kelvin to Farenheit Table. I also set the desired character widths and precisions for each table to what was specified in the lab document. Here is a picture of my results which match what was expected in the lab doc:

![Alt text](<Part 2 Tables.jpg>)

Part 3 OLED Screen Extra Credit:

For Part 3 we were asked to use the oled screen on our Nucleo board to display static text reading "Hello World!". However, I thought that this was rather unintersting. So, I modified the code to first display "Hello World!" for 3 seconds followed by "ECE 13!" for another 3 seconds before returning to the inital "Hello World!" repeatedly in a loop. Here are pictures of my results:

![Alt text](<Part 3 OLED.JPG>)

![Alt text](<Part 3 OLED-2.JPG>)


This concluded Lab 1.

Personal Comments & Observations:

Overall, I thought this was an enjoyable lab. It served as a good introduction to the course and the devolopment enviroment we will be using throughout. I thought the hardest part of this lab was just getting everything setup and working properly. One problem I encountered was installing the proper drivers on Windows. However, I thankfully found the files on STM's website. Besides that the actual coding part of the lab was pretty straightforward.






