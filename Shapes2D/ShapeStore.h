#pragma once
#include "List.h"
#include "ShapeWizard.h"

namespace Shapes2D {

	template<typename TFloat>
	class ShapeStore {

		class ListNode;

		List<ListNode> list;

	public:	

		void AddShape(ShapeType shapeType) {
			list.Add(ListNode(ShapeWizard<TFloat>::CreateShape(shapeType), shapeType));
		}

		class ListNode {
		public:
			ListNode(Shape<TFloat> *shape, ShapeType shapeType) :
				shape(shape),
				shapeType(shapeType) 
			{
			}

			Shape<TFloat> *shape;
			ShapeType shapeType;
		};		
	};
}

