#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queue.c"



//若是A instruction返回0
//若是label symbol 或 variable symbol返回1
//若是C instruction返回2
int det_ins(char *c){
	int i=0;
	char s[10]={"\0"};
	while(c[i]!='\0'){
		if(c[i]=='@'){
			if ( strlen(c+i+1) == strlen(itoa(atoi(c+i+1),s,10))) {
//				printf("integer\n");
				return 0;
			}else{
//				printf("string\n");
				return 1;
			}
		}
		else if(c[i]=='=' || c[i]==';'){
			return 2;
		}
		i++;
	}
	return -1;
}

//十進位轉二進位 
int *dec2bin(int n){
	int i=0;
	int *a=calloc(16,sizeof(int));
	while(n>0){
		a[i]=(n%2);
		i++;
		n=n/2;
	}
	printf("\n");
	return a;
}

void printbin(int *num){
    for(int i=15; i >= 0; i--)
        printf("%d",num[i]);
    printf("\n");
}
//integer string to integer array
char *int2str(int *n){
	char *output=malloc(sizeof(char)*17);;
	int i=0;
	int j=15;
	while(i<16){
		output[i]=n[j]+'0';
		i++;
		j--;
	}
	output[16]='\n';
	output[17]='\0';
	return output;
}

//判斷是否為jump instruction 
int str_equal(char *str){
	for(int i=0;i<strlen(str);i++){
		if(str[i]=='='){
			return i;
		}
	}
	return -1;
}

//將c instruction 的 dest 轉成machine code 
char *find_dest_ins_bin(char *str){
	char dest_arr[8][4]={"","M","D","MD","A","AM","AD","AMD"};
	for (int n=0;n<8;n++){
		if(strcmp(str,dest_arr[n])==0){
			int i=2;
			char *a=malloc(3*sizeof(char));
			while(n>0){
				a[i]=(n%2)+'0';
				i--;
				n=n/2;
			}
			while(i>=0){
				a[i]='0';
				i--;
			}
			a[3]='\0';
			return a;
		}
	}
}
//將c instruction 的 jump 轉成machine code 
char *find_jump_ins_bin(char *str){
	char dest_arr[8][4]={"","JGT","JEQ","JGE","JLT","JNE","JLE","JMP"};
	for (int n=0;n<8;n++){
		if(strcmp(str,dest_arr[n])==0){
			int i=2;
			char *a=malloc(3*sizeof(char));
			while(n>0){
				a[i]=(n%2)+'0';
				i--;
				n=n/2;
			}
			while(i>=0){
				a[i]='0';
				i--;
			}
			a[3]='\0';
			return a;
		}
	}
}
//將c instruction 的 comp 轉成machine code
char *find_comp_ins_bin(char *str){
	printf("%s\n",str);
	char areg_arr[18][4]={"0","1","-1","D","A","!D","!A","-D","-A","D+1","A+1","D-1","A-1","D+A","D-A","A-D","D&A","D|A"};
	char mem_arr[18][4]={"","","","","M","","!M","","-M","","M+1","","M-1","D+M","D-M","M-D","D&M","D|M"};
	char bin_arr[18][7]={"101010","111111","111010","001100","110000","001101","110001","001111","110011","011111","110111","001110","110010","000010","010011","000111","000000","010101"};
    char *concated=calloc(9,sizeof(char));
	for (int n=0;n<18;n++){
		if(strcmp(str,areg_arr[n])==0){
			strcat(concated,"0");
			return strcat(concated,bin_arr[n]);
		}
	}
	printf("\n");
	for (int n=0;n<18;n++){
		if(strcmp(str,mem_arr[n])==0){
			strcat(concated,"1");
			return strcat(concated,bin_arr[n]);
		}
	}
}
//將label symbol寫入symbol table 
void en_label_symbol(FILE *fptr1,struct Queue *queue){
	int num=0;
	char str[100];
	int count=0;
    while (fgets(str,sizeof(str),fptr1) != NULL)
    {	
    	char *find = strchr(str,'\n');
    	if(find){
        	*find = '\0';
    	}
    	if(str[0]!='/' && strlen(str)!=0){

			int len=strlen(str);
			char *label_sym=calloc(len+1,sizeof(char));
			int i=1;
    		if(str[0]=='('){
    			while(str[i]!=')'){
    				label_sym[i-1]=str[i];
    				i++;
				}
				label_sym[i-1]='\0';
    			enqueue(queue,num-(count++),label_sym);
			}
    		num++;
		}
	}

}
//將variable symbol寫入symbol table 
void en_var_symbol(FILE *fptr1,struct Queue *queue){
	
	int num=16;
	char strv[100];
    while (fgets(strv,sizeof(strv),fptr1) != NULL)
    {	
    	
//    	printf("str=%s\n",strv);
    	char *find = strchr(strv,'\n');
    	if(find){
        	*find = '\0';
    	}
    	
    	if(strv[0]!='/' && strlen(strv)!=0){
//    		printf("det_ins(str)=%d\n",det_ins(strv));
    		
			if (det_ins(strv)==1){
				int len=strlen(strv);
	//			char label_sym[len+1];
				char *var_sym=calloc(len+1,sizeof(char));
				int i=0;
				int j=0;
				while(strv[j]!='@'){
					j++;
				}
				
//				printf("var=%s\n",p);
    			while(strv[i+j+1]!='\0'){
    				var_sym[i]=strv[i+j+1];
    				i++;
				}
				
				var_sym[i]='\0';
//    			printf("num=%d\n",num);
//    			printf("%d\n",det_ins(strv));
    			
    			if (check_queue(queue,var_sym)==-1){
//    				printf("len=%d i=%d\n",len,i);
//    				printf("%s %s %d\n",queue->front->symbol,var_sym,strcmp(queue->front->symbol,var_sym));
//    				printf("var_sym=%s\n",var_sym);
    				enqueue(queue,num,var_sym);
    				num++;
				}
	    						
			}
		}
	}
}

int main(void){

	struct Queue *queue=create_predefined();
	FILE *fptr1,*fptr2;
	
	char *filename1="D:\\nand2tetris\\nand2tetris\\projects\\06\\max\\Max.asm";
	char *filename2="D:\\nand2tetris\\nand2tetris\\projects\\06\\max\\Max.hack";
//	char *filename1="D:\\nand2tetris\\nand2tetris\\projects\\06\\rect\\Rect.asm";
//	char *filename2="D:\\nand2tetris\\nand2tetris\\projects\\06\\rect\\Rect.hack";
//	char *filename1="D:\\nand2tetris\\nand2tetris\\projects\\06\\pong\\Pong.asm";
//	char *filename2="D:\\nand2tetris\\nand2tetris\\projects\\06\\pong\\Pong.hack";
	
	fptr1=fopen(filename1,"r");
	en_label_symbol(fptr1,queue);
	fclose(fptr1);
	
	fptr1=fopen(filename1,"r");
	en_var_symbol(fptr1,queue);
	fclose(fptr1);
	
//	show_queue(queue);
//	return 0;
	
	char str[100];
	int num=0;
	char *ptr;
	fptr1=fopen(filename1,"r");
	fptr2=fopen(filename2,"w");
	
	//https://reurl.cc/10qN3m
    while (fgets(str,sizeof(str),fptr1) != NULL)
    {	//一行行讀檔 
    	char *find = strchr(str,'\n');
    	if(find)
    	{
        	*find = '\0';
    	}
    	//去除空白及註解 
    	if(str[0]!='/' && strlen(str)!=0){
    		ptr=str;
    		printf("det_ins(ptr)=%d\n",det_ins(ptr));
    		//A instruction
    		if (det_ins(ptr)==0){
				int j=0;
				while(str[j]==' ' || str[j]=='@'){
					j++;
				}
    			int num_ptr=atoi(ptr+j);
    			int* num_bin=dec2bin(num_ptr);
    			char *str_int=int2str(num_bin);
    			fputs(str_int,fptr2);
    			free(str_int);
			}
			//label symbol or variable symbol
    		else if (det_ins(ptr)==1){
    			int i=0;
    			int j=0;
				int len=strlen(str);
				char *var_sym=calloc(len+1,sizeof(char));
				while(str[j]!='@'){
					j++;
				}
				
    			while(str[i+j+1]!='\0'){
    				var_sym[i]=str[i+j+1];
    				i++;
				}
				int num_ptr=check_queue(queue,var_sym);
    			int* num_bin=dec2bin(num_ptr);
    			char *str_int=int2str(num_bin);
    			fputs(str_int,fptr2);
    			free(str_int);
			}
			//C instruction
			else if(det_ins(ptr)==2){
				char *comp_result;
				char *dest_result;
				char *jmp_result;
				char *empty="";
				int j=0;
				while(str[j]==' '){
					j++;
				}
				if(str_equal(ptr+j)==-1){
					// jump instruction
					char *p=strchr(ptr+j,';');
					*p='\0';
					char *comp=p+1;
					comp[3]='\0';
					if(strlen(comp)>10 || strlen(ptr+j)>10){
						printf("Make sure delete blank space and commend\n");
					}
					comp_result=find_comp_ins_bin(ptr+j);
					dest_result=find_dest_ins_bin(empty);
					jmp_result=find_jump_ins_bin(comp);
				}else if(str_equal(ptr+j)!=-1){
					//non jump instruction
					char *p=strchr(ptr+j,'=');
					*p='\0';
					char *comp=p+1;
					if(strlen(comp)>10 || strlen(ptr+j)>10){
						printf("Make sure delete blank space and commend\n");
					}
					comp_result=find_comp_ins_bin(comp);
					dest_result=find_dest_ins_bin(ptr+j);
					jmp_result=find_jump_ins_bin(empty);

				}
				// 合併字串 
				char *c_ins_result=calloc(17,sizeof(char));
				strcat(c_ins_result,"111");
				strcat(c_ins_result,comp_result);
				strcat(c_ins_result,dest_result);
				strcat(c_ins_result,jmp_result);
				c_ins_result[16]='\n';
				c_ins_result[17]='\0';
				fputs(c_ins_result,fptr2);
				free(comp_result);
				free(dest_result);
				free(jmp_result);
				free(c_ins_result);
			}
	        num++;
		}

    }
    printf("num=%d\n",num);
    fclose(fptr1);
	fclose(fptr2);
    free(queue);
    
	return 0;
}
