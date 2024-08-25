#include <iostream>
#include <string>
#include <memory>
#include <vector>

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
        //int age;
        double weight;
        double height;
        double BMI;
        std::vector<std::pair<std::shared_ptr<Animal>, AnimalRelationship>> animalrelationshipsvecSP;

    protected:
        int age;

    public:
        Animal(); // default ctor
        Animal(std::string name, int age, double weight, double height);  // parameterized ctor
        ~Animal();

        static std::string getAnimalRelationship(const AnimalRelationship& rel);
        static std::string get_weight_type(const double& BMI);

        void setName(const std::string& iname);
        const std::string& getName() const;
        void setAge(const int& a);
        void setBMI(const double& weight, const double& height);
        const double get_portion_size(void) const;
        const double getBMI(void);
        const int getAge(void);
        void setWeight(const double& a);
        const double getWeight(void);
        void setHeight(const double& a);
        const double getHeight(void);
        void add_relationshipSP(const std::shared_ptr<Animal>& animal, AnimalRelationship relationship);
        bool hasRelationship(const AnimalRelationship& relationship);
        void get_animals_of_relationship(const AnimalRelationship& relationship_type) const;
        const void describe() const;

        bool operator== (const Animal &other);
};


class Dog : public Animal 
{
    private :

    public :
        void setAge(const int& a);
        const int getAge(void);
};

