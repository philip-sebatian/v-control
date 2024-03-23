    
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int top=0;

typedef struct act{
  char action;
  char letter ;
}actions;
actions action_stack[1024];
actions * get_action_stack(int size){
  actions * action_stack = (actions *)malloc(size*sizeof(actions));
  return action_stack;
}

//function for getting  the dp pointer
int ** get_dp(char * word1,char *word2){
  int l1 = strlen(word1);
  int l2 = strlen(word2);
  //dynamically allocates a 2d array for computation of dp
  int **dp=(int**)malloc((l1+1)*sizeof(int *));
  for(int i =0 ; i< l1+1;i++){
    dp[i]=(int*)malloc((l2+1)*sizeof(int *));
  }
  //fills the base cases in the dp table and also fills other values with zeroes
  for(int i =0 ; i < l1+1;i++){
    for(int j=0 ; j < l2+1;j++){
      dp[i][j]=0;
    }
  }
  for(int i=0 ; i<l1+1;i++){
    dp[i][0]=i;
  }
  for(int i =0; i <l2+1;i++){
    dp[0][i]=i;
  }
  
  //the dp loop for calculating distance of the strings
  for(int i =1; i<l1+1;i++){
    for(int j=1 ; j<l2+1;j++){
      if(word1[i-1]==word2[j-1]){

        dp[i][j]=dp[i-1][j-1];
      }
      else{
        if(dp[i-1][j]<dp[i][j-1]){
          dp[i][j]=dp[i-1][j]+1;
        }
        else{
          dp[i][j]=dp[i][j-1]+1;
        }
      }
    }
  }
  return dp;

}

//for tracing actions on action stack array dynamically alocated by actions
actions * trace_actions(actions * action_stack,int **dp,char * word1,char * word2){
  int i =strlen(word1);
  actions temp_action ;
  int j =strlen(word2);
  while(i>0 && j>0){
    if(word1[i-1]==word2[j-1]){
      i--;
      j--;
    }
    else{
      if(dp[i-1][j]+1==dp[i][j] && i!=0){
        temp_action.action='r';
        temp_action.letter=word1[i-1];
        action_stack[top]=temp_action;
        printf("%s-%c\n","remove",word1[i-1]);
        i--;
        top++;
      }
      else{
        if(j==0){
          continue;
        }
          temp_action.action='a';
          temp_action.letter=word2[j-1];
          action_stack[top]=temp_action;
          printf("%s-%c\n","add",word2[j-1]);
        
          j--;
          top++;
      }
    }
  }
  
  while(i>0){
    temp_action.action='r';
    temp_action.letter=word1[i-1];
    action_stack[top]=temp_action;
    printf("%s-%c\n","remove",word1[i-1]);
    top++;
    i--;
  }
  while(j>0){
    temp_action.action='a';
    temp_action.letter=word2[j-1];
    action_stack[top]=temp_action;
    printf("%s-%c\n","add",word2[j-1]);
    top++;
    j--;
  }
  return action_stack;
}
//main point
int main(int argc, char * argv[]){
  actions *action_stack=get_action_stack(1024);
  char * word1 = argv[1];
  char * word2 = argv[2];
  int l1 = strlen(word1);
  int l2 = strlen(word2);
  int **dp=get_dp(word1,word2);
  
  printf("\n\n");
  for(int i =0 ; i < l1+1;i++){
    for(int j=0 ; j < l2+1;j++){
      printf("%d\t",dp[i][j]);
    }
    printf("\n");
  }
  /*this is for backtracking the actions that were perforemed to obtain the string the s1*/
  
  /*while(i>0 && j>0){
    if(word1[i-1]==word2[j-1]){
      i--;
      j--;
    }
    else{
      if(dp[i-1][j]+1==dp[i][j] && i!=0){
        temp_action.action='r';
        temp_action.letter=word1[i-1];
        action_stack[top]=temp_action;
        printf("%s-%c\n","remove",word1[i-1]);
        i--;
        top++;
      }
      else{
        if(j==0){
          continue;
        }
          temp_action.action='a';
          temp_action.letter=word2[j-1];
          action_stack[top]=temp_action;
          printf("%s-%c\n","add",word2[j-1]);
        
          j--;
          top++;
      }
    }
  }
  
  while(i>0){
    temp_action.action='r';
    temp_action.letter=word1[i-1];
    action_stack[top]=temp_action;
    printf("%s-%c\n","remove",word1[i-1]);
    top++;
    i--;
  }
  while(j>0){
    temp_action.action='a';
    temp_action.letter=word2[j-1];
    action_stack[top]=temp_action;
    printf("%s-%c\n","add",word2[j-1]);
    top++;
    j--;
  }*/
  
  trace_actions(action_stack,dp,word1,word2);
  printf("\n\n");
 int curr =0 ;
 while(curr<top){
  if(action_stack[curr].action=='r')
   printf("%s %c\n","remove",action_stack[curr].letter);
   else
   printf("%s %c\n","add",action_stack[curr].letter);
   curr++;
 }
 free(dp);
}