/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:56:48 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 10:03:14 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{

}

TargetGenerator::TargetGenerator(const TargetGenerator &copy)
{
	*this = copy;
}

TargetGenerator::~TargetGenerator()
{
	if (this->targets.size() > 0)
	{
		std::map<std::string, ATarget *>::iterator it = this->targets.begin();
		std::map<std::string, ATarget *>::iterator ite = this->targets.end();
		while (it != ite)
		{
			delete it->second;
			it++;
		}
	}
	
	//std::vector<ATarget*>::iterator start = this->targets.begin();
	//std::vector<ATarget*>::iterator end = this->targets.end();

	//while(start != end)
	//{
	//	if ((*start)->getType().size() > 0)
	//		delete *start;
	//	start++;
	//}

	//this->targets.clear();
}

TargetGenerator &TargetGenerator::operator=(const TargetGenerator &src)
{
	this->targets = src.targets;
	return (*this);
}

void TargetGenerator::learnTargetType(ATarget *target)
{
	if (target)
	{
		std::map<std::string, ATarget *>::iterator it = this->targets.find(target->getType());
		if (it == targets.end())
		this->targets[target->getType()] = target->clone();
	}
	
	//if (target)
	//{
	//	std::vector<ATarget*>::iterator start = this->targets.begin();
	//	std::vector<ATarget*>::iterator end = this->targets.end();

	//	while(start != end)
	//	{
	//		if ((*start)->getType().compare(target->getType()) == 0)
	//			return ;
	//		start++;
	//	}

	//	this->targets.push_back(target->clone());
	//}
}

void TargetGenerator::forgetTargetType(std::string const &targetName)
{
	std::map<std::string, ATarget *>::iterator it = this->targets.find(targetName);

	if (it != this->targets.end())
	{
		delete it->second;
		this->targets.erase(it);
	}
		
	//std::vector<ATarget*>::iterator start = this->targets.begin();
	//std::vector<ATarget*>::iterator end = this->targets.end();

	//while(start != end)
	//{
	//	if ((*start)->getType().compare(target) == 0)
	//	{
	//		delete *start;
	//		start = this->targets.erase(start);
	//	}
	//	start++;
	//}
}

ATarget *TargetGenerator::createTarget(std::string const &targetName)
{
	std::map<std::string, ATarget *>::iterator it = this->targets.find(targetName);

	if (it != this->targets.end())
	{
		return (it->second->clone());
	}
	return (NULL);
	
	//std::vector<ATarget*>::iterator ite = this->targets.end();
	//for (std::vector<ATarget*>::iterator it = this->targets.begin(); it != ite; ++it)
	//{
	//	if ((*it)->getType() == target) {
	//		return (*it);
	//	}
	//}
	//return (nullptr);
}
