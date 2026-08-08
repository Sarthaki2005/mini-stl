#include <iostream>
#include <functional>
#include <string>
using namespace std;
template <typename K, typename V>
class HashMap
{
  struct Node
  {
    K key;
    V val;
    Node *next;
    Node(const K &k, const V &v) : key(k), val(v), next(nullptr) {}
  };
  size_t bucket_cnt;
  size_t size_;
  Node **buckets;
  float max_load_factor_;

public:
  HashMap(size_t capacity = 8) : bucket_cnt(capacity), size_(0), max_load_factor_(0.75f)
  {
    buckets = new Node *[bucket_cnt];
    for (size_t i = 0; i < bucket_cnt; i++)
    {
      buckets[i] = nullptr;
    }
  }

  size_t getBucketIndex(const K &key) const
  {
    return std::hash<K>{}(key) % bucket_cnt;
  }

  float load_factor() const
  {
    return static_cast<float>(size_) / bucket_cnt;
  }

  float max_load_factor() const
  {
    return max_load_factor_;
  }

  void max_load_factor(float value)
  {
    max_load_factor_ = value;
  }

  void insert(const K &key, const V &val)
  {
    size_t index = getBucketIndex(key);
    Node *current = buckets[index];
    while (current != nullptr)
    {
      if (current->key == key)
      {
        current->val = val;
        return;
      }
      current = current->next;
    }
    Node *newNode = new Node(key, val);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    size_++;
    if (load_factor() > max_load_factor_)
    {
      rehash(2 * bucket_cnt);
    }
  }

  void rehash(size_t new_bucket_cnt)
  {
    Node **new_buckets = new Node *[new_bucket_cnt];
    for (size_t i = 0; i < new_bucket_cnt; i++)
    {
      new_buckets[i] = nullptr;
    }
    for (size_t i = 0; i < bucket_cnt; i++)
    {
      Node *current = buckets[i];
      while (current != nullptr)
      {
        Node *next = current->next;
        size_t index = std::hash<K>{}(current->key) % new_bucket_cnt;

        current->next = new_buckets[index];
        new_buckets[index] = current;
        current = next;
      }
    }
    delete[] buckets;
    buckets = new_buckets;
    bucket_cnt = new_bucket_cnt;
  }

  V *get(const K &key) const
  {
    size_t index = std::hash<K>{}(key) % bucket_cnt;
    Node *current = buckets[index];
    while (current != nullptr)
    {
      if (current->key == key)
      {
        return &current->val;
      }
      current = current->next;
    }
    return nullptr;
  }

  bool contains(const K &key) const
  {
    return get(key) != nullptr;
  }

  bool erase(const K &key)
  {
    size_t index = getBucketIndex(key);
    Node *current = buckets[index];
    Node *prevNode = nullptr;
    while (current != nullptr)
    {
      if (current->key == key)
      {
        if (prevNode == nullptr)
        {
          buckets[index] = current->next;
        }
        else
        {
          prevNode->next = current->next;
        }
        delete current;
        size_--;
        return true;
      }
      prevNode = current;
      current = current->next;
    }
    return false;
  }

  ~HashMap()
  {
    for (size_t i = 0; i < bucket_cnt; i++)
    {
      Node *current = buckets[i];
      while (current != nullptr)
      {
        Node *next = current->next;
        delete current;
        current = next;
      }
    }
    delete[] buckets;
  }

  void reserve(size_t n)
  {
    size_t req_buckets = static_cast<size_t>(n / max_load_factor_) + 1;
    if (req_buckets > bucket_cnt)
      rehash(req_buckets);
  }
};
