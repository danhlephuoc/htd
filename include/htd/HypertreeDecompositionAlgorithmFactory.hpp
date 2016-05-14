/*
 * File:   HypertreeDecompositionAlgorithmFactory.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IHypertreeDecompositionAlgorithm.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IHypertreeDecompositionAlgorithm interface.
     */
    class HypertreeDecompositionAlgorithmFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~HypertreeDecompositionAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static HypertreeDecompositionAlgorithmFactory & instance(void);

            htd::IHypertreeDecompositionAlgorithm * getHypertreeDecompositionAlgorithm(void);

            void setConstructionTemplate(htd::IHypertreeDecompositionAlgorithm * original);

            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation);

            void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

        private:
            htd::IHypertreeDecompositionAlgorithm * constructionTemplate_;

            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations_;

            HypertreeDecompositionAlgorithmFactory(void);

            HypertreeDecompositionAlgorithmFactory(const HypertreeDecompositionAlgorithmFactory & original);

            HypertreeDecompositionAlgorithmFactory & operator=(const HypertreeDecompositionAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_HPP */
