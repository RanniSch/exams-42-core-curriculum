/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:13:08 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/18 08:17:13 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>

class Warlock {
		private:
				std::string name;
				std::string title;
				
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
};

#endif

// c++ -Wall -Werror -Wextra Warlock.cpp main.cpp 