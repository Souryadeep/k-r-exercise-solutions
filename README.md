# The C Programming Language: K&R; Exercise solutions

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)  

*Solved by*: Souryadeep  
*Source code*: Folders in the repo are named as per the problem number in the book  
*Text Book*: [Link to text](https://kremlin.cc/k&r.pdf)

## Usage  

**Install**: gcc, g++, make on your system.  

Note: Installing gcc is sufficient to compile the code in this repo. You may use the base Makefile template in the repo to compile the code. You would need to install make on your system in this case.  


	- Linux:  

		- sudo apt update  
		- sudo apt install build-essential  
		- sudo apt-get install manpages-dev  

	- Windows:  

		- Use the following link to download the exe from the MinGW temporary page   
		- https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download  
		- Run the executable, and all will be setup  

**Optional**: If you wish, you could work on solving multiple memory leaks in the code. For this, use Valgrind with the compiled executable, to tell you how many leaks exist in the code. **Hint**: the leaky codes are the ones where I used malloc and didn't free at the end of the code. 

Compiling the code on linux command line/windows command prompt:  

	- gcc -g -Wall programname.c -o test  
	- -g flag is a debug flag  
	- -Wall turns on warnings    
	- -o test names the executable as test. If you do not use this, a.out executable is generated  


Executing the code:   

	- Linux: ./test (run this from the directory test is generated in)    
	- Windows: test.exe (same comment as above)  

Using Valgrind:  

	- Only on linux: valgrind --leak-check=yes ./test  

If you are unable to run the code, please feel free to reach out to me in the comments of this repo.  


## Note
Each problem can have multiple solutions. I have tried to use the best practices from K&R in my solutions.
In case you have any doubts, please feel free to reach out to me via email: souryadeep.sen@columbia.edu
Please submit a pull request if you see some issue with the code/feel it can be improved.

I am self taught in C programming and have been using 📖 The C Programming Language 2nd edition by K&R for my reference. I found this to be a very effective book to 👨‍🎓 learn from and recommend to anyone looking to learn the C language. The exercise problems are very important to better your understanding of concepts, so attempt them yourselves. Make sure to type 💻 your code, not copy and paste. This is beneficial, since you learn syntax better this way.
