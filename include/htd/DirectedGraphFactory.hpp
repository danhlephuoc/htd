/*
 * File:   DirectedGraphFactory.hpp
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

#ifndef HTD_HTD_DIRECTEDGRAPHFACTORY_HPP
#define HTD_HTD_DIRECTEDGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/GraphTypeFactory.hpp>
#include <htd/IMutableDirectedGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableDirectedGraph interface.
     */
    class DirectedGraphFactory : public htd::GraphTypeFactory<htd::IDirectedGraph, htd::IMutableDirectedGraph>
    {
        public:
            using htd::GraphTypeFactory<htd::IDirectedGraph, htd::IMutableDirectedGraph>::createInstance;

            /**
             *  Constructor for the factory class.
             */
            HTD_API DirectedGraphFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API DirectedGraphFactory(const DirectedGraphFactory & original) = delete;

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API DirectedGraphFactory & operator=(const DirectedGraphFactory & original) = delete;

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~DirectedGraphFactory();

            /**
             *  Create a new IMutableDirectedGraph object.
             *
             *  @return A new IMutableDirectedGraph object.
             */
            HTD_API htd::IMutableDirectedGraph * createInstance(void) const HTD_OVERRIDE;

            /**
             *  Create a new IMutableDirectedGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableDirectedGraph object of the given size.
             */
            HTD_API htd::IMutableDirectedGraph * createInstance(std::size_t initialSize) const;
    };
}

#endif /* HTD_HTD_DIRECTEDGRAPHFACTORY_HPP */
