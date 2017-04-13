//
//  vbo.hpp
//  DCPPTest
//
//  Created by Jorge López on 27/3/17.
//
//

#ifndef vbo_hpp
#define vbo_hpp

#include <map>

#include "containers/array.h"

#include "glwraps.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	template <typename ArrayType>
	class CVBO
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
	public:
		static CVBO<ArrayType>& Create(ArrayType* array, const EVBOUsage usage);
		static void Delete(const CVBO<ArrayType>& vbo);
		
		static void Activate(const CVBO<ArrayType>& vbo);
		static void Submit(const CVBO<ArrayType>& vbo, size_t primitiveSize);
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const unsigned int	Id()		const { return m_id; }
		const EVBOTarget	Target()	const { return m_target; }
		const EVBOUsage		Usage()		const { return m_usage; }
		const ArrayType*	DataArray() const { return m_dataArray; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	private:
		CVBO (const unsigned int identifier, const EVBOTarget target, const EVBOUsage usage, ArrayType* dataArray):
		m_id(identifier),
		m_target(target),
		m_usage(usage),
		m_dataArray(dataArray)
		{}

		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		unsigned int	m_id;
		EVBOTarget		m_target;
		EVBOUsage		m_usage;
		ArrayType*		m_dataArray;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	template<typename ArrayType>
	using TVBOMap = std::map<unsigned int, CVBO<ArrayType>>;
	
	// ===========================================================
	// Template implementation
	// ===========================================================
	
	template<typename ArrayType>
	inline
	CVBO<ArrayType>& CVBO<ArrayType>::Create(ArrayType* array, const EVBOUsage usage)
	{
		GLuint identifier;
		glGenBuffers(1, &identifier);
		return CVBO<ArrayType>((unsigned int)identifier, usage, array);
	}
	
	template<typename ArrayType>
	inline
	void CVBO<ArrayType>::Delete(const CVBO<ArrayType>& vbo)
	{
		const GLuint identifier = (GLuint)vbo.Id();
		glDeleteBuffers(1, &identifier);
	}
	
	template<typename ArrayType>
	inline
	void CVBO<ArrayType>::Activate(const CVBO<ArrayType>& vbo)
	{
		const GLuint identifier = (GLuint)vbo.Id();
		glBindBuffer(vbo.Target(), identifier);
	}
	
	template<typename ArrayType>
	inline
	void CVBO<ArrayType>::Submit(const CVBO<ArrayType>& vbo, size_t primitiveSize)
	{
		const ArrayType* arrayData = vbo.DataArray();
		const GLuint identifier = (GLuint)vbo.Id();
		glBindBuffer(vbo.Target(), identifier);
		glBufferData(vbo.Target(), arrayData->CurrentSize()*primitiveSize, arrayData, vbo.Usage());
	}
}

#endif /* vbo_hpp */
