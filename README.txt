#start server
./sever 

#start client
./client [ip address of a server]  [folder/filename] [folder/filename]…..

EXAMPLE TO START A CLIENT: 

./client 127.0.0.1 file.txt file2.txt 

./client 127.0.0.1 myfolder file.txt myfolder3

*******************************************************************************

Preferably use folders or files in a SERVER.

Can also use like this for the folder one step outside current working directory:

./client 127.0.0.1 ../myfolder

If the program correctly locates the folder or the files you will see output like output of LS command and it will appear  on clients screen”. Server will continue to say running and to terminate it press CTR+C. 

Client will terminate automatically.


