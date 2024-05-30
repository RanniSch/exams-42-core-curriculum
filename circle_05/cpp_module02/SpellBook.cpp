#include "SpellBook.hpp"

SpellBook::SpellBook()
{

}

//SpellBook::SpellBook(const SpellBook &copy)
//{
//	*this = copy;
//}

SpellBook::~SpellBook()
{
	if (this->spellBook.size() > 0)
	{
		std::map<std::string, ASpell *>::iterator it = this->spellBook.begin();
		std::map<std::string, ASpell *>::iterator ite = this->spellBook.end();
		while (it != ite)
		{
			delete it->second;
			it++;
		}
	}
}

//SpellBook &SpellBook::operator=(const SpellBook &src)
//{
//	this->book = src.book;

//	return (*this);
//}

void SpellBook::learnSpell(ASpell *spell)
{
	if (spell)
	{
	//	this->spellBook.insert(std::pair<std::string, ASpell *>(spell->getName(), spell));
		std::map<std::string, ASpell *>::iterator it = this->spellBook.find(spell->getName());
		if (it == spellBook.end())
			this->spellBook[spell->getName()] = spell->clone();
	}
}

void SpellBook::forgetSpell(const std::string &spellName)
{
	std::map<std::string, ASpell *>::iterator it = this->spellBook.find(spellName);

	if (it != this->spellBook.end())
	{
		delete it->second;
		this->spellBook.erase(it);
	}
}

ASpell *SpellBook::createSpell(const std::string &spellName) const
{
	std::map<std::string, ASpell *>::const_iterator it = this->spellBook.find(spellName);

	if (it != this->spellBook.end())
	{
		return (it->second->clone());
	}
	return (NULL);
}
