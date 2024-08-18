#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Animal.h"

int main() 
{
  std::vector<Animal> AnimalsVec;
  
  Animal dogFemale;
  dogFemale.setName("DoggyFemale");
  dogFemale.setAge(5);       
  dogFemale.setWeight(6);
  AnimalsVec.push_back(dogFemale);
  //describeFriend(dogFemale);    /
  dogFemale.describe(dogFemale);  // wish to discuss : is this correct : object calling and reference to object passing. Is there a way to just do object calling ? I tried but animalrelationshipsvecSP was not accessible in 'describe;
  std::cout << "\n\n\n";

  // / wish to discuss : should i have used 'describeFriend' or is 'describe' ok, or neither ?
  

  Animal puppy;
  puppy.setName("Puppy");
  puppy.setAge(2);         
  puppy.setWeight(3);
  AnimalsVec.push_back(puppy);
  //describeFriend(puppy);
  puppy.describe(puppy);
  std::cout << "\n\n\n";

  
  Animal dogMale;
  dogMale.setName("DoggyMale");
  dogMale.setAge(10);          
  dogMale.setWeight(15);     
  dogMale.add_relationshipSP(std::make_shared<Animal>(dogFemale), AnimalRelationship::Partner);  // wish to discuss : make_shared
  dogMale.add_relationshipSP(std::make_shared<Animal>(puppy), AnimalRelationship::Child);
  AnimalsVec.push_back(dogMale);
  //describeFriend(dogMale);
  dogMale.describe(dogMale);
  std::cout << "\n\n\n";
  
  
  

  Animal kitten("kitten", 3, 3.3);   // ctor initialisation?
  AnimalsVec.push_back(kitten);
  //describeFriend(kitten);
  kitten.describe(kitten);
  std::cout << "\n\n\n";



  
  Animal catMum("Catty", 4, 4.4);    // ctor initialisation?
  catMum.add_relationshipSP(std::make_shared<Animal>(kitten), AnimalRelationship::Child);
  AnimalsVec.push_back(catMum);
  //describeFriend(catMum);
  catMum.describe(catMum);
  std::cout << "\n\n\n";


  std::cout << "\n\n\n";
  
    
  for (auto itr : AnimalsVec)
  {
      get_animals_of_relationship(itr, AnimalRelationship::Child);
      get_animals_of_relationship(itr, AnimalRelationship::Partner);
      get_animals_of_relationship(itr, AnimalRelationship::Sibling);   // no results will be returned because no animal has siblings
  }
}