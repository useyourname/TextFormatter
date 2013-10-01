TextFormatter
=============

Unix-like command line program that formats text (left-align, right-align, center-align, justify)
written in simple procedural messy C++ with terrible variable names.

**instructions:**  
1) Compile and run the program  
2) type in command of the form:  
numberofColumnsPerLine inputTextFileName options  

**options are:**  
`rr`&emsp;&emsp;&emsp;Left-aligned (ragged right; it is the default mode)  
`rl`&emsp;&emsp;&emsp;Right-aligned (ragged left)  
`c`&emsp;&emsp;&emsp;Centered  
`j`&emsp;&emsp;&emsp;right and left justified (space out text so that each line is the same length)  
`f`&emsp;&emsp;&emsp;change print mode to forward  
`r`&emsp;&emsp;&emsp;change print mode to reverse  
`p`&emsp;&emsp;&emsp;print all lines  
`k <k>`&emsp;&emsp;&emsp;print kth line of text  
`s <s>`&emsp;&emsp;&emsp;print lines only containing the specified string in <s>  
`q`&emsp;&emsp;&emsp;Quit program  

**example:**  
created a text file called "text" with the following text:  
"Hello. I am a command line program that formats text.  
Instructions:  
1) Compile and run the program  
2) type in command of the form:  
numberofColumnsPerLine inputTextFileName options"  


**in the terminal:**

    g++ textFormatter.cc -o textJustify  
    ./textJustify    
    50 text j p    
    Hello.  I  am  a command line program that formats  
    text. Instructions: 1) Compile and run the program  
    2)     type    in    command    of    the    form:  
    numberofColumnsPerLine  inputTextFileName  options

