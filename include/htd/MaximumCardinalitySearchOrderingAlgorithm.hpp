/* 
 * File:   MaximumCardinalitySearchOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_HPP
#define	HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_HPP

#include <vector>

#include <htd/Globals.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>

namespace htd
{
    class MaximumCardinalitySearchOrderingAlgorithm : public virtual htd::IOrderingAlgorithm
    {
        public:
            MaximumCardinalitySearchOrderingAlgorithm(void);
            
            ~MaximumCardinalitySearchOrderingAlgorithm();
            
            htd::ConstCollection<htd::vertex_t> computeOrdering(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            MaximumCardinalitySearchOrderingAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            MaximumCardinalitySearchOrderingAlgorithm & operator=(const MaximumCardinalitySearchOrderingAlgorithm &) { return *this; }
    };
}

#endif /* HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_HPP */