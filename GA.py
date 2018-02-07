import random
import matplotlib.pyplot as plt
GEN_SIZE = 100      #Number of organisms
GENE_NO = 20        #Number of genes in each organisms
GENE_TYPES = 4        #Types of genes

class Organism:
    def __init__(self, gene=None, fitness=None):
        self.gene = gene
        self.fitness = fitness

    def FitnessCalcOrg(self):
        count = 0
        for i in range(GENE_NO):
            if self.gene[i]==ideal_org.gene[i]:
                count += 1
        return count

    def initialise(self):
        temp=[]
        for i in range(GENE_NO):
            randNum = random.randint(0,100000) % 4
            if randNum == 0:
                temp.append("A")
            elif randNum == 1:
                temp.append("B")
            elif randNum == 2:
                temp.append("C")
            else:
                temp.append("D")
        self.gene = temp
        self.fitness = self.FitnessCalcOrg()



    def display(self):
        print ''.join(self.gene)        #An organism

class Generation:
    def __init__(self):
        self.members = []       #members of the Generation
        self.averageFitness = None
        self.totalFitness = None

    def avg_fitness(self):
        FitnessEach = []
        for i in self.members:
            FitnessEach.append(i.fitness)
        self.totalFitness = sum(FitnessEach)
        return sum(FitnessEach)/GEN_SIZE


    def populate_gen(self):
        for i in range(GEN_SIZE):
            temp = Organism()
            temp.initialise()
            self.members.append(temp)
            self.averageFitness = self.avg_fitness()

    def display_gen(self):
        for i in self.members:
            i.display()     #A generation of organism

    def display_fitness(self):
        for i in self.members:
            print i.fitness

    def set_fitness(self):
        FitnessEach = []
        for i in self.members:
            FitnessEach.append(i.fitness)
        self.totalFitness = sum(FitnessEach)
        self.averageFitness = float(self.totalFitness) / float(GEN_SIZE)

def select_One(gen):
    stop_point = random.randint(0,1000000) % (gen.totalFitness+1)
    sum = 0
    for org in gen.members:
        sum = sum + org.fitness
        if sum>=stop_point:
            return org

def crossover(parent1, parent2):
    child = Organism()
    crossPoint = random.randint(0,100000)%GENE_NO
    temp=[]
    for i in range(GENE_NO):
        mut_factor = random.randint(0, 199990) % 1000
        if mut_factor == 0:
            x = random.randint(0, 100000) % GENE_TYPES
            if x == 0:
                temp.append('A')
            elif x == 1:
                temp.append('B')
            elif x == 2:
                temp.append('C')
            else:
                temp.append('D')
        if i <= crossPoint:
            temp.append(parent1.gene[i])
        else:
            temp.append(parent2.gene[i])
    child.gene = temp
    child.fitness = child.FitnessCalcOrg()
    return child

def evolve_gen(current_gen):
    next_gen = Generation()
    for i in range(100):
        next_gen.members.append(crossover(select_One(current_gen),select_One(current_gen)))
    next_gen.set_fitness()
    return next_gen

def stopGeneration(curGen):
    for i in range(GEN_SIZE):
        if curGen.members[i].fitness == GENE_NO:
            return 1
        else:
            return 0

generationList = []
fitnessList = []

ideal_org = Organism()
ideal_org.initialise()      #initialising the ideal organism

firstGen = Generation()
firstGen.populate_gen()

currentGen = Generation()
currentGen = evolve_gen(firstGen)
prevGen = Generation()
count = 1

while not stopGeneration(currentGen):
    print "Average fitness of generation %d is %f" % (count, currentGen.averageFitness)
    generationList.append(count)
    fitnessList.append(currentGen.averageFitness)
    prevGen.members = currentGen.members
    prevGen.averageFitness = currentGen.averageFitness
    prevGen.totalFitness = currentGen.totalFitness
    currentGen = evolve_gen(currentGen)
    count += 1

print "Ideal organism achieved in generation", count + 1

plt.plot(generationList, fitnessList, 'b-')
plt.axis([0, count + 2, 0, 20])
plt.show()
    