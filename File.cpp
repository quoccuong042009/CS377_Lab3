

#include <stdio.h>
#include <unistd.h>
# include <stdlib.h>
#include <fstream>
#include <queue> 
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sstream>
using namespace std;
char disk[16];
fstream *myfile;

class MyFileSystem
{
public:
	int fd;
  MyFileSystem(char diskName[16])
  {
    // open the file with the above name
    // this file will act as the "disk" for your file system
    printf("Openning Disk %s\n",diskName );
    if(disk_exist(diskName)){
    myfile = new  fstream;
    myfile->open (diskName, ios::out | ios::app | ios::binary);
   	printf("File Exist\n");
   	int i=0;
   	for(i=0;i<16;i++)
   		disk[i]=diskName[i];
   }
  }


  bool disk_exist(const char diskName[16])
{
    std::ifstream indisk(diskName);
    return indisk.good();
}

  int create(char name[8], int size)
  { //create a file with this name and this size

    // high level pseudo code for creating a new file

    // Step 1: Check to see if we have sufficient free space on disk by
    //   reading in the free block list. To do this:
    // Move the file pointer to the start of the disk file.
    // Read the first 128 bytes (the free/in-use block information)
    // Scan the list to make sure you have sufficient free blocks to
    //   allocate a new file of this size
  int sucess =0;
    char * memblock;
  int count = size;
    memblock =  (char *) calloc(128,sizeof(char)); 
    fstream file (disk, ios::in|ios::out|ios::binary|ios::ate);
    file.seekg (0,file.beg);
    file.read (memblock, 128);
    int i=0;
    std::queue<int> allocatedblockList;
    for (i=1 ; i<128 ; i++)
    {
     // printf("pass for loop\n" );
      if(size<=0)      // finish allocate blocks
        break;
      if(memblock[i]==0){
         allocatedblockList.push(i);
         memblock[i]=1;
         printf("allicated block\n" );
         size--;
       }
    }
     if(size==0)
        sucess=1;
      else
      {
        while(allocatedblockList.size()!=0){
          memblock[allocatedblockList.front()]=0;
          allocatedblockList.pop();
        }
      }
    file.seekp (0,file.beg);
    file.write (memblock, 128);
   // file.close();
    
    // Step 2: we look for a free inode on disk
    // Read in an inode
     int index =0;
   //  int can_create =0;
     while(index <=15){
     char *inodeblock =  (char *) calloc(48,sizeof(char)); 
     file.seekg (128+index*48,file.beg);
     file.read (inodeblock, 48);

 //    // Check the "used" field to see if it is free
      if(inodeblock[47]==0){
      //	can_create=1;
      inodeblock[47]=1;
     // copy name to name file
     for(i=0;i<8;i++)
      inodeblock[i]=name[i];
    // copy the size to size file
     inodeblock[11]=count;
     int blockindex=12;
      while(allocatedblockList.size()!=0)
      {
        printf("Pass here\n");
         inodeblock[blockindex]=allocatedblockList.front();
         blockindex++;
         allocatedblockList.pop();
      }

      file.seekp (128+index*48,file.beg);
      file.write (inodeblock, 48);
      file.seekg (128+index*48,file.beg);
      file.read (inodeblock, 48);
      for(i=0;i<8;i++)
       printf("%c",inodeblock[i] );
      	break;
      }
      else
        index++;
  }
 //    // If not, repeat the above two steps until you find a free inode

 //    // Set the "used" field to 1

    // Copy the filename to the "name" field
    // Copy the file size (in units of blocks) to the "size" field

    // Step 3: Allocate data blocks to the file
    // for(i=0;i<size;i++)
      // Scan the block list that you read in Step 1 for a free block
      // Once you find a free block, mark it as in-use (Set it to 1)
      // Set the blockPointer[i] field in the inode to this block number.
    // end for

    // Step 4: Write out the inode and free block list to disk
    // Move the file pointer to the start of the file 
    // Write out the 128 byte free block list
    // Move the file pointer to the position on disk where this inode was stored
    // Write out the inode
   file.close();  
  } // End Create

 

  int Delete(char name[8])
  {
    // Delete the file with this name

    // Step 1: Locate the inode for this file
    // Move the file pointer to the 1st inode (129th byte)
    // Read in an inode
    // If the inode is free, repeat above step.
    // If the inode is in use, check if the "name" field in the
    //   inode matches the file we want to delete. If not, read the next
    //   inode and repeat

    // Step 2: free blocks of the file being deleted
    // Read in the 128 byte free block list (move file pointer to start
    //   of the disk and read in 128 bytes)
    // Free each block listed in the blockPointer fields as follows:
    // for(i=0;i< inode.size; i++) 
      // freeblockList[ inode.blockPointer[i] ] = 0;

    // Step 3: mark inode as free
    // Set the "used" field to 0.

    // Step 4: Write out the inode and free block list to disk
    // Move the file pointer to the start of the file 
    // Write out the 128 byte free block list
    // Move the file pointer to the position on disk where this inode was stored
    // Write out the inode

  } // End Delete


  int ls()
  { 
    // List names of all files on disk

    // Step 1: read in each inode and print
    // Move file pointer to the position of the 1st inode (129th byte)
    // for(i=0;i<16;i++)
      // Read in an inode
      // If the inode is in-use
        // print the "name" and "size" fields from the inode
    // end for

  } // End ls

  int read(char name[8], int blockNum, char* buf[1024])
  {
    // read this block from this file

    // Step 1: locate the inode for this file
    // Move file pointer to the position of the 1st inode (129th byte)
    // Read in an inode
    // If the inode is in use, compare the "name" field with the above file
    // If the file names don't match, repeat

    // Step 2: Read in the specified block
    // Check that blockNum < inode.size, else flag an error
    // Get the disk address of the specified block
    // That is, addr = inode.blockPointer[blockNum]
    // Move the file pointer to the block location (i.e., to byte #
    //   addr*1024 in the file)

    // Read in the block => Read in 1024 bytes from this location
    //   into the buffer "buf"

  } // End read


  int write(char name[8], int blockNum, char* buf[1024])
  {
    // write this block to this file

    // Step 1: locate the inode for this file
    // Move file pointer to the position of the 1st inode (129th byte)
    // Read in a inode
    // If the inode is in use, compare the "name" field with the above file
    // If the file names don't match, repeat

    // Step 2: Write to the specified block
    // Check that blockNum < inode.size, else flag an error
    // Get the disk address of the specified block
    // That is, addr = inode.blockPointer[blockNum]
    // Move the file pointer to the block location (i.e., byte # addr*1024)

    // Write the block! => Write 1024 bytes from the buffer "buff" to 
    //   this location

  } // end write

 };

std::queue<std::string> instruction;

int main(int argc, char *argv[])
{
	char* buf[1024];
	int i=0;
	for(i=0;i<1024;i++)
		buf[i]=0;
  //printf("Open Disk %s\n",argv[1] );
  char *diskName = new char[16];
  diskName = argv[1];
  //read(diskName);
   MyFileSystem *filesys;
  
  // MyFileSystem filesys;
 char content[1000];
 std::ifstream TextFile;
 TextFile.open("input.txt");
 int count = 0 ;   // use to count the number of words in command
 while(TextFile.getline (content,1000))
  {
    char *token= std::strtok(content, " ");
      while (token != NULL) {
         printf("%s ",token);
      	  if(token!=NULL)
      	 instruction.push(token);
      	token = std::strtok(NULL, " ");
      }
      printf("\n");
      
      if(instruction.size()==3)
    	{
    	    std::string command = instruction.front();
    	    instruction.pop();
    	    std::string f = instruction.front();
    	    instruction.pop();
    	    std::string s = instruction.front();
    	    instruction.pop();
    	    int size = std::stoi (s);
    	    char *file = new char[8];
    	   // file = f;
    	   std::strcpy(file, f.c_str());
    	    if(command == "C")
    	    	filesys->create(file,size);
    	    else if(command=="W")
    	    	filesys->write(file,size,buf);
    	    else if (command=="R")
    	    	filesys->read(file,size,buf);
         }
         else if(instruction.size()==2)
         {
         	instruction.pop();
         	std::string f = instruction.front();
    	    instruction.pop();
    	     char *file = new char[8];
    	     std::strcpy(file, f.c_str());
    	     filesys->Delete(file);
         }
         else if (instruction.size()==1)
         {
         	std::string command = instruction.front();
    	    instruction.pop();
         	if(command=="L")
         		filesys->ls();
         	else
         	{
         		char *c = new char[16];
    	       std::strcpy(c, command.c_str());
    	      // MyFileSystem fs(c);
               filesys = new MyFileSystem(c);
         	}
         }
       
        // clear the queue for next instruction
        while(instruction.size()!=0)
        	instruction.pop();
  }
  return 0;
}
