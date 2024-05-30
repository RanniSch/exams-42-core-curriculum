/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:11:28 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:24:44 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock()
{
	//std::cout << this->name << ": This looks like another boring day." << std::endl;
}

Warlock::Warlock(const std::string &p_name, const std::string &p_title) : name(p_name), title(p_title)
{
		std::cout << this->name << ": This looks like another boring day." << std::endl;
		//std::cout << this->getName() << ": This looks like another boring day." << std::endl;
}

Warlock::Warlock(const Warlock &copy)
{
	this->name = copy.name;
	this->title = copy.title;
	//std::cout << this->name << ": This looks like another boring day." << std::endl;
	//*this = copy;
}

Warlock::~Warlock()
{
	std::cout << this->name << ": My job here is done!" << std::endl;
	
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
	
	//std::vector<ASpell*>::iterator start = this->spells.begin();
	//std::vector<ASpell*>::iterator end = this->spells.end();

	//while (start != end)
	//{
	//	delete (*start);
	//	start++;
	//}
	//this->spells.clear();
}

Warlock &Warlock::operator=(const Warlock &src)
{
	this->name = src.name;
	this->title = src.title;
	//this->spells = src.spells;

	return(*this);
}

const std::string &Warlock::getName() const
{
	return (this->name);
}

const std::string &Warlock::getTitle() const
{
	return (this->title);
}

void Warlock::setTitle(const std::string &p_title)
{
	this->title = p_title;
}

void Warlock::introduce() const
{
	std::cout << this->name << ": I am " << this->name << ", " << this->getTitle() << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *spell)
{
	if (spell)
	{
		std::map<std::string, ASpell *>::iterator it = this->spellBook.find(spell->getName());

		if (it == this->spellBook.end())
		{
			this->spellBook[spell->getName()] = spell->clone();
		}
	}
	
	//std::vector<ASpell*>::iterator start = this->spells.begin();
	//std::vector<ASpell*>::iterator end = this->spells.end();
	
	//while (start != end)
	//{
	//	if ((*start)->getName().compare(spell->getName()) == 0)
	//		return ;
	//	start++;
	//}
	//this->spells.push_back(spell->clone());
}

void Warlock::forgetSpell(const std::string spellName)
{
	std::map<std::string, ASpell *>::iterator it = this->spellBook.find(spellName);
	if (it != this->spellBook.end())
	{
		delete it->second;
		this->spellBook.erase(it);
	}
	
	//std::vector<ASpell*>::iterator start = this->spells.begin();
	//std::vector<ASpell*>::iterator end = this->spells.end();

	//while (start != end)
	//{
	//	if ((*start)->getName().compare(spell_name) == 0)
	//	{
	//		this->spells.erase(start);
	//		return ;
	//	}
	//	start++;
	//}
}
void Warlock::launchSpell(const std::string spellName, const ATarget &target) const
{
	std::map<std::string, ASpell *>::const_iterator it = this->spellBook.find(spellName);
	
	if (it != this->spellBook.end())
		it->second->launch(target);
	
	//std::vector<ASpell*>::iterator start = this->spells.begin();
	//std::vector<ASpell*>::iterator end = this->spells.end();

	//while (start != end)
	//{
	//	if ((*start)->getName().compare(spell_nam) == 0)
	//	{
	//		(*start)->launch(target);
	//	}
	//	start++;
	//}
}
