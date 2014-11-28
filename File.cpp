

#include <stdio.h>
#include <unistd.h>
# include <stdlib.h>
#include <fstream>
#include <queue> 
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

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
     fd = open(diskName,O_WRONLY | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);
   	 printf("File Exist\n");
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

    // Step 2: we look for a free inode on disk
    // Read in an inode
    // Check the "used" field to see if it is free
    // If not, repeat the above two steps until you find a free inode
    // Set the "used" field to 1
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

      printf("%s\n", " create here" );
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




void executeInstruction( std::queue<std::string> instruction )
 {
    std::queue<std::string> instruc = instruction;
    printf("%d\n",instruction.size());
       
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
    	   {

    	   }
         }
   
 }




/*
read the instruction in file and prepare for execution
*/
void read(char diskName[16])
{
// MyFileSystem filesys;
 char content[1000];
 std::ifstream TextFile;
 TextFile.open("input.txt");
 int count = 0 ;   // use to count the number of words in command
 while(TextFile.getline (content,1000))
  {
  	// count=0;
    char *token= std::strtok(content, " ");
      while (token != NULL) {
         printf("%s ",token);
      	  if(token!=NULL)
      	 instruction.push(token);
      	token = std::strtok(NULL, " ");
      }
        executeInstruction(instruction);

        // clear the queue for next instruction
        while(instruction.size()!=0)
        	instruction.pop();
      printf("\n");
  }
}



int main(int argc, char *argv[])
{
  printf("Open Disk %s\n",argv[1] );
  char *diskName = new char[16];
  diskName = argv[1];
  //read(diskName);
   MyFileSystem filesys(diskName);
 // filesys.ls();
  return 0;
}
