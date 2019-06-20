#CODE FROM: https://en.wikipedia.org/wiki/Tower_of_Hanoi
#USED AS TEMPLATE FOR C IMPLEMENTATION

import time

A = [i for i in range(5, 0, -1)]
height = len(A)-1 #stable height value for animation
B = []
C = []

def move(n, source, target, auxiliary):
    if n > 0:
        # move n - 1 disks from source to auxiliary, so they are out of the way
        move(n - 1, source, auxiliary, target)

        # move the nth disk from source to target
        target.append(source.pop())

        # Display our progress using a recursive function to draw it out
        drawDisks(A, B, C, height)
        print("") #provide spacing
        time.sleep(0.3) #pause for a moment to animate

        # move the n - 1 disks that we left on auxiliary onto target
        move(n - 1, auxiliary, target, source)

def drawDisks(A, B, C, position, width = 2 * int(max(A))):
    #width parameter defaults to double of the largest sized disk in the initial tower.
    if position >= 0:
        #if A has a value in the list at the given position, create a disk at its position (height)
        valueInA = " " if position >= len(A) else createDisk(A[position])
        #same for B and C
        valueInB = " " if position >= len(B) else createDisk(B[position])
        valueInC = " " if position >= len(C) else createDisk(C[position])

        #print each row
        print("{0:^{width}}{1:^{width}}{2:^{width}}".format(valueInA, valueInB, valueInC, width=width))

        #recursivly call this method again to the next position (height)
        drawDisks(A, B, C, position-1, width)
    else:
        #when done with recurisve, print column labels
        print("{0:^{width}}{1:^{width}}{2:^{width}}".format("A", "B", "C", width=width))

def createDisk(size):
    '''simple recursive method to create a slanted disk.'''
    if size==1:
        return "/\\"
    else:
        return "/" + createDisk(size-1) + "\\"

# initiate call from source A to target C with auxiliary B
move(len(A), A, B, C)
