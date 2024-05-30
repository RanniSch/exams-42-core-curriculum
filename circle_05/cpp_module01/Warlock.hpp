/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:11:39 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 09:19:05 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <map>
//# include <vector>
# include "ASpell.hpp"
# include "ATarget.hpp"

class Warlock
{
		private:
				std::string name;
				std::string title;
				
				Warlock();
				Warlock(const Warlock &copy);
				Warlock &operator=(const Warlock &src);

				std::map<std::string, ASpell *> spellBook;
				//std::vector<ASpell*> spells;
	
		public:
				Warlock(const std::string &p_name, const std::string &p_title);
				~Warlock();

				const std::string &getName() const;
				const std::string &getTitle() const;

				void setTitle(const std::string &p_title);

				void introduce() const;

				void learnSpell(ASpell *spell);
				void forgetSpell(const std::string spellName);
				void launchSpell(const std::string spellName, const ATarget &target) const;
};

#endif
