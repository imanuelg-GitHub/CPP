#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Animal.h"

typedef std::vector<std::pair<std::shared_ptr<Animal>, AnimalRelationship>> vPair;

// global function
std::string getAnimalRelationship(int val)
{
    switch (val) 
    {
        case 0:
          return "Parent";
          break;
        case 1:
          return "Child";
          break;
        case 2:
          return "Sibling";
          break;
        case 3:
          return "Partner";
          break;
        default:
          return "Error";  // should not get here
    }
}


//-Implement a describe() method, that simply outputs to the console all the properties and values of the animal object.
// TODO : print the relationship the animal has
void describeFriend(Animal& animal)  // friend function
{
  std::cout << "Details of the animal are:\n" << 
   "\t\t  Name           : " << animal.getName() << "\n" <<
   "\t\t  Age            : " << animal.getAge() << "\n" <<
   "\t\t  Weight         : " << animal.getWeight() << "\n";
}


// Implement a get_animals_of_relationship() method that takes a relationship type and returns all the animals of that type of relationship.
void get_animals_of_relationship(Animal& animal, AnimalRelationship relationship_type)  // friend function
{
  for (vPair::iterator iter = animal.animalrelationshipsvecSP.begin(); iter != animal.animalrelationshipsvecSP.end(); ++iter) 
  { 
      if (static_cast<int>(relationship_type) == static_cast<int>(iter->second))
      {
          std::cout << animal.getName() << " has relationship : " << getAnimalRelationship(static_cast<int>(relationship_type)) << "\n";
      }
  }
}


//Name, age, weight, animalrelationships
Animal::Animal() : name{""}, weight{0}, animalrelationshipsvecSP{}
{
}

// - Create another constructor alongside the default one for easier initialization of the member values.
Animal::Animal(std::string iname, int iage, double iweight) // wish to discuss : is what you meant a parameterized ctor ?
{
    name = iname;
    age = iage;
    weight = iweight;
}


Animal::~Animal()
{

}

void Animal::setName(std::string iname)
{
  name = iname;
}


std::string Animal::getName(void)
{
  return name;
}


void Animal::setAge(int a)
{
  age = a;
}


int Animal::getAge(void)
{
  return age;
}

void Animal::setWeight(double a)
{
  weight = a;
}


double Animal::getWeight(void)
{
  return weight;
}

//myanimal.hasRelationship(AnimalRelationship.Child)

bool Animal::hasRelationship(AnimalRelationship relationship)
{
    for (auto itr : animalrelationshipsvecSP)
    {
        if (itr.second == relationship)
        {
          return true;
        }
    }
    return false;
}



// -Implement an add_relationship() method to the animal class, that takes both the animal and the relationship type and adds this to the vector.
void Animal::add_relationshipSP(std::shared_ptr<Animal> animal, AnimalRelationship relationship_type)
{
      animalrelationshipsvecSP.push_back(std::make_pair(animal,relationship_type));
}




void Animal::describe(Animal& animal)
{
    std::cout << "Details of the animal are:\n" << 
       "\t\t  Name           : " << animal.getName() << "\n" <<
       "\t\t  Age            : " << animal.getAge() << "\n" <<
       "\t\t  Weight         : " << animal.getWeight() << "\n";
  
    std::cout << "\t\t  Relationships  :\n";
    for (auto itr : animalrelationshipsvecSP)
    {
          std::cout << "\t\t\t\t" << itr.first->getName() << " : ";
          std::cout << getAnimalRelationship(static_cast<int>(itr.second)) << "\n";
    }
    std::cout << "\n\n";
}


