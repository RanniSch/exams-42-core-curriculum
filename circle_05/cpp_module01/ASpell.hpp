/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:36:16 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:29:19 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <iostream>
# include "ATarget.hpp"

class ATarget;

class ASpell
{
		protected:
				std::string name;
				std::string effects;
	
		public:
				ASpell();
				ASpell(const std::string &p_name, const std::string &p_effects);
				ASpell(const ASpell &copy);
				virtual ~ASpell();

				ASpell &operator=(const ASpell &src);
				
				const std::string getName() const;
				const std::string getEffects() const;
				//std::string getName() const;
				//std::string getEffects() const;

				virtual ASpell *clone() const = 0;

				void launch(const ATarget &target) const;
};

#endif
