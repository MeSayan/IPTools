#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------
 * Name:   ipinfo
 * Author: Sayan Mahapatra
 * Date:	23/05/2016
 * Description: A small program to list out information like City,Region
 * of an public IP. Data is provided by the website "ipinfo.io"
 * ---------------------------------------------------------------------
 */
 
 
int main(int argc, char *argv[])
{
	int i,j=1;
	char command[80];
	char c;
	
	
	//Generating INFO File
	
	if(argc==1)
	system("curl -s ipinfo.io>>ipinfo.txt");
	else
	for(i=1;i<=argc-1;i++)
	{
		
		sprintf(command,"curl -s ipinfo.io/%s>>ipinfo.txt",argv[i]);
		system(command);
		
	}
	
	//Reading And Parsing INFO File
    FILE *fp=fopen("ipinfo.txt","r");
    
    if(fp==NULL)
    {
		printf("File Not Found\n");
		exit(-1);
	}

    while((c=fgetc(fp))!=EOF)
	{
		if(c=='{')
		{
			if(argc!=1)
			printf("Details for IP Adrress: %s\n",argv[j++]);
			else
			printf("Details for Host's IP\n");
			printf("--------------------------------------------------------------------------------\n");
		}
	    
	    if(c=='}')
			printf("--------------------------------------------------------------------------------\n");
			
		if(c!='{' && c!='}' && c!='"')
			printf("%c",c);
			
		else if(c=='"')
		{
			c=fgetc(fp);
			if(c!='"')
			printf("%c",c);
			else
			printf("N/A");
		}
			
	}	
	fclose(fp);
	
	//Cleaning Up!
	system("rm ./ipinfo.txt");
	printf("\n");
	
	exit(0);
}
		
