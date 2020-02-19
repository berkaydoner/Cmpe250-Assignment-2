/*
Student Name: Berkay Döner
Student Number: 2017400117
Project Number: 2
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "RestaurantOrganizer.h"

using namespace std;

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }
}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){
    if(tableCapacity[heap[0]]>=groupSize){//checks if group can be placed
        tableCapacity[heap[0]]=tableCapacity[heap[0]]-groupSize;//updates the table's capacity
        outFile<<heap[0]<<endl;
        heapDown(0);/*since capacity of this table has decreased, it should be on a lower
        level of the max-heap, so it is percolated down.*/
    }
    else{
        outFile<<-1<<endl;//group is too big, write -1
    }
}

void RestaurantOrganizer::heapUp(int index){
    index++;//index is incremented as heap operations are done assuming first element is at index 1
    while(index>1&&tableCapacity[heap[index/2-1]]<tableCapacity[heap[index-1]]){
        /*This loop runs while index>1 and parent's value is smaller than element's value.*/
        /*This 3 lines swaps the value of heap[index-1] and heap[index/2-1] so that element's value
        and its parents value is swapped.*/
        int temp = heap[index-1];
        heap[index-1] = heap[index/2-1];
        heap[index/2-1] = temp;
        index = index/2;//next element is the parent of this element.
    }
}

void RestaurantOrganizer::heapDown(int index){
    index++;//index is started from 1.
    while(index*2<=numberOfTables){//This loop runs if this element has a child.
        int indexOfMaxChild=index*2;//max child is initialized as the left child.
        if(index*2!=numberOfTables&&tableCapacity[heap[index*2]]>=tableCapacity[heap[index*2-1]]) {
            if(tableCapacity[heap[indexOfMaxChild]]==tableCapacity[heap[indexOfMaxChild-1]]){
                /*If left child has the same capacity with the right child, max child is
                 the one with the smaller table number.*/
                if(heap[indexOfMaxChild]<heap[indexOfMaxChild-1]){
                    indexOfMaxChild++;//right child has a smaller table number, it is preferable.
                }
            }
            else {
                indexOfMaxChild++;//the right child has a bigger capacity, so it is preferable.
            }
        }
        if(tableCapacity[heap[index-1]]<tableCapacity[heap[indexOfMaxChild-1]]){
            //If max child has a bigger capacity, it should be swapped with this element.
                int temp = heap[index - 1];
                heap[index - 1] = heap[indexOfMaxChild - 1];
                heap[indexOfMaxChild - 1] = temp;
                index = indexOfMaxChild;//index is updated so that process occurs iteratively.
        }
        else if(tableCapacity[heap[index-1]]==tableCapacity[heap[indexOfMaxChild-1]]){
            /*If max child has the same capacity, it is only swapped if its table number is smaller
            than this element's table number. If that's not the case, loop should terminate.*/
            if(heap[index-1]>heap[indexOfMaxChild-1]){
                int temp = heap[index - 1];
                heap[index - 1] = heap[indexOfMaxChild - 1];
                heap[indexOfMaxChild - 1] = temp;
                index = indexOfMaxChild;//element and its child is swapped, so index should be updated.
            }
            else{
                break;//terminates the loop, since child has a bigger table number.
            }
        }
        else{
            break;//terminates the loop, since the maximum capacity of the children is smaller than this element.
        }
    }
}

void RestaurantOrganizer::printSorted(ofstream& outFile){
    /*This method iteratively writes the element on the root(max element) then updates its value to 0,
     * so that it should be percolated down and not encountered again.*/
    for(int i =0;i<numberOfTables;i++){
        outFile << tableCapacity[heap[0]] << " ";//Writes the capacity
        tableCapacity[heap[0]] = 0;//Updates the capacity to minimum
        heapDown(0);//Updates the heap
    }
}

// YOU CAN ADD YOUR HELPER FUNCTIONS

