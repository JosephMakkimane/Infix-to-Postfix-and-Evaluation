#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<conio.h>

char precedence(char a, char b){
    if(((a=='+'||a=='-') && (b=='*'||b=='^'||b=='/'||b=='%')) || ((a=='*'||a=='/'||a=='%') && (b=='^'))){
        return(b);
    }
    return(a);
}

char * convert(char * infx){
int top =-1, count =0;
char * pstfx;
char * exp;
exp = (char *) malloc(sizeof(char));
pstfx = (char *) malloc(sizeof(char));
strcpy(exp," ");
strcpy(pstfx," ");
char operators[20];
    int l = strlen(infx);
    for(int i=0; i<l; i++){
        char sym=infx[i];

/*if((isdigit(sym))&&(i==0))
strcpy(pstfx,&sym);*/

        if(isdigit(sym))
            strncat(pstfx, &sym, 1);
       
        else if(sym==' '){
            char s=infx[i-1];
           
            /*if(s=='+'|| s=='-' || s=='*' || s=='^' || s=='/' || s=='%'){
               
            }*/
            if(isdigit(s)){
                if(count==0){
                    //strcpy(exp," ");
                    strcat(exp,pstfx);
                    strcpy(pstfx," ");
                    count++;
                }
                strcat(exp,pstfx);
                strcpy(pstfx," ");
            }
           
        }
       
        else if(sym=='+'|| sym=='-' || sym=='*' || sym=='^' || sym=='/' || sym=='%'){
            M:
            if(top==-1){
                operators[0]=sym;
                top++;
                continue;
            }
            if(precedence(operators[top],sym)==operators[top]){
                strcat(exp," ");
                strncat(exp,&operators[top--],1);
                goto M;                
            }
            else
                operators[++top]=sym;
        }
        else if(sym=='('){
            sym=infx[++i];
            char *temp; int marker=0, c=0;
temp = (char *) malloc(sizeof(char));
strcpy(temp,"");
            while(sym!=')'){
               
                if(c==0 && sym !=' '){
                    strcpy(temp,sym+"");
                    c+=1;
                }
               
                strncat(temp,&sym,1);
                sym=infx[++i];
                if(sym=='('){
                    marker++;
                }
                else if((sym==')')&&(marker!=0)){
                    strncat(temp,&sym,1);
                    sym=infx[++i];
                    marker--;
                }

            }
            strcat(exp,convert(temp));
        }

    }
    L:
    if(top!=-1){
        strcat(exp," ");
        strncat(exp,&operators[top--],1);
        goto L;
    }
return(exp);
}

int pow(int a, int b){
int c=1;

for(int i=1; i<=b; i++){
c*=a;
}
return(c);
}

int solve(char * exp){
int l = strlen(exp);
int i;
int r[30],top=-1;

char * temp;
temp = (char *) malloc(sizeof(char));
strcpy(temp,"");

for(i=0; i<l; i++){
char sym=exp[i];

if(isdigit(sym))
strncat(temp,&sym,1);

else if(sym == ' '){
if(i==0)
break;

char c=exp[i-1];

if(isdigit(c)){

int j = strlen(temp);
int a=0, k,count=0;

for(k=j-1; k!=-1;k--){
char sym=temp[k];
if(isdigit(sym)){

a+=((int) sym-'0')*pow(10,count++);
//printf("%d",a);
}
else if((sym==' ')&&(k!=j-1)){
break;
}
}
strcpy(temp," ");
r[++top]=a;
}

}
else if(sym=='+'|| sym=='-' || sym=='*' || sym=='^' || sym=='/' || sym=='%'){
int a=r[top--];
int b=r[top--];
int h;
if(sym=='+')
h=(b+a);
if(sym=='-')
h=(b-a);
if(sym=='*')
h=(b*a);
if(sym=='/')
h=((int)b/a);
if(sym=='^')
h=pow(b,a);
if(sym=='%')
h=(b%a);
r[++top]=h;
}

}
return(r[top]);
}

char * removeLeading(char *str)
{
    int idx = 0, j, k = 0;
char *str1;
str1 = (char *) malloc(sizeof(char));
    // Iterate String until last
    // leading space character
    while (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\n')
    {
        idx++;
    }
 
    // Run a for loop from index until the original
    // string ends and copy the content of str to str1
    for (j = idx; str[j] != '\0'; j++)
    {
        str1[k] = str[j];
        k++;
    }
 
    // Insert a string terminating character
    // at the end of new string
    str1[k] = '\0';
 
    // Print the string with no whitespaces
    return(str1);
}

int main(){
char * input;
input = (char *) malloc(sizeof(char));
printf("Enter an infix Expression: ");
scanf("%[^\n]s",input);

printf("%s",convert(input));
strcpy(input,convert(input));
strcat(input," ");
strcpy(input,removeLeading(input));
printf("\n%d",solve(input));
getch();
    return 0;
}
