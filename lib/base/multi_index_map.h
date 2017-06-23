#pragma once

#include <cstdint>
#include <map>
#include <unordered_map>
#include <type_traits>

namespace terra
{
	template<typename PrimaryKey, typename ForeignKey0, typename Value, bool hash = false>
	class MultiKeyIndexMap1
	{
	private:
		typedef typename std::conditional<hash, std::unordered_map<PrimaryKey, Value>, std::map<PrimaryKey, Value>>::type MapKV;
		typedef typename std::conditional<hash, std::unordered_map<ForeignKey0, PrimaryKey>, std::map<ForeignKey0, PrimaryKey>>::type MapFP;
		typedef typename std::conditional<hash, std::unordered_map<PrimaryKey, ForeignKey0>, std::map<PrimaryKey, ForeignKey0>>::type MapPF;
		MapKV kv_;
		MapFP fk2pk_;
		MapPF pk2fk_;

	public:
		void InsertPKeyValue(const PrimaryKey& pkey, Value&& val);
		void InsertPKeyValue(const PrimaryKey& pkey, const Value& val);
		void SetFKey2PKey(const ForeignKey0&fkey, const PrimaryKey& pkey);

		Value* GetValueByPrimaryKey(const PrimaryKey& pkey);
		Value* GetValueByForeignkey(const ForeignKey0& fkey);

		std::size_t EraseValueByPrimaryKey(const PrimaryKey& pkey);
		std::size_t EraseValueByForeignkey(const ForeignKey0& fkey);
		std::size_t EraseForeignKeyOnly(const ForeignKey0& fkey);

		MapKV&  get_kv_map() { return kv_; }
		MapFP&  get_fk2pk_map() { return fk2pk_; }
		MapPF&  get_pk2fk_map() { return pk2fk_; }
	};

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	void MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::InsertPKeyValue(const PrimaryKey& pkey, Value&& val)
	{
		kv_[pkey] = std::move(val);
	}

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	void MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::InsertPKeyValue(const PrimaryKey& pkey, const Value& val)
	{
		kv_[pkey] = val;
	}

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	void MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::SetFKey2PKey(const ForeignKey0& fkey, const PrimaryKey& pkey)
	{
		fk2pk_[fkey] = pkey;
		pk2fk_[pkey] = fkey;
	}

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	Value* MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::GetValueByPrimaryKey(const PrimaryKey& pkey)
	{
		auto iter = kv_.find(pkey);
		if (iter == kv_.end()) {
			return nullptr;
		}
		return &(iter->second);
	}

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	Value* MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::GetValueByForeignkey(const ForeignKey0& fkey)
	{
		auto iter1 = fk2pk_.find(fkey);
		if (iter1 == fk2pk_.end()) {
			return nullptr;
		}
		auto iter2 = kv_.find(iter1->second);
		if (iter2 == kv_.end())
		{
			return nullptr;
		}
		return &(iter2->second);
	}

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	std::size_t MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::EraseValueByPrimaryKey(const PrimaryKey& pkey)
	{
		auto iter = pk2fk_.find(pkey);
		if (iter != pk2fk_.end())
		{
			fk2pk_.erase(iter->second);
			pk2fk_.erase(iter);
		}
		return kv_.erase(pkey);
	}

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	std::size_t MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::EraseValueByForeignkey(const ForeignKey0& fkey)
	{
		auto iter = fk2pk_.find(fkey);
		assert(iter != fk2pk_.end());
		if (iter == fk2pk_.end())
		{
			return 0;
		}
		pk2fk_.erase(iter->second);
		fk2pk_.erase(iter);
		return kv_.erase(iter->second);
	}

	template<typename PrimaryKey, typename ForeignKey0, typename Value>
	std::size_t MultiKeyIndexMap1<PrimaryKey, ForeignKey0, Value>::EraseForeignKeyOnly(const ForeignKey0& fkey)
	{
		auto iter = fk2pk_.find(fkey);
		assert(iter != fk2pk_.end());
		if (iter == fk2pk_.end())
		{
			return 0;
		}
		pk2fk_.erase(iter->second);
		return fk2pk_.erase(iter);
	}
}