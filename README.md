# Mathematical-Expression-Calculator
**This program evaluates complex arithmetic expressions with binary and unary operations, as well as with pre-defined or yet to be defined variables.**  
  
Data Structures Used:
- Vectors (Standard Template Library)  
  
This program provides three **key functionalities**:  
- **Full-Word-Search**: program returns whether a user-provided word is found in the input dictionary. (e.g. figs)
- **Prefix-Search**: program lists all words in the input dictionary that start with a user-provided prefix. (e.g. hu*)
- **Wildcard-Search**: program listd all the words of the dictionary that match the search-string up to one character. (e.g. ke*tle)

Program can be invoked using:  
mymachine-promt >> ./mydictionary -d <dictionaryFile> -l <MaxNumOfWordsInOutput>

where...
- **-d** is the flag indicating that the lexeme proceeding it is the file name of the dictionary to be used.
- **-l** is the flag indicating that the number proceeding it is the maximum number of results to be outputted.  
  
At the start of the program, the user is presented with a prompt.
