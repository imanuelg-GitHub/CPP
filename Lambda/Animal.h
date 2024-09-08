#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>
 

typedef std::function<double(void)> amitf;

enum class AnimalRelationship
{
      Parent = 0, 
      Child,   
      Sibling,
      Partner
};

enum class AnimalWeightType
{
        Unknown = -1,
        Underweight = 0,
        Normal,
        Overweight,
        Obese
};



class Animal
{
    private:
        std::string name;
        double weight;
        double height;
        std::vector<std::pair<std::shared_ptr<Animal>, AnimalRelationship>> animalrelationshipsvecSP;

    protected:
        int age;

    public:
        Animal(); // default ctor
        Animal(std::string name, int age, double weight, double height);  // parameterized ctor
        virtual ~Animal();

        static std::string getAnimalRelationship(const AnimalRelationship& rel);


        // First = function return type cannot be modified
        // Second = parameters cannot be modified
        // Third = object member variables cannot be modified

        void setName(const std::string& iname);
        const std::string& getName() const;
        virtual void setAge(const int& a);
        const double get_portion_size() const;
        inline const double getBMI() const;
        const int getAge() const;
        void setWeight(const double& a);
        const double getWeight() const;
        void setHeight(const double& a);
        const double getHeight();
        void add_relationshipSP(const std::shared_ptr<Animal>& animal, AnimalRelationship relationship);
        bool hasRelationship(const std::shared_ptr<Animal>& animal, const AnimalRelationship& relationship);
        void get_animals_of_relationship(const AnimalRelationship& relationship_type) const;
        const std::string get_weight_type() const;
        const void describe() const;

        bool operator== (const Animal& other);
        Animal* operator+ (std::shared_ptr<Animal>& parent2);

        std::function<double(void)> getBMIlambdaInHfile = [=]() -> double   // [=] capture by value, can also do [&] capture by ref
        { 
            if (height != 0)   // error handling for division by 0
            {
                return weight / (height * height);
            }
            else
            {
                std::cout << "Cannot divide by " << height << ". Returning -1\n";
                return -1.0;
            } 
        };

        std::function<double(void)> getBMIlambdaInCPPfile;
};


class Dog : public Animal 
{


    private :

    public :
        Dog() : Animal(){} // default ctor
        Dog(std::string name, int age, double weight, double height) : Animal(name, age, weight, height)
        {
        }
        void setAge(const int& a) override;  // Don't have to use 'overide', works anyway with 'virtual'
        const int getAge() const;
};

