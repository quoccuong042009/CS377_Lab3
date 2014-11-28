

# include "myFileSystem.h"
# include <stdlib.h>
# include "myFileSystem.h"
#include <fstream>

void read()
{
 char content[1000];
 std::ifstream TextFile;
 TextFile.open("input.txt");
 int count = 0 ;   // use to count the number of words in command
 while(TextFile.getline (content,1000))
  {
    char *token= std::strtok(content, " ");
      count++;
      while (token != NULL) {
         std::string str(token);
         count++;
         printf("%s\n",str);
      	 token = std::strtok(NULL, " ");
      }
  }

}




int main(int argc, char *argv[])
{
  printf("Open Disk %s\n",argv[1] );
  return 0;
}
