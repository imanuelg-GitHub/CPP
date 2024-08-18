#include <iostream>
#include <string>
#include <memory>
#include <vector>

std::string getAnimalRelationship(int val);

enum class AnimalRelationship
{
  Parent = 0, 
  Child,   
  Sibling,
  Partner
};

class Animal
{
    private:
        std::string name;
        int age;
        double weight;
        std::vector<std::pair<std::shared_ptr<Animal>, AnimalRelationship>> animalrelationshipsvecSP;
        std::vector<int> AmiVec;

    public:
        Animal(); // default ctor
        Animal(std::string name, int age, double weight);  // parameterized ctor
        ~Animal();
        void setName(std::string iname);
        std::string getName(void);
        void setAge(int a);
        int getAge(void);
        void setWeight(double a);
        double getWeight(void);
        void add_relationship(Animal animal, AnimalRelationship relationship);
        void add_relationshipSP(std::shared_ptr<Animal> animal, AnimalRelationship relationship);
        bool hasRelationship(AnimalRelationship relationship);
        void get_animals_of_relationship(AnimalRelationship relationship_type);
        void describe(Animal& animal);
        friend void describeFriend(Animal &animal);
        friend void get_animals_of_relationship(Animal& animal, AnimalRelationship relationship_type);
};

