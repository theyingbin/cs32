#include <iostream>
#include <string>
using namespace std;

class Character{
public:
	Character(string name){
		m_name = name;
	}
	string name() const{
		return m_name;
	}
	virtual void printWeapon() const = 0;
	virtual string attackAction() const{
		return "rushes toward the enemy";
	}
	virtual ~Character(){

	}
private:
	string m_name;
};
class Dwarf: public Character{
public:
	Dwarf(string name)
		:Character(name)
	{
		m_weapon = "axe";
	}
	virtual void printWeapon() const{
		cout << "an " << m_weapon;
	}
	virtual ~Dwarf(){
		cout << "Destroying " << name() << " the dwarf" << endl;
	}
private:
	string m_weapon;
};
class Elf : public Character{
public:
	Elf(string name, int numArrows)
		:Character(name)
	{
		m_weapon = "bow";
		m_numArrows = numArrows;
	}
	virtual void printWeapon() const{
		cout << "a " << m_weapon << " and quiver of " << m_numArrows << " arrow";
		if (m_numArrows != 1)
			cout << "s";
	}
	virtual ~Elf(){
		cout << "Destroying " << name() << " the elf" << endl;
	}
private:
	string m_weapon;
	int m_numArrows;
};
class Boggie : public Character{
public:
	Boggie(string name)
		:Character(name)
	{
		m_weapon = "short sword";
	}
	virtual void printWeapon() const{
		cout << "a " << m_weapon;
	}
	virtual string attackAction() const{
		return "whimpers";
	}
	virtual ~Boggie(){
		cout << "Destroying " << name() << " the boggie" << endl;
	}
private:
	string m_weapon;
};
