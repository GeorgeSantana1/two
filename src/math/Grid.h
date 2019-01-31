//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Axis.h>

#ifndef MUD_CPP_20
#include <stdint.h>
#endif

namespace mud
{
	export_ class Grided3
	{
	public:
		struct Dim
		{
		public:
			Dim() {}
			Dim(int period, size_t limit, int increment, size_t modulo, size_t divide)
				: m_period(period), m_limit(limit), m_increment(increment), m_modulo(modulo), m_divide(divide)
			{}

			size_t dim_index(size_t index) { return index % m_modulo / m_divide; }

			bool has_neighbour(size_t index) { return dim_index(index) != m_limit; }
			size_t neighbour_mod(size_t index) { return dim_index(index) == m_limit ? index + m_increment - m_period : index + m_increment; }
			size_t neighbour(size_t index) { return index + m_increment; }

		protected:
			int m_period;
			size_t m_limit;
			int m_increment;
			size_t m_modulo;
			size_t m_divide;
		};
	};

	export_ template <class T_Array>
	class Grided : public T_Array, public Grided3
	{
	public:
		typedef class T_Array::value_type T;

	public:
		Grided(size_t x, size_t y, size_t z)
			: T_Array(x*y*z), m_x(x), m_y(y), m_z(z), m_sq(x*y)
		{
			this->reset_dims();
		}

		Grided(size_t x, size_t y, size_t z, const T& val)
			: T_Array(x*y*z, val), m_x(x), m_y(y), m_z(z), m_sq(x*y)
		{
			this->reset_dims();
		}

		Grided(size_t s)
			: Grided(s, s, s)
		{}

		Grided()
			: Grided(0, 0, 0)
		{}

		Dim& dim(SignedAxis axis) { return m_dims[size_t(axis)]; }

		void reset_dims()
		{
			dim(SignedAxis::PlusX)  = {  int(m_x), m_x - 1, +1, m_x, 1 };
			dim(SignedAxis::MinusX) = { -int(m_x), 0, -1, m_x, 1 };
			dim(SignedAxis::PlusY)  = {  int(m_x*m_y), m_y - 1, +int(m_x), m_sq, m_x };
			dim(SignedAxis::MinusX) = { -int(m_x*m_y), 0, -int(m_x), m_sq, m_x };
			dim(SignedAxis::PlusZ)  = {  int(m_x*m_y*m_z), m_z - 1, +int(m_sq), SIZE_MAX, m_sq };
			dim(SignedAxis::MinusZ) = { -int(m_x*m_y*m_z), 0, -int(m_sq), SIZE_MAX, m_sq };
		}

		void clear(T val)
		{
			for(size_t i = 0; i < this->size(); ++i)
				(*this)[i] = val;
		}

		void reset(size_t x, size_t y, size_t z)
		{
			m_x = x; m_y = y; m_z = z; m_sq = x*y;
			this->reset_dims();
			this->resize(x*y*z);
		}
		
		void reset(size_t x, size_t y, size_t z, T val)
		{
			reset(x, y, z);
			clear(val);
		}

		inline T& at(size_t i) { return T_Array::operator[](i); }
		inline const T& at(size_t i) const { return T_Array::operator[](i); }

		inline T& at(size_t x, size_t y, size_t z = 0) { return at(x + y*m_x + z*m_sq); }
		inline const T& at(size_t x, size_t y, size_t z = 0) const { return at(x + y*m_x + z*m_sq); }

		inline T* safe_at(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &at(x, y, z); }
		
		inline size_t index_at(size_t x, size_t y, size_t z) { return x + y*m_x + z*m_sq; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

		bool border(size_t index, Side direction) { return !m_dims[size_t(direction)].has_neighbour(index); }

		size_t neighbour_mod(size_t index, Side direction) { return m_dims[size_t(direction)].neighbour_mod(index); }
		size_t neighbour(size_t index, Side direction) { return m_dims[size_t(direction)].neighbour(index); }

		T& neighbour_item(size_t index, Side direction) { return at(neighbour(index, direction)); }

		T* safe_neighbour(size_t index, Side direction) { if(!border(index, direction)) return &neighbour_item(index, direction); return nullptr; }

		template <class T_Visitor>
		bool visit_near_dist(size_t x, size_t y, size_t z, size_t d, T_Visitor callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;

			size_t dsquare = d * d;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					if(!(i == x && j == y))
						if((x - i)*(x - i) + (y - j)*(y - j) <= dsquare)
							if(!callback(this->at(i, j, z)))
								return false;
			return true;
		}

		template <class T_Visitor>
		bool visit_near_2d(size_t x, size_t y, size_t z, size_t d, T_Visitor callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;

			//size_t dsquare = d*d;
			//if(sq(x - i) + sq(y - j) > dsquare)
			//	continue;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					if(!(i == x && j == y))
						if(!callback(this->at(i, j, z)))
							return false;
			return true;
		}

		template <class T_Visitor>
		bool visit_near(size_t x, size_t y, size_t z, size_t d, T_Visitor callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t zMin = z > d ? z - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;
			size_t zMax = z + d + 1 > m_z ? m_z : z + d + 1;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					for(size_t k = zMin; k < zMax; ++k)
						if(!(i == x && j == y && k == z))
							if(!callback(this->at(i, j, k)))
								return false;
			return true;
		}

		template <class T_Visitor>
		bool visit_near_dist(size_t index, size_t dist, T_Visitor callback)
		{
			return this->visit_near_dist(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		template <class T_Visitor>
		bool visit_near_2d(size_t index, size_t dist, T_Visitor callback)
		{
			return this->visit_near_2d(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		template <class T_Visitor>
		bool visit_near(size_t index, size_t dist, T_Visitor callback)
		{
			return this->visit_near(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		vector<T*> neighbours(size_t index, size_t dist)
		{
			vector<T*> result;
			this->visit_near(index, dist, [&](T& obj){ result.push_back(&obj); return true; });
			return result;
		}

		vector<T*> neighbours_2d(size_t index, size_t dist)
		{
			vector<T*> result;
			this->visit_near_2d(index, dist, [&](T& obj){ result.push_back(&obj); return true; });
			return result;
		}

	public:
		size_t m_x, m_y, m_z;
		size_t m_sq;

		//enum_array<Side, Dim> m_dims;
		Dim m_dims[6] = {};
	};

	export_ template <class T_Element>
	struct refl_ struct_ Grid : public Grided<vector<T_Element>>
	{
		using Grided<vector<T_Element>>::Grided;
	};


	export_ template <class T_Element>
	struct refl_ struct_ array3d : public vector<T_Element>
	{
	public:
		typedef T_Element T;

	public:
		array3d(size_t x, size_t y, size_t z)
			: vector<T_Element>(x*y*z), m_x(x), m_y(y), m_z(z)
		{}

		array3d(size_t x, size_t y, size_t z, const T& val)
			: vector<T_Element>(x*y*z, val), m_x(x), m_y(y), m_z(z)
		{}

		array3d(size_t s)
			: array3d(s, s, s)
		{}

		array3d()
			: array3d(0, 0, 0)
		{}

		void clear(T val)
		{
			for(size_t i = 0; i < this->size(); ++i)
				(*this)[i] = val;
		}

		void reset(size_t x, size_t y, size_t z)
		{
			m_x = x; m_y = y; m_z = z;
			this->resize(x*y*z);
		}

		void reset(size_t x, size_t y, size_t z, T val)
		{
			reset(x, y, z);
			clear(val);
		}

		inline T& at(size_t x, size_t y, size_t z = 0) { return vector<T_Element>::operator[](x + y*m_x + z*m_x*m_y); }
		inline const T& at(size_t x, size_t y, size_t z = 0) const { return vector<T_Element>::operator[](x + y*m_x + z*m_x*m_y); }
		inline T* safeAt(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &at(x, y, z); }

		inline size_t indexAt(size_t x, size_t y, size_t z) { return x + y*m_x + z*m_x*m_y; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

	public:
		size_t m_x, m_y, m_z;
	};

	export_ MUD_MATH_EXPORT func_ void grid(const uvec3& size, vector<uvec3>& output_coords);
	export_ MUD_MATH_EXPORT func_ vec3 grid_center(const uvec3& coord, const vec3& cell_size);

	export_ MUD_MATH_EXPORT func_ void index_list(uint32_t size, vector<uint32_t>& output_indices);
}
