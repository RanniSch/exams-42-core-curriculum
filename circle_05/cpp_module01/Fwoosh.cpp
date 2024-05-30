/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:48:51 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:35:22 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fwoosh.hpp"

//Fwoosh::Fwoosh()
Fwoosh::Fwoosh() : ASpell("Fwoosh", "fwooshed")
{
	//this->name = "Fwoosh";
	//this->effects = "fwooshed";
}

Fwoosh::~Fwoosh()
{
	
}

//Fwoosh *Fwoosh::clone() const
ASpell *Fwoosh::clone() const
{
	return (new Fwoosh());
}