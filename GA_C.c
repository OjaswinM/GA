//Version 2 adds mutation and stop condition

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define GEN_SIZE 100     //Number of organisms
#define GENE_NO 20          //Number of genes in each organism
#define GENE_TYPES 4        //Types of genes

//structure to store the organism
struct organism
{
    char gene[GENE_NO];
    int fitness;
};

typedef struct organism ORG;

ORG init_organism(void);        //assigns random genes to the organism passed
void display_org(ORG a);        //used to display the genes
void display_gen(ORG a[]);      //to display the generation
void populate_gen(ORG gen[]);       //populates the starting generation
int fitness_calculator(ORG a,ORG ideal);        //returns fitness of organism
void assign_fitness(ORG gen[],ORG ideal);      //calculates fitness of all the organisms in the generation
float avg_gen_fitness(ORG gen[]);     //returns average fitness of the generation
int check_stop_condition(ORG gen[]);        //returns 1 if stop condition is satisfied else 0
ORG* evolve_gen(ORG gen[]);      //returns the new generation after evolution
int total_fitness_calculator(ORG gen[]);    //calculates total fitness of the generation
ORG select_one(ORG gen[]);  //select one organism from the generating. Organisms with higher fitness have more chance of being selected
ORG crossover(ORG par1,ORG par2);   //crosses the genes of two parents to create a new organism
void copy_gen(ORG gen1[],ORG gen2[]);   //coping gen2 to gen2

int main()
{
    ORG ideal_org,a,current_gen[GEN_SIZE],prev_gen[GEN_SIZE];
    int i=0,generation=0;

    //seeding the rand()
    srand(time(0));

    //initialising ideal organism
    ideal_org=init_organism();
    populate_gen(current_gen);
    assign_fitness(current_gen,ideal_org);
    //display_gen(current_gen);
    printf("Average fitness of initial generation is %f\n",avg_gen_fitness(current_gen));
    printf("\n--------------------STARTING EVOLUTION---------------------------\n\n");

    while(!check_stop_condition(current_gen))
    {
        copy_gen(prev_gen,current_gen);
        //display_gen(prev_gen);
       copy_gen(current_gen,evolve_gen(current_gen));
        assign_fitness(current_gen,ideal_org);
        //display_gen(current_gen);
        printf("Generation %d: Average fitness is %f\n",i,avg_gen_fitness(current_gen));
        i++;
    }

    printf("\n--------------------STOPPING EVOLUTION---------------------------\n\n");
    printf("Ideal organism achieved in generation %d!\n",i);
    //display_gen(current_gen);
}

ORG init_organism(void)
{
    ORG temp;
    int i,test;

    //traversing the genes
    for(i=0;i<GENE_NO;i++)
    {
        //randomly assigning one of the four gene types
        test=rand()%GENE_TYPES;
        switch(test)
        {
            case 0:temp.gene[i]='A';break;
            case 1:temp.gene[i]='B';break;
            case 2:temp.gene[i]='C';break;
            case 3:temp.gene[i]='D';break;
        }
    }

    //initializing fitness
    temp.fitness=-1;
    return temp;
}

void display_org(ORG a)
{
    int i;

    //traversing the genes
    for(i=0;i<GENE_NO;i++)
    {
        printf("%c",a.gene[i]);
    }
    printf("\tFitness: %d\n",a.fitness);
}

void populate_gen(ORG gen[])
{
    int i;

    //for each organism in the generation, initialize
    for(i=0;i<GEN_SIZE;i++)
    {
        gen[i]=init_organism();
    }
}

void display_gen(ORG a[])
{
    int i;

    //for each organism in generation
    for(i=0;i<GEN_SIZE;i++)
    {
        printf("%d. ",i);
        display_org(a[i]);
    }
}

int fitness_calculator(ORG a, ORG ideal)
{
    int count=0,i;

    //for each gene
    for(i=0;i<GENE_NO;i++)
    {
        //if gene at position i is same as ideal gene at position i increase counter
        if(a.gene[i]==ideal.gene[i])
            count++;
    }
    return count;
}

void assign_fitness(ORG gen[],ORG ideal)
{
    int i;

    //assign fitness to each organism of generation
    for(i=0;i<GEN_SIZE;i++)
    {
        gen[i].fitness=fitness_calculator(gen[i],ideal);
    }
}

float avg_gen_fitness(ORG gen[])
{
    int i;
    float sum=0;

    //for each organism in generation
     for(i=0;i<GEN_SIZE;i++)
    {
        //printf("%d. %d\n",i,gen[i].fitness);
        sum=sum+gen[i].fitness;
    }
    return(sum/GEN_SIZE);
}

int check_stop_condition(ORG gen[])
{
    int i;
    //traversing the generation
    for(i=0;i<GEN_SIZE;i++)
    {
        //if ideal fitness is achieved
        if(gen[i].fitness==GENE_NO)
        {
            return 1;
        }
    }
    return 0;
}

ORG* evolve_gen(ORG gen[])
{
    int i;
    static ORG next_gen[GEN_SIZE];
    for(i=0;i<GEN_SIZE;i++)
    {
        next_gen[i]=crossover(select_one(gen),select_one(gen));
    }
    return next_gen;
}

int total_fitness_calculator(ORG gen[])
{
    //calculates total fitness
    int i,sum=0;
    for(i=0;i<GEN_SIZE;i++)
    {
        sum=sum+gen[i].fitness;
    }
    return sum;
}

ORG select_one(ORG gen[])
{
    int sum=0,fitness_total,i,stop_point;
    fitness_total = total_fitness_calculator(gen);

    //a random stop point
    stop_point=rand()%(fitness_total+1);
    for(i=0;i<GEN_SIZE;i++)
    {
        //the fitnesses are added till the sum is greater than the stop point. That organism is selected
        sum=sum+gen[i].fitness;
        if(sum>=stop_point)
        {
            return(gen[i]);
        }
    }
}

ORG crossover(ORG par1,ORG par2)
{
    ORG child;
    int mut_factor,test;
    int cross_point,i;
    cross_point=rand()%GENE_NO;
    for(i=0;i<GENE_NO;i++)
    {
        mut_factor=rand()%1000;
        if(i<=cross_point)
        {
            if(mut_factor==0)
            {
                test=rand()%GENE_TYPES;
                switch(test)
                {
                    case 0:child.gene[i]='A';break;
                    case 1:child.gene[i]='B';break;
                    case 2:child.gene[i]='C';break;
                    case 3:child.gene[i]='D';break;
                }
            }
            else
            {
                child.gene[i]=par1.gene[i];
            }
        }
        else
        {
            if(mut_factor==0)
            {
                test=rand()%GENE_TYPES;
                switch(test)
                {
                    case 0:child.gene[i]='A';break;
                    case 1:child.gene[i]='B';break;
                    case 2:child.gene[i]='C';break;
                    case 3:child.gene[i]='D';break;
                }
            }
            else
            {
                child.gene[i]=par2.gene[i];
            }
        }
    }
    child.fitness=-1;
    return child;
}

void copy_gen(ORG gen1[],ORG gen2[])
{
    int i;
    for(i=0;i<GEN_SIZE;i++)
    {
        gen1[i]=gen2[i];
    }
}
