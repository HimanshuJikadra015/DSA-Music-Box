/*

    Date: 19/11/2022
    Roll No.: 21BCE098 HIMANSHU R. JIKADRA and 21BCE096, 21BCE099
    Course Code and Name: 2CS301 DSA

    INNOVATIVE ASSIGNMENT PROJECT

    TOPIC : Music Box Program
    
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<time.h>

/*
    implementation of binary search trees;
*/ 

// structure of nodes having song data;
struct songNode{
    char*name;
    int length;
    struct songNode*lft;
    struct songNode*rgt;
};

// structure of root node in song's bst;
struct songBstree{
    int sz;
    struct songNode*root;
};

void blue(){
    printf("\033[0;34m");
}

void green(){
    printf("\033[0;32m");
}

void yellow(){
    printf("\033[0;33m");
}

// structure of nodes having album data;
struct albumNode{
    struct songBstree*songs;
    char*title;
    int year;
    char*singer;
    struct albumNode*lft;
    struct albumNode*rgt;
};

// structure of root node in album's bst;
struct albumBstree{
    int sz;
    struct albumNode*root;
};

/*
    implemetation of various functions of binary search tree;
*/ 

// to create node in song's bst;
struct songNode*newSongNode(char*name,int length){
    struct songNode*tmp=(struct songNode*)malloc(sizeof(struct songNode));
    tmp->lft=NULL;
    tmp->rgt=NULL;
    tmp->length=length;
    tmp->name=name;
    return tmp;
}

// to create node in album's bst;
struct albumNode*newAlbumNode(char*albumTitle, char*singerName, int releaseYr){
    struct albumNode*tmp=(struct albumNode*)malloc(sizeof(struct albumNode));
    tmp->lft=NULL;
    tmp->rgt=NULL;
    tmp->singer=singerName;
    tmp->songs=(struct songBstree*)malloc(sizeof(struct songBstree));
    tmp->songs->sz=0;
    tmp->songs->root=NULL;
    tmp->title=albumTitle;
    tmp->year=releaseYr;
    return tmp;
}

// to access node (song) from song's bst;
struct songNode*getSong(struct songNode*songNode_){
    struct songNode*tmp=songNode_;
    while(tmp->lft!=NULL){
        tmp=tmp->lft;
    }
    return tmp;
}

// to add node (song) in song's bst;
struct songNode*addSong(struct songNode*songNode_, char*songName, int songLen, int*error){
    if(songNode_){
        int comp=strcmp(songNode_->name,songName);
        if(comp>0){
            songNode_->lft=addSong(songNode_->lft, songName, songLen, error);
        }
        else if(comp<0){
            songNode_->rgt=addSong(songNode_->rgt, songName, songLen, error);
        }
        else{
            *error=1;
        }
    }else{
        return newSongNode(songName, songLen);
    }
    return songNode_;
}

// to delete node (song) from song's bst;
struct songNode*removeSong(struct songNode*songNode_, char*songName, int*error){
    if(songNode_){
        int comp=strcmp(songNode_->name,songName);
        if(comp>0){
            songNode_->lft=removeSong(songNode_->lft, songName, error);
        }
        else if(comp<0){
            songNode_->rgt=removeSong(songNode_->rgt, songName, error);
        }
        else{
            *error=0;
            struct songNode*newSong=NULL;
            struct songNode*tmp=songNode_;
            if(songNode_->lft!=NULL && songNode_->rgt!=NULL){
                newSong=getSong(songNode_->rgt);
                newSong->lft=songNode_->lft;
                newSong->rgt=songNode_->rgt;
                newSong->rgt=removeSong(newSong->rgt, newSong->name, error);
            }
            else if(songNode_->lft!=NULL){
                newSong=songNode_->lft;
            }
            else if(songNode_->rgt!=NULL){
                newSong=songNode_->rgt;
            }
            free(tmp);
            return newSong;
        }
    }
    return songNode_;
}

// to access node (album) from album's bst;
struct albumNode*getAlbum(struct albumNode*albumNode_){
    struct albumNode*tmp=albumNode_;
    while(tmp->lft!=NULL){
        tmp=tmp->lft;
    }
    return tmp;
}

// to check whether node (album) is present in album's bst or not;
int ifAlbumExist(struct albumNode*albumNode_,char*albumTitle){
    if(albumNode_){
        if(strcmp(albumNode_->title,albumTitle)==0){
            return 1;
        }
        return(ifAlbumExist(albumNode_->lft,albumTitle) || ifAlbumExist(albumNode_->rgt,albumTitle))? 1:0;
    }
    return 0;
}

// to print song of particular album node bst;
void songsOfAlbum(struct songNode*songNode_){
    if(songNode_){
        printf("\n");
        songsOfAlbum(songNode_->lft);
        printf("\t\t\t\tNAME OF THE SONG IS :: %s.\n",songNode_->name);
        printf("\t\t\t\tLENGTH OF THE SONG IS :: %d SECONDS.\n",songNode_->length);
        printf("\n");
        songsOfAlbum(songNode_->rgt);
    }
}

// to add node (album) in album's bst;
struct albumNode*addAlbum(struct albumNode*albumNode_, char*albumTitle, char*singerName, int releaseYr){
    if(albumNode_){
        if(albumNode_->year>releaseYr){
            albumNode_->lft=addAlbum(albumNode_->lft, albumTitle, singerName, releaseYr);
        }
        else{
            albumNode_->rgt=addAlbum(albumNode_->rgt, albumTitle, singerName, releaseYr);
        }
    }
    else{
        return newAlbumNode(albumTitle, singerName, releaseYr);
    }
    return albumNode_;
}

// to delete node (album) from album's bst;
struct albumNode*removeAlbum(struct albumNode*albumNode_, int*error, char*albumTitle){
    if(albumNode_){
        if(strcmp(albumTitle,albumNode_->title)==0){
            *error = 0;
            struct albumNode*tmp=albumNode_;
            struct albumNode*newAlbum=NULL;
            if(albumNode_->lft!=NULL && albumNode_->rgt!=NULL){
                newAlbum=getAlbum(albumNode_->rgt);
                newAlbum->lft=albumNode_->lft;
                newAlbum->rgt=albumNode_->rgt;
                newAlbum->rgt=removeAlbum(newAlbum->rgt, error, newAlbum->title);
                return newAlbum;
            }
            else if(albumNode_->lft!=NULL){
                newAlbum=albumNode_->lft;
            }
            else if(albumNode_->rgt!=NULL){
                newAlbum=albumNode_->rgt;
            }
            free(tmp);
            return newAlbum;
        }
        albumNode_->lft=removeAlbum(albumNode_->lft, error, albumTitle);
        albumNode_->rgt=removeAlbum(albumNode_->rgt, error, albumTitle);
    }
    return albumNode_;
}

// to show all nodes (albums) of album's bst;
void showAllAlbums(struct albumNode*albumNode_){
    if(albumNode_){
        showAllAlbums(albumNode_->lft);
        printf("\t\t\t\tNAME OF THE ALBUM :: %s\n",albumNode_->title);
        printf("\t\t\t\tRELEASE YEAR OF THE ALBUM :: %d\n",albumNode_->year);
        printf("\t\t\t\tSINGER OF THE ALBUM :: %s.\n",albumNode_->singer);
        printf("\n");
        showAllAlbums(albumNode_->rgt);
    }
}

// to display all details(songs) of the particular node (album) of album's bst;
void showAlbumDetails(struct albumNode*albumNode_, char*albumTitle){
    if(albumNode_){
        if(strcmp(albumTitle,albumNode_->title)==0){
            printf("\t\t\t\tDETAILS OF THE ALBUM '%s'.\n",albumNode_->title);
            printf("\n");
            printf("\t\t\t\tNAME OF THE ALBUM :: %s\n",albumNode_->title);
            printf("\t\t\t\tRELEASE YEAR OF THE ALBUM :: %d\n",albumNode_->year);
            printf("\t\t\t\tSINGER OF THE ALBUM :: %s.\n\n",albumNode_->singer);
            printf("\t\t\t\tSONGS IN THIS ALBUM ARE :: \n");
            songsOfAlbum(albumNode_->songs->root);
            return;
        }
        showAlbumDetails(albumNode_->lft,albumTitle);
        showAlbumDetails(albumNode_->rgt,albumTitle);
        printf("\n");
    }
}

// to add node (song) of song's bst in node (album) of album's bst;
void addSongInAlbum(struct albumNode*albumNode_, char*albumTitle, char*songName, int songLen, int*error){
    if(albumNode_){
        if(strcmp(albumNode_->title,albumTitle)==0){
            albumNode_->songs->root=addSong(albumNode_->songs->root,songName,songLen,error);
            return;
        }
        addSongInAlbum(albumNode_->lft, albumTitle, songName, songLen, error);
        addSongInAlbum(albumNode_->rgt, albumTitle, songName, songLen, error);
    }
}

// to remove node (song) from song's bst which is in node (album) of album's bst;
void removeSongFromAlbum(struct albumNode*albumNode_, char*albumTitle, char*songName, int*error){
    if(albumNode_){
        if(strcmp(albumNode_->title,albumTitle)==0){
            albumNode_->songs->root=removeSong(albumNode_->songs->root, songName, error);
            return;
        }
        removeSongFromAlbum(albumNode_->lft, albumTitle, songName, error);
        removeSongFromAlbum(albumNode_->rgt, albumTitle, songName, error);
    }
}

// to display all nodes (songs) of all nodes (albums) of album's bst;
void showListOfAllSongs(struct albumNode*albumNode_){
    if(albumNode_){
        showListOfAllSongs(albumNode_->lft);
        songsOfAlbum(albumNode_->songs->root);
        showListOfAllSongs(albumNode_->rgt);
    }
} 

// to display nodes (albums) of album's bst with same release data;
void showAlbumsByRelease(struct albumNode*albumNode_, int lowYr, int uppYr, int*error){
    if(albumNode_){
        if(albumNode_->year>=lowYr){
            showAlbumsByRelease(albumNode_->lft, lowYr, uppYr, error);
        }
        if(albumNode_->year>=lowYr && albumNode_->year<=uppYr){
            *error=0;
            printf("\t\t\t\tNAME OF THE ALBUM :: %s\n",albumNode_->title);
            printf("\t\t\t\tRELEASE YEAR OF THE ALBUM :: %d\n",albumNode_->year);
            printf("\t\t\t\tSINGER OF THE ALBUM :: %s.\n\n",albumNode_->singer);
        }
        if(albumNode_->year<=uppYr){
            showAlbumsByRelease(albumNode_->rgt, lowYr, uppYr, error);
        }
    }
}

// to display nodes (songs) of song's bst with same length data;
void songsByLength(struct songNode*songNode_, int lowLen, int uppLen, char*singerName, int*error){
    if(songNode_){
        songsByLength(songNode_->lft, lowLen, uppLen, singerName, error);
        if(songNode_->length>=lowLen && songNode_->length<=uppLen){
            // printf("%s, ",songNode_->name);
            // printf("%d, ",songNode_->length);
            // printf("%s.\n",singerName);
            printf("\t\t\t\tNAME OF THE SONG :: %s\n",songNode_->name);
            printf("\t\t\t\tRELEASE YEAR OF THE ALBUM :: %d\n",songNode_->length);
            printf("\t\t\t\tSINGER OF THE ALBUM :: %s.\n\n",singerName);
            *error=0;
        }
        songsByLength(songNode_->rgt, lowLen, uppLen, singerName, error);
    }
}

// to display nodes (songs) of album's bst with same length data;
void showSongssByLength(struct albumNode*albumNode_, int lowLen, int uppLen, int*error){
    if(albumNode_){
        showSongssByLength(albumNode_->lft, lowLen, uppLen, error);
        songsByLength(albumNode_->songs->root, lowLen, uppLen, albumNode_->singer, error);
        showSongssByLength(albumNode_->rgt, lowLen, uppLen, error);
    }
}

// menu driven program;
int main(){
    blue();
    struct albumBstree*musicBox = (struct albumBstree*)malloc(sizeof(struct albumBstree));
    musicBox->root=NULL;
    musicBox->sz=0;
    while(1){
        printf("\n\n\n\n\n");
        printf("\t\t\t\t(: WELCOME TO THE MUSIC BOX APPLICATION PROGRAM :)\n");
        printf("\n");
        printf("\t\t\t\tPRESS '1' TO ADD AN ALBUM.\n");
        printf("\t\t\t\tPRESS '2' TO REMOVE AN ALBUM.\n");
        printf("\t\t\t\tPRESS '3' TO SEE THE LIST OF ALL ALBUMS.\n");
        printf("\t\t\t\tPRESS '4' TO SEE DETAILED INFORMATION ABOUT A PARTICULAR ALBUM.\n");
        printf("\t\t\t\tPRESS '5' TO ADD A SONG TO THE SONG LIST OF AN ALBUM.\n");
        printf("\t\t\t\tPRESS '6' TO A REMOVE A SONG FROM THE SONGLIST OF AN ALBUM.\n");
        printf("\t\t\t\tPRESS '7' TO SEE THE LIST OF ALL SONGS OF THE MUSIC BOX.\n");
        printf("\t\t\t\tPRESS '8' TO SEE THE LIST OF ALBUMS RELEASED BETWEEN PARTICULAR YEARS.\n");
        printf("\t\t\t\tPRESS '9' TO SEE THE LIST OF SONGS WITH THE LENGTH OF PARTICULAR SCOPE.\n");
        printf("\t\t\t\tPRESS '10' TO EXIT MUSIC BOX PROGRAM :(\n");
        printf("\n");
        printf("\t\t\t\tENTER YOUR CHOICE :: ");
        int choice;
        scanf("%d",&choice);
        // system("cls");
        char*checkInput = (char*)malloc(sizeof(char)*30);
        switch(choice){
            case 1:{
                green();
                printf("\n\n\n\n\n");
                int releaseYr=0;
                // char albumTitle[50], singerName[50];
                char*albumTitle=(char*)malloc(sizeof(char)*30);
                char*singerName=(char*)malloc(sizeof(char)*30);
                printf("\n");
                printf("\t\t\t\tTO ADD A ALBUM IN THE MUSIC BOX.\n"); 
                printf("\t\t\t\tKINDLY ENTER THE BELOW MENTIONED DETAILS :)\n");
                printf("\n");
                printf("\t\t\t\tENTER THE NAME OF THE ALBUM :: ");
                while((getchar())!='\n');
                scanf("%[^\n]%*c",albumTitle);
                printf("\t\t\t\tENTER THE RELEASE YEAR OF THE ALBUM :: ");
                scanf("%d",&releaseYr);
                printf("\t\t\t\tENTER THE NAME OF THE SINGER :: ");
                while((getchar())!='\n');
                scanf("%[^\n]%*c",singerName);

                if(ifAlbumExist(musicBox->root,albumTitle)==1){
                    printf("\n");
                    printf("\t\t\t\tTHE ALBUM WITH THE NAME '%s' ALREADY EXISTS THERE IN THE MUSIC BOX.\n",albumTitle);
                    break;
                }

                musicBox->root=addAlbum(musicBox->root,albumTitle,singerName,releaseYr);
                musicBox->sz++;
                printf("\n");
                printf("\t\t\t\tTHE ALBUM HAS BEEN SUCCESSFULLY ADDED TO THE MUSIC BOX :)\n");
                printf("\t\t\t\tALBUM NAME :: %s\n",albumTitle);
                // system("cls");
                blue();
                break;
            }
            case 2:{
                yellow();
                printf("\n\n\n\n\n");
                printf("\t\t\t\tTO REMOVE A ALBUM FROM THE MUSIC BOX.\n"); 
                printf("\t\t\t\tKINDLY ENTER THE BELOW MENTIONED DETAILS :)\n");
                printf("\n");
                printf("\t\t\t\tENTER THE NAME OF THE ALBUM THAT YOU WANT TO DELETE FROM THE MUSIC BOX :: ");
                char*albumTitle=(char*)malloc(sizeof(char)*30);
                while((getchar())!='\n');
                scanf("%[^\n]%*c",albumTitle);
                int error=1;
                musicBox->root=removeAlbum(musicBox->root,&error,albumTitle);
                printf("\n");
                if(error){
                    printf("\t\t\t\tTHE ALBUM WITH THE NAME '%s' DOESN'T EXISTS THERE IN THE MUSIC BOX.\n",albumTitle);
                }else{
                    musicBox->sz--;
                    printf("\t\t\t\tTHE ALBUM HAS BEEN SUCCESSFULLY DELETED FROM THE MUSIC BOX :)\n");
                    printf("\t\t\t\tDELETED ALBUM NAME :: %s\n",albumTitle);
                }
                // system("cls");
                blue();
                break;
            }
            case 3:{
                green();
                printf("\n\n\n\n\n");
                printf("\t\t\t\tLIST OF THE ALL ALBUMS PRESENT IN THE MUSIC BOX :: \n\n");
                showAllAlbums(musicBox->root);
                if(musicBox->root==NULL){
                    printf("\t\t\t\tNO ALBUMS ARE THERE IN THE MUSIC BOX.\n");
                }
                // system("cls");
                blue();
                break;
            }
            case 4:{
                yellow();
                printf("\n\n\n\n\n");
                printf("\t\t\t\tDETAILED INFORMATION ABOUT A PARTICULAR ALBUM. \n");
                printf("\t\t\t\tENTER THE NAME OF THE ALBUM THAT YOU WANT TO SEE :: ");
                char*albumTitle=(char*)malloc(sizeof(char)*30);
                while((getchar())!='\n');
                scanf("%[^\n]%*c",albumTitle);
                printf("\n");
                if(ifAlbumExist(musicBox->root,albumTitle)==0){
                    printf("\t\t\t\tTHE ALBUM WITH THE NAME '%s' DOESN'T EXISTS THERE IN THE MUSIC BOX.\n",albumTitle);
                    break;
                }
                showAlbumDetails(musicBox->root,albumTitle);
                // system("cls");
                blue();
                break;
            }
            case 5:{
                green();
                printf("\n\n\n\n\n");
                char*albumTitle=(char*)malloc(sizeof(char)*30);
                char*songName=(char*)malloc(sizeof(char)*30);
                int songLen=0;
                printf("\t\t\t\tTO ADD A SONG IN ANY ALBUM OF THE MUSIC BOX.\n"); 
                printf("\t\t\t\tKINDLY ENTER THE BELOW MENTIONED DETAILS :)\n");
                printf("\n");
                printf("\t\t\t\tPLEASE ENTER THE NAME OF THE ALBUM IN WHICH SONG WILL BE ADDED :: ");
                while((getchar())!='\n');
                scanf("%[^\n]%*c",albumTitle);
                printf("\n");
                if(ifAlbumExist(musicBox->root,albumTitle)==0){
                    printf("\t\t\t\tTHE ALBUM WITH THE NAME '%s' DOESN'T EXISTS THERE IN THE MUSIC BOX.\n",albumTitle);
                    break;
                }
                printf("\t\t\t\tPLEASE ENTER THE LENGTH OF THE SONG IN SECONDS :: ");
                scanf("%d",&songLen);
                printf("\t\t\t\tPLEASE ENTER THE NAME OF THE SONG YOU WANT TO ADD IN ALBUM '%s' :: ",albumTitle);
                while((getchar())!='\n');
                scanf("%[^\n]%*c",songName);
                int error=0;
                addSongInAlbum(musicBox->root,albumTitle,songName,songLen,&error);
                if(error){
                    printf("\n");
                    printf("\t\t\t\tTHE SONG WITH THE NAME '%s' ALREADY EXISTS THERE IN THE ALBUM '%s'.\n",songName,albumTitle);
                }else{
                    musicBox->root->songs->sz++;
                    printf("\n");
                    printf("\t\t\t\tTHE SONG HAS BEEN SUCCESSFULLY ADDED IN THE ALBUM '%s' :)\n",albumTitle);
                    printf("\t\t\t\tSONG NAME :: %s\n",songName);
                }
                // system("cls");
                blue();
                break;
            }
            case 6:{
                yellow();
                printf("\n\n\n\n\n");
                char*albumTitle = (char*)malloc(sizeof(char)*30);
                char*songName = (char*)malloc(sizeof(char)*30);
                int songLen=0;
                printf("\t\t\t\tTO REMOVE A SONG FROM ANY ALBUM OF THE MUSIC BOX.\n"); 
                printf("\t\t\t\tKINDLY ENTER THE BELOW MENTIONED DETAILS :)\n");
                printf("\n");
                printf("\t\t\t\tPLEASE ENTER THE NAME OF THE ALBUM FROM WHICH SONG WILL BE DELETED :: ");
                while((getchar())!='\n');
                scanf("%[^\n]%*c",albumTitle);
                printf("\n");
                if(ifAlbumExist(musicBox->root,albumTitle)==0){
                    printf("\t\t\t\tTHE ALBUM WITH THE NAME '%s' DOESN'T EXISTS THERE IN THE MUSIC BOX.\n",albumTitle);
                    break;
                }
                printf("\t\t\t\tPLEASE ENTER THE LENGTH OF THE SONG THAT YOU WANT TO DELETE FROM THE ALBUM '%s' :: ",albumTitle);
                scanf("%d",&songLen);
                printf("\t\t\t\tPLEASE ENTER THE NAME OF THE SONG THAT YOU WANT TO DELETE FROM THE ALBUM '%s' :: ",albumTitle);
                while((getchar())!='\n');
                scanf("%[^\n]%*c",songName);
                int error=1;
                removeSongFromAlbum(musicBox->root, albumTitle, songName, &error);
                if(error){
                    printf("\t\t\t\tTHE SONG WITH THE NAME '%s' DOESN'T EXISTS THERE IN THE ALBUM '%s'.\n",songName,albumTitle);
                }else{
                    musicBox->root->songs->sz--;
                    printf("\t\t\t\tTHE SONG HAS BEEN SUCCESSFULLY DELETED FROM THE ALBUM '%s' :)\n",albumTitle);
                    printf("\t\t\t\tDELETED SONG NAME :: %s\n",songName);
                }
                // system("cls");
                blue();
                break;
            }
            case 7:{
                green();
                printf("\n\n\n\n\n");
                printf("\t\t\t\tLIST OF THE ALL SONGS PRESENT IN THE MUSIC BOX :: \n\n");
                showListOfAllSongs(musicBox->root);
                if(musicBox->root==NULL){
                    printf("\t\t\t\tNO SONGS ARE THERE IN THE MUSIC BOX.\n");
                }
                // system("cls");
                blue();
                break;
            }
            case 8:{
                yellow();
                printf("\n\n\n\n\n");
                int lowYr=0, uppYr=0;
                printf("\t\t\t\tTO SEE LIST OF THE ALL ALBUMS RELEASED BETWEEN PARTICULAR YEARS. \n\n");
                printf("\t\t\t\tKINDLY ENTER THE BELOW MENTIONED DETAILS :)\n");
                printf("\n");
                printf("\t\t\t\tPLEASE ENTER THE LOWER BOUND YEAR :: ");
                scanf("%d",&lowYr);
                printf("\t\t\t\tPLEASE ENTER THE UPPER BOUND YEAR :: ");
                scanf("%d",&uppYr);
                printf("\n");
                if(lowYr>uppYr){
                    printf("\t\t\t\tINVALID INPUT..!\n");
                    printf("\t\t\t\tUPPER BOUND YEAR CANNOT BE SMALLER THAN LOWER BOUND YEAR :(\n");
                }else{
                    int error=1;
                    showAlbumsByRelease(musicBox->root, lowYr, uppYr, &error);
                    if(error){
                        printf("\t\t\t\tNONE OF THE ALBUMS IN THE MUSICBOX RELEASED BETWEEN %d AND %d YEARS :(\n",lowYr,uppYr);
                    }
                }
                // system("cls");
                blue();
                break;
            }
            case 9:{
                green();
                printf("\n\n\n\n\n");
                int lowLen=0, uppLen=0;
                printf("\t\t\t\tTO SEE LIST OF THE ALL SONGS WHICH LENGTHS ARE IN PARTICULAR SCOPE.\n\n");
                printf("\t\t\t\tKINDLY ENTER THE BELOW MENTIONED DETAILS :)\n");
                printf("\n");
                printf("\t\t\t\tPLEASE ENTER THE LOWER BOUND LENGTH :: ");
                scanf("%d",&lowLen);
                printf("\t\t\t\tPLEASE ENTER THE UPPER BOUND LENGTH :: ");
                scanf("%d",&uppLen);
                printf("\n");
                if(lowLen>uppLen){
                    printf("\t\t\t\tINVALID INPUT..!\n");
                    printf("\t\t\t\tUPPER BOUND LENGTH CANNOT BE SMALLER THAN LOWER BOUND LENGTH :(\n");
                }else{
                    int error=1;
                    showSongssByLength(musicBox->root, lowLen, uppLen, &error);
                    if(error){
                        printf("\t\t\t\tNONE OF THE SONGS IN THE MUSICBOX HAVE LENGTH BETWEEN %d AND %d YEARS :(\n",lowLen,uppLen);
                    }
                }
                // system("cls");
                blue();
                break;
            }
            case 10:{
                yellow();
                printf("\n\n\n\n\n");
                printf("\t\t\t\tTHANK YOU FOR USING MUSIC BOX APPLICATION :))\n");
                printf("\n");
                return 0; 
                blue();
                break;
            }
            default:{
                green();
                printf("\n\n\n\n\n");
                printf("\t\t\t\tINVALID CHOICE..!\n");
                printf("\t\t\t\tENTER VALID CHOICE :)\n");
                blue();
            }
        }
    }
}