/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:45:28 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 10:12:17 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

# include "ASpell.hpp"
# include "ATarget.hpp"
# include <map>
//# include <vector>

class SpellBook
{
		private:
				SpellBook(const SpellBook &copy);
				SpellBook &operator=(const SpellBook &src);

				std::map<std::string, ASpell *> spellBook;

		public:
				SpellBook();
				~SpellBook();

				void learnSpell(ASpell *spell);
				void forgetSpell(const std::string &spellName);
				ASpell *createSpell(const std::string &spellName) const;
};

#endif