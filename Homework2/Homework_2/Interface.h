#pragma once
#include <string>
#include <vector>
#include <cstddef>//size_t
#include <stdexcept>
#include <queue>
#include "Exception_OutOfMemory.h"

using std::string;
using std::vector;
using std::size_t;
using std::queue;

struct Worker
{
    /// @brief Worker name
    string name;
    /// @brief Parent node
    Worker* boss = nullptr; // parent node
    /// @brief Number of all workers below him in the Hierarchy
    size_t subordinatesNum = 0;
    /// @brief Pointers to direct subordinates
    vector<Worker*> servants; 
    
};

class Hierarchy
{
private:
    //fields
    /// @brief Default boss name
    const string BOSS_NAME="Uspeshnia";
    /// @brief Pointer to the root node 
    Worker* boss=nullptr; 
    /// @brief Hierarchy can have a name
    string objName;

    //methods
    ///  @brief Turns data string into a tree
    void processData(const string& data); 
    /// @brief Helper for processData. Finds the next name while working with the data
    string getNextName(const string& data,size_t& index);
    /// @brief Deletes all workers with recursion
    void deleteHierarchy(Worker* currentNode);
    /// @brief Searches for the worker in the tree
    /// @return Worker pointer if found , nullptr is not
    Worker* findWorker(const string& name,Worker* current) const;
    /// @brief Returns true if symbow is '-', '\n' , '\t' or ' '
    bool isEmptySymb(const char symb) const;
    /// @brief Recursively creates copy of each node in the tree
    Worker* copyTree(Worker* nodeToCopy, Worker* previous);
    /// @brief Takes sorted vector and adds a new item in it
    void addInSorter(vector<Worker*>& vec, Worker* item);
    /// @brief Returns the Hierarchy as a string
    string printNode(Worker* node) const;
    /// @brief Returns tree height . Used for longest chain
    size_t getHeight(Worker* node) const;
    /// @brief Used after object creation to set the numbers corectly
    size_t findAllWorkersSubordinatesNum(Worker* node);
    /// @brief Returns the number of employees with more than 20 subordinates on level in the tree
    size_t findOverloadedOnLvl(const int level, Worker* node) const;
    /// @brief Removes a worker from a vector
    void removeServant(vector<Worker*>& vec, Worker* worker);
    /// @brief Modifies value of subordinatesNum of each worker up to the root. Used when moving, adding, removing workers
    void updateSubNumAbove(const int modifier, Worker* start);
    /// @brief Incorporates the tree , starting from the given node
    void incorporateTree(Worker* node);
    /// @brief Returns the worker with biggest salary in the vector
    Worker* findBiggestSalary(const vector<Worker*>& vec) const;
    /// @brief Modernizes tree. Level is the level in tree regarding the given node
    void modernizeOnLvl(const size_t level, Worker* node);
    /// @brief Merges two Hierarchy with sorted by name employees .Used by join
    void mergeSorted(const Hierarchy& other , Hierarchy& newObj,  Worker* searched, Worker* lastBoss) const;

public:
    /// @brief Move constructor
    Hierarchy(Hierarchy&& r) noexcept;
    /// @brief Copy constructor that can set new name to current object
    Hierarchy(const Hierarchy& r,const string newName="");
    /// @brief Default constructor
    Hierarchy(const string& data,const string& name="");
    /// @brief Destructor. Calls deleteHierarchy
    ~Hierarchy() noexcept;
    void operator=(const Hierarchy&) = delete;
    /// @brief Returns if names are aqual
    bool operator==(const Hierarchy& other) const;
    /// @brief Returns if current objects name is bigger as a string
    bool operator>(const Hierarchy& other) const;
    /// @brief Returns if current objects name is smaller as a string
    bool operator<(const Hierarchy& other) const;
    /// @brief Calls printNode and returns tree as a string
    string print() const;
    /// @brief Returns longest chain in the tree
    int longest_chain() const;
    /// @brief True if there is a worker with name , equal to the given
    bool find(const string& name) const;
    /// @brief Number of all employees
    int num_employees() const;
    /// @brief Number of employees with more than 20 subordinates
    int num_overloaded(int level = 20) const;
    /// @brief Returns the name of the manager of a worker with the given name
    string manager(const string& name) const;
    /// @brief Number of subordinates of a worker with the given name
    int num_subordinates(const string& name) const;
    /// @brief Salary of a worker with the given name
    int getSalary(const string& who) const;
    /// @brief Removes a worker from the tree and move his subordinates to higher positions
    bool fire(const string& who);
    /// @brief Adds or moves a worker with given name to his new boss (if he exists in the tree)
    bool hire(const string& who, const string& boss);
    /// @brief Incorporates the tree
    void incorporate();
    /// @brief Modernizes the tree
    void modernize();
    /// @brief Merges current tree with another and makes a new one . Nodes are deep copied
    Hierarchy join(const Hierarchy& right) const;
    /// @brief Returns object name
    string getName() const;
};

