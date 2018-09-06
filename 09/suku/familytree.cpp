/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 3: Suku on pahin                                                  #
# File: familytree.cpp                                                      #
# Description: Module for the project 'Suku on pahin'                       #
#       This module handles all the operations of the program, except the   #
#       command-line interface.                                             #
#############################################################################
*/
#include "familytree.hh"

#include <memory>
#include <map>
#include <set>
#include <string>
#include <algorithm>


// Constructor.
Familytree::Familytree() {

}


// Adds a new person to datastructure, gives error if person is already added.
// id: persons name, used to give the information to person struct.
// height: persons height, used to give the information to person struct.
void Familytree::addNewPerson(const std::__cxx11::string& id, const int& height,
                              std::ostream& output)
{
    if (not isInFamilytree(id)) {
        std::shared_ptr<Person> person( new Person );
        person->id_ = id;
        person->height_ = height;
        persons[id] = person;
    }

    else {
        output << "Error. Person already added." << std::endl;
    }
}


// Prints everyone in the datastructure in alphabetical order
// output: used for printing names
void Familytree::printPersons(std::ostream& output) const
{
    for (auto i : persons) {
        std::shared_ptr<Person> person = i.second;
        output << person->id_ << ", " << person->height_ << '\n';
    }
}


// Link Person structs together with pointers to form families
// child: name of the child
// parents: vector containing names of the parents
// output: for printing error messages
void Familytree::addRelation(const std::__cxx11::string& child,
                             const std::vector<std::__cxx11::string>& parents,
                             std::ostream& output)
{
    Person* ptr_child = getPointer(child);

    if (ptr_child != nullptr) {
        for (int i = 0; i < 2; i++) {
            if ((getPointer(parents.at(i)) != nullptr) && (parents.at(i) != "-")) {
                getPointer(parents.at(i))->children_.push_back(ptr_child);
                ptr_child->parents_.at(i) = getPointer(parents.at(i));
            }
        }
    }

    else {
        printNotFound(child, output);
    }
}


// Prints the children of the given id, prints message if there's no children.
// id: name of the person whose childrens' names are going to be printed.
// output: for printing the names and for error messages.
void Familytree::printChildren(const std::__cxx11::string& id,
                               std::ostream& output) const
{
    if (isInFamilytree(id)) {
        std::string group = "children";

        int amount = persons.at(id)->children_.size();
        if (amount != 0) {
            IdSet children_names = vectorToIdSet(persons.at(id)->children_);

            output << id << " has " << amount << " " << group << ":" << std::endl;
            for (auto name : children_names) {
                output << name << std::endl;
            }
        }

        else {
            printNoGroup(id, group, output);
        }
    }

    else {
        printNotFound(id, output);
    }
}


// Prints the parents of the given id, prints message if id has no parents.
// id: name if the person whose parents' names are going to be printed.
// output: for printing the names and for error messages.
void Familytree::printParents(const std::__cxx11::string& id,
                              std::ostream& output) const
{
    if (isInFamilytree(id)) {
        std::string group = "parents";

        IdSet parents_names = vectorToIdSet(persons.at(id)->parents_);
        int amount = parents_names.size();

        if (amount != 0) {
            output << id << " has " << amount << " " << group << ":" << std::endl;
            for (auto name : parents_names) {
                output << name << std::endl;
            }
        }

        else {
            printNoGroup(id, group, output);
        }
    }

    else {
        printNotFound(id, output);
    }
}


// Prints the names of the id's siblings, prints message if id has no siblings.
// id: name of the person whose siblings' names are to be printed.
// output: for printing the names and for error messages.
void Familytree::printSiblings(const std::__cxx11::string& id,
                               std::ostream& output) const
{
    if (isInFamilytree(id)) {
        std::string group = "siblings";

        Person* person = getPointer(id);

        IdSet names;

        // Helper method that fetches given persons' siblings.
        getSiblingNameSet(person, names);

        int amount = names.size();

        if (amount > 0) {
            output << id << " has " << amount << " " << group << ":" << std::endl;
            for (auto name : names) {
                output << name << std::endl;
            }
        }

        else {
            printNoGroup(id, group, output);
        }
    }

    else {
        printNotFound(id, output);
    }
}


// Prints the names of id's cousins, prints message if id has no cousins.
// id: name if the person whose cousins' names are to be printed.
// output: for printing the names and for error messages.
void Familytree::printCousins(const std::__cxx11::string& id,
                              std::ostream& output) const
{
    // Helper method to check whether id exists.
    if (isInFamilytree(id)) {
        std::string group = "cousins";

        IdSet cousin_names;

        Person* parent1 = persons.at(id)->parents_.at(0);
        Person* parent2 = persons.at(id)->parents_.at(1);

        if ((parent1 == nullptr) && (parent2 == nullptr)) {
            printNoGroup(id, group, output);
        }

        else {
            IdSet parent1_siblings;
            IdSet parent2_siblings;
            IdSet parent_siblings;

            // Helper method that fetches given persons siblings.
            getSiblingNameSet(parent1, parent1_siblings);

            // Helper method that fetches given persons siblings.
            getSiblingNameSet(parent2, parent2_siblings);

            // Helper method that merges two sets into one set.
            mergeIdSets(parent1_siblings, parent2_siblings, parent_siblings);

            for (auto person : parent_siblings) {
                if (persons.at(person)->children_.size() != 0) {

                    IdSet names = vectorToIdSet(persons.at(person)->children_);
                    for (auto name : names) {
                        cousin_names.insert(name);
                    }
                }
            }

            int amount = cousin_names.size();

            if (amount != 0) {
                output << id << " has " << amount << " " << group << ":" << std::endl;
                for (auto name : cousin_names) {
                    output << name << std::endl;
                }
            }

            else {
                printNoGroup(id, group, output);
            }
        }
    }

    else {
        printNotFound(id, output);
    }
}


// Goes through id's lineage to find the tallest person and
// print his/her name and height.
// id: person whose lineage is being searched.
// output: for printing the name + height and for error messages.
void Familytree::printTallestInLineage(const std::__cxx11::string& id,
                                       std::ostream& output) const
{
    // Helper method to check whether id exists.
    if (isInFamilytree(id)) {

        // Helper method that returns a pointer to a shortest/tallest person.
        Person* tallest = shortestOrTallest(id, true);

        if (tallest->id_ == id) {
            output << "With the height of " << tallest->height_ << ", " << id;
            output << " is the tallest person in his/her lineage." << std::endl;
        }

        else {
            output << "With the height of " << tallest->height_ << ", ";
            output << tallest->id_<< " is the tallest person in " << id;
            output << "'s lineage." << std::endl;
        }
    }

    else {
        printNotFound(id, output);
    }
}


// Goes through id's lineage to find the shortest person and
// print his/her name and height.
// id: person whose lineage is being searched.
// output: for printing the name + height and for error messages.
void Familytree::printShortestInLineage(const std::__cxx11::string& id,
                                        std::ostream& output) const
{
    // Helper method to check whether id exists.
    if (isInFamilytree(id)) {

        // Helper method that returns a pointer to a shortest/tallest person.
        Person* shortest = shortestOrTallest(id, false);

        if (shortest->id_ == id) {
            output << "With the height of " << shortest->height_ << ", " << id;
            output << " is the shortest person in his/her lineage." << std::endl;
        }

        else {
            output << "With the height of " << shortest->height_ << ", ";
            output << shortest->id_<< " is the shortest person in " << id;
            output << "'s lineage." << std::endl;
        }
    }

    else {
        printNotFound(id, output);
    }
}


// Prints n:th grandchildren of the given id and given n.
// id: person whose grandchildren's names are being print.
// n: number of levels where we look for persons grandchildren.
// output: for printing the names and for error messages.
void Familytree::printGrandChildrenN(const std::__cxx11::string& id,
                                     const int n, std::ostream& output) const
{
    std::string group;
    for (int i = 0; i < n - 1; i++) {
        group += "great-";
    }
    group += "grandchildren";


    if (n >= 1) {

        // Helper method to check whether id exists.
        if (isInFamilytree(id)) {
            IdSet id_container;

            Person* person = getPointer(id);

            // Helper method that handels searching recursively for n:th level
            // grandparents/-children.
            int current_level = 0;
            getPersonsOnLevel(person, id_container, false, n, current_level);

            int amount = id_container.size();

            if (amount != 0) {
                output << id << " has " << amount << " ";

                for (int i = 0; i < n - 1; i++) {
                    output << "great-";
                }

                output << "grandchildren:" << std::endl;

                for (auto name : id_container) {
                    output << name << std::endl;
                }
            }

            else {
                printNoGroup(id, group, output);
            }
        }

        else {
            printNotFound(id, output);
        }
    }

    else {
        output << "Error. Level can't be less than 1." << std::endl;
    }
}


// Prints n:th grandparents of the given id and given n.
// id: person whose grandparents' names are being print.
// n: number of levels where we look for persons grandparents.
// output: for printing the names and for error messages.
void Familytree::printGrandParentsN(const std::__cxx11::string& id, const int n,
                                    std::ostream& output) const
{
    std::string group;
    for (int i = 0; i < n - 1; i++) {
        group += "great-";
    }
    group += "grandparents";


    if (n >= 1) {

        // Helper method to check whether id exists.
        if (isInFamilytree(id)) {
            IdSet id_container;

            Person* person = getPointer(id);

            // Helper method that handels searching recursively for n:th level
            // grandparents/-children.
            int current_level = 0;
            getPersonsOnLevel(person, id_container, true, n, current_level);

            int amount = id_container.size();

            if (amount != 0) {
                output << id << " has " << amount << " ";

                for (int i = 0; i < n - 1; i++) {
                    output << "great-";
                }

                output << "grandparents:" << std::endl;

                for (auto name : id_container) {
                    output << name << std::endl;
                }
            }

            else {
                printNoGroup(id, group, output);
            }
        }

        else {
            printNotFound(id, output);
        }
    }

    else {
        output << "Error. Level can't be less than 1." << std::endl;
    }
}


// Takes an id and returns a pointer corresponding the given id.
// id: used to get the pointer corresponding with the id.
Person *Familytree::getPointer(const std::__cxx11::string& id) const
{
    if (id != "-") {
        Person* address = persons.at(id).get();
        return address;
    }

    else {
        Person* address = nullptr;
        return address;
    }
}


// Used for printing 'not found' messages.
// id: name of the one who was not found.
// output: used for printing the message.
void Familytree::printNotFound(const std::__cxx11::string& id,
                               std::ostream& output) const
{
    output << "Error. " << id << " not found." << std::endl;
}


// Used for printing '<group> not found' messages.
// id: name of the person who doesn't have requested group.
// group: group's name that was not found.
// output: used for printing the message.
void Familytree::printNoGroup(const std::string& id, std::string& group,
                              std::ostream& output) const
{
    output << id << " has no " << group << "." << std::endl;
}


// Checks whether a person exists in the datastructure or not. Returns 'true'
// if id is found and vice versa.
// id: name of the person who is being searched for.
bool Familytree::isInFamilytree(const std::string& id) const
{
    auto i = persons.find(id);
    if (i != persons.end()) {
        return true;
    }

    else {
        return false;
    }
}


// Turns contenst of a vector to set of ids and returns the set.
// container: vector that contains pointers.
IdSet Familytree::vectorToIdSet(const std::vector<Person*>& container) const
{
    IdSet names;

    for (auto name : container) {

        if (name != nullptr) {
            names.insert(name->id_);
        }
    }
    return names;
}


// Searches for given persons siblings and adds them to a set, excluding the
// person him/herself.
// person: person whose siblings are being searched for.
// sibling_names: set where names of a persons siblings are added.
void Familytree::getSiblingNameSet(Person* person, IdSet& sibling_names) const
{

    if (person != nullptr) {

        for (auto parent : person->parents_) {

            if (parent != nullptr) {
                std::vector<Person*> siblings = parent->children_;
                sibling_names = vectorToIdSet(siblings);
                sibling_names.erase(person->id_);
            }
        }
    }
}


// Takes to sets and merges them together to form one set.
// set1, set2: sets given to be merged.
// merged_set: set that is the merging of the two given sets.
void Familytree::mergeIdSets(IdSet& set1, IdSet& set2, IdSet& merged_set) const
{
    std::merge(set1.begin(), set1.end(),
               set2.begin(), set2.end(),
               inserter(merged_set, merged_set.end()));
}


// Handles initiation of recursion in right direction and returning of the
// pointer to the tallest/shortest person.
// id: name of the person whose lineage is being searched.
// tallest: true -> recursion will search for the tallest, false -> shortest.
Person* Familytree::shortestOrTallest(const std::string& id,
                                      const bool& tallest) const
{
    Person* person = getPointer(id);

    if (tallest) {
        Person* tallest_person = heightRecursive(person, true);
        return tallest_person;
    }

    else {
        Person* shortest_person = heightRecursive(person, false);
        return shortest_person;
    }
}


// Recursive method that will go through a given persons lineage and search for
// shortest/tallest person.
// person: person that is in that moment being compared to in height.
// tallest: true -> search for tallest, false -> search for shortest.
Person* Familytree::heightRecursive(Person* person,
                                    const bool& tallest) const
{
    std::vector<Person*> children = person->children_;
    Person* taller_or_shorter = nullptr;

    if (children.size() != 0) {

        // go through persons children and their children and so on until
        // the lineage ends and then compare people together to find the
        // shortest/tallest person.
        for (auto i : children) {
            Person* child = heightRecursive(i, tallest);

            if (tallest) {
                if (child->height_ > person->height_) {
                    taller_or_shorter = child;
                }

                else {
                    taller_or_shorter = person;
                }
            }

            else {
                if (child->height_ < person->height_) {
                    taller_or_shorter = child;
                }

                else {
                    taller_or_shorter = person;
                }
            }
            person = taller_or_shorter;
        }

        return taller_or_shorter;
    }

    else {
        return person;
    }
}


// Recursively goes through the familytree to the n:th level and inserts the
// names of n:th level grandparents/children.
// person: person whose n:th level grandparents/children are being looked for.
// id_container: set that has the names of grandparents/children inserted into.
// direction_up: true -> we go up the familytree, false -> down the familytree.
void Familytree::getPersonsOnLevel(Person* const person, IdSet& id_container,
                                const bool& direction_down, const int& n,
                                int current_level) const
{
    current_level++;

    if (current_level == n + 1) {

        if (direction_down) {

            for (auto parent : person->parents_) {
                if (parent != nullptr) {
                      id_container.insert(parent->id_);
                }
            }
        }

        else {
            for (auto child : person->children_) {
                id_container.insert(child->id_);
            }
        }
    }

    // Function going to advance the levels by calling itself until a
    // desired level is reached.
    else {

        if (direction_down) {

            for (auto parent : person->parents_) {
                if (parent != nullptr) {
                    getPersonsOnLevel(parent, id_container, direction_down,
                                   n, current_level);
                }
            }
        }

        else {
            for (auto child : person->children_) {
                getPersonsOnLevel(child, id_container, direction_down,
                               n, current_level);
            }
        }
    }
}


// Destructor.
Familytree::~Familytree() {

}
