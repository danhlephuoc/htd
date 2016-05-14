/*
 * File:   ConnectedComponentAlgorithmFactory.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2016, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 *
 * This file is part of htd.
 *
 * htd is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * htd is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP
#define HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IConnectedComponentAlgorithm.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IConnectedComponentAlgorithm interface.
     */
    class ConnectedComponentAlgorithmFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~ConnectedComponentAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static ConnectedComponentAlgorithmFactory & instance(void);

            htd::IConnectedComponentAlgorithm * getConnectedComponentAlgorithm(void);

            void setConstructionTemplate(htd::IConnectedComponentAlgorithm * original);

        private:
            htd::IConnectedComponentAlgorithm * constructionTemplate_;

            ConnectedComponentAlgorithmFactory(void);

            ConnectedComponentAlgorithmFactory(const ConnectedComponentAlgorithmFactory & original);

            ConnectedComponentAlgorithmFactory & operator=(const ConnectedComponentAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP */
