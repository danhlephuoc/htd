/* 
 * File:   LabeledHypergraph.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_HTD_LABELEDHYPERGRAPH_HPP
#define	HTD_HTD_LABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Hypergraph.hpp>
#include <htd/ILabeledHypergraph.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/BidirectionalGraphLabeling.hpp>
#include <htd/Label.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>

#include <set>
#include <vector>
#include <stdexcept>

namespace htd
{
    template<typename VertexLabelType, typename HyperedgeLabelType>
    class LabeledHypergraph : public htd::Hypergraph, public virtual htd::ILabeledHypergraph
    {
        public:
            LabeledHypergraph<VertexLabelType, HyperedgeLabelType>(void) : Hypergraph(), labelings_()
            {
                labelings_.setLabeling(htd::name_label_name, new htd::BidirectionalGraphLabeling());
            }
            
            LabeledHypergraph<VertexLabelType, HyperedgeLabelType>(std::size_t size) : Hypergraph(size), labelings_()
            {
                labelings_.setLabeling(htd::name_label_name, new htd::BidirectionalGraphLabeling());
            }
            
            ~LabeledHypergraph<VertexLabelType, HyperedgeLabelType>()
            {

            }

            std::size_t edgeCount(const VertexLabelType & vertexLabel) const
            {
                std::size_t ret = 0;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    ret = htd::Hypergraph::edgeCount(locatedVertex);
                }
                else
                {
                    throw std::logic_error("std::size_t htd::LabeledHypergraph::edgeCount(const VertexLabelType &) const");
                }

                return ret;
            }

            bool isVertex(const VertexLabelType & vertexLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::name_label_name))
                {
                    auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(vertexLabel);

                        ret = labeling->isVertexLabel(label);
                    }
                }

                return ret;
            }

            bool isHyperedge(const HyperedgeLabelType & edgeLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::name_label_name))
                {
                    auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(edgeLabel);

                        ret = labeling->isHyperedgeLabel(label);
                    }
                }

                return ret;
            }
            bool isConnected(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2) const
            {
                bool ret = false;

                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::unknown_vertex && locatedVertex2 != htd::unknown_vertex)
                {
                    ret = htd::Hypergraph::isConnected(locatedVertex1, locatedVertex2);
                }

                return ret;
            }

            bool isNeighbor(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2) const
            {
                bool ret = false;

                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::unknown_vertex && locatedVertex2 != htd::unknown_vertex)
                {
                    ret = htd::Hypergraph::isNeighbor(locatedVertex1, locatedVertex2);
                }

                return ret;
            }
            
            std::size_t neighborCount(const VertexLabelType & vertexLabel) const
            {
                std::size_t ret = 0;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    ret = htd::Hypergraph::neighborCount(locatedVertex);
                }

                return ret;
            }
            
            void getNeighbors(const VertexLabelType & vertexLabel, htd::vertex_container & output) const
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    htd::Hypergraph::getNeighbors(locatedVertex, output);
                }
            }

            htd::vertex_t neighbor(const VertexLabelType & vertexLabel, htd::index_t index) const
            {
                htd::vertex_t ret = 0;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    ret = htd::Hypergraph::neighbor(locatedVertex, index);
                }
                else
                {
                    throw std::out_of_range("htd::vertex_t htd::LabeledHypergraph::neighbor(const VertexLabelType &, htd::index_t)");
                }

                return ret;
            }

            bool isIsolatedVertex(const VertexLabelType & vertexLabel) const
            {
                bool ret = false;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    ret = htd::Hypergraph::isIsolatedVertex(locatedVertex);
                }

                return ret;
            }

            void getHyperedges(htd::hyperedge_container & output, const VertexLabelType & vertexLabel) const
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    htd::Hypergraph::getHyperedges(output, locatedVertex);
                }
            }

            const htd::hyperedge_t & hyperedge(htd::index_t index, const VertexLabelType & vertexLabel) const
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex == htd::unknown_vertex)
                {
                    throw std::out_of_range("htd::vertex_t htd::LabeledHypergraph::hyperedge(htd::index_t, const VertexLabelType &)");
                }

                return htd::Hypergraph::hyperedge(index, locatedVertex);
            }

            htd::vertex_t addVertex(const VertexLabelType & vertexLabel)
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    throw std::logic_error("htd::vertex_t htd::LabeledHypergraph::addVertex(const VertexLabelType &)");
                }

                htd::vertex_t ret = htd::Hypergraph::addVertex();

                setVertexName(ret, vertexLabel);

                return ret;
            }

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE
            {
                labelings_.removeLabels(vertex);

                htd::Hypergraph::removeVertex(vertex);
            }

            void removeVertex(const VertexLabelType & vertexLabel)
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    labelings_.removeLabels(locatedVertex);

                    htd::Hypergraph::removeVertex(locatedVertex);
                }
            }

            void removeVertex(htd::vertex_t vertex, bool addNeighborHyperedge) HTD_OVERRIDE
            {
                labelings_.removeLabels(vertex);

                htd::Hypergraph::removeVertex(vertex, addNeighborHyperedge);
            }

            void removeVertex(const VertexLabelType & vertexLabel, bool addNeighborHyperedge)
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::unknown_vertex)
                {
                    labelings_.removeLabels(locatedVertex);

                    htd::Hypergraph::removeVertex(locatedVertex, addNeighborHyperedge);
                }
            }

            void addEdge(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2)
            {
                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::unknown_vertex && locatedVertex2 != htd::unknown_vertex)
                {
                    htd::Hypergraph::addEdge(locatedVertex1, locatedVertex2);
                }
                else
                {
                    throw std::logic_error("std::size_t htd::LabeledHypergraph::addEdge(const VertexLabelType &, const VertexLabelType &)");
                }
            }

            void addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2, const HyperedgeLabelType & label)
            {
                htd::Hypergraph::addEdge(vertex1, vertex2);

                htd::hyperedge_t hyperedge;

                hyperedge.push_back(vertex1);
                hyperedge.push_back(vertex2);

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                setHyperedgeName(hyperedge, label);
            }

            void addEdge(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2, const HyperedgeLabelType & label)
            {
                Label<VertexLabelType> label1(vertexLabel1);
                Label<VertexLabelType> label2(vertexLabel2);

                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::unknown_vertex && locatedVertex2 != htd::unknown_vertex)
                {
                    addEdge(locatedVertex1, locatedVertex2);
                }
            }

            void addEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertex(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(vertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::addEdge(hyperedge);
                }
            }

            void addEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end, const HyperedgeLabelType & label)
            {
                htd::Hypergraph::addEdge(begin, end);

                htd::hyperedge_t hyperedge(begin, end);

                setHyperedgeName(hyperedge, label);
            }

            void addEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end, const HyperedgeLabelType & label)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertex(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(vertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::addEdge(hyperedge);

                    setHyperedgeName(hyperedge, label);
                }
            }

            void addEdge(const std::pair<VertexLabelType, VertexLabelType> & edge)
            {
                addEdge(edge.first, edge.second);
            }

            void addEdge(const htd::edge_t & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.first, edge.second, label);
            }

            void addEdge(const std::pair<VertexLabelType, VertexLabelType> & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.first, edge.second, label);
            }
            
            void addEdge(const std::vector<VertexLabelType> & edge)
            {
                addEdge(edge.begin(), edge.end());
            }

            void addEdge(const std::vector<VertexLabelType> & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.begin(), edge.end(), label);
            }

            void addEdge(const htd::hyperedge_t & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.begin(), edge.end(), label);
            }

            void removeEdge(const HyperedgeLabelType & label)
            {
                HTD_UNUSED(label);

                //TODO Implement
            }
            
            void removeEdge(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2)
            {
                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::unknown_vertex && locatedVertex2 != htd::unknown_vertex)
                {
                    htd::Hypergraph::removeEdge(locatedVertex1, locatedVertex2);
                }
            }
            
            void removeEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    ok = isVertex(*it);

                    if (ok)
                    {
                        hyperedge.push_back(vertex(*it));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::removeEdge(hyperedge);

                    labelings_.removeLabels(hyperedge);
                }
            }
            
            void removeEdge(const std::pair<VertexLabelType, VertexLabelType> & edge)
            {
                removeEdge(edge.first, edge.second);
            }
            
            void removeEdge(const std::vector<VertexLabelType> & edge)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto & vertex : edge)
                {
                    ok = isVertex(vertex);

                    if (ok)
                    {
                        hyperedge.push_back(vertex(vertex));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::removeEdge(hyperedge);

                    labelings_.removeLabels(hyperedge);
                }
            }

            std::size_t labelCount(void) const HTD_OVERRIDE
            {
                return labelings_.labelCount();
            }


            void getLabelNames(std::vector<std::string> & output) const HTD_OVERRIDE
            {
                return labelings_.getLabelNames(output);
            }

            std::string labelName(htd::index_t index) const HTD_OVERRIDE
            {
                if (index >= labelings_.labelCount())
                {
                    throw std::out_of_range("std::string htd::LabeledHypergraph::labelName(htd::index_t) const");
                }

                return labelings_.labelName(index);
            }

            const htd::ILabel * label(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE
            {
                if (!labelings_.isLabelingName(labelName))
                {
                    throw std::out_of_range("std::string htd::LabeledHypergraph::labelName(htd::index_t) const");
                }

                auto labeling = labelings_.labeling(labelName);

                if (labeling->hasLabel(vertex))
                {
                    throw std::out_of_range("std::string htd::LabeledHypergraph::labelName(htd::index_t) const");
                }

                return labeling->label(vertex);
            }

            htd::IGraphLabeling * cloneLabeling(const std::string & labelName) const HTD_OVERRIDE
            {
                if (!labelings_.isLabelingName(labelName))
                {
                    throw std::out_of_range("std::string htd::LabeledHypergraph::labelName(htd::index_t) const");
                }

                return labelings_.labeling(labelName)->clone();
            }

            bool hasLabel(const std::string & labelName, htd::vertex_t vertex) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(labelName))
                {
                    auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                    if (labeling != nullptr)
                    {
                        ret = labeling->hasLabel(vertex);
                    }
                }

                return ret;
            }

            bool hasLabel(const std::string & labelName, const htd::hyperedge_t & edge) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(labelName))
                {
                    auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                    if (labeling != nullptr)
                    {
                        ret = labeling->hasLabel(edge);
                    }
                }

                return ret;
            }

            const VertexLabelType & label(htd::vertex_t vertex) const
            {
                if (!labelings_.isLabelingName(labelName))
                {
                    throw std::logic_error("const VertexLabelType & htd::LabeledHypergraph::label(htd::vertex_t) const");
                }

                auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                if (labeling == nullptr)
                {
                    throw std::logic_error("const VertexLabelType & htd::LabeledHypergraph::label(htd::vertex_t) const");
                }

                if (!labeling->hasLabel(vertex))
                {
                    throw std::logic_error("const VertexLabelType & htd::LabeledHypergraph::label(htd::vertex_t) const");
                }

                auto label = dynamic_cast<htd::Label<VertexLabelType> *>(labeling->label(vertex));

                return *(label->value);
            }

            const HyperedgeLabelType & label(const htd::hyperedge_t & edge) const
            {
                if (!labelings_.isLabelingName(labelName))
                {
                    throw std::logic_error("const HyperedgeLabelType & htd::LabeledHypergraph::label(const htd::hyperedge_t &) const");
                }

                auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                if (labeling == nullptr)
                {
                    throw std::logic_error("const HyperedgeLabelType & htd::LabeledHypergraph::label(const htd::hyperedge_t &) const");
                }

                if (!labeling->hasLabel(vertex))
                {
                    throw std::logic_error("const HyperedgeLabelType & htd::LabeledHypergraph::label(const htd::hyperedge_t &) const");
                }

                auto label = dynamic_cast<htd::Label<HyperedgeLabelType> *>(labeling->label(edge));

                return *(label->value);
            }

            void setLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IGraphLabeling *>(labelings_.labeling(labelName));

                if (labeling != nullptr)
                {
                    labeling->setLabel(vertex, label);
                }
            }

            void setLabel(const std::string & labelName, const htd::hyperedge_t & edge, htd::ILabel * label)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IGraphLabeling *>(labelings_.labeling(labelName));

                if (labeling != nullptr)
                {
                    labeling->setLabel(edge, label);
                }
            }

            void removeLabel(const std::string & labelName, htd::vertex_t vertex)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IGraphLabeling *>(labelings_.labeling(labelName));

                if (labeling != nullptr)
                {
                    labeling->removeLabel(vertex);
                }
            }

            void removeLabel(const std::string & labelName, const htd::hyperedge_t & edge)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IGraphLabeling *>(labelings_.labeling(labelName));

                if (labeling != nullptr)
                {
                    labeling->removeLabel(edge);
                }
            }

            bool isVertexName(const VertexLabelType & vertexLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::name_label_name))
                {
                    auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(vertexLabel);

                        ret = labeling->isVertexLabel(label);
                    }
                }

                return ret;
            }

            bool isHyperedgeName(const HyperedgeLabelType & edgeLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::name_label_name))
                {
                    auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(edgeLabel);

                        ret = labeling->isHyperedgeLabel(label);
                    }
                }

                return ret;
            }

            htd::vertex_t getVertex(const VertexLabelType & label) const
            {
                if (isVertex(label))
                {
                    throw std::logic_error("htd::vertex_t htd::LabeledHypergraph::getVertex(const VertexLabelType &) const");
                }

                return vertex(label);
            }

            const htd::hyperedge_t & getHyperedge(const HyperedgeLabelType & label) const
            {
                if (isHyperedge(label))
                {
                    throw std::logic_error("htd::vertex_t htd::LabeledHypergraph::getHyperedge(const HyperedgeLabelType &) const");
                }

                return hyperedge(label);
            }

        private:
            htd::LabelingCollection labelings_;

            htd::vertex_t vertex(const VertexLabelType & vertexLabel) const
            {
                htd::vertex_t ret = htd::unknown_vertex;

                if (labelings_.isLabelingName(htd::name_label_name))
                {
                    auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(vertexLabel);

                        if (labeling->isVertexLabel(label))
                        {
                            ret = labeling->getVertex(label);
                        }
                    }
                }

                return ret;
            }

            const htd::hyperedge_t & hyperedge(const HyperedgeLabelType & edgeLabel) const
            {
                if (!labelings_.isLabelingName(htd::name_label_name))
                {
                    throw std::logic_error("const htd::hyperedge_t & htd::LabeledHypergraph::hyperedge(const HyperedgeLabelType &) const");
                }

                auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                if (labeling == nullptr)
                {
                    throw std::logic_error("const htd::hyperedge_t & htd::LabeledHypergraph::hyperedge(const HyperedgeLabelType &) const");
                }

                Label<VertexLabelType> label(edgeLabel);

                if (!labeling->isHyperedgeLabel(label))
                {
                    throw std::logic_error("const htd::hyperedge_t & htd::LabeledHypergraph::hyperedge(const HyperedgeLabelType &) const");
                }

                return labeling->getHyperedge(label);
            }

            void setVertexName(htd::vertex_t vertex, const VertexLabelType & vertexLabel)
            {
                if (labelings_.isLabelingName(htd::name_label_name))
                {
                    labelings_.setLabeling(htd::name_label_name, new htd::BidirectionalGraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                if (labeling != nullptr)
                {
                    Label<VertexLabelType> label(vertexLabel);

                    labeling->setLabel(vertex, label);
                }
            }

            void setHyperedgeName(const htd::hyperedge_t & edge, const HyperedgeLabelType & edgeLabel)
            {
                if (labelings_.isLabelingName(htd::name_label_name))
                {
                    labelings_.setLabeling(htd::name_label_name, new htd::BidirectionalGraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(labelings_.labeling(htd::name_label_name));

                if (labeling != nullptr)
                {
                    Label<HyperedgeLabelType> label(edgeLabel);

                    labeling->setLabel(edge, label);
                }
            }
    };
}

#endif /* HTD_HTD_LABELEDHYPERGRAPH_HPP */
