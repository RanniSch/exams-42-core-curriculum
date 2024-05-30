/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:36:32 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 08:41:34 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>
# include "ASpell.hpp"

class ASpell;

class ATarget
{
		protected:
				std::string type;


		public:
				ATarget();
				ATarget(const std::string &p_type);
				ATarget(const ATarget &copy);
				virtual ~ATarget();

				ATarget &operator=(const ATarget &src);

				const std::string &getType() const;

				virtual ATarget *clone() const = 0;

				void getHitBySpell(const ASpell &spell) const;
};

#endif
