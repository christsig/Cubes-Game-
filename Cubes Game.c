#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 5
#define K1 3
#define K2 2
#define K3 2


struct node{
    int cubes[3]; 
    int isMax;
    int cost;
    struct node *nextNodes[6];
    struct node *path;
};


struct node *root;

int numOfCubesTaken(int move){
    if(move<=2){
        return 1;
    }
    if(move==3){
        return K1;
    }
    if(move==4){
        return K2;
    }
    if(move==5){
        return K3;
    }
}

struct node *newNode(struct node *n, int move){
    struct node *temp;
    int i,j;

    temp = (struct node *)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    for(i=0;i<3;i++){
        temp->cubes[i] = n->cubes[i];
    }
    temp->isMax = !(n->isMax);

    if(move == 0 || move == 3){
        temp->cubes[0] -= numOfCubesTaken(move);
    }
    else if(move == 1 || move == 4){
        temp->cubes[1] -= numOfCubesTaken(move);
    }
    else{
        temp->cubes[2] -= numOfCubesTaken(move);
    }

    return temp;
}

void init(struct node *n){
    int i=0;

    if(n == NULL)
        return;
    for(i=0;i<6;i++){
        if(i==0 || i==3){
            if(n->cubes[0]- numOfCubesTaken(i)>=0){
                n->nextNodes[i] = newNode(n,i);
                init(n->nextNodes[i]);
            }
            else{
                n->nextNodes[i] = NULL;
            }
        }
        else if(i==1 || i==4){
            if(n->cubes[1]- numOfCubesTaken(i)>=0){
                n->nextNodes[i] = newNode(n,i);
                init(n->nextNodes[i]);
            }
            else{
                n->nextNodes[i] = NULL;
            }
        }
        else{
            if(n->cubes[2]- numOfCubesTaken(i)>=0){
                n->nextNodes[i] = newNode(n,i);
                init(n->nextNodes[i]);
            }
            else{
                n->nextNodes[i] = NULL;
            }
        }

    }


}

void minimax(struct node *n){
    
    int counter = 0;
    int i,j;

    if(n==NULL){
        return;
    }
    for(i=0;i<6;i++){
        if(n->nextNodes[i] == NULL){
            counter++;
        }
    }
    if(counter == 6){
       
        if(n->isMax == 1){
           
            n->cost = -100;
        }
        else{
            n->cost = 100;
        }
    }
    else{
        for(i=0;i<6;i++){
           
            minimax(n->nextNodes[i]);
        }

        for(i=0;i<6;i++){
          
            if(n->nextNodes[i] != NULL){
                n->path = n->nextNodes[i];
                n->cost = n->nextNodes[i]->cost;
                break;
            }
        }
        for(j=i+1;j<6;j++){
            if(n->nextNodes[j] != NULL){
                if(n->isMax == 1){
                    if(n->nextNodes[j]->cost > n->cost){
                        n->cost = 100;
                        n->path = n->nextNodes[j];
                        break;
                    }
                }
                else{
                    if(n->nextNodes[j]->cost < n->cost){
                        n->cost = -100;
                        n->path = n->nextNodes[j];
                        break;
                    }
                }
            }

        }

    }
}
int gameOver(struct node *n){
    int i, counter =0;

    for(i=0;i<6;i++){
        if(n->nextNodes[i] == NULL){
            counter++;
        }
    }
    if(counter == 6){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    int i;
    struct node *game;
    int move;

    root = (struct node *)malloc(sizeof(struct node));
    if(root == NULL){
        exit(0);
    }
    for(i=0;i<3;i++){
        root->cubes[i] = M;
    }
    root->isMax = 1;

    init(root);
    minimax(root);

    game = root;

    for(i=0;i<3;i++){
        printf("%d ",game->cubes[i]);
    }
    printf("%d\n",game->isMax);

    while(gameOver(game) == 0){
        if(game->isMax == 1){
            game = game->path;
        }
        else{
            do{
                printf("Next move\n");
                printf("Take 1 red-->1\n");
                printf("Take 1 green-->2\n");
                printf("Take 1 yellow-->3\n");
                printf("Take K1 red-->4\n");
                printf("Take K2 green-->5\n");
                printf("Take K3 yellow-->6\n");
                printf("move = ");
                scanf("%d",&move);
            }while(game->nextNodes[move-1] == NULL);

            game = game->nextNodes[move-1];
        }

        for(i=0;i<3;i++){
            printf("%d ",game->cubes[i]);
        }
        printf("\n");
    }
    if(game->isMax == 1){
        printf("Winner is MIN\n");
    }
    else{
        printf("Winner is MAX\n");
    }
}
