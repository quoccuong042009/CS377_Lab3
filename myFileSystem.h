#pragma once

class MyFileSystem
{

public:
  MyFileSystem();
 
  MyFileSystem(char diskName[16]);

  int create(char name[8], int size);

  int Delete (char name[8]);
  
  int ls();

  int read(char name[8], int blockNum, char* buf[1024]);
  
  int write(char name[8], int blockNum, char* buf[1024]);
  
};
