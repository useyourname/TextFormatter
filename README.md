TextFormatter
=============

Unix-like command line program that formats text (left-align, right-align, center-align, justify)

**Instructions:**  
1) Compile and run the program  
2) type in command of the form:  
numberofColumnsPerLine inputTextFileName options  

**options are:**  
*rr*     Left-aligned (ragged right; it is the default mode)  
*rl*     Right-aligned (ragged left)  
*c*      Centered  
*j*      right and left justified (space out text so that each line is the same length)  
*f*      change print mode to forward  
*r*      change print mode to reverse  
*p*      print all lines  
*k <k>*  print kth line of text  
*s <s>*  print lines only containing the specified string in <s>  
*q*      Quit program  

**example:**  
created a text file called "text" with the following text:  
"Hello. I am a command line program that formats text.  
Instructions:  
1) Compile and run the program  
2) type in command of the form:  
numberofColumnsPerLine inputTextFileName options"  


in the terminal:  
  g++ textFormatter.cc -o textJustify  
  ./textJustify  
  50 text j p  
  Hello.  I  am  a command line program that formats  
  text. Instructions: 1) Compile and run the program  
  2)     type    in    command    of    the    form:  
  numberofColumnsPerLine  inputTextFileName  options  

