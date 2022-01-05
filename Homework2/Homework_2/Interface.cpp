#include "Interface.h"

void Hierarchy::processData(const string& data)
{
	if (data.empty()) {
		return;
	}
	size_t index = 0;
	string bossName, workerName;
	Worker* currentBoss = nullptr; //while processing is it very likely to add servants to the same boss multiple times so that can save time
	try {
		while (index < data.size() - 1)//last one is \n
		{
			//get data
			bossName = getNextName(data, index);
			if (bossName.empty()) break;
			workerName = getNextName(data, index);
			if (boss && findWorker(workerName,boss)) {//so we already have someone with that name
				throw std::logic_error("Found worker duplication.");
			}
			//assign
			if (!currentBoss) {
				if (bossName != BOSS_NAME)
				{
					throw std::logic_error("Boss not found");
				}
				else
				{
					boss = new Worker{ BOSS_NAME,nullptr };//Uspeshniq
					//std::cout << "(Created boss " << bossName << ")\n";
					currentBoss = boss;
				}
			}
			else if (currentBoss->name != bossName)
			{
				currentBoss = findWorker(bossName, boss);
			}

			addInSorter(currentBoss->servants, new Worker{ workerName,currentBoss });
		}
	}
	catch (const std::logic_error& e) {
		if (boss) {
			deleteHierarchy(boss);
		}
		throw e;
	}
	catch (const std::exception& e) {
		if (boss) {
			deleteHierarchy(boss);
		}
		throw e;
	}
}

bool Hierarchy::isEmptySymb(const char symb) const
{
	return symb == '-' || symb == '\n' || symb == ' ' || symb=='\t';
}

Worker* Hierarchy::copyTree(Worker* nodeToCopy, Worker* previous)
{
	Worker* copy = nullptr;
	try {
		copy = new Worker{ nodeToCopy->name,previous,nodeToCopy->subordinatesNum };
		for (int i = 0; i < nodeToCopy->servants.size(); i++) {
			copy->servants.push_back(copyTree(nodeToCopy->servants[i], copy));
		}
	}
	catch (const std::exception& e) {
		if (copy) {
			deleteHierarchy(copy);
		}
		throw e; //that way the tree will be delete up to the root
	}
	return copy;
}

string Hierarchy::getNextName(const string& data, size_t& index)
{
	while (index < data.size() && isEmptySymb(data[index]))
	{
		++index;
	}
	const size_t startIndex = index;
	while (index < data.size() && !isEmptySymb(data[index]))
	{
		++index;
	}
	if (index == data.size() && data[data.size() - 1] != '\n') {//no closing endl
		throw std::invalid_argument("Invalid data string");
	}
	return data.substr(startIndex, index - startIndex); //++ to skip '\n' or '-'
}


Worker* Hierarchy::findWorker(const string& name, Worker* current) const
{
	if (current->name == name) {
		return current;
	}
	Worker* worker = nullptr;
	for (int i = 0; i < current->servants.size(); i++) {
		worker = findWorker(name, current->servants[i]);
		if (worker)
			return worker;
	}
	return nullptr;
}

Hierarchy::Hierarchy(Hierarchy&& r) noexcept
{
	boss = r.boss;
	r.boss = nullptr;
	objName = r.objName;
	r.objName.clear();
}

Hierarchy::Hierarchy(const Hierarchy& r,const string newName )
{
	boss = copyTree(r.boss, nullptr);
	objName = newName.empty() ? r.objName : newName;
}

string Hierarchy::printNode(Worker* node) const
{
	//! USE PRIORITY QUEUE instead of sorting the vectors
	string ans;
	Worker* current = nullptr;
	queue<Worker*> workers;
	workers.push(boss);
	while (!workers.empty()) {
		current = workers.front();
		workers.pop();
		for (int i = 0; i < current->servants.size(); i++) {
			workers.push(current->servants[i]);
			ans += current->name + '-' + current->servants[i]->name + '\n';
		}
	}
	return ans;
}

Hierarchy::Hierarchy(const string& data,const string& name)
{
	processData(data);
	if (boss)
	{
		findAllWorkersSubordinatesNum(boss);
	}
	objName = name;
}

void Hierarchy::addInSorter(vector<Worker*>& vec, Worker* item)
{
	vec.push_back(nullptr);
	for (size_t i = vec.size() - 1; i >= 0; i--) {
		if (i == 0 || vec[i - 1]->name < item->name) {
			vec[i] = item;
			return;
		}
		else {
			vec[i] = vec[i - 1];
		}
	}
}

void Hierarchy::deleteHierarchy(Worker* currentNode)
{
	for (int i = 0; i < currentNode->servants.size(); i++) {
		deleteHierarchy(currentNode->servants[i]);
	}
	delete currentNode;
}

Hierarchy::~Hierarchy() noexcept
{
	if (boss) {
		deleteHierarchy(boss);
	}
}

size_t Hierarchy::getHeight(Worker* node) const
{
	size_t maxSubHeight = 0;
	for (int i = 0; i < node->servants.size(); i++) {
		maxSubHeight = std::max(maxSubHeight, getHeight(node->servants[i]));
	}
	return 1 + maxSubHeight;
}

string Hierarchy::print() const
{
	return boss ? printNode(boss) : "";
}

size_t Hierarchy::findOverloadedOnLvl(const int level, Worker* node) const
{
	size_t overloaded = node->subordinatesNum > 20 ? 1 : 0;
	for (size_t i = 0; i < node->servants.size(); i++) {
		if (node->servants[i]->subordinatesNum > level) {
			overloaded += findOverloadedOnLvl(20, node->servants[i]);
		}
	}
	return overloaded;
}

size_t Hierarchy::findAllWorkersSubordinatesNum(Worker* node)
{
	node->subordinatesNum = node->servants.size();
	for (size_t i = 0; i < node->servants.size(); i++) {
		node->subordinatesNum += findAllWorkersSubordinatesNum(node->servants[i]);
	}
	return node->subordinatesNum;
}

int Hierarchy::longest_chain() const
{
	return boss ? getHeight(boss) : 0;
}

void Hierarchy::removeServant(vector<Worker*>& vec, Worker* worker)
{
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i]->name == worker->name) {
			vec.erase(vec.begin() + i);
			return;
		}
	}
}

bool Hierarchy::find(const string& name) const
{
	return boss && findWorker(name, boss) != nullptr;
}

void Hierarchy::updateSubNumAbove(const int modifier, Worker* start)
{
	if (!start) return;

	start->subordinatesNum += modifier;
	updateSubNumAbove(modifier, start->boss);

}

int Hierarchy::num_employees() const
{
	return boss ? boss->subordinatesNum + 1 : 0;
}

void Hierarchy::incorporateTree(Worker* node)
{
	
	if (node->servants.size() < node->subordinatesNum) {
		//if there can be a chance for further incorporation
		for (size_t i = 0; i < node->servants.size(); i++) {
			incorporateTree(node->servants[i]);
		}
	}
	if (node->servants.size() >= 2) {
		Worker* toPromote = findBiggestSalary(node->servants);
		//std::cout << "Promoting " << toPromote->name << " for ";
		for (size_t i = 0; i < node->servants.size(); i++)
		{//move them
			if (node->servants[i]->name != toPromote->name) {
				addInSorter(toPromote->servants, node->servants[i]);
				node->servants[i]->boss = toPromote;
				//
				//std::cout << node->servants[i]->name;
			}//std::cout << std::endl;
		}
		node->servants.clear();
		node->servants.push_back(toPromote);
	}
}

int Hierarchy::num_overloaded(int level) const
{
	return boss ? findOverloadedOnLvl(level, boss) : 0;
}

void Hierarchy::modernizeOnLvl(const size_t level, Worker* node)
{
	//std::cout << "(" << node->name << ")\n";
	vector<Worker*> original = node->servants; //when going down in the tree we can change the servants and mess up the recurshion call
	for (size_t i = 0; i < original.size(); i++) {
		modernizeOnLvl(level + 1, original[i]);
	}
	original.clear();

	if (level % 2 == 1 && !node->servants.empty())//even and is team leader
	{
		//std::cout << "Level " << level << ": removing "<<node->name<<std::endl;
		Worker* _boss = node->boss;
		removeServant(_boss->servants, node);//we will remove the node
		for (size_t i = 0; i < node->servants.size(); i++)//we move his team into leader's team
		{
			addInSorter(_boss->servants, node->servants[i]);
			node->servants[i]->boss = _boss;
		}
		updateSubNumAbove(-1, _boss);
		delete node;
	}
}

Worker* Hierarchy::findBiggestSalary(const vector<Worker*>& vec) const
{
	size_t maxSalary = 0;
	Worker* richest = vec[0];
	for (size_t i = 0; i < vec.size(); i++) {
		if ((vec[i]->subordinatesNum * 50 + vec[i]->servants.size() * 450) > maxSalary) {
			richest = vec[i];
			maxSalary = vec[i]->subordinatesNum * 50 + vec[i]->servants.size() * 450;
		}
	}
	return richest;
}

string Hierarchy::manager(const string& name) const
{
	if (!boss || name == BOSS_NAME) return "";
	Worker* worker = findWorker(name, boss);
	return worker? worker->boss->name : "";
}

void Hierarchy::mergeSorted(const Hierarchy& other, Hierarchy& newObj, Worker* searched, Worker* lastBoss) const
{//used by join, copies elements that are not added already in the new hierarchy and also sort them in the new vector

	Worker* inThisObj = findWorker(searched->name, boss); 
	Worker* inOtherObj = other.findWorker(searched->name, other.boss);
	vector<Worker*> newVec; //vector of searched object

	size_t ind1 = 0, ind2 = 0;
	//push by slightly faster sorting

	while ((inThisObj && ind1 < inThisObj->servants.size()) || (inOtherObj && ind2 < inOtherObj->servants.size()))
	{
		if (!inThisObj || ind1 >= inThisObj->servants.size())
		{
			if (!newObj.find(inOtherObj->servants[ind2]->name))
			{//if we dont have it added already
				newVec.push_back(new Worker{ inOtherObj->servants[ind2]->name, searched }); //copy it!
			}
			++ind2;
		}
		else if (!inOtherObj || ind2 >= inOtherObj->servants.size())
		{
			if (!newObj.find(inThisObj->servants[ind1]->name))
			{//if we dont have it added already

				newVec.push_back(new Worker{ inThisObj->servants[ind1]->name, searched });
			}
			++ind1;
		}
		else if (inThisObj->servants[ind1]->name == inOtherObj->servants[ind2]->name)
		{ //add one and continue for both
			if (!newObj.find(inThisObj->servants[ind1]->name))
			{//if we dont have it added already
				newVec.push_back(new Worker{ inThisObj->servants[ind1]->name, searched });//copy it
			}
			++ind1;
			++ind2;
		}
		else {
			if (inThisObj->servants[ind1]->name < inOtherObj->servants[ind2]->name && !newObj.find(inThisObj->servants[ind1]->name))
			{
				newVec.push_back(new Worker{ inThisObj->servants[ind1++]->name , searched });
			}
			else if (!newObj.find(inOtherObj->servants[ind2]->name))
			{
				newVec.push_back(new Worker{ inOtherObj->servants[ind2++]->name , searched });
			}
		}
	}
	if (!lastBoss) {
		searched = new Worker{ searched->name,nullptr,0,std::move(newVec) }; //create Uspeshniq
		newObj.boss = searched;//uspeshniq
	}
	else {
		searched->servants = std::move(newVec);//assign servants
	}
	for (size_t i = 0; i < searched->servants.size(); i++) {//check all newly added
		mergeSorted(other, newObj, searched->servants[i], searched);
	}


}
int Hierarchy::num_subordinates(const string& name) const
{
	if (!boss) return -1;
	Worker* worker = findWorker(name, boss);
	return worker ? worker->servants.size() : -1;
}

int Hierarchy::getSalary(const string& who) const
{
	Worker* worker = findWorker(who, boss);
	return worker ? (worker->subordinatesNum * 50 + worker->servants.size() * 450) : -1;
}

bool Hierarchy::fire(const string& who)
{
	Worker* fired = findWorker(who, boss);
	if (fired && fired != boss) {
		Worker* _boss = fired->boss;
		removeServant(_boss->servants, fired);
		for (size_t i = 0; i < fired->servants.size(); i++) {
			addInSorter(_boss->servants, fired->servants[i]);
		}
		delete fired;
		updateSubNumAbove(-1, _boss);
		return true;
	}
	return false;
}

bool Hierarchy::hire(const string& who, const string& boss)
{
	Worker* newBoss = findWorker(boss, this->boss);
	if (!newBoss) return false;
	Worker* hired = findWorker(who, this->boss);
	//
	if (hired)//exists
	{
		if (hired->boss->name == boss) return true; //he's already working as his servant
		//otherwise we remove him from his previous boss
		removeServant(hired->boss->servants, hired);
		updateSubNumAbove(-1, hired->boss);
		//and re-hire
	}
	else
	{
		hired = new Worker{ who };
	}
	addInSorter(newBoss->servants, hired);
	updateSubNumAbove(1, newBoss);
	hired->boss = newBoss;
	return true;
}

void Hierarchy::incorporate()
{
	if (boss)
	{
		incorporateTree(boss);
	}
}

void Hierarchy::modernize()
{
	if (boss)
	{
		modernizeOnLvl(0, boss);
	}
}

bool Hierarchy::operator==(const Hierarchy& other) const
{
	return objName == other.objName;
}

bool Hierarchy::operator>(const Hierarchy& other) const
{
	return objName > other.objName;
}
bool Hierarchy::operator<(const Hierarchy& other) const {
	return objName < other.objName;
}
Hierarchy Hierarchy::join(const Hierarchy& right) const
{

	Hierarchy* merged = nullptr;
	try {
		if (!right.boss) {
			merged = new Hierarchy(*this); //copy
		}
		else if (!boss) {
			merged = new Hierarchy(right); //copy
		}
		else {
			merged = new Hierarchy("");
			mergeSorted(right, *merged, boss, nullptr);
			merged->findAllWorkersSubordinatesNum(merged->boss);
		}
	}
	catch (...) {
		if (merged && merged->boss) {
			merged->deleteHierarchy(merged->boss);
		}
		throw OutOfMemory(); //do it better!
	}

	return *merged;
}


string Hierarchy::getName() const
{
	return objName;
}
