#pragma once
#include <fstream>
#include <iostream>
#include "Command.h"
#include "Interface.h"
#include "Exception_ExitProgram.h"
#include "Exception_FileCantLoad.h"
#include "BinaryTree.h"
/// @brief Responsible for working with command line . Uses command to recognize command and extract parameters ,then calls the right functions in Hierarchy . Inherits Command
class FrontEnd : protected Command {
private:
	/// @brief AVL tree that stores the loaded Hierarchy objects.
	BinaryTree<Hierarchy> hierarchies;
	/// @brief Creates new hierarchy
	void load();
	/// @brief Saves object to a file path.
	void save();
	/// @brief Calls  Hierarchy::find() and prints result.
	void find();
	/// @brief Calls  Hierarchy::num_subordinates() and prints result.
	void num_subordinates();
	/// @brief  Calls  Hierarchy::manager() and prints result.
	void manager();
	/// @brief  Calls  Hierarchy::num_employees() and prints result.
	void num_employees();
	/// @brief Calls  Hierarchy::num_overloaded() and prints result.
	void num_overloaded();
	/// @brief Calls  Hierarchy::fire() and prints result.
	void fire();
	/// @brief Calls  Hierarchy::hire() and prints result.
	void hire();
	/// @brief Combines two  Hierarchy objects into one and adds it to the existing ones.
	void join();
	/// @brief Calls  Hierarchy::salary() and prints result.
	void salary();
	/// @brief Calls  Hierarchy::incorporate() 
	void incorporate(); 
	/// @brief Calls  Hierarchy::modernize() 
	void modernize();
	/// @brief Prints on console the commands and rules how to be used properly.
	void help();
	/// @brief Throws ExitProgram exception to warn that Exit command is being executed.
	/// @warning ExitProgram exception should be caught wherever the class is used!
	void exit();
	/// @brief Deletes the data from hierarchies vector.
	void deleteHierarchies();
	/// @brief Returns the pointer of the Hierarchy from the tree
	Hierarchy* findHierarchy(const std::string& name) const;
	/// @brief Saves the whole file content in a string and returns it.Throws FileCantLoad exception if opening the file fails
	/// @return All of file's content.
	/// @warning FileCantLoad exception should be caught when using the function
	string readFromFile(const std::string& fileName) const;
	/// @brief Writes data in a file with the given name .Throws FileCantLoad exception if opening the file fails
	/// @warning FileCantLoad exception should be caught when using the function
	void writeInFile(const std::string& fileName, std::string& data) const;
	/// @brief Reads console input until ^Z or ^D is not found. 
	/// @return The whole input without the ending symbows.
	string readFromConsole() const;
	/// @brief Used by writeInFile to ask user if he wants to delete file information in case file already exists.
	/// @return True for deleting. False for disagree
	bool agreesToDelete() const;
public:
	/// @brief Default general purpose contrustor
	FrontEnd()=default;
	/// @brief  Copy constructor
	/// @param other 
	FrontEnd(const FrontEnd& other);
	/// @brief Move constructor
	FrontEnd(const FrontEnd&& other) noexcept;
	/// @brief Deletes all data from hierarhies
	~FrontEnd() noexcept;
	/// @brief Assignment operator
	FrontEnd& operator=(const FrontEnd& other);
	/// @brief Move Assignment operator
	FrontEnd& operator=(FrontEnd&& other) noexcept;
	/// @brief Uses Command::processCommand() and switches the command . Calls the proper functon for it's execution.
	/// @param commandLine String containing both command and parameters.
	/// @warning Invalid commands will throw ExitProgram exeption.
	void executeCommand(std::string commandLine);

};