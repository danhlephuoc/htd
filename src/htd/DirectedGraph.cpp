/* 
 * File:   DirectedGraph.cpp
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

#ifndef HTD_HTD_DIRECTEDGRAPH_CPP
#define	HTD_HTD_DIRECTEDGRAPH_CPP

#include <htd/Helpers.hpp>
#include <htd/DirectedGraph.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <set>

htd::DirectedGraph::DirectedGraph(void) : htd::DirectedGraph::DirectedGraph(0)
{

}

htd::DirectedGraph::DirectedGraph(std::size_t size)
    : size_(size),
      next_vertex_(htd::first_vertex + size),
      deletions_(),
      incomingNeighborhood_(size, std::set<htd::vertex_t>()),
      outgoingNeighborhood_(size, std::set<htd::vertex_t>())
{
    
}

htd::DirectedGraph::~DirectedGraph()
{
    
}

std::size_t htd::DirectedGraph::vertexCount(void) const
{
    return size_ - deletions_.size();
}

std::size_t htd::DirectedGraph::edgeCount(void) const
{
    std::size_t ret = 0;
    
    for (auto& v : outgoingNeighborhood_)
    {
        ret += v.size();
    }
    
    return ret;
}

std::size_t htd::DirectedGraph::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = incomingNeighborhood_[vertex].size() + outgoingNeighborhood_[vertex].size();
    }
    else
    {
        throw std::out_of_range("std::size_t htd::DirectedGraph::edgeCount(htd::vertex_t) const");
    }

    return ret;
}

bool htd::DirectedGraph::isVertex(htd::vertex_t vertex) const
{
    return vertex < next_vertex_ && vertex != htd::unknown_vertex && !std::binary_search(deletions_.begin(), deletions_.end(), vertex);
}

htd::vertex_t htd::DirectedGraph::vertex(htd::index_t index) const
{
    htd::vertex_t ret = htd::unknown_vertex;
    
    if (index < size_ - deletions_.size())
    {
        htd::vertex_t vertex = 0;
        
        std::size_t currentIndex = 0;
        
        while (currentIndex < index)
        {
            if (!std::binary_search(deletions_.begin(), deletions_.end(), vertex))
            {
                ++currentIndex;
            }
            
            ++vertex;
        }
        
        ret = vertex;
    }
    
    return ret;
}

bool htd::DirectedGraph::isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    if (!isVertex(vertex1) || !isVertex(vertex2))
    {
        throw std::out_of_range("htd::DirectedGraph::isNeighbor(id_t, id_t)");
    }
    
    return std::binary_search(incomingNeighborhood_[vertex1].begin(), incomingNeighborhood_[vertex1].end(), vertex2) ||
           std::binary_search(outgoingNeighborhood_[vertex1].begin(), outgoingNeighborhood_[vertex1].end(), vertex2);
}

bool htd::DirectedGraph::isIncomingNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    if (!isVertex(vertex1) || !isVertex(vertex2))
    {
        throw std::out_of_range("htd::DirectedGraph::isIncomingNeighbor(id_t, id_t)");
    }
    
    return std::binary_search(incomingNeighborhood_[vertex1].begin(), incomingNeighborhood_[vertex1].end(), vertex2);
}

bool htd::DirectedGraph::isOutgoingNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    if (!isVertex(vertex1) || !isVertex(vertex2))
    {
        throw std::out_of_range("htd::DirectedGraph::isOutgoingNeighbor(id_t, id_t)");
    }
    
    return std::binary_search(outgoingNeighborhood_[vertex1].begin(), outgoingNeighborhood_[vertex1].end(), vertex2);
}

bool htd::DirectedGraph::isConnected(void) const
{
    bool ret = true;
    
    if (size_ > 0)
    {
        htd::vertex_t start = htd::first_vertex;
        
        htd::vertex_container newVertices;
        htd::vertex_container tmpVertices;

        std::vector<bool> reachableVertices(size_);

        for (auto deleted : deletions_)
        {
            reachableVertices[deleted - htd::first_vertex] = true;
            
            if (start == deleted)
            {
                start++;
            }
        }
        
        reachableVertices[start - htd::first_vertex] = true;

        newVertices.push_back(start);

        while (newVertices.size() > 0) 
        {
            std::swap(tmpVertices, newVertices);

            newVertices.resize(0);

            for (htd::vertex_container::const_iterator it = tmpVertices.begin(); it != tmpVertices.end(); it++)
            {
                for (std::set<id_t>::const_iterator it2 = outgoingNeighborhood_[*it - htd::first_vertex].begin(); it2 != outgoingNeighborhood_[*it - htd::first_vertex].end(); it2++)
                {
                    if (!reachableVertices[*it2 - htd::first_vertex])
                    {
                        reachableVertices[*it2 - htd::first_vertex] = true;

                        newVertices.push_back(*it2);
                    }
                }

                for (std::set<id_t>::const_iterator it2 = incomingNeighborhood_[*it - htd::first_vertex].begin(); it2 != incomingNeighborhood_[*it - htd::first_vertex].end(); it2++)
                {
                    if (!reachableVertices[*it2 - htd::first_vertex])
                    {
                        reachableVertices[*it2 - htd::first_vertex] = true;

                        newVertices.push_back(*it2);
                    }
                }
            }
        }
        
        ret = std::find(reachableVertices.begin(), reachableVertices.end(), false) == reachableVertices.end();
    }
    else
    {
        ret = false;
    }
    
    return ret;
}

bool htd::DirectedGraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    bool ret = false;

    if (isVertex(vertex1) && isVertex(vertex2))
    {
        if (vertex1 != vertex2)
        {
            std::vector<id_t> newVertices;
            std::vector<id_t> tmpVertices;

            std::vector<bool> reachableVertices(size_);

            reachableVertices[vertex1] = true;

            newVertices.push_back(vertex1);

            while (!ret && newVertices.size() > 0) 
            {
                std::swap(tmpVertices, newVertices);

                newVertices.resize(0);

                for (std::vector<id_t>::const_iterator it = tmpVertices.begin(); !ret && it != tmpVertices.end(); it++)
                {
                    for (std::set<id_t>::const_iterator it2 = outgoingNeighborhood_[*it].begin(); !ret && it2 != outgoingNeighborhood_[*it].end(); it2++)
                    {
                        if (!reachableVertices[*it2])
                        {
                            reachableVertices[*it2] = true;

                            newVertices.push_back(*it2);

                            ret = *it2 == vertex2;
                        }
                    }

                    for (std::set<id_t>::const_iterator it2 = incomingNeighborhood_[*it].begin(); !ret && it2 != incomingNeighborhood_[*it].end(); it2++)
                    {
                        if (!reachableVertices[*it2])
                        {
                            reachableVertices[*it2] = true;

                            newVertices.push_back(*it2);

                            ret = *it2 == vertex2;
                        }
                    }
                }
            }
        }
        else
        {
            ret = true;
        }
    }
    
    return ret;
}

bool htd::DirectedGraph::isReachable(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    if (!isVertex(vertex1) || !isVertex(vertex2))
    {
        throw std::out_of_range("htd::DirectedGraph::isConnected(id_t, id_t)");
    }
    
    bool ret = false;
    
    //TODO Covered by check above?
    if (std::find(deletions_.begin(), deletions_.end(), vertex1) == deletions_.end() &&
        std::find(deletions_.begin(), deletions_.end(), vertex2) == deletions_.end())
    {
        if (vertex1 != vertex2)
        {
            std::vector<id_t> newVertices;
            std::vector<id_t> tmpVertices;

            std::vector<bool> reachableVertices(size_);

            reachableVertices[vertex1] = true;

            newVertices.push_back(vertex1);

            while (newVertices.size() > 0) 
            {
                std::swap(tmpVertices, newVertices);

                newVertices.resize(0);

                for (std::vector<id_t>::const_iterator it = tmpVertices.begin(); !ret && it != tmpVertices.end(); it++)
                {
                    for (std::set<id_t>::const_iterator it2 = outgoingNeighborhood_[*it].begin(); !ret && it2 != outgoingNeighborhood_[*it].end(); it2++)
                    {
                        if (!reachableVertices[*it2])
                        {
                            reachableVertices[*it2] = true;

                            newVertices.push_back(*it2);

                            ret = *it2 == vertex2;
                        }
                    }
                }
            }
        }
        else
        {
            ret = true;
        }
    }
    
    return ret;
}

std::size_t htd::DirectedGraph::neighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (!isVertex(vertex))
    {
        throw std::out_of_range("htd::DirectedGraph::getNeighborCount(id_t)");
    }
    
    ret = htd::compute_set_union_size(incomingNeighborhood_[vertex].begin(), incomingNeighborhood_[vertex].end(),
                                      outgoingNeighborhood_[vertex].begin(), outgoingNeighborhood_[vertex].end());
    
    return ret;
}

std::size_t htd::DirectedGraph::incomingNeighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (!isVertex(vertex))
    {
        throw std::out_of_range("htd::DirectedGraph::getIncomingNeighborCount(id_t)");
    }
    
    ret = incomingNeighborhood_[vertex].size();
    
    return ret;
}

std::size_t htd::DirectedGraph::outgoingNeighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (!isVertex(vertex))
    {
        throw std::out_of_range("htd::DirectedGraph::getOutgoingNeighborCount(id_t)");
    }
    
    ret = outgoingNeighborhood_[vertex].size();
    
    return ret;
}
            
void htd::DirectedGraph::getNeighbors(htd::vertex_t vertex, vertex_container & output) const
{
    if (isVertex(vertex))
    {
        std::set_union(incomingNeighborhood_[vertex].begin(), incomingNeighborhood_[vertex].end(),
                       outgoingNeighborhood_[vertex].begin(), outgoingNeighborhood_[vertex].end(),
                       std::back_inserter(output));
    }
}

htd::vertex_t htd::DirectedGraph::neighbor(htd::vertex_t vertex, htd::id_t index) const
{
    htd::vertex_t ret = htd::unknown_vertex;
    
    if (isVertex(vertex))
    {
        std::size_t currentIndex = 0;
        
        auto first1 = incomingNeighborhood_[vertex].begin();
        auto first2 = outgoingNeighborhood_[vertex].begin();
        
        auto last1 = incomingNeighborhood_[vertex].end();
        auto last2 = outgoingNeighborhood_[vertex].end();
        
        //TODO Make reusable
        while (currentIndex <= index && first1 != last1) 
        {
            if (first2 == last2)
            {
                while (currentIndex <= index && first1 != last1)
                {    
                    if (currentIndex == index)
                    {
                        ret = *first1;
                    }

                    ++currentIndex;

                    ++first1;
                }
            }
            
            if (*first2 < *first1) 
            {
                if (currentIndex == index)
                {
                    ret = *first2;
                }
                
                ++currentIndex;
                
                ++first2;
            }
            else
            {
                if (currentIndex == index)
                {
                    ret = *first1++;
                }
                
                ++currentIndex;
                
                if (!(*first1 < *first2))
                {
                    ++first2;
                }
                
                ++first1;
            }
        }
        
        while (currentIndex <= index && first2 != last2)
        {    
            if (currentIndex == index)
            {
                ret = *first2;
            }
            
            ++currentIndex;
            
            ++first2;
        }
    }
    
    return ret;
}

void htd::DirectedGraph::getIncomingNeighbors(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (!isVertex(vertex))
    {
        throw std::out_of_range("htd::DirectedGraph::getIncomingNeighbors(id_t, vertex_container&)");
    }
    
    //TODO Covered by check above?
    if (std::find(deletions_.begin(), deletions_.end(), vertex) == deletions_.end())
    {
        std::copy(incomingNeighborhood_[vertex].begin(), incomingNeighborhood_[vertex].end(), std::back_inserter(output));
    }
}

void htd::DirectedGraph::getOutgoingNeighbors(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (!isVertex(vertex))
    {
        throw std::out_of_range("htd::DirectedGraph::getOutgoingNeighbors(id_t, vertex_container&)");
    }

    //TODO Covered by check above?
    if (std::find(deletions_.begin(), deletions_.end(), vertex) == deletions_.end())
    {
        std::copy(outgoingNeighborhood_[vertex].begin(), outgoingNeighborhood_[vertex].end(), std::back_inserter(output));
    }
}

htd::vertex_t htd::DirectedGraph::incomingNeighbor(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::unknown_vertex;

    if (isVertex(vertex))
    {
        auto& neighborhood = incomingNeighborhood_[vertex - htd::first_vertex];

        if (index < neighborhood.size())
        {
            auto position = neighborhood.begin();

            std::advance(position, index);

            ret = *position;
        }
        else
        {
            throw std::out_of_range("htd::vertex_t htd::DirectedGraph::incomingNeighbor(htd::vertex_t, htd::index_t) const");
        }
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::DirectedGraph::incomingNeighbor(htd::vertex_t, htd::index_t) const");
    }

    return ret;
}

htd::vertex_t htd::DirectedGraph::outgoingNeighbor(htd::vertex_t vertex, htd::index_t index) const
{

    htd::vertex_t ret = htd::unknown_vertex;

    if (isVertex(vertex))
    {
        auto& neighborhood = outgoingNeighborhood_[vertex - htd::first_vertex];

        if (index < neighborhood.size())
        {
            auto position = neighborhood.begin();

            std::advance(position, index);

            ret = *position;
        }
        else
        {
            throw std::out_of_range("htd::vertex_t htd::DirectedGraph::outgoingNeighbor(htd::vertex_t, htd::index_t) const");
        }
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::DirectedGraph::outgoingNeighbor(htd::vertex_t, htd::index_t) const");
    }

    return ret;
}

void htd::DirectedGraph::getVertices(htd::vertex_container & output) const
{
    for (htd::vertex_t vertex = 0; vertex < size_; vertex++)
    {
        if (isVertex(vertex))
        {
            output.push_back(vertex);
        }
    }
}

std::size_t htd::DirectedGraph::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex = 0; vertex < size_; vertex++)
    {
        if (isVertex(vertex))
        {
            if (incomingNeighborhood_[vertex - htd::first_vertex].size() == 0 && outgoingNeighborhood_[vertex - htd::first_vertex].size() == 0)
            {
                ret++;
            }
        }
    }

    return ret;
}

void htd::DirectedGraph::getIsolatedVertices(htd::vertex_container & output) const
{
    for (htd::vertex_t vertex = 0; vertex < size_; vertex++)
    {
        if (isVertex(vertex))
        {
            if (incomingNeighborhood_[vertex - htd::first_vertex].size() == 0 && outgoingNeighborhood_[vertex - htd::first_vertex].size() == 0)
            {
                output.push_back(vertex);
            }
        }
    }
}

htd::vertex_t htd::DirectedGraph::isolatedVertex(htd::index_t index) const
{
    htd::vertex_t ret = htd::unknown_vertex;

    htd::vertex_container result;

    getIsolatedVertices(result);

    if (index < result.size())
    {
        ret = result[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::DirectedGraph::isolatedVertex(htd::index_t) const");
    }

    return ret;
}

bool htd::DirectedGraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = incomingNeighborhood_[vertex - htd::first_vertex].size() == 0 && outgoingNeighborhood_[vertex - htd::first_vertex].size() == 0;
    }

    return ret;
}

void htd::DirectedGraph::getEdges(htd::edge_container & output) const
{
    for (size_t vertex1 = 0; vertex1 < size_; vertex1++)
    {
        for (auto& vertex2 : outgoingNeighborhood_[vertex1])
        {
            output.push_back(edge_t(vertex1, vertex2));
        }
    }
}

void htd::DirectedGraph::getEdges(htd::edge_container & output, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        for (auto& vertex2 : outgoingNeighborhood_[vertex])
        {
            output.push_back(edge_t(vertex, vertex2));
        }
    }
    else
    {
        throw std::out_of_range("htd::DirectedGraph::getEdges(htd::edge_container&, id_t)");
    }
}

const htd::edge_t & htd::DirectedGraph::edge(htd::index_t index) const
{
    HTD_UNUSED(index);

    //TODO Implement
    throw std::out_of_range("const htd::edge_t & htd::DirectedGraph::edge(htd::index_t) const");
}

const htd::edge_t & htd::DirectedGraph::edge(htd::index_t index, htd::vertex_t vertex) const
{
    HTD_UNUSED(index);
    HTD_UNUSED(vertex);

    //TODO Implement
    throw std::out_of_range("const htd::edge_t & htd::DirectedGraph::edge(htd::index_t, htd::vertex_t) const");
}

void htd::DirectedGraph::getHyperedges(htd::hyperedge_container & output) const
{
    for (size_t vertex1 = 0; vertex1 < size_; vertex1++)
    {
        for (auto& vertex2 : outgoingNeighborhood_[vertex1])
        {
            hyperedge_t hyperedge;

            if (vertex1 < vertex2)
            {
                hyperedge.push_back(vertex1);
                hyperedge.push_back(vertex2);
            }
            else
            {
                hyperedge.push_back(vertex2);
                hyperedge.push_back(vertex1);
            }

            output.push_back(hyperedge);
        }
    }
}

void htd::DirectedGraph::getHyperedges(htd::hyperedge_container & output, htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::out_of_range("htd::DirectedGraph::edges(htd::hyperedge_container&, id_t)");
    }
    
    //TODO Covered by check above?
    if (std::find(deletions_.begin(), deletions_.end(), vertex) == deletions_.end())
    {
        for (auto& vertex2 : outgoingNeighborhood_[vertex])
        {
            htd::hyperedge_t hyperedge;

            if (vertex < vertex2)
            {
                hyperedge.push_back(vertex);
                hyperedge.push_back(vertex2);
            }
            else
            {
                hyperedge.push_back(vertex2);
                hyperedge.push_back(vertex);
            }

            output.push_back(hyperedge);
        }
    }
}

const htd::hyperedge_t & htd::DirectedGraph::hyperedge(htd::index_t index) const
{
    HTD_UNUSED(index);

    //TODO Implement
    throw std::out_of_range("const htd::hyperedge_t & htd::DirectedGraph::hyperedge(htd::index_t) const");
}

const htd::hyperedge_t & htd::DirectedGraph::hyperedge(htd::index_t index, htd::vertex_t vertex) const
{
    HTD_UNUSED(index);
    HTD_UNUSED(vertex);

    //TODO Implement
    throw std::out_of_range("const htd::hyperedge_t & htd::DirectedGraph::hyperedge(htd::index_t, htd::vertex_t) const");
}

htd::vertex_t htd::DirectedGraph::addVertex(void)
{
    htd::vertex_t ret = next_vertex_;

    size_++;

    next_vertex_++;

    incomingNeighborhood_.push_back(std::set<htd::vertex_t>());

    outgoingNeighborhood_.push_back(std::set<htd::vertex_t>());

    return ret;
}

void htd::DirectedGraph::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        for (auto incomingNeighbor : incomingNeighborhood_[vertex])
        {
            outgoingNeighborhood_[incomingNeighbor].erase(vertex);
        }
        
        for (auto outgoingNeighbor : outgoingNeighborhood_[vertex])
        {
            incomingNeighborhood_[outgoingNeighbor].erase(vertex);
        }
        
        outgoingNeighborhood_[vertex].clear();

        deletions_.insert(vertex);
    }
}

void htd::DirectedGraph::removeVertex(htd::vertex_t vertex, bool addNeighborClique)
{
    if (isVertex(vertex))
    {
        for (auto neighbor1 : incomingNeighborhood_[vertex])
        {
            if (addNeighborClique && neighbor1 != vertex)
            {
                for (auto neighbor2 : incomingNeighborhood_[vertex])
                {
                    if (neighbor1 != neighbor2 && neighbor2 != vertex)
                    {
                        outgoingNeighborhood_[neighbor1].insert(neighbor2);
                        outgoingNeighborhood_[neighbor2].insert(neighbor1);

                        incomingNeighborhood_[neighbor1].insert(neighbor2);
                        incomingNeighborhood_[neighbor2].insert(neighbor1);
                    }
                }

                for (auto neighbor2 : outgoingNeighborhood_[vertex])
                {
                    if (neighbor1 != neighbor2 && neighbor2 != vertex)
                    {
                        outgoingNeighborhood_[neighbor1].insert(neighbor2);
                        outgoingNeighborhood_[neighbor2].insert(neighbor1);

                        incomingNeighborhood_[neighbor1].insert(neighbor2);
                        incomingNeighborhood_[neighbor2].insert(neighbor1);
                    }
                }
            }
            
            outgoingNeighborhood_[neighbor1].erase(vertex);
        }
        
        for (auto neighbor1 : outgoingNeighborhood_[vertex])
        {
            if (addNeighborClique && neighbor1 != vertex)
            {
                for (auto neighbor2 : incomingNeighborhood_[vertex])
                {
                    if (neighbor1 != neighbor2 && neighbor2 != vertex)
                    {
                        outgoingNeighborhood_[neighbor1].insert(neighbor2);
                        outgoingNeighborhood_[neighbor2].insert(neighbor1);

                        incomingNeighborhood_[neighbor1].insert(neighbor2);
                        incomingNeighborhood_[neighbor2].insert(neighbor1);
                    }
                }

                for (auto neighbor2 : outgoingNeighborhood_[vertex])
                {
                    if (neighbor1 != neighbor2 && neighbor2 != vertex)
                    {
                        outgoingNeighborhood_[neighbor1].insert(neighbor2);
                        outgoingNeighborhood_[neighbor2].insert(neighbor1);

                        incomingNeighborhood_[neighbor1].insert(neighbor2);
                        incomingNeighborhood_[neighbor2].insert(neighbor1);
                    }
                }
            }
            
            incomingNeighborhood_[neighbor1].erase(vertex);
        }
        
        outgoingNeighborhood_[vertex].clear();

        deletions_.insert(vertex);
    }
}

void htd::DirectedGraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        outgoingNeighborhood_[vertex1].insert(vertex2);
        incomingNeighborhood_[vertex2].insert(vertex1);
    }
}


void htd::DirectedGraph::addEdge(const htd::edge_t & edge)
{
    if (isVertex(edge.first) && isVertex(edge.second))
    {
        outgoingNeighborhood_[edge.first].insert(edge.second);
        incomingNeighborhood_[edge.second].insert(edge.first);
    }
}

void htd::DirectedGraph::removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        outgoingNeighborhood_[vertex1].erase(vertex2);
        incomingNeighborhood_[vertex2].erase(vertex1);
    }
}

void htd::DirectedGraph::removeEdge(const htd::edge_t & edge)
{
    if (isVertex(edge.first) && isVertex(edge.second))
    {
        outgoingNeighborhood_[edge.first].erase(edge.second);
        incomingNeighborhood_[edge.second].erase(edge.first);
    }
}

#endif /* HTD_HTD_DIRECTEDGRAPH_CPP */
