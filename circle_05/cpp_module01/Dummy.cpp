/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:48:22 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:36:15 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dummy.hpp"

//Dummy::Dummy()
Dummy::Dummy() : ATarget("Target Practice Dummy")
{
	//this->type = "Target Practice Dummy";
}

Dummy::~Dummy()
{

}

//Dummy *Dummy::clone() const
ATarget *Dummy::clone() const
{
	return (new Dummy());
}
