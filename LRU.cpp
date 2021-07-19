#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

template<typename KeyT, typename ValueT>
class LRUCache
{
public:
	//定义别名
	typedef std::pair<KeyT, ValueT> Pair;
	typedef std::list<Pair> List;
	typedef std::unordered_map<KeyT, typename List::iterator> Map;

	//有构造函数
	explicit LRUCache(int cap);
	//析构函数
	~LRUCache();

	//加入数据
	bool put(KeyT key, ValueT value);
	//获取数据
	bool get(KeyT key, ValueT* pValue);

	//获取链表大小
	std::size_t size() const;

	//拷贝构造函数被禁用
	LRUCache(const LRUCache&) = delete;
	//拷贝复制函数被禁用
	LRUCache& operator=(const LRUCache&) = delete;


private:
	int m_capacity;	//阈值, 当链表超过该值时需要进行某位淘汰
	List m_list; 	//链表
	Map m_map;		//哈希表
};

template <typename KeyT, typename ValueT>
LRUCache<KeyT, ValueT>::LRUCache(int cap): m_capacity(cap){}

template <typename KeyT, typename ValueT>
LRUCache<KeyT, ValueT>:: ~LRUCache()
{
	m_list.clear();
	m_map.clear();
}

template <typename KeyT, typename ValueT>
std::size_t LRUCache<KeyT, ValueT>::size() const
{
	return m_list.size();
}

template <typename KeyT, typename Value>
{
	//查找key是否在哈希表中
	typename Map::iterator itor = m_map.find(key);
	//如果存在，则要将老数据从哈希表和链表中删除
	if(itor != m_map.end())
	{
		//从链表里删除老数据
		m_list.erase(itor->second);
		//从哈希表中删除老数据
		m_map.erase(itor);
	}

	//插入到链表头中
	m_list.push_front(std::make_pair(key, value));
	//将队头的链表节点存放到哈希表
	m_map[key] = m_list.begin();

	//当链表大小超过阈值后，要进行末尾删除
	if(m_list.size() > m_capacity)
	{
		//获取链表末尾的key值，以便哈希表能删除此节点
		KeyT endKey = m_list.back().first;
		//移除链表末尾的节点
		m_list.pop_back();
		//从哈希表中删除该节点
		m_map.erase(endKey);
	}

	return true;
}

template <typename KeyT, typename ValueT>
bool LRUCache<KeyT, ValueT>::get(KeyT key, ValueT* pValue)
{
	//查找key是否在哈希表
	typename Map::iterator mapItor = m_map.find(key);
	//如果不存在，则返回false
	if(mapItor == m_map.end())
	{
		return false;
	}

	//如果存在：
	//1. 链表要将数据删除
	//2. 再将数据加入到链表队头
	//目的是为了维持链表队头是最近访问的数据

	//取出哈希表的value值，也就是链表节点
	typename List::iterator listItor = mapItor->second;

	//创建新的键值对
	std::pair<KeyT, ValueT> listPair = std::make_pair(listItor->first, listItor->second);

	//从链表中删除该节点
	m_list.erase(listItor);

	//将数据加入到队头
	m_list.push_front(listPair);

	//更新哈希表
	m_map[key] = m_list.begin();

	//取出链表节点内容key-value的value值，然后赋值
	*pValue = listPair.second;

	return true;
}

