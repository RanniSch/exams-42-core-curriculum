/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:02 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 10:06:50 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <map>
# include <algorithm>
//# include <vector>
# include "ASpell.hpp"
# include "ATarget.hpp"
# include "SpellBook.hpp"

class Warlock
{
		private:
				std::string name;
				std::string title;
				SpellBook	spellBook;
				
				Warlock();
				Warlock(const Warlock &copy);
				Warlock &operator=(const Warlock &src);
	
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