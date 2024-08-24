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
  dogFemale.setWeight(80);
  dogFemale.setHeight(1.8);
  dogFemale.setBMI(dogFemale.getWeight(), dogFemale.getHeight());
  AnimalsVec.push_back(dogFemale);
  dogFemale.describe();
  std::cout << "\n\n\n";


  //Animal* puppyFemale = new Animal();
  std::shared_ptr<Animal> puppyFemale {std::make_shared<Animal>("puppyFemale", 22, 12, 1.2)};
  puppyFemale->setBMI(puppyFemale->getWeight(), puppyFemale->getHeight());
  puppyFemale->add_relationshipSP(std::make_shared<Animal>(dogFemale), AnimalRelationship::Parent);  // is this correct, i.e. does this make_shared refer to the dogFemale above, or is that a secondary dogFemale ?  hospefully the former
  AnimalsVec.push_back(*puppyFemale.get());   // glad I sorted this
  puppyFemale->describe();
  std::cout << "\n\n\n";
  

  Animal puppy;
  puppy.setName("Puppy");
  puppy.setAge(2);         
  puppy.setWeight(50);
  puppy.setHeight(1.1);
  puppy.setBMI(puppy.getWeight(), puppy.getHeight());
  puppy.add_relationshipSP(puppyFemale, AnimalRelationship::Sibling); 
  AnimalsVec.push_back(puppy);
  puppy.describe();
  std::cout << "\n\n\n";

  
  Animal dogMale;
  dogMale.setName("DoggyMale");
  dogMale.setAge(10);          
  dogMale.setWeight(150);    
  dogMale.setHeight(2.2);
  dogMale.setBMI(dogMale.getWeight(), dogMale.getHeight());
  dogMale.add_relationshipSP(std::make_shared<Animal>(dogFemale), AnimalRelationship::Partner);  
  dogMale.add_relationshipSP(std::make_shared<Animal>(puppy), AnimalRelationship::Child);
  AnimalsVec.push_back(dogMale);
  dogMale.describe();
  std::cout << "\n\n\n";
  
  
  

  Animal kitten("kitten", 3, 3.3, 1.3);   // ctor initialisation
  kitten.setBMI(kitten.getWeight(), kitten.getHeight());
  AnimalsVec.push_back(kitten);
  kitten.describe();
  std::cout << "\n\n\n";



  
  Animal catMum("Catty", 4, 0, 0);    // ctor initialisation
  catMum.setBMI(catMum.getWeight(), catMum.getHeight());
  catMum.add_relationshipSP(std::make_shared<Animal>(kitten), AnimalRelationship::Child);
  AnimalsVec.push_back(catMum);
  catMum.describe();
  std::cout << "\n\n\n";



  for (const auto& itr : AnimalsVec) 
  {
          itr.get_animals_of_relationship(AnimalRelationship::Parent);
          itr.get_animals_of_relationship(AnimalRelationship::Child);
          itr.get_animals_of_relationship(AnimalRelationship::Sibling);
          itr.get_animals_of_relationship(AnimalRelationship::Partner);
  }

  
  std::cout << "\n\n\n";
  Dog ddd;
  ddd.setAge(5);
  std::cout << "ddd.getAge() = " << ddd.getAge() << "\n";
  
}