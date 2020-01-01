/** \file assetManager.h
*	\brief
*/

#pragma once
#include <map>
#include <memory>

/**	\class
	*	\brief
	*/

template <class G>
class AssetManager
{
private:
	std::map<std::string,std::shared_ptr<G>> m_container; //!< Data structure to hold assets
public:
	bool contains(const std::string& key); //!< Is this item in the container already
	void add(const std::string& key, std::shared_ptr<G>& element); //!< Add element to the container
	std::shared_ptr<G> get(const std::string& key); //!< Get a point to an asset. Return nullptr if not found

};

template<class G>
inline bool AssetManager<G>::contains(const std::string & key)
{
	if (m_container[key] != nullptr)
	{
		return true;
	}
	else
	{
		return false
	}
}

template<class G>
inline void AssetManager<G>::add(const std::string & key, std::shared_ptr<G>& element)
{
	m_container.insert(std::pair(key, element));
}

template<class G>
inline std::shared_ptr<G> AssetManager<G>::get(const std::string & key)
{
	return m_container[key];
}

