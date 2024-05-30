/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:40:47 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:40:56 by rschlott         ###   ########.fr       */
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
