//
//  transform.h
//  BitThemAll
//
//  Created by Jorge López González on 27/12/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef BitThemAll_transform_h
#define BitThemAll_transform_h

#include "math/matrix.h"

#include "component.h"

#include <vector>

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	/**
	 * \class
	 * \brief
	 * \author Jorge Lopez Gonzalez
	 *
	 * Description.
	 */
	class CTransform : public CComponent
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		RTTI_DECLARATIONS(CTransform, CComponent)
		
	public:
		typedef std::vector<CTransform*>	TTransformList;
		typedef TTransformList::iterator	TTransformIterator;
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		// Getters
		const math::Matrix4x4f&	LocalMatrix() const { return m_matrix; }
		const math::Matrix4x4f	WorldMatrix() const;
		
		const TTransformList	Childs() const { return ml_childs; }
		TTransformIterator		Begin() { return ml_childs.begin(); }
		TTransformIterator		End() { return ml_childs.end(); }
		
		CTransform*				Root() const { return mp_root; }
		CTransform*				Parent() const { return mp_parent; }
		
		void					Parent(CTransform* parent);
		
		math::Vector3f			LocalPos() const { return m_matrix.Translation(); }
		math::Vector3f			WorldPos() const { return WorldMatrix().Translation(); }
		
		math::Vector3f			LocalEulerAngles() const { return m_matrix.EulerAngles(); }
		math::Vector3f			WorldEulerAngles() const { return WorldMatrix().EulerAngles(); }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CTransform()
		{
			Reset();
		}
		
		~CTransform() {}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Reset();
		
		void AddChild(CTransform* child);
		
		void Translate(const math::Vector3f& position);
		void Rotate(const math::Vector3f& rotation);
		void Scale(const math::Vector3f& scale);
		
		// Transforms position from local space to world space.
		math::Vector3f TransformPosition(const math::Vector3f& point);
		
		// ===========================================================
		// Fields
		// ===========================================================
        
    private:
		CTransform*			mp_root;    // Topmost transform in the hierarchy
		CTransform*			mp_parent;  // Transform parent

		math::Matrix4x4f	m_matrix;   // Local
		TTransformList		ml_childs;
    };
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif