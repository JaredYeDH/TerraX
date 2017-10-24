#pragma once

namespace terra
{
	template<typename I>
	struct type_traits
	{
		using value_type = I;
	};

	template<typename I>
	struct type_traits<I*> {
		using value_type = I;
	};

	template<typename I, std::size_t N>
	struct type_traits<I[N]> {
		using value_type = I;
	};

	template<typename T, bool = std::is_class_v<type_traits<T>::value_type>>
	struct Functor
	{
		static void Serilize(std::string& str, const T& val)
		{
			std::cout << "not class" << std::endl;
		}
	};

	template<typename T>
	struct Functor<T, true>
	{
		static void Serilize(std::string& str, const T& val)
		{
			std::cout << "class" << std::endl;
		}
	};

	template<typename T>
	struct Functor<T*, true>
	{
		static void Serilize(std::string& str, const T* val)
		{
			std::cout << "class pointer" << std::endl;
		}
	};

	template<typename T>
	struct Functor<T*, false>
	{
		static void Serilize(std::string& str, const T* val)
		{
			std::cout << "pointer" << std::endl;
		}
	};

	template<typename T, std::size_t N>
	struct Functor<T[N], true>
	{
		static void Serilize(std::string& str, T val[])
		{
			std::cout << "class array" << std::endl;
		}
	};

	template<typename T, std::size_t N>
	struct Functor<T[N], false>
	{
		static void Serilize(std::string& str, T val[])
		{
			std::cout << "array" << std::endl;
		}
	};

	/*
	//test case
	Functor<int>::Serilize(msg, a);
	const char* sz = "const char*";
	Functor<const char*>::Serilize(msg, sz);
	char arr[32] = "array";
	Functor<char[32]>::Serilize(msg, arr);

	CCCC* pccr = new CCCC;
	Functor<CCCC*>::Serilize(msg, pccr);

	CCCC carr[10];
	Functor<CCCC[10]>::Serilize(msg, carr);
	*/
}
