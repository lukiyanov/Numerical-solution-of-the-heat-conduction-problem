#pragma once
#include <string.h>
#include <stdexcept>

namespace solution
{
	// ƒвумерна€ матрица. ћаксимальное быстродействие, минимум проверок.
	template <class T> class Matrix2D
	{
		const size_t m_sizeX, m_sizeY, m_sizeTotal;
	public:
		T* m_pArray;
	public:
		Matrix2D(const size_t sizeX, const size_t sizeY);
		~Matrix2D();

		inline T& operator() (const size_t indexX, const size_t indexY);
		inline const Matrix2D& operator= (const Matrix2D& source);

		inline size_t GetSizeX() const { return m_sizeX; }
		inline size_t GetSizeY() const { return m_sizeY; }
		inline T* GetRawPointer(const size_t indexX, const size_t indexY);
	};

	// ----------------------------------------------------------------------------
	template <class T>
	Matrix2D<T>::Matrix2D(const size_t sizeX, const size_t sizeY) :
		m_sizeX(sizeX),
		m_sizeY(sizeY),
		m_sizeTotal(sizeX * sizeY)
	{
		if (!sizeX)
			throw std::exception("Got 0 as X size, Matrix3D<T>::Matrix3D(...)");
		if (!sizeY)
			throw std::exception("Got 0 as Y size, Matrix3D<T>::Matrix3D(...)");

		m_pArray = new T[m_sizeTotal];
	}

	// ----------------------------------------------------------------------------
	template <class T>
	Matrix2D<T>::~Matrix2D()
	{
		delete[] m_pArray;
	}

	// ----------------------------------------------------------------------------
	template <class T>
	T* Matrix2D<T>::GetRawPointer(const size_t indexX, const size_t indexY)
	{
#ifdef _DEBUG
		if (indexX >= m_sizeX)
			throw std::out_of_range("Out of range on X, Matrix3D<T>::operator()");

		if (indexY >= m_sizeY)
			throw std::out_of_range("Out of range on Y, Matrix3D<T>::operator()");
#endif // DEBUG

		return m_pArray + (indexY * m_sizeX + indexX);
	}

	// ----------------------------------------------------------------------------
	template <class T>
	T& Matrix2D<T>::operator() (const size_t indexX, const size_t indexY)
	{
#ifdef _DEBUG
		if (indexX >= m_sizeX)
			throw std::out_of_range("Out of range on X, Matrix3D<T>::operator()");

		if (indexY >= m_sizeY)
			throw std::out_of_range("Out of range on Y, Matrix3D<T>::operator()");
#endif // DEBUG

		// Ќе факт что компил€тор встроит вызов GetRawPointer, а нам нужна производительность.
		return m_pArray[indexY * m_sizeX + indexX];
	}

	// ----------------------------------------------------------------------------
	template <class T>
	const Matrix2D<T>& Matrix2D<T>::operator= (const Matrix2D<T>& source)
	{
#ifdef _DEBUG
		// ѕодразумеваетс€ что мы будем присваивать друг другу только матрицы одного размера.
		// ƒействительно, дл€ нашей простой задачи этого достаточно.
		if (m_sizeX != source.m_sizeX || m_sizeY != source.m_sizeY)
			throw std::domain_error("Incompatible size of matrixes in Matrix3D::operator=().");
#endif // DEBUG

		memcpy(m_pArray, source.m_pArray, sizeof(T) * m_sizeTotal);
		return *this;
	}

	// ----------------------------------------------------------------------------
}