#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
struct song
{
    char genre[100];
    char author[100];
    char song[100];
    char time[6];
    char fav[2];
} n[1000];
void wrong()
{
    int k;
    printf("ERROR:wrong input\n");
    scanf("%d",k);
}
int check(int nr)
{
        if(nr>=1 && nr<=5)
            return 1;
    return -1;
}
void deletus(struct song *n,FILE *read,int *x,int nr)
{
    struct song temp;
    int i,j,k=*x;
    for(j=0; j<=k; j++)
        if(j==nr)
            for(i=j; i<=k; i++)
                n[i]=n[i+1];
    strcpy(n[k].genre,"");
    strcpy(n[k].author,"");
    strcpy(n[k].song,"");
    strcpy(n[k].time,"");
    strcpy(n[k].fav,"");

    k--;
    *x=k;
}
void write(struct song *n,FILE *read,int *x)
{
    int j,k=*x;
    for(j=0; j<=k; j++)
        fprintf(read,"%s,%s,%s,%s,%s\n",n[j].genre,n[j].author,n[j].song,n[j].time,n[j].fav);
    fclose(read);
}
void comp(struct song *n,int *x,int nr)
{
    struct song temp;
    int sw,array[1000],i,j,k=*x;
    char cp1[7],cp2[7];
    switch(nr)
    {
    case 1:
        for(i=0; i<k; i++)
            for(j=0; j<k-i; j++)
                if(strcmp(n[j].genre,n[j+1].genre)>0)
                {
                    temp=n[j];
                    n[j]=n[j+1];
                    n[j+1]=temp;
                }
        break;
    case 2:
        for(i=0; i<k; i++)
            for(j=0; j<k-i; j++)
                if(strcmp(n[j].author,n[j+1].author)>0)
                {
                    temp=n[j];
                    n[j]=n[j+1];
                    n[j+1]=temp;
                }
        break;
    case 3:
        for(i=0; i<k; i++)
            for(j=0; j<k-i; j++)
                if(strcmp(n[j].song,n[j+1].song)>0)
                {
                    temp=n[j];
                    n[j]=n[j+1];
                    n[j+1]=temp;
                }
        break;
    case 4:
        for(i=0; i<=k; i++)
            if(strlen(n[i].time)==5)
            {
                strncpy(cp1,n[i].time,2);
                strcpy(cp2,n[i].time+3);
                array[i]=atoi(cp1)*60+atoi(cp2);
            }
            else if(strlen(n[i].time)==4)
            {
                strncpy(cp1,n[i].time,1);
                strcpy(cp2,n[i].time+2);
                array[i]=atoi(cp1)*60+atoi(cp2);
            }
            else
            {
                printf("error:wrong time length\n");
                break;
            }
        for(i=0; i<k; i++)
            for(j=0; j<k-i; j++)
                if(array[j]>array[j+1])
                {
                    temp=n[j];
                    n[j]=n[j+1];
                    n[j+1]=temp;
                    sw=array[j];
                    array[j]=array[j+1];
                    array[j+1]=sw;

                }
        break;
    case 5:
        for(i=0; i<k; i++)
            for(j=0; j<k-i; j++)
                if(strcmp(n[j].fav,n[j+1].fav)<0)
                {
                    temp=n[j];
                    n[j]=n[j+1];
                    n[j+1]=temp;
                }

        break;
    }

}
void print(struct song *n,int *i)
{
    int j,nr;
    for(j=0; j<=i; j++)
        printf("(%d)%s,%s,%s,%s,%s\n",j+1,n[j].genre,n[j].author,n[j].song,n[j].time,n[j].fav);
}
void reading(struct song *n,FILE *read,int *x)
{
    int k=*x;
    char *string2,*string,chr[1000];
    while(fgets(chr,1000,read))
    {
        string2=strtok(chr,"\n");
        string=strtok(string2,",");
        while(string!=NULL)
        {
            k++;
            strcpy(n[k].genre,string);
            string=strtok(NULL,",");
            strcpy(n[k].author,string);
            string=strtok(NULL,",");
            strcpy(n[k].song,string);
            string=strtok(NULL,",");
            strcpy(n[k].time,string);
            string=strtok(NULL,",");
            strcpy(n[k].fav,string);
            string=strtok(NULL,",");
        }
    }
    *x=k;
}
int main()
{
    FILE *read=fopen("songlist.txt","r");
    int max,l=0,k=-1;
    reading(n,read,&k);
    int nr;
    while(true!=false)
    {
        printf("To show the list of songs,press 1\n");
        printf("To sort the songs,press 2\n");
        printf("To add a new song,press 3\n");
        printf("To delete an existing song,press 4\n");
        printf("To favorite&unfavorite a song,press 5\n");
        printf("Your input:");
        scanf("%d",&nr);
        if(check(nr)==1)
        {
            switch(nr)
            {
            case 1:
            {
                print(n,k);
                scanf("%d",&nr);
                break;
            }
            case 2:
            {
                printf("What do you want to sort them by?\n");
                printf("For genre, press 1\nFor author, press 2\nFor song, press 3\nFor time, press 4\nFor favorite songs, press 5\n");
                scanf("%d",&nr);
                if(check(nr)==1)
                {
                    comp(n,&k,nr);
                    print(n,k);
                    read=fopen("songlist.txt","w");
                    write(n,read,&k);
                    scanf("%d",&nr);
                }
                else
                    wrong();

                break;
            }
            case 3:
            {
                printf("Enter the data of the song you want to add\n");
                k++;
                getchar();
                printf("Genre:");
                gets(n[k].genre);
                printf("Author:");
                gets(n[k].author);
                printf("Name of the song:");
                gets(n[k].song);
                printf("Length of the song:");
                gets(n[k].time);
                printf("Press 1 if you want to favorite it,0 if you don't:");
                gets(n[k].fav);
                read=fopen("songlist.txt","w");
                write(n,read,&k);
                scanf("%d",&nr);
                break;
            }
            case 4:
            {

                printf("Which song do you want to delete?\n");
                print(n,k);
                scanf("%d",&nr);
                if(nr>=1 && nr<=k+1)
                {
                    deletus(n,read,&k,nr-1);
                    read=fopen("songlist.txt","w");
                    write(n,read,&k);
                    print(n,k);
                    scanf("%d",&nr);
                    break;
                }
                else
                    wrong();


            }
            case 5:
            {
                printf("Which song do you want to modify?\n");
                print(n,k);
                scanf("%d",&nr);
                if(nr>=1 && nr<=k+1)
                {
                    if(strcmp(n[nr-1].fav,"0")==0)
                    {
                        strcpy(n[nr-1].fav,"1");
                        read=fopen("songlist.txt","w");
                        write(n,read,&k);
                    }
                    else
                    {
                        strcpy(n[nr-1].fav,"0");
                        read=fopen("songlist.txt","w");
                        write(n,read,&k);
                    }
                    print(n,k);
                    scanf("%d",&nr);
                }
                else
                    wrong();

                break;
            }
            }
        }
        else
            wrong();

        system("cls");
    }
    fclose(read);
    return 0;
}
