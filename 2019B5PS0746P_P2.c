
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define BUFFER_SIZE 1000 // to use in get s


void new() ;
void save() ;
void saveas() ;
void search() ;
void delete() ;
int compareFile(FILE *fp, FILE *ft) ;
int compare() ;



// creating main menu in main function .
void main()
{

    char option ;
    printf("\n******************************************************************************************") ;
    printf(" \n a ) Open a new file \n") ;
    printf(" b ) Save (edit)  \n") ;
    printf(" c ) Save as \n") ;
    printf(" d ) Search \n") ;
    printf(" e ) Compare \n") ;
    printf(" f) delete \n") ;
     printf(" g) exit \n") ;
    printf("Enter your option  \n") ;

   // switch will compare user input and open further function .
   
    option = getchar() ;
        switch(option)
    {
    case 'a':
        new() ;
        break;
    case 'b' :
        save() ;
        break ;
    case 'c' :
        saveas() ;
        break ;
    case 'd' :
        search() ;
        break ;
    case 'e' :
        compare() ;
        break ;
    case 'f' :
        delete() ;
        break ;
    case 'g' :
    exit(0) ;
    break ;
    default :
       { printf("wrong entry") ;
        main() ;                                       // open main menu again in case of wrong entry
        }}}



    // open a new file
    void new()
        {
        FILE *fp ;
        char name[BUFFER_SIZE] ;
        char c ;
        char d ;
        int i =0 ;
        int j = 0 ;
        printf("input file name \n \n") ;
        scanf("%s", name) ;

        fp = fopen(name, "w") ;

        printf("\n\n enter new content . To submit ; press ^ followed by enter.\n \n ") ;
        // the wile loop take input in c till eof is pressed by user .
        while(( c=getchar() ) != '^')
            {
            if(i==0)   // done to prevent new line error . the first value of c which is new line is not printed
            i=1 ;
        else
           fputc(c,fp) ; // put c in file
        }

        d=getchar() ;                         // to consume linebreak left from scanf
        printf("\t") ;

        fclose(fp) ;                       // file closed
        
        
        if(i == 1)     
         printf("\nsuccess") ;
         main() ;
            
        }
  // open saved file and edit it


    void save()
        {
        FILE *fp ;
        int j=0 ;
        FILE *ftemp ;
        char name[100] ;
        char ch ;
        char d ;
        char c ;
        char buffer[BUFFER_SIZE] ;
        char newline[BUFFER_SIZE] ;
        int i=0 ;
        int line ;
        char opt ;

        
        
        // taking file to be edited .

        printf("input file you want to edit \n") ;
        scanf("%s" , name) ;

        
        
        // opening file to be edited and a temperory file .
        ftemp = fopen("temp.txt", "w") ;
        fp =fopen(name, "r") ;

        
        
        // checking if file to be edited exist .  open main menu
      if (fp == NULL )
        {
         printf("file does not exist \n") ;
         
         
         printf("press any key followed by enter go back to main menu") ;
         scanf("%d" , &j) ;

      
         d=getchar() ;                         // to consume linebreak left from scanf
         printf("\t ") ;

          if(j == 1)
          main() ;
          else
          main() ;         
         }
       else  // if file exist
        { 
        
        
           
          // showing current file content .
          printf("this is current file :  \n") ;
          while((ch = fgetc(fp)) != EOF)
          printf("%c", ch);

          
          // option to how to edit file      
          printf("\na) To rewrite a current line in file \n") ;
          printf("b) To delete a current line in file \n") ;
          printf("choose your option") ;
          
          d=getchar() ;                         // to consume linebreak left from scanf
          printf("\t ") ;
          
          opt = getchar() ;                      // getting value and performin appropiate task .
          
          
          
        switch(opt)
    {
    case 'a':
        
        {
                
          //taking line number to be edited and new line .
          printf("\nenter line number you want to edit . numbering start from 1 .\n") ;
          scanf("%d", &line) ;

          d=getchar() ;                         // to consume linebreak left from scanf
          printf("\t ") ;
       
       
          printf("\nenter new line\n") ;   
          fgets(newline, BUFFER_SIZE, stdin);   // fgets used instead of scanf as we also need to take spaces

          i=0 ;                                 // to check which line to replace
          rewind(fp) ;                          // to move cursor back to starting position


        while((c=fgets( buffer , BUFFER_SIZE, fp)) != NULL) // gets return null every time it encounter a line break . each line is stored in buffer one by one .
            {
            i++ ;                 // thus i represent line number as we increase it everytime there is a line break .

            if (i==line)          // if i = line ; we take line from newline (user) ; otherwise line is take from buffer which has existing file .
            {
              fputs(newline, ftemp) ;
            }
            else
            {
              fputs(buffer , ftemp) ;
            }
            }


        // while loop end .closing all file
        fclose(fp);
        fclose(ftemp);


        //Delete original file
        remove(name);

        // Rename temporary file as original file
        rename("temp.txt", name);

           
          
        
        // allowing user to go back to main menu .
         printf("\nSuccessfully done ");
         printf("\npress any key followed by enter  to go back to main menu\n") ;
         scanf("%d" , &j) ;

         
         d=getchar() ;                         // to consume linebreak left from scanf
         printf("\t ") ;

          if(j == 1)
          main() ;
          else
          main() ;
          
          break ;
        
          }// case a end
   
    case 'b' :
          {
          
           //taking line number to be deleted .
          printf("\nenter line number you want to delete . numbering start from 1 .\n") ;
          scanf("%d", &line) ;

         
          i=0 ;                                 // to check which line to replace
          rewind(fp) ;                          // to move cursor back to starting position


        while((c=fgets( buffer , BUFFER_SIZE, fp)) != NULL) // gets return null every time it encounter a line break . each line is stored in buffer one by one .
            {
            i++ ;                 // thus i represent line number as we increase it everytime there is a line break .

            if (i==line)          // if i = line ; we dont take anyline ; otherwise line is take from buffer which has existing file .
            {
               printf("\t ") ;
            }
            else
            {    
            fputs(buffer , ftemp) ;
            }
            }


        // while loop end .closing all file
        fclose(fp);
        fclose(ftemp);


        //Delete original file
        remove(name);

        // Rename temporary file as original file
        rename("temp.txt", name);
        
        // Displaying new file
        fp =fopen(name, "r") ;
        
        printf("this is new file :  \n") ;
        while((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
        fclose(fp) ; 
       
        
        // allowing user to go back to main menu .
         printf("\nSuccessfully done \n");
         printf("press any key followed by enter to go back to main menu\n") ;
         scanf("%d" , &j) ;

      
         d=getchar() ;                         // to consume linebreak left from scanf
         printf("\t ") ;

          if(j == 1)
          main() ;
          else
          main() ;
          break ;
          }         // case b bracket
          default :
          {printf("\n wrong option . \ngoing to main") ;
           d=getchar() ;                         // to consume linebreak left from scanf
           printf("\t ") ;
          main() ;
          }
          }          // switch bracket
          }          // else bracket
          }         




// save as
    void saveas()
    {
        // declaring essential variable
        FILE *fp ;
        FILE *ftemp ;
        char name[100] ;
        char ch ;
        char newname[100] ;
        int j= 0 ;
        char c ;
        char buffer[BUFFER_SIZE] ;
        char newline[BUFFER_SIZE] ;
        int i=0 ;
        int line ;
        char d ;
        char opt ;
        char o ;

        // taking file to be edited and new file name
        printf("\ninput file name you want to edit and save as other file name keeping the old copy \n") ;
        scanf("%s" , name) ;

        printf("input new file name of the edited file\n") ;
        scanf("%s", newname) ;




        // opening both file .
        ftemp = fopen(newname, "w") ;
        fp =fopen(name, "r") ;


        // checking if file to be edited exist and allowinh user to exit .

    if (fp == NULL )
        {
          printf("file does not exist \n") ;
          
          printf("press any key followed by enter to go back to main menu\n") ;
          scanf("%d" , &j) ;
          d=getchar() ;                         // to consume linebreak left from scanf
          printf("\t ") ; 
           
          if(j == 1)
          main() ;
          else
          main() ;
          
          }
    else
        {
            // displaying current file
            printf("\nthis is current file .\n") ;
            while((ch = fgetc(fp)) != EOF)
            printf("%c", ch);

            
          // asking how user want to edit file .   
          printf("\n\na) To rewrite a current line in file \n") ;
          printf("b) To delete a current line in file \n") ;
          printf("c) save as without editing \n") ;
          printf("choose your option") ;
          
          d=getchar() ;                         // to consume linebreak left from scanf
          printf("\t") ;
          
          opt = getchar() ;
          
          
          
        switch(opt)
    {
    case 'a':
        
        {           
                   
          
             // taking line to be edited and its content .
             printf("\nenter line number you want to edit . numbering start from 1 .\n") ;
             scanf("%d", &line) ;

             printf("enter new line\n") ;

             d=getchar() ;                         // to consume linebreak left from scanf
             printf("\t ") ;

             //similar to save . saving each line in buffer . writing from newline when i=line and buffer otherwise
             fgets(newline, BUFFER_SIZE, stdin);
             i=0 ;
             rewind(fp) ;
             while((c=fgets( buffer , BUFFER_SIZE, fp)) != NULL)
              {
                  i++ ;
                  if (i==line)
                  {
                      fputs(newline, ftemp) ;
                  }
                  else
                  {
                       fputs(buffer , ftemp) ;
                  }
              }


              // Close all files
              fclose(fp);
              fclose(ftemp);


            // allowing user to go back to main menu .
            printf("\nSuccessfully done ");
            printf("\npress any key followed by enter to go back to main menu\n") ;
            scanf("%d" , &j) ;

            d=getchar() ;                         // to consume linebreak left from scanf
            printf("\t ") ;

            if(j == 1)
            main() ;
            else
            main() ;
            
            break ;
            } 
            
      case 'b' :
         {
         
             // taking line to be deleted
             printf("\nenter line number you want to edit . numbering start from 1 .\n") ;
             scanf("%d", &line) ;

            
             i=0 ;                       // to return to starting position
             rewind(fp) ;
             while((c=fgets( buffer , BUFFER_SIZE, fp)) != NULL)
              {
                  i++ ;
                  if (i==line)
                  {
                      printf("\t ") ;
                  }
                  else
                  {
                       fputs(buffer , ftemp) ;
                  }
              }


              // Close all files
              fclose(fp);
              fclose(ftemp);


            // allowing user to go back to main menu .
            printf("\nSuccessfully done ");
            printf("\npress any key followed by enter to go back to main menu\n") ;
            scanf("%d" , &j) ;

            d=getchar() ;                         // to consume linebreak left from scanf
            printf("\t ") ;

            if(j == 1)
            main() ;
            else
            main() ;
            break ;
           }         // case b bracket
           
           
    case 'c' :
           {
           
            d=getchar() ;                         // to consume linebreak left from scanf
            printf("\t ") ;
            rewind(fp) ;
           
    while((o = fgetc(fp)) != EOF)                 // copying the content of the file
    { 
        fputc(o, ftemp); 
         
    } 
    
              // Close all files
              fclose(fp);
              fclose(ftemp);
              
            d=getchar() ;                         // to consume linebreak left from scanf
            printf("\t ") ;


            // allowing user to go back to main menu .
            printf("\nSuccessfully done ");
            printf("\npress any key followed by enter to go back to main menu\n") ;
            scanf("%d" , &j) ;

            d=getchar() ;                         // to consume linebreak left from scanf
            printf("\t ") ;

            if(j == 1)
            main() ;
            else
            main() ;
            break ;
           }    
            
           
           
     default :
          {printf("\n \nwrong option . \ngoing to main") ;
           d=getchar() ;                         // to consume linebreak left from scanf
           printf("\t ") ;
          main() ;
          }
          }          // switch bracket
          }          // else bracket
          }         


            
           
       
      




        // SEARCH FILE
void search()
{
     // declaring essential variable .
      char word[50] ;
      char name[50] ;
      FILE *fp ;
      char content[100] ;
      int count = 0 ;
      int line = 0 ;
      char d ;
      int j =0 ;   
    
    // taking file to be edited and new file name
        printf("input file name you want to search \n") ;
        scanf("%s" , name) ;
        
     // taking word to search 
        printf("input word u want to search \n") ;
        scanf("%s" , word) ;

     //        
       fp =fopen(name, "r") ;
       
     // opening and checking file and letting user go to main menu  
    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        printf("press any key followed by enter  to go back to main menu\n") ;
        scanf("%d" , &j) ;
        
        d=getchar() ;                         // to consume linebreak left from scanf
        printf("\t ") ;


        if(j == 1)
        main() ;
        else
        main() ;
    }                                        // if file exist
     
     printf("/n the file is .\n") ;
     while(fgets(content, 99, fp) != NULL)   // 99 as last will be \o
     {
     for(int i=0 ; i<strlen(content); i++) {
			bool check = 0;
			 // if first leetr match check other letter otherwise not
			if(content[i] == word[0]) 
			{   
			check = 1;
				for(int k=1; k<strlen(word); k++) {    // checking thr remaining letter remaining letters in search word
				if(word[k] != content[i+k])
				{
						check=0;
						break;    // if current letter does not match , break the loop and check =0
				}
				}
				if(check) 
				{
					printf("[[%s]]", word);    // if word was found then print in square bracket
					i += strlen(word) - 1;    // then increment i by length of search word 
					count++;
				}
			}
			if(!check)
				printf("%c", content[i]);    // print the current letter only if word not found
								
	}
	
    }
    
             printf("\nSuccessfully done . the word occur %d time ", count);
	fclose(fp);

         // allowing user to go back to main menu .
          
            d=getchar() ;                         // to consume linebreak left from scanf
            printf("\t ") ;
            
            
            printf("\npress any key followed by enter to go back to main menu\n") ;
            scanf("%d" , &j) ;

            d=getchar() ;                         // to consume linebreak left from scanf
            printf("\t ") ;
           

            if(j == 1)
            main() ;
            else
            main() ;
            
    


      
    
}




    // compare file


int compare()
{
    // declaring neccesary file pointer and variable
    char name1[100];
    char name2[100];
    FILE *fp;
    FILE * ft;
    int j= 0 ;
    int com;
    char d ;

    // taking filename
    printf("\nEnter first file:\n ");
    scanf("%s", name1);

    printf("Enter second file:\n ");
    scanf("%s", name2);

    //  Open all files to compare
    fp = fopen(name1, "r");
    ft = fopen(name2, "r");

    // if fopen return null ; then it is unable to open first file
    if (fp == NULL )
    {
        /* Unable to open first file hence allowing user to exit */
        printf("\nUnable to open first file.\n");
        printf("press any key followed by enter to go back to main menu\n") ;
        scanf("%d" , &j) ;

        if(j == 1)
        main() ;
        else
        main() ;
    }
    else if(ft == NULL)
       {
        // Unable to open second file hence allowing user to exit
        printf("\nUnable to open second file.\n");
        printf("press any key followed by enter to go back to main menu\n") ;

        scanf("%d" , &j) ;

        if(j == 1)
        main() ;
        else
        main() ;
    }
    else
    {
    // Calling funtion to compare file . it return 0 if file are equal
    com = compareFile(fp, ft);
    }
    if (com == 0)
    {
        printf("\nBoth files are equal.");
    }
    else
    {
        printf("\nFiles are not equal.");

    }


    // Finally closing files
    fclose(fp);
    fclose(ft);

        printf("press any key followed by enter to go back to main menu") ;
        scanf("%d" , &j) ;
        d=getchar() ;                         // to consume linebreak left from scanf
        printf("\t ") ; 
           
        

        if(j == 1)
        main() ;
        else
        main() ;
    return 0;
}


// Function to compare two files.
//Returns 0 if both files are equivalent, otherwise returns


int compareFile(FILE *fp, FILE *ft)
{
    char w1, w2;

    do
    {
        // Input character from both files
        w1 = fgetc(fp);
        w2 = fgetc(ft);

        // If characters are not same then return -1
        if (w1 != w2)
            return -1;


    } while (w1 != EOF && w2 != EOF);


    
        return 0;
    
}


// program to delete a file

 void delete()
{
  int check ;
  char file[25];
  int j= 0 ;
  char d ;
  printf("Enter name of a file you wish to delete\n");
  scanf( "%s", file);


  check = remove(file); // delete the file and return 0 to check if succesfull

  if (check == 0)
    {
        printf(" file deleted successfully. \n");

        printf("press any key followed by enter to go back to main menu") ;
        scanf("%d" , &j) ;
        
         d=getchar() ;                         // to consume linebreak left from scanf
         printf("\t ") ; 
       
        if(j == 1)
        main() ;
        else
        main() ;
    }
  else
   {

    printf("Unable to delete the file\n");
    printf("press any key followed by enter to go back to main menu") ;
    scanf("%d" , &j) ;
    
    d=getchar() ;                         // to consume linebreak left from scanf
    printf("\t ") ; 
    
           
    
    if(j == 1)
    main() ;
    else
    main() ;
}}





    

