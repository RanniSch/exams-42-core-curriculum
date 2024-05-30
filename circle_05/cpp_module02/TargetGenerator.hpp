/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:56:25 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:59:19 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include "ATarget.hpp"
# include <map>
//# include <vector>

class TargetGenerator
{
		private:
				TargetGenerator(const TargetGenerator &copy);
				TargetGenerator &operator=(const TargetGenerator &src);

				std::map<std::string, ATarget *> targets;
				//std::vector<ATarget*> targets;

		public:
				TargetGenerator();
				~TargetGenerator();

				void learnTargetType(ATarget *target);
				void forgetTargetType(const std::string &targetName);
				ATarget *createTarget(const std::string &targetName);

};

#endif