#ifndef CHARMAP_H
#define CHARMAP_H
#include <vector>
#include <iterator>
#include <initializer_list>
#include <cstring>

template <typename T>
struct CharMap
{
  private:
    typedef std::pair<const char *, T> key_value_pair;
    std::vector<key_value_pair> m_map;

  public:
    typedef typename std::vector<key_value_pair>::const_iterator const_map_iterator;
    CharMap() = default;
    CharMap(const std::initializer_list<key_value_pair> &init) : m_map{init}
    {
    }
    const_map_iterator begin() const
    {
        return m_map.begin();
    }
    const_map_iterator end() const
    {
        return m_map.end();
    }
    const_map_iterator find(const char *key) const
    {
        for (auto it = m_map.begin(); it != m_map.end(); it++)
        {
            if (std::strcmp(it->first, key) == 0)
                return it;
        }
        return end();
    }

    T &operator[](const char *key)
    {
        for (auto &pair : m_map)
        {
            if (std::strcmp(key, pair.first) == 0)
                return pair.second;
        }
        T temp[1] = {};
        T &obj = temp[0];
        return obj;
    }
    void insert(const key_value_pair &keyValuePair)
    {
        m_map.push_back(keyValuePair);
    }
    void insert(const char *key, const T &value)
    {
        m_map.push_back(make_pair(key, value));
    }
    void erase(const_map_iterator keyItr)
    {
        m_map.erase(keyItr);
    }
    void clear()
    {
        m_map.clear();
    }
};

#endif //CHARMAP_H
