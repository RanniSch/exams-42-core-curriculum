/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:07:30 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 10:10:40 by rschlott         ###   ########.fr       */
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
		this->spellBook.learnSpell(spell);
}

void Warlock::forgetSpell(const std::string spellName)
{
	this->spellBook.forgetSpell(spellName);
}
void Warlock::launchSpell(const std::string spellName, const ATarget &target) const
{
	ASpell * castSpell = spellBook.createSpell(spellName);
	
	if (castSpell)
	{
		castSpell->launch(target);
		delete castSpell;
	}
}
