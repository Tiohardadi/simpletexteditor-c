#include <string.h>
#include <stdio.h>
#include<windows.h>

#define nil NULL
#define textLine(p) (p)->textLine
#define next(p) (p)->next

#define first(p) (p).first
#define last(p) (p).last
#define CTRL(k) ((k)  & 0x1f)



typedef struct tElmText *address;
typedef struct tElmText {
	char textLine[60];
	address next;
}ElmText;
typedef struct{
	address first;
	address last;
}Text;


address alokasi(char text[]);
void deAlokasi(address p);
void printText(Text P,int align);
void createText(Text *P);
void add(Text *P, char text[]);
void del(Text *P);
int jumlahHurufPadaText(Text P);
int jumlahHurufVokalPadaText(Text P);
int jumlahKataPadaText(Text P);
int jumlahKataSamaPadaText(Text P);
void cariKataPadaText(Text P,char text[]);
void gotoxy(int x,int y);

int main () {
	Text myText;
    char ch;
    char temp[60];
    char cari[20];
    int i,align;
    boolean fullscr=1;
    char *word;
    system("MODE 120,30");
    createText(&myText);
    add(&myText,"");
	while(1){
		system("cls");
		if(fullscr==1){
			for(i=0;i<=29;i++){
				gotoxy(60,i);printf("|");	
			}
			gotoxy(61,0);printf("-----------------------------------------------------------");
	   		gotoxy(75,1);printf("Data");
	   		gotoxy(90,1);printf("|");
	   		gotoxy(102,1);printf("Shorhcut");
	   		gotoxy(61,2);printf("-----------------------------------------------------------");
	   		
	   		gotoxy(62,3);printf("Jumlah Huruf       : %d",jumlahHurufPadaText(myText));
	   		gotoxy(62,4);printf("Jumlah Huruf Vokal : %d",jumlahHurufVokalPadaText(myText));
	   		gotoxy(62,5);printf("Jumlah Kata        : %d",jumlahKataPadaText(myText));
	   		gotoxy(62,6);printf("Jumlah Kata Sama   : %d",jumlahKataSamaPadaText(myText));
	   		
	   		
	   		
			for(i=2;i<=25;i++){
				gotoxy(90,i);printf("|");	
			}
			gotoxy(92,3);printf("Align Right       > CTRL+Q");
	   		gotoxy(92,4);printf("Align Center      > CTRL+W");
	   		gotoxy(92,5);printf("Align Left        > CTRL+E");
	   		gotoxy(92,6);printf("Show/Hide SideTab > CTRL+S");
	   		gotoxy(92,7);printf("Cari Kata         > CTRL+C");
	   		
			gotoxy(61,26);printf("-----------------------------------------------------------");
			gotoxy(62,27);printf("Cari : ");
			gotoxy(61,29);printf("-----------------------------------------------------------");
	   
	   		
	   	}
		
		
		
		gotoxy(0,0);printf("------------------------------------------------------------");
   		gotoxy(20,1);printf("Simple Text Editor");
   		gotoxy(0,2);printf("------------------------------------------------------------");
   		printText(myText,align);
   		ch=getch();
   		if(ch=='\b'){
   			if(first(myText)!=nil){
				if(strlen(textLine(last(myText)))>0) {
					textLine(last(myText))[strlen(textLine(last(myText)))-1] = 0;
				}
				else if(strlen(textLine(last(myText)))==0){
					del(&myText);
				}
			}
			
		}	
		else if(ch=='\r'){
  			add(&myText,"");
		}
		else if(ch==CTRL('s')){
			if(fullscr==0){
				system("MODE 120,30");
				fullscr=1;
			}
			else{
				system("MODE 60,30");
				fullscr=0;
			}
  			
		}
		else if(ch==CTRL('q')&&fullscr==1){
  			align=1;
		}
		else if(ch==CTRL('w')&&fullscr==1){
  			align=3;
		}
		else if(ch==CTRL('e')&&fullscr==1){
  			align=2;
		}
		else if(ch==CTRL('c')&&fullscr==1){
  			gotoxy(69,27);scanf("%s",&cari);
  			cariKataPadaText(myText,cari);
  			strcpy(cari,"");
  			getch();
  			
		}
		else{
			if(first(myText)!=nil){
				strncat(textLine(last(myText)),&ch,1);
				word = strrchr(textLine(last(myText)), ' ');
				if(strlen(textLine(last(myText)))==61&&word!=nil){
					
					strcpy(temp,word+1);
					strcpy(word,"");
					add(&myText,temp);	
				}
				else if(strlen(textLine(last(myText)))==60&&word==nil){
					add(&myText,"");
				}
			}
			else{
				add(&myText,"");
			}	
		}
		
		
   	}
   
  
   return(0);
}

address alokasi(char text[]){
	//kamus
	address P;
	//algoritma
	P=(address) malloc(sizeof(ElmText));
	strcpy(textLine(P),text);
	next(P)=nil;	
	return (P);
}

void deAlokasi(address p){

	//Kamus
	
	//Algoritma
	free(p);
}

void printText(Text P,int align){
	// kamus
	address awal;
	int i;
	// algoritma
	awal = first(P);
	if(awal!=nil){
		while (awal!=nil){
			printf("\n");
			if(align==2){
				for(i=60-strlen(textLine(awal));i>=1;i--){
					printf(" ");
				}
			}
			else if (align==3){
				for(i=(60-strlen(textLine(awal)))/2;i>=1;i--){
					printf(" ");
				}
			}
			printf(textLine(awal));
			
			awal=next(awal);
		}
		
	}
}

void createText(Text *P){
	//Kamus
	
	//algoritma
	first(*P) = nil;
	last(*P) = nil;
}

void add(Text *P, char text[]){
	address Px;
	address awal;
	// algoritma
	Px = alokasi(text);
	awal = first(*P);
	if(awal==nil){
		first(*P)=Px; 
		last(*P)=Px; 	
	}
	else{
		next(last(*P)) = Px;
		last(*P)=Px;
	}
}

void del(Text *P){

	//Kamus
	address p;
	address sAwal;
	//Algoritma
	if(first(*P)!=nil){
		if(first(*P) == last(*P)){
			p = first(*P);
			first(*P) = nil;
			last(*P) = nil;
			deAlokasi(p);
		
		} else {
			sAwal=first(*P);
			while(next(sAwal)!=last(*P)){
				sAwal=next(sAwal);
			}
			p = last(*P);
			last(*P) = sAwal;
			next((*P).last) = nil;
			deAlokasi(p);
		}
	}
}

int jumlahHurufPadaText(Text P){
	// kamus
	address awal;
	int i,hasil=0;
	// algoritma
	awal = first(P);
	if(awal!=nil){
		while (awal!=nil){
			for(i=0;i<strlen(textLine(awal));i++){
				if(textLine(awal)[i]!=' ' && textLine(awal)[i] !='\n'&& textLine(awal)[i] !='\t'){
					hasil+=1;
				}
			}
			awal=next(awal);
		}
		
	}
	return hasil;
	
}

int jumlahHurufVokalPadaText(Text P){
	// kamus
	address awal;
	int i,hasil=0;
	// algoritma
	awal = first(P);
	if(awal!=nil){
		while (awal!=nil){
			for(i=0;i<strlen(textLine(awal));i++){
				if((tolower(textLine(awal)[i])=='a'||tolower(textLine(awal)[i])=='i'||tolower(textLine(awal)[i])=='u'||tolower(textLine(awal)[i])=='e'||tolower(textLine(awal)[i])=='o' ) && textLine(awal)[i]!=' ' && textLine(awal)[i] !='\n'&& textLine(awal)[i] !='\t'){
					hasil+=1;
				}
			}
			awal=next(awal);
		}
		
	}
	return hasil;
	
}

int jumlahKataPadaText(Text P){
	// kamus
	address awal;
	int i,hasil=0;
	// algoritma
	awal = first(P);
	if(awal!=nil){
		while (awal!=nil){
				for(i=0;i<strlen(textLine(awal));i++){
					if(textLine(awal)[i]!=' '&& textLine(awal)[i]!='\t'&&(textLine(awal)[i+1] ==' '||textLine(awal)[i+1] =='\t'||textLine(awal)[i+1] =='\0')){
						hasil++;
					}
				}
			awal=next(awal);
		}
		
	}
	return hasil;
	
}

int jumlahKataSamaPadaText(Text P){
	char tempText[30][60];
	char tempKata[30];
	int kata=0;
	int huruf=0;
	int hasil=0;
	int hasilTotal=0;
	int i,x,y;	
	address awal;


	awal = first(P);
		while (awal!=nil){
			kata++;   
		    huruf = 0;
			for( i=0; i<strlen(textLine(awal)); i++){  
		        if(textLine(awal)[i] != ' ' && textLine(awal)[i] != '\t'&& textLine(awal)[i] != '\n'&& textLine(awal)[i+1] != '\n'){  
		            tempText[kata][huruf] = tolower(textLine(awal)[i]); 
					huruf++; 
		        }  
		        else{  
					if(textLine(awal)[i-1] != ' '){
						kata++;   
		            	huruf = 0;	
					} 
		              
		        } 
		    }
			awal=next(awal);
			
		}
			
	
   	for(x = 0; x <= kata; x++){  
    	hasil = 0;
		strcpy(tempKata,tempText[x]); 
        for(y = 0; y <= kata; y++){ 
           if(strcmp(tempKata, tempText[y]) == 0 && strcmp(tempKata,"-") != 0&& strcmp(tempKata,"\0") != 0){  
               hasil++;   
               strcpy(tempText[y],"-");  
           } 
        }
        if(hasil==1){
           	hasil=0;
		}
        hasilTotal=hasilTotal+hasil;
         
    } 

	return hasilTotal;
}

void cariKataPadaText(Text P,char text[]){
	char tempText[30][60];
	int kata=1;
	int huruf=0;
	int kataGarisSembelumnya=0;
	int garis=1;
	int i;	
	boolean ketemu=0;
	address awal;


	awal = first(P);
	while (awal!=nil && ketemu!=1){
	    huruf = 0;
		for(i = 0; i < strlen(textLine(awal)); i++){  
	        if(textLine(awal)[i] != ' ' && textLine(awal)[i] != '\t'&& textLine(awal)[i] != '\n'&& textLine(awal)[i+1] != '\n'){  
	            tempText[kata][huruf] = textLine(awal)[i]; 
				huruf++; 
	        }  
	        else{  
				if(textLine(awal)[i-1] != ' '){
					kata++;
	            	huruf = 0;	
				} 
	              
	        } 
	    }
	    i=0;
	   
		while(ketemu != 1 && i <= kata){  
			if(strcmp(tempText[i],text) == 0){   
				gotoxy(62,28);printf("Ditemukan, kata ke-%d pada garis %d",i-kataGarisSembelumnya,garis);
				ketemu=1;
			}
			i++;
	    }
	    kataGarisSembelumnya=kata;
		kata++;
		garis++; 
		awal=next(awal);
		
		
		
	}	  
	if(!ketemu){
		gotoxy(62,28);printf("Tidak temukan ");
		
		
	}
}

void gotoxy(int x,int y){
	HANDLE handle;
	COORD coord;
	coord.X =x;
	coord.Y =y;
	handle =GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,coord);
}


