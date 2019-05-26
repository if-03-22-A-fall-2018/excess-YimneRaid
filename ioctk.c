//Yimne Raid

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>


int main(int argc, char const *argv[]) {
  struct winsize ws;
	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}
  FILE* fd=fopen("text.txt","r");
  char answer='\0';
  int last_count=0;
  int line_count=0;
  int row_count=0;
  char curr;
  int count=0;
  do {
      while (ws.ws_row>line_count) {
        curr=fgetc(fd);
        if(curr=='\n'||row_count>ws.ws_col){
          line_count++;
          row_count=0;
        }
        if(line_count==ws.ws_row)
          break;

        if(curr=='\0')
          last_count=count;

        count++;
        row_count++;
        printf("%c",curr);
      }
      answer=getchar();

      if (answer=='\n') {
        line_count=0;
        row_count=0;
      }

      else if (answer=='b'||answer=='B') {
        if(last_count!=0)
        {
          fseek(fd,-last_count,SEEK_CUR);
        }
        else{
          fseek(fd,-count,SEEK_CUR);
          count=0;
        }
      }
  } while(answer!='c');
}
