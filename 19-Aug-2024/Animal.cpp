#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Animal.h"


#define DOGYEARS 7  


std::string Animal::getAnimalRelationship(const AnimalRelationship& rel)
{
    switch (rel) 
    {
        case AnimalRelationship::Parent:
          return "Parent";
          break;
        case AnimalRelationship::Child:
          return "Child";
          break;
        case AnimalRelationship::Sibling:
          return "Sibling";
          break;
        case AnimalRelationship::Partner:
          return "Partner";
          break;
        default:
          return "Error";  // should not get here
    }
}


// Implement a get_animals_of_relationship() method that takes a relationship type and returns all the animals of that type of relationship.
void Animal::get_animals_of_relationship(const AnimalRelationship& relationship_type) const
{
  for (auto iter = animalrelationshipsvecSP.begin(); iter != animalrelationshipsvecSP.end(); ++iter) 
  { 
      if (static_cast<int>(relationship_type) == static_cast<int>(iter->second))
      {
          std::cout << name << " has relationship : " << Animal::getAnimalRelationship(relationship_type) << "\n";
          
      }
  }
}


//Name, age, weight, animalrelationships
Animal::Animal() : name{""}, weight{0}, height{0}, animalrelationshipsvecSP{}
{
}

// - Create another constructor alongside the default one for easier initialization of the member values.
Animal::Animal(std::string iname, int iage, double iweight, double iheight)
{
    name   = iname;
    age    = iage;
    weight = iweight;
    height = iheight;
}


Animal::~Animal()
{

}

void Animal::setName(const std::string& iname)
{
  name = iname;
}


const std::string& Animal::getName() const
{
  return name;
}


void Animal::setAge(const int& a)
{
  age = a;
}


const int Animal::getAge(void)
{
  return age;
}


void Animal::setBMI(const double& weight, const double& height)
{
  if (height == 0.0)  // protect against division by 0
  {
          std::cout << "Error : Height is 0, cannot divide by 0, BMI will be 0\n";
          BMI = 0;
          return;
  }
  BMI = weight / (height * height);  // I still don't understand how this works when height = 0
}

const double Animal::getBMI(void)
{
  return BMI;
}


const double Animal::get_portion_size(void) const // why does const before and after work ?
{
  return 100 - BMI;
}


void Animal::setWeight(const double& a)
{
  weight = a;
}


const double Animal::getWeight(void)
{
  return weight;
}


void Animal::setHeight(const double& a)
{
  height = a;
}


const double Animal::getHeight(void)
{
  return height;
}



std::string Animal::get_weight_type(const double& BMI)
{
    if (BMI < 18.5)
    {
        return "Underweight";
    }
    else if (BMI >= 18.5 && BMI < 25 )
    {
        return "Normal";
    }
    else if (BMI >= 25 && BMI < 40 )
    {
        return "Overweight";
    }
    else if (BMI >= 40)
    {
        return "Obese";
    }
    else
    {
        return "something else..."; // should not get here
    }
}


bool Animal::hasRelationship(const AnimalRelationship& relationship)
{
    for (const auto& itr : animalrelationshipsvecSP)
    {
        if (itr.second == relationship)
        {
          return true;
        }
    }
    return false;
}



// -Implement an add_relationship() method to the animal class, that takes both the animal and the relationship type and adds this to the vector.
void Animal::add_relationshipSP(const std::shared_ptr<Animal>& animal, AnimalRelationship relationship_type)
{
      animalrelationshipsvecSP.push_back(std::make_pair(animal,relationship_type));
}




const void Animal::describe() const
{
    std::cout << "Details of the animal are:"  << "\n"    << 
       "\t\t  Name           : " << name       << "\n"    <<
       "\t\t  Age            : " << age        << "\n"    <<
       "\t\t  Weight         : " << weight     << "\n"    <<
       "\t\t  Height         : " << height     << "\n"    <<
       "\t\t  BMI            : " << BMI        << " ("    << get_weight_type(BMI) << ")\n" <<
       "\t\t  PortionSize    : " << get_portion_size()    << "\n";

    std::cout << "\t\t  Relationships  :\n";
    for (auto itr : animalrelationshipsvecSP)
    {
          std::cout << "\t\t\t\t" << (itr.first)->getName() << " : ";
          std::cout << Animal::getAnimalRelationship(itr.second) << "\n";
    }
    
    std::cout << "\n\n";
}


bool Animal::operator== (const Animal &other)
{ 
    return name == other.name;    
} 

void Dog::setAge(const int& a)
{
    age = a * DOGYEARS;
}


const int Dog::getAge(void)
{
    return age;
}
