/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:36:24 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:30:18 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"

ASpell::ASpell()
{
	this->name = "no name";
	this->effects = "no effects";
}

ASpell::ASpell(const std::string &p_name, const std::string &p_effects) : name(p_name), effects(p_effects)
{

}

ASpell::ASpell(const ASpell &copy)
{
	this->name = copy.name;
	this->effects = copy.effects;
	//*this = copy;
}

ASpell::~ASpell()
{

}

ASpell &ASpell::operator=(const ASpell &src)
{
	this->name = src.name;
	this->effects = src.effects;

	return (*this);

}

const std::string ASpell::getName() const
{
	return (this->name);
}

const std::string ASpell::getEffects() const
{
	return (this->effects);
}

void ASpell::launch(const ATarget &target) const
{
	target.getHitBySpell(*this);
}
