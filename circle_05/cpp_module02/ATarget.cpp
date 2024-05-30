/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:32:15 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:32:23 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"

ATarget::ATarget()
{
	this->type = "no type";
}

ATarget::ATarget(const std::string &p_type) : type(p_type)
{

}

ATarget::ATarget(const ATarget &copy)
{
	this->type = copy.type;
	//*this = copy;
}

ATarget::~ATarget()
{

}

ATarget &ATarget::operator=(const ATarget &src)
{
	this->type = src.type;

	return (*this);
}

const std::string &ATarget::getType() const
{
	return (this->type);
}

void ATarget::getHitBySpell(const ASpell &spell) const
{
	std::cout << this->type << " has been " << spell.getEffects() << "!" << std::endl;
}
