#include <iostream>
#include <string>
#include <memory>
#include <vector>
 
#include "Animal.h"


const int DOGYEARS = 7;


// relationships were added using add_relationshipSP, so using std::shared_ptr<Animal> reference 
Animal* Animal::operator+ (std::shared_ptr<Animal>& parent2)
{
    if (this->hasRelationship (parent2, AnimalRelationship::Partner))
        {
            Animal* pchild = new Animal();
            pchild->setName("newChild");
            pchild->setAge(4); 
            pchild->setWeight(200);
            pchild->setHeight(3);
            return pchild;

        }
    
        std::cout << this->name << " and " << parent2->name  << " are not partners\n";
        return NULL;
}



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


const int Animal::getAge() const
{
    return age;
}


inline const double Animal::getBMI() const
{
   if (height != 0)   // error handling for division by 0
   {
       return weight / (height * height);
   }
   else
   {
       std::cout << "Cannot divide by " << height << ". Returning -1\n";
       return -1;
   }
}


const double Animal::get_portion_size() const 
{
     return 100 - getBMI();
}


void Animal::setWeight(const double& a)
{
     weight = a;
}


const double Animal::getWeight() const   // const : weight (also all member variables) cannot be changed but since returning copy of double, it's a copy (but member variable weight remains unchaged)
{
     return weight;
}


void Animal::setHeight(const double& a)
{
      height = a;
}


const double Animal::getHeight()
{
    return height;
}




const std::string Animal::get_weight_type() const
{
    AnimalWeightType animalweighttype = AnimalWeightType::Unknown;  // initial arbitary value
    
    if (getBMI() < 18.5)
    {
        animalweighttype = AnimalWeightType::Underweight;
    }
    else if (getBMI() >= 18.5 && getBMI() < 25 )
    {
        animalweighttype = AnimalWeightType::Normal;
    }
    else if (getBMI() >= 25 && getBMI() < 40 )
    {
        animalweighttype = AnimalWeightType::Overweight;
    }
    else if (getBMI() >= 40)
    {
        animalweighttype = AnimalWeightType::Obese;
    }
    else
    {
        animalweighttype = AnimalWeightType::Unknown;  // should not get here
    }

    switch (animalweighttype) 
    {
        case AnimalWeightType::Underweight:
            return "Underweight";
            break;
        case AnimalWeightType::Normal:
            return "Normal";
            break;
        case AnimalWeightType::Overweight:
            return "Overweight";
            break;
        case AnimalWeightType::Obese:
            return "Obese";
            break;
        default:
            return "Error";  // should not get here
    }
}





bool Animal::hasRelationship(const std::shared_ptr<Animal>& animal, const AnimalRelationship& relationship)
{
    for (const auto& itr : animalrelationshipsvecSP)
    {
        if (itr.first == animal && itr.second == relationship)
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
       "\t\t  BMI            : " << getBMI()   << " ("    << get_weight_type() << ")\n" <<
       "\t\t  PortionSize    : " << get_portion_size()    << "\n";

    std::cout << "\t\t  Relationships  :\n";
    for (auto itr : animalrelationshipsvecSP)
    {
          std::cout << "\t\t\t\t" << (itr.first)->getName() << " : ";
          std::cout << Animal::getAnimalRelationship(itr.second) << "\n";
    }
    
    std::cout << "\n\n";
}


bool Animal::operator== (const Animal& other)
{ 
    return name == other.name;    
} 



void Dog::setAge(const int& a)
{
    age = a * DOGYEARS;
}


const int Dog::getAge() const 
{
    return age;
}
