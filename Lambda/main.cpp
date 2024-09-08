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
  AnimalsVec.push_back(dogFemale);
  dogFemale.describe();
  std::shared_ptr<Animal> dogFemaleSP {std::make_shared<Animal>(dogFemale)};
  std::cout << "\n\n\n";


  std::shared_ptr<Animal> puppyFemale {std::make_shared<Animal>("puppyFemale", 22, 12, 1.2)};  // same as : Animal* puppyFemale = new Animal();  but later 'delete' required
  puppyFemale->add_relationshipSP(std::make_shared<Animal>(dogFemale), AnimalRelationship::Parent);
  AnimalsVec.push_back(*puppyFemale.get());
  puppyFemale->describe();
  std::cout << "\n\n\n";


  Animal puppy;
  puppy.setName("Puppy");
  puppy.setAge(2);         
  puppy.setWeight(50);
  puppy.setHeight(1.1);
  puppy.add_relationshipSP(puppyFemale, AnimalRelationship::Sibling); 
  AnimalsVec.push_back(puppy);
  puppy.describe();
  std::shared_ptr<Animal> puppySP {std::make_shared<Animal>(puppy)};
  std::cout << "\n\n\n";


  Animal dogMale;
  dogMale.setName("DoggyMale");
  dogMale.setAge(10);          
  dogMale.setWeight(150);    
  dogMale.setHeight(2.2);
  dogMale.add_relationshipSP(dogFemaleSP, AnimalRelationship::Partner); 
  dogMale.add_relationshipSP(puppySP, AnimalRelationship::Child);  
  AnimalsVec.push_back(dogMale);
  dogMale.describe();  
  if ( 
          dogMale.hasRelationship (dogFemaleSP, AnimalRelationship::Partner) &&
          dogMale.hasRelationship (puppySP, AnimalRelationship::Child)
     )   
          {
                          std::cout << "\t\t  Yes : DoggyMale has dogFemale as Partner\n";
          }
          else
          {
                          std::cout << "\t\t  No : DoggyMale does not have dogFemale as Partner\n";
          }
  std::cout << "\n\n\n";




  Animal kitten("kitten", 3, 3.3, 1.3);   // ctor initialisation
  AnimalsVec.push_back(kitten);
  kitten.describe();
  std::cout << "\n\n\n";




  Animal catMum("catMum", 4, 0, 5);    // ctor initialisation
  std::shared_ptr<Animal> kittenSP {std::make_shared<Animal>(kitten)};
  catMum.add_relationshipSP(kittenSP, AnimalRelationship::Child);  
  AnimalsVec.push_back(catMum);
  catMum.describe();
  if ( catMum.hasRelationship (kittenSP, AnimalRelationship::Child) )   
  {
                std::cout << "\t\t  Yes : catMum has kitten\n";
  }
  else
  {
                std::cout << "\t\t  No : catMum has no kitte\n";
  }

  std::cout << "\n\n\n";
  


  for (const auto& itr : AnimalsVec) 
  {
          itr.get_animals_of_relationship(AnimalRelationship::Parent);
          itr.get_animals_of_relationship(AnimalRelationship::Child);
          itr.get_animals_of_relationship(AnimalRelationship::Sibling);
          itr.get_animals_of_relationship(AnimalRelationship::Partner);
  }
  std::cout << "\n\n\n";


  std::cout << "Operator overloading '=='\n";
  if (puppy == kitten)   // operator overloading ==
  {
        std::cout << "\t\t  Same Animal\n";
  }
  else
  {
        std::cout << "\t\t  Not Same Animal\n";
  }


  // using inheritated class
  std::cout << "\n\n\ninheritated class : \n";
  Animal* pNewDog = new Dog {};
  pNewDog->setAge(3); // Hiding base class function (sets 5) because calling base class method
                      // overriding calls subclass function using virtual functionality (method resolution)
  std::cout << "\t\t  pNewDog->getAge() = [" << pNewDog->getAge() << "]\n";
  delete pNewDog;   // will do in dtor if allocated in ctor


  std::cout << "\n\n\nOperator overloading '+'\n";
  Animal *pc = new Animal();
  pc = dogMale + dogFemaleSP; // relationships were added using add_relationshipSP, so the second animal is the SP reference 
  if (pc)
  {
         pc->describe();
  }
  delete pc;    // will do in dtor if allocated in ctor

        
 
  std::cout << "End\n"; 
}

